#pragma once

#include "enemy.h"

class Model;

class BossEnemy : public Enemy
{
private:

    static Model* EnemyModel;
    static Model* _EnemyModel;

    ID3D11VertexShader* VertexShader = NULL;
    ID3D11PixelShader* PixelShader = NULL;
    ID3D11InputLayout* VertexLayout = NULL;

    float rot = 0.f;
    int a = 0;
    float x = 0.0f;

public:
    void Init();
    void Uninit();
    void Update();
    void Draw();

    static void Load();
    static void UnLoad();
};