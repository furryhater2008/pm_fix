enum QueryTriggerInteraction {
	UseGlobal = 0,
	Ignore = 1,
	Collide = 2,
};
enum class KeyCode : int {
	None = 0,
	Backspace = 8,
	Delete = 127,
	Tab = 9,
	Clear = 12,
	Return = 13,
	Pause = 19,
	Escapee = 27,
	Space = 32,
	Keypad0 = 256,
	Keypad1 = 257,
	Keypad2 = 258,
	Keypad3 = 259,
	Keypad4 = 260,
	Keypad5 = 261,
	Keypad6 = 262,
	Keypad7 = 263,
	Keypad8 = 264,
	Keypad9 = 265,
	KeypadPeriod = 266,
	KeypadDivide = 267,
	KeypadMultiply = 268,
	KeypadMinus = 269,
	KeypadPlus = 270,
	KeypadEnter = 271,
	KeypadEquals = 272,
	UpArrow = 273,
	DownArrow = 274,
	RightArrow = 275,
	LeftArrow = 276,
	Insert = 277,
	Home = 278,
	End = 279,
	PageUp = 280,
	PageDown = 281,
	F1 = 282,
	F2 = 283,
	F3 = 284,
	F4 = 285,
	F5 = 286,
	F6 = 287,
	F7 = 288,
	F8 = 289,
	F9 = 290,
	F10 = 291,
	F11 = 292,
	F12 = 293,
	F13 = 294,
	F14 = 295,
	F15 = 296,
	Alpha0 = 48,
	Alpha1 = 49,
	Alpha2 = 50,
	Alpha3 = 51,
	Alpha4 = 52,
	Alpha5 = 53,
	Alpha6 = 54,
	Alpha7 = 55,
	Alpha8 = 56,
	Alpha9 = 57,
	Exclaim = 33,
	DoubleQuote = 34,
	Hash = 35,
	Dollar = 36,
	Percent = 37,
	Ampersand = 38,
	Quote = 39,
	LeftParen = 40,
	RightParen = 41,
	Asterisk = 42,
	Plus = 43,
	Comma = 44,
	Minus = 45,
	Period = 46,
	Slash = 47,
	Colon = 58,
	Semicolon = 59,
	Less = 60,
	Equals = 61,
	Greater = 62,
	Question = 63,
	At = 64,
	LeftBracket = 91,
	Backslash = 92,
	RightBracket = 93,
	Caret = 94,
	Underscore = 95,
	BackQuote = 96,
	A = 97,
	B = 98,
	C = 99,
	D = 100,
	E = 101,
	F = 102,
	G = 103,
	H = 104,
	I = 105,
	J = 106,
	K = 107,
	L = 108,
	M = 109,
	N = 110,
	O = 111,
	P = 112,
	Q = 113,
	R = 114,
	S = 115,
	T = 116,
	U = 117,
	V = 118,
	W = 119,
	X = 120,
	Y = 121,
	Z = 122,
	LeftCurlyBracket = 123,
	Pipe = 124,
	RightCurlyBracket = 125,
	Tilde = 126,
	Numlock = 300,
	CapsLock = 301,
	ScrollLock = 302,
	RightShift = 303,
	LeftShift = 304,
	RightControl = 305,
	LeftControl = 306,
	RightAlt = 307,
	LeftAlt = 308,
	LeftCommand = 310,
	LeftApple = 310,
	LeftWindows = 311,
	RightCommand = 309,
	RightApple = 309,
	RightWindows = 312,
	AltGr = 313,
	Help = 315,
	Print = 316,
	SysReq = 317,
	Break = 318,
	Menu = 319,
	Mouse0 = 323,
	Mouse1 = 324,
	Mouse2 = 325,
	Mouse3 = 326,
	Mouse4 = 327,
	Mouse5 = 328,
	Mouse6 = 329
};
enum class BuildingGrade {
	None = -1,
	Twigs,
	Wood,
	Stone,
	Metal,
	TopTier,
	Count
};
enum class Signal {
	Attack,
	Alt_Attack,
	DryFire,
	Reload,
	Deploy,
	Flinch_Head,
	Flinch_Chest,
	Flinch_Stomach,
	Flinch_RearHead,
	Flinch_RearTorso,
	Throw,
	Relax,
	Gesture,
	PhysImpact,
	Eat,
	Startled
};
enum MountPoses : int {
	Chair,
	Driving,
	Horseback,
	HeliUnarmed,
	HeliArmed,
	HandMotorBoat,
	MotorBoatPassenger,
	SitGeneric,
	SitRaft,
	StandDrive,
	SitShootingGeneric,
	SitMinicopter_Pilot,
	SitMinicopter_Passenger,
	Standing = 128
};
enum BoneList : int {
	l_hip = 1,
	l_knee,
	l_foot,
	l_toe,
	l_ankle_scale,
	pelvis,
	penis,
	GenitalCensor,
	GenitalCensor_LOD0,
	Inner_LOD0,
	GenitalCensor_LOD1,
	GenitalCensor_LOD2,
	r_hip,
	r_knee,
	r_foot,
	r_toe,
	r_ankle_scale,
	spine1,
	spine1_scale,
	spine2,
	spine3,
	spine4,
	l_clavicle,
	l_upperarm,
	l_forearm,
	l_hand,
	l_index1,
	l_index2,
	l_index3,
	l_little1,
	l_little2,
	l_little3,
	l_middle1,
	l_middle2,
	l_middle3,
	l_prop,
	l_ring1,
	l_ring2,
	l_ring3,
	l_thumb1,
	l_thumb2,
	l_thumb3,
	IKtarget_righthand_min,
	IKtarget_righthand_max,
	l_ulna,
	neck,
	head,
	jaw,
	eyeTranform,
	l_eye,
	l_Eyelid,
	r_eye,
	r_Eyelid,
	r_clavicle,
	r_upperarm,
	r_forearm,
	r_hand,
	r_index1,
	r_index2,
	r_index3,
	r_little1,
	r_little2,
	r_little3,
	r_middle1,
	r_middle2,
	r_middle3,
	r_prop,
	r_ring1,
	r_ring2,
	r_ring3,
	r_thumb1,
	r_thumb2,
	r_thumb3,
	IKtarget_lefthand_min,
	IKtarget_lefthand_max,
	r_ulna,
	l_breast,
	r_breast,
	BoobCensor,
	BreastCensor_LOD0,
	BreastCensor_LOD1,
	BreastCensor_LOD2,
	collision,
	displacement
};
enum class CursorLockMode {
	None = 0,
	Locked = 1,
	Confined = 2
};
enum PlayerFlags : int {
	Unused1 = 1,
	Unused2 = 2,
	IsAdmin = 4,
	ReceivingSnapshot = 8,
	Sleeping = 16,
	Spectating = 32,
	Wounded = 64,
	IsDeveloper = 128,
	Connected = 256,
	ThirdPersonViewmode = 1024,
	EyesViewmode = 2048,
	ChatMute = 4096,
	NoSprint = 8192,
	Aiming = 16384,
	DisplaySash = 32768,
	Relaxed = 65536,
	SafeZone = 131072,
	ServerFall = 262144,
	Workbench1 = 1048576,
	Workbench2 = 2097152,
	Workbench3 = 4194304,
};
enum class Layer : uint32_t {
	Default = 0,
	TransparentFX = 1,
	Ignore_Raycast = 2,
	Reserved1 = 3,
	Water = 4,
	UI = 5,
	Reserved2 = 6,
	Reserved3 = 7,
	Deployed = 8,
	Ragdoll = 9,
	Invisible = 10,
	AI = 11,
	PlayerMovement = 12,
	Vehicle_Detailed = 13,
	Game_Trace = 14,
	Vehicle_World = 15,
	World = 16,
	Player_Server = 17,
	Trigger = 18,
	Player_Model_Rendering = 19,
	Physics_Projectile = 20,
	Construction = 21,
	Construction_Socket = 22,
	Terrain = 23,
	Transparent = 24,
	Clutter = 25,
	Debris = 26,
	Vehicle_Large = 27,
	Prevent_Movement = 28,
	Prevent_Building = 29,
	Tree = 30,
	Unused2 = 31
};
enum LayerMasks : int {
	Default = 1,
	TransparentFX = 2,
	Ignore_Raycast = 4,
	Reserved1 = 8,
	Water = 16,
	UI = 32,
	Reserved2 = 64,
	Reserved3 = 128,
	Deployed = 256,
	Ragdoll = 512,
	Invisible = 1024,
	AI = 2048,
	Player_Movement = 4096,
	Vehicle_Detailed = 8192,
	Game_Trace = 16384,
	Vehicle_World = 32768,
	World = 65536,
	Player_Server = 131072,
	Trigger = 262144,
	Player_Model_Rendering = 524288,
	Physics_Projectile = 1048576,
	Construction = 2097152,
	Construction_Socket = 4194304,
	Terrain = 8388608,
	Transparent = 16777216,
	Clutter = 33554432,
	Debris = 67108864,
	Vehicle_Large = 134217728,
	Prevent_Movement = 268435456,
	Prevent_Building = 536870912,
	Tree = 1073741824,
	//Unused2 = -2147483648,
};
enum Lifestate {
	Alive = 0,
	Dead = 1
};
enum class ModelStateFlag : uint32_t {
	Ducked = 1,
	Jumped = 2,
	OnGround = 4,
	Sleeping = 8,
	Sprinting = 16,
	OnLadder = 32,
	Flying = 64,
	Aiming = 128,
	Prone = 256,
	Mounted = 512,
	Relaxed = 1024,
	OnPhone = 2048,
};
enum class EventType : int {
	Zero = 0,
	Repaint = 7
};
enum class Button : int {
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
	FIRE_THIRD = 134217728
};
class BufferList {
public:
	char pad_0000[ 0x10 ];
	int32_t size;
	char pad_0014[ 0x4 ];
	void* buffer;
};
class ListDictionary {
public:
	char pad_0000[ 0x20 ];
	class BufferList* keys;
	class BufferList* vals;
};
template<typename T>
class List {
public:
	uint32_t size;
	T get(uint32_t idx) {
		const auto internal_list = reinterpret_cast<uintptr_t>(this + 0x20);
		return *reinterpret_cast<T*>(internal_list + idx * sizeof(T));
	}
	T get_value(uint32_t idx) {
		const auto list = *reinterpret_cast<uintptr_t*>((uintptr_t)this + 0x10);
		const auto internal_list = list + 0x20;
		return *reinterpret_cast<T*>(internal_list + idx * sizeof(T));
	}
	T operator[](uint32_t idx) { return get(idx); }
	const uint32_t get_size( ) { return *reinterpret_cast<uint32_t*>((uintptr_t)this + 0x18); }
	template<typename F>
	void for_each(const F callback) {
		for (auto i = 0; i < get_size( ); i++) {
			auto object = this->get(i);
			if (!object)
				continue;
			callback(object, i);
		}
	}
};
typedef struct _UncStr {
	char stub[ 0x10 ];
	int len;
	wchar_t str[ 1 ];
} *pUncStr;
struct Explosion {
public:
	std::string name;
	float timeSince;
	Vector3 position;
};
class BulletTracer {
public:
	Vector3 start;
	Vector3 end;
	BulletTracer( ) {
		this->start = Vector3::Zero( );
		this->end = Vector3::Zero( );
	}
	BulletTracer(Vector3 st, Vector3 en) {
		this->start = st;
		this->end = en;
	}
};
class CBounds {
public:
	Vector3 center;
	Vector3 extents;
};

