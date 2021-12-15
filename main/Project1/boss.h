#pragma once

#include "enemy.h"
#include <list>

class Model;

class BossEnemy : public Enemy
{
private:

    static Model* BossModel[];

    static Enemy* en[];

    ID3D11VertexShader* VertexShader = NULL;
    ID3D11PixelShader* PixelShader = NULL;
    ID3D11InputLayout* VertexLayout = NULL;

    float rot = 0.f;
    float fsin = 0.f;
    float fcos = 0.f;
    int a = 0;
    int life = 20;
    bool re = false;

public:
    void Init();
    void Uninit();
    void Update();
    void Draw();

    void UseLife() { life--; };

    static void Load();
    static void UnLoad();
};