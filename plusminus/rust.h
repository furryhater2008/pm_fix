using ptr_t = uint64_t;
enum UnmanagedCallingConvention {
	UnmanagedCdecl,
	UnmanagedStdcall,
	UnmanagedFastcall,
};

template<typename t_Function>
class UnmanagedPointer {
public:

	template<typename... t_FunctionParameters>
	auto operator()(t_FunctionParameters... params) {
		using result_type = decltype(std::declval<t_Function>()(std::declval<t_FunctionParameters>()...));
		using function_cdecl_ptr_t = result_type(__cdecl*)(t_FunctionParameters...);
		using function_stdcall_ptr_t = result_type(__stdcall*)(t_FunctionParameters...);
		using function_fastcall_ptr_t = result_type(_fastcall*)(t_FunctionParameters...);

		switch (this->m_CallingConvention) {
		case UnmanagedCdecl:
			return reinterpret_cast<function_cdecl_ptr_t>(this->m_Address)(params...);
		case UnmanagedStdcall:
			return reinterpret_cast<function_stdcall_ptr_t>(this->m_Address)(params...);
		case UnmanagedFastcall:
			return reinterpret_cast<function_fastcall_ptr_t>(this->m_Address)(params...);
		}
	}

	UnmanagedPointer(ptr_t dwAddress, UnmanagedCallingConvention unmCallingConvention) {
		this->m_Address = dwAddress;
		this->m_CallingConvention = unmCallingConvention;
	}
private:
	ptr_t m_Address;
	UnmanagedCallingConvention m_CallingConvention;
};
class SafeExecution {
public:
	static int fail(unsigned int code, struct _EXCEPTION_POINTERS* ep) {
		if (code == EXCEPTION_ACCESS_VIOLATION) {
			return EXCEPTION_EXECUTE_HANDLER;
		}
		else {
			return EXCEPTION_CONTINUE_SEARCH;
		};
	}
public:
	template<typename T = void*, typename R = void*, typename... Args>
	static T Execute(uint64_t ptr, R ret, Args... args) {
		__try {
			return reinterpret_cast<T(__stdcall*)(Args...)>(ptr)(args...);
		}
		__except (fail(GetExceptionCode(), GetExceptionInformation())) {
			return ret;
		}
	}
};



#define STATIC_FUNCTION(method_path,name,ta) static inline UnmanagedPointer<ta> name = { METHOD(method_path), UnmanagedStdcall }



class Transform {
public:
	Vector3 position() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Transform::get_position(): Vector3");
		return SafeExecution::Execute<Vector3>(off, Vector3::Zero(), this);
	}
	Vector3 InverseTransformPoint(Vector3 position) {
		if (!this) return Vector3::Zero();

		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Transform::InverseTransformPoint(Vector3): Vector3");

		return reinterpret_cast<Vector3(__fastcall*)(Transform*, Vector3)>(off)(this, position);
	}

	Vector3 InverseTransformDirection(Vector3 position) {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Transform::InverseTransformDirection(Vector3): Vector3");
		return SafeExecution::Execute<Vector3>(off, Vector3::Zero(), this, position);
	}

	Vector3 up() {
		if (!this)
			return Vector3::Zero();

		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Transform::get_up(): Vector3");
		return SafeExecution::Execute<Vector3>(off, Vector3::Zero(), this);
	}
	void set_position(Vector3 value) {
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Transform::set_position(Vector3): Void");
		reinterpret_cast<void(__fastcall*)(Transform*, Vector3)>(off)(this, value);
	}
};
class GameObject {
public:
	const wchar_t* name()
	{
		if (!this) return 0;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Object::get_name(): String");
		return reinterpret_cast<il2cpp::String * (__fastcall*)(GameObject*)>(off)(this)->buffer;
	}
};
class Object {
public:
	Transform* transform() {
		if (!this) return nullptr;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Component::get_transform(): Transform");
		return SafeExecution::Execute<Transform*>(off, nullptr, this);
	}
};

class Event {
public:
	STATIC_FUNCTION("UnityEngine.IMGUIModule::UnityEngine::Event::get_current(): Event", get_current, Event* ());
	EventType get_type() {
		if (!this) return EventType::Zero;
		static auto off = METHOD("UnityEngine.IMGUIModule::UnityEngine::Event::get_type(): EventType");
		return reinterpret_cast<EventType(__fastcall*)(Event*)>(off)(this);
	}
};
class Type {
public:
	// pass as "Namespace.Classname, Assembly.Name"
	static Type* GetType(const char* qualified_name) {
		static auto off = METHOD("mscorlib::System::Type::GetType(String): Type");
		return reinterpret_cast<Type * (__cdecl*)(il2cpp::String*)>(off)(il2cpp::String::New(qualified_name));
	}
	static Type* SkinnedMeshRenderer() {
		Type* type = GetType(xorstr("UnityEngine.SkinnedMeshRenderer, UnityEngine.CoreModule"));
		return type;
	}
	static Type* Renderer() {
		Type* type = GetType(xorstr("UnityEngine.Renderer, UnityEngine.CoreModule"));
		return type;
	}
	static Type* Shader() {
		Type* type = GetType(xorstr("UnityEngine.Shader, UnityEngine.CoreModule"));
		return type;
	}
	static Type* Projectile() {
		Type* type = GetType(xorstr("Projectile, Assembly-CSharp"));
		return type;
	}
	static Type* ItemModProjectile() {
		Type* type = GetType(xorstr("ItemModProjectile, Assembly-CSharp"));
		return type;
	}
};
class Component : public Object {
public:
	template<typename T = Component>
	T* GetComponent(Type* type) {
		if (!this || !type) return nullptr;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Component::GetComponent(Type): Component");
		return reinterpret_cast<T * (__fastcall*)(Component*, Type*)>(off)(this, type);
	}
	GameObject* gameObject() {
		if (!this) return nullptr;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Component::get_gameObject(): GameObject");
		return SafeExecution::Execute<GameObject*>(off, nullptr, this);
	}
	uint32_t class_name_hash() {
		__try {
			if (!this) return 0;
			auto oc = *reinterpret_cast<uint64_t*>(this);
			if (!oc) return 0;
			if (!*reinterpret_cast<char**>(oc + 0x10)) return 0;
			const char* name = *reinterpret_cast<char**>(oc + 0x10);
			if (!name) return 0;
			return RUNTIME_CRC32(name);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) { return 0; };
	}
};
class Transform;
class Bone {
public:
	Vector3 position;
	bool visible;
	Transform* transform;
	Bone() {
		this->position = Vector3::Zero();
		this->visible = false;
	}
	Bone(Vector3 position, bool visible) {
		this->position = position;
		this->visible = visible;
		this->transform = nullptr;
	}
	Bone(Vector3 position, bool visible, Transform* traa) {
		this->position = position;
		this->visible = visible;
		this->transform = traa;
	}
	
};
class BoneCache {
public:
	Bone* head;
	Bone* neck;
	Bone* root;
	Bone* spine4;
	Bone* spine1;
	Bone* l_clavicle;
	Bone* l_upperarm;
	Bone* l_forearm;
	Bone* l_hand;
	Bone* r_clavicle;
	Bone* r_upperarm;
	Bone* r_forearm;
	Bone* r_hand;
	Bone* pelvis;
	Bone* l_hip;
	Bone* l_knee;
	Bone* l_ankle_scale;
	Bone* l_foot;
	Bone* r_hip;
	Bone* r_knee;
	Bone* r_ankle_scale;
	Bone* r_foot;

	il2cpp::box_bounds bounds;
	Vector2 dfc;
	Quaternion eye_rot;

	BoneCache() {
		head = new Bone();
		neck = new Bone();
		root = new Bone();
		spine4 = new Bone();
		spine1 = new Bone();
		l_clavicle = new Bone();
		l_upperarm = new Bone();
		l_forearm = new Bone();
		l_hand = new Bone();
		r_clavicle = new Bone();
		r_upperarm = new Bone();
		r_forearm = new Bone();
		r_hand = new Bone();
		pelvis = new Bone();
		l_hip = new Bone();
		l_knee = new Bone();
		l_ankle_scale = new Bone();
		l_foot = new Bone();
		r_hip = new Bone();
		r_knee = new Bone();
		r_ankle_scale = new Bone();
		r_foot = new Bone();
	}
};
std::map<uint64_t, BoneCache*> cachedBones = std::map<uint64_t, BoneCache*>();
class Attack {
public:
	FIELD("Rust.Data::ProtoBuf::Attack::hitID", hitID, uint32_t);
	FIELD("Rust.Data::ProtoBuf::Attack::hitBone", hitBone, uint32_t);
	FIELD("Rust.Data::ProtoBuf::Attack::hitMaterialID", hitMaterialID, uint32_t);
	FIELD("Rust.Data::ProtoBuf::Attack::hitPositionWorld", hitPositionWorld, Vector3);
	FIELD("Rust.Data::ProtoBuf::Attack::hitNormalWorld", hitNormalWorld, Vector3);
	FIELD("Rust.Data::ProtoBuf::Attack::pointStart", pointStart, Vector3);
	FIELD("Rust.Data::ProtoBuf::Attack::pointEnd", pointEnd, Vector3);
};
class Model;
class ItemModProjectile {

};
class BaseNetworkable : public Component {
public:
	class EntityRealm {
	public:
		template<typename T = BaseNetworkable*> T Find(uint32_t uid) {
			static auto off = METHOD("Assembly-CSharp::EntityRealm::Find(UInt32): BaseNetworkable");
			return reinterpret_cast<T(__fastcall*)(EntityRealm*, uint32_t)>(off)(this, uid);
		}
		template<typename T = BaseNetworkable*>
		T FindClosest(uint32_t hash, BaseNetworkable* targetEnt, float dist) {
			T ent = nullptr;

			auto entityList = this->entityList();
			if (entityList) {
				for (int i = 1; i < entityList->vals->size; i++) {
					auto baseNetworkable = *reinterpret_cast<BaseNetworkable**>(std::uint64_t(entityList->vals->buffer) + (0x20 + (sizeof(void*) * i)));
					if (!baseNetworkable) continue;

					if (baseNetworkable->class_name_hash() == hash && baseNetworkable->transform()->position().distance(targetEnt->transform()->position()) <= dist) {
						ent = reinterpret_cast<T>(baseNetworkable);
						break;
					}
				}
			}

			return ent;
		}

