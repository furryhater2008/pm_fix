namespace framework {
	float yeet1;
	float yeet2;
	float yeet3;
	float yeet4;
	namespace extras {
		enum menuitemtype {
			SWITCH = 0,
			slider,
			section
		};
		struct menuitems_t {
			menuitems_t(std::wstring name, float* value = 0, int itemtype = menuitemtype::SWITCH, int minimumvalue = 0, int maximumvalue = 1) {
				this->name = name;
				this->value = value;
				this->itemtype = itemtype;
				this->minimumvalue = minimumvalue;
				this->maximumvalue = maximumvalue;
			}

			std::wstring name;
			float* value;
			int itemtype;
			int minimumvalue;
			int maximumvalue;
		};
	}
	std::vector<extras::menuitems_t> menuitems;
	int x = 50, y = 100, w = 200, h = 15;
	float idk = 0;
	float idk2 = 0;
	float cat_0;
	float cat_1;
	float cat_2;
	float cat_3;
	float cat_4;
	int currentselecteditem = 0;
	int menu_alpha;
	int menu_pos;
	float menu_anim = true;
	void handleinput() {
		if (show)
			return;

		if (GetAsyncKeyState(VK_DOWN) & 1) {
			if (currentselecteditem > (menuitems.size() - 2))
				currentselecteditem = 0;
			else
				currentselecteditem++;
		}


		if (GetAsyncKeyState(VK_UP) & 1) {
			if (currentselecteditem < 1)
				currentselecteditem = menuitems.size() - 1;
			else
				currentselecteditem--;
		}
	}
	void addchildren() {
		menuitems.push_back(extras::menuitems_t(L"legit", &cat_0, extras::menuitemtype::section));
		if (cat_0) {
			menuitems.push_back(extras::menuitems_t(L"yeet1", &yeet1));
		}
		menuitems.push_back(extras::menuitems_t(L"visuals", &cat_1, extras::menuitemtype::section));
		if (cat_1) {
			menuitems.push_back(extras::menuitems_t(L"yeet2", &yeet2));
		}
		menuitems.push_back(extras::menuitems_t(L"chams", &cat_2, extras::menuitemtype::section));
		if (cat_2) {
			menuitems.push_back(extras::menuitems_t(L"yeet3", &yeet3));
		}
		menuitems.push_back(extras::menuitems_t(L"misc", &cat_3, extras::menuitemtype::section));
		if (cat_3) {
			menuitems.push_back(extras::menuitems_t(L"yeet4", &yeet4));
		}
		h += 15 * menuitems.size();
	}
	void renderbackground() {
		Renderer::FillRectangle(Vector2(x + menu_pos, y), Vector2(w, h), D2D1::ColorF(0.11, 0.11, 0.11, menu_alpha / 255));
		Renderer::Rectangle(Vector2(x + menu_pos, y), Vector2(w, h), D2D1::ColorF(0, 0, 0, menu_alpha / 255));
		Renderer::FillRectangle(Vector2(x + menu_pos, y), Vector2(w, 15), D2D1::ColorF(0.09, 0.09, 0.09, menu_alpha / 255));
		Renderer::Rectangle(Vector2(x + menu_pos, y), Vector2(w, 15), D2D1::ColorF(0, 0, 0, menu_alpha / 255));
		Renderer::String(Vector2(x + menu_pos + (w / 2), y + 1), L"plusminus", D2D1::ColorF::White, true, true);
		//render::draw_text_string(0, 0, render::fonts::watermark_font, std::to_string(currentselecteditem), false, color(220, 220, 220, 255));
		Renderer::FillRectangle(Vector2(x + menu_pos + 1, y + 15 + (15 * currentselecteditem)), Vector2(w - 1 - 1, 15 - 1), D2D1::ColorF(0.19, 0.19, 0.19, (menu_alpha / 2) / 255));
	}
	void renderchildren() {
		if (!(menuitems.size() > 0))
			return;
		for (int i = 0; i < menuitems.size(); i++) {
			if (menuitems[i].itemtype == extras::menuitemtype::section)
				Renderer::String(Vector2(x + menu_pos + 3, y + 16 + (15 * i)), menuitems[i].name.c_str(), *menuitems[i].value ? D2D1::ColorF(1, 1, 1, menu_alpha / 255) : D2D1::ColorF(1, 1, 1, menu_alpha / 255), true);
			else if (menuitems[i].itemtype == extras::menuitemtype::SWITCH) {
				Renderer::String(Vector2(x + menu_pos + 8, y + 16 + (15 * i)), menuitems[i].name.c_str(), D2D1::ColorF(0.66, 0.66, 0.66, menu_alpha / 255), true);
				Renderer::String(Vector2(x + menu_pos + 8 + 189, y + 16 + (15 * i)), *menuitems[i].value ? L"on" : L"off", *menuitems[i].value ? D2D1::ColorF(0.03, 0.86, 0.03, menu_alpha / 255) : D2D1::ColorF(0.86, 0.03, 0.03, menu_alpha / 255), true, true);
			}
			else {
				Renderer::String(Vector2(x + menu_pos + 8, y + 16 + (15 * i)), menuitems[i].name.c_str(), D2D1::ColorF(170, 170, 170, menu_alpha / 255), true);
				Renderer::String(Vector2(x + menu_pos + 8 + 189, y + 16 + (15 * i)),std::to_wstring((int)*menuitems[i].value).c_str(),D2D1::ColorF(0.03, 0.86, 0.03, menu_alpha / 255), true, true);
				//render::text(x + menu_pos + 8, y + 16 + (15 * i), fontlist::mainfont, display, color(255, 255, 255, 255), false, true, color(0, 0, 0, 255));
			}
		}
	}
	void handlechildren() {
		if (!(menuitems.size() > 0))
			return;

		for (int i = 0; i < menuitems.size(); i++) {
			if (i == currentselecteditem) {
				switch (menuitems[i].itemtype) {
				case extras::menuitemtype::SWITCH:
				{
					if (GetAsyncKeyState(0x0d) & 1 || GetAsyncKeyState(0x0d) & 1 && show)
						*menuitems[i].value = !*menuitems[i].value;



				} break;
				case extras::menuitemtype::slider:
				{
					if ((GetAsyncKeyState(VK_RIGHT) & 1) && *menuitems[i].value < menuitems[i].maximumvalue && show)
						*menuitems[i].value += 1;

					if ((GetAsyncKeyState(VK_LEFT) & 1) && *menuitems[i].value > menuitems[i].minimumvalue && show)
						*menuitems[i].value -= 1;
				} break;
				case extras::menuitemtype::section:
				{
					if (GetAsyncKeyState(0x0d) & 1 || GetAsyncKeyState(0x0d) & 1 && show)
						*menuitems[i].value = !*menuitems[i].value;

				} break;
				}
			}
		}

		renderchildren();
	}
	void run() {
		static bool _pressed = true;

		if (!_pressed && GetAsyncKeyState(VK_INSERT))
			_pressed = true;
		else if (_pressed && !GetAsyncKeyState(VK_INSERT)) {
			_pressed = false;
			show = !show;
		}

		if (show) {
			menu_alpha = min(menu_alpha + 7, 255);
			if (menu_anim)
				menu_pos = min(menu_alpha + 4, 255);
			else
				menu_pos = 255;
		}
		else {
			menu_alpha = max(menu_alpha - 7, 0);
			if (menu_anim)
				menu_pos = max(menu_alpha - 4, 0);
			else
				menu_pos = 255;
		}

		static Vector2 oldpos;
		static Vector2 mousepos;
		static bool _dragging = false;
		bool _click = false;
		static bool _resizing = false;
		static int _drag_x = 300;
		static int _drag_y = 350;
		int finalsize = 200;
		POINT p;
		GetCursorPos(&p);
		Vector2 _mouse_pos = Vector2(p.x, p.y);
		if (GetAsyncKeyState(VK_LBUTTON))
			_click = true;

		if (_dragging && !_click)
			_dragging = false;

		if (_resizing && !_click)
			_resizing = false;

		if (_dragging && _click) {
			x = _mouse_pos.x - _drag_x;
			y = _mouse_pos.y - _drag_y;
		}
		if (Rect(x + menu_pos, y, finalsize, finalsize).Contains(Vector2(p.x, p.y)) && !(Rect(
			x + 10, y + 20, finalsize - 10, finalsize - 10).Contains(Vector2(p.x, p.y)))) {
			_dragging = true;
			_drag_x = _mouse_pos.x - x;
			_drag_y = _mouse_pos.y - y;
		}

		addchildren();
		handleinput();
		renderbackground();
		handlechildren();

		menuitems.clear();
		h = 15;
	}
}