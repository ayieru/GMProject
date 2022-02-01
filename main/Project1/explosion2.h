#pragma once
#include "gameobject.h"

class Explosion2 : public GameObject
{
private:

    ID3D11Buffer* VertexBuffer = NULL;
    ID3D11ShaderResourceView* Texture = NULL;
    ID3D11VertexShader* VertexShader = NULL;
    ID3D11PixelShader* PixelShader = NULL;
    ID3D11InputLayout* VertexLayout = NULL;

    int flame;

public:
    void Init();
    void Uninit();
    void Update();
    void Draw();
    void Load();
    void UnLoad();
};