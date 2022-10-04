void weapon_set() {
	Item* weapon = LocalPlayer::Entity()->GetActiveWeapon();
	if (weapon == nullptr) return;

	//-3 - hammer, -2 - bows, -1 - eoka, 0-nopatch, 1 - meele, 2 - semiautomatic, 3 - automatic
	Weapon target = weapon->Info();
	if (!target.id) return;
	if (!target.category) return;
	if (target.category == -2) {
		weapon->NoSway();
		weapon->FastBow();
		return;
	}
	if (target.category == 3) {
		weapon->NoSway();
		weapon->RapidFire();
		return;
	}
	if (target.category == 2) {
		weapon->NoSway();
		weapon->RapidFire();
		weapon->SetAutomatic();
		return;
	}
	if (target.category == -1) {
		weapon->NoSway();
		weapon->EokaTap();
		return;
	}
}
float w_last_syringe = 0.f;
bool w_healing = false;
void misc_set() {
	//if (w_last_syringe == 0.f) {
	//	w_last_syringe = LocalPlayer::Entity()->lastSentTickTime();
	//}
	//Item* weapon = LocalPlayer::Entity()->GetActiveWeapon();
	//if ((weapon->GetID() == 1079279582 || weapon->GetID() == -2072273936) && vars::misc::faster_healing) {
	//	typedef void(__stdcall* afamos1)(DWORD64, Str);
	//	DWORD64 Held = read(weapon + O::Item::heldEntity, DWORD64);
	//	write(Held + O::Item::heldEntity, 1.f, float); //disable animation
	//	float curtime = LocalPlayer::Entity()->GetTick();
	//	bool deployed = read(Held + 0x1A8, bool); // protected bool isDeployed;
	//	//0x800 secondary
	//	if (deployed && curtime > w_last_syringe + 0.5f) {
	//		if (w_healing) {
	//			afamos1 ss = (afamos1)((DWORD64)vars::stor::gBase + 0x7C0320); //public void ServerRPC(string funcName) { }
	//			ss(Held, Str(L"UseSelf"));
	//		}
	//		else curtime += 0.1f;
	//		w_last_syringe = curtime;
	//		w_healing = true;
	//	}
	//	else if (!deployed) {
	//		w_healing = false;
	//	}
	//}
	//else {
	//	w_healing = false;
	//}
	if (vars::misc::gravity) {
		if (GetAsyncKeyState(vars::keys::gravitykey))
			LocalPlayer::Entity()->SetGravity(vars::misc::gravity_modifier);
		else LocalPlayer::Entity()->SetGravity(2.5f);
	}
	auto klass = read(vars::stor::gBase + CO::ConvarGraphics, DWORD64);
	auto static_fields = read(klass + 0xB8, DWORD64);
	if (GetAsyncKeyState(vars::keys::zoom)) {
		write(static_fields + 0x18, 10.f, float);
	}
	else {
		write(static_fields + 0x18, vars::misc::fov, float);
	}
	if (vars::misc::spiderman) {
		uintptr_t Movement = read(LocalPlayer::Entity() + O::BasePlayer::movement, uintptr_t);
		write(Movement + O::PlayerWalkMovement::groundAngle, 0.f, float);
		write(Movement + O::PlayerWalkMovement::groundAngleNew, 0.f, float);
	}
	LocalPlayer::Entity()->PatchCamspeed();
	if (vars::misc::fakeadmin)
		LocalPlayer::Entity()->FakeAdmin();
}
namespace lol {
	void do_attack(f_object target, uintptr_t Held, bool transform) {
		if (!target.valid || !Held) return;

		if (read(Held + O::AttackEntity::nextAttackTime, float) >= Time::time()) { return; }
		if (read(Held + O::AttackEntity::timeSinceDeploy, float) < read(Held + O::AttackEntity::deployDelay, float)) { return; }

		uintptr_t staticHitTest = read(vars::stor::gBase + CO::HitTest, DWORD64); if (!staticHitTest) return;
		uintptr_t newHitTest = il2cpp::il2cpp_object_new1(staticHitTest); if (!newHitTest) return;

		uintptr_t trans; Ray ray = Ray(LocalPlayer::Entity()->get_bone_pos(neck), (target.position - LocalPlayer::Entity()->get_bone_pos(neck)).Normalized());
		if (!target.entity) return;
		if (transform) {
			trans = reinterpret_cast<BasePlayer*>(target.entity)->mono_transform(head);
		}
		else {
			//trans = utils::GetTransform((DWORD64)target.entity);
			trans = (DWORD64)reinterpret_cast<Object*>(target.entity)->transform();
		} if (!trans) {
			//LogSystem::Log(xorstr(L"No transform found"), 1.f);
			return;
		}

		write(newHitTest + O::HitTest::MaxDistance, 1000.f, float);
		write(newHitTest + O::HitTest::HitTransform, trans, uintptr_t);
		write(newHitTest + O::HitTest::AttackRay, ray, Ray);
		write(newHitTest + O::HitTest::DidHit, true, bool);
		write(newHitTest + O::HitTest::HitEntity, reinterpret_cast<BasePlayer*>(target.entity), BasePlayer*);
		write(newHitTest + O::HitTest::HitPoint, reinterpret_cast<Transform*>(trans)->InverseTransformPoint(target.position), Vector3);
		write(newHitTest + O::HitTest::HitNormal, reinterpret_cast<Transform*>(trans)->InverseTransformPoint(target.position), Vector3);
		write(newHitTest + O::HitTest::damageProperties, read(Held + O::BaseMelee::damageProperties, uintptr_t), uintptr_t);
		reinterpret_cast<void(*)(uintptr_t, float)>(vars::stor::gBase + CO::StartAttackCooldown)(Held, read(Held + O::AttackEntity::repeatDelay, float));
		return reinterpret_cast<void(*)(uintptr_t, uintptr_t)>(vars::stor::gBase + CO::ProcessAttack)(Held, newHitTest);
	}
	// 0, -9.1 * gravityModifier, 0
	TraceResult traceProjectile(Vector3 position, Vector3 velocity, float drag, Vector3 gravity, Vector3 targetPoint) {
		constexpr float num = 0.03125f;
		Vector3 prevPosition = position;
		float prevDist = FLT_MAX;
		Line resultLine = Line(position, position);
		float travelTime = 0.f;
		TraceResult result;

		for (; travelTime < 8.f; ) {
			prevPosition = position;
			position += velocity * num;

			Line line = Line(prevPosition, position);
			Vector3 nearest = line.ClosestPoint(targetPoint);

			float dst = (nearest - targetPoint).Length();

			if (dst > prevDist) {
				break;
			}
			prevDist = dst;
			resultLine = line;

			velocity += gravity * num;
			velocity -= velocity * drag * num;
			travelTime += num;
		}

		Vector3 hitPos = resultLine.ClosestPoint(targetPoint);

		result.hitDist = (hitPos - targetPoint).Length();
		result.hitPosition = hitPos;
		result.outVelocity = velocity;
		result.hitTime = travelTime - num;
		return result;
	};
	uintptr_t shader;
	int property;
	float LastUpdate = 0.f;
	void update_chams() {
	//	if (LocalPlayer::Entity()->lastSentTickTime() > LastUpdate + 15.f) {
	//		reinterpret_cast<void(*)()>(vars::stor::gBase + CO::RebuildAll)();
	//		LastUpdate = LocalPlayer::Entity()->lastSentTickTime();
	//	}
	}
	float LastGrade = 0.f;
	void auto_grade(uintptr_t buildingblocc) {
		BuildingBlock* block = reinterpret_cast<BuildingBlock*>(buildingblocc);
		//LogSystem::Log(xorstr(L"xd"), 5.f);
		if (LocalPlayer::Entity()->lastSentTickTime() > LastGrade + 0.35f
			&& block->CanAffordUpgrade((BuildingGrade)vars::misc::grade_, LocalPlayer::Entity())
			&& block->CanChangeToGrade((BuildingGrade)vars::misc::grade_, LocalPlayer::Entity())
			&& !block->IsUpgradeBlocked()) {
			block->UpgradeToGrade((BuildingGrade)vars::misc::grade_, LocalPlayer::Entity());
			LastGrade = LocalPlayer::Entity()->lastSentTickTime();
		}
	}
	float LastKnock = 0.f; float LastOpen = 0.f; float LastHatch = 0.f;
	void knocker(uintptr_t Door) {
		typedef void(__stdcall* DoorFunction)(uintptr_t, BasePlayer*);
		if (LocalPlayer::Entity()->lastSentTickTime() > LastKnock + 0.5f) {
			((DoorFunction)(vars::stor::gBase + CO::KnockDoor))(Door, LocalPlayer::Entity());
			LastKnock = LocalPlayer::Entity()->lastSentTickTime();
		}
		if (LocalPlayer::Entity()->lastSentTickTime() > LastOpen + 0.1f) {
			((DoorFunction)(vars::stor::gBase + CO::OpenDoor))(Door, LocalPlayer::Entity());
			LastOpen = LocalPlayer::Entity()->lastSentTickTime();
		}
		if (LocalPlayer::Entity()->lastSentTickTime() > LastHatch + 0.1f) {
			((DoorFunction)(vars::stor::gBase + CO::OpenHatch))(Door, LocalPlayer::Entity());
			LastHatch = LocalPlayer::Entity()->lastSentTickTime();
		}
	}
	float LastPickup = 0.f;
	void pickup_player(BasePlayer* ent) {
		typedef void(__stdcall* AssistPlayer)(BasePlayer*, BasePlayer*);
		if (!LocalPlayer::Entity()->is_teammate(ent->userID()) && vars::misc::revive_team_only) return;
		if (LocalPlayer::Entity()->lastSentTickTime() > LastPickup + 0.5f) {
			((AssistPlayer)(vars::stor::gBase + CO::AssistPlayer))(ent, LocalPlayer::Entity());
			LastPickup = LocalPlayer::Entity()->lastSentTickTime();
		}
	}
	void cachePlayer(BasePlayer* player) {
		auto model = player->model();
		if (model) {
			auto cache = new BoneCache();

			cache->head = model->resolve(STATIC_CRC32("head"));
			cache->neck = model->resolve(STATIC_CRC32("neck"));
			cache->root = model->resolve(STATIC_CRC32("root"));
			cache->spine4 = model->resolve(STATIC_CRC32("spine4"));
			cache->spine1 = model->resolve(STATIC_CRC32("spine1"));
			cache->l_clavicle = model->resolve(STATIC_CRC32("l_clavicle"));
			cache->l_upperarm = model->resolve(STATIC_CRC32("l_upperarm"));
			cache->l_forearm = model->resolve(STATIC_CRC32("l_forearm"));
			cache->l_hand = model->resolve(STATIC_CRC32("l_hand"));
			cache->r_clavicle = model->resolve(STATIC_CRC32("r_clavicle"));
			cache->r_upperarm = model->resolve(STATIC_CRC32("r_upperarm"));
			cache->r_forearm = model->resolve(STATIC_CRC32("r_forearm"));
			cache->r_hand = model->resolve(STATIC_CRC32("r_hand"));
			cache->pelvis = model->resolve(STATIC_CRC32("pelvis"));
			cache->l_hip = model->resolve(STATIC_CRC32("l_hip"));
			cache->l_knee = model->resolve(STATIC_CRC32("l_knee"));
			cache->l_ankle_scale = model->resolve(STATIC_CRC32("l_ankle_scale"));
			cache->l_foot = model->resolve(STATIC_CRC32("l_foot"));
			cache->r_hip = model->resolve(STATIC_CRC32("r_hip"));
			cache->r_knee = model->resolve(STATIC_CRC32("r_knee"));
			cache->r_ankle_scale = model->resolve(STATIC_CRC32("r_ankle_scale"));
			cache->r_foot = model->resolve(STATIC_CRC32("r_foot"));

			if (!map_contains_key(cachedBones, player->userID()))
				cachedBones.insert(std::make_pair(player->userID(), cache));
			else
				cachedBones[player->userID()] = cache;
		}
	}
	void auto_farm_loop(bool weaponmelee, uintptr_t active) {
		if (vars::misc::auto_pickup) {
			f_object entity = f_object::get_closest_object(LocalPlayer::Entity()->get_bone_pos(head),
				xorstr("/collectable/"),
				Vector3::Zero(),
				Vector3::Zero(),
				Vector3::Zero(),
				false
			);
			if (entity.valid) {
				Vector3 local = utils::ClosestPoint(LocalPlayer::Entity(), entity.position);
				if (Math::Distance_3D(local, entity.position) < 3.f) {
					if (reinterpret_cast<BaseEntity*>(entity.entity)->IsValid()) {
						utils::ServerRPC(entity.entity, Str(xorstr(L"Pickup")));
					}
				}
			}
		}
		if (vars::misc::auto_grade) {
			f_object building_block = f_object::get_closest_object(LocalPlayer::Entity()->get_bone_pos(head),
				xorstr(""),
				Vector3::Zero(),
				Vector3::Zero(),
				Vector3::Zero(),
				true,
				xorstr("BuildingBlock"));
			if (building_block.valid) {
				Vector3 local = utils::ClosestPoint(LocalPlayer::Entity(), building_block.position);
				if (Math::Distance_3D(local, building_block.position) <= 2.f) {
					if (reinterpret_cast<BaseEntity*>(building_block.entity)->IsValid()) {
						lol::auto_grade(building_block.entity);
					}
				}
			}
		}
		if (vars::misc::auto_farm_barrel) {
			if (weaponmelee) {
				f_object ore_hot_spot = f_object::get_closest_object(LocalPlayer::Entity()->get_bone_pos(head),
					xorstr("barrel"),
					Vector3::Zero(),
					Vector3::Zero(),
					Vector3::Zero(),
					false,
					xorstr(""));
				if (ore_hot_spot.valid) {
					Vector3 local = utils::ClosestPoint(LocalPlayer::Entity(), ore_hot_spot.position);
					if (Math::Distance_3D(local, ore_hot_spot.position) <= 2.f) {
						if (reinterpret_cast<BaseEntity*>(ore_hot_spot.entity)->IsValid()) {
							lol::do_attack(ore_hot_spot, active, false);
						}
					}
				}
			}
		}
		if (vars::misc::auto_farm_ore) {
			if (weaponmelee) {
				f_object ore_hot_spot = f_object::get_closest_object(LocalPlayer::Entity()->get_bone_pos(head),
					xorstr(""),
					Vector3::Zero(),
					Vector3::Zero(),
					Vector3::Zero(),
					true,
					xorstr("OreHotSpot"));
				if (ore_hot_spot.valid) {
					Vector3 local = utils::ClosestPoint(LocalPlayer::Entity(), ore_hot_spot.position);
					if (Math::Distance_3D(local, ore_hot_spot.position) <= 2.f) {
						if (reinterpret_cast<BaseEntity*>(ore_hot_spot.entity)->IsValid()) {
							lol::do_attack(ore_hot_spot, active, false);
						}
					}
				}
			}
		}
		if (vars::misc::auto_farm_tree) {
			if (weaponmelee) {
				f_object tree_entity = f_object::get_closest_object(LocalPlayer::Entity()->get_bone_pos(head),
					xorstr(""),
					Vector3::Zero(),
					Vector3::Zero(),
					Vector3::Zero(),
					true,
					xorstr("TreeEntity"));
				if (tree_entity.valid) {
					tree_entity.position = Vector3::Zero();
					f_object tree_marker = f_object::get_closest_object(LocalPlayer::Entity()->get_bone_pos(head),
						xorstr(""),
						Vector3::Zero(),
						Vector3::Zero(),
						Vector3::Zero(),
						true,
						xorstr("TreeMarker"));
					if (tree_marker.valid) {
						Vector3 locala = utils::ClosestPoint(LocalPlayer::Entity(), tree_marker.position);
						if (Math::Distance_3D(locala, tree_marker.position) <= 2.f) {
							tree_entity.position = tree_marker.position;
							Vector3 local = utils::ClosestPoint(LocalPlayer::Entity(), tree_entity.position);
							if (Math::Distance_3D(local, tree_entity.position) <= 2.f) {
								if (reinterpret_cast<BaseEntity*>(tree_entity.entity)->IsValid()) {
									lol::do_attack(tree_entity, active, false);
								}
							}
						}
					}
				}
			}
		}
	}
}
void TestFlying() {
	vars::stuff::flyhackPauseTime = Mathf::Max(0.f, vars::stuff::flyhackPauseTime - Time::deltaTime());
	bool inAir = false;
	float radius = reinterpret_cast<float(*)(BasePlayer*)>(vars::stor::gBase + CO::GetRadius)(LocalPlayer::Entity());
	float height = reinterpret_cast<float(*)(BasePlayer*, bool)>(vars::stor::gBase + CO::GetHeight)(LocalPlayer::Entity(), false);
	//Vector3 vector = (LocalPlayer::Entity()->lastSentTick()->position() + read(read<uintptr_t>(LocalPlayer::Entity() + 0x4c0) + 0x218)) * 0.5f; //internal Vector3 position; || public class PlayerModel : ListComponent<PlayerModel>, IOnParentDestroying 
	Vector3 vector = (LocalPlayer::Entity()->lastSentTick()->position() + read(read(LocalPlayer::Entity() + O::BasePlayer::lastSentTick, uintptr_t) + O::PlayerModel::position, Vector3)) * 0.5f; //internal Vector3 position;
	Vector3 vector2 = vector + Vector3(0.f, radius - 2.f, 0.f);
	Vector3 vector3 = vector + Vector3(0.f, height - radius, 0.f);
	float radius2 = radius - 0.05f;
	bool a = Physics::CheckCapsule(vector2, vector3, radius2, 1503731969, QueryTriggerInteraction::Ignore);
	inAir = !a;

	if (inAir) {
		bool flag = false;

		//Vector3 vector4 = read<Vector3>(read<uintptr_t>(LocalPlayer::Entity() + 0x4c0) + 0x218) - LocalPlayer::Entity()->lastSentTick()->position(); //internal Vector3 position; || public class PlayerModel : ListComponent<PlayerModel>, IOnParentDestroying 
		Vector3 vector4 = read(read(LocalPlayer::Entity() + O::BasePlayer::lastSentTick, uintptr_t) + O::PlayerModel::position, Vector3) - LocalPlayer::Entity()->lastSentTick()->position(); //internal Vector3 position;
		float num3 = Mathf::Abs(vector4.y);
		float num4 = reinterpret_cast<float(*)(Vector3)>(vars::stor::gBase + CO::Magnitude2D)(vector4);//Magnitude2D
		if (vector4.y >= 0.f) {
			vars::stuff::flyhackDistanceVertical += vector4.y;
			flag = true;
		}
		if (num3 < num4) {
			vars::stuff::flyhackDistanceHorizontal += num4;
			flag = true;
		}
		if (flag) {
			float num5 = Mathf::Max((vars::stuff::flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
			float num6 = LocalPlayer::Entity()->GetJumpHeight() + num5;
			if (vars::stuff::flyhackDistanceVertical > num6) {
				//return true;
			}
			float num7 = Mathf::Max((vars::stuff::flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
			float num8 = 5.f + num7;
			if (vars::stuff::flyhackDistanceHorizontal > num8) {
				//return true;
			}
		}
	}
	else {
		vars::stuff::flyhackDistanceHorizontal = 0.f;
		vars::stuff::flyhackDistanceVertical = 0.f;
	}
}
void CheckFlyhack() {
	TestFlying();
	float num5 = Mathf::Max((vars::stuff::flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
	float num6 = LocalPlayer::Entity()->GetJumpHeight() + num5;
	vars::stuff::max_flyhack = num6;
	if (vars::stuff::flyhackDistanceVertical <= num6) {
		vars::stuff::flyhack = vars::stuff::flyhackDistanceVertical;
	}

	float num7 = Mathf::Max((vars::stuff::flyhackPauseTime > 0.f) ? 10 : 1.5, 0.f);
	float num8 = 5.f + num7;
	vars::stuff::max_hor_flyhack = num8;
	if (vars::stuff::flyhackDistanceHorizontal <= num8) {
		vars::stuff::hor_flyhack = vars::stuff::flyhackDistanceHorizontal;
	}
}

namespace other {
	Vector3 m_manipulate = Vector3::Zero();
	void find_manipulate_angle() {
		Vector3 re_p = LocalPlayer::Entity()->transform()->position() + LocalPlayer::Entity()->transform()->up() * (PlayerEyes::EyeOffset().y + LocalPlayer::Entity()->eyes()->viewOffset().y);

		Vector3 choice = Vector3::Zero();

		if (utils::LineOfSight(re_p, reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->get_bone_pos(head))) {
			m_manipulate = Vector3::Zero();
			return;
		}


		auto right = LocalPlayer::Entity()->eyes()->MovementRight();
		auto forward = LocalPlayer::Entity()->eyes()->MovementForward();
		auto _forward = LocalPlayer::Entity()->eyes()->HeadForward();

		float desyncTime = (Time::realtimeSinceStartup() - LocalPlayer::Entity()->lastSentTickTime()) - 0.03125 * 3;
		float mm_max_eye = (0.1f + ((desyncTime + 2.f / 60.f + 0.125f) * 1.5f) * LocalPlayer::Entity()->MaxVelocity()) - 0.05f;


		std::array<Vector3, 56> arr = {
			Vector3(right.x * (mm_max_eye / 2), 0.f, right.z * (mm_max_eye / 2)), // small right
			Vector3(right.x * mm_max_eye, 0.f, right.z * mm_max_eye), // big right

			Vector3(right.x * (mm_max_eye / 2), (1.4f / 2), right.z * (mm_max_eye / 2)), // small right up
			Vector3(right.x * mm_max_eye, 1.4f, right.z * mm_max_eye), // big right up

			Vector3(right.x * (mm_max_eye / 2), -(1.4f / 2), right.z * (4.f / 2)), // small right down
			Vector3(right.x * mm_max_eye, -1.4f, right.z * mm_max_eye), // big right down

			Vector3(-(right.x * (mm_max_eye / 2)), 0.f, -(right.z * (mm_max_eye / 2))), // small left
			Vector3(-(right.x * mm_max_eye), 0.f, -(right.z * mm_max_eye)), // big left

			Vector3(-(right.x * (mm_max_eye / 2)), (1.4f / 2), -(right.z * (mm_max_eye / 2))), // small left up
			Vector3(-(right.x * mm_max_eye), 1.4f, -(right.z * mm_max_eye)), // big left up

			Vector3(-(right.x * (mm_max_eye / 2)), -(1.4f / 2), -(right.z * (mm_max_eye / 2))), // small left down
			Vector3(-(right.x * mm_max_eye), -1.4f, -(right.z * mm_max_eye)), // big left down 

			Vector3(0.f, (1.4f / 2), 0.f), // small up
			Vector3(0.f, 1.4f, 0.f), // big up

			Vector3(0.f, -(1.4f / 2), 0.f), // small down
			Vector3(0.f, -1.4f, 0.f), // big down

			Vector3(forward.x * (mm_max_eye / 2), 0.f, forward.z * (mm_max_eye / 2)),// small forward
			Vector3(forward.x * mm_max_eye, 0.f, forward.z * mm_max_eye), // big forward

			Vector3(forward.x * (mm_max_eye / 2), (1.4f / 2), forward.z * (mm_max_eye / 2)),// small forward up
			Vector3(forward.x * mm_max_eye, 1.4f, forward.z * mm_max_eye), // big forward up

			Vector3(forward.x * (mm_max_eye / 2), -(1.4f / 2), forward.z * (mm_max_eye / 2)),// small forward down
			Vector3(forward.x * mm_max_eye, -1.4f, forward.z * mm_max_eye), // big forward down

			Vector3(-(forward.x * (mm_max_eye / 2)), 0.f, -(forward.z * (mm_max_eye / 2))),// small reverse
			Vector3(-(forward.x * mm_max_eye), 0.f, -(forward.z * mm_max_eye)), // big reverse 

			Vector3(-(forward.x * (mm_max_eye / 2)), (1.4f / 2), -(forward.z * (mm_max_eye / 2))),// small reverse up
			Vector3(-(forward.x * 4.f), 1.4f, -(forward.z * 4.f)), // big reverse up

			Vector3(-(forward.x * (mm_max_eye / 2)), -(1.4f / 2), -(forward.z * (mm_max_eye / 2))),// small reverse down
			Vector3(-(forward.x * mm_max_eye), -1.4f, -(forward.z * mm_max_eye)), // big reverse down
		}; // restoring procedure: *= 1.428571428571429 for 0.7f

		for (auto s : arr) {
			Vector3 point = re_p + s;

			if (!utils::LineOfSight(point, re_p))
				continue;

			if (!utils::LineOfSight(reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer)->get_bone_pos(head), point))
				continue;

			choice = s;
			break;
		}
		if (choice.empty()) {
			m_manipulate = Vector3::Zero();
			return;
		}
		
		m_manipulate = choice;
	}
}

