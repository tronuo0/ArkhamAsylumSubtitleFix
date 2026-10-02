#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <unknwn.h>
#include <cwchar>
// Original minimal proxy. Loads only this draft's named ASI.
static INIT_ONCE once=INIT_ONCE_STATIC_INIT;
static HMODULE original;
static BOOL CALLBACK Initialize(PINIT_ONCE,PVOID,PVOID*) {
    wchar_t path[MAX_PATH]; UINT n=GetSystemDirectoryW(path,MAX_PATH);
    if(n && n<MAX_PATH-13) { wcscat_s(path,L"\\dinput8.dll"); original=LoadLibraryW(path); }
    DWORD length=GetModuleFileNameW(nullptr,path,MAX_PATH);
    if(!length || length>=MAX_PATH) return TRUE;
    wchar_t* slash=wcsrchr(path,L'\\'); if(!slash) return TRUE;
    wcscpy_s(slash+1,MAX_PATH-(slash+1-path),L"ArkhamSubtitleScale.asi");
    HMODULE plugin=LoadLibraryW(path);
    if(plugin) {
        auto init=(BOOL (__cdecl*)())GetProcAddress(plugin,"InitializeSubtitleScale");
        if(init) init();
    } else OutputDebugStringW(L"Arkham Subtitle Scale: ASI could not be loaded.\n");
    return TRUE;
}
extern "C" HRESULT WINAPI ProxyDirectInput8Create(HINSTANCE instance,DWORD version,REFIID iid,LPVOID* out,LPUNKNOWN outer) {
    InitOnceExecuteOnce(&once,Initialize,nullptr,nullptr);
    using Fn=HRESULT (WINAPI*)(HINSTANCE,DWORD,REFIID,LPVOID*,LPUNKNOWN);
    auto fn=original?(Fn)GetProcAddress(original,"DirectInput8Create"):nullptr;
    if(!fn) { if(out) *out=nullptr; return E_FAIL; }
    return fn(instance,version,iid,out,outer);
}
BOOL WINAPI DllMain(HINSTANCE instance,DWORD reason,LPVOID) {
    if(reason==DLL_PROCESS_ATTACH) DisableThreadLibraryCalls(instance);
    return TRUE;
}
