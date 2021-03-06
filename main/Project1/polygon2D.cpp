#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"

#include "polygon2D.h"

void Polygon2D::Init()
{
	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(50.0f, 0.0f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(300.0f, 0.0f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(50.0f, 400.0f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(300.0f, 400.0f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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

	Renderer::CreateVertexShader(&VertexShader, &VertexLayout, "unlitTextureVS.cso");
	Renderer::CreatePixelShader(&PixelShader, "unlitTexturePS.cso");
}

void Polygon2D::Uninit()
{
	VertexBuffer->Release();
	Texture->Release();
	VertexShader->Release();
	PixelShader->Release();
	VertexLayout->Release();
}

void Polygon2D::Draw()
{
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

void Polygon2D::SetTextrue(const char* Filename, float x, float y,int Id)
{
	textureId = Id;

	D3DXIMAGE_INFO info;
	D3DXGetImageInfoFromFile(Filename, &info);
	w = (float)info.Width;
	h = (float)info.Height;

	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;
	{
		vertex[0].Position = D3DXVECTOR3(x, y, 0.0f);
		vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].TexCoord = D3DXVECTOR2(0.f, 0.f);

		vertex[1].Position = D3DXVECTOR3(x + w, y, 0.0f);
		vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].TexCoord = D3DXVECTOR2(1.f, 0.f);

		vertex[2].Position = D3DXVECTOR3(x, y + h, 0.0f);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].TexCoord = D3DXVECTOR2(0.f, 1.f);

		vertex[3].Position = D3DXVECTOR3(x + w, y + h, 0.0f);
		vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].TexCoord = D3DXVECTOR2(1.f, 1.f);
	}

	Renderer::GetDeviceContext()->Unmap(VertexBuffer, 0);

	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		Filename,
		NULL,
		NULL,
		&Texture,
		NULL);
	assert(Texture);
}

void Polygon2D::SetTextrue(const char* Filename, float x, float y, int tcx, int tcy, int tcw, int tch, int Id)
{
	textureId = Id;

	D3DXIMAGE_INFO info;
	D3DXGetImageInfoFromFile(Filename, &info);
	w = (float)info.Width;
	h = (float)info.Height;

	float u0 = (float)tcx / w;
	float v0 = (float)tcy / h;
	float u1 = (float)(tcx + tcw) / w;
	float v1 = (float)(tcy + tch) / h;

	//頂点データ書き換え
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;
	{
		vertex[0].Position = D3DXVECTOR3(x, y, 0.0f);
		vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].TexCoord = D3DXVECTOR2(u0, v0);

		vertex[1].Position = D3DXVECTOR3(x + tcw, y, 0.0f);
		vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].TexCoord = D3DXVECTOR2(u1, v0);

		vertex[2].Position = D3DXVECTOR3(x, y + tch, 0.0f);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].TexCoord = D3DXVECTOR2(u0, v1);

		vertex[3].Position = D3DXVECTOR3(x + tcw, y + tch, 0.0f);
		vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].TexCoord = D3DXVECTOR2(u1, v1);
	}

	Renderer::GetDeviceContext()->Unmap(VertexBuffer, 0);

	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		Filename,
		NULL,
		NULL,
		&Texture,
		NULL);
	assert(Texture);
}

void Polygon2D::SetTextrue(float x, float y, int Id)
{
	Scene* scene = Manager::GetScene();
	std::vector<Polygon2D*> list = scene->GetGameObjects<Polygon2D>(2);
	for (Polygon2D* p : list) {
		if (Id == p->textureId && p->Texture != nullptr) {

			D3D11_MAPPED_SUBRESOURCE msr;
			Renderer::GetDeviceContext()->Map(p->VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
			
			VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;
			{
				vertex[0].Position = D3DXVECTOR3(x, y, 0.0f);
				vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
				vertex[0].TexCoord = D3DXVECTOR2(0.f, 0.f);

				vertex[1].Position = D3DXVECTOR3(x + w, y, 0.0f);
				vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
				vertex[1].TexCoord = D3DXVECTOR2(1.f, 0.f);

				vertex[2].Position = D3DXVECTOR3(x, y + h, 0.0f);
				vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
				vertex[2].TexCoord = D3DXVECTOR2(0.f, 1.f);

				vertex[3].Position = D3DXVECTOR3(x + w, y + h, 0.0f);
				vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
				vertex[3].TexCoord = D3DXVECTOR2(1.f, 1.f);
			}
			Renderer::GetDeviceContext()->Unmap(p->VertexBuffer, 0);
		}
	}
}

void Polygon2D::SetTextrue(float x, float y, int tcx, int tcy, int tcw, int tch, int Id)
{
	Scene* scene = Manager::GetScene();
	std::vector<Polygon2D*> list = scene->GetGameObjects<Polygon2D>(2);
	for (Polygon2D* p : list) {
		if (Id == p->textureId && p->Texture != nullptr) {

 			float u0 = (float)tcx / w;
			float v0 = (float)tcy / h;
			float u1 = (float)(tcx + tcw) / w;
			float v1 = (float)(tcy + tch) / h;

			D3D11_MAPPED_SUBRESOURCE msr;
			Renderer::GetDeviceContext()->Map(p->VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

			VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;
			{
				vertex[0].Position = D3DXVECTOR3(x, y, 0.0f);
				vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
				vertex[0].TexCoord = D3DXVECTOR2(u0, v0);

				vertex[1].Position = D3DXVECTOR3(x + tcw, y, 0.0f);
				vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
				vertex[1].TexCoord = D3DXVECTOR2(u1, v0);

				vertex[2].Position = D3DXVECTOR3(x, y + tch, 0.0f);
				vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
				vertex[2].TexCoord = D3DXVECTOR2(u0, v1);

				vertex[3].Position = D3DXVECTOR3(x + tcw, y + tch, 0.0f);
				vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
				vertex[3].TexCoord = D3DXVECTOR2(u1, v1);
			}

			Renderer::GetDeviceContext()->Unmap(p->VertexBuffer, 0);
			break;
		}
	}
}

void Polygon2D::SwitchTexture(const char* Filename, int Id)
{
	Scene* scene = Manager::GetScene();
	std::vector<Polygon2D*> list = scene->GetGameObjects<Polygon2D>(2);
	for (Polygon2D* p : list) {
		if (Id == p->textureId) {
			D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
				Filename,
				NULL,
				NULL,
				&p->Texture,
				NULL);
			assert(p->Texture);
		}
	}
}

void Polygon2D::DestoryTexture(int Id)
{
	Scene* scene = Manager::GetScene();
	std::vector<Polygon2D*> list = scene->GetGameObjects<Polygon2D>(2);
	for (Polygon2D* p : list) {
		if (Id == p->textureId) {
			p->SetDestroy();
		}
	}
}