#include <map>
#include "lazyimp.h"
template<typename T1, typename T2> bool map_contains_key(T1 map, T2 key) {
	return map.count(key) > 0;
}

namespace il2cpp {
	template<typename T>
	class list {
	public:
		T get(uint32_t idx)
		{
			const auto internal_list = reinterpret_cast<uintptr_t>(this + 0x20);
			return *reinterpret_cast<T*>(internal_list + idx * sizeof(T));
		}

		T get_value(uint32_t idx)
		{
			const auto list = *reinterpret_cast<uintptr_t*>((uintptr_t)this + 0x10);
			const auto internal_list = list + 0x20;
			return *reinterpret_cast<T*>(internal_list + idx * sizeof(T));
		}

		T operator[](uint32_t idx) { return get(idx); }

		const uint32_t get_size() { return *reinterpret_cast<uint32_t*>((uintptr_t)this + 0x18); }

		template<typename F>
		void for_each(const F callback)
		{
			for (auto i = 0; i < get_size(); i++) {
				auto object = this->get(i);
				if (!object)
					continue;
				callback(object, i);
			}
		}
	};
	auto gameAssembly = GetModuleHandleA(xorstr("GameAssembly.dll"));
	static std::map<uint32_t, uint64_t> offsets = std::map<uint32_t, uint64_t>();
#define ProcAddr(func) GetProcAddress(gameAssembly, func)

	template<typename T, typename... Args>
	inline T call(const char* func, Args... args) {
		return reinterpret_cast<T(__fastcall*)(Args...)>(ProcAddr(func))(args...);
	}

	class String {
	public:
		char pad_0000[0x10];
		int len;
		wchar_t buffer[0];

		static String* New(const char* str) {
			__try {
				return call<String*, const char*>(xorstr("il2cpp_string_new"), str);
			}
			__except (1) { return 0; }
		}
	};
	class Il2CppType {
	public:
		char* name() {
			return call<char*, Il2CppType*>(xorstr("il2cpp_type_get_name"), this);
		}
	};

	class Il2CppMethod {
	public:
		uint32_t paramCount() {
			return call<uint32_t, Il2CppMethod*>(xorstr("il2cpp_method_get_param_count"), this);
		}

		Il2CppType* retType() {
			return call<Il2CppType*, Il2CppMethod*>(xorstr("il2cpp_method_get_return_type"), this);
		}

		Il2CppType* getParam(uint32_t idx) {
			return call<Il2CppType*, Il2CppMethod*, uint32_t>(xorstr("il2cpp_method_get_param"), this, idx);
		}

		char* name() {
			return call<char*, Il2CppMethod*>(xorstr("il2cpp_method_get_name"), this);
		}
	};

	uint64_t il2cpp_resolve_icall(const char* str) {
		return call<uint64_t, const char*>(xorstr("il2cpp_resolve_icall"), str);
	}
	uint64_t il2cpp_object_new1(uint64_t klass) {
		return call<uint64_t, uint64_t>(xorstr("il2cpp_object_new"), klass);
	}

	class Il2CppField {
	public:
		char* name() {
			return call<char*, Il2CppField*>(xorstr("il2cpp_field_get_name"), this);
		}

		uint32_t offset() {
			return call<uint32_t, Il2CppField*>(xorstr("il2cpp_field_get_offset"), this);
		}
	};
	class CBounds {
	public:
		Vector3 center;
		Vector3 extents;
	};
	struct box_bounds {
		float left, right, top, bottom;

		bool empty() {
			if (this->left == 0 && this->right == 0 && this->top == 0 && this->bottom == 0)
				return true;

			if (this->left == FLT_MAX || this->right == FLT_MIN || this->top == FLT_MAX || this->bottom == FLT_MIN)
				return true;

			return false;
		}
		static box_bounds nulls() {
			return { 0, 0, 0, 0 };
		}
	};
	class Il2CppClass {
	public:
		class Il2CppImage* image; //0x0000
		char pad_0008[8]; //0x0008
		char* name; //0x0010
		char* namespaze; //0x0018
		char pad_0020[152]; //0x0020
		void* static_fields; //0x00B8

		Il2CppMethod* methods(void* iter) {
			return call<Il2CppMethod*, Il2CppClass*, void*>(xorstr("il2cpp_class_get_methods"), this, iter);
		}

		Il2CppField* fields(void* iter) {
			return call<Il2CppField*, Il2CppClass*, void*>(xorstr("il2cpp_class_get_fields"), this, iter);
		}
	}; //Size: 0x00C0

	class Il2CppImage {
	public:
		char* assemblyName; //0x0000
		char* name; //0x0008

