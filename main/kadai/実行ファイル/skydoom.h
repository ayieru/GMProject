#pragma once
#include "gameobject.h"

class SkyDoom : public GameObject
{
private:

    static Model* skymodel;

    ID3D11VertexShader* VertexShader = NULL;
    ID3D11PixelShader* PixelShader = NULL;
    ID3D11InputLayout* VertexLayout = NULL;

public:
    void Init();
    void Uninit();
    void Update();
    void Draw();
};