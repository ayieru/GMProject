#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "polygon2D.h"
#include "scene.h"
#include "UI.h"
#include "UI_life.h"
#include "UI_sp.h"
#include "result.h"

#include "Toul.h"
#include "camera.h"
#include "game.h"

void UI::Init()
{
	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(-16.0f, 9.0f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(16.0f, 9.0f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(-16.f, -9.0f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(16.0f, -9.0f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファ
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DYNAMIC;   //変える
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; //かえる

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &VertexBuffer);

	//テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"Asset/Texture/UI.png",
		NULL,
		NULL,
		&Texture,
		NULL);

	assert(Texture);

	Renderer::CreateVertexShader(&VertexShader, &VertexLayout, "unlitTextureVS.cso");

	Renderer::CreatePixelShader(&PixelShader, "unlitTexturePS.cso");

	Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Scale = D3DXVECTOR3(1.3f, 1.35f, 1.0f);

	_life = 2;
	f_life = 0;
	_special = 3;
	f_special = 0;
}

void UI::Uninit()
{
	VertexBuffer->Release();
	Texture->Release();
	VertexShader->Release();
	PixelShader->Release();
	VertexLayout->Release();
}

void UI::Update()
{
	Scene* scene = Manager::GetScene();

	if (_life == -1) {
		//Manager::SetScene<Result>();
	}

	//更新
	if (_life != f_life) {
		std::vector<Life*> lifelist = scene->GetGameObjects<Life>(2);
		for (Life* life : lifelist) {
			life->SetDestroy();
		}
		for (int i = 0; i < _life; i++) {
			scene->AddGameObject<Life>(2)->SetPosition(D3DXVECTOR3(1020.0f + i * 40.0f * 1.5f, 190.0f, 0.0f));
		}
		f_life = _life;
	}

	if (_special != f_special) {
		std::vector<Special*> lifelist = scene->GetGameObjects<Special>(2);
		for (Special* life : lifelist) {
			life->SetDestroy();
		}
		for (int i = 0; i < _special; i++) {
			scene->AddGameObject<Special>(2)->SetPosition(D3DXVECTOR3(1040.0f + i * 40.0f * 1.5f, 310.0f, 0.0f));
		}
		f_special = _special;
	}

	if (GetAsyncKeyState(VK_UP) && _life < 4) {
		_life++;
		_special++;
	}

	if (GetAsyncKeyState(VK_DOWN) && _life > 1) {
		_life--;
		_special--;
	}
}

void UI::Draw()
{
	//入力レイアウト
	Renderer::GetDeviceContext()->IASetInputLayout(VertexLayout);

	Renderer::GetDeviceContext()->VSSetShader(VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(PixelShader, NULL, 0);

	//ワールドマトリクス設定
	D3DXMATRIX world, s, r, t;

	Camera* camera = Manager::GetScene()->GetGameObject<Camera>(0);
	D3DXMatrixInverse(&r, nullptr, &camera->GetCameraViewMatrix());
	r._41 = 0.0f;
	r._42 = 0.0f;
	r._43 = 0.0f;

	D3DXMatrixScaling(&s, Scale.x, Scale.y, Scale.z);
	D3DXMatrixTranslation(&t, Position.x, Position.y, Position.z);
	world = s * r * t;
	Renderer::SetWorldMatrix(&world);

	//頂点バッファ
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);

	//マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Renderer::SetMaterial(material);

	//テクスチャ
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &Texture);

	//プリミティブトポロジ
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//描画
	Renderer::GetDeviceContext()->Draw(4, 0); //頂点数

}