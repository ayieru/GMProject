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

	ti = Rotation;

	for (int i = 0; i < MAXENEMY; i++) {
		en[i] = new Enemy();
		life[i] = MAXLIFE;
	}
	life[0] = MAXLIFE * 2;

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
		Position.x += 0.05f;
	}

	if (Position.x <= -25.f) {
		re = false;
	}
	else if(re) {
		Position.x -= 0.05f;
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

	Rotation.y += 0.03f;
	ti.y += 0.05f;

	for (int i = 0; i < MAXENEMY; i++) {
		if (life[i] <= 0) {
			en[i] = nullptr;

			if (i == 0) {
				SetDestroy();
			}
		}
	}
	if (en[0] != nullptr) {
		en[0]->SetRotation(Rotation);
		en[0]->SetScale(Scale);
		en[0]->SetEnemy(Position, BWMode::eblack);
	}
	if (en[1] != nullptr) {
		en[1]->SetRotation(ti);
		en[1]->SetScale(Scale);
		en[1]->SetEnemy(Position + D3DXVECTOR3(fcos, 0.f, fsin), BWMode::eblack);
	}
	if (en[2] != nullptr) {
		en[2]->SetRotation(Rotation);
		en[2]->SetScale(Scale);
		en[2]->SetEnemy(Position + D3DXVECTOR3(-fcos, 0.f, fsin), BWMode::eblack);
	}
	if (en[3] != nullptr) {
		en[3]->SetRotation(Rotation);
		en[3]->SetScale(Scale);
		en[3]->SetEnemy(Position + D3DXVECTOR3(fcos, 0.f, -fsin), BWMode::eblack);
	}
	if (en[4] != nullptr) {
		en[4]->SetRotation(ti);
		en[4]->SetScale(Scale);
		en[4]->SetEnemy(Position + D3DXVECTOR3(-fcos, 0.f, -fsin), BWMode::eblack);
	}
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

	for (int i = 1; i < MAXENEMY; i++) {
		if (en[i] != nullptr) {
			D3DXVECTOR3 p = en[i]->GetPosition();
			D3DXVECTOR3 k = en[i]->GetRotation();
			D3DXMatrixRotationYawPitchRoll(&r, k.y, k.x, k.z);
			D3DXMatrixTranslation(&t, p.x, p.y, p.z);
			world = s * r * t;
			Renderer::SetWorldMatrix(&world);
			en[i]->EnemyModel->Draw();
		}
	}
}

void BossEnemy::Load()
{
	int i = 0;

	for (int j = 0; j < 6; j++) {
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
