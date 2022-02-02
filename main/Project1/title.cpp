#include "main.h"
#include "scene.h"
#include "manager.h"
#include "renderer.h"

#include "Toul.h"
#include "audio.h"
#include "polygon2D.h"
#include "title.h"
#include "game.h"

Polygon2D* Title::poly;

void Title::Init()
{
	poly = AddGameObject<Polygon2D>(2);
	poly->SetTextrue("Asset\\Texture\\title1.png", 0.f, 0.f, 0);
	poly = AddGameObject<Polygon2D>(2);
	poly->SetTextrue("Asset\\Texture\\cursor.png", SCREEN_WIDTH * 2 / 7, SCREEN_HEIGHT * 3.2 / 9, 1);
	poly = AddGameObject<Polygon2D>(2);
	poly->SetTextrue("Asset\\Texture\\start0.png", SCREEN_WIDTH * 4 / 10, SCREEN_HEIGHT / 3, 2);
	poly = AddGameObject<Polygon2D>(2);
	poly->SetTextrue("Asset\\Texture\\tutorial0.png", SCREEN_WIDTH * 4 / 10, SCREEN_HEIGHT / 2, 3);
	poly = AddGameObject<Polygon2D>(2);
	poly->SetTextrue("Asset\\Texture\\score0.png", SCREEN_WIDTH * 4 / 10, SCREEN_HEIGHT * 2 / 3, 4);
	
	t = type::Game;

	poly->DestoryTexture(1);

	se1 = Manager::GetScene()->AddGameObject<Audio>(2);
	se2 = Manager::GetScene()->AddGameObject<Audio>(2);

	Audio* bgm = AddGameObject<Audio>(2);
	bgm->PlayBGM(BGM::main);
}

void Title::Uninit()
{
	Scene::Uninit();
}

void Title::Update()
{
	Scene::Update();

	if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_W)) {
		if (hold == 0) {
			switch (t) {
			case type::Game:
				break;
			case type::Score:
				break;
			case type::Tutorial:
				break;
			}
		}
		hold++;
	}else if (GetAsyncKeyState(VK_S) || GetAsyncKeyState(VK_DOWN)) {
		if (hold == 0) {
			switch (t) {
			case type::Game:
				break;
			case type::Score:
				break;
			case type::Tutorial:
				break;
			}
		}
		hold++;
	}
	else {
		hold = 0;
	}

	if (GetAsyncKeyState(VK_RETURN)) {
		se1->PlaySE(SE::cursor);
		switch (t) {
		case type::Game:
			Manager::SetScene<Game>();
			break;
		case type::Score:
			break;
		case type::Tutorial:
			break;
		}
	}
}

void Title::SetGame()
{
	se1->PlaySE(SE::cursor);
	t = type::Game;
}

void Title::SetTutorial()
{
	se1->PlaySE(SE::cursor);
	t = type::Tutorial;
}

void Title::SetScore()
{
	se1->PlaySE(SE::cursor);
	t = type::Score;
}