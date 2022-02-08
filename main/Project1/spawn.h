#pragma once
 
#include "gameobject.h"
#include "spawnload.h"

#include <list>


class Spawn :public GameObject
{
private:

	class Audio* bgm;

	float frame;

	std::list<SpawnLoad::EnemySpawn> SpawnData{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};