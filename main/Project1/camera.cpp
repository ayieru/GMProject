#include "main.h"
#include "manager.h"
#include "renderer.h"

#include <iostream>
#include <mutex>
#include <directxmath.h>
#include "camera.h"
#include "Toul.h"
#include "player.h"
#include "enemy.h"
#include "game.h"

void Camera::Init()
{
	Position = D3DXVECTOR3(0.f, 20.0f,0.f);
	Rotation = D3DXVECTOR3(0.f, 0.f, 0.f);
	Target   = D3DXVECTOR3(0.f, 0.f, 0.f);
	Up       = D3DXVECTOR3(0.f, 1.f, 1.f);
}

void Camera::Uninit()
{

}

void Camera::Update()
{
}

void Camera::Draw()
{
	//ビューマトリクス設定
	D3DXMatrixLookAtLH(&viewMatrix, &Position, &Target, &Up);

	Renderer::SetViewMatrix(&viewMatrix);

	//プロジェクションマトリクス設定
	D3DXMATRIX ProjectionMatrix,r;
	D3DXMatrixRotationYawPitchRoll(&r, Rotation.y, Rotation.x, Rotation.z);
	D3DXMatrixPerspectiveFovLH(&ProjectionMatrix, D3DXToRadian(60), (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 1000.0f);

	Renderer::SetProjectionMatrix(&ProjectionMatrix);
}

void Camera::Load()
{
}

void Camera::UnLoad()
{
}
