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
#include "skydoom.h"
#include "audio.h"
#include "game.h"
#include "result.h"
#include "UI.h"
#include "UI_life.h"
#include "UI_sp.h"
#include "white.h"
#include "spawn.h"


void Game::Init()
{
	Enemy::Load();
	Bullet::Load();

	AddGameObject<Camera>(0);
	AddGameObject<UI>(2);
	AddGameObject<Field>(1);
	AddGameObject<Spawn>(1);
	AddGameObject<Enemy>(1)->SetEnemy(D3DXVECTOR3(0.0f, -20.0f, 5.0f),BWMode::black);
	AddGameObject<Enemy>(1)->SetEnemy(D3DXVECTOR3(3.0f, -20.0f, 6.0f), BWMode::white);
	AddGameObject<Enemy>(1)->SetPosition(D3DXVECTOR3(-3.0f, -20.0f, -2.0f));
	AddGameObject<Player>(1);

	//Audio* bgm = AddGameObject<Audio>(2);
	//bgm->Load("");
	//bgm->Play(true);

	Audio* bgm = AddGameObject<Audio>(2);
	bgm->Load("Asset\\Audio\\01.wav");
	//bgm->Play(true);
}

void Game::Uninit()
{
	Scene::Uninit();

	Enemy::UnLoad();
	Bullet::UnLoad();
}

void Game::Update()
{
		Scene::Update();
	if (GetAsyncKeyState(VK_RETURN)) {
		Manager::SetScene<Result>();
	}
}
