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
	{60,0.f,20.f,BWMode::eblack},
	{120,-20.f,20.f ,BWMode::eblack},
	{320,0.f,20.f ,BWMode::eblack},
	{320,-20.f,20.f ,BWMode::ewhite},
	{320,0.f,20.f ,BWMode::ewhite},
	{320,0.f,20.f ,BWMode::eblack},
	{700,0.f,20.f ,BWMode::eblack},
	{720,0.f,20.f ,BWMode::eblack},
	{740,0.f,20.f ,BWMode::ewhite},
	{760,0.f,20.f ,BWMode::eblack},
	{1000,0.f,20.f ,BWMode::eblack},
	{1000,0.f,20.f ,BWMode::eblack},
	{1070,0.f,20.f ,BWMode::eblack},
	{1070,0.f,20.f ,BWMode::eblack},
	{1070,0.f,20.f ,BWMode::eblack},
	{1100,0.f,20.f ,BWMode::eblack},
	{1100,0.f,20.f ,BWMode::eblack},
	{1100,0.f,20.f ,BWMode::eblack},
	{1100,-40.f,20.f ,BWMode::eblack},
	{1100,0.f,20.f ,BWMode::eblack},
	{1100,0.f,20.f ,BWMode::eblack},
	{1120,0.f,20.f ,BWMode::eblack},
	{1140,0.f,20.f ,BWMode::eblack},
	{1160,0.f,20.f ,BWMode::eblack},
	{1180,0.f,20.f ,BWMode::eblack},
	{1110,0.f,20.f ,BWMode::eblack},
	{1110,0.f,20.f ,BWMode::eblack},
	{1160,0.f,20.f ,BWMode::eblack},
	{1180,0.f,20.f ,BWMode::eblack},
	{1120,0.f,20.f ,BWMode::eblack},
	};

	SpawnData.sort([this](EnemySpawn a, EnemySpawn b)
	{return a.spawn_frame < b.spawn_frame; });
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

	for (EnemySpawn q : SpawnData) {
		if (frame == q.spawn_frame) {
			D3DXVECTOR3 pos = D3DXVECTOR3(q.x, -20.3f, q.y);
			Manager::GetScene()->AddGameObject<Enemy>(1)->SetEnemy(pos, q.mode);
		}
	}
}

void Spawn::Draw(){}
