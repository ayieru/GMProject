#pragma once
#include "gameobject.h"
#include <list>
#include <algorithm>

struct EnemySpawn
{
	int spawn_frame;
	float x;
	float y;

};

class Spawn :public GameObject
{
private:

	int max = 31;
	int frame;

	EnemySpawn Data[];
	std::list<EnemySpawn*> SpawnData;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};