#include "Game.h"

void Game::Reset()
{
    isPaused = false;
    isResetting = false;
    currentWave = 0;
    killCount = 0;
    selectedStatChoices.clear();
}
