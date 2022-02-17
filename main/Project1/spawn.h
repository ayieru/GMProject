#pragma once
 
#include "gameobject.h"

#include <list>


class Spawn :public GameObject
{
private:

	class Audio* bgm;

	float frame;

	std::list<EnemySpawn> SpawnData{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};