

int Drehungswinkel = 90;
void swastika_crosshair( ) {
	POINT Screen; 
	Screen.x = vars::stuff::ScreenWidth; Screen.y = vars::stuff::ScreenHeight;
	POINT Middle; Middle.x = (int)(Screen.x / 2); Middle.y = (int)(Screen.y / 2);
	int a = (int)(Screen.y / 2 / 30);
	float gamma = atan(a / a);
	int i = 0;
	while (i < 4) {
		std::vector <int> p;
		p.push_back(a * sin(Math::GRD_TO_BOG(Drehungswinkel + (i * 90))));									//p[0]		p0_A.x
		p.push_back(a * cos(Math::GRD_TO_BOG(Drehungswinkel + (i * 90))));									//p[1]		p0_A.y
		p.push_back((a / cos(gamma)) * sin(Math::GRD_TO_BOG(Drehungswinkel + (i * 90) + Math::BOG_TO_GRD(gamma))));	//p[2]		p0_B.x
		p.push_back((a / cos(gamma)) * cos(Math::GRD_TO_BOG(Drehungswinkel + (i * 90) + Math::BOG_TO_GRD(gamma))));	//p[3]		p0_B.y

		Renderer::Line(Vector2(Middle.x, Middle.y), Vector2(Middle.x + p[ 0 ], Middle.y - p[ 1 ]), D2D1::ColorF::Red);
		Renderer::Line(Vector2(Middle.x + p[ 0 ], Middle.y - p[ 1 ]), Vector2(Middle.x + p[ 2 ], Middle.y - p[ 3 ]), D2D1::ColorF::Red);

		i++;
	}
}