		uint64_t classcount() {
			return call<uint64_t, Il2CppImage*>(xorstr("il2cpp_image_get_class_count"), this);
		}

		Il2CppClass* get_class(uint64_t idx) {
			return call<Il2CppClass*, Il2CppImage*, uint64_t>(xorstr("il2cpp_image_get_class"), this, idx);
		}
	}; //Size: 0x0010

	template<typename T = uint64_t>
	T il2cpp_array_new(Il2CppClass* klazz, uint64_t length) {
		return call<T, Il2CppClass*, uint64_t>(xorstr("il2cpp_array_new"), klazz, length);
	}

	class Il2CppAssembly {
	public:
		uint64_t buffer;
	};
	template<typename T>
	T il2cpp_object_new(Il2CppClass* klazz)
	{
		return call<T, Il2CppClass*>(xorstr("il2cpp_object_new"), klazz);
	}
	class Il2CppDomain {
	public:
		size_t assemblyCount() {
			size_t size = 0;
			auto assemblies = call<Il2CppAssembly**, Il2CppDomain*, void*>(xorstr("il2cpp_domain_get_assemblies"), this, &size);

			return size;

		}

		Il2CppAssembly** assemblies() {
			size_t size = 0;

			return call<Il2CppAssembly**, Il2CppDomain*, void*>(xorstr("il2cpp_domain_get_assemblies"), this, &size);
		}
	};

	Il2CppDomain* il2cpp_domain_get() {
		return call<Il2CppDomain*>(xorstr("il2cpp_domain_get"));
	}

	void* il2cpp_runtime_invoke(void* method_ptr, void* obj, void** param, void** exc) {
		return call<void*, void*, void*, void**, void**>(xorstr("il2cpp_runtime_invoke"), method_ptr, obj, param, exc);
	}

	void* il2cpp_object_get_virtual_method(void* obj, void* method) {
		return call<void*, void*, void*>(xorstr("il2cpp_object_get_virtual_method"), obj, method);
	}
	
