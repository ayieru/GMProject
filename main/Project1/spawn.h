#pragma once
#include "gameobject.h"

class Spawn :public GameObject
{
private:
	typedef struct EnemySpawn_tag
	{
		int spawn_frame;
		float x, y;

	}EnemySpawn;

	int max = 31;
	int frame;

	Spawn::EnemySpawn EnemySpawnData[];

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};