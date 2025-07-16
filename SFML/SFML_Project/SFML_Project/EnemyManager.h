#pragma once
#include "Util.h"
#include "Enemy.h"
#include "CameraManager.h"

//#include "StarManager.hpp"      // starManager가 적이 죽으면 일정확률로 떨어뜨리는 경험치 같음 


class EnemyManager 
{
private:
    vector<unique_ptr<Enemy>> enemies;

    Player* player;
    //StarManager* starMgr;
    CameraManager* camera;

    void spawnWave();

public:
    EnemyManager(Player* player, /*StarManager* starMgr,*/ CameraManager* camera) : player(player), camera(camera) {}

    void update(float dt);
    void draw(sf::RenderTarget& target) const;
    //void applyDamage(const std::vector<ProjectileManager::Orb>& orbs);    // 이건 캐릭터 주변으로 도는 발사체 같음 


};




