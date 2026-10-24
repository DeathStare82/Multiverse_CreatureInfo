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

void CreatureDlgHandler::HideDefaultBattleSpellItems()
{
    if (!dlg)
        return;

    for (int id = DLG_NATIVE_SPELL_FIRST_ID; id <= DLG_NATIVE_SPELL_LAST_ID; ++id)
        if (auto *item = dlg->GetH3DlgItem(id))
            item->HideDeactivate();

    // 다이얼로그 아이템 힌트 설정 (함수 내부 배치)
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
} // <- 함수의 닫는 괄호가 여기에 정상적으로 위치해야 합니다.