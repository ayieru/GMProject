#pragma once
#include "gameobject.h"

class UI : public GameObject
{
private:

    ID3D11Buffer* VertexBuffer = NULL;
    ID3D11ShaderResourceView* Texture = NULL;
    ID3D11VertexShader* VertexShader = NULL;
    ID3D11PixelShader* PixelShader = NULL;
    ID3D11InputLayout* VertexLayout = NULL;

    int a = 0;

    static int _life;
    int f_life = 0;
    static int _special;
    int f_special = 0;

public:
    void Init();
    void Uninit();
    void Update();
    void Draw();

    void UseSpecial() { _special--; }
    void UseLife() { _life--; }

    static int GetLife() { return _life; }
    static int GetSpecial() { return _special; }
};