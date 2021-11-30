#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "result.h"
#include "spawn.h"
#include "enemy.h"
#include "game.h"

void Spawn::Init()
{
	Data[] = {
	{60,0.f,20.f },
	{120,-20.f,20.f },
	{320,0.f,20.f },
	{320,-20.f,20.f },
	{320,0.f,20.f },
	{320,0.f,20.f },
	{700,0.f,20.f },
	{720,0.f,20.f },
	{740,0.f,20.f },
	{760,0.f,20.f },
	{1000,0.f,20.f },
	{1000,0.f,20.f },
	{1070,0.f,20.f },
	{1070,0.f,20.f },
	{1070,0.f,20.f },
	{1100,0.f,20.f },
	{1100,0.f,20.f },
	{1100,0.f,20.f },
	{1100,-40.f,20.f },
	{1100,0.f,20.f },
	{1100,0.f,20.f },
	{1120,0.f,20.f },
	{1140,0.f,20.f },
	{1160,0.f,20.f },
	{1180,0.f,20.f },
	{1110,0.f,20.f },
	{1110,0.f,20.f },
	{1160,0.f,20.f },
	{1180,0.f,20.f },
	{1120,0.f,20.f },
	};

	//SpawnData = sorted(SpawnData.)

	SpawnData.sort([this](EnemySpawn* a, EnemySpawn* b)
	{return a->spawn_frame < b->spawn_frame; });
}

void Spawn::Uninit()
{

}

void Spawn::Update()
{
	frame++;

	if (frame > 3000) {
		//Manager::SetScene<Result>();
	}

	for (EnemySpawn* q : SpawnData) {
		if (frame == q->spawn_frame) {
			D3DXVECTOR3 pos = D3DXVECTOR3(q->x, -20.3f, q->y);
			Manager::GetScene()->AddGameObject<Enemy>(1)->SetEnemy(pos, BWMode::eblack);
		}
		else {
			break;
		}
	}
}

void Spawn::Draw()
{
}