		FIELD("Assembly-CSharp::EntityRealm::entityList", entityList, ListDictionary*);
	};
	static EntityRealm* clientEntities() {
		static auto clazz = CLASS("Assembly-CSharp::BaseNetworkable");
		return *reinterpret_cast<EntityRealm**>(std::uint64_t(clazz->static_fields));
	}
};
class BaseEntity : public BaseNetworkable {
public:

	Vector3 GetWorldVelocity() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("Assembly-CSharp::BaseEntity::GetWorldVelocity(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(BaseEntity*)>(off)(this);
	}
	bool IsDestroyed() {
		if (!this) return true;
		static auto off = OFFSET("Assembly-CSharp::BaseNetworkable::<IsDestroyed>k__BackingField");
		return *reinterpret_cast<bool*>(this + off);
	}
	void ServerRPC(const char* funcName) {
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::BaseEntity::ServerRPC(String): Void");
		reinterpret_cast<void(__stdcall*)(BaseEntity*, il2cpp::String*)>(off)(this, il2cpp::String::New(funcName));
	}
	bool IsValid() {
		if (!this) return false;
		return !this->IsDestroyed();
	}
	std::uint32_t ShortPrefabName_hash() {
		if (!this) return 0;
		static auto off = METHOD("Assembly-CSharp::BaseNetworkable::get_ShortPrefabName(): String");
		return RUNTIME_CRC32_W(reinterpret_cast<il2cpp::String * (__fastcall*)(BaseNetworkable*)>(off)(this)->buffer);
	}
	FIELD("Assembly-CSharp::BaseEntity::model", model, Model*);
};
class RenderSettings {
public:
	enum class AmbientMode {
		Skybox,
		Trilight,
		Flat,
		Custom
	};
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::RenderSettings::set_ambientMode(Rendering.AmbientMode): Void", set_ambientMode, void(AmbientMode));
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::RenderSettings::set_ambientIntensity(Single): Void", set_ambientIntensity, void(float));
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::RenderSettings::set_ambientLight(Color): Void", set_ambientLight, void(Color));
};
class Input {
public:
	STATIC_FUNCTION("UnityEngine.InputLegacyModule::UnityEngine::Input::GetKeyDown(KeyCode): Boolean", GetKeyDown, bool(KeyCode));
	STATIC_FUNCTION("UnityEngine.InputLegacyModule::UnityEngine::Input::GetKey(KeyCode): Boolean", GetKey, bool(KeyCode));
};
class Shader {
public:
	static Shader* Find(char* name) {
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Shader::Find(String): Shader");
		return reinterpret_cast<Shader * (__fastcall*)(il2cpp::String*)>(off)(il2cpp::String::New(name));
	}
	static int PropertyToID(char* name) {
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Shader::PropertyToID(String): Int32");
		return reinterpret_cast<int(__fastcall*)(il2cpp::String*)>(off)(il2cpp::String::New(name));
	}
};
class Material {
public:
	/*void SetColor(int proper, Color value) {
		if (!this) return;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Material::SetColor(Int32,Color): Void");
		return reinterpret_cast<void(__fastcall*)(Material*, int, Color)>(off)(this, proper, value);
	}*/
	void SetColor(char* proper, Color value) {
		if (!this) return;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Material::SetColor(String,Color): Void");
		return reinterpret_cast<void(__fastcall*)(Material*, il2cpp::String*, Color)>(off)(this, il2cpp::String::New(proper), value);
	}
	void SetInt(char* name, int value) {
		if (!this) return;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Material::SetInt(String,Int32): Void");
		return reinterpret_cast<void(__fastcall*)(Material*, il2cpp::String*, int)>(off)(this, il2cpp::String::New(name), value);
	}
	void SetFloat(char* name, float value) {
		if (!this) return;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Material::SetFloat(String,Single): Void");
		return reinterpret_cast<void(__fastcall*)(Material*, il2cpp::String*, float)>(off)(this, il2cpp::String::New(name), value);
	}
	Shader* shader() {
		if (!this) return nullptr;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Material::get_shader(): Shader");
		return reinterpret_cast<Shader * (__fastcall*)(Material*)>(off)(this);
	}
	void set_shader(Shader* val, uint64_t off) {
		static int exceptionCounter = 0;
		__try {
			if (exceptionCounter <= 10) {
				exceptionCounter++;
				return;
			}
			if (!this || !val || !off) return;

			return reinterpret_cast<void(__fastcall*)(Material*, Shader*)>(off)(this, val);
		}
		__except (SafeExecution::fail(GetExceptionCode(), GetExceptionInformation())) {
			exceptionCounter = 0;
		};
	}
};
class BasePlayer;
Shader* glowShader;
Shader* WirShader;
Shader* FieldChams;
Shader* FieldRainbow;
Shader* Xray;
Shader* FloatChams;
Shader* chamsShader;
BasePlayer* Player = nullptr;
BasePlayer* target_ply = nullptr;
BasePlayer* closest_ply = nullptr;
class BaseCombatEntity : public BaseEntity {
public:
	enum class LifeState {
		Alive = 0,
		Dead = 1
	};
	const char* ClassName() {
		if (!this) return "";
		auto oc = *reinterpret_cast<uint64_t*>(this);
		if (!oc) return "";
		return *reinterpret_cast<char**>(oc + 0x10);
	}
	uint32_t ClassNameHash() {
		if (!this) return 0;
		auto oc = *reinterpret_cast<uint64_t*>(this);
		if (!oc) return 0;
		const char* name = *reinterpret_cast<char**>(oc + 0x10);
		return RUNTIME_CRC32(name);
	}
	bool IsPlayer() {
		if (!this) return false;
		return !strcmp(this->ClassName(), xorstr("BasePlayer")) ||
			!strcmp(this->ClassName(), xorstr("NPCPlayerApex")) ||
			!strcmp(this->ClassName(), xorstr("NPCMurderer")) ||
			!strcmp(this->ClassName(), xorstr("NPCPlayer")) ||
			!strcmp(this->ClassName(), xorstr("HumanNPC")) ||
			!strcmp(this->ClassName(), xorstr("Scientist")) ||
			!strcmp(this->ClassName(), xorstr("TunnelDweller")) ||
			!strcmp(this->ClassName(), xorstr("BanditGuard")) ||
			!strcmp(this->ClassName(), xorstr("ScientistNPC")) ||
			!strcmp(this->ClassName(), xorstr("NPCMissionProvider")) ||
			!strcmp(this->ClassName(), xorstr("Scientist")) ||
			!strcmp(this->ClassName(), xorstr("ScientistNPCNew")) ||
			!strcmp(this->ClassName(), xorstr("HTNPlayer"));

	}
	FIELD("Assembly-CSharp::BaseCombatEntity::_health", health, float);
	FIELD("Assembly-CSharp::BaseCombatEntity::sendsHitNotification", sendsHitNotification, bool);
	FIELD("Assembly-CSharp::BaseCombatEntity::sendsMeleeHitNotification", sendsMeleeHitNotification, bool);
	FIELD("Assembly-CSharp::BaseCombatEntity::sendsMeleeHitNotification", lastNotifyFrame, int);
	FIELD("Assembly-CSharp::BaseCombatEntity::lifestate", lifestate, LifeState);
};
class Time {
public:
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_time(): Single", time, float());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_deltaTime(): Single", deltaTime, float());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_fixedTime(): Single", fixedTime, float());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_unscaledTime(): Single", unscaledTime, float());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_unscaledDeltaTime(): Single", unscaledDeltaTime, float());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_fixedDeltaTime(): Single", fixedDeltaTime, float());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_maximumDeltaTime(): Single", maximumDeltaTime, float());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_smoothDeltaTime(): Single", smoothDeltaTime, float());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_timeScale(): Single", timeScale, float());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_frameCount(): Int32", frameCount, int());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_renderedFrameCount(): Int32", renderedFrameCount, int());
	STATIC_FUNCTION("UnityEngine.CoreModule::UnityEngine::Time::get_realtimeSinceStartup(): Single", realtimeSinceStartup, float());
};

class Physics {
public:
	STATIC_FUNCTION("UnityEngine.PhysicsModule::UnityEngine::Physics::get_gravity(): Vector3", get_gravity, Vector3());
	static void IgnoreLayerCollision(int layer1, int layer2, bool ignore) {
		return reinterpret_cast<void(*)(int, int, bool)>(il2cpp::il2cpp_resolve_icall(xorstr("UnityEngine.Physics::IgnoreLayerCollision")))(layer1, layer2, ignore);
	}

