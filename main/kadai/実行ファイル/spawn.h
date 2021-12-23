#pragma once
#include "gameobject.h"
#include <list>

enum class EnemyState {
	A,
	B,
	C,
	D,
	E,
	Boss1,
	Boss2,
	Boss3,
};

struct EnemySpawn
{
	int spawn_frame;
	float x,y;
	BWMode mode;
	EnemyState state;
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