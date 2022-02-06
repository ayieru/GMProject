#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "result.h"
#include "spawn.h"
#include "enemy.h"
#include "game.h"
#include "boss.h"
#include "audio.h"

void Spawn::Init()
{
	SpawnData = {
	{1060,0.f,20.f,BWMode::eblack},
	{720,-20.f,20.f ,BWMode::eblack},
	{520,0.f,20.f ,BWMode::eblack},
	{520,-20.f,20.f ,BWMode::ewhite},
	{520,0.f,20.f ,BWMode::ewhite},
	{520,0.f,20.f ,BWMode::eblack},
	{800,0.f,20.f ,BWMode::eblack},
	{820,0.f,20.f ,BWMode::eblack},
	{840,0.f,20.f ,BWMode::ewhite},
	{860,0.f,20.f ,BWMode::eblack},
	{1200,0.f,20.f ,BWMode::eblack},
	{1200,0.f,20.f ,BWMode::eblack},
	{1270,0.f,20.f ,BWMode::eblack},
	{1270,0.f,20.f ,BWMode::eblack},
	{1270,0.f,20.f ,BWMode::eblack},
	{1400,0.f,20.f ,BWMode::ewhite},
	{1500,0.f,20.f ,BWMode::ewhite},
	{1500,0.f,20.f ,BWMode::ewhite},
	{1500,-40.f,20.f ,BWMode::eblack},
	{1500,0.f,20.f ,BWMode::eblack},
	{1500,0.f,20.f ,BWMode::eblack},
	{1520,0.f,20.f ,BWMode::eblack},
	{1810,0.f,20.f ,BWMode::eblack},
	{1810,0.f,20.f ,BWMode::eblack},
	{2010,0.f,20.f ,BWMode::eblack},
	{2010,0.f,20.f ,BWMode::eblack},
	{2010,0.f,20.f ,BWMode::eblack},
	{2010,0.f,20.f ,BWMode::eblack},
	{2010,0.f,20.f ,BWMode::eblack},
	{2010,0.f,40.f ,BWMode::ewhite},
	};

	SpawnData.sort([this](EnemySpawn a, EnemySpawn b)
	{return a.spawn_frame < b.spawn_frame; });

	bgm = Manager::GetScene()->AddGameObject<Audio>(2);
	bgm->PlayBGM(BGM::game);
}

void Spawn::Uninit()
{
	bgm->StopBGM(BGM::game);
	bgm->StopBGM(BGM::boss);
}

void Spawn::Update()
{
	frame++;

	if (frame == 3000) {
		bgm->StopBGM(BGM::game);
		bgm->PlayBGM(BGM::boss);
		Manager::GetScene()->AddGameObject<BossEnemy>(1);
	}

	for (EnemySpawn &q : SpawnData) {
		if (frame >= q.spawn_frame) {
			if (frame == q.spawn_frame) {
				D3DXVECTOR3 pos = D3DXVECTOR3(q.x, -20.3f, q.y);
				Manager::GetScene()->AddGameObject<Enemy>(1)->SetEnemy(pos, q.mode);
			}
		}
		else {
			break;
		}
	}
}

void Spawn::Draw(){}
