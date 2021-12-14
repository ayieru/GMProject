#pragma once

#include "enemy.h"
#include <list>
#include <algorithm>

class Model;

class BossEnemy : public Enemy
{
private:

    std::list<Model*> static BossModel;

    ID3D11VertexShader* VertexShader = NULL;
    ID3D11PixelShader* PixelShader = NULL;
    ID3D11InputLayout* VertexLayout = NULL;

public:
    void Init();
    void Uninit();
    void Update();
    void Draw();

    static void Load();
    static void UnLoad();
};