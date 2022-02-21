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
	SpawnData = SpawnLoad::LoadData("Asset/data.csv");

	SpawnData.sort([this](SpawnLoad::EnemySpawn a, SpawnLoad::EnemySpawn b)
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

	for (SpawnLoad::EnemySpawn&q : SpawnData) {
		if (frame >= q.spawn_frame) {
			if (frame == q.spawn_frame) {
				if (q.state == EnemyState::boss) {
					bgm->StopBGM(BGM::game);
					bgm->PlayBGM(BGM::boss);
					Manager::GetScene()->AddGameObject<BossEnemy>(1);
					break;
				}
				D3DXVECTOR3 pos = D3DXVECTOR3(q.x, -20.3f, q.y);
				Manager::GetScene()->AddGameObject<Enemy>(1)->SetEnemy(pos, q.mode,q.state);
			}
		}
		else {
			break;
		}
	}
}
