// dllmain.cpp : 데몬의 원본 식별자와 최신 빌드 호환 적용
#include "pch.h"
#include "CreatureDlgHooks.h"
#include "PluginSettings.h"

Patcher *globalPatcher = nullptr;
PatcherInstance *_PI = nullptr;

using namespace h3;

_LHF_(HooksInit)
{
    preview::MonPreview::Get();
    Dlg_CreatureInfo_HooksInit(_PI);
    Dlg_CreatureSpellInfo_HooksInit(_PI);
    creatureInfo::RegisterPluginSettingsButton();
    return EXEC_DEFAULT;
}

// C 스타일 링크 및 내보내기를 적용하여 Era 로더가 진입점을 완벽하게 인식하도록 합니다.
extern "C" __declspec(dllexport) BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    static bool plugin_On = false;

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        if (!plugin_On)
        {
            plugin_On = true;

            // Multiverse 모드가 인식하는 데몬의 원본 플러그인 식별자 사용
            Era::ConnectEra(hModule, "EraPlugins.CreatureInformation.daemon_n");
            
            globalPatcher = GetPatcher();
            if (globalPatcher)
            {
                _PI = globalPatcher->CreateInstance("EraPlugins.CreatureInformation.daemon_n");
                if (_PI)
                {
                    _PI->WriteLoHook(0x4EEAF2, HooksInit);
                }
            }
        }
        break;

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}