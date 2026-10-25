// dllmain.cpp : 최소 로드 테스트용
#include "pch.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        // 우선 내부 초기화 코드를 모두 배제하고 DLL이 정상 로드되는지 테스트합니다.
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}