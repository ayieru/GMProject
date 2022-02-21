#pragma once

#include "scene.h"

class Tutorial :public Scene
{
private:
	int page = 0;
	int hold = 1;

	static class Audio* se;
	static class Polygon2D* poly;

public:
	void Init();
	void Uninit();
	void Update();
};