#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "polygon2D.h"
#include "result.h"
#include "audio.h"
#include "title.h"
#include "Toul.h"

void Result::Init()
{
	Polygon2D* title;
	//title->Load("Asset\\Texture\\ê}2.png");
	AddGameObject<Polygon2D>(2);

	Audio* bgm = AddGameObject<Audio>(2);
	bgm->Load("Asset\\Audio\\01.wav");

}

void Result::Uninit()
{
	Scene::Uninit();
}

void Result::Update()
{
	Scene::Update();
	if (GetAsyncKeyState(VK_S)) {
		Manager::SetScene<Title>();
	}
}
