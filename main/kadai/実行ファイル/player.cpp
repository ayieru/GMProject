#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "model.h"
#include "game.h"
#include "player.h"
#include "Toul.h"
#include "bullet.h"
#include "enemy.h"
#include "audio.h"
#include "camera.h"
#include "UI.h"
#include "white.h"

#include <string>
#include <iostream>

Model* Player::b_model;
Model* Player::w_model;

void Player::Init()
{
	b_model = new Model();
	b_model->Load("Asset\\Models\\p_black.obj");

	w_model = new Model();
	w_model->Load("Asset\\Models\\p_white.obj");

	BWMode mode = BWMode::pblack;

	Renderer::CreateVertexShader(&VertexShader, &VertexLayout, "vertexLightingVS.cso");
	Renderer::CreatePixelShader(&PixelShader, "vertexLightingPS.cso");

	Position = D3DXVECTOR3(-16.0f, -21.3f, -16.0f);
	Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	D3DXQuaternionIdentity(&Quaternion);
}

void Player::Uninit()
{
	b_model->Unload();
	delete b_model;

	w_model->Unload();
	delete w_model;

	VertexShader->Release();
	PixelShader->Release();
	VertexLayout->Release();
}

void Player::Update()
{
	D3DXVECTOR3 forward = GetForward();

	//移動
	if (Position.z < -25.f || Position.x > 10.f || Position.x < -40.f) {

	}
	if (GetAsyncKeyState(VK_J)) {
		if (GetAsyncKeyState(VK_W) && Position.z < 21.0f) Position += forward * 0.1f * 0.5f;
		if (GetAsyncKeyState(VK_S)) Position -= forward * 0.1f * 0.5f;
		if (GetAsyncKeyState(VK_D)) Position.x += 0.1f * 0.5f;
		if (GetAsyncKeyState(VK_A)) Position.x -= 0.1f * 0.5f;
	}
	else {
		if (GetAsyncKeyState(VK_W) && Position.z < 21.f) Position += forward * 0.3f;
		if (GetAsyncKeyState(VK_S) && Position.z > -20.5f) Position -= forward * 0.4f;
		if (GetAsyncKeyState(VK_D) && Position.x < 8.f) Position.x += 0.35f;
		if (GetAsyncKeyState(VK_A) && Position.x > -37.5f) Position.x -= 0.35f;
	}

	//shot
	if (GetAsyncKeyState(VK_K)) {
		if (a == 0) {
			Audio* se = Manager::GetScene()->AddGameObject<Audio>(2);
			se->Load("Asset\\Audio\\02.wav");
			//se->Play(false);
			Manager::GetScene()->AddGameObject<Bullet>(1)->
				SetBullet(Position + D3DXVECTOR3(0.f, 1.f, 0.f), forward, Mode);
		}
		a++;

		if (a > 5) {
			a = 0;
		}
	}
	else {
		a = 0;
	}

	//sp
	if (GetAsyncKeyState(VK_L)) {
		Scene* scene = Manager::GetScene();
		if (intervaltime == 0) {
			if (scene->GetGameObject<UI>(2)->GetSpecial() > 0) {
				scene->AddGameObject<White>(1);
				std::vector<Enemy*> lifelist = scene->GetGameObjects<Enemy>(1);
				for (Enemy* enemy : lifelist) {
					enemy->SetDestroy();
				}
				std::vector<Bullet*> bulletlist = scene->GetGameObjects<Bullet>(1);
				for (Bullet* life : bulletlist) {
					life->SetDestroy();
				}
				scene->GetGameObject<UI>(2)->UseSpecial();
				intervaltime++;
			}
		}
		else {
			intervaltime++;
		}
	}
	else if (intervaltime != 0 && intervaltime <= 200) {
		intervaltime++;
	}
	else {
		intervaltime = 0;
	}

	//切り替え
	if (GetAsyncKeyState(VK_SPACE)) {
		if (b == false) {
			Audio* bgm = Manager::GetScene()->AddGameObject<Audio>(2);
			bgm->Load("Asset\\Audio\\02.wav");
			//bgm->Play(false);

			if (Mode == BWMode::pblack){
				Mode = BWMode::pwhite;
			}
			else {
				Mode = BWMode::pblack;
			}
		}
		b = true;
	}
	else {
		b = false;
	}

	//回転
	if (GetAsyncKeyState(VK_W)) {
		D3DXQUATERNION quat;
		D3DXVECTOR3 axis = D3DXVECTOR3(1.f, 0.f, 0.f);
		D3DXQuaternionRotationAxis(&quat, &axis, 0.1f);
		Quaternion *= quat;
	}
	if (GetAsyncKeyState(VK_S)) {
		D3DXQUATERNION quat;
		D3DXVECTOR3 axis = D3DXVECTOR3(1.f, 0.f, 0.f);
		D3DXQuaternionRotationAxis(&quat, &axis, -0.1f);
		Quaternion *= quat;
	}
	if (GetAsyncKeyState(VK_D)) {
		D3DXQUATERNION quat;
		D3DXVECTOR3 axis = D3DXVECTOR3(0.f, 0.f, 1.f);
		D3DXQuaternionRotationAxis(&quat, &axis, -0.1f);
		Quaternion *= quat;
	}
	if (GetAsyncKeyState(VK_A)) {
		D3DXQUATERNION quat;
		D3DXVECTOR3 axis = D3DXVECTOR3(0.f, 0.f, 1.f);
		D3DXQuaternionRotationAxis(&quat, &axis, 0.1f);
		Quaternion *= quat;
	}

}

void Player::Draw()
{
	//入力レイアウト
	Renderer::GetDeviceContext()->IASetInputLayout(VertexLayout);

	Renderer::GetDeviceContext()->VSSetShader(VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(PixelShader, NULL, 0);

	//ワールドマトリクス設定
	D3DXMATRIX world, s, r, t;
	D3DXMatrixScaling(&s, Scale.x, Scale.y, Scale.z);
	D3DXMatrixRotationQuaternion(&r, &Quaternion);
	D3DXMatrixTranslation(&t, Position.x, Position.y, Position.z);
	world = s * r * t;
	Renderer::SetWorldMatrix(&world);

	if (Mode == BWMode::pblack) {
		b_model->Draw();
	}
	else {
		w_model->Draw();
	}

}
