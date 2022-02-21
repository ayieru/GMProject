#pragma once

#include "scene.h"

class Game :public Scene
{
private:
	static bool end;
public:
	void Init();
	void Uninit();
	void Update();
	static void GameEnd();
};