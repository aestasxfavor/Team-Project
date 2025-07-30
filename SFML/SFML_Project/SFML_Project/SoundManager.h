#pragma once
#include "Util.h"

class SoundManager
{
private:
    sf::SoundBuffer attackBuffer;
    sf::Sound attackSound;

    sf::Music music;

    bool isMuted = false;
    bool isPlaying = false;

    float bgmVolume = 100.f;        // 배경음 볼륨
	float sfxVolume = 40.f;         // 효과음 볼륨

public:
    // BGM 파일 로드 및 재생
    bool LoadBGM(const std::string& filePath);

    // 재생, 중지, 음소거
    void PlayBGM(bool loop = true);
    void StopBGM();
    void ToggleMute();

    // 상태 확인
    bool IsPlaying() const;
    bool IsMuted() const;

    // 효과음 로드 함수
    bool LoadAttackSound(const std::string& filePath);

    // 효과음 재생 함수
    void PlayAttackSound();

   
};

extern SoundManager soundManager;