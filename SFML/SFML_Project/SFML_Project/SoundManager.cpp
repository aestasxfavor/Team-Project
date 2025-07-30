#include "SoundManager.h"

// 전역 SoundManager 객체 생성
SoundManager soundManager;

// ==========================================================
// [BGM 관련]
// ==========================================================

// BGM 파일 로드
// - 지정된 경로의 음악 파일을 로드함
bool SoundManager::LoadBGM(const string& filePath)
{
    if (!music.openFromFile(filePath))
    {
        cerr << "[SoundManager] BGM 파일 로드 실패: " << filePath << endl;
        return false;
    }

    cout << "[SoundManager] BGM 파일 로드 성공: " << filePath << endl;
    return true;
}

// BGM 재생
// - loop 값에 따라 반복 여부 설정 (기본: true)
void SoundManager::PlayBGM(bool loop)
{
    if (isMuted)
        return;

    music.setLoop(loop);
    music.play();
    isPlaying = true;

    cout << "[SoundManager] BGM 재생 시작" << endl;
}

// BGM 정지
// - 음악 재생을 멈추고 상태값도 false로 변경
void SoundManager::StopBGM()
{
    music.stop();
    isPlaying = false;

    cout << "[SoundManager] BGM 중지" << endl;
}

// BGM 음소거 토글
// - 음소거 시 볼륨 0, 해제 시 기존 볼륨(예: 80)로 복귀
void SoundManager::ToggleMute()
{
    isMuted = !isMuted;

    if (isMuted)
    {
        music.setVolume(0.f);
        cout << "[SoundManager] 음소거 활성화" << endl;
    }
    else
    {
        music.setVolume(80.f); // 볼륨 복구 (필요 시 bgmVolume 변수 활용 가능)
        cout << "[SoundManager] 음소거 해제" << endl;
    }
}

// ==========================================================
// [상태 확인 함수]
// ==========================================================

// 현재 BGM이 재생 중인지 여부 반환
bool SoundManager::IsPlaying() const
{
    return isPlaying;
}

// 현재 음소거 상태인지 여부 반환
bool SoundManager::IsMuted() const
{
    return isMuted;
}

// ==========================================================
// [효과음 관련]
// ==========================================================

// 공격 효과음 파일 로드
bool SoundManager::LoadAttackSound(const string& filePath)
{
    if (!attackBuffer.loadFromFile(filePath))
    {
        cerr << "[SoundManager] 공격 효과음 로드 실패: " << filePath << endl;
        return false;
    }

    attackSound.setBuffer(attackBuffer);
    attackSound.setVolume(40.f); // sfxVolume 사용 가능
    return true;
}

// 공격 효과음 재생
// - 음소거 상태가 아닐 경우만 재생
void SoundManager::PlayAttackSound()
{
    if (!isMuted)
        attackSound.play();
}
