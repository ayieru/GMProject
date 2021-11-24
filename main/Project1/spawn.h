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

	int frame;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};