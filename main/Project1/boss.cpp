#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "model.h"
#include "boss.h"
#include "bullet.h"
#include "game.h"
#include "explosion2.h"
#include "audio.h"
#include "score.h"

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

	for (int i = 0; i < MAXENEMY; i++) {
		Eposition[i] = Position;
	}

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
	Scene* scene = Manager::GetScene();

	//位置更新
	rot += 0.05f;
	fsin = 4 * sinf(rot);
	fcos = 4 * cosf(rot);

	//ボス位置
	{
		if (Position.x >= 0.f) {
			re = true;
		}
		else if (!re) {
			Position.x += 0.05f;
		}

		if (Position.x <= -25.f) {
			re = false;
		}
		else if (re) {
			Position.x -= 0.05f;
		}
	}
	if (en[0] != nullptr) {
		en[0]->SetRotation(Rotation);
		en[0]->SetScale(Scale);
		en[0]->SetEnemy(Position, BWMode::eblack);
	}
	if (en[1] != nullptr) {
		Eposition[1] = Position + D3DXVECTOR3(fcos, 0.f, fsin);
		en[1]->SetRotation(ti);
		en[1]->SetScale(Scale);
		en[1]->SetEnemy(Eposition[1], BWMode::eblack);
	}
	if (en[2] != nullptr) {
		Eposition[2] = Position + D3DXVECTOR3(-fcos, 0.f, fsin);
		en[2]->SetRotation(Rotation);
		en[2]->SetScale(Scale);
		en[2]->SetEnemy(Eposition[2], BWMode::eblack);
	}
	if (en[3] != nullptr) {
		Eposition[3] = Position + D3DXVECTOR3(fcos, 0.f, -fsin);
		en[3]->SetRotation(Rotation);
		en[3]->SetScale(Scale);
		en[3]->SetEnemy(Eposition[3], BWMode::eblack);
	}
	if (en[4] != nullptr) {
		Eposition[4] = Position + D3DXVECTOR3(-fcos, 0.f, -fsin);
		en[4]->SetRotation(ti);
		en[4]->SetScale(Scale);
		en[4]->SetEnemy(Eposition[4], BWMode::eblack);
	}
	
	//回転更新
	Rotation.y += 0.03f;
	ti.y += 0.05f;

	//弾
	if (a % 2 == 1) {
		scene->AddGameObject<Bullet>(1)->SetBullet(Position + D3DXVECTOR3(0.0f, -1.0f, 0.0f), GetForward(), BWMode::ewhite);
	}
	if (a == 0) {
		scene->AddGameObject<Bullet>(1)->SetBullet(Position + D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.f), Mode);
		scene->AddGameObject<Bullet>(1)->SetBullet(Position + D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR3(0.2f, 0.0f, -1.f), Mode);
		scene->AddGameObject<Bullet>(1)->SetBullet(Position + D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR3(-0.2f, 0.0f, -1.f), Mode);
		scene->AddGameObject<Bullet>(1)->SetBullet(Position + D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR3(0.4f, 0.0f, -1.f), Mode);
		scene->AddGameObject<Bullet>(1)->SetBullet(Position + D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR3(-0.4f, 0.0f, -1.f), Mode);
	}
	a++;
	if (a > 20) {
		a = 0;
	}

	for (int i = 0; i < MAXENEMY; i++) {
		if (life[i] == 0 ) {
			Audio* se = Manager::GetScene()->AddGameObject<Audio>(2);
			se->PlaySE(SE::ex);
			en[i] = nullptr;
			life[i] = -1;
			scene->GetGameObject<Score>(2)->AddScore(1000);
			scene->AddGameObject<Explosion2>(1)->SetPosition(Eposition[i]);
			if (i == 0) {
				scene->GetGameObject<Score>(2)->AddScore(10000);
				SetDestroy();
			}
		}
	}

	//その他
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
	en[0]->_EnemyModel->Draw();

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
