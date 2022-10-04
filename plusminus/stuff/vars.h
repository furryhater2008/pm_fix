bool init, show = true;
#define null NULL

float indicator_x = 100;
float indicator_y = 100;

std::string C4 = xorstr("C4");
std::string Satchel = xorstr("Satchel");
std::string IncenRocket = xorstr("Incendiary Rocket");
std::string Rocket = xorstr("Rocket");

std::wstring wC4 = xorstr(L"C4");
std::wstring wSatchel = xorstr(L"Satchel");
std::wstring wIncenRocket = xorstr(L"Incendiary Rocket");
std::wstring wRocket = xorstr(L"Rocket");

bool should_interactive = false;
Vector2 screen_center = {0, 0};
namespace Global
{
	bool Panic = false;
	int ScreenHigh = 0;
	int ScreenWidth = 0;
	HWND hWindow = nullptr;
	WNDPROC oWindproc = nullptr;
	float BoneToAim = 0.5;

	int BoneToAim2 = 1;
	DWORD64 PresentDelta = 0;
	char ConfigName[0x100] = "cfg";
}
namespace vars {
	namespace stuff {
		inline Vector3(*Original_BodyLeanOffset)(UINT_PTR);
		bool manipulated = false;
		bool Manipulator = false;
		bool chams = false;
		bool chams1 = false;
		bool chams3 = false;
		bool manipulated1121 = false;
		bool autoshot = false;
		bool medic = false;
		bool farmassist = false;
		Vector3 m_manipulate = Vector3::Zero();
		float m_last_manipulate_time = 0.0f;
		float desync = 0.0f;
		bool gongetflyhack = false;
		float flyhackDistanceVertical = 0.f;
		float flyhackDistanceHorizontal = 0.f;
		float flyhackPauseTime;
		float flyhack = 0.f;
		float hor_flyhack = 0.f;
		float max_flyhack = 0.f;
		float max_hor_flyhack = 0.f;
		int anti_aim_ = 0;
		std::wstring dlldirectory;
		bool debugtab = false;
		int testInt = 0;
		float testFloat = 0.f;
		float testF1loat = 0.f;
		float testFloat1 = 0.f;
		float testFloat2 = 0.f;
		float testFloat3 = 0.f;
		bool testBool = false;
		bool testBool2 = false;
		bool testBool3 = false;
		char testChar[0x100] = "testyvesty";
		char testChar2[0x100] = "testyvesty";
		bool Panic = false;
		bool LoadCheat = false;
		inline float ScreenHeight = 0;
		inline float ScreenWidth = 0;
		char ConfigName[0x100] = "cfg";
	}
	namespace Colors
	{
		inline float Chams[] = { 1.f,1.f,1.f,1.f };
		inline float VisibleChams[] = { 0.f,1.f,0.f,1.f };
		inline float InVisibleChams[] = { 1.f,0.f,0.f,1.f };
		inline float Visible[] = { 0.f, 1.f, 0.f, 0.000f };
		inline float InVisible[] = { 1.f,0.f,0.f,1.f };
	}
	namespace keys {
		inline bool PressedKeys[256] = {};
		int manipulator{ 0x4C };
		int weaponspam{ 0x4C };
		int instakill{ 0x4C };
		int zoom = { 0x42 };
		int suicide = { 0x5A };
		int longneck = { 0x4D };
		int forcepos{ 0x4E };
		int psilent{ 0x50 }; // P key
		int locktarget{ 0x4A };
		int aimkey{ 0x58 }; // VK_RMOUSE
		int gravitykey{ 0x04 };
	}
	namespace stor {
		uintptr_t uBase = NULL;
		uintptr_t gBase = NULL;
		uintptr_t closestPlayer = NULL;
		uintptr_t closestHeli = NULL;
		uintptr_t meme_target = NULL;
	}
	namespace combat {
		bool manipulator = false;
		bool line = false;
		bool line1 = false;
		bool tracer = false;
		bool marker = false;
		bool tree_reflect = false;
		bool magicbollet = false;
		bool always_heli_rotor = false;
		bool always_headshot = false;
		bool silent_melee = false;
		bool psilent = false;
		bool psilent_autoshoot = false;
		bool psilentonkey = false;
		int psilenttarget = 0;
		bool aimbot = false;
		bool smooth = false;
		float smooth_factor = 1;
		bool instakill = false;
		bool instakillonkey = false;

