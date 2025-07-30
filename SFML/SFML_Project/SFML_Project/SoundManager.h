#pragma once
#include "Util.h"
// Todo. 배경음악이랑 인겜 내 사운드 넣기
// 사운드를 언제 중단하고 언제 실행되는지 조건 생각해서 넣기 
// 효과음은 넣는게 어려울거같은데 어쩌지 배경음악이라도 넣어야하나 적 생성하고 공격하는게 난잡해서 죽일때마다 효과음 넣으면 정신없을거같은데 배경만 넣어야할거같기도 



class SoundManager
{
private:
 /*   sf::SoundBuffer bgmBuffer;
    sf::Sound bgmSound;*/

    sf::Music music;

    bool isMuted = false;
    bool isPlaying = false;

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

   
};
extern SoundManager soundManager;