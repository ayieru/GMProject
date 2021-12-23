#pragma once
#include "gameobject.h"

class Life : public GameObject
{
private:
	ID3D11Buffer* VertexBuffer;
	ID3D11ShaderResourceView* Texture;
	ID3D11VertexShader* VertexShader;
	ID3D11PixelShader* PixelShader;
	ID3D11InputLayout* VertexLayout;

	int life = 0;
	float width;
	float height;

public:

	void Init();
	void Uninit();
	void Update();
	void Draw();
};