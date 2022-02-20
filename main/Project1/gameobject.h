#pragma once
#define GAMEOBJECT_MAX (100)

#include <iostream>
#include <vector>
#include <string>


enum class BWMode {
    pblack,
    pwhite,
    eblack,
    ewhite,
};

enum class EnemyState {
    A,
    B,
    C,
    D,
};

class GameObject
{
protected:
    D3DXVECTOR3 Position;
    D3DXVECTOR3 Rotation;
    D3DXVECTOR3 Scale; 
    D3DXVECTOR3 Forward;

    D3DXQUATERNION Quaternion;

    EnemyState Estate;

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
    D3DXVECTOR3 GetRotation() { return Rotation; }
    //前方向ベクトル
    D3DXVECTOR3 GetForward() 
    {
        D3DXMATRIX r;
        D3DXMatrixRotationYawPitchRoll(&r, Rotation.y, Rotation.x, Rotation.z);

        D3DXVECTOR3 forward;
        forward.x = r._31;
        forward.y = r._32;
        forward.z = r._33;

        return forward;
    }
    //OBBの生成
    D3DXVECTOR3 GetOBBX()
    {
        D3DXMATRIX world, scale, rot, trans;
        D3DXMatrixScaling(&scale, Scale.x, Scale.y, Scale.z);
        D3DXMatrixTranslation(&trans, Position.x, Position.y, Position.z);

        if (Quaternion != D3DXVECTOR3(0, 0, 0)) {
            D3DXMatrixRotationQuaternion(&rot, &Quaternion);
        }
        else {
            D3DXMatrixRotationYawPitchRoll(&rot, Rotation.y, Rotation.x, Rotation.z);
        }

        world = scale * rot * trans;

        D3DXVECTOR3 vx;
        vx.x = world._11;
        vx.y = world._12;
        vx.z = world._13;

        return vx * 0.5f;
    }
    D3DXVECTOR3 GetOBBY()
    {
        D3DXMATRIX world, scale, rot, trans;
        D3DXMatrixScaling(&scale, Scale.x, Scale.y, Scale.z);

        if (Quaternion) {
            D3DXMatrixRotationQuaternion(&rot, &Quaternion);
        }
        else {
            D3DXMatrixRotationYawPitchRoll(&rot, Rotation.y, Rotation.x, Rotation.z);
        }

        D3DXMatrixTranslation(&trans, Position.x, Position.y, Position.z);
        world = scale * rot * trans;

        D3DXVECTOR3 vy;
        vy.x = world._21;
        vy.y = world._22;
        vy.z = world._23;

        return vy * 0.5f;
    }
    D3DXVECTOR3 GetOBBZ()
    {
        D3DXMATRIX world, scale, rot, trans;
        D3DXMatrixScaling(&scale, Scale.x, Scale.y, Scale.z);

        if (Quaternion) {
            D3DXMatrixRotationQuaternion(&rot, &Quaternion);
        }
        else {
            D3DXMatrixRotationYawPitchRoll(&rot, Rotation.y, Rotation.x, Rotation.z);
        }

        D3DXMatrixTranslation(&trans, Position.x, Position.y, Position.z);
        world = scale * rot * trans;

        D3DXVECTOR3 vz;
        vz.x = world._31;
        vz.y = world._32;
        vz.z = world._33;

        return vz * 0.5f;
    }

    //Set関数
    void SetPosition(D3DXVECTOR3 sPosition) { Position = sPosition; }
    void SetRotation(D3DXVECTOR3 sRotation) { Rotation = sRotation; }
    void SetScale(D3DXVECTOR3 sScale) { Scale = sScale; }
    void SetEnemy(D3DXVECTOR3 sPosition, BWMode sMode) { Position = sPosition, Mode = sMode; }
    void SetEnemy(D3DXVECTOR3 sPosition, BWMode sMode, EnemyState sState) { Position = sPosition, Mode = sMode, Estate = sState; }
    void SetForward(D3DXVECTOR3 sPosition, D3DXVECTOR3 sForward) { Position = sPosition, Forward = sForward; }
    void SetBullet(D3DXVECTOR3 sPosition, D3DXVECTOR3 sForward, BWMode sMode) { Position = sPosition, D3DXVec3Normalize(&Forward,&sForward), Mode = sMode; }
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