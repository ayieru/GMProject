#pragma once

#include "scene.h"

enum class type {
	Game,
	Tutorial,
	Score,
};

class Title :public Scene
{
private:
	type t;
	Audio* se1;
	Audio* se2;

	static class Polygon2D* poly;

	int hold = 0;

	void SetGame();
	void SetTutorial();
	void SetScore();

public:
	void Init();
	void Uninit();
	void Update();
};