void pre_draw( ) {
	if (vars::crosshair::swastika) {
		swastika_crosshair( );

		Drehungswinkel += 2.f;
		if (Drehungswinkel >= 90.f) {
			Drehungswinkel = 0.f;
		}
	}
	
	auto* TargetPlayerA = reinterpret_cast<BasePlayer*>(vars::stor::closestPlayer);
	Vector2 kek = Renderer::CanvasSize( );
	vars::stuff::ScreenWidth = kek.x;
	vars::stuff::ScreenHeight = kek.y;
	float xs = vars::stuff::ScreenWidth / 2, ys = vars::stuff::ScreenHeight / 2;
	if (vars::crosshair::default) {
		Renderer::Line(Vector2{xs, ys}, Vector2{xs + 4, ys + 4}, D2D1::ColorF::White, 0.7f);
		Renderer::Line(Vector2{xs, ys}, Vector2{xs + 4, ys - 4}, D2D1::ColorF::White, 0.7f);
		Renderer::Line(Vector2{xs, ys}, Vector2{xs - 4, ys - 4}, D2D1::ColorF::White, 0.7f);
		Renderer::Line(Vector2{xs, ys}, Vector2{xs - 4, ys + 4}, D2D1::ColorF::White, 0.7f);

		Renderer::Line(Vector2{xs + 4, ys + 4}, Vector2{xs + 4 + 4, ys + 4 + 4}, D2D1::ColorF::Black, 0.7f);
		Renderer::Line(Vector2{xs + 4, ys - 4}, Vector2{xs + 4 + 4, ys - 4 - 4}, D2D1::ColorF::Black, 0.7f);
		Renderer::Line(Vector2{xs - 4, ys - 4}, Vector2{xs - 4 - 4, ys - 4 - 4}, D2D1::ColorF::Black, 0.7f);
		Renderer::Line(Vector2{xs - 4, ys + 4}, Vector2{xs - 4 - 4, ys + 4 + 4}, D2D1::ColorF::Black, 0.7f);
	}
	if (vars::crosshair::custom) {
		if (vars::crosshair::dot) {
			Renderer::FillRectangle(Vector2{xs , ys}, Vector2{2, 2}, D2D1::ColorF::White);
		}
		// i did it ! lol
		Renderer::FillRectangle(Vector2{xs + vars::crosshair::gap, ys}, Vector2{vars::crosshair::length, 2}, D2D1::ColorF::White); // right
		Renderer::FillRectangle(Vector2{xs - vars::crosshair::gap + 2, ys}, Vector2{-vars::crosshair::length , 2}, D2D1::ColorF::White); // left
		Renderer::FillRectangle(Vector2{xs , ys - vars::crosshair::gap + 2}, Vector2{2 , -vars::crosshair::length}, D2D1::ColorF::White); // up
		Renderer::FillRectangle(Vector2{xs , ys + vars::crosshair::gap}, Vector2{2 , vars::crosshair::length}, D2D1::ColorF::White); // down
	}
	if (vars::combat::visualize_fov) {
		Renderer::Circle(Vector2{xs, ys}, D2D1::ColorF::White, vars::combat::fov, 1.f);
	}
	float FOV = vars::combat::fov, CurFOV;
	if (vars::stor::closestPlayer != NULL) {
		if (FOV < (CurFOV = GetFov(TargetPlayerA, BoneList(0.5))) && !vars::combat::lock_target) {
			vars::stor::closestPlayer = NULL;
		}
	}
	if (vars::stor::closestHeli != NULL) {
		Vector3 pos = reinterpret_cast<BaseEntity*>(vars::stor::closestHeli)->transform( )->position( );
		if (FOV < (CurFOV = GetFovHeli(pos))) {
			vars::stor::closestHeli = NULL;
		}
	}
	if (reinterpret_cast<BaseEntity*>(vars::stor::closestPlayer)->IsDestroyed( )) {
		vars::stor::closestPlayer = NULL;
	}
	if (reinterpret_cast<BaseEntity*>(vars::stor::closestHeli)->IsDestroyed( )) {
		vars::stor::closestHeli = NULL;
	}
	if (vars::combat::lock_target && vars::stor::closestPlayer != NULL) {
		Renderer::Text(Vector2{xs, ys - 50}, D2D1::ColorF::PaleVioletRed, true, true, xorstr(L"Target Locked: %s"), TargetPlayerA->_displayName( ));
	}
	if (vars::ores::closest_ore) {
		static float screenX = vars::stuff::ScreenWidth;
		static float screenY = vars::stuff::ScreenHeight;
		Vector2 startPos = Vector2(screenX / 2.f, screenY - 200.f);

		f_object tr1 = f_object::get_closest_object(LocalPlayer::Entity( )->get_bone_pos(head), xorstr("ore.prefab"));
		Vector2 screen;
		if (utils::w2s(tr1.position, screen) && tr1.valid) {
			Renderer::Line(startPos, screen, D2D1::ColorF::GhostWhite, 1.f);

			f_object tr2 = f_object::get_closest_object(tr1.position, xorstr("ore.prefab"), tr1.position);
			Vector2 screen2;
			if (utils::w2s(tr2.position, screen2) && tr2.valid) {
				Renderer::Line(screen, screen2, D2D1::ColorF::GhostWhite, 1.f);

				f_object tr3 = f_object::get_closest_object(tr2.position, xorstr("ore.prefab"), tr1.position, tr2.position);
				Vector2 screen3;
				if (utils::w2s(tr3.position, screen3) && tr3.valid) {
					Renderer::Line(screen2, screen3, D2D1::ColorF::GhostWhite, 1.f);

					f_object tr4 = f_object::get_closest_object(tr3.position, xorstr("ore.prefab"), tr1.position, tr2.position, tr3.position);
					Vector2 screen4;
					if (utils::w2s(tr4.position, screen4) && tr4.valid) {
						Renderer::Line(screen3, screen4, D2D1::ColorF::GhostWhite, 1.f);
					}
				}
			}
		}
	}
	if (vars::stor::closestPlayer != NULL && vars::players::targetline && TargetPlayerA->IsValid( )) {
		static float screenX = vars::stuff::ScreenWidth;
		static float screenY = vars::stuff::ScreenHeight;
		static Vector2 startPos;
		if (vars::players::targetline_pos == 0) {
			startPos = Vector2(screenX / 2.f, screenY - 200.f);
		}
		if (vars::players::targetline_pos == 1) {
			startPos = Vector2(screenX / 2, screenY / 2);
		}
		Vector2 ScreenPos;
		if (!(TargetPlayerA->get_bone_pos(spine1).x == 0 && TargetPlayerA->get_bone_pos(spine1).y == 0 && TargetPlayerA->get_bone_pos(spine1).z == 0)) {
			if (utils::w2s(TargetPlayerA->get_bone_pos(head), ScreenPos)) {
				Renderer::Line(startPos, ScreenPos, D2D1::ColorF::Red, 1.f);
			}
		}
	}
	if (vars::combat::visualize_prediction && TargetPlayerA->IsValid( )) {
		Vector2 t;
		if (!(TargetPlayerA->get_bone_pos(spine1).x == 0 && TargetPlayerA->get_bone_pos(spine1).y == 0 && TargetPlayerA->get_bone_pos(spine1).z == 0)) {
			if (utils::w2s(a::get_aim_point(GetBulletSpeed( ), GetGravity(LocalPlayer::Entity( )->GetActiveWeapon( )->LoadedAmmo( ))), t)) {
				Renderer::Circle(t, D2D1::ColorF::Red, 4.5f);
			}
		}
	}
	//DoIcon();
	if (vars::stor::closestHeli != NULL && vars::visuals::patrol_heli) {
		static float screenX = vars::stuff::ScreenWidth;
		static float screenY = vars::stuff::ScreenHeight;
		static Vector2 startPos = Vector2(screenX / 2.f, screenY - 200.f);
		Vector2 ScreenPos;
		if ((int)ceil(read(vars::stor::closestHeli + 0x20C, float)) > 0) {
			if (utils::w2s(reinterpret_cast<BaseEntity*>(vars::stor::closestHeli)->transform( )->position( ), ScreenPos)) 
				Renderer::Line(startPos, ScreenPos, D2D1::ColorF(0.3f, 0.34f, 1.f), 1.f);
		}

	}
	if (vars::combat::fov > (kek.y - 3)) { vars::combat::fov = (kek.y - 3); } // limit fov
	if (vars::misc::fov < 30) { vars::misc::fov = 80; } // limit graph fov
	if (vars::combat::smooth_factor <= 0) { vars::combat::smooth_factor = 1; }
	if (vars::misc::grade_ > 4) { vars::misc::grade_ = 4; }
	if (vars::weapons::hitdistance < 300) { vars::weapons::hitdistance = 300; }
	if (vars::misc::anti_aim && vars::misc::anti_aim_indicator) {
		int radius = 80;
		float range = 5;
		int LineLength = 50;
		POINT p;
		if (GetCursorPos(&p)) {
			if (p.x >= indicator_x - radius && p.x <= indicator_x + radius) {
				if (p.y >= indicator_y - radius && p.y <= indicator_y + radius) {
					if (GetAsyncKeyState(VK_LBUTTON) && show) {
						indicator_x = p.x;
						indicator_y = p.y;
					}
				}
			}
		}
		Renderer::FillCircle(Vector2(indicator_x, indicator_y), D2D1::ColorF(0.13, 0.13, 0.13, 0.6), radius);//this draws that grey circle u see :]
		float origyaw = vars::stuff::anti_aim_;
		Renderer::CosTanSinLine(origyaw, range, indicator_x, indicator_y, LineLength, D2D1::ColorF::Red);//this the function from b4 btw
	}
	if (TargetPlayerA) {
		if (vars::stor::closestPlayer != NULL && vars::players::belt && TargetPlayerA->IsValid( )) {//&& !TargetPlayerA->IsNpc( ) 
			const float Height = 275.f;
			const float Width = 150.f;
			POINT p;
			if (GetCursorPos(&p)) {
				if (p.x >= vars::players::beltx && p.x <= vars::players::beltx + Width) {
					if (p.y >= vars::players::belty && p.y <= vars::players::belty + Height) {
						if (GetAsyncKeyState(VK_LBUTTON) && show) {
							vars::players::beltx = p.x - (Width / 2);
							vars::players::belty = p.y - (Height / 2);
						}
					}
				}
			}
			Renderer::FillRectangle({vars::players::beltx, vars::players::belty}, {Width, Height}, D2D1::ColorF(0.06f, 0.06f, 0.06f, 0.94f));
			Renderer::Rectangle({vars::players::beltx, vars::players::belty}, {Width, Height}, D2D1::ColorF(0.43f, 0.43f, 0.50f, 0.50f));
			Renderer::Text({vars::players::beltx + (Width / 2), vars::players::belty + 10}, D2D1::ColorF::White, true, true, TargetPlayerA->_displayName( ));
			Renderer::Line({vars::players::beltx, vars::players::belty + 20}, {vars::players::beltx + Width, vars::players::belty + 20}, D2D1::ColorF(0.43f, 0.43f, 0.50f, 0.50f), 1);
			float Pos = 0;
			if (TargetPlayerA->item_list_b( )) {
				for (int i = 0; i < TargetPlayerA->item_list_b( )->get_size( ); i++) { // belt
					Item* ActWeapon = TargetPlayerA->item_list_b( )->get_value(i);
					wchar_t prefix[ 3 ];
					if (ActWeapon) {
						if (ActWeapon == TargetPlayerA->GetActiveWeapon( )) {
							_swprintf(prefix, xorstr(L"->"));
						}
						else {
							_swprintf(prefix, xorstr(L""));
						}
						wchar_t* ActiveItem = ActWeapon->get_name( );
						if (ActiveItem) {
							if (ActiveItem != nullptr && wcslen(ActiveItem) < 20)
							{
								Renderer::Text({ vars::players::beltx + (Width / 2), vars::players::belty + 40 + Pos }, D2D1::ColorF::White, true, true, xorstr(L"%s %s [x%d]"), prefix, ActiveItem, ActWeapon->count());
							}
						}
					}
					Pos += 15;
				}
			}
			Renderer::FillRectangle(Vector2{vars::players::beltx + (Width / 2) - 40, vars::players::belty + 135}, Vector2{80 * (TargetPlayerA->health( ) / 100.f), 10}, D2D1::ColorF(0.f, 255.f, 0.f, 0.8f));
			Renderer::Rectangle(Vector2{vars::players::beltx + (Width / 2) - 40, vars::players::belty + 135}, Vector2{80, 10}, D2D1::ColorF::White, 0.5f);
			float cPos = 125;
			if (TargetPlayerA->item_list_w( )) {
				for (int i = 0; i < TargetPlayerA->item_list_w( )->get_size( ); i++) { // clothes
					Item* ActWeapon = TargetPlayerA->item_list_w( )->get_value(i);
					if (ActWeapon) {
						wchar_t* ActiveItem = ActWeapon->get_name( );
						if (ActiveItem) {
							Renderer::Text({vars::players::beltx + (Width / 2), vars::players::belty + 40 + cPos}, D2D1::ColorF::White, true, true, xorstr(L"%s"), ActiveItem);
						}
					}
					cPos += 15;
				}
			}
		}
	}
	ent_loop( );
}