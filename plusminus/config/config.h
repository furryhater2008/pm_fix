#include <string>
#include <vector>
#include <Windows.h>
template <typename T>
class VarType
{
public:
	VarType(std::string category_, std::string name_, T* value_)
	{
		category = category_;
		name = name_;
		value = value_;
	}

	std::string category, name;
	T* value;
};

class CConfig
{
public:
	CConfig()
	{
		ints = std::vector<VarType<int>*>();
		bools = std::vector<VarType<bool>*>();
		floats = std::vector<VarType<float>*>();
	}

	void Initialize()
	{
		szPath = "C:\\plusminus\\";
		Setup();
	}

	void Save()
	{
		std::string file;
		file = szPath + vars::stuff::ConfigName + ".cfg";

		CreateDirectoryA(szPath.c_str(), NULL);

		for (VarType<int>* pValue : ints)
			WritePrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), std::to_string(*pValue->value).c_str(), file.c_str());

		for (VarType<float>* pValue : floats)
			WritePrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), std::to_string(*pValue->value).c_str(), file.c_str());

		for (VarType<bool>* pValue : bools)
			WritePrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), *pValue->value ? "1" : "0", file.c_str());
	}

	void Load()
	{
		std::string file;
		file = szPath + vars::stuff::ConfigName + ".cfg";
		CreateDirectoryA(szPath.c_str(), NULL);

		char value_l[32] = { '\0' };

		for (VarType<int>* pValue : ints)
		{
			GetPrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), "", value_l, 32, file.c_str());
			*pValue->value = atoi(value_l);
		}

		for (VarType<float>* pValue : floats)
		{
			GetPrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), "", value_l, 32, file.c_str());
			*pValue->value = (float)atof(value_l);
		}

		for (VarType<bool>* pValue : bools)
		{
			GetPrivateProfileStringA(pValue->category.c_str(), pValue->name.c_str(), "", value_l, 32, file.c_str());
			*pValue->value = !strcmp(value_l, "1");
		}
	}

