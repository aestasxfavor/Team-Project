// 효 추가
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <Windows.h>	// 이건 혹시 몰라서 
#include <conio.h>
#include <time.h>
#include <utility>
#include <chrono>
#include <cstdlib> // rand()
#include <cmath>	// 작아졌다 커졌다 느낌을 주기위한 애니메이션 (sin 함수 사용)
#include <functional>


// 자료구조 컨테이너
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
#include <ranges>		// 범위기반 알고리즘 헤더

using namespace std;

// 밑에 따로 해놓은 것도 네임스페이스 충돌 방지를 위해 필요한것만 선언(vector, queue 등 필요하면 추가예정)
using std::cout;
using std::cin;
using std::endl;
using std::string;

// 효 추가: 상대경로 하는 게 나중 공동작업 들어갈 때 충돌 안나기 때문에 요렇게 했습니다
inline std::string GetrscPath(const std::string& filename)
{
	return "../../Rjpg/" + filename;
}

// 폰트 전용 상대경로 
inline std::string GetscPath(const std::string& filename)
{
	return "../../Rjpg/Font/" + filename;
}