#pragma once
#include "gameobject.h"

class Score : public GameObject
{
private:

    ID3D11Buffer* VertexBuffer = NULL;
    ID3D11ShaderResourceView* Texture = NULL;
    ID3D11VertexShader* VertexShader = NULL;
    ID3D11PixelShader* PixelShader = NULL;
    ID3D11InputLayout* VertexLayout = NULL;

    int num = 4;

public:
    void Init();
    void Uninit();
    void Update();
    void Draw();
    void Load();
    void UnLoad();
};