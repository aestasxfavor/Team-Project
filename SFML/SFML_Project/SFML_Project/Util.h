#pragma once

// ==========================================================
// [SFML 관련 라이브러리]
// ==========================================================
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// ==========================================================
// [기본 시스템 헤더]
// ==========================================================
#include <iostream>
#include <Windows.h>     // 윈도우 전용 기능 (ex. Sleep 등)
#include <conio.h>       // 콘솔 입력 (_kbhit, _getch 등)
#include <time.h>        // 시간 관련 (srand, time)
#include <chrono>        // 고정밀도 시간 측정
#include <cstdlib>       // rand(), srand()
#include <cmath>         // 수학 함수 (ex. sin 함수로 애니메이션)
#include <functional>    // 함수 객체, 람다 표현식
#include <utility>       // std::pair 등
#include <iomanip>       // 입출력 포맷 조절
#include <sstream>       // 문자열 스트림 (숫자 → 문자열 변환 등)

// ==========================================================
// [표준 자료구조 컨테이너]
// ==========================================================
#include <string>
#include <vector>
#include <set>
#include <list>
#include <queue>
#include <deque>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <ranges>        // C++20 범위 기반 알고리즘

// ==========================================================
// [기본 네임스페이스 지정]
// ==========================================================
// 전체 using namespace std는 피하고 필요한 것만 제한적으로 사용

using namespace std;

using std::cout;
using std::cin;
using std::endl;
using std::string;

// ==========================================================
// [리소스 경로 유틸 함수]
// ==========================================================

// 상대경로로 통일해서 협업 시 경로 충돌 방지

// 공용 리소스 폴더 경로 생성기
inline std::string GetrscPath(const std::string& filename)
{
	return "../../Rjpg/" + filename;
}

// 폰트 전용 경로 생성기
inline std::string GetscPath(const std::string& filename)
{
	return "../../Rjpg/Font/" + filename;
}

// 사운드 전용 경로 생성기
inline std::string GetSoundPath(const std::string& filename)
{
	return "../../Rjpg/Sound/" + filename;
}
