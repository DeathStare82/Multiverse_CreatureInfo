#include "pch.h"
#include "CreatureDlgHooks.h"
#include "PluginSettings.h"

// MonPreview.cpp 등 다른 파일에서 참조하는 전역 변수를 반드시 정의해야 링커 에러가 안 납니다.
Patcher *globalPatcher = nullptr;
PatcherInstance *_PI = nullptr;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}