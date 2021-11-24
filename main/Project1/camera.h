#pragma once
#include "gameobject.h"

class Camera : public GameObject
{
private:
    D3DXVECTOR3 Target;
    D3DXVECTOR3 Up;
    D3DXMATRIX  viewMatrix;

    D3DXQUATERNION _Quaternion;

    POINT old_po, now_po, screen;

    enum class CameraMode {
        TopView,
        ThirdPerson,
        FirstPerson,
        Rockon,
    };

    CameraMode mode;

public:
    void Init();
    void Uninit();
    void Update();
    void Draw();
    void Load();
    void UnLoad();

    D3DXMATRIX GetCameraViewMatrix() const { return viewMatrix; }
};