	STATIC_FUNCTION("Assembly-CSharp::GamePhysics::CheckCapsule(Vector3,Vector3,Single,Int32,QueryTriggerInteraction): Boolean", CheckCapsule, bool(Vector3, Vector3, float, int, QueryTriggerInteraction));
};
class ItemDefinition : public Component {
public:
	FIELD("Assembly-CSharp::ItemDefinition::itemid", itemid, int);
};
class BaseProjectile /*: public AttackEntity*/ {
public:
	class Magazine {
	public:
		FIELD("Assembly-CSharp::Magazine::ammoType", ammoType, ItemDefinition*);
		FIELD("Assembly-CSharp::Magazine::contents", contents, int);
	};
	FIELD("Assembly-CSharp::BaseProjectile::primaryMagazine", primaryMagazine, Magazine*);
	FIELD("Assembly-CSharp::BaseProjectile::nextReloadTime", nextReloadTime, float);
	FIELD("Assembly-CSharp::BaseProjectile::reloadTime", reloadTime, float);
	FIELD("Assembly-CSharp::BaseProjectile::lastShotTime", lastShotTime, float);
	FIELD("Assembly-CSharp::BaseProjectile::projectileVelocityScale", projectileVelocityScale, float);//timeSinceDeploy
	FIELD("Assembly-CSharp::AttackEntity::timeSinceDeploy", timeSinceDeploy, float);//timeSinceDeploy deployDelay
	FIELD("Assembly-CSharp::AttackEntity::deployDelay", deployDelay, float);
	FIELD("Assembly-CSharp::AttackEntity::repeatDelay", repeatDelay, float);
	void LaunchProjectile() {
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::BaseProjectile::LaunchProjectile(): Void");
		return reinterpret_cast<void(__fastcall*)(BaseProjectile*)>(off)(this);
	}
	void DoAttack() {
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::BaseProjectile::DoAttack(): Void");
		return reinterpret_cast<void(__fastcall*)(BaseProjectile*)>(off)(this);
	}
	bool Empty() {
		if (!this) return true;
		if (!this->primaryMagazine()) return true;

		return this->primaryMagazine()->contents() <= 0;
	}
	bool HasAttackCooldown()
	{
		if (!this) return false;

		static auto off = METHOD("Assembly-CSharp::AttackEntity::HasAttackCooldown(): Boolean");

		return reinterpret_cast<bool(__fastcall*)(BaseProjectile*)>(off)(this);
	}
	float get_NextAttackTime()
	{
		if (!this) return false;

		static auto off = METHOD("Assembly-CSharp::AttackEntity::get_NextAttackTime(): Single");

		return reinterpret_cast<bool(__fastcall*)(BaseProjectile*)>(off)(this);
	}
	void ShotFired() {
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::BaseProjectile::ShotFired(): Void");
		return reinterpret_cast<void(__fastcall*)(BaseProjectile*)>(off)(this);
	}
	void DidAttackClientside() {//BeginCycle
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::BaseProjectile::DidAttackClientside(): Void");
		return reinterpret_cast<void(__fastcall*)(BaseProjectile*)>(off)(this);
	}
	void UpdateAmmoDisplay() { //ShotFired DidAttackClientside
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::BaseProjectile::UpdateAmmoDisplay(): Void");
		return reinterpret_cast<void(__fastcall*)(BaseProjectile*)>(off)(this);
	}
	void BeginCycle() {//BeginCycle
		if (!this) return;
		static auto off = METHOD("Assembly-CSharp::BaseProjectile::BeginCycle(): Void");
		return reinterpret_cast<void(__fastcall*)(BaseProjectile*)>(off)(this);
	}
	float GLOBAL_TIME = 0.f;
	bool HasReloadCooldown() {
		return GLOBAL_TIME < this->nextReloadTime();
	}
	uint32_t class_name_hash() {
		__try {
			if (!this) return 0;
			auto oc = *reinterpret_cast<uint64_t*>(this);
			if (!oc) return 0;
			if (!*reinterpret_cast<char**>(oc + 0x10)) return 0;
			const char* name = *reinterpret_cast<char**>(oc + 0x10);
			if (!name) return 0;
			return RUNTIME_CRC32(name);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) { return 0; };
	}
};

class DamageTypeList {
public:
	enum class DamageType {
		Generic,
		Hunger,
		Thirst,
		Cold,
		Drowned,
		Heat,
		Bleeding,
		Poison,
		Suicide,
		Bullet,
		Slash,
		Blunt,
		Fall,
		Radiation,
		Bite,
		Stab,
		Explosion,
		RadiationExposure,
		ColdExposure,
		Decay,
		ElectricShock,
		Arrow,
		AntiVehicle,
		Collision,
		Fun_Water,
		LAST
	};
	float Total() {
		if (!this) return false;
		static auto off = METHOD("Assembly-CSharp::Rust::DamageTypeList::Total(): Single");
		return reinterpret_cast<float(__fastcall*)(DamageTypeList*)>(off)(this);
	}
};
class HitInfo {
public:
	FIELD("Assembly-CSharp::HitInfo::Initiator", Initiator, BaseEntity*);
	FIELD("Assembly-CSharp::HitInfo::WeaponPrefab", WeaponPrefab, BaseEntity*);
	FIELD("Assembly-CSharp::HitInfo::DoHitEffects", DoHitEffects, bool);
	FIELD("Assembly-CSharp::HitInfo::DoDecals", DoDecals, bool);
	FIELD("Assembly-CSharp::HitInfo::IsPredicting", IsPredicting, bool);
	FIELD("Assembly-CSharp::HitInfo::UseProtection", UseProtection, bool);
	FIELD("Assembly-CSharp::HitInfo::DidHit", DidHit, bool);
	FIELD("Assembly-CSharp::HitInfo::HitEntity", HitEntity, BaseEntity*);
	FIELD("Assembly-CSharp::HitInfo::HitBone", HitBone, uint32_t);
	FIELD("Assembly-CSharp::HitInfo::HitPart", HitPart, uint32_t);
	FIELD("Assembly-CSharp::HitInfo::HitMaterial", HitMaterial, uint32_t);
	FIELD("Assembly-CSharp::HitInfo::HitPositionWorld", HitPositionWorld, Vector3);
	FIELD("Assembly-CSharp::HitInfo::HitPositionLocal", HitPositionLocal, Vector3);
	FIELD("Assembly-CSharp::HitInfo::HitNormalWorld", HitNormalWorld, Vector3);
	FIELD("Assembly-CSharp::HitInfo::HitNormalLocal", HitNormalLocal, Vector3);
	FIELD("Assembly-CSharp::HitInfo::PointStart", PointStart, Vector3);
	FIELD("Assembly-CSharp::HitInfo::PointEnd", PointEnd, Vector3);
	FIELD("Assembly-CSharp::HitInfo::ProjectileID", ProjectileID, int);
	FIELD("Assembly-CSharp::HitInfo::ProjectileDistance", ProjectileDistance, float);
	FIELD("Assembly-CSharp::HitInfo::ProjectileVelocity", ProjectileVelocity, Vector3);
	FIELD("Assembly-CSharp::HitInfo::damageTypes", damageTypes, DamageTypeList*);
};
struct ProjectileWeaponModModifier {
};
class TOD_Sky {
public:
};
class BossFormController {
public:
};
class Collider {
public:
};
class Effect {
public:
};
class RigidBody {
public:
	Vector3 velocity() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("UnityEngine.PhysicsModule::UnityEngine::Rigidbody::get_velocity(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(RigidBody*)>(off)(this);
	}
	void set_velocity(Vector3 value) {
		if (!this) return;
		static auto off = METHOD("UnityEngine.PhysicsModule::UnityEngine::Rigidbody::set_velocity(Vector3): Void");
		return reinterpret_cast<void(__fastcall*)(RigidBody*, Vector3)>(off)(this, value);
	}
};
class PlayerWalkMovement {
public:
	FIELD("Assembly-CSharp::PlayerWalkMovement::flying", flying, bool);
	FIELD("Assembly-CSharp::PlayerWalkMovement::maxAngleWalking", maxAngleWalking, float);
	FIELD("Assembly-CSharp::PlayerWalkMovement::body", body, RigidBody*);
	FIELD("Assembly-CSharp::PlayerWalkMovement::maxVelocity", maxVelocity, float);
	FIELD("Assembly-CSharp::PlayerWalkMovement::groundAngle", groundAngle, float);
	FIELD("Assembly-CSharp::PlayerWalkMovement::groundAngleNew", groundAngleNew, float);
	FIELD("Assembly-CSharp::PlayerWalkMovement::groundNormal", groundNormal, Vector3);
	FIELD("Assembly-CSharp::PlayerWalkMovement::jumpTime", jumpTime, float);
	FIELD("Assembly-CSharp::PlayerWalkMovement::landTime", landTime, float);
	FIELD("Assembly-CSharp::PlayerWalkMovement::groundTime", groundTime, float);
	FIELD("Assembly-CSharp::PlayerWalkMovement::gravityMultiplier", gravityMultiplier, float);
	FIELD("Assembly-CSharp::PlayerWalkMovement::climbing", climbing, bool);
	FIELD("Assembly-CSharp::PlayerWalkMovement::sliding", sliding, bool);
	FIELD("Assembly-CSharp::PlayerWalkMovement::grounded", grounded, bool);
	FIELD("Assembly-CSharp::PlayerWalkMovement::jumping", jumping, bool);
	FIELD("Assembly-CSharp::PlayerWalkMovement::swimming", swimming, bool);
	FIELD("Assembly-CSharp::PlayerWalkMovement::ladder", ladder, void*);
	FIELD("Assembly-CSharp::BaseMovement::<Ducking>k__BackingField", Ducking, float);
	FIELD("Assembly-CSharp::BaseMovement::<TargetMovement>k__BackingField", TargetMovement, Vector3);
};
enum BUTTON {
	FORWARD = 2,
	BACKWARD = 4,
	LEFT = 8,
	RIGHT = 16,
	JUMP = 32,
	DUCK = 64,
	SPRINT = 128,
	USE = 256,
	FIRE_PRIMARY = 1024,
	FIRE_SECONDARY = 2048,
	RELOAD = 8192,
	FIRE_THIRD = 134217728,
};
class InputState {
public:
	static inline bool(*IsDown_)(InputState*, BUTTON) = nullptr;
	bool IsDown(BUTTON btn) {
		return IsDown_(this, btn);
	}
};
class TeamMember {
public:
	bool online() {
		return *reinterpret_cast<bool*>(this + 0x38);
	}
	uint64_t& userID() {
		return *reinterpret_cast<uint64_t*>(this + 0x20);
	}
	Vector3& position() {
		return *reinterpret_cast<Vector3*>(this + 0x2C);
	}
	const wchar_t* displayName() {
		if (!this) return L"---";
		return (*reinterpret_cast<il2cpp::String**>(this + 0x18))->buffer;
	}
};
class ModelState {
public:
	void set_jumped(bool value) {
		if (!this) return;
		static auto off = METHOD("Rust.Data::ModelState::set_jumped(Boolean): Void");
		return reinterpret_cast<void(__fastcall*)(ModelState*, bool)>(off)(this, value);
	}
	void set_ducked(bool value) {
		if (!this) return;
		static auto off = METHOD("Rust.Data::ModelState::set_ducked(Boolean): Void");
		return reinterpret_cast<void(__fastcall*)(ModelState*, bool)>(off)(this, value);
	}
	void set_mounted(bool value) {
		if (!this) return;
		static auto off = METHOD("Rust.Data::ModelState::set_mounted(Boolean): Void");
		return reinterpret_cast<void(__fastcall*)(ModelState*, bool)>(off)(this, value);
	}
	FIELD("Rust.Data::ModelState::flags", flags, int);
};
class BaseMountable {
public:
};
class PlayerProjectileAttack {
public:
};
class TraceInfo {
public:
};
class ViewModel {
public:
};
class PlayerNameID {
public:
	wchar_t* username() {
		auto username = (pUncStr)(*reinterpret_cast<uintptr_t*>((uintptr_t)this + 0x18));
		return username->str;
	}