class Rect {
public:
	float x; // 0x10
	float y; // 0x14
	float wid; // 0x18
	float hei; // 0x1C
	Rect(float x, float y/*top left*/, float x_rightsize, float y_downsize) { this->x = x; this->y = y; wid = x_rightsize; hei = y_downsize; }
	Rect( ) { this->x = 0; this->y = 0; wid = 0; hei = 0; }
	bool Contains(Vector2 point) { return point.x >= x && point.x < (x + wid) && point.y >= y && point.y < (y + hei); }
};
class Color {
public:
	float r;
	float g;
	float b;
	float a;
	Color(float rr, float gg, float bb, float aa) {
		r = rr;
		g = gg;
		b = bb;
		a = aa;
	}
};
struct Ray {
public:
	Vector3 m_Origin;
	Vector3 m_Direction;

	Ray() {
		this->m_Origin = Vector3(0, 0, 0);
		this->m_Direction = Vector3(0, 0, 0);
	}

	Ray(Vector3 origin, Vector3 direction) {
		this->m_Origin = origin;
		this->m_Direction = direction;
	}

	Vector3 ClosestPoint(Vector3 pos) {
		return this->m_Origin + this->m_Direction * (pos - this->m_Origin).dot_product(this->m_Direction);
	}
};
template<typename T = void*>
class Array {
public:
	uint32_t size( ) {
		if (!this) return 0;

		return *reinterpret_cast<uint32_t*>(this + 0x18);
	}

	T get(int idx) {
		if (!this) return T{};

		return *reinterpret_cast<T*>(this + (0x20 + (idx * 0x8)));
	}
	T gett(int idx) {
		if (!this) return T{};

		return *reinterpret_cast<T*>(this + 0x20 + idx * 0x8);
	}
};



#define MAX_STRING_LEN 64
class Str {
	char zpad[ 0x10 ];
public:
	int size;
	wchar_t str[ MAX_STRING_LEN + 1 ];
	Str(const wchar_t* st) {
		size = min(wcslen((wchar_t*)st), MAX_STRING_LEN);
		for (int i = 0; i < size; i++) {
			str[ i ] = st[ i ];
		}
		str[ size ] = 0;
	}
};
struct TraceResult {
	float hitDist;
	Vector3 hitPosition;
	Vector3 outVelocity;
	float hitTime;

	TraceResult( ) {
		this->hitDist = 0.f;
		this->hitPosition = Vector3::Zero( );
		this->outVelocity = Vector3::Zero( );
		this->hitTime = 0.f;
	}
};