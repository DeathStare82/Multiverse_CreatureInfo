#include "header.h"

void HandleCreatureDlg(H3Dlg *dlg)
{
    if (!dlg)
        return;

    // 사기(212) 및 행운(213) 텍스트 아이템에 마우스 오버 힌트 부여
    if (auto *moraleText = dlg->GetText(212))
    {
        moraleText->SetHints("사기 확률 설명: 기본 수치에 따른 추가 행동 확률이 적용됩니다.", h3_NullString, true);
    }

    if (auto *luckText = dlg->GetText(213))
    {
        luckText->SetHints("행운 확률 설명: 전투 시 일정 확률로 2배 피해를 입힙니다.", h3_NullString, true);
    }

    // 여분발사횟수(104) 힌트 부여
    if (auto *extraShotsText = dlg->GetText(104))
    {
        extraShotsText->SetHints("여분 탄환 수: 남은 사격 횟수와 추가 보급된 탄환입니다.", h3_NullString, true);
    }
}