	unsigned long user_id() {
		return *reinterpret_cast<unsigned long*>((uintptr_t)this + 0x20);
	}
};
class PlayerEyes : public Component {
public:
	FIELD("Assembly-CSharp::PlayerEyes::viewOffset", viewOffset, Vector3);
	FIELD("Assembly-CSharp::PlayerEyes::<bodyRotation>k__BackingField", bodyRotation, Quaternion);
	static Vector3 EyeOffset() {
		static auto clazz = CLASS("Assembly-CSharp::PlayerEyes");
		return *reinterpret_cast<Vector3*>(std::uint64_t(clazz->static_fields));
	}
	Vector3 get_position() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("Assembly-CSharp::PlayerEyes::get_position(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(PlayerEyes*)>(off)(this);
	}
	Quaternion get_rotation() {
		if (!this) return Quaternion{};
		static auto off = METHOD("Assembly-CSharp::PlayerEyes::get_rotation(): Quaternion");
		return reinterpret_cast<Quaternion(__fastcall*)(PlayerEyes*)>(off)(this);
	}

	Vector3 MovementForward() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("Assembly-CSharp::PlayerEyes::MovementForward(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(PlayerEyes*)>(off)(this);
	}
	Vector3 MovementRight() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("Assembly-CSharp::PlayerEyes::MovementRight(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(PlayerEyes*)>(off)(this);
	}
	Vector3 HeadForward() {
		if (!this) return Vector3::Zero();
		static auto off = METHOD("Assembly-CSharp::PlayerEyes::HeadForward(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(PlayerEyes*)>(off)(this);
	}

};
class BaseMovement {
public:
	FIELD("Assembly-CSharp::BaseMovement::adminCheat", adminCheat, bool);
	FIELD("Assembly-CSharp::BaseMovement::<TargetMovement>k__BackingField", TargetMovement, Vector3);
	FIELD("Assembly-CSharp::BaseMovement::<Running>k__BackingField", Running, float);
	FIELD("Assembly-CSharp::BaseMovement::<Grounded>k__BackingField", Grounded, float);
	FIELD("Assembly-CSharp::BaseMovement::<Ducking>k__BackingField", Ducking, float);
};
class Renderer_ {
public:
	Material* material() {
		if (!this) return nullptr;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Renderer::get_material(): Material");
		return reinterpret_cast<Material* (__fastcall*)(Renderer_*)>(off)(this);
	}
	void set_material(Material* value) {
		if (!this) return;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Renderer::set_material(Material): Void");
		return reinterpret_cast<void(__fastcall*)(Renderer_*, Material*)>(off)(this, value);
	}
	bool isVisible() {
		if (!this) return false;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Renderer::get_isVisible(): Boolean");
		return reinterpret_cast<bool(__fastcall*)(Renderer_*)>(off)(this);
	}
	Array<Material*>* materials() {
		if (!this) return nullptr;
		static auto off = METHOD("UnityEngine.CoreModule::UnityEngine::Renderer::get_materials(): Material[]");
		return reinterpret_cast<Array<Material*>*(__fastcall*)(Renderer_*)>(off)(this);
	}
};
class PlayerModel;
class Renderer_;
class SkinnedMultiMesh {
public:
	List<Renderer_*>* Renderers() {
		if (!this) return nullptr;
		static auto off = OFFSET("Assembly-CSharp::SkinnedMultiMesh::<Renderers>k__BackingField");
		return *reinterpret_cast<List<Renderer_*>**>(this + off);
	}
	static inline void(*RebuildModel_)(SkinnedMultiMesh*, PlayerModel*, bool) = nullptr;
	void RebuildModel(PlayerModel* model, bool reset) {
		return RebuildModel_(this, model, reset);
	}
};
class PlayerModel {
public:
	FIELD("Assembly-CSharp::PlayerModel::position", position, Vector3);
	bool isNpc() {
		if (!this) return false;
		static auto off = OFFSET("Assembly-CSharp::PlayerModel::<IsNpc>k__BackingField");
		return *reinterpret_cast<bool*>(this + off);
	}
	FIELD("Assembly-CSharp::PlayerModel::_multiMesh", _multiMesh, SkinnedMultiMesh*);
};
class PlayerTick {
public:
	Vector3 position() {
		Vector3 th = read(this + 0x20, Vector3);
		if (!th.empty()) {
			return th;
		}
		else { return Vector3::Zero(); }
	}
};
class ConsoleOptions {
public:
	bool IsFromServer() { return read(this + 0x6, bool); }
};
class Item {
public:
	uintptr_t entity() {
		return read(this + 0x98, uintptr_t);
	}
	template<typename T = void*>
	T* heldEntity() {
		if (!this) return nullptr;
		static auto off = OFFSET("Assembly-CSharp::Item::heldEntity");
		return *reinterpret_cast<T**>(this + off);
	}
	int GetID() {
		DWORD64 Info = read((DWORD64)this + 0x20, DWORD64); // public ItemDefinition info;
		int ID = read(Info + 0x18, int); // public int itemid;
		return ID;
	}
	char* ClassName() {
		return (char*)read(read(this->entity(), DWORD64) + 0x10, DWORD64);
	}
	int LoadedAmmo() {
		uintptr_t Held = this->entity();
		if (!Held) return 0;

		uintptr_t Magazine = read(Held + O::BaseProjectile::primaryMagazine, uintptr_t);
		if (!Magazine) return 0;

		uintptr_t ammoType = read(Magazine + 0x20, uintptr_t);
		if (!ammoType) return 0;

		int ammo = read(ammoType + 0x18, int);
		return ammo;
	}
	Weapon Info() {
		int ID = GetID();
		for (Weapon k : info) {
			if (k.id == ID) {
				return k;
			}
		}
		return Weapon{ 0 };
	}
	wchar_t* get_name() {
		uintptr_t Info = read(this + 0x20, uintptr_t);
		uintptr_t DispName = read(Info + 0x28, uintptr_t);
		pUncStr Str = ((pUncStr)read(DispName + 0x18, uintptr_t)); // default
		if (!Str) return nullptr; return Str->str;
	}
	int count() {
		return read(this + 0x30, int);
	}
	int uid() {
		return read(this + 0x28, int);
	}
	void RapidFire() {
		if (vars::weapons::rapid_fire) {
			DWORD64 heldentity = this->entity();
			write(heldentity + O::AttackEntity::repeatDelay, 0.09f, float);
		}
	}
	void NoSway() {
		DWORD64 Heldd = this->entity();
		if (vars::weapons::no_sway) {
			write(Heldd + 0x2C8, 0.f, float);
			write(Heldd + 0x2CC, 0.f, float);
		}
	}
	void SetAutomatic() {
		if (vars::weapons::automatic) {
			DWORD64 Heldd = this->entity();
			write(Heldd + O::BaseProjectile::automatic, 1, bool);
		}
	}
	void FastBow() {
		if (vars::weapons::fastbow) {
			DWORD64 Heldd = this->entity();
			write(Heldd + O::BowWeapon::attackReady, true, bool);
			write(Heldd + O::BowWeapon::arrowBack, 1.f, float);
		}
	}
	void EokaTap() {
		if (vars::weapons::eokatap) {
			DWORD64 Heldd = this->entity();
			write(Heldd + O::BowWeapon::attackReady, 1.f, float); // successFraction
			write(Heldd + O::BowWeapon::wasAiming, true, bool); // didSparkThisFrame
		}
	}
};
class ItemContainer {
public:
	FIELD("Assembly-CSharp::ItemContainer::itemList", itemList, List<Item*>*);
};
class PlayerInventory {
public:
	FIELD("Assembly-CSharp::PlayerInventory::containerBelt", containerBelt, ItemContainer*);
	FIELD("Assembly-CSharp::PlayerInventory::containerWear", containerWear, ItemContainer*);
	FIELD("Assembly-CSharp::PlayerInventory::containerMain", containerMain, ItemContainer*);
};
class HeldEntity : public BaseEntity {
public:
	FIELD("Assembly-CSharp::HeldEntity::viewModel", viewModel, ViewModel*);
	static inline void(*AddPunch_)(HeldEntity*, Vector3, float) = nullptr;
	void AddPunch(Vector3 amount, float duration) {
		return AddPunch_(this, amount, duration);
	}
	Item* GetItem() {
		if (!this) return nullptr;
		static auto off = METHOD("Assembly-CSharp::HeldEntity::GetItem(): Item");
		return reinterpret_cast<Item * (__fastcall*)(HeldEntity*)>(off)(this);
	}
};
class BasePlayer : public BaseCombatEntity {
public:
	const wchar_t* _displayName() {
		if (!this) return L"";
		static auto off = OFFSET("Assembly-CSharp::BasePlayer::_displayName");
		return (*reinterpret_cast<il2cpp::String**>(this + off))->buffer;
	}
	FIELD("Assembly-CSharp::BasePlayer::eyes", eyes, PlayerEyes*);
	FIELD("Assembly-CSharp::BasePlayer::lastSentTick", lastSentTick, PlayerTick*);
	FIELD("Assembly-CSharp::BasePlayer::userID", userID, uint64_t);
	bool isCached() {
		return map_contains_key(cachedBones, this->userID());
	}
	Vector3 midPoint() {
		if (!this->isCached())
			return Vector3::Zero();

		return this->bones()->r_foot->position.midPoint(this->bones()->l_foot->position) - Vector3(0.0f, 0.1f, 0.0f);
	}
	float GetTick() {
		return read(this + O::BasePlayer::lastSentTick, float);
	}
	bool is_visible() {
		if (!this->isCached())
			return false;

		if (cachedBones[this->userID()]->head->visible ||
			cachedBones[this->userID()]->neck->visible ||
			cachedBones[this->userID()]->spine4->visible ||
			cachedBones[this->userID()]->pelvis->visible ||
			cachedBones[this->userID()]->r_foot->visible ||
			cachedBones[this->userID()]->l_foot->visible ||
			cachedBones[this->userID()]->r_knee->visible ||
			cachedBones[this->userID()]->l_knee->visible) {

			return true;
		}

		return false;
	}

