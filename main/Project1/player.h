#pragma once
#include "gameobject.h"



class Player : public GameObject
{
private:

    static class Model* b_model;

    static class Model* w_model;

    ID3D11VertexShader* VertexShader = NULL;
    ID3D11PixelShader* PixelShader = NULL;
    ID3D11InputLayout* VertexLayout = NULL;
    D3DXQUATERNION _Quaternion;

    float a = 0.0f;
    bool  b = false;
    int   c = 0;
    float x = 0.1f;

public:
    void Init();
    void Uninit();
    void Update();
    void Draw();

    BWMode GetPlayerMode() const { return Mode; }
};