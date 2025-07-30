#pragma once
#include "Util.h"

// SoundManager 클래스
// - BGM 및 효과음(SFX)을 관리하는 사운드 전담 클래스
// - BGM 재생, 정지, 음소거 / 효과음 재생 등을 처리함

class SoundManager
{
private:
    // ================== [효과음 관련] ==================
    sf::SoundBuffer attackBuffer;     // 공격 효과음 버퍼
    sf::Sound attackSound;            // 공격 효과음 객체

    // ================== [배경음악 관련] ==================
    sf::Music music;                  // BGM 음악 객체

    // ================== [상태 및 볼륨 설정] ==================
    bool isMuted = false;             // 음소거 여부
    bool isPlaying = false;           // 재생 중 여부

    float bgmVolume = 100.f;          // BGM 볼륨 (0~100)
    float sfxVolume = 40.f;           // 효과음 볼륨 (0~100)

public:
    // ================== [BGM 제어] ==================

    // BGM 파일 로드 (성공 시 true 반환)
    bool LoadBGM(const string& filePath);

    // BGM 재생 (기본은 루프 재생)
    void PlayBGM(bool loop = true);

    // BGM 정지
    void StopBGM();

    // BGM 음소거/해제 토글
    void ToggleMute();

    // ================== [효과음 제어] ==================

    // 공격 효과음 로드 (성공 시 true 반환)
    bool LoadAttackSound(const string& filePath);

    // 공격 효과음 재생
    void PlayAttackSound();

    // ================== [상태 확인 함수] ==================

    // BGM 재생 여부 확인
    bool IsPlaying() const;

    // 음소거 상태 확인
    bool IsMuted() const;
};

// 외부 전역 인스턴스 선언 (cpp 파일에 정의 필요)
extern SoundManager soundManager;
