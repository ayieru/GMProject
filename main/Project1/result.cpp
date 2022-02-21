#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "polygon2D.h"
#include "result.h"
#include "audio.h"
#include "title.h"
#include "Toul.h"
#include "UI.h"
#include "score.h"

Polygon2D* Result::poly;

void Result::Init()
{
	poly = AddGameObject<Polygon2D>(2);
	poly->SetTextrue("Asset\\Texture\\sc.png",0.f, 0.f, 0);

	//total
	for (int i = 1; i <= 7; i++) {
		poly = Manager::GetScene()->AddGameObject<Polygon2D>(2);
		poly->SetTextrue("Asset\\Texture\\number.dds", 1000.f - 35 * i, 500.f, 0, 0, 50, 100, i);
	}

	//sp
	for (int i = 1; i <= 7; i++) {
		poly = Manager::GetScene()->AddGameObject<Polygon2D>(2);
		poly->SetTextrue("Asset\\Texture\\number.dds", 1000.f - 35 * i, 350.f, 0, 0, 50, 100, i + 7);
	}

	//life
	for (int i = 1; i <= 7; i++) {
		poly = Manager::GetScene()->AddGameObject<Polygon2D>(2);
		poly->SetTextrue("Asset\\Texture\\number.dds", 1000.f - 35 * i, 250.f, 0, 0, 50, 100, i + 14);
	}

	hold = 1;

	life = (UI::GetLife() + 1) * 2000;
	sp = UI::GetSpecial() * 2000;
	score = Score::GetScore() + life + sp;
}

void Result::Uninit()
{
	Scene::Uninit();
}

void Result::Update()
{
	//life
	if (Lnum != life) {
		Lnum += 111;
		if (life < Lnum)Lnum = life;
		for (int i = 1; i < life; i++) {
			num = Lnum / (int)std::pow(10, i);
			if (num == 0) {
				for (int j = 1; j <= i; j++) {
					count = Lnum / (int)std::pow(10, i - j);
					poly->SetTextrue(1000.f - 35 * (i - j + 1), 250.f, 50 * (count % 10), 0, 50, 100, i - j + 1 + 14);
				}
				break;
			}
		}
	}

	//sp
	if (Snum != sp) {
		Snum += 111;
		if (sp < Snum)Snum = sp;
		for (int i = 1; i < sp; i++) {
			num = Snum / (int)std::pow(10, i);
			if (num == 0) {
				for (int j = 1; j <= i; j++) {
					count = Snum / (int)std::pow(10, i - j);
					poly->SetTextrue(1000.f - 35 * (i - j + 1), 350.f, 50 * (count % 10), 0, 50, 100, i - j + 1 + 7);
				}
				break;
			}
		}
	}

	//total
	if (Tnum != score) {
		Audio* se = Manager::GetScene()->AddGameObject<Audio>(2);
		se->PlaySE(SE::cursor);
		Tnum += score / 100;
		if (score < Tnum)Tnum = score;
		for (int i = 1; i < score; i++) {
			num = Tnum / (int)std::pow(10, i);
			if (num == 0) {
				for (int j = 1; j <= i; j++) {
					count = Tnum / (int)std::pow(10, i - j);
					poly->SetTextrue(1000.f - 35 * (i - j + 1), 500.f, 50 * (count % 10), 0, 50, 100, i - j + 1);
				}
				break;
			}
		}
	}

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
