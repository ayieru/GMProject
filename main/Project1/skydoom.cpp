#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "skydoom.h"
#include "scene.h"
#include <string>
#include <iostream>

Model* SkyDoom::skymodel;

void SkyDoom::Init()
{
	skymodel = new Model();
	skymodel->Load("Asset\\Models\\skyDoom.obj");

	Renderer::CreateVertexShader(&VertexShader, &VertexLayout, "unlitTextureVS.cso");

	Renderer::CreatePixelShader(&PixelShader, "unlitTexturePS.cso");

	Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Scale = D3DXVECTOR3(100.0f, 100.0f, 100.0f);
}

void SkyDoom::Uninit()
{
	skymodel->Unload();
	delete skymodel;

	VertexShader->Release();
	PixelShader->Release();
	VertexLayout->Release();
}

void SkyDoom::Update()
{
}

void SkyDoom::Draw()
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

	skymodel->Draw();
}