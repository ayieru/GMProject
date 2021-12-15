#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "model.h"
#include "boss.h"
#include "bullet.h"
#include "game.h"

#include <string>
#include <iostream>
#include <random>

Enemy* BossEnemy::en[5];

void BossEnemy::Init()
{
	Position = D3DXVECTOR3(-14.0f, -20.3f, 15.0f);
	Rotation = D3DXVECTOR3(0.0f, 1.0f, 1.0f);
	Scale = D3DXVECTOR3(2.0f, 2.0f, 2.0f);
	Mode = BWMode::eblack;

	for (int i = 0; i < 2; i++) {
		en[i] = Manager::GetScene()->AddGameObject<Enemy>(1);
	}

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
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<> r(1, 10);

	rot += 0.05f;

	fsin = 4 * sinf(rot);
	fcos = 4 * cosf(rot);

	if (Position.x >= 0.f) {
		re = true;
	}
	else if(!re){
		Position.x += 0.1f;
	}

	if (Position.x <= -25.f) {
		re = false;
	}
	else if(re) {
		Position.x -= 0.1f;
	}

	if (a == 0) {
		Manager::GetScene()->AddGameObject<Bullet>(1)->
			SetBullet(Position + D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), Mode);
		Manager::GetScene()->AddGameObject<Bullet>(1)->
			SetBullet(Position + D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR3(0.2f, 0.0f, -1.0f), Mode);
		Manager::GetScene()->AddGameObject<Bullet>(1)->
			SetBullet(Position + D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR3(-0.2f, 0.0f, -1.0f), Mode);
	}
	a++;
	if (a > 10) {
		a = 0;
	}

	Rotation.y += 0.02f;

	if (life <= 0) {
		SetDestroy();
	}

	en[1]->SetPosition(Position + D3DXVECTOR3(fcos, 0.f, fsin));
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
	en[0]->EnemyModel->Draw();

	D3DXVECTOR3 p = en[1]->GetPosition();
	D3DXMatrixTranslation(&t, p.x, p.y, p.z);
	world = s * r * t;
	Renderer::SetWorldMatrix(&world);
	en[1]->EnemyModel->Draw();

}

void BossEnemy::Load()
{
	int i = 0;

	for (int j = 0; j < 5; j++) {
		if (i == 0) {
			en[j]->EnemyModel = new Model();
			en[j]->EnemyModel->Load("Asset\\Models\\e_black.obj");
			i++;
		}
		else {
			en[j]->EnemyModel = new Model();
			en[j]->EnemyModel->Load("Asset\\Models\\e_white.obj");
		}
	}
}

void BossEnemy::UnLoad()
{
	//for (int i = 0; i < 5; i++) {
	//	en[i]->EnemyModel->Unload();
	//}
}
