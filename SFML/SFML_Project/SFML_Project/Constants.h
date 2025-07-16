#pragma once
#pragma once
#include <SFML/System.hpp>

// 윈도우 설정
constexpr unsigned WINDOW_WIDTH = 1024;
constexpr unsigned WINDOW_HEIGHT = 768;
constexpr char     WINDOW_TITLE[] = "Rebel Of Kitty";

// 플레이어 관련
constexpr float   PLAYER_SPEED = 200.f;    // 픽셀/초
constexpr float   PLAYER_START_X = 1267.f / 2; // 맵 중앙
constexpr float   PLAYER_START_Y = 1275.f / 2;
constexpr unsigned PLAYER_FRAME_COUNT = 5;
constexpr float   PLAYER_ANIM_SPEED = 1.0f;     // 초당 프레임 전환

// 투사체(ayProj) 관련
constexpr unsigned PROJ_FRAME_COUNT = 4;
constexpr float    PROJ_ANIM_SPEED = 1.0f;    // 초당 프레임 전환
constexpr float    PROJ_MIN_RADIUS = 100.f;   // 최소 반경
constexpr float    PROJ_MAX_RADIUS = 150.f;   // 최대 반경
constexpr float    PROJ_ROT_SPEED = 180.f;    // 도/초

// 별(star) 수집 관련
constexpr float    STAR_PICKUP_DIST = 50.f;    // 픽셀
constexpr unsigned STAR_THRESHOLDS[] = { 10, 20 }; // 10 → 4개, 20 → 8개

// 적 생성 관련
constexpr float    ENEMY_SPAWN_INTERVAL = 5.f; // 초당 웨이브 간격
constexpr unsigned ENEMIES_PER_WAVE = 5;
constexpr float    ENEMY_MIN_SPAWN_DIST = 500.f;
constexpr unsigned MAX_ENEMIES_TOTAL = 100;
constexpr float    ENEMY_SPEED = 20.f; // 픽셀/초 

// 맵 크기 (배경 이미지 크기)
constexpr float MAP_WIDTH = 1267.f;
constexpr float MAP_HEIGHT = 1275.f;
