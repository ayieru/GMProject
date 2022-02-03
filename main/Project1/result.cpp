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
	Polygon2D* poly = AddGameObject<Polygon2D>(2);
	poly->SetTextrue("Asset\\Texture\\score0.png", 100.f, 100.f, 0);
}

void Result::Uninit()
{
	Scene::Uninit();
}

void Result::Update()
{
	Scene::Update();
	if (GetAsyncKeyState(VK_BACK)) {
		Manager::SetScene<Title>();
	}
}
