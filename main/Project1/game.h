#pragma once

#include "scene.h"

class Game :public Scene
{
private:
	class Audio* bgm;

public:
	void Init();
	void Uninit();
	void Update();
};