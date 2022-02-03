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

	int textureId;
	float w = 0.f;
	float h = 0.f;

public:

    void Init();
    void Uninit();
	void Update() {};
	void Draw();

	void SetTextrue(const char* Filename, float x, float y,int Id);
	void SetTextrue(const char* Filename, float x, float y, int tcx, int tcy, int tcw, int tch, int Id);
	void SetTextrue(float x, float y, int Id);
	void SetTextrue(float x, float y, int tcx, int tcy, int tcw, int tch, int Id);
	void SwitchTexture(const char* Filename, int Id);
	
	void DestoryTexture(int Id);
};