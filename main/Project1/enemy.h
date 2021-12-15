#pragma once

#include "gameobject.h"

#include  <list>

class Model;

class Enemy : public GameObject
{
private:
    //std::list<Model*> static enemy;

    ID3D11VertexShader* VertexShader = NULL;
    ID3D11PixelShader* PixelShader = NULL;
    ID3D11InputLayout* VertexLayout = NULL;

    float rot = 0.f;
    int a = 0;
    float x = 0.0f;

public:

    static Model* EnemyModel;
    static Model* _EnemyModel;

    void Init();
    void Uninit();
    void Update();
    void Draw();

    static void Load();
    static void UnLoad();
};