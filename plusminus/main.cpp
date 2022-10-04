#include "includes.h"
//#pragma comment(lib, "ntdll.lib")

void main_thread(HINSTANCE hModule) {
	Start( );
	hk__( );

	/*AllocConsole();
	freopen("CONOUT$", "w", stdout);*/
}
bool DllMain(HMODULE hMod, std::uint32_t call_reason, void*) {
	if (call_reason != DLL_PROCESS_ATTACH)
		return false;

#ifdef disable
#else
	const auto handle = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(main_thread), hMod, 0, nullptr);
	if (handle != NULL)
		CloseHandle(handle);
#endif

	return true;
}