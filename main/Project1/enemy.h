#pragma once

#include "gameobject.h"

#include  <list>

class Model;

enum class EnemyState {
    A,
    B,
    C,
    D,
    E,
    Boss1,
    Boss2,
    Boss3
};

class Enemy : public GameObject
{
private:
    std::list<Model*> enemy;

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