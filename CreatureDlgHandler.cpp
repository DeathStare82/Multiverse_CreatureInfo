#include "pch.h"
#include "CreatureDlgHandler.h"
#include "CreatureDlgHooks.h"
#include "CreatureDlgLayout.h"
#include "PluginSettings.h"
#include "CreatureSpellEffects.h"

#include <algorithm>
#include <string>
#include <cstdio>

using namespace h3;
using namespace creatureInfo;

// 1. 생성자 (필수)
CreatureDlgHandler::CreatureDlgHandler(H3CreatureInfoDlg *dlg, H3CombatCreature *stack, H3Army *army,
                                     int armySlotIndex, const H3Hero *hero, int playerColor)
    : dlg(dlg), stack(stack), army(army), armySlotIndex(armySlotIndex), hero(hero), playerColor(playerColor)
{
    // 초기화 로직
}

// 2. 소멸자 (필수)
CreatureDlgHandler::~CreatureDlgHandler()
{
    // 정리 로직
}

// 3. ScrollTo 함수 (필수)
void CreatureDlgHandler::ScrollTo(int position)
{
    // 스크롤 구현 로직
}

// 4. BuildDescriptionArea 함수 (필수)
int CreatureDlgHandler::BuildDescriptionArea()
{
    return 0;
}

// 5. 기존 기본 다이얼로그 처리 함수 내에 힌트 코드 추가
void CreatureDlgHandler::HideDefaultBattleSpellItems()
{
    if (!dlg)
        return;

    for (int id = DLG_NATIVE_SPELL_FIRST_ID; id <= DLG_NATIVE_SPELL_LAST_ID; ++id)
        if (auto *item = dlg->GetH3DlgItem(id))
            item->HideDeactivate();

    // 마우스 오버 힌트 부여
    if (auto *moraleText = dlg->GetText(212))
    {
        moraleText->SetHints("사기 확률 설명: 기본 수치에 따른 추가 행동 확률이 적용됩니다.", h3_NullString, true);
    }

    if (auto *luckText = dlg->GetText(213))
    {
        luckText->SetHints("행운 확률 설명: 전투 시 일정 확률로 2배 피해를 입힙니다.", h3_NullString, true);
    }

    if (auto *extraShotsText = dlg->GetText(104))
    {
        extraShotsText->SetHints("여분 탄환 수: 남은 사격 횟수와 추가 보급된 탄환입니다.", h3_NullString, true);
    }
}