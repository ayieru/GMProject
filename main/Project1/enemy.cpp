#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "model.h"
#include "keyboard.h"
#include "enemy.h"
#include "player.h"
#include "bullet.h"
#include "game.h"
#include "score.h"

#include <string>
#include <iostream>
#include <random>

Model* Enemy::EnemyModel;
Model* Enemy::_EnemyModel;

void Enemy::Init()
{
	Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Rotation = D3DXVECTOR3(0.0f, 1.0f, 1.0f);
	Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	Renderer::CreateVertexShader(&VertexShader, &VertexLayout, "vertexLightingVS.cso");
	Renderer::CreatePixelShader(&PixelShader, "vertexLightingPS.cso");

}

void Enemy::Uninit()
{
	VertexShader->Release();
	PixelShader->Release();
	VertexLayout->Release();
}

void Enemy::Update()
{
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<> r(1,10);

	Rotation.y += r(mt) * 0.01f;

	if (a != 0) {
		Manager::GetScene()->AddGameObject<Bullet>(1)->
			SetBullet(Position + D3DXVECTOR3(0.0f, -1.0f, 0.0f), GetForward(),Mode);
	}
	a++;

	if (a > 10) {
		a = 0;
	}

	Position.z -= 0.1f;
}

void Enemy::Draw()
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

	if (Mode == BWMode::eblack) {
		EnemyModel->Draw();
	}
	else {
		_EnemyModel->Draw();
	}
}

void Enemy::Load()
{
	EnemyModel = new Model();
	EnemyModel->Load("Asset\\Models\\e_black.obj");

	_EnemyModel = new Model();
	_EnemyModel->Load("Asset\\Models\\e_white.obj");
}

void Enemy::UnLoad()
{
	EnemyModel->Unload();
	delete EnemyModel;
	
	_EnemyModel->Unload();
	delete _EnemyModel;
}