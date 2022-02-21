#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "gameobject.h"
#include "polygon2D.h"
#include "camera.h"
#include "field.h"
#include "model.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "explosion.h"
#include "explosion2.h"
#include "skydoom.h"
#include "audio.h"
#include "game.h"
#include "result.h"
#include "UI.h"
#include "UI_life.h"
#include "UI_sp.h"
#include "white.h"
#include "spawn.h"
#include "boss.h"
#include "score.h"
#include "title.h"
#include "spawnload.h"

bool Game::end = false;

void Game::Init()
{
	Enemy::Load();
	Bullet::Load();
	BossEnemy::Load();

	AddGameObject<Camera>(0);
	AddGameObject<UI>(2);
	AddGameObject<Field>(1);
	AddGameObject<Spawn>(1);
	AddGameObject<Player>(1);

	end = false;
}

void Game::Uninit()
{
	Scene::Uninit();

	Enemy::UnLoad();
	Bullet::UnLoad();
	BossEnemy::UnLoad();
}

void Game::Update()
{
	Scene::Update();

	if (GetAsyncKeyState(VK_F1)) {
		Manager::SetScene<Game>();
	}

	if (GetAsyncKeyState(VK_ESCAPE)) {
		int on_button;
		on_button = MessageBox(NULL, TEXT("タイトルに戻りますか？"), TEXT("タイトルに戻る"), MB_YESNO);
		if (on_button == IDYES) {
			Manager::SetScene<Title>();
		}
	}

	if(end) Manager::SetScene<Result>();
}

void Game::GameEnd()
{
	end = true;
}
