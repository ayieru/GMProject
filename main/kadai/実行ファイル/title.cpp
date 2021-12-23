#include "main.h"
#include "scene.h"
#include "manager.h"
#include "renderer.h"

#include "audio.h"
#include "polygon2D.h"
#include "title.h"
#include "game.h"

void Title::Init()
{
	Polygon2D* title;
	//title->Load("Asset\\Texture\\ê}1.png");
	AddGameObject<Polygon2D>(2);

	Audio* bgm = AddGameObject<Audio>(2);
	bgm->Load("Asset\\Audio\\01.wav");

}

void Title::Uninit()
{
	Scene::Uninit();
}

void Title::Update()
{
	Scene::Update();
	if (GetAsyncKeyState(VK_SPACE)) {
	
		Audio* bgm = AddGameObject<Audio>(2);
		bgm->Load("Asset\\Audio\\02.wav");
		bgm->Play(false);

		Manager::SetScene<Game>();
	}

}
