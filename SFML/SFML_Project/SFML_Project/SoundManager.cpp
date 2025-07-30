#include "SoundManager.h"

SoundManager soundManager;  // 전역 SoundManager 객체 생성

bool SoundManager::LoadBGM(const std::string& filePath)
{
    if (!music.openFromFile(filePath))
    {
        std::cerr << "[SoundManager] BGM 파일 로드 실패: " << filePath << std::endl;
        return false;
    }

    std::cout << "[SoundManager] BGM 파일 로드 성공: " << filePath << std::endl;
    return true;
}

void SoundManager::PlayBGM(bool loop)
{
    if (isMuted)
        return;

    music.setLoop(loop);
    music.play();
    isPlaying = true;

    std::cout << "[SoundManager] BGM 재생 시작" << std::endl;
}

void SoundManager::StopBGM()
{
    music.stop();
    isPlaying = false;

    std::cout << "[SoundManager] BGM 중지" << std::endl;
}

void SoundManager::ToggleMute()
{
    isMuted = !isMuted;

    if (isMuted)
    {
        music.setVolume(0.f);
        std::cout << "[SoundManager] 음소거 활성화" << std::endl;
    }
    else
    {
        music.setVolume(80.f); // 볼륨 원상복귀
        std::cout << "[SoundManager] 음소거 해제" << std::endl;
    }
}

bool SoundManager::IsPlaying() const
{
    return isPlaying;
}

bool SoundManager::IsMuted() const
{
    return isMuted;
}

bool SoundManager::LoadAttackSound(const std::string& filePath)
{
    if (!attackBuffer.loadFromFile(filePath))
    {
        std::cerr << "[SoundManager] 공격 효과음 로드 실패: " << filePath << std::endl;
        return false;
    }

    attackSound.setBuffer(attackBuffer);
    attackSound.setVolume(40.f);
    return true;
}

void SoundManager::PlayAttackSound()
{
    if (!isMuted)
        attackSound.play();
}
