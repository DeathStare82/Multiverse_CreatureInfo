// dllmain.cpp : 최소 로드 테스트용
#include "pch.h"
#include "CreatureDlgHooks.h"
#include "PluginSettings.h"

// 다른 파일(MonPreview.cpp 등)에서 공유해서 쓰는 변수이므로 반드시 정의되어 있어야 합니다.
Patcher *globalPatcher = nullptr;
PatcherInstance *_PI = nullptr;

using namespace h3;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    static bool initialized = false;

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        if (!initialized)
        {
            initialized = true;
            // Era 프레임워크 연결만 안전하게 수행하여 DLL 로드 여부를 테스트합니다.
            Era::ConnectEra(hModule, "EraPlugins.Multiverse_CreatureInfo");
        }
        break;

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}