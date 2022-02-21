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

	hold = 1;
}

void Result::Uninit()
{
	Scene::Uninit();
}

void Result::Update()
{
	Scene::Update();
	if (GetAsyncKeyState(VK_RETURN)) {
		if (hold == 0) {
		Manager::SetScene<Title>();
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
