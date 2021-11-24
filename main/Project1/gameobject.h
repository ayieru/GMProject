#pragma once
#define GAMEOBJECT_MAX (100)

enum class BWMode {
    black,
    white,
};

class GameObject
{
protected:
    D3DXVECTOR3 Position;
    D3DXVECTOR3 Rotation;
    D3DXVECTOR3 Scale; 
    D3DXVECTOR3 Forward;
    BWMode  Mode;

    bool destroy = false;

public:
    GameObject(){}          //コンストラクタ
    virtual ~GameObject(){} //デストラクタ(純粋仮想)

    virtual void Init() = 0;
    virtual void Uninit() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;

    //Get関数
    BWMode GetMode() { return Mode; }
    D3DXVECTOR3 GetPosition() { return Position; }
    D3DXVECTOR3 GetForward() //前方向ベクトル
    {
        D3DXMATRIX r;
        D3DXMatrixRotationYawPitchRoll(&r, Rotation.y, Rotation.x, Rotation.z);

        D3DXVECTOR3 forward;
        forward.x = r._31;
        forward.y = r._32;
        forward.z = r._33;

        return forward;
    }

    //Set関数
    void SetPosition(D3DXVECTOR3 sPosition) { Position = sPosition; }
    void SetEnemy(D3DXVECTOR3 sPosition, BWMode sMode) { Position = sPosition, Mode = sMode; }
    void SetForward(D3DXVECTOR3 sPosition, D3DXVECTOR3 sForward) { Position = sPosition, Forward = sForward; }
    void SetBullet(D3DXVECTOR3 sPosition, D3DXVECTOR3 sForward, BWMode sMode) { Position = sPosition, Forward = sForward, Mode = sMode; }
    void SetDestroy() { destroy = true; }

    bool Destroy() {
        if (destroy) {
            Uninit();
            delete this;
            return true;
        }
        else {
            return false;
        }
    }

};