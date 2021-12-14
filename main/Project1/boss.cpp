#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "model.h"
#include "boss.h"



void BossEnemy::Init()
{
	Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Rotation = D3DXVECTOR3(0.0f, 1.0f, 1.0f);
	Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	Mode = BWMode::pblack;

	Renderer::CreateVertexShader(&VertexShader, &VertexLayout, "vertexLightingVS.cso");
	Renderer::CreatePixelShader(&PixelShader, "vertexLightingPS.cso");
}

void BossEnemy::Uninit()
{
	VertexShader->Release();
	PixelShader->Release();
	VertexLayout->Release();
}

void BossEnemy::Update()
{
}

void BossEnemy::Draw()
{
	//入力レイアウト
	Renderer::GetDeviceContext()->IASetInputLayout(VertexLayout);

	Renderer::GetDeviceContext()->VSSetShader(VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(PixelShader, NULL, 0);

	//ワールドマトリクス設定
	D3DXMATRIX world, s, r, t;
	D3DXMatrixScaling(&s, Scale.x, Scale.y, Scale.z);
	D3DXMatrixRotationYawPitchRoll(&r, Rotation.y, Rotation.x, Rotation.z);
	D3DXMatrixTranslation(&t, Position.x, Position.y, Position.z);
	world = s * r * t;
	Renderer::SetWorldMatrix(&world);

	for (Model* q : BossModel) {
		if (q != nullptr) {
			q->Draw();
		}
	}
}

void BossEnemy::Load()
{
	int i = 0;

	for (Model* q : BossModel) {
		if (i == 0) {
			q->Load("Asset\\Models\\e_black.obj");
			i++;
		}
		else {
			q->Load("Asset\\Models\\e_white.obj");
		}
	}
}

void BossEnemy::UnLoad()
{
	for (Model* q : BossModel) {
		q->Unload();
	}
}
