#pragma once
#include "gameobject.h"

class Polygon2D : public GameObject
{
private:
	ID3D11Buffer*             VertexBuffer;
	ID3D11ShaderResourceView* Texture;
	ID3D11VertexShader*       VertexShader;
	ID3D11PixelShader*        PixelShader;
	ID3D11InputLayout*        VertexLayout;

public:

    void Init();
    void Uninit();
    void Update();
	void Draw();

	void SetTextrue(const char* Filename, float x, float y);

};