#pragma once

#include "scene.h"

class Result :public Scene
{
private:
	static class Polygon2D* poly;

	int hold = 1;

	int score;
	int life;
	int sp;

	int num = 0;
	int count = 0;

	int Lnum = 0;
	int Snum = 0;
	int Tnum = 0;

public:
	void Init();
	void Uninit();
	void Update();
};