	Il2CppClass* klass(uint32_t path) {
		if (map_contains_key(offsets, path))
			return reinterpret_cast<Il2CppClass*>(offsets[path]);

		Il2CppDomain* domain = il2cpp_domain_get();
		Il2CppAssembly** assemblies = domain->assemblies();

		for (int i = 0; i < domain->assemblyCount(); i++) {
			Il2CppImage* image = *reinterpret_cast<Il2CppImage**>(*reinterpret_cast<uint64_t*>(std::uint64_t(assemblies) + (0x8 * i)));
			for (int c = 0; c < image->classcount(); c++) {
				std::string temp(image->assemblyName);
				temp.erase(temp.find(xorstr(".dll")), 4);

				Il2CppClass* klass = image->get_class(c);
				char* name = klass->name;
				char* ns = klass->namespaze;
				if (std::string(ns).empty())
					temp = temp + xorstr("::") + name;
				else
					temp = temp + xorstr("::") + ns + xorstr("::") + name;

				if (path == RUNTIME_CRC32(temp.c_str())) {
					uint64_t ptr = std::uint64_t(klass);

					offsets.insert(std::make_pair(path, ptr));
					return klass;
				}
			}
		}

		return nullptr;
	}
	uint64_t method(uint32_t path) {
		if (map_contains_key(offsets, path))
			return offsets[path];

		Il2CppDomain* domain = il2cpp_domain_get();
		Il2CppAssembly** assemblies = domain->assemblies();

		for (int i = 0; i < domain->assemblyCount(); i++) {
			Il2CppImage* image = *reinterpret_cast<Il2CppImage**>(*reinterpret_cast<uint64_t*>(std::uint64_t(assemblies) + (0x8 * i)));
			for (int c = 0; c < image->classcount(); c++) {
				std::string temp(image->assemblyName);
				temp.erase(temp.find(xorstr(".dll")), 4);

				Il2CppClass* klass = image->get_class(c);
				if (!klass) continue;

				char* name = klass->name;
				char* ns = klass->namespaze;
				if (std::string(ns).empty())
					temp = temp + xorstr("::") + name;
				else
					temp = temp + xorstr("::") + ns + xorstr("::") + name;

				Il2CppMethod* mthd;
				void* iter = NULL;
				while (mthd = klass->methods(&iter)) {
					if (!mthd) continue;

					std::string temp2(temp + xorstr("::") + mthd->name());

					if (mthd->paramCount() > 0) {
						temp2 = temp2 + xorstr("(");
						for (int p = 0; p < mthd->paramCount(); p++) {
							std::string t(mthd->getParam(p)->name());
							t = t.substr(t.find(xorstr(".")) + 1);
							temp2 = temp2 + t + xorstr(",");
						}
						std::string t(mthd->retType()->name());
						temp2 = temp2.substr(0, temp2.size() - 1);
						temp2 = temp2 + xorstr("): ") + t.substr(t.find(".") + 1);
					}
					else {
						std::string t(mthd->retType()->name());
						temp2 = temp2 + xorstr("(): ") + t.substr(t.find(".") + 1);
					}

					if (RUNTIME_CRC32(temp2.c_str()) == path) {
						offsets.insert(std::make_pair(path, std::uint64_t(mthd)));

						return std::uint64_t(mthd);
					}
				}
			}
		}

		return 0;
	}
	uint64_t field(uint32_t path) {
		if (map_contains_key(offsets, path))
			return std::uint32_t(offsets[path]);

		Il2CppDomain* domain = il2cpp_domain_get();
		Il2CppAssembly** assemblies = domain->assemblies();

		for (int i = 0; i < domain->assemblyCount(); i++) {
			Il2CppImage* image = *reinterpret_cast<Il2CppImage**>(*reinterpret_cast<uint64_t*>(std::uint64_t(assemblies) + (0x8 * i)));
			for (int c = 0; c < image->classcount(); c++) {
				std::string temp(image->assemblyName);
				temp.erase(temp.find(xorstr(".dll")), 4);

				Il2CppClass* klass = image->get_class(c);
				char* name = klass->name;
				char* ns = klass->namespaze;
				if (std::string(ns).empty())
					temp = temp + xorstr("::") + name;
				else
					temp = temp + xorstr("::") + ns + xorstr("::") + name;

				Il2CppField* field;
				void* iter = NULL;
				while (field = klass->fields(&iter)) {
					if (!field) continue;

					std::string t(temp + xorstr("::") + field->name());
					if (RUNTIME_CRC32(t.c_str()) == path) {
						uint32_t off = field->offset();
						offsets.insert(std::make_pair(path, off));

						return off;
					}
				}
			}
		}

		return 0;
	}
	void init_classes() {
		Il2CppDomain* domain = il2cpp_domain_get();
		Il2CppAssembly** assemblies = domain->assemblies();

		for (int i = 0; i < domain->assemblyCount(); i++) {
			Il2CppImage* image = *reinterpret_cast<Il2CppImage**>(*reinterpret_cast<uint64_t*>(std::uint64_t(assemblies) + (0x8 * i)));
			for (int c = 0; c < image->classcount(); c++) {
				std::string temp(image->assemblyName);
				temp.erase(temp.find(xorstr(".dll")), 4);

				Il2CppClass* klass = image->get_class(c);
				char* name = klass->name;
				char* ns = klass->namespaze;
				if (std::string(ns).empty())
					temp = temp + xorstr("::") + name;
				else
					temp = temp + xorstr("::") + ns + xorstr("::") + name;

				uint64_t ptr = std::uint64_t(klass);

				offsets.insert(std::make_pair(RUNTIME_CRC32(temp.c_str()), ptr));
			}
		}
	}
	void init_methods() {
		Il2CppDomain* domain = il2cpp_domain_get();
		Il2CppAssembly** assemblies = domain->assemblies();

		for (int i = 0; i < domain->assemblyCount(); i++) {
			Il2CppImage* image = *reinterpret_cast<Il2CppImage**>(*reinterpret_cast<uint64_t*>(std::uint64_t(assemblies) + (0x8 * i)));
			for (int c = 0; c < image->classcount(); c++) {
				std::string temp(image->assemblyName);
				temp.erase(temp.find(xorstr(".dll")), 4);

				Il2CppClass* klass = image->get_class(c);
				if (!klass) continue;

				char* name = klass->name;
				char* ns = klass->namespaze;
				if (std::string(ns).empty())
					temp = temp + xorstr("::") + name;
				else
					temp = temp + xorstr("::") + ns + xorstr("::") + name;

				Il2CppMethod* mthd;
				void* iter = NULL;
				while (mthd = klass->methods(&iter)) {
					if (!mthd) continue;

					std::string temp2(temp + xorstr("::") + mthd->name());

					if (mthd->paramCount() > 0) {
						temp2 = temp2 + xorstr("(");
						for (int p = 0; p < mthd->paramCount(); p++) {
							std::string t(mthd->getParam(p)->name());
							t = t.substr(t.find(xorstr(".")) + 1);
							temp2 = temp2 + t + xorstr(",");
						}
						std::string t(mthd->retType()->name());
						temp2 = temp2.substr(0, temp2.size() - 1);
						temp2 = temp2 + xorstr("): ") + t.substr(t.find(".") + 1);
					}
					else {
						std::string t(mthd->retType()->name());
						temp2 = temp2 + xorstr("(): ") + t.substr(t.find(".") + 1);
					}

					offsets.insert(std::make_pair(RUNTIME_CRC32(temp2.c_str()), std::uint64_t(mthd)));
				}
			}
		}
	}
	void init_fields() {
		Il2CppDomain* domain = il2cpp_domain_get();
		Il2CppAssembly** assemblies = domain->assemblies();

		for (int i = 0; i < domain->assemblyCount(); i++) {
			Il2CppImage* image = *reinterpret_cast<Il2CppImage**>(*reinterpret_cast<uint64_t*>(std::uint64_t(assemblies) + (0x8 * i)));
			for (int c = 0; c < image->classcount(); c++) {
				std::string temp(image->assemblyName);
				temp.erase(temp.find(xorstr(".dll")), 4);

				Il2CppClass* klass = image->get_class(c);
				char* name = klass->name;
				char* ns = klass->namespaze;
				if (std::string(ns).empty())
					temp = temp + xorstr("::") + name;
				else
					temp = temp + xorstr("::") + ns + xorstr("::") + name;

				Il2CppField* field;
				void* iter = NULL;
				while (field = klass->fields(&iter)) {
					if (!field) continue;

					std::string t(temp + xorstr("::") + field->name());
					uint32_t off = field->offset();
					offsets.insert(std::make_pair(RUNTIME_CRC32(t.c_str()), off));
				}
			}
		}
	}
	class default_t {
	public:
		template<typename T>
		operator T() const { return T(); }
	};