	FIELD("Assembly-CSharp::PlayerEyes::viewOffset", viewOffset, Vector3);

	static inline void(*ClientInput_)(BasePlayer*, uintptr_t) = nullptr;
	void ClientInput(uintptr_t unk) {
		return ClientInput_(this, unk);
	}
	void set_viewangles(const Vector2& VA) {
		DWORD64 Input = read(this + O::BasePlayer::input, DWORD64);
		write(Input + 0x3C, VA, Vector2);
	}
	Vector2 viewangles() {
		DWORD64 Input = read(this + O::BasePlayer::input, DWORD64);
		return read(Input + 0x3C, Vector2);
	}
	Vector3 newVelocity() {
		if (!this) return Vector3::Zero();
		static auto off = OFFSET("Assembly-CSharp::PlayerModel::newVelocity");
		return *reinterpret_cast<Vector3*>(this + off);
	}
	float GetHealth() {
		return this->health();
	}
	bool IsNpc() {
		DWORD64 PlayerModel = read(this + O::BasePlayer::playerModel, DWORD64);
		return read(PlayerModel + O::PlayerModel::IsNpck__BackingField, bool); //private bool <IsNpc>k__BackingField;
	}
	void InfinityJump() {
		INT64 Movement = read((const uintptr_t)this + O::BasePlayer::movement, UINT64);
		write(Movement + 0xc8, Vector3(0, 1000000, 0), Vector3);
		write(Movement + 0xc4, Vector3(9999999, 9999999, 9999999), Vector3);
	}
	void AntiSpread()
	{
		if (vars::weapons::no_spread)
		{
			DWORD64 Held = read(this + O::Item::heldEntity, DWORD64);
			write(Held + O::BaseProjectile::stancePenalty, 0.f, float);
			write(Held + O::BaseProjectile::aimconePenalty, 0.f, float);
			write(Held + O::BaseProjectile::aimCone, 0.f, float);
			write(Held + O::BaseProjectile::hipAimCone, 0.f, float);
			write(Held + O::BaseProjectile::aimconePenaltyPerShot, 0.f, float);
		}
	}
	ULONG64 mono_transform(int bone) {
		DWORD64 entity_model = read(this + 0x120, DWORD64);
		DWORD64 bone_dict = read(entity_model + 0x48, DWORD64);
		DWORD64 val = read(bone_dict + 0x20 + bone * 0x8, DWORD64);
		return val;
	}
	void SetFov(float val) {
		auto klass = read(vars::stor::gBase + CO::ConvarGraphics, DWORD64);
		auto static_fields = read(klass + 0xB8, DWORD64);
		write(static_fields + 0x18, val, float);
	}
	void PatchCamspeed() {
		auto klass = read(vars::stor::gBase + CO::Client, DWORD64);
		auto static_fields = read(klass + 0xB8, DWORD64);
		write(static_fields + 0x2C, 1.f, float);
		write(static_fields + 0x20, 1.f, float);
		write(static_fields + 0x34, 1.f, float);
		write(static_fields + 0x28, 1.f, float);
	}
	bool HasFlags(int Flg) {
		return (read(this + O::BasePlayer::playerFlags, int) & Flg);
	}
	typedef Vector3(__stdcall* Transform1)(UINT64);
	Vector3 GetPosition(ULONG_PTR pTransform) {
		if (!pTransform) return Vector3();
		Transform1 original = (Transform1)(vars::stor::gBase + O::UnityEngine_Transform::get_position);
		Vector3 res = original(pTransform);
		return res;
	}
	float GetTickTime() {
		return read(this + O::BasePlayer::lastSentTickTime, float);
	}
	uintptr_t get_player_model() {
		return *reinterpret_cast<uintptr_t*>((uintptr_t)this + O::BasePlayer::playerModel);
	}
	DWORD64 GetTransform(int bone) {
		DWORD64 player_model = read(this + O::BaseEntity::model, DWORD64);// public Model model;_public class BaseEntity : BaseNetworkable, IProvider, ILerpTarget, IPrefabPreProcess // TypeDefIndex: 8714
		DWORD64 boneTransforms = read(player_model + 0x48, DWORD64);//public Transform[] boneTransforms;
		DWORD64 BoneValue = read((boneTransforms + (0x20 + (bone * 0x8))), DWORD64);
		return BoneValue;
	}
	Vector3 GetPosition() {
		return GetPosition(GetTransform(Global::BoneToAim));
	}
	FIELD("Assembly-CSharp::Model::boneTransforms", boneTransforms, Array<Transform*>*);
	FIELD("Assembly-CSharp::Model::boneNames", boneNames, Array<il2cpp::String*>*);

	Vector3 get_bone_pos(BoneList bone) {
		uintptr_t player_model = read(this + 0x130, uintptr_t);// public Model model
		uintptr_t boneTransforms = read(player_model + 0x48, uintptr_t);//public Transform[] boneTransforms;
		Transform* transform = read(boneTransforms + 0x20 + bone * 0x8, Transform*);
		//const Transform* transform = read(BoneValue + 0x10, Transform*);

		if (!transform)
			return Vector3::Zero();
		//Vector3 pos = Vector3::Zero( );
		//static auto get_position = reinterpret_cast<void(__fastcall*)(Transform*, Vector3&)>(std::uint64_t(vars::stor::uBase + 0xDD2160));
		//get_position(transform, pos);
		return transform->position();
	}
	DWORD64 GetTeammateByPos(int Id) {
		DWORD64 ClientTeam = read(this + O::BasePlayer::clientTeam, DWORD64);
		DWORD64 members = read(ClientTeam + 0x30, DWORD64);
		DWORD64 List = read(members + 0x10, DWORD64);
		DWORD64 player = read(List + 0x20 + (Id * 0x8), DWORD64);
		return read(player + 0x20, DWORD64);
	}
	bool is_teammate(DWORD64 SteamID) {
		bool ret = false;
		for (int i = 0; i < 8; i++) {
			if (GetTeammateByPos(i) == SteamID) {
				ret = true;
				break;
			}
		}
		return ret;
	}

	bool IsMenu() {
		return reinterpret_cast<bool(*)()>(vars::stor::gBase)();
	}
	bool HasPlayerFlag(PlayerFlags flag) {
		if (!this) return false;

		return (PlayerFlags() & flag) == flag;
	}
	void add_modelstate_flag(ModelStateFlag flag) {
		DWORD64 mstate = read(this + O::BasePlayer::modelState, DWORD64);
		int flags = read(mstate + O::ModelState::flags, int);
		write(mstate + O::ModelState::flags, flags |= (int)flag, int);
	}
	void remove_modelstate_flag(ModelStateFlag flag) {
		DWORD64 mstate = read(this + O::BasePlayer::modelState, DWORD64);
		int flags = read(mstate + O::ModelState::flags, int);
		write(mstate + O::ModelState::flags, flags &= (int)flag, int);
	}
	bool has_modelstate_flag(ModelStateFlag flag) {
		DWORD64 mstate = read(this + O::BasePlayer::modelState, DWORD64);
		int flags = read(mstate + O::ModelState::flags, int);
		return flags & (int)flag;
	}
	float GetJumpHeight() {
		return reinterpret_cast<float(_fastcall*)(BasePlayer*)>(vars::stor::gBase + CO::GetJumpHeight)(this);
	}

