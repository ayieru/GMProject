#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"

#include "score.h"
#include "camera.h"
#include "polygon2D.h"
#include <iostream>

Polygon2D* Score::poly;
int Score::score = 0;

void Score::Init()
{
	for (int i = 1; i <= 7; i++) {
		poly = Manager::GetScene()->AddGameObject<Polygon2D>(2);
		poly->SetTextrue("Asset\\Texture\\number.dds", 1250.f - 35 * i, 50.f, 0, 0, 50, 100, i);
	}

	Renderer::CreateVertexShader(&VertexShader, &VertexLayout, "unlitTextureVS.cso");
	Renderer::CreatePixelShader(&PixelShader, "unlitTexturePS.cso");

	Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	score = 0;
}

void Score::Uninit()
{
	VertexShader->Release();
	PixelShader->Release();
	VertexLayout->Release();
}

void Score::Update()
{
	//更新されたか
	if (renum != score) {
		renum += score/100;
		if (score < renum)renum = score;	//remun が score より大きくなった
		for (int i = 1; i < renum; i++) {
			num = renum / (int)std::pow(10,i);	//num が０になったとき i は桁数
			if (num == 0) {
				for (int j = 1; j <= i; j++) {	// i (桁数)になるまで右から更新
					count = renum / (int)std::pow(10, i - j);	//count には数字が入る０〜９
					poly->SetTextrue(1250.f - 35 * (i - j + 1), 50.f, 50 * (count % 10), 0, 50, 100, i - j + 1);
				}
				break;
			}
		}
	}
}
