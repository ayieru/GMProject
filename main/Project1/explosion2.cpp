#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "explosion2.h"
#include "camera.h"
#include "game.h"

void Explosion2::Init()
{
	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(-2.0f, 2.0f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(2.0f, 2.0f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(-2.0f, -2.0f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(2.0f, -2.0f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@
	D3D11_BUFFER_DESC bd{};
	bd.Usage = D3D11_USAGE_DYNAMIC;   //�ς���
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; //������

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &VertexBuffer);

	//�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"Asset/Texture/ex2.dds",
		NULL,
		NULL,
		&Texture,
		NULL);

	assert(Texture);

	Renderer::CreateVertexShader(&VertexShader, &VertexLayout, "Asset\\cso\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&PixelShader, "Asset\\cso\\unlitTexturePS.cso");

	Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Scale = D3DXVECTOR3(2.0f, 2.0f, 2.0f);

}

void Explosion2::Uninit()
{
	VertexBuffer->Release();
	Texture->Release();
	VertexShader->Release();
	PixelShader->Release();
	VertexLayout->Release();
}

void Explosion2::Update()
{
	flame++;

	if (flame >= 20) {
		SetDestroy();
	}
}

void Explosion2::Draw()
{
	//���_�f�[�^��������
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	float x = flame % 5 * 0.2f;
	float y = flame / 2 * 0.5f;

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;
	{
		vertex[0].Position = D3DXVECTOR3(-3.0f, 3.0f, 0.0f);
		vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].TexCoord = D3DXVECTOR2(x, y);

		vertex[1].Position = D3DXVECTOR3(3.0f, 3.0f, 0.0f);
		vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].TexCoord = D3DXVECTOR2(x + 0.2f, y);

		vertex[2].Position = D3DXVECTOR3(-3.0f, -3.0f, 0.0f);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].TexCoord = D3DXVECTOR2(x, y + 0.5f);

		vertex[3].Position = D3DXVECTOR3(3.0f, -3.0f, 0.0f);
		vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].TexCoord = D3DXVECTOR2(x + 0.2f, y + 0.5f);
	}

	Renderer::GetDeviceContext()->Unmap(VertexBuffer, 0);

	//���̓��C�A�E�g
	Renderer::GetDeviceContext()->IASetInputLayout(VertexLayout);

	Renderer::GetDeviceContext()->VSSetShader(VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(PixelShader, NULL, 0);

	//���[���h�}�g���N�X�ݒ�
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

	//���_�o�b�t�@
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);

	//�}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Renderer::SetMaterial(material);

	//�e�N�X�`��
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &Texture);

	//�v���~�e�B�u�g�|���W
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//�`��
	Renderer::GetDeviceContext()->Draw(4, 0); //���_��
}

void Explosion2::Load()
{
}

void Explosion2::UnLoad()
{
}
