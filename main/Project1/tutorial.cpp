#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"

#include "tutorial.h"
#include "camera.h"
#include "title.h"
#include "polygon2D.h"
#include "audio.h" 
#include <iostream>

Polygon2D* Tutorial::poly;
Audio* Tutorial::se;

void Tutorial::Init()
{
	se = Manager::GetScene()->AddGameObject<Audio>(2);

	poly = AddGameObject<Polygon2D>(2);
	poly->SetTextrue("Asset\\Texture\\t1.png", 0.f, 0.f, 0);

	page = 0;
	hold = 1;
}

void Tutorial::Uninit()
{
	Scene::Uninit();
}

void Tutorial::Update()
{
	Scene::Update();

	if (GetAsyncKeyState(VK_RETURN)) {
		if (hold == 0) {
			se->PlaySE(SE::cursor);
			if (page == 0) poly->SetTextrue("Asset\\Texture\\t2.png", 0.f, 0.f, 0);
			if (page == 1) poly->SetTextrue("Asset\\Texture\\t3.png", 0.f, 0.f, 0);
			if (page == 2) Manager::SetScene<Title>();
			page++;
		}
		hold++;
	}
	else {
		hold = 0;
	}

	if (GetAsyncKeyState(VK_ESCAPE)) {
		int on_button;
		on_button = MessageBox(NULL, TEXT("タイトルに戻りますか？"), TEXT("タイトルに戻る"), MB_YESNO);
		if (on_button == IDYES) {
			Manager::SetScene<Title>();
		}
	}
}