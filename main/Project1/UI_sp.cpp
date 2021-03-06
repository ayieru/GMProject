#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "UI.h"
#include "UI_sp.h"

void Special::Init()
{
	//テクスチャのセット
	width = 40.f;
	height = 40.f;

	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(width, 0.0f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(0.f, height, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(width, height, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &VertexBuffer);

	//テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"Asset/Texture/bl.png",
		NULL,
		NULL,
		&Texture,
		NULL);

	assert(Texture);

	Renderer::CreateVertexShader(&VertexShader, &VertexLayout, "unlitTextureVS.cso");

	Renderer::CreatePixelShader(&PixelShader, "unlitTexturePS.cso");

	Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void Special::Uninit()
{
	VertexBuffer->Release();
	Texture->Release();
	VertexShader->Release();
	PixelShader->Release();
	VertexLayout->Release();
}

void Special::Update()
{

}

void Special::Draw()
{
	////位置のセット
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;
	vertex[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
	vertex[1].Position = D3DXVECTOR3(width, 0.0f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
	vertex[2].Position = D3DXVECTOR3(0.f, height, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
	vertex[3].Position = D3DXVECTOR3(width, height, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	for (int i = 0; i < 4; i++) {
		vertex[i].Position += Position;
	}

	Renderer::GetDeviceContext()->Unmap(VertexBuffer, 0);

	//入力レイアウト
	Renderer::GetDeviceContext()->IASetInputLayout(VertexLayout);

	Renderer::GetDeviceContext()->VSSetShader(VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(PixelShader, NULL, 0);

	//マトリクス
	Renderer::SetWorldViewProjection2D();

	//頂点バッファ
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);

	//テクスチャ
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &Texture);

	//プリミティブトポロジ
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//描画
	Renderer::GetDeviceContext()->Draw(4, 0); //頂点数


}