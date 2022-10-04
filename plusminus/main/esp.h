namespace radar {
	//float range = vars::visuals::radar::range/*161.1f*/;
	//float size = vars::visuals::radar::size/*121.5f*/;

	void do_dot(DWORD64 ObjectClass, DWORD64 Object, char* buff, char* target, D2D1::ColorF clr) {
		Vector3 local = LocalPlayer::Entity( )->get_bone_pos(head);
		if (strstr(buff, target)) {
			uintptr_t BaseObject = read(ObjectClass + 0x30, uintptr_t);
			uintptr_t Transform = read(BaseObject + 0x8, uintptr_t);
			uintptr_t VisualState = read(Transform + 0x38, uintptr_t);
			Vector3 pos = read(VisualState + 0x90, Vector3);
			float y = local.x - pos.x;
			float x = local.z - pos.z;

			float dist = Math::Distance_3D(local, pos);
			Vector3 eulerAngles = Math::EulerAngles(LocalPlayer::Entity( )->eyes( )->get_rotation( ));
			float num = atan2(y, x) * 57.29578f - 270.f - eulerAngles.y;
			float PointPos_X = dist * cos(num * 0.0174532924f);
			float PointPos_Y = dist * sin(num * 0.0174532924f);
			PointPos_X = PointPos_X * (vars::visuals::radar::size / vars::visuals::radar::range) / 2.f;
			PointPos_Y = PointPos_Y * (vars::visuals::radar::size / vars::visuals::radar::range) / 2.f;

			float mid_x = vars::visuals::radar::x + vars::visuals::radar::size / 2;
			float mid_y = vars::visuals::radar::y + vars::visuals::radar::size / 2;

			Vector2 point = Vector2(vars::visuals::radar::x + vars::visuals::radar::size / 2.f + PointPos_X, vars::visuals::radar::y + vars::visuals::radar::size / 2.f + PointPos_Y);
			if (Math::Distance_2D(point, Vector2(mid_x, mid_y)) < vars::visuals::radar::size) {
				Renderer::FillCircle(point, clr, 2.5f);
			}
		}
	}
	void radar_bg( ) {
		float mid_x = vars::visuals::radar::x + vars::visuals::radar::size / 2;
		float mid_y = vars::visuals::radar::y + vars::visuals::radar::size / 2;
		POINT p;
		if (GetCursorPos(&p)) {
			if (p.x >= mid_x - vars::visuals::radar::size && p.x <= mid_x + vars::visuals::radar::size) {
				if (p.y >= mid_y - vars::visuals::radar::size && p.y <= mid_y + vars::visuals::radar::size) {
					if (GetAsyncKeyState(VK_LBUTTON) && show) {
						vars::visuals::radar::x = p.x - (vars::visuals::radar::size / 2);
						vars::visuals::radar::y = p.y - (vars::visuals::radar::size / 2);
					}
				}
			}
		}
		Renderer::FillCircle(Vector2(mid_x, mid_y), D2D1::ColorF(0.06f, 0.06f, 0.06f, 0.94f), vars::visuals::radar::size);
		Renderer::Circle(Vector2(mid_x, mid_y), D2D1::ColorF(0.43f, 0.43f, 0.50f, 0.50f), vars::visuals::radar::size);

		//Renderer::Circle(Vector2(mid_x, mid_y), D2D1::ColorF::Red, 2.5f);
		Renderer::Triangle(Vector2(mid_x, mid_y), D2D1::ColorF::Red, 3.5f);
	}
	void radar_logic(DWORD64 ObjectClass, DWORD64 Object, char* buff) {
		float mid_x = vars::visuals::radar::x + vars::visuals::radar::size / 2;
		float mid_y = vars::visuals::radar::y + vars::visuals::radar::size / 2;
		if (LocalPlayer::Entity( )) {
			Vector3 local = LocalPlayer::Entity( )->get_bone_pos(head);
			if (strstr(buff, xorstr("player.prefab")) || strstr(buff, xorstr("scientist")) && !strstr(buff, xorstr("prop")) && !strstr(buff, xorstr("corpse"))) {
				BasePlayer* Player = (BasePlayer*)Object;
				if (!Player->isCached( )) return;

				Vector3 ply = cachedBones[ Player->userID( ) ]->head->position;
				float dist = Math::Distance_3D(local, ply);
				float y = local.x - ply.x;
				float x = local.z - ply.z;

				Vector3 eulerAngles = Math::EulerAngles(LocalPlayer::Entity( )->eyes( )->get_rotation( )/*pViewMatrix->GetRotation()*/);
				float num = atan2(y, x) * 57.29578f - 270.f - eulerAngles.y;
				float PointPos_X = dist * cos(num * 0.0174532924f);
				float PointPos_Y = dist * sin(num * 0.0174532924f);
				PointPos_X = PointPos_X * (vars::visuals::radar::size / vars::visuals::radar::range) / 2.f;
				PointPos_Y = PointPos_Y * (vars::visuals::radar::size / vars::visuals::radar::range) / 2.f;

				Vector2 point = Vector2(vars::visuals::radar::x + vars::visuals::radar::size / 2.f + PointPos_X, vars::visuals::radar::y + vars::visuals::radar::size / 2.f + PointPos_Y);

				if (Math::Distance_2D(point, Vector2(mid_x, mid_y)) < vars::visuals::radar::size) {
					auto var = 402402;
					if (var = 402402) {
						if (!Player->HasFlags(PlayerFlags::Sleeping)) {
							if (LocalPlayer::Entity( )->is_teammate(Player->userID( ))) {
								Renderer::FillCircle(point, D2D1::ColorF::Lime, 2.5f);
							}
							else {
								if (Player->health( ) <= 0) {
									Renderer::FillCircle(point, D2D1::ColorF::Red, 2.5f);
								}
								else {
									if (Player->is_visible( )) {
										Renderer::FillCircle(point, D2D1::ColorF::White, 2.5f);
									}
									else {
										Renderer::FillCircle(point, D2D1::ColorF::DarkGray, 2.5f);
									}
								}
							}
						}
						else if (Player->HasFlags(PlayerFlags::Sleeping) && !vars::players::sleeperignore) {
							Renderer::FillCircle(point, D2D1::ColorF::Orange, 2.5f);
						}
					}
					else if (Player->IsNpc( ) && (vars::npc::box || vars::npc::name || vars::npc::tracers || vars::npc::healthbar)) {
						Renderer::FillCircle(point, D2D1::ColorF::Yellow, 2.5f);
					}
				}
			}
			if (vars::visuals::patrol_heli) {
				do_dot(ObjectClass, Object, buff, xorstr("assets/prefabs/npc/patrol helicopter/patrolhelicopter.prefab"), D2D1::ColorF(0.5f, 0.54f, 1.f));
			}
		}
	}
}
namespace otherEsp {
	void miscvis(DWORD64 ObjectClass, char* buff, bool boolean, bool showDistance, float drawDistance, const char* substring, const wchar_t* targettext, D2D1::ColorF color) {
		if (boolean) {
			if (strstr(buff, substring)) {

				Vector2 screen_Pos;
				if (ObjectClass) {
					if (utils::w2s(reinterpret_cast<BaseEntity*>(ObjectClass)->transform( )->position( )/*utils::GetEntityPosition(gameObject)*/, screen_Pos)) {
						if ((int)Math::Distance_3D(LocalPlayer::Entity( )->get_bone_pos(head), reinterpret_cast<BaseEntity*>(ObjectClass)->transform( )->position( )) <= drawDistance) {
							Renderer::Text({screen_Pos.x, screen_Pos.y}, color, true, true, xorstr(L"%s"), targettext);
							//DDraw::Sphere({ screen_Pos.x, screen_Pos.y }, 0.2f, Color(1, 1, 1, 1), 0.00001f, true);
							//DDraw::Box(entity->transform()->position() + Vector3(0.f, 0.f, 0.f), 0.2f, Color(RGB_RAINBOW.r, RGB_RAINBOW.g, RGB_RAINBOW.b, 255.f), 0.00001f, true);
							if (showDistance) {
								Renderer::Text(screen_Pos + Vector2(0, 15), color, true, true, xorstr(L"[%.2f m]"), Math::Distance_3D(LocalPlayer::Entity( )->get_bone_pos(head), reinterpret_cast<BaseEntity*>(ObjectClass)->transform( )->position( )));
							}
						}
					}
				}
			}
		}
	}
	void bradley(DWORD64 ObjectClass, DWORD64 Object, char* buff) {
		if (vars::visuals::bradley_apc) {
			if (strstr(buff, xorstr("bradleyapc.prefab"))) {

				BaseCombatEntity* bradley = (BaseCombatEntity*)Object;
				if (bradley) {
					Vector3 pos = bradley->transform( )->position( );/*utils::GetEntityPosition(object);*/
					int distance = Math::Distance_3D(LocalPlayer::Entity( )->get_bone_pos(head), pos);
					float health = bradley->health( );
					Vector2 screen;
					if (utils::w2s(pos, screen)) {
						if (health > 0) {
							Renderer::Text(screen, D2D1::ColorF::Red, true, true, xorstr(L"Bradley APC [%.2fm]"), Math::Distance_3D(LocalPlayer::Entity( )->get_bone_pos(head), pos));

							Renderer::FillRectangle(Vector2{screen - Vector2(30, 0) + Vector2(0, 15)}, Vector2{60 * (health / 1000.f), 6}, D2D1::ColorF(0.f, 255.f, 0.f, 0.8f));
							Renderer::Rectangle(Vector2{screen - Vector2(30, 0) + Vector2(0, 15)}, Vector2{60, 6}, D2D1::ColorF::Black, 0.5f);
						}
					}
				}
			}
		}
	}
	void corpse(DWORD64 ObjectClass, DWORD64 Object, char* buff) {
		if (vars::visuals::other::corpse) {
			if (strstr(buff, xorstr("player_corpse.prefab"))) {

				BaseEntity* corpse = (BaseEntity*)Object;
				if (corpse) {
					Vector3 pos = corpse->transform( )->position( );
					float distance = Math::Distance_3D(LocalPlayer::Entity( )->get_bone_pos(head), pos);
					Vector2 screen;
					if (utils::w2s(pos, screen) && distance <= vars::visuals::other::draw_distance) {
						auto* corpsename = reinterpret_cast<pUncStr>(read(corpse + 0x2B0, DWORD64));
						Renderer::Text({screen.x, screen.y}, D2D1::ColorF::Firebrick, true, true, xorstr(L"Corpse | %s"), corpsename->str);
						if (vars::visuals::other::show_distance) {
							Renderer::Text(screen + Vector2(0, 15), D2D1::ColorF::Firebrick, true, true, xorstr(L"[%.2f m]"), distance);
						}
					}
				}
			}
		}
	}
	void tc(DWORD64 ObjectClass, DWORD64 Object, char* buff) {
		if (vars::visuals::base::tc) {
			if (strstr(buff, xorstr("cupboard.tool.deployed.prefab"))) {

				BaseEntity* cupboard = (BaseEntity*)Object;
				if (cupboard) {
					Vector3 pos = cupboard->transform( )->position( );
					float distance = Math::Distance_3D(LocalPlayer::Entity( )->get_bone_pos(head), pos);
					Vector2 screen;
					if (utils::w2s(pos, screen) && distance <= vars::visuals::base::draw_distance) {
						int pos = 15;
						int upkeep = read(cupboard + 0x564, float);
						Renderer::Text(screen, D2D1::ColorF::YellowGreen, true, true, xorstr(L"Tool Cupboard | %d hours"), upkeep / 60);
						if (vars::visuals::base::show_distance) {
							Renderer::Text(screen + Vector2(0, 15), D2D1::ColorF::YellowGreen, true, true, xorstr(L"[%.2f m]"), distance);
							pos += 15;
						}
						uintptr_t authedPly = read(cupboard + 0x570, uintptr_t);
						List<PlayerNameID*>* authedPly_list = read(authedPly + 0x10, List<PlayerNameID*>*);
						authedPly_list->for_each([ & ](PlayerNameID* authorizedPlayer, int32_t idx) {
							if (authorizedPlayer) {
								auto user = authorizedPlayer->username( );
								Renderer::Text(screen + Vector2(0, pos), D2D1::ColorF::YellowGreen, true, true, user);
								pos += 15;
							}
							});
					}
				}
			}
		}
	}
	void sleepingbag(DWORD64 ObjectClass, DWORD64 Object, char* buff) {
		if (vars::visuals::base::sleeping_bag) {
			if (strstr(buff, xorstr("sleepingbag_leather_deployed.prefab"))) {

				BaseEntity* bag = (BaseEntity*)Object;
				if (bag) {
					Vector3 pos = bag->transform( )->position( );
					float distance = Math::Distance_3D(LocalPlayer::Entity( )->get_bone_pos(head), pos);
					Vector2 screen;
					if (utils::w2s(pos, screen) && distance <= vars::visuals::base::draw_distance) {
						auto* bagname = reinterpret_cast<pUncStr>(read(bag + 0x418, DWORD64));
						Renderer::Text({screen.x, screen.y}, D2D1::ColorF::Olive, true, true, xorstr(L"Sleeping Bag | %s"), bagname->str);
						if (vars::visuals::base::show_distance) {
							Renderer::Text(screen + Vector2(0, 15), D2D1::ColorF::Olive, true, true, xorstr(L"[%.2f m]"), distance);
						}
					}
				}
			}
		}
	}
	void bed(DWORD64 ObjectClass, DWORD64 Object, char* buff) {
		if (vars::visuals::base::bed) {
			if (strstr(buff, xorstr("bed_deployed.prefab"))) {

				BaseEntity* bag = (BaseEntity*)Object;
				if (bag) {
					Vector3 pos = bag->transform( )->position( );
					float distance = Math::Distance_3D(LocalPlayer::Entity( )->get_bone_pos(head), pos);
					Vector2 screen;
					if (utils::w2s(pos, screen) && distance <= vars::visuals::base::draw_distance) {
						auto* bagname = reinterpret_cast<pUncStr>(read(bag + 0x418, DWORD64));
						Renderer::Text({screen.x, screen.y}, D2D1::ColorF::OliveDrab, true, true, xorstr(L"Bed | %s"), bagname->str);
						if (vars::visuals::base::show_distance) {
							Renderer::Text({screen.x, screen.y}, D2D1::ColorF::OliveDrab, true, true, xorstr(L"[%.2f m]"), distance);
						}
					}
				}
			}
		}
	}
	void stash(DWORD64 ObjectClass, DWORD64 Object, char* buff) {
		typedef bool(__stdcall* IsHidden)(BaseEntity*);
		if (vars::visuals::other::stash) {
			if (strstr(buff, xorstr("small_stash_deployed.prefab"))) {

				BaseEntity* stash = (BaseEntity*)Object;
				if (stash) {
					Vector3 pos = stash->transform( )->position( );
					float distance = Math::Distance_3D(LocalPlayer::Entity( )->get_bone_pos(head), pos);
					Vector2 screen;
					if (utils::w2s(pos, screen) && distance <= vars::visuals::other::draw_distance) {
						if (((IsHidden)(vars::stor::gBase + CO::IsHidden))(stash)) {
							Renderer::Text({screen.x, screen.y}, D2D1::ColorF::Yellow, true, true, xorstr(L"Stash [Hidden]"));

						}
						else {
							Renderer::Text({screen.x, screen.y}, D2D1::ColorF::Yellow, true, true, xorstr(L"Stash [Open]"));
						}
						if (vars::visuals::other::show_distance) {
							Renderer::Text(screen + Vector2(0, 15), D2D1::ColorF::Yellow, true, true, xorstr(L"[%.2f m]"), distance);
						}
					}
				}
			}
		}
	}
	void hackablecrate(DWORD64 ObjectClass, DWORD64 Object, char* buff) {
		typedef bool(__stdcall* IsBeingHacked)(BaseEntity*);
		typedef bool(__stdcall* IsFullyHacked)(BaseEntity*);
		if (vars::visuals::crates::chinook) {
			if (strstr(buff, xorstr("codelockedhackablecrate.prefab"))) {

				BaseEntity* crate = (BaseEntity*)Object;
				if (crate) {
					Vector3 pos = crate->transform( )->position( );
					float distance = Math::Distance_3D(LocalPlayer::Entity( )->get_bone_pos(head), pos);
					Vector2 screen;
					if (utils::w2s(pos, screen)) {
						uintptr_t timerText = read(crate + 0x448, uintptr_t);
						auto* m_Text = reinterpret_cast<pUncStr>(read(timerText + 0xD0, DWORD64));
						D2D1::ColorF color = D2D1::ColorF::OrangeRed;
						if (!((IsFullyHacked)(vars::stor::gBase + CO::IsFullyHacked))(crate)) {
							if (((IsBeingHacked)(vars::stor::gBase + CO::IsBeingHacked))(crate)) {
								color = D2D1::ColorF::LightGoldenrodYellow;
								Renderer::Text({screen.x, screen.y}, D2D1::ColorF::LightGoldenrodYellow, true, true, xorstr(L"Chinook Crate | %s"), m_Text->str);
							}
							else {
								color = D2D1::ColorF::OrangeRed;
								Renderer::Text({screen.x, screen.y}, D2D1::ColorF::OrangeRed, true, true, xorstr(L"Chinook Crate"));
							}
						}
						else {
							color = D2D1::ColorF::LightSeaGreen;
							Renderer::Text({screen.x, screen.y}, D2D1::ColorF::LightSeaGreen, true, true, xorstr(L"Chinook Crate [Open]"));
						}
						Renderer::Text(screen + Vector2(0, 15), color, true, true, xorstr(L"[%.2f m]"), distance);
					}
				}
			}
		}
	}
	void world(DWORD64 ObjectClass, DWORD64 Object, char* buff) {
		typedef uintptr_t(__stdcall* GetItem)(uintptr_t);
		
	}
}
void Skeleton(BasePlayer* player, D2D1::ColorF color) {
	auto head_pos = cachedBones[ player->userID( ) ]->head->position;
	auto spine4_pos = cachedBones[ player->userID( ) ]->spine4->position;
	auto l_clavicle_pos = cachedBones[ player->userID( ) ]->l_clavicle->position;
	auto l_upperarm_pos = cachedBones[ player->userID( ) ]->l_upperarm->position;
	auto l_forearm_pos = cachedBones[ player->userID( ) ]->l_forearm->position;
	auto l_hand_pos = cachedBones[ player->userID( ) ]->l_hand->position;
	auto r_clavicle_pos = cachedBones[ player->userID( ) ]->r_clavicle->position;
	auto r_upperarm_pos = cachedBones[ player->userID( ) ]->r_upperarm->position;
	auto r_forearm_pos = cachedBones[ player->userID( ) ]->r_forearm->position;
	auto r_hand_pos = cachedBones[ player->userID( ) ]->r_hand->position;
	auto pelvis_pos = cachedBones[ player->userID( ) ]->pelvis->position;
	auto l_hip_pos = cachedBones[ player->userID( ) ]->l_hip->position;
	auto l_knee_pos = cachedBones[ player->userID( ) ]->l_knee->position;
	auto l_ankle_scale_pos = cachedBones[ player->userID( ) ]->l_ankle_scale->position;
	auto l_foot_pos = cachedBones[ player->userID( ) ]->l_foot->position;
	auto r_hip_pos = cachedBones[ player->userID( ) ]->r_hip->position;
	auto r_knee_pos = cachedBones[ player->userID( ) ]->r_knee->position;
	auto r_ankle_scale_pos = cachedBones[ player->userID( ) ]->r_ankle_scale->position;
	auto r_foot_pos = cachedBones[ player->userID( ) ]->r_foot->position;

	Vector2 head, spine, l_clavicle, l_upperarm, l_forearm, l_hand, r_clavicle, r_upperarm, r_forearm, r_hand, pelvis, l_hip, l_knee, l_ankle_scale, l_foot, r_hip, r_knee, r_ankle_scale, r_foot;
	if (utils::w2s(head_pos, head) &&
		utils::w2s(spine4_pos, spine) &&
		utils::w2s(l_clavicle_pos, l_clavicle) &&
		utils::w2s(l_upperarm_pos, l_upperarm) &&
		utils::w2s(l_forearm_pos, l_forearm) &&
		utils::w2s(l_hand_pos, l_hand) &&
		utils::w2s(r_clavicle_pos, r_clavicle) &&
		utils::w2s(r_upperarm_pos, r_upperarm) &&
		utils::w2s(r_forearm_pos, r_forearm) &&
		utils::w2s(r_hand_pos, r_hand) &&
		utils::w2s(pelvis_pos, pelvis) &&
		utils::w2s(l_hip_pos, l_hip) &&
		utils::w2s(l_knee_pos, l_knee) &&
		utils::w2s(l_ankle_scale_pos, l_ankle_scale) &&
		utils::w2s(l_foot_pos, l_foot) &&
		utils::w2s(r_hip_pos, r_hip) &&
		utils::w2s(r_knee_pos, r_knee) &&
		utils::w2s(r_ankle_scale_pos, r_ankle_scale) &&
		utils::w2s(r_foot_pos, r_foot)) {

		Renderer::Line(head, spine, color, 1.5f, true);
		Renderer::Line(spine, l_upperarm, color, 1.5f, true);
		Renderer::Line(l_upperarm, l_forearm, color, 1.5f, true);
		Renderer::Line(l_forearm, l_hand, color, 1.5f, true);
		Renderer::Line(spine, r_upperarm, color, 1.5f, true);
		Renderer::Line(r_upperarm, r_forearm, color, 1.5f, true);
		Renderer::Line(r_forearm, r_hand, color, 1.5f, true);
		Renderer::Line(spine, pelvis, color, 1.5f, true);
		Renderer::Line(pelvis, l_hip, color, 1.5f, true);
		Renderer::Line(l_hip, l_knee, color, 1.5f, true);
		Renderer::Line(l_knee, l_foot, color, 1.5f, true);
		Renderer::Line(pelvis, r_hip, color, 1.5f, true);
		Renderer::Line(r_hip, r_knee, color, 1.5f, true);
		Renderer::Line(r_knee, r_foot, color, 1.5f, true);
	}
}
void CornerBox(float Entity_x, float Entity_y, float Entity_w, float Entity_h, D2D1::ColorF color) {
	Renderer::Line({Entity_x, Entity_y}, {Entity_x + Entity_w / 3.5f, Entity_y}, D2D1::ColorF::Black, 3.f);
	Renderer::Line({Entity_x, Entity_y}, {Entity_x + Entity_w / 3.5f, Entity_y}, color);
	Renderer::Line({Entity_x, Entity_y}, {Entity_x,Entity_y + Entity_h / 3.5f}, D2D1::ColorF::Black, 3.f);
	Renderer::Line({Entity_x, Entity_y}, {Entity_x,Entity_y + Entity_h / 3.5f}, color);

	Renderer::Line({Entity_x + Entity_w, Entity_y}, {(Entity_x + Entity_w) - Entity_w / 3.5f, Entity_y}, D2D1::ColorF::Black, 3.f);
	Renderer::Line({Entity_x + Entity_w, Entity_y}, {(Entity_x + Entity_w) - Entity_w / 3.5f, Entity_y}, color);
	Renderer::Line({Entity_x + Entity_w, Entity_y}, {Entity_x + Entity_w,Entity_y + Entity_h / 3.5f}, D2D1::ColorF::Black, 3.f);
	Renderer::Line({Entity_x + Entity_w, Entity_y}, {Entity_x + Entity_w,Entity_y + Entity_h / 3.5f}, color);

	Renderer::Line({Entity_x + Entity_w, Entity_y + Entity_h}, {(Entity_x + Entity_w) - Entity_w / 3.5f, Entity_y + Entity_h}, D2D1::ColorF::Black, 3.f);
	Renderer::Line({Entity_x + Entity_w, Entity_y + Entity_h}, {(Entity_x + Entity_w) - Entity_w / 3.5f, Entity_y + Entity_h}, color);
	Renderer::Line({Entity_x + Entity_w, Entity_y + Entity_h}, {Entity_x + Entity_w,(Entity_y + Entity_h) - Entity_h / 3.5f}, D2D1::ColorF::Black, 3.f);
	Renderer::Line({Entity_x + Entity_w, Entity_y + Entity_h}, {Entity_x + Entity_w,(Entity_y + Entity_h) - Entity_h / 3.5f}, color);

	Renderer::Line({Entity_x, Entity_y + Entity_h}, {Entity_x + Entity_w / 3.5f, Entity_y + Entity_h}, D2D1::ColorF::Black, 3.f);
	Renderer::Line({Entity_x, Entity_y + Entity_h}, {Entity_x + Entity_w / 3.5f, Entity_y + Entity_h}, color);
	Renderer::Line({Entity_x, Entity_y + Entity_h}, {Entity_x,(Entity_y + Entity_h) - Entity_h / 3.5f}, D2D1::ColorF::Black, 3.f);
	Renderer::Line({Entity_x, Entity_y + Entity_h}, {Entity_x,(Entity_y + Entity_h) - Entity_h / 3.5f}, color);
}
void OOF(BasePlayer* ply, ImColor color) {
	if (vars::players::sleeperignore && ply->HasFlags(PlayerFlags::Sleeping)) return;
	//if (!vars::npc::oof_arrows && ply->IsNpc( )) return;
	if (!ply) return;
	if (!LocalPlayer::Entity( )->isCached( )) return;

	if (vars::players::oof_arrows) {
		if (utils::OOF(ply)) {
			Vector3 local = cachedBones[ LocalPlayer::Entity( )->userID( ) ]->head->position;
			float y = local.x - cachedBones[ ply->userID( ) ]->head->position.x;
			float x = local.z - cachedBones[ ply->userID( ) ]->head->position.z;
			Vector3 eulerAngles = Math::EulerAngles(LocalPlayer::Entity( )->eyes( )->get_rotation( ));
			float num = atan2(y, x) * 57.29578f - 180.f - eulerAngles.y;
			Vector2 point = Renderer::CosTanSinLineH(num, 5.f, screen_center.x, screen_center.y, 200.f);
			Vector2 tp0 = Renderer::CosTanSinLineH(num, 5.f, vars::stuff::ScreenWidth / 2, vars::stuff::ScreenHeight / 2, 150.f);
			Vector2 tp1 = Renderer::CosTanSinLineH(num + 2.f, 5.f, vars::stuff::ScreenWidth / 2, vars::stuff::ScreenHeight / 2, 140.f);
			Vector2 tp2 = Renderer::CosTanSinLineH(num - 2.f, 5.f, vars::stuff::ScreenWidth / 2, vars::stuff::ScreenHeight / 2, 140.f);

			/*Renderer::RectangleFillPoint(point, 9.f, 9.f, D2D1::ColorF(0.06f, 0.06f, 0.06f, 0.94f));
			Renderer::RectanglePoint(point, 9.f, 9.f, color);*/
			ImGui::GetBackgroundDrawList()->AddTriangleFilled({ tp0.x,tp0.y }, { tp1.x,tp1.y }, { tp2.x,tp2.y }, color);
		}
		
	}
}
typedef bool(__stdcall* IsDucked)(BasePlayer*);
void Box3D(BasePlayer* player, D2D1::ColorF color) {
	CBounds bounds = CBounds( );

	IsDucked ducked = (IsDucked)(vars::stor::gBase + CO::IsDucked);
	if (ducked(player)) {
		bounds.center = cachedBones[ player->userID( ) ]->l_foot->position.midPoint(cachedBones[ player->userID( ) ]->r_foot->position) + Vector3(0.0f, 0.55f, 0.0f);
		bounds.extents = Vector3(0.4f, 0.65f, 0.4f);
	}
	else {
		if (player->HasFlags(PlayerFlags::Wounded) || player->HasFlags(PlayerFlags::Sleeping)) {
			bounds.center = cachedBones[ player->userID( ) ]->pelvis->position;
			bounds.extents = Vector3(0.9f, 0.2f, 0.4f);
		}
		else {
			bounds.center = cachedBones[ player->userID( ) ]->l_foot->position.midPoint(cachedBones[ player->userID( ) ]->r_foot->position) + Vector3(0.0f, 0.85f, 0.0f);
			bounds.extents = Vector3(0.4f, 0.9f, 0.4f);
		}
	}

	float y = Math::EulerAngles(player->eyes( )->get_rotation( )).y;
	Vector3 center = bounds.center;
	Vector3 extents = bounds.extents;
	Vector3 frontTopLeft = Math::RotatePoint(center, Vector3(center.x - extents.x, center.y + extents.y, center.z - extents.z), y);
	Vector3 frontTopRight = Math::RotatePoint(center, Vector3(center.x + extents.x, center.y + extents.y, center.z - extents.z), y);
	Vector3 frontBottomLeft = Math::RotatePoint(center, Vector3(center.x - extents.x, center.y - extents.y, center.z - extents.z), y);
	Vector3 frontBottomRight = Math::RotatePoint(center, Vector3(center.x + extents.x, center.y - extents.y, center.z - extents.z), y);
	Vector3 backTopLeft = Math::RotatePoint(center, Vector3(center.x - extents.x, center.y + extents.y, center.z + extents.z), y);
	Vector3 backTopRight = Math::RotatePoint(center, Vector3(center.x + extents.x, center.y + extents.y, center.z + extents.z), y);
	Vector3 backBottomLeft = Math::RotatePoint(center, Vector3(center.x - extents.x, center.y - extents.y, center.z + extents.z), y);
	Vector3 backBottomRight = Math::RotatePoint(center, Vector3(center.x + extents.x, center.y - extents.y, center.z + extents.z), y);

	Vector2 frontTopLeft_2d, frontTopRight_2d, frontBottomLeft_2d, frontBottomRight_2d, backTopLeft_2d, backTopRight_2d, backBottomLeft_2d, backBottomRight_2d;
	if (utils::w2s(frontTopLeft, frontTopLeft_2d) &&
		utils::w2s(frontTopRight, frontTopRight_2d) &&
		utils::w2s(frontBottomLeft, frontBottomLeft_2d) &&
		utils::w2s(frontBottomRight, frontBottomRight_2d) &&
		utils::w2s(backTopLeft, backTopLeft_2d) &&
		utils::w2s(backTopRight, backTopRight_2d) &&
		utils::w2s(backBottomLeft, backBottomLeft_2d) &&
		utils::w2s(backBottomRight, backBottomRight_2d)) {

		Renderer::Line(frontTopLeft_2d, frontTopRight_2d, color, 1.5f, true);
		Renderer::Line(frontTopRight_2d, frontBottomRight_2d, color, 1.5f, true);
		Renderer::Line(frontBottomRight_2d, frontBottomLeft_2d, color, 1.5f, true);
		Renderer::Line(frontBottomLeft_2d, frontTopLeft_2d, color, 1.5f, true);
		Renderer::Line(backTopLeft_2d, backTopRight_2d, color, 1.5f, true);
		Renderer::Line(backTopRight_2d, backBottomRight_2d, color, 1.5f, true);
		Renderer::Line(backBottomRight_2d, backBottomLeft_2d, color, 1.5f, true);
		Renderer::Line(backBottomLeft_2d, backTopLeft_2d, color, 1.5f, true);
		Renderer::Line(frontTopLeft_2d, backTopLeft_2d, color, 1.5f, true);
		Renderer::Line(frontTopRight_2d, backTopRight_2d, color, 1.5f, true);
		Renderer::Line(frontBottomRight_2d, backBottomRight_2d, color, 1.5f, true);
		Renderer::Line(frontBottomLeft_2d, backBottomLeft_2d, color, 1.5f, true);
	}
}
void ESP(BasePlayer* BP, const D2D1::ColorF color) {
	if (vars::players::sleeperignore && BP->HasFlags(PlayerFlags::Sleeping)) return;
	if (!BP) return;
	Vector2 tempFeetR, tempFeetL;
	if (utils::w2s(cachedBones[ BP->userID( ) ]->r_foot->position, tempFeetR) && utils::w2s(cachedBones[ BP->userID( ) ]->l_foot->position, tempFeetL)) {
		if (tempFeetR.x == 0 && tempFeetR.y == 0) return;
		Vector2 tempHead;
		if (utils::w2s(cachedBones[ BP->userID( ) ]->head->position + Vector3(0, 0.2f, 0), tempHead)) {
			Vector2 tempFeet = (tempFeetR + tempFeetL) / 2.f;
			float Entity_h = tempHead.y - tempFeet.y;
			float w = Entity_h / 4;
			float Entity_x = tempFeet.x - w;
			float Entity_y = tempFeet.y;
			float Entity_w = Entity_h / 2;
			Vector3 middlePointWorld = cachedBones[ BP->userID( ) ]->l_foot->position.midPoint(cachedBones[ BP->userID( ) ]->r_foot->position);
			int CurPos = 0;
			int CurPos2 = 0;
			Vector2 middlePointPlayerTop;
			Vector2 middlePointPlayerFeet;
			if (utils::w2s(middlePointWorld + Vector3(0, 2, 0), middlePointPlayerTop) && utils::w2s(middlePointWorld, middlePointPlayerFeet)) {

				if (vars::players::fillbox) {
					if ((int)BP->health( ) > 0) {
						Renderer::FillRectangle(Vector2{Entity_x, Entity_y}, Vector2{Entity_w, Entity_h}, D2D1::ColorF(0.f, 0.f, 0.f, 0.4f));
					}
				}
				static float r = 1.00f, g = 0.00f, b = 1.00f;
				static int cases = 0;
				switch (cases)
				{
				case 0: { r -= 0.005f; if (r <= 0) cases += 1; break; }
				case 1: { g += 0.005f; b -= 0.005f; if (g >= 1) cases += 1; break; }
				case 2: { r += 0.005f; if (r >= 1) cases += 1; break; }
				case 3: { b += 0.005f; g -= 0.005f; if (b >= 1) cases = 0; break; }
				default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
				}
				if (vars::misc::instakillindicator) {
					if (GetAsyncKeyState(vars::keys::instakill)) {
						auto local = LocalPlayer::Entity();
						float desyncTime = (Time::realtimeSinceStartup() - local->lastSentTickTime());
						Renderer::Circle(Vector2{ middlePointPlayerTop.x, middlePointPlayerTop.y - 10.f }, D2D1::ColorF(r, g, b, 255.f), 7.f * (desyncTime), 1.f);
						
					}

				}
				if (vars::players::box) {
					if (vars::players::boxstyle == 0) {
						Renderer::Rectangle(Vector2{Entity_x, Entity_y}, Vector2{Entity_w, Entity_h}, D2D1::ColorF::Black, 3.f);
						Renderer::Rectangle(Vector2{Entity_x, Entity_y}, Vector2{Entity_w, Entity_h}, color);
					}
					if (vars::players::boxstyle == 1) {
						CornerBox(Entity_x, Entity_y, Entity_w, Entity_h, color);
					}
					if (vars::players::boxstyle == 2) {
						Box3D(BP, color);
					}
				}
				if (vars::players::name) {
					Renderer::Text(Vector2{ middlePointPlayerTop.x, middlePointPlayerTop.y}, color, true, true, BP->_displayName( ));
					CurPos += 15;
				}
				if (vars::players::weapon) {
					if (BP->health( ) > 0) {
						Item* weapon = BP->GetActiveWeapon( );
						if (weapon) {
							Renderer::Text(Vector2{middlePointPlayerFeet.x, middlePointPlayerFeet.y + CurPos + 10.f}, color, true, true, xorstr(L"%s [x%d]"), weapon->get_name( ), weapon->count( ));
							CurPos += 15;
						}
						/*else {
							if (vars::stuff::testBool) {
								auto window = ImGui::GetCurrentWindow( );
								window->DrawList->AddImage((void*)logo, ImVec2(tempHead.x, tempHead.y), ImVec2(tempHead.x + 66, tempHead.y + 66));
							}
						}*/
					}
				}
				if (vars::players::healthdist) {
					Renderer::Text(Vector2{middlePointPlayerFeet.x, middlePointPlayerFeet.y + CurPos + 10.f}, color, true, true, xorstr(L"[%.2fM] [%dHP]"), Math::Distance_3D(LocalPlayer::Entity( )->get_bone_pos(head), BP->get_bone_pos(head)), (int)BP->health( ));
					CurPos += 15;
				}
				if (vars::players::healthbar) {
					int health = (int)BP->health( );
					float maxheal = 100.f;
					if (vars::players::healthbarstyle == 0) {
						if ((int)Math::Distance_3D(LocalPlayer::Entity( )->get_bone_pos(head), cachedBones[ BP->userID( ) ]->head->position) < 201) {
							Renderer::FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 2, Entity_h }, D2D1::ColorF::Black);
                            Renderer::FillRectangle(Vector2{Entity_x + Entity_w - 8.f, Entity_y}, Vector2{2, Entity_h * (health / maxheal)}, D2D1::ColorF(0.f, 255.f, 0.f, 0.8f));
							Renderer::Text(Vector2{ Entity_x + Entity_w - 8.f, (Entity_y) + (Entity_h * (health / maxheal))}, D2D1::ColorF::White, true, true, xorstr(L"%d"), (int)health);
							//Renderer::t(footPos + Vector2(60 * (health / maxheal), y_), Color3(255, 255, 255), 8.f, true, true, wxorstr_(L"%d"), (int)health);
						}
					}
					if (vars::players::healthbarstyle == 1) {
						if ((int)BP->health( ) <= 33) {
							Renderer::FillRectangle(Vector2{middlePointPlayerFeet.x - 30, middlePointPlayerFeet.y + CurPos + 5}, Vector2{60 * (health / maxheal), 6}, D2D1::ColorF(255.f, 0.f, 0.f, 0.8f));
						}
						if ((int)BP->health( ) >= 34 && (int)BP->health( ) <= 66) {
							Renderer::FillRectangle(Vector2{middlePointPlayerFeet.x - 30, middlePointPlayerFeet.y + CurPos + 5}, Vector2{60 * (health / maxheal), 6}, D2D1::ColorF(255.f, 202.f, 0.f, 0.8f));
						}
						if ((int)BP->health( ) >= 67) {
							Renderer::FillRectangle(Vector2{middlePointPlayerFeet.x - 30, middlePointPlayerFeet.y + CurPos + 5}, Vector2{60 * (health / maxheal), 6}, D2D1::ColorF(0.f, 255.f, 0.f, 0.8f));
						}
						Renderer::Rectangle(Vector2{middlePointPlayerFeet.x - 30, middlePointPlayerFeet.y + CurPos + 5}, Vector2{60, 6}, D2D1::ColorF::Black, 0.5f);
					}
				}
				if (vars::players::tracers && !BP->HasFlags(PlayerFlags::Sleeping)) {
					static float screenX = vars::stuff::ScreenWidth;
					static float screenY = vars::stuff::ScreenHeight;
					static Vector2 startPos;
					if (vars::players::tracers_pos == 0) {
						startPos = Vector2(screenX / 2.f, screenY - 200.f);
					}
					if (vars::players::tracers_pos == 1) {
						startPos = Vector2(screenX / 2, screenY / 2);
					}
					if ((int)BP->health( ) > 0) {
						Renderer::Line(startPos, tempHead, color, 0.5f);
					}
				}
			}
		}
	}
}
void NPCESP(BasePlayer* BP, D2D1::ColorF color) {
	Vector2 tempFeetR, tempFeetL;
	if (utils::w2s(BP->get_bone_pos(r_foot), tempFeetR) && utils::w2s(BP->get_bone_pos(l_foot), tempFeetL)) {
		if (tempFeetR.x == 0 && tempFeetR.y == 0) return;
		Vector2 tempHead;
		if (utils::w2s(BP->get_bone_pos(jaw) + Vector3(0.f, 0.16f, 0.f), tempHead)) {
			Vector2 tempFeet = (tempFeetR + tempFeetL) / 2.f;
			float Entity_h = tempHead.y - tempFeet.y;
			float w = Entity_h / 4;
			float Entity_x = tempFeet.x - w;
			float Entity_y = tempFeet.y;
			float Entity_w = Entity_h / 2;
			Vector3 middlePointWorld = BP->get_bone_pos(l_foot).midPoint(BP->get_bone_pos(r_foot));
			int CurPos = 0;
			int CurPos2 = 0;
			Vector2 middlePointPlayerTop;
			Vector2 middlePointPlayerFeet;
			if (utils::w2s(middlePointWorld + Vector3(0, 2, 0), middlePointPlayerTop) && utils::w2s(middlePointWorld, middlePointPlayerFeet)) {
				if (vars::npc::fillbox) {
					Renderer::FillRectangle(Vector2{Entity_x, Entity_y}, Vector2{Entity_w, Entity_h}, D2D1::ColorF(0.f, 0.f, 0.f, 0.4f));
				}
				if (vars::npc::box) {
					if (vars::npc::boxstyle == 0) {
						Renderer::Rectangle(Vector2{Entity_x, Entity_y}, Vector2{Entity_w, Entity_h}, D2D1::ColorF::Black, 3.f);
						Renderer::Rectangle(Vector2{Entity_x, Entity_y}, Vector2{Entity_w, Entity_h}, color);
					}
					if (vars::npc::boxstyle == 1) {
						CornerBox(Entity_x, Entity_y, Entity_w, Entity_h, color);
					}
				}
				if (vars::npc::name) {
					Renderer::Text(Vector2{middlePointPlayerFeet.x, middlePointPlayerFeet.y + 10.f}, color, true, true, xorstr(L"NPC"));
					CurPos2 += 15;
				}
				if (vars::npc::weapon) {
					const wchar_t* ActiveWeaponName;
					Item* ActWeapon = BP->GetActiveWeapon( );
					ActiveWeaponName = ActWeapon->get_name( );
					if (!ActWeapon) {
						ActiveWeaponName = xorstr(L"---");
					}
					else {
						ActiveWeaponName = ActWeapon->get_name( );
					}
					Renderer::Text(Vector2{middlePointPlayerFeet.x, middlePointPlayerFeet.y + CurPos2 + 10.f}, color, true, true, ActiveWeaponName);
					CurPos2 += 15;
				}
				if (vars::npc::healthdist) {
					Renderer::Text(Vector2{middlePointPlayerFeet.x, middlePointPlayerFeet.y + CurPos2 + 10.f}, color, true, true, xorstr(L"[%.2fM] [%dHP]"), Math::Distance_3D(LocalPlayer::Entity( )->get_bone_pos(head), BP->get_bone_pos(head)), (int)BP->health( ));
					CurPos2 += 15;
				}
				if (vars::npc::healthbar) {
					int health = (int)BP->health( );
					float maxheal = 150.f;
					if (vars::npc::healthbarstyle == 0) {
						if ((int)Math::Distance_3D(LocalPlayer::Entity( )->get_bone_pos(head), BP->get_bone_pos(head)) < 201) {
							if ((int)BP->health( ) <= 33) {
								Renderer::FillRectangle(Vector2{Entity_x + Entity_w - 8.f, Entity_y}, Vector2{5, Entity_h * (health / maxheal)}, D2D1::ColorF(255.f, 0.f, 0.f, 0.8f));
							}
							if ((int)BP->health( ) >= 34 && (int)BP->health( ) <= 66) {
								Renderer::FillRectangle(Vector2{Entity_x + Entity_w - 8.f, Entity_y}, Vector2{5, Entity_h * (health / maxheal)}, D2D1::ColorF(255.f, 202.f, 0.f, 0.8f));
							}
							if ((int)BP->health( ) >= 67) {
								Renderer::FillRectangle(Vector2{Entity_x + Entity_w - 8.f, Entity_y}, Vector2{5, Entity_h * (health / maxheal)}, D2D1::ColorF(0.f, 255.f, 0.f, 0.8f));
							}
							Renderer::Rectangle(Vector2{Entity_x + Entity_w - 8.f, Entity_y}, Vector2{5, Entity_h}, D2D1::ColorF::Black, 0.5f);
						}
					}
					if (vars::npc::healthbarstyle == 1) {
						if ((int)BP->health( ) <= 33) {
							Renderer::FillRectangle(Vector2{middlePointPlayerFeet.x - 30, middlePointPlayerFeet.y + CurPos}, Vector2{60 * (health / maxheal), 6}, D2D1::ColorF(255.f, 0.f, 0.f, 0.8f));
						}
						if ((int)BP->health( ) >= 34 && (int)BP->health( ) <= 66) {
							Renderer::FillRectangle(Vector2{middlePointPlayerFeet.x - 30, middlePointPlayerFeet.y + CurPos}, Vector2{60 * (health / maxheal), 6}, D2D1::ColorF(255.f, 202.f, 0.f, 0.8f));
						}
						if ((int)BP->health( ) >= 67) {
							Renderer::FillRectangle(Vector2{middlePointPlayerFeet.x - 30, middlePointPlayerFeet.y + CurPos}, Vector2{60 * (health / maxheal), 6}, D2D1::ColorF(0.f, 255.f, 0.f, 0.8f));
						}
						Renderer::Rectangle(Vector2{middlePointPlayerFeet.x - 30, middlePointPlayerFeet.y + CurPos}, Vector2{60, 6}, D2D1::ColorF::Black, 0.5f);
					}
				}
				if (vars::npc::tracers) {
					static float screenX = vars::stuff::ScreenWidth;
					static float screenY = vars::stuff::ScreenHeight;
					static Vector2 startPos = Vector2(screenX / 2.0f, screenY - 200.f);
					Renderer::Line(startPos, tempHead, color, 0.5f);
				}
			}
		}
	}
}