	default_t const defaultt = default_t();
#define METHOD(path) *reinterpret_cast<uint64_t*>(il2cpp::method(STATIC_CRC32(path)))
#define CLASS(path) il2cpp::klass(STATIC_CRC32(path))
#define ASSIGN_HOOK(method_path,hook) hook = reinterpret_cast<decltype(hook)>(METHOD(method_path))
#define OFFSET(path) il2cpp::field(STATIC_CRC32(path))
#define NP(type) type nonptr = il2cpp::defaultt; if(!this) return nonptr;
#define FIELD(field_path,name,type) type& name() { \
		NP(type) \
		static auto off = OFFSET(field_path); \
		return *reinterpret_cast<type*>(this + off); }
	char* memstr(char* haystack, const char* needle, int size) {
		char* p;
		char needlesize = strlen(needle);
		for (p = haystack; p <= (haystack - needlesize + size); p++) {
			if (memcmp(p, needle, needlesize) == 0)
				return p; /* found */
		}
		return NULL;
	}
	namespace unity {
		// getting camera using header scanning (epic)
		uint64_t get_camera() {
			const auto base = (uint64_t)GetModuleHandleA(xorstr("UnityPlayer.dll"));
			if (!base)
				return 0;
			const auto dos_header = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
			const auto nt_header = reinterpret_cast<IMAGE_NT_HEADERS64*>(base + dos_header->e_lfanew);
			uint64_t data_base;
			uint64_t data_size;
			for (int i = 0;;) {
				const auto section = reinterpret_cast<IMAGE_SECTION_HEADER*>(
					base + dos_header->e_lfanew + // nt_header base 
					sizeof(IMAGE_NT_HEADERS64) +  // start of section headers
					(i * sizeof(IMAGE_SECTION_HEADER))); // section header at our index
				if (strcmp((char*)section->Name, xorstr(".data")) == 0) {
					data_base = section->VirtualAddress + base;
					data_size = section->SizeOfRawData;
					break;
				}
				i++;
				if (i >= nt_header->FileHeader.NumberOfSections) {
					Beep(500, 1000);
					return 0;
				}
			}
			uint64_t camera_table = 0;
			const auto camera_string = memstr((char*)data_base, xorstr("AllCameras"), data_size);
			for (auto walker = (uint64_t*)camera_string; walker > 0; walker -= 1) {
				if (*walker > 0x100000 && *walker < 0xF00000000000000) {
					// [[[[unityplayer.dll + ctable offset]]] + 0x30] = Camera
					camera_table = *walker;
					break;
				}
			}
			if (camera_table)
				return camera_table;
			Beep(500, 1000);
			return 0;
		}
		Matrix getViewMatrix() {
			static auto camera_list = get_camera();
			if (!camera_list) return Matrix();

			auto camera_table = *reinterpret_cast<uint64_t*>(camera_list);
			auto cam = *reinterpret_cast<uint64_t*>(camera_table);

			return *reinterpret_cast<Matrix*>(cam + 0x2E4);
		}
	}
	
	static void init() {
		init_classes( );
		init_methods( );
		init_fields( );
	}
}