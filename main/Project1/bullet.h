#pragma once

#include "gameobject.h"

class Bullet : public GameObject
{
private:

    static Model* BulletModel;
    static Model* _BulletModel;

    ID3D11VertexShader* VertexShader = nullptr;
    ID3D11PixelShader* PixelShader = nullptr;
    ID3D11InputLayout* VertexLayout = nullptr;

    float speed = 0.f;

    bool PlayerOBB();

public:
    void Init();
    void Uninit();
    void Update();
    void Draw();

    static void Load();
    static void UnLoad();
};