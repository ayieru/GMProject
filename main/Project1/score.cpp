#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"

#include "score.h"
#include "camera.h"
#include "polygon2D.h"

Polygon2D* Score::poly;

void Score::Init()
{
	poly = Manager::GetScene()->AddGameObject<Polygon2D>(2);
	poly->SetTextrue("Asset\\Texture\\number.dds", 0.f, 0.f, 10);

	Renderer::CreateVertexShader(&VertexShader, &VertexLayout, "unlitTextureVS.cso");
	Renderer::CreatePixelShader(&PixelShader, "unlitTexturePS.cso");

	Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Scale = D3DXVECTOR3(2.0f, 2.0f, 2.0f);
}

void Score::Uninit()
{
	VertexBuffer->Release();
	Texture->Release();
	VertexShader->Release();
	PixelShader->Release();
	VertexLayout->Release();
}

void Score::Update()
{
	//XV‚³‚ê‚½‚©
	if (renum != num) {
		num++;
		renum = num;
	}
}

void Score::Draw()
{
	//poly->Draw();
}
