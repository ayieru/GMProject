#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "bullet.h"
#include "scene.h"
#include "enemy.h"
#include "player.h"
#include "explosion.h"
#include "UI.h"
#include "boss.h"
#include <string>
#include <iostream>

//スタティックメンバ変数は再定義が必要
Model* Bullet::BulletModel;
Model* Bullet::_BulletModel;

void Bullet::Init()
{
	Position = D3DXVECTOR3(0.0f, -2.0f, 0.0f);
	Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Scale    = D3DXVECTOR3(0.3f, 0.3f, 0.3f);
	Forward  = D3DXVECTOR3(0.f, 0.f, 0.f);
	Mode = Manager::GetScene()->GetGameObject<Player>(1)->GetPlayerMode();

	speed = 0.5f;

	Renderer::CreateVertexShader(&VertexShader, &VertexLayout, "vertexLightingVS.cso");
	Renderer::CreatePixelShader(&PixelShader, "vertexLightingPS.cso");
}

void Bullet::Uninit()
{
	VertexShader->Release();
	PixelShader->Release();
	VertexLayout->Release();
}

void Bullet::Update()
{
	Scene* scene = Manager::GetScene();

	if (Position.z > 28.0f || Position.z < -25.f || Position.x > 10.f || Position.x < -40.f) {
		SetDestroy();
	}

	//エネミー当たり判定
	if (Mode == BWMode::pblack || Mode == BWMode::pwhite) {

		std::vector<Enemy*> enemylist = scene->GetGameObjects<Enemy>(1);
		for (Enemy* enemy : enemylist) {

			D3DXVECTOR3 enemyPosition = enemy->GetPosition();
			D3DXVECTOR3 direction = Position - enemyPosition;
			float length = D3DXVec3Length(&direction);

			if (length < 1.0f) {
				if ((enemy->GetMode() != BWMode::eblack && Mode != BWMode::pwhite) ||
					(enemy->GetMode() != BWMode::ewhite && Mode != BWMode::pblack)) {
					enemy->SetDestroy();
					SetDestroy();
					scene->AddGameObject<Explosion>(1)->SetPosition(enemyPosition);
				}
				SetDestroy();
			}
		}
	}

	//プレイヤー当たり判定
	if (Mode == BWMode::eblack || Mode == BWMode::ewhite) {

		Player* player = scene->GetGameObject<Player>(1);

		if ((player->GetMode() != BWMode::pblack && Mode != BWMode::ewhite) ||
			(player->GetMode() != BWMode::pwhite && Mode != BWMode::eblack)) {

			if (PlayerOBB()) {
				std::vector<Bullet*> bulletlist = scene->GetGameObjects<Bullet>(1);

				//他のたまを消す
				for (Bullet* bullet : bulletlist) {
					bullet->SetDestroy();
				}
				SetDestroy();
				scene->AddGameObject<Explosion>(1)->SetPosition(player->GetPosition() + D3DXVECTOR3(0.0f, 0.5f, 0.0f));
				scene->GetGameObject<UI>(2)->UseLife();
			}
		}
	}

	//ボス当たり判定
	if (Mode == BWMode::pblack || Mode == BWMode::pwhite) {

		BossEnemy* boss = scene->GetGameObject<BossEnemy>(1);
		if (boss != nullptr) {
			if ((boss->GetMode() != BWMode::pblack && Mode != BWMode::ewhite) ||
				(boss->GetMode() != BWMode::pwhite && Mode != BWMode::eblack)) {

				if (BossOBB()) {
					std::vector<Bullet*> bulletlist = scene->GetGameObjects<Bullet>(1);

					SetDestroy();
					scene->AddGameObject<Explosion>(1)->SetPosition(boss->GetPosition() + D3DXVECTOR3(0.0f, 0.5f, 0.0f));

					//UI、ステータスの変更を追加する↓
					scene->GetGameObject<BossEnemy>(1)->UseLife();
				}
			}
		}
	}

	Position += Forward * speed;
}

