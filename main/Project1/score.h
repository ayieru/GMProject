#pragma once
#include "gameobject.h"

class Score : public GameObject
{
private:

    ID3D11Buffer* VertexBuffer = NULL;
    ID3D11ShaderResourceView* Texture = NULL;
    ID3D11VertexShader* VertexShader = NULL;
    ID3D11PixelShader* PixelShader = NULL;
    ID3D11InputLayout* VertexLayout = NULL;

    static class Polygon2D* poly;

    int score = 0;

    int num = 0;
    int renum = 0;

public:
    void Init();
    void Uninit();
    void Update();
    void Draw();


    void AddScore(int num) { score += num; };
    void Load();
    void UnLoad();
};