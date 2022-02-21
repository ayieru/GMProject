#pragma once
#include "gameobject.h"

class Score : public GameObject
{
private:

    ID3D11VertexShader* VertexShader = NULL;
    ID3D11PixelShader* PixelShader = NULL;
    ID3D11InputLayout* VertexLayout = NULL;

    static class Polygon2D* poly;

    static int score;

    int num = 0;
    int count = 0;
    int renum = 0;

public:
    void Init();
    void Uninit();
    void Update();
    void Draw() {};

    void AddScore(int num) { score += num; };
    static int GetScore() { return score; };

    void Load();
    void UnLoad();
};