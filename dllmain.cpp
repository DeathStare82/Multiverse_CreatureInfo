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

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    static _bool_ plugin_On = 0;

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        if (!plugin_On)
        {
            plugin_On = 1;

            // 1. Era 연결을 가장 먼저 수행하여 환경을 초기화합니다.
            Era::ConnectEra(hModule, "EraPlugins.Multiverse_CreatureInfo");

            // 2. 그 후 패처 인스턴스를 생성하고 훅을 등록합니다.
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
        break; // 빠져 있던 break 추가

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}