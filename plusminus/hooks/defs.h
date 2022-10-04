namespace hk_defs {
	typedef void(__fastcall* SendProjectileAttack_fn)(BasePlayer*, PlayerProjectileAttack*);
	inline SendProjectileAttack_fn original_sendprojectileattack{ };

	typedef void(__fastcall* launch)(Projectile*);
	inline launch original_launch{ };

	typedef void(__fastcall* dfixd)(PlayerWalkMovement*, ModelState*);
	inline dfixd original_dofixedupdate{ };

	typedef void(__fastcall* clientupdate)(BasePlayer*);
	inline clientupdate original_clientupdate{ };

	typedef void(__fastcall* clientupdate_sleeping)(BasePlayer*);
	inline clientupdate_sleeping original_clientupdate_sleeping{ };

	typedef bool(__fastcall* dhit)(Projectile*, HitTest*, Vector3, Vector3);
	inline dhit original_dohit{ };

	typedef bool(__fastcall* IsDown_hk)(InputState*, BUTTON);
	inline IsDown_hk original_IsDown{ };

	typedef bool(__fastcall* movement_walking)(PlayerWalkMovement*, InputState*, ModelState*);
	inline movement_walking original_walking{ };

	typedef Projectile* (__fastcall* create_projectile_fn)(BaseProjectile*, void*, Vector3, Vector3, Vector3);
	inline create_projectile_fn original_create_projectile{ };

	typedef Projectile* (__fastcall* create_melee_projectile_fn)(uintptr_t, Str, Vector3, Vector3, Vector3);
	inline create_melee_projectile_fn original_melee_create_projectile{ };

	typedef bool(__fastcall* can_attack_fn)(BasePlayer*);
	inline can_attack_fn original_canattack{ };

	typedef void(__fastcall* clientinput_fn)(BasePlayer*, ModelState*);
	inline clientinput_fn original_clientinput{ };

	typedef void(__fastcall* dohitnotify)(BaseCombatEntity*, HitInfo*);
	inline dohitnotify original_dohitnotify{ };

	typedef void(__fastcall* lateupd)(TOD_Sky*);
	inline lateupd original_updateambient{ };

	typedef void(__fastcall* jmp)(PlayerWalkMovement*, ModelState*, bool);
	inline jmp original_jump{ };

	typedef void(__fastcall* rerf)(Projectile*, float);
	inline rerf original_domovement{ };

	typedef void(__fastcall* OnGUI_hk)(DDraw*);
	inline OnGUI_hk original_ongui{ };

	typedef void(__fastcall* thr)(uintptr_t);
	inline thr original_throw{ };

	typedef bool(__fastcall* isheadshot)(HitInfo*);
	inline isheadshot original_getisheadshot{ };

	typedef void(__fastcall* traceallthing)(HitTest*, List<TraceInfo*>, uintptr_t);
	inline traceallthing original_traceall{ };

	typedef float(__fastcall* getrandvel)(ItemModProjectile*);
	inline getrandvel original_getrandomvelocity{ };

	typedef void(__fastcall* sendclienttick)(BasePlayer*);
	inline sendclienttick original_sendclienttick{ };

	typedef void(__fastcall* UnregisterFromVisibilityS)(BasePlayer*, float, bool);
	inline UnregisterFromVisibilityS original_UnregisterFromVisibility{ };

	typedef Vector3(__fastcall* getpos)(PlayerEyes*);
	inline getpos original_geteyepos{ };

	typedef void(__fastcall* crrfrawef)(BasePlayer*, Vector3);
	inline crrfrawef original_forcepos{ };

	typedef Vector3(__fastcall* modifiedaimconedirection)(float, Vector3, bool);
	inline modifiedaimconedirection original_aimconedirection{ };

	typedef void(__fastcall* addpunch)(HeldEntity*, Vector3, float);
	inline addpunch original_addpunch{ };

	typedef void(__fastcall* hurt)(BossFormController*, float, Vector3, Collider*);
	inline hurt original_hurt{ };

	typedef GameObject*(__fastcall* createff)(pUncStr, Effect*);
	inline createff original_createeffect{ };

	typedef void(__fastcall* serverrpc)(BaseEntity*, pUncStr);
	inline serverrpc original_serverrpc{ };

	typedef Vector3(__fastcall* movetowards)(Vector3, Vector3, float);
	inline movetowards original_movetowards{ };

	typedef bool(__fastcall* refr)(Projectile*, uint32_t, Vector3, Vector3, float);
	inline refr original_refract{ };

	typedef void(__fastcall* SetFlying_fn)(ModelState*, bool);
	inline SetFlying_fn original_setflying{ };

	typedef void(__fastcall* ProcessAttack_hk)(BaseMelee*, HitTest*);
	inline ProcessAttack_hk Original_ProcessAttack_hk{ };

	typedef Vector3(__fastcall* hk_BodyLeanOffset)(PlayerEyes*);
	inline hk_BodyLeanOffset Original_BodyLeanOffset{ };

	typedef void(__fastcall* hk_DoFirstPersonCamera)(PlayerEyes*, Component*);
	inline hk_DoFirstPersonCamera Original_DoFirstPersonCamera_hk{ };

	typedef Vector3(__fastcall* hk_EyePositionForPlayer)(BaseMountable*, BasePlayer*, Quaternion*);
	inline hk_EyePositionForPlayer Original_EyePositionForPlayer{ };

	typedef pUncStr(__fastcall* consoleRun)(ConsoleOptions*, pUncStr, DWORD64);
	inline consoleRun original_consolerun{ };

	typedef void(__fastcall* viewmodelPlay)(ViewModel*, pUncStr, int);
	inline viewmodelPlay original_viewmodelplay{ };

	typedef bool(__fastcall* cancan)(BaseMountable*);
	inline cancan original_canholditems{ };

	typedef void(__fastcall* HandleRunning_fn)(void*, void*, bool);
	inline HandleRunning_fn original_handleRunning{};

	typedef void(__fastcall* onland)(BasePlayer*, float);
	inline onland original_onland{ };

	typedef void(__fastcall* handlejumping)(PlayerWalkMovement*, ModelState*, bool, bool);
	inline handlejumping original_handleJumping{ };
}