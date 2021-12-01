#pragma once
#include "gameobject.h"
#include <list>
#include <algorithm>

struct EnemySpawn
{
	int spawn_frame;
	float x,y;
	BWMode mode;
};

class Spawn :public GameObject
{
private:

	int max = 31;
	int frame;

	std::list<EnemySpawn> SpawnData{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};