private:
	void SetupValue(int& value, int def, std::string category, std::string name)
	{
		value = def;
		ints.push_back(new VarType<int>(category, name, &value));
	}

	void SetupValue(bool& value, bool def, std::string category, std::string name)
	{
		value = def;
		bools.push_back(new VarType<bool>(category, name, &value));
	}

	void SetupValue(float& value, float def, std::string category, std::string name)
	{
		value = def;
		floats.push_back(new VarType<float>(category, name, &value));
	}

	void Setup()
	{
		SetupValue(vars::combat::always_headshot, false, xorstr("Combat"), xorstr("HitboxOverride"));
		//SetupValue(vars::combat::hs_percentage, 100, xorstr("Combat"), xorstr("HeadshotPercentage"));
		SetupValue(vars::combat::always_heli_rotor, false, xorstr("Combat"), xorstr("AlwaysHeliHotspot"));
		SetupValue(vars::combat::silent_melee, false, xorstr("Combat"), xorstr("SilentMelee"));
		SetupValue(vars::combat::psilent, false, xorstr("Combat"), xorstr("pSilent"));
		SetupValue(vars::combat::psilentonkey, false, xorstr("Combat"), xorstr("pSilentOnKey"));
		SetupValue(vars::combat::aimbot, false, xorstr("Combat"), xorstr("Aimbot"));
		SetupValue(vars::combat::smooth, false, xorstr("Combat"), xorstr("Smooth"));
		SetupValue(vars::combat::smooth_factor, 1, xorstr("Combat"), xorstr("Smoothing"));
		SetupValue(vars::combat::visualize_fov, false, xorstr("Combat"), xorstr("DrawFov"));
		SetupValue(vars::combat::fov, 100.f, xorstr("Combat"), xorstr("Fov"));
		SetupValue(vars::combat::range, 300.f, xorstr("Combat"), xorstr("Range"));
		SetupValue(vars::combat::bodyaim, false, xorstr("Combat"), xorstr("Baim"));
		SetupValue(vars::combat::ignore_sleepers, false, xorstr("Combat"), xorstr("IgnoreSleepers"));
		SetupValue(vars::combat::ignore_team, false, xorstr("Combat"), xorstr("IgnoreTeam"));
		SetupValue(vars::combat::ignore_npc, false, xorstr("Combat"), xorstr("IgnoreNpc"));
		SetupValue(vars::combat::ignore_invisible, false, xorstr("Combat"), xorstr("IgnoreInvisible"));
		SetupValue(vars::combat::ignore_heli, false, xorstr("Combat"), xorstr("IgnoreHeli"));

		SetupValue(vars::weapons::no_recoil, false, xorstr("Weapon"), xorstr("NoRecoil"));
		SetupValue(vars::weapons::recoil_control, 100.f, xorstr("Weapon"), xorstr("RecoilControl"));
		SetupValue(vars::weapons::no_spread, false, xorstr("Weapon"), xorstr("NoSpread"));
		SetupValue(vars::weapons::no_sway, false, xorstr("Weapon"), xorstr("NoSway"));
		SetupValue(vars::weapons::remove_attack_anim, false, xorstr("Weapon"), xorstr("NoAttackAnim"));
		SetupValue(vars::weapons::rapid_fire, false, xorstr("Weapon"), xorstr("RapidFire"));
		SetupValue(vars::weapons::automatic, false, xorstr("Weapon"), xorstr("Automatic"));
		SetupValue(vars::weapons::thick_bullet, false, xorstr("Weapon"), xorstr("ThickBullets"));
		SetupValue(vars::weapons::fast_bullets, false, xorstr("Weapon"), xorstr("CBSM"));
		SetupValue(vars::weapons::minicopter_aim, false, xorstr("Weapon"), xorstr("Minicopter Aim"));
		SetupValue(vars::weapons::eokatap, false, xorstr("Weapon"), xorstr("EokaTap"));
		SetupValue(vars::weapons::fastbow, false, xorstr("Weapon"), xorstr("FastBow"));
		SetupValue(vars::weapons::penetrate, false, xorstr("Weapon"), xorstr("Penetrate"));
		SetupValue(vars::weapons::spoof_hitdistance, false, xorstr("Weapon"), xorstr("SpoofHitDistance"));
		SetupValue(vars::weapons::hitdistance, 300.f, xorstr("Weapon"), xorstr("HitDistance"));
		
		SetupValue(vars::players::name, false, xorstr("Players"), xorstr("name"));
		SetupValue(vars::players::box, false, xorstr("Players"), xorstr("box"));
		SetupValue(vars::players::boxstyle, 0, xorstr("Players"), xorstr("boxstyle"));
		SetupValue(vars::players::fillbox, false, xorstr("Players"), xorstr("fillbox"));
		SetupValue(vars::players::oof_arrows, false, xorstr("Players"), xorstr("oof_arrows"));
		SetupValue(vars::players::skeleton, false, xorstr("Players"), xorstr("skeleton"));
		SetupValue(vars::players::healthdist, false, xorstr("Players"), xorstr("healthdist"));
		SetupValue(vars::players::healthbar, false, xorstr("Players"), xorstr("healthbar"));
		SetupValue(vars::players::healthbarstyle, 0, xorstr("Players"), xorstr("healthbarstyle"));
		SetupValue(vars::players::weapon, false, xorstr("Players"), xorstr("weapon"));
		SetupValue(vars::players::tracers, false, xorstr("Players"), xorstr("tracers"));
		SetupValue(vars::players::chams, false, xorstr("Players"), xorstr("chams"));
		SetupValue(vars::players::chams_xqz, false, xorstr("Players"), xorstr("chams_xqz"));
		SetupValue(vars::players::targetline, false, xorstr("Players"), xorstr("targetline"));
		SetupValue(vars::players::belt, false, xorstr("Players"), xorstr("belt"));
		SetupValue(vars::players::beltx, 300.f, xorstr("Players"), xorstr("beltx"));
		SetupValue(vars::players::belty, 300.f, xorstr("Players"), xorstr("belty"));
		SetupValue(vars::players::sleeperignore, false, xorstr("Players"), xorstr("sleeperignore"));

		SetupValue(vars::npc::name, false, xorstr("NPCs"), xorstr("name"));
		SetupValue(vars::npc::box, false, xorstr("NPCs"), xorstr("box"));
		SetupValue(vars::npc::boxstyle, 0, xorstr("NPCs"), xorstr("boxstyle"));
		SetupValue(vars::npc::oof_arrows, false, xorstr("NPCs"), xorstr("oof_arrows"));
		SetupValue(vars::npc::fillbox, false, xorstr("NPCs"), xorstr("fillbox"));
		SetupValue(vars::npc::skeleton, false, xorstr("NPCs"), xorstr("skeleton"));
		SetupValue(vars::npc::healthdist, false, xorstr("NPCs"), xorstr("healthdist"));
		SetupValue(vars::npc::healthbar, false, xorstr("NPCs"), xorstr("healthbar"));
		SetupValue(vars::npc::healthbarstyle, 0, xorstr("NPCs"), xorstr("healthbarstyle"));
		SetupValue(vars::npc::weapon, false, xorstr("NPCs"), xorstr("weapon"));
		SetupValue(vars::npc::tracers, false, xorstr("NPCs"), xorstr("tracers"));
		
		SetupValue(vars::misc::fov, 90.f, xorstr("Misc"), xorstr("SexyFuckingFovValue"));
		SetupValue(vars::misc::spoof_ladderstate, false, xorstr("Misc"), xorstr("SpoofOnLadder"));
		SetupValue(vars::misc::flyhack_indicator, false, xorstr("Misc"), xorstr("FlyhackIndicator"));
		SetupValue(vars::misc::anti_aim, false, xorstr("Misc"), xorstr("AntiAim"));
		SetupValue(vars::misc::anti_aim_speed, 25, xorstr("Misc"), xorstr("AntiAimSpeed"));
		SetupValue(vars::misc::anti_aim_yaw, 0, xorstr("Misc"), xorstr("AntiAimYaw"));
		SetupValue(vars::misc::anti_aim_indicator, false, xorstr("Misc"), xorstr("AntiAimIndicator"));
		SetupValue(vars::misc::hit_logs, false, xorstr("Misc"), xorstr("HitLogs"));
		SetupValue(vars::misc::faster_healing, false, xorstr("Misc"), xorstr("FastHeal"));
		SetupValue(vars::misc::fake_lag, false, xorstr("Misc"), xorstr("FakeLag"));
		SetupValue(vars::misc::fakeadmin, false, xorstr("Misc"), xorstr("FakeAdmin"));
		SetupValue(vars::misc::annoyer, false, xorstr("Misc"), xorstr("Annoyer"));
		SetupValue(vars::misc::suicide, false, xorstr("Misc"), xorstr("Suicide"));
		SetupValue(vars::misc::no_fall, false, xorstr("Misc"), xorstr("NoFall"));
		SetupValue(vars::misc::can_attack, false, xorstr("Misc"), xorstr("ShootAnywhere"));
		SetupValue(vars::misc::omnidirectional_sprinting, false, xorstr("Misc"), xorstr("OmniSprint"));
		SetupValue(vars::misc::long_neck, false, xorstr("Misc"), xorstr("LongNeck"));
		SetupValue(vars::misc::walker, false, xorstr("Misc"), xorstr("IgnoreCollision"));
		SetupValue(vars::misc::jesus, false, xorstr("Misc"), xorstr("Jesus"));
		SetupValue(vars::misc::spiderman, false, xorstr("Misc"), xorstr("Spiderman"));
		SetupValue(vars::misc::inf_jump, false, xorstr("Misc"), xorstr("InfiniteJump"));
		SetupValue(vars::misc::better_jump, false, xorstr("Misc"), xorstr("BetterJump"));
		SetupValue(vars::misc::custom_hitsound, false, xorstr("Misc"), xorstr("CustomHitsound"));
		SetupValue(vars::misc::auto_pickup, false, xorstr("Misc"), xorstr("AutoCollect"));
		SetupValue(vars::misc::auto_revive, false, xorstr("Misc"), xorstr("AutoAssist"));
		SetupValue(vars::misc::auto_grade, false, xorstr("Misc"), xorstr("AutoGrade"));
		SetupValue(vars::misc::grade_, 1, xorstr("Misc"), xorstr("Grade"));
		SetupValue(vars::misc::insta_revive, false, xorstr("Misc"), xorstr("InstaRevive"));
		SetupValue(vars::misc::revive_team_only, false, xorstr("Misc"), xorstr("AssistTeamOnly"));
		SetupValue(vars::misc::auto_farm_ore, false, xorstr("Misc"), xorstr("SilentOre"));
		SetupValue(vars::misc::auto_farm_tree, false, xorstr("Misc"), xorstr("SilentTree"));
		SetupValue(vars::misc::bright_ambient, false, xorstr("Misc"), xorstr("CustomAmbient"));
		SetupValue(vars::misc::rayleigh_changer, false, xorstr("Misc"), xorstr("Rayleigh"));
		SetupValue(vars::misc::rayleigh, 1.f, xorstr("Misc"), xorstr("RayleighAmount"));
		SetupValue(vars::misc::custom_time, false, xorstr("Misc"), xorstr("CustomTime"));
		SetupValue(vars::misc::time, 10.f, xorstr("Misc"), xorstr("Time"));
		SetupValue(vars::misc::gravity, false, xorstr("Misc"), xorstr("Gravity"));
		SetupValue(vars::misc::gravity_modifier, 0.f, xorstr("Misc"), xorstr("GravityModifier"));

		SetupValue(vars::ores::stone, false, xorstr("ores"), xorstr("stone"));
		SetupValue(vars::ores::sulfur, false, xorstr("ores"), xorstr("sulfur"));
		SetupValue(vars::ores::metal, false, xorstr("ores"), xorstr("metal"));
		SetupValue(vars::ores::show_collectables, false, xorstr("ores"), xorstr("ShowCollectabless"));
		SetupValue(vars::ores::draw_distance, 300.f, xorstr("ores"), xorstr("oreDrawDistance"));
		SetupValue(vars::ores::show_distance, false, xorstr("ores"), xorstr("showDistttatattattatwtawt"));

		SetupValue(vars::visuals::radar_, false, xorstr("visuals"), xorstr("Radar"));
		SetupValue(vars::visuals::raid_esp, false, xorstr("visuals"), xorstr("Raids"));
		SetupValue(vars::visuals::patrol_heli, false, xorstr("visuals"), xorstr("PatrolHeli"));
		SetupValue(vars::visuals::bradley_apc, false, xorstr("visuals"), xorstr("BradleyAPC"));
		SetupValue(vars::visuals::animals::bear, false, xorstr("visuals"), xorstr("bear"));
		SetupValue(vars::visuals::animals::pig, false, xorstr("visuals"), xorstr("pig"));
		SetupValue(vars::visuals::animals::wolf, false, xorstr("visuals"), xorstr("wolf"));
		SetupValue(vars::visuals::animals::chicken, false, xorstr("visuals"), xorstr("chicken"));
		SetupValue(vars::visuals::animals::deer, false, xorstr("visuals"), xorstr("deer"));
		SetupValue(vars::visuals::animals::draw_distance, 300.f, xorstr("visuals"), xorstr("animal_distance"));
		SetupValue(vars::visuals::animals::show_distance, false, xorstr("visuals"), xorstr("showdist"));
		SetupValue(vars::visuals::vehicles::minicopter, false, xorstr("visuals"), xorstr("Minicopter"));
		SetupValue(vars::visuals::vehicles::scrapheli, false, xorstr("visuals"), xorstr("ScrapHeli"));
		SetupValue(vars::visuals::vehicles::boat, false, xorstr("visuals"), xorstr("Boat"));
		SetupValue(vars::visuals::vehicles::rhib, false, xorstr("visuals"), xorstr("RHIB"));
		SetupValue(vars::visuals::vehicles::show_distance, false, xorstr("visuals"), xorstr("vehicleDistance"));
		SetupValue(vars::visuals::vehicles::draw_distance, 300.f, xorstr("visuals"), xorstr("drawVehicleDistance"));
		SetupValue(vars::visuals::turrets::auto_turret, false, xorstr("visuals"), xorstr("AutoTurret"));
		SetupValue(vars::visuals::turrets::flame_turret, false, xorstr("visuals"), xorstr("FlameTurret"));
		SetupValue(vars::visuals::turrets::shotgun_turret, false, xorstr("visuals"), xorstr("ShotgunTurret"));
		SetupValue(vars::visuals::turrets::landmine, false, xorstr("visuals"), xorstr("Landmine"));
		SetupValue(vars::visuals::turrets::bear_trap, false, xorstr("visuals"), xorstr("BearTrap"));
		SetupValue(vars::visuals::turrets::sam_site, false, xorstr("visuals"), xorstr("sam_site"));
		SetupValue(vars::visuals::turrets::show_distance, false, xorstr("visuals"), xorstr("trapDistance"));
		SetupValue(vars::visuals::turrets::draw_distance, 300.f, xorstr("visuals"), xorstr("drawTrapDistance"));
		SetupValue(vars::visuals::base::bed, false, xorstr("visuals"), xorstr("bed"));
		SetupValue(vars::visuals::base::boxes, false, xorstr("visuals"), xorstr("boxes"));
		SetupValue(vars::visuals::base::sleeping_bag, false, xorstr("visuals"), xorstr("sleeping_bag"));
		SetupValue(vars::visuals::base::tc, false, xorstr("visuals"), xorstr("tc"));
		SetupValue(vars::visuals::base::show_distance, false, xorstr("visuals"), xorstr("base_ShowDist"));
		SetupValue(vars::visuals::base::draw_distance, 300.f, xorstr("visuals"), xorstr("draw_drawdww"));
		SetupValue(vars::visuals::other::corpse, false, xorstr("visuals"), xorstr("Corpse"));
		SetupValue(vars::visuals::other::stash, false, xorstr("visuals"), xorstr("Stash"));
		SetupValue(vars::visuals::other::hemp, false, xorstr("visuals"), xorstr("Hemp"));
		SetupValue(vars::visuals::other::dropped_items, false, xorstr("visuals"), xorstr("DroppedItems"));
		SetupValue(vars::visuals::other::bodybag, false, xorstr("visuals"), xorstr("bodybag"));
		SetupValue(vars::visuals::other::show_distance, false, xorstr("visuals"), xorstr("otherDistance"));
		SetupValue(vars::visuals::other::draw_distance, 300.f, xorstr("visuals"), xorstr("drawOtherDistance"));
		SetupValue(vars::visuals::crates::supply, false, xorstr("visuals"), xorstr("Supply"));
		SetupValue(vars::visuals::crates::chinook, false, xorstr("visuals"), xorstr("Chinook"));
		SetupValue(vars::visuals::crates::heli, false, xorstr("visuals"), xorstr("Heli"));
		SetupValue(vars::visuals::crates::elite, false, xorstr("visuals"), xorstr("elite"));
		SetupValue(vars::visuals::crates::military, false, xorstr("visuals"), xorstr("military"));
		SetupValue(vars::visuals::crates::bradley, false, xorstr("visuals"), xorstr("Bradley"));
		SetupValue(vars::visuals::crates::show_distance, false, xorstr("visuals"), xorstr("cratehsowdist"));
		SetupValue(vars::visuals::crates::draw_distance, 300.f, xorstr("visuals"), xorstr("otherDistanceCRTATES"));

		SetupValue(vars::keys::locktarget, 0x4A, xorstr("Keys"), xorstr("LockTarget"));
		SetupValue(vars::keys::aimkey, 0x58, xorstr("Keys"), xorstr("aimKey"));
		SetupValue(vars::keys::gravitykey, 0x04, xorstr("Keys"), xorstr("gravityKey"));
		SetupValue(vars::keys::forcepos, 0x4E, xorstr("Keys"), xorstr("froc"));
		SetupValue(vars::keys::suicide, 0x5A, xorstr("Keys"), xorstr("suicide"));
		SetupValue(vars::keys::weaponspam, 0x4C, xorstr("Keys"), xorstr("weaponspam"));
		SetupValue(vars::keys::psilent, 0x50, xorstr("Keys"), xorstr("pSilent"));
		SetupValue(vars::keys::longneck, 0x4D, xorstr("Keys"), xorstr("neck"));

		SetupValue(vars::crosshair::default, false, xorstr("Crosshair"), xorstr("Default"));
		SetupValue(vars::crosshair::swastika, false, xorstr("Crosshair"), xorstr("Swastika"));
		SetupValue(vars::crosshair::custom, false, xorstr("Crosshair"), xorstr("Custom"));
		SetupValue(vars::crosshair::gap, 5.f, xorstr("Crosshair"), xorstr("Gap"));
		SetupValue(vars::crosshair::length, 5.f, xorstr("Crosshair"), xorstr("Length"));
		SetupValue(vars::crosshair::dot, false, xorstr("Crosshair"), xorstr("Dot"));

		SetupValue(indicator_x, 100.f, xorstr("a"), xorstr("x"));
		SetupValue(indicator_y, 100.f, xorstr("a"), xorstr("y"));

		SetupValue(vars::visuals::radar::x, 100.f, xorstr("Radar"), xorstr("x"));
		SetupValue(vars::visuals::radar::y, 100.f, xorstr("Radar"), xorstr("y"));
		SetupValue(vars::visuals::radar::size, 121.f, xorstr("Radar"), xorstr("size"));
		SetupValue(vars::visuals::radar::range, 160.f, xorstr("Radar"), xorstr("range"));

		SetupValue(vars::colors::ambient_color.x, 0.8f, xorstr("colors"), xorstr("ambient x"));
		SetupValue(vars::colors::ambient_color.y, 0.8f, xorstr("colors"), xorstr("ambient y"));
		SetupValue(vars::colors::ambient_color.z, 0.8f, xorstr("colors"), xorstr("ambient z"));
		SetupValue(vars::colors::ambient_color.w, 0.8f, xorstr("colors"), xorstr("ambient w"));
		SetupValue(vars::colors::chams.x, 1, xorstr("colors"), xorstr("chams x"));
		SetupValue(vars::colors::chams.y, 0, xorstr("colors"), xorstr("chams y"));
		SetupValue(vars::colors::chams.z, 0, xorstr("colors"), xorstr("chams z"));
		SetupValue(vars::colors::chams.w, 1, xorstr("colors"), xorstr("chams w"));
	}

	std::string szPath = "";

protected:
	std::vector<VarType<int>*> ints;
	std::vector<VarType<bool>*> bools;
	std::vector<VarType<float>*> floats;
};

CConfig config;