void Bullet::Draw()
{
	//入力レイアウト
	Renderer::GetDeviceContext()->IASetInputLayout(VertexLayout);

	Renderer::GetDeviceContext()->VSSetShader(VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(PixelShader, NULL, 0);

	//ワールドマトリクス設定
	D3DXMATRIX world, s, r, t;
	D3DXMatrixScaling(&s, Scale.x, Scale.y, Scale.z);
	D3DXMatrixRotationYawPitchRoll(&r, Rotation.x, Rotation.y, Rotation.z + Position.z);
	D3DXMatrixTranslation(&t, Position.x, Position.y, Position.z);
	world = s * r * t;
	Renderer::SetWorldMatrix(&world);

	if (Mode == BWMode::pblack || Mode == BWMode::eblack) {
		BulletModel->Draw();
	}
	else {
		_BulletModel->Draw();
	}

}

bool Bullet::PlayerOBB()
{
	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>(1);

	D3DXVECTOR3 pPosition = player->GetPosition();
	D3DXVECTOR3 direction = Position - pPosition;

	D3DXVECTOR3 obbX, obbY, obbZ;
	float obbLenX, obbLenY, obbLenZ;

	obbX = player->GetOBBX();
	obbLenX = D3DXVec3Length(&obbX);
	obbX /= obbLenX;

	obbY = player->GetOBBY();
	obbLenY = D3DXVec3Length(&obbY);
	obbY /= obbLenY;

	obbZ = player->GetOBBZ();
	obbLenZ = D3DXVec3Length(&obbZ);
	obbZ /= obbLenZ;

	float lenX, lenY, lenZ;

	lenX = D3DXVec3Dot(&obbX, &direction);
	lenY = D3DXVec3Dot(&obbY, &direction);
	lenZ = D3DXVec3Dot(&obbZ, &direction);

	if (fabs(lenX) < obbLenX && fabs(lenZ) < obbLenZ && fabs(lenY) < obbLenY) {
		return true;
	}
	else {
		return false;
	}
}

bool Bullet::BossOBB()
{
	Scene* scene = Manager::GetScene();
	BossEnemy* enemy = scene->GetGameObject<BossEnemy>(1);
	Enemy* benemy = enemy->GetEn(1);

	D3DXVECTOR3 pPosition = benemy->GetPosition();
	D3DXVECTOR3 direction = Position - pPosition;
	float length = D3DXVec3Length(&direction);
	if (length > 2.0f) return false;

	D3DXVECTOR3 obbX, obbY, obbZ;
	float obbLenX, obbLenY, obbLenZ;

	obbX = benemy->GetOBBX();
	obbLenX = D3DXVec3Length(&obbX);
	obbX /= obbLenX;

	obbY = benemy->GetOBBY();
	obbLenY = D3DXVec3Length(&obbY);
	obbY /= obbLenY;

	obbZ = benemy->GetOBBZ();
	obbLenZ = D3DXVec3Length(&obbZ);
	obbZ /= obbLenZ;

	float lenX, lenY, lenZ;

	lenX = D3DXVec3Dot(&obbX, &direction);
	lenY = D3DXVec3Dot(&obbY, &direction);
	lenZ = D3DXVec3Dot(&obbZ, &direction);

	if (fabs(lenX) < obbLenX && fabs(lenZ) < obbLenZ && fabs(lenY) < obbLenY) {
		return true;
	}
	else {
		return false;
	}
}

void Bullet::Load()
{
	BulletModel = new Model();
	BulletModel->Load("Asset\\Models\\t_black.obj");

	_BulletModel = new Model();
	_BulletModel->Load("Asset\\Models\\t_white.obj");
}

void Bullet::UnLoad()
{
	BulletModel->Unload();
	delete BulletModel;

	_BulletModel->Unload();
	delete _BulletModel;
}