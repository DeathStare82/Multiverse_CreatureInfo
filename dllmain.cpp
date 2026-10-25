// dllmain.cpp : Определяет точку входа для приложения DLL.
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

// 델파이 기반 Era 프레임워크가 진입점을 정확히 찾을 수 있도록 C 스타일로 외부에 노출합니다.
extern "C" __declspec(dllexport) BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    static bool initialized = false;

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        if (!initialized)
        {
            initialized = true;
            Era::ConnectEra(hModule, "EraPlugins.Multiverse_CreatureInfo");
            
            globalPatcher = GetPatcher();
            if (globalPatcher)
            {
                _PI = globalPatcher->CreateInstance("EraPlugins.Multiverse_CreatureInfo");
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