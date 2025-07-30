#pragma once
#include "Util.h"
#include "Player.h"
#include "StageManager.h"
#include "SceneManager.h"
#include "UIManager.h"


class Game
{
private:
    bool isPaused = false;                 // 일시정지 상태
    bool isResetting = false;              // 리셋 상태
    int currentWave = 0;                   // 현재 웨이브
    int killCount = 0;                     // 총 처치 수

    vector<PlayerStats::StatOption> selectedStatChoices;  // 선택된 능력치 옵션들

public:
    // 상태 관리
    void SetPaused(bool paused) { isPaused = paused; }
    bool IsPaused() const { return isPaused; }

    void SetResetting(bool resetting) { isResetting = resetting; }
    bool IsResetting() const { return isResetting; }

    void Reset(); // 상태 전체 리셋

    // 웨이브 관련
    void SetWave(int wave) { currentWave = wave; }
    int GetWave() const { return currentWave; }
    void NextWave() { ++currentWave; }

    // 킬 수 관리
    void AddKill() { ++killCount; }
    void ResetKillCount() { killCount = 0; }
    int GetKillCount() const { return killCount; }

    // 스탯 선택 관련
    void SetSelectedChoices(const vector<PlayerStats::StatOption>& choices) { selectedStatChoices = choices; }
    const vector<PlayerStats::StatOption>& GetSelectedChoices() const { return selectedStatChoices; }
    void ClearSelectedChoices() { selectedStatChoices.clear(); }
};