		float range = 300.f;
		float fov = 100.f;
		bool bodyaim = false;
		bool visualize_fov = false;
		bool visualize_prediction = false;
		bool lock_target = false;
		bool ignore_players = false;
		bool ignore_heli = false;
		bool ignore_invisible = false;
		bool ignore_sleepers = false;
		bool ignore_team = true;
		bool ignore_npc = false;
	}
	namespace weapons {
		bool no_recoil = false;
		float recoil_control = 100.f;
		bool fast_bullets = false;
		bool penetrate = false;
		bool minicopter_aim = false;
		bool spoof_hitdistance = false;
		float hitdistance = 100.f;
		bool remove_attack_anim = false;
		bool no_spread = false;
		bool automatic = false;
		bool thick_bullet = false;
		bool no_sway = false;
		bool rapid_fire = false;
		bool fastbow = false;
		bool eokatap = false;
		
	}
	namespace players {
		bool oof_arrows = false;
		bool chams = false;
		bool chams_xqz = false;
		bool belt = false;
		float beltx = 50.f;
		float belty = 50.f;
		bool box = false;
		int boxstyle = 0;
		bool skeleton = false;
		bool name = false;
		bool healthdist = false;
		bool healthbar = false;
		int healthbarstyle = 0;
		bool weapon = false;
		bool sleeperignore = false;
		bool tracers = false;
		int tracers_pos = 0;
		bool targetline = false;
		int targetline_pos = 0;
		bool fillbox = false;
	}
	namespace npc {
		bool chams_xqz = false;
		bool chams = false;
		bool oof_arrows = false;
		bool box = false;
		int boxstyle = false;
		bool skeleton = false;
		bool name = false;
		bool healthdist = false;
		bool healthbar = false;
		int healthbarstyle = 0;
		bool weapon = false;
		bool tracers = false;
		bool fillbox = false;
	}
	namespace ores {
		bool closest_ore = false;
		bool show_collectables = false;
		bool stone = false;
		bool sulfur = false;
		bool metal = false;
		bool hemps = false;
		bool show_distance = false;
		float draw_distance = 300.f;
	}
	namespace visuals {
		bool raid_esp = false;
		bool bradley_apc = false;
		bool patrol_heli = false;
		bool radar_ = false;
		namespace radar {
			float x = 300.f;
			float y = 300.f;
			float range = 160.f;
			float size = 120.f;
		}
		namespace base {
			bool tc = false;
			bool sleeping_bag = false;
			bool bed = false;
			bool boxes = false;
			bool show_distance = false;
			float draw_distance = 300.f;
		}
		namespace vehicles {
			bool minicopter = false;
			bool scrapheli = false;
			bool boat = false;
			bool rhib = false;
			bool show_distance = false;
			float draw_distance = 300.f;
		}
		namespace turrets {
			bool auto_turret = false;
			bool flame_turret = false;
			bool shotgun_turret = false;
			bool landmine = false;
			bool sam_site = false;
			bool bear_trap = false;
			bool show_distance = false;
			float draw_distance = 300.f;
		}
		namespace other {
			bool dropped_items = false;
			bool bodybag = false;
			bool corpse = false;
			bool stash = false;
			bool hemp = false;
			bool show_distance = false;
			float draw_distance = 300.f;
		}
		namespace crates {
			bool elite = false;
			bool military = false;
			bool supply = false;
			bool chinook = false;
			bool heli = false;
			bool bradley = false;
			bool show_distance = false;
			float draw_distance = 300.f;
		}
		namespace animals {
			bool bear = false;
			bool pig = false;
			bool chicken = false;
			bool wolf = false;
			bool deer = false;
			bool show_distance = false;
			float draw_distance = 300.f;
		}
	}
	namespace misc	{
		bool instakillindicator = false;
		bool weapon_spam = false;
		bool flyhack_indicator = false;
		bool farmbot = false;
		bool spiderman = false;
		bool better_jump = false;
		bool no_fall = false;
		bool anti_aim_indicator = false;
		bool hit_logs = false;
		bool auto_farm_ore = false;
		bool auto_farm_tree = false;
		bool can_attack = false;
		bool jesus = false;
		bool SwimOnGround = false;
		bool walker = false;
		bool auto_grade = false;
		int grade_ = 0;
		bool faster_healing = false;
		bool suicide = false;
		bool mass_suicide = false;
		bool long_neck = false;
		bool inf_jump = false;
		bool insta_revive = false;
		bool auto_revive = false;
		bool revive_team_only = false;
		bool rayleigh_changer = false;
		float rayleigh = 10.f;
		bool annoyer = false;
		bool bright_ambient = false;
		bool auto_farm_barrel = false;
		bool egg_bot = false;
		bool auto_pickup = false;
		bool spoof_ladderstate = false;
		bool anti_aim = false;
		float anti_aim_speed = 10;
		int anti_aim_yaw = false;
		bool fake_lag = false;
		bool silent_walk = false;
		float fov = 90.f;
		bool gravity = false;
		float gravity_modifier = 0.f;
		bool custom_hitsound = false;
		bool omnidirectional_sprinting = false;
		bool fakeadmin = false;
		bool custom_time = false;
		float time = 10.0f;
	}
	namespace crosshair {
		bool default = false;
		bool swastika = false;

		bool custom = false;
		bool dot = false;
		float gap = 5.f;
		float length = 5.f;
	}
	namespace player
	{
		bool Hpbar = false;
		bool fill = false;
		bool enable = false;
		bool distance = false;
		bool player = false;
		bool Wounded = false;
		bool Name = false;
		bool Weapon = false;
		bool npc = false;
		bool sleepers = false;
		bool box = false;
		int boxstyle = 0;
		bool skeleton = false;
		bool health_bar = false;
		bool debug_prefab = false;
	}
	namespace MiscVisual
	{
		bool radar_ = false;
		namespace radar {
			float x = 300.f;
			float y = 300.f;
			float range = 160.f;
			float size = 140.f;
		}
		bool rayleigh_changer = false;
		float rayleigh = 1.f;
		bool patrol_heli = false;
		bool RaidEsp = false;
		bool nighmode = false;
		bool target_info = false;
		bool activ_slot = false;
		bool reload_indicator = false;
		bool corsshairs = false;
		int corsshairsstyle = 0;
	}
	namespace resource
	{
		bool ores = false;
		bool stash = false;
		bool vehicles = false;
		bool hemp = false;
		bool corpses = false;
		bool traps = false;
		bool world = false;
	}
	namespace combot
	{
		bool target = false;
		int targetline_pos = 0;

		bool keybinds = false;

		bool logo = true;
		bool fake_lag = false;
		float fake_tick = 0.5f;
		bool Skeet_indicator = false;
		bool indicator_lua = false;
		bool bfly = false;
		int fly;
		bool bclimb = false;
		int assist;
		bool auto_farm_tree = false;
		bool auto_farm_ore = false;
		bool silent_melee = false;
		bool magic_fire = false;
		//bool fly = false;
		bool remove_attack_anim = false;
		bool hitslog = false;
		bool pierce = false;
		bool autoshoot = false;
		bool Perfect_Silent_player = false;
		bool Perfect_Silent_Heli = false;
		bool Manipulated = false;
		bool always_heli_weakspot = false;
		bool draw_targeting_fov = false;
		int targetbone = 0;
		int Falelag_type = 0;
		float fovaim = 50.f;
		bool aimbot = false;
		int aimkey = { 0 };
		bool smooth = false;
		int smooth_factor = 1;
		bool hitsound = false;
		//misc
		bool spoof_hitdistance = false;
		bool spiderman = false;

		float hitdistance = 100.f;
		bool AlwaysSprint = false;
		bool running = false;
		float fov = 90.f;
		int zoomkey = { 0x42 };
		bool bullet_tracers = false;
		bool Jesus = false;
		bool Nofalldamage = false;
		bool Noattacksprinting = false;
		bool nojumpingrestriction = false;
		bool nosprintingrestriction = false;

		bool OnLadder = false;
		int OnLadderkey = { 0 };
		int ManipulatedKey = { 0 };

		bool fakeadmin = false;

		//MiscWeapon
		float recoil_control = 100.f;
		float spead_control = 100.f;
		bool no_sway = false;
		bool big_bullets = false;
		bool fast_bullets = false;
		bool insta_eoka = false;
		bool automatic = false;
		bool fakeshots = false;
		int fakeshotkey = { 0 };
		int FLY = { 0 };
	}
	namespace colors {
		ImVec4 player_esp = { 1.0f, 1.0f, 1.0f, 1.0f };
		ImVec4 team_esp = { 0.f, 1.0f, 0.f, 1.0f };
		ImVec4 dead_esp = { 1.0f, 0.f, 0.f, 1.0f };
		ImVec4 sleeper_esp = { 1.0f, 0.5f, 0.f, 1.0f };
		ImVec4 chams = { 1.0f, 0.f, 0.f, 1.0f };

		ImVec4 npc_esp = { 1.0f, 1.0f, 0.f, 1.0f };
	
		ImVec4 ambient_color = { 0.8f, 0.8f, 0.8f, 0.8f };
	}
}