	bool GetKeyState(Button b) {
		DWORD64 InputState = read(read(this + O::BasePlayer::input, DWORD64) + 0x20, DWORD64);
		DWORD64 Cur = read(InputState + 0x10, DWORD64);
		if (!Cur) return false;
		int btn = read(Cur + 0x14, int);
		return ((btn & (int)b) == (int)b);
	}
	Item* GetWeaponInfo(int Id) {
		DWORD64 Inventory = read(this + O::BasePlayer::inventory, DWORD64);
		DWORD64 Belt = read(Inventory + 0x28, DWORD64); // containerBelt
		DWORD64 ItemList = read(Belt + 0x38, DWORD64);// public List<Item> itemList;
		DWORD64 Items = read(ItemList + 0x10, DWORD64); //	public List<InventoryItem.Amount> items;
		return (Item*)read(Items + 0x20 + (Id * 0x8), DWORD64);
	}
	bool IsDucked() { // lad don't fancy calling functions in a non-game thread, eh, thy lad shall recreate it.
		if (!this) return false;

		if (this->movement() != nullptr)
			return this->movement()->Ducking() > 0.5f;

		return this->modelState() != nullptr && this->modelState()->flags() & 1;
	}
	List<Item*>* item_list_b() {
		DWORD64 Inventory = read(this + O::BasePlayer::inventory, DWORD64);
		DWORD64 Belt = read(Inventory + 0x28, DWORD64); // containerBelt
		return read(Belt + 0x38, List<Item*>*);// public List<Item> itemList;
	}
	Item* GetClothesInfo(int Id) {
		DWORD64 Inventory = read(this + O::BasePlayer::inventory, DWORD64);
		DWORD64 Belt = read(Inventory + 0x30, DWORD64); // containerWear
		DWORD64 ItemList = read(Belt + 0x38, DWORD64);// public List<Item> itemList;
		DWORD64 Items = read(ItemList + 0x10, DWORD64); //	public List<InventoryItem.Amount> items;
		return (Item*)read(Items + 0x20 + (Id * 0x8), DWORD64);
	}
	List<Item*>* item_list_w() {
		DWORD64 Inventory = read(this + O::BasePlayer::inventory, DWORD64);
		DWORD64 Belt = read(Inventory + 0x30, DWORD64); // containerWear
		return read(Belt + 0x38, List<Item*>*);// public List<Item> itemList;
	}
	BoneCache* bones() {
		return this->isCached() ? cachedBones[this->userID()] : new BoneCache();
	}
	Item* GetActiveWeapon() {
		int ActUID = read(this + O::BasePlayer::clActiveItem, int);
		if (!ActUID) return nullptr;
		Item* ActiveWeapon;
		for (int i = 0; i < 6; i++)
			if (ActUID == (ActiveWeapon = GetWeaponInfo(i))->uid())
				return ActiveWeapon;
		return nullptr;
	}
	void Chams(Color visibleColor, Color invisibleColor)
	{
	
	}
	template<typename T = HeldEntity>
	T* GetHeldEntity() {
		if (!this) return nullptr;

		auto inventory = this->inventory();
		if (!inventory) return nullptr;

		auto belt = inventory->containerBelt();
		if (!belt) return nullptr;

		auto item_list = belt->itemList();
		if (!item_list) return nullptr;

		for (int i = 0; i < item_list->size; i++) {
			auto item = reinterpret_cast<Item*>(item_list->get(i));
			if (!item) continue;

			if (item->uid() == this->clActiveItem())
				return item->heldEntity<T>();
		}

		return nullptr;
	}
	Item* GetHeldItem() {
		if (!this) return nullptr;

		auto inventory = this->inventory();
		if (!inventory) return nullptr;

		auto belt = inventory->containerBelt();
		if (!belt) return nullptr;

		auto item_list = belt->itemList();
		if (!item_list) return nullptr;

		for (int i = 0; i < item_list->size; i++) {
			auto item = reinterpret_cast<Item*>(item_list->get(i));
			if (!item) continue;

			if (item->uid() == this->clActiveItem())
				return item;
		}

		return nullptr;
	}
	FIELD("Assembly-CSharp::BasePlayer::lastSentTickTime", lastSentTickTime, float);
	FIELD("Assembly-CSharp::BasePlayer::clientTickInterval", clientTickInterval, float);
	FIELD("Assembly-CSharp::BasePlayer::inventory", inventory, PlayerInventory*);
	FIELD("Assembly-CSharp::BasePlayer::clActiveItem", clActiveItem, uint32_t);
	FIELD("Assembly-CSharp::BasePlayer::mounted", mounted, BaseMountable*);
	FIELD("Assembly-CSharp::BasePlayer::modelState", modelState, ModelState*);
	FIELD("Assembly-CSharp::BasePlayer::movement", movement, PlayerWalkMovement*);
	FIELD("Assembly-CSharp::BasePlayer::playerModel", playerModel, PlayerModel*);

	void FakeAdmin() {
		int Flags = read(this + O::BasePlayer::playerFlags, int);
		write(this + O::BasePlayer::playerFlags, (Flags |= 4), int);
	}
	void SetGravity(float val) {
		DWORD64 Movement = read(this + O::BasePlayer::movement, DWORD64);
		write(Movement + O::PlayerWalkMovement::gravityMultiplier, val, float);
	}
	Bone* find_mpv_bone() {
		if (!this)
			return nullptr;

		if (!this->isCached())
			return nullptr;

		auto bones = this->bones();

		if (bones->head->visible)
			return bones->head;

		if (bones->neck->visible)
			return bones->neck;

		if (bones->spine1->visible)
			return bones->spine1;

		if (bones->spine4->visible)
			return bones->spine4;

		if (bones->l_hand->visible)
			return bones->l_hand;

		if (bones->r_hand->visible)
			return bones->r_hand;

		if (bones->l_forearm->visible)
			return bones->l_forearm;

		if (bones->r_forearm->visible)
			return bones->r_forearm;

		if (bones->pelvis->visible)
			return bones->pelvis;

		if (bones->l_knee->visible)
			return bones->l_knee;

		if (bones->r_knee->visible)
			return bones->r_knee;

		if (bones->l_foot->visible)
			return bones->l_foot;

		if (bones->r_foot->visible)
			return bones->r_foot;

		return bones->head;
	}
	float GetMaxSpeed() {
		if (!this) return 0.f;
		static auto off = METHOD("Assembly-CSharp::BasePlayer::GetMaxSpeed(): Single");
		return reinterpret_cast<float(__fastcall*)(BasePlayer*)>(off)(this);
	}
	float MaxVelocity() {
		if (!this) return 0.f;

		if (this->mounted())
			return this->GetMaxSpeed() * 4;

		return this->GetMaxSpeed();
	}

};
class DDraw {
public:
	STATIC_FUNCTION("Assembly-CSharp::UnityEngine::DDraw::Line(Vector3,Vector3,Color,Single,Boolean,Boolean): Void", Line, void(Vector3, Vector3, Color, float, bool, bool));
	STATIC_FUNCTION("Assembly-CSharp::UnityEngine::DDraw::Sphere(Vector3,Single,Color,Single,Boolean): Void", Sphere, void(Vector3, float, Color, float, bool));
	STATIC_FUNCTION("Assembly-CSharp::UnityEngine::DDraw::Text(String,Vector3,Color,Single): Void", Text, void(il2cpp::String*, Vector3, Color, float));
	STATIC_FUNCTION("Assembly-CSharp::UnityEngine::DDraw::Arrow(Vector3,Vector3,Single,Color,Single): Void", Arrow, void(Vector3, Vector3, float, Color, float));
	STATIC_FUNCTION("Assembly-CSharp::UnityEngine::DDraw::Capsule(Vector3,Quaternion,Single,Single,Color,Single,Boolean): Void", Capsule, void(Vector3, Quaternion, float, float, Color, float, bool));
	STATIC_FUNCTION("Assembly-CSharp::UnityEngine::DDraw::Box(Vector3,Single,Color,Single,Boolean): Void", Box, void(Vector3, float, Color, float, bool));
	STATIC_FUNCTION("Assembly-CSharp::UnityEngine::DDraw::Get(): DDraw", Get, DDraw* ());
	/*static inline void(*OnGUI_)(DDraw*) = nullptr;
	void OnGUI() {
		return OnGUI_(this);
	}*/
};
class AssetBundle {
public:
	Array<il2cpp::String*>* GetAllAssetNames() {
		if (!this) return {};
		static auto off = METHOD("UnityEngine.AssetBundleModule::UnityEngine::AssetBundle::GetAllAssetNames(): String[]");
		return reinterpret_cast<Array<il2cpp::String*>*(*)(AssetBundle*)>(off)(this);
	}
	template<typename T = Object>
	T* LoadAsset(char* name, Type* type) {
		if (!this) return {};
		static auto off = METHOD("UnityEngine.AssetBundleModule::UnityEngine::AssetBundle::LoadAsset(String,Type): Object");
		return reinterpret_cast<T * (*)(AssetBundle*, il2cpp::String*, Type*)>(off)(this, il2cpp::String::New(name), type);
	}
	static AssetBundle* LoadFromFile(const char* path) {
		static auto off = METHOD("UnityEngine.AssetBundleModule::UnityEngine::AssetBundle::LoadFromFile(String): AssetBundle");
		return reinterpret_cast<AssetBundle * (*)(il2cpp::String*)>(off)(il2cpp::String::New(path));
	}
};
class BasePlayer;
class LocalPlayer {
public:
	static BasePlayer* Entity() {
		static auto clazz = CLASS("Assembly-CSharp::LocalPlayer");
		return *reinterpret_cast<BasePlayer**>(std::uint64_t(clazz->static_fields));
	}
};
class Mathf {
public:
	static float Abs(float a) {
		return reinterpret_cast<float(_fastcall*)(float)>(vars::stor::gBase + CO::MathfAbs)(a);
	}
	static float Max(float a, float b) {
		return reinterpret_cast<float(_fastcall*)(float, float)>(vars::stor::gBase + CO::MathfMax)(a, b);//UnityEngine_Mathf
	}
};
class BuildingBlock {
public:
	bool IsUpgradeBlocked() {
		typedef bool(__stdcall* IsUpgradeBlocked)(BuildingBlock*);
		return ((IsUpgradeBlocked)(vars::stor::gBase + CO::IsUpgradeBlocked))(this);
	}
	bool CanChangeToGrade(BuildingGrade i, BasePlayer* ply) {
		typedef bool(__stdcall* CanChangeToGrade)(BuildingBlock*, BuildingGrade, BasePlayer*);
		return ((CanChangeToGrade)(vars::stor::gBase + CO::CanChangeToGrade))(this, i, ply);
	}
	bool CanAffordUpgrade(BuildingGrade i, BasePlayer* ply) {
		typedef bool(__stdcall* CanAffordUpgrade)(BuildingBlock*, BuildingGrade, BasePlayer*);
		return ((CanAffordUpgrade)(vars::stor::gBase + CO::CanAffordUpgrade))(this, i, ply);
	}
	void UpgradeToGrade(BuildingGrade i, BasePlayer* ply) {
		typedef void(__stdcall* UpgradeToGrade)(BuildingBlock*, BuildingGrade, BasePlayer*);
		((UpgradeToGrade)(vars::stor::gBase + CO::UpgradeToGrade))(this, i, ply);
	}
};
class HitTest {
public:

	static HitTest* New()
	{
		HitTest* hitTest = il2cpp::il2cpp_object_new<HitTest*>(CLASS("Assembly-CSharp::HitTest"));

		return hitTest;
	}

	BaseEntity* HitEntity() { return read(this + O::HitTest::HitEntity, BaseEntity*); }
	void HitEntity(BaseEntity* en) { write(this + O::HitTest::HitEntity, en, BaseEntity*); }
	FIELD("Assembly-CSharp::HitTest::AttackRay", AttackRay, Ray);
	FIELD("Assembly-CSharp::HitTest::Radius", Radius, float);
	FIELD("Assembly-CSharp::HitTest::Forgiveness", Forgiveness, float);
	FIELD("Assembly-CSharp::HitTest::MaxDistance", MaxDistance, float);
	FIELD("Assembly-CSharp::HitTest::MultiHit", MultiHit, bool);
	FIELD("Assembly-CSharp::HitTest::BestHit", BestHit, bool);
	FIELD("Assembly-CSharp::HitTest::HitEntity", HitEntity1, BaseNetworkable*);
	FIELD("Assembly-CSharp::HitTest::DidHit", DidHit, bool);
	FIELD("Assembly-CSharp::HitTest::ignoreEntity", ignoreEntity, BaseEntity*);
	FIELD("Assembly-CSharp::HitTest::HitPoint", HitPoint, Vector3);
	FIELD("Assembly-CSharp::HitTest::HitNormal", HitNormal, Vector3);
	FIELD("Assembly-CSharp::HitTest::HitMaterial", HitMaterial, il2cpp::String*);
	FIELD("Assembly-CSharp::HitTest::HitDistance", HitDistance, float);
	FIELD("Assembly-CSharp::HitTest::HitTransform", HitTransform, Transform*);
	FIELD("Assembly-CSharp::HitTest::HitPart", HitPart, uint32_t);
	FIELD("Rust.Data::ProtoBuf::Attack::hitPositionWorld", hitPositionWorld, Vector3);

	Vector3 HitPointWorld() {
		if (!this) return Vector3();
		static auto off = METHOD("Assembly-CSharp::HitTest::HitPointWorld(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(HitTest*)>(off)(this);
	}

	Vector3 HitNormalWorld() {
		if (!this) return Vector3();
		static auto off = METHOD("Assembly-CSharp::HitTest::HitNormalWorld(): Vector3");
		return reinterpret_cast<Vector3(__fastcall*)(HitTest*)>(off)(this);
	}
	static inline Attack* (*BuildAttackMessage_)(HitTest*) = nullptr;
	Attack* BuildAttackMessage() {
		return BuildAttackMessage_(this);
	}
};
class AttackEntity : public BaseEntity {
public:
	void StartAttackCooldown(float cooldown)
	{
		if (!this) return;

		static auto off = METHOD("Assembly-CSharp::AttackEntity::StartAttackCooldown(Single): Void");

		return reinterpret_cast<void(__fastcall*)(AttackEntity*, float)>(off)(this, cooldown);
	}
	bool HasAttackCooldown()
	{
		if (!this) return false;

		static auto off = METHOD("Assembly-CSharp::AttackEntity::HasAttackCooldown(): Boolean");

		return reinterpret_cast<bool(__fastcall*)(AttackEntity*)>(off)(this);
	}
	FIELD("Assembly-CSharp::AttackEntity::repeatDelay", repeatDelay, float);
	FIELD("Assembly-CSharp::AttackEntity::lastTickTime", lastTickTime, float);
};
class BaseMelee : public AttackEntity {
public:
	//STATIC_FUNCTION("Assembly-CSharp::BaseMelee::ProcessAttack(HitTest): Void", ProcessAttack, void(HitTest*));
	void DoAttack(HitTest* test)
	{
		if (!this) return;

		static auto off = METHOD("Assembly-CSharp::BaseMelee::ProcessAttack(HitTest): Void");

		return reinterpret_cast<void(__fastcall*)(BaseMelee*, HitTest*)>(off)(this, test);
	}
	static inline void (*ProcessAttack_)(BaseMelee*, HitTest*) = nullptr;
	FIELD("Assembly-CSharp::BaseMelee::maxDistance", maxDistance, float);
	void ProcessAttack(HitTest* test) {
		return ProcessAttack_(this, test);
	}
};
class Projectile {
public:
	Vector3 initialVelocity() { return read(this + 0x18, Vector3); }
	float drag() { return read(this + 0x24, float); }
	float gravityModifier() { return read(this + 0x28, float); }
	float thickness() { return read(this + 0x2C, float); }
	float initialDistance() { return read(this + 0x30, float); }
	bool remainInWorld() { return read(this + 0x34, bool); }
	float stickProbability() { return read(this + 0x38, float); }
	float breakProbability() { return read(this + 0x3C, float); }
	float conditionLoss() { return read(this + 0x40, float); }
	float ricochetChance() { return read(this + 0x44, float); }
	float penetrationPower() { return read(this + 0x48, float); }
	uintptr_t damageProperties() { return read(this + 0x50, uintptr_t); }
	uintptr_t damageDistances() { return read(this + 0x58, uintptr_t); }
	uintptr_t damageMultipliers() { return read(this + 0x60, uintptr_t); }
	uintptr_t rendererToScale() { return read(this + 0x70, uintptr_t); }
	uintptr_t firstPersonRenderer() { return read(this + 0x78, uintptr_t); }
	bool createDecals() { return read(this + 0x80, bool); }
	bool doDefaultHitEffects() { return read(this + 0x81, bool); }
	uintptr_t flybySound() { return read(this + 0x88, uintptr_t); }
	float flybySoundDistance() { return read(this + 0x90, float); }
	uintptr_t closeFlybySound() { return read(this + 0x98, uintptr_t); }
	float closeFlybyDistance() { return read(this + 0xA0, float); }
	float tumbleSpeed() { return read(this + 0xA4, float); }
	Vector3 tumbleAxis() { return read(this + 0xA8, Vector3); }
	Vector3 swimScale() { return read(this + 0xB4, Vector3); }
	Vector3 swimSpeed() { return read(this + 0xC0, Vector3); }
	BasePlayer* owner() { return (BasePlayer*)read(this + 0xD0, uintptr_t); }
	uintptr_t sourceWeaponPrefab() { return read(this + 0xD8, uintptr_t); }
	uintptr_t sourceProjectilePrefab() { return read(this + 0xE0, uintptr_t); }
	uintptr_t mod() { return read(this + 0xe8, uintptr_t); }
	int projectileID() { return read(this + 0xF0, int); }
	uint32_t seed() { return read(this + 0xF4, uint32_t); }
	bool clientsideEffect() { return read(this + 0xF8, bool); }
	bool clientsideAttack() { return read(this + 0xF9, bool); }
	float integrity() { return read(this + 0xFC, float); }
	//float maxDistance() { return read(this + 0x100, float); }
	uintptr_t modifier() { return read(this + 0x104, uintptr_t); }
	bool invisible() { return read(this + 0x114, bool); }
	Vector3 currentVelocity() { return read(this + 0x118, Vector3); }
	Vector3 currentPosition() { return read(this + 0x124, Vector3); }
	float traveledDistance() { return read(this + 0x130, float); }
	float traveledTime() { return read(this + 0x134, float); }
	float launchTime() { return read(this + 0x138, float); }
	Vector3 sentPosition() { return read(this + 0x13C, Vector3); }
	Vector3 previousPosition() { return read(this + 0x148, Vector3); }
	Vector3 previousVelocity() { return read(this + 0x154, Vector3); }
	float previousTraveledTime() { return read(this + 0x160, float); }
	bool isRicochet() { return read(this + 0x164, bool); }
	bool isRetiring() { return read(this + 0x165, bool); }
	bool flybyPlayed() { return read(this + 0x166, bool); }
	bool wasFacingPlayer() { return read(this + 0x167, bool); }
	uintptr_t flybyPlane() { return read(this + 0x168, uintptr_t); }
	Ray flybyRay() { return read(this + 0x178, Ray); }
	uintptr_t cleanupAction() { return read(this + 0x190, uintptr_t); }
	HitTest* hitTest() { return read(this + 0x198, HitTest*); }
	float swimRandom() { return read(this + 0x1A0, float); }

	void initialVelocity(Vector3 a) { write(this + 0x18, a, Vector3); }
	void drag(float a) { write(this + 0x24, a, float); }
	void gravityModifier(float a) { write(this + 0x28, a, float); }
	void thickness(float a) { write(this + 0x2C, a, float); }
	void initialDistance(float a) { write(this + 0x30, a, float); }
	void remainInWorld(bool a) { write(this + 0x34, a, bool); }
	void stickProbability(float a) { write(this + 0x38, a, float); }
	void breakProbability(float a) { write(this + 0x3C, a, float); }
	void conditionLoss(float a) { write(this + 0x40, a, float); }
	void ricochetChance(float a) { write(this + 0x44, a, float); }
	void penetrationPower(float a) { write(this + 0x48, a, float); }
	void damageProperties(uintptr_t a) { write(this + 0x50, a, uintptr_t); }
	void damageDistances(uintptr_t a) { write(this + 0x58, a, uintptr_t); }
	void damageMultipliers(uintptr_t a) { write(this + 0x60, a, uintptr_t); }
	void rendererToScale(uintptr_t a) { write(this + 0x70, a, uintptr_t); }
	void firstPersonRenderer(uintptr_t a) { write(this + 0x78, a, uintptr_t); }
	void createDecals(bool a) { write(this + 0x80, a, bool); }
	void doDefaultHitEffects(bool a) { write(this + 0x81, a, bool); }
	void flybySound(uintptr_t a) { write(this + 0x88, a, uintptr_t); }
	void flybySoundDistance(float a) { write(this + 0x90, a, float); }
	void closeFlybySound(uintptr_t a) { write(this + 0x98, a, uintptr_t); }
	void closeFlybyDistance(float a) { write(this + 0xA0, a, float); }
	void tumbleSpeed(float a) { write(this + 0xA4, a, float); }
	void tumbleAxis(Vector3 a) { write(this + 0xA8, a, Vector3); }
	void swimScale(Vector3 a) { write(this + 0xB4, a, Vector3); }
	void swimSpeed(Vector3 a) { write(this + 0xC0, a, Vector3); }
	void owner(uintptr_t a) { write(this + 0xD0, a, uintptr_t); }
	void sourceWeaponPrefab(uintptr_t a) { write(this + 0xD8, a, uintptr_t); }
	void sourceProjectilePrefab(uintptr_t a) { write(this + 0xE0, a, uintptr_t); }
	void mod(uintptr_t a) { write(this + 0xE8, a, uintptr_t); }
	void projectileID(uint32_t a) { write(this + 0xF0, a, uint32_t); }
	void seed(uint32_t a) { write(this + 0xF4, a, uint32_t); }
	void clientsideEffect(bool a) { write(this + 0xF8, a, bool); }
	void clientsideAttack(bool a) { write(this + 0xF9, a, bool); }
	void integrity(float a) { write(this + 0xFC, a, float); }
	//void maxDistance(float a) { write(this + 0x100, a, float); }
	void modifier(uintptr_t a) { write(this + 0x104, a, uintptr_t); }
	void invisible(bool a) { write(this + 0x114, a, bool); }
	void currentVelocity(Vector3 a) { write(this + 0x118, a, Vector3); }
	void currentPosition(Vector3 a) { write(this + 0x124, a, Vector3); }
	void traveledDistance(float a) { write(this + 0x130, a, float); }
	void traveledTime(float a) { write(this + 0x134, a, float); }
	void launchTime(float a) { write(this + 0x138, a, float); }
	void sentPosition(Vector3 a) { write(this + 0x13C, a, Vector3); }
	void previousPosition(Vector3 a) { write(this + 0x148, a, Vector3); }
	void previousVelocity(Vector3 a) { write(this + 0x154, a, Vector3); }
	void previousTraveledTime(float a) { write(this + 0x160, a, float); }
	void isRicochet(bool a) { write(this + 0x164, a, bool); }
	void isRetiring(bool a) { write(this + 0x165, a, bool); }
	void flybyPlayed(bool a) { write(this + 0x166, a, bool); }
	void wasFacingPlayer(bool a) { write(this + 0x167, a, bool); }
	void flybyPlane(uintptr_t a) { write(this + 0x168, a, uintptr_t); }
	void flybyRay(Ray a) { write(this + 0x178, a, Ray); }
	void cleanupAction(uintptr_t a) { write(this + 0x190, a, uintptr_t); }
	void hitTest(uintptr_t a) { write(this + 0x198, a, uintptr_t); }
	void swimRandom(float a) { write(this + 0x1A0, a, float); }

	bool DoHit(HitTest* test, Vector3 point, Vector3 normal) {
		static auto off = METHOD("Assembly-CSharp::Projectile::DoHit(HitTest,Vector3,Vector3): Boolean");
		return reinterpret_cast<bool(__fastcall*)(Projectile*, HitTest*, Vector3, Vector3)>(off)(this, test, point, normal);
	}
	bool isAuthoritative() {
		if (!this) return false;
		static auto off = METHOD("Assembly-CSharp::Projectile::get_isAuthoritative(): Boolean");
		return reinterpret_cast<bool(__fastcall*)(Projectile*)>(off)(this);
	}
};
class GamePhysics {
public:
	enum class QueryTriggerInteraction {
		UseGlobal = 0,
		Ignore = 1,
		Collide = 2,
	};

	STATIC_FUNCTION("Assembly-CSharp::GamePhysics::LineOfSight(Vector3,Vector3,Int32,Single,BaseEntity): Boolean", LineOfSight, bool(Vector3, Vector3, int, float, BaseEntity));
};
namespace utils {
	bool w2s(Vector3 world, Vector2& screen) {
		const auto matrix = il2cpp::unity::getViewMatrix().transpose();

		const Vector3 translation = { matrix[3][0], matrix[3][1], matrix[3][2] };
		const Vector3 up = { matrix[1][0], matrix[1][1], matrix[1][2] };
		const Vector3 right = { matrix[0][0], matrix[0][1], matrix[0][2] };

		const auto w = translation.dot_product(world) + matrix[3][3];

		if (w < 0.1f)
			return false;

		const auto x = right.dot_product(world) + matrix[0][3];
		const auto y = up.dot_product(world) + matrix[1][3];

		screen =
		{
			(vars::stuff::ScreenWidth / 2) * (1.f + x / w),
			(vars::stuff::ScreenHeight / 2) * (1.f - y / w)
		};

		return true;
	}
	bool OOF(BasePlayer* ply) {
		Vector3 pos = ply->get_bone_pos(head);
		Vector2 screen;

		if (!utils::w2s(pos, screen))
			return true;

		float num = Math::Distance_2D(screen_center, screen);
		return num > 1000.f;
	}
	Vector3 GetEntityPosition(std::uint64_t entity) {
		if (!entity) return Vector3::Zero();

		uintptr_t plyVis = read(entity + 0x8, uintptr_t);
		if (!plyVis) return Vector3::Zero();

		uintptr_t visualState = read(plyVis + 0x38, uintptr_t);
		if (!visualState) return Vector3::Zero();

		Vector3 ret = read(visualState + 0x90, Vector3);
		return ret;
	}
	Vector3 ClosestPoint(BasePlayer* player, Vector3 vec) {
		typedef Vector3(__stdcall* CPoint)(BasePlayer*, Vector3);
		Vector3 result = ((CPoint)(vars::stor::gBase + CO::ClosestPoint))(player, vec);
		return result;
	}
	bool LineOfSight(Vector3 a, Vector3 b) {
		BaseEntity ab;
		int mask = vars::weapons::penetrate ? 10551296 : 1503731969; // projectile los, flyhack mask, intellisense reload
		bool result = GamePhysics::LineOfSight(a, b, mask, 0.f, ab) && GamePhysics::LineOfSight(b, a, mask, 0.f, ab);
		return result;
	}

	//uintptr_t ShaderFind(Str name) {
	//	typedef uintptr_t(__stdcall* ShaderFind)(Str);
	//	uintptr_t result = ((ShaderFind)(vars::stor::gBase + CO::ShaderFind))(name);
	//	return result;
	//}
	void ServerRPC(DWORD64 ent, Str func) {
		typedef void(__stdcall* Pick)(DWORD64, Str);
		return ((Pick)(vars::stor::gBase + CO::ServerRPC))(ent, func);
	}
	class StringPool {
	public:
		static uint32_t Get(const char* str) {
			static auto off = METHOD("Assembly-CSharp::StringPool::Get(String): UInt32");
			return reinterpret_cast<uint32_t(__fastcall*)(il2cpp::String*)>(off)(il2cpp::String::New(str));
		}

		static il2cpp::String* Get(uint32_t i) {
			static auto off = METHOD("Assembly-CSharp::StringPool::Get(UInt32): String");
			return reinterpret_cast<il2cpp::String * (__fastcall*)(uint32_t)>(off)(i);
		}
	};
}
// need 2 keep here 4 now || TO-DO move up
class Model : public Component {
public:
	FIELD("Assembly-CSharp::Model::boneTransforms", boneTransforms, Array<Transform*>*);
	//FIELD("Assembly-CSharp::BoneDictionary::hashDict", hashDict, List<int, Transform*>*);
	FIELD("Assembly-CSharp::Model::boneNames", boneNames, Array<il2cpp::String*>*);

	Bone* resolve(uint32_t hash) {
		if (!this) return nullptr;

		if (!this->boneNames() || !this->boneTransforms()) return nullptr;

		auto bone_names = this->boneNames();
		auto bone_transforms = this->boneTransforms();

		for (int i = 0; i < bone_names->size(); i++) {
			auto bone_name = bone_names->get(i);
			auto bone_transform = bone_transforms->get(i);
			if (!bone_name || !bone_transform) continue;

			if (RUNTIME_CRC32_W(bone_name->buffer) == hash) {
				Vector3 ret = LocalPlayer::Entity()->transform()->position() + LocalPlayer::Entity()->transform()->up() * (PlayerEyes::EyeOffset().y + LocalPlayer::Entity()->eyes()->viewOffset().y);
				return new Bone(bone_transform->position(), utils::LineOfSight(bone_transform->position(), ret), bone_transform);
			}
		}

		return nullptr;
	}
};