#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "result.h"
#include "spawn.h"
#include "enemy.h"
#include "game.h"

void Spawn::Init()
{
	SpawnData = {
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
	{1500,0.f,20.f },
	{1520,0.f,20.f },
	{1540,0.f,20.f },
	{1560,0.f,20.f },
	{1580,0.f,20.f },
	{1620,0.f,20.f },
	{1640,0.f,20.f },
	{1660,0.f,20.f },
	{1680,0.f,20.f },
	{1720,0.f,20.f },
	};
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

	for (auto q : SpawnData) {
		if (frame == q.spawn_frame) {
			D3DXVECTOR3 pos = D3DXVECTOR3(q.x, -20.3f, q.y);
			Manager::GetScene()->AddGameObject<Enemy>(1)->SetEnemy(pos, BWMode::black);
		}
	}
}

void Spawn::Draw()
{
}
