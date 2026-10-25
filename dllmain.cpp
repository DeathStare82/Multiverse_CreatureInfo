// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
#include "CreatureDlgHooks.h"
#include "PluginSettings.h"

Patcher *globalPatcher = nullptr;
PatcherInstance *_PI = nullptr;

using namespace h3;

_LHF_(HooksInit)
{
    try {
        preview::MonPreview::Get();
        Dlg_CreatureInfo_HooksInit(_PI);
        Dlg_CreatureSpellInfo_HooksInit(_PI);
        creatureInfo::RegisterPluginSettingsButton();
    } catch (...) {}

    return EXEC_DEFAULT;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    static bool initialized = false;

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        if (!initialized)
        {
            initialized = true;
            try
            {
                // Era 연결 시도
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
            catch (...)
            {
                // 초기화 중 예외가 발생해도 크래시로 인한 DLL 로드 실패를 방지합니다.
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