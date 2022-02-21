#pragma once

#include "scene.h"

class Result :public Scene
{
private:
	int hold = 1;
public:
	void Init();
	void Uninit();
	void Update();
};