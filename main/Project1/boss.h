#pragma once

#include "enemy.h"
#include <list>

class Model;

class BossEnemy : public Enemy
{
private:

    static Enemy* en[];

    const int MAXENEMY = 5;
    const int MAXLIFE = 12;

    ID3D11VertexShader* VertexShader = NULL;
    ID3D11PixelShader* PixelShader = NULL;
    ID3D11InputLayout* VertexLayout = NULL;

    D3DXVECTOR3* Eposition = new D3DXVECTOR3[MAXENEMY];

    float rot = 0.f;
    float fsin = 0.f;
    float fcos = 0.f;
    int a = 0;
    int ss = 0;
    int* life = new int[MAXENEMY];
    bool re = false;
    bool A = false;

    D3DXVECTOR3 ti;

public:
    void Init();
    void Uninit();
    void Update();
    void Draw();

    Enemy* GetEn(int num) const { return en[num]; }

    void UseLife(int num) { life[num]--; }

    static void Load();
    static void UnLoad();
};