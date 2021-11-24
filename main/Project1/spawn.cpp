#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "result.h"
#include "spawn.h"
#include "game.h"

void Spawn::Init()
{
	Spawn::EnemySpawn EnemySpawnData[] = {
	{60,SCREEN_WIDTH,SCREEN_HEIGHT * 0.5f },
	{120,SCREEN_WIDTH,SCREEN_HEIGHT * 0.2f },
	{320,SCREEN_WIDTH,SCREEN_HEIGHT * 0.25f },
	{320,SCREEN_WIDTH,SCREEN_HEIGHT * 0.5f },
	{320,SCREEN_WIDTH,SCREEN_HEIGHT * 0.75f },
	{320,SCREEN_WIDTH,SCREEN_HEIGHT * 0.8f },
	{700,SCREEN_WIDTH,SCREEN_HEIGHT * 0.2f },
	{720,SCREEN_WIDTH,SCREEN_HEIGHT * 0.3f },
	{740,SCREEN_WIDTH,SCREEN_HEIGHT * 0.4f },
	{760,SCREEN_WIDTH,SCREEN_HEIGHT * 0.5f },
	{1000,SCREEN_WIDTH,SCREEN_HEIGHT * 0.5f },
	{1000,SCREEN_WIDTH,SCREEN_HEIGHT * 0.2f },
	{1070,SCREEN_WIDTH,SCREEN_HEIGHT * 0.25f },
	{1070,SCREEN_WIDTH,SCREEN_HEIGHT * 0.5f },
	{1070,SCREEN_WIDTH,SCREEN_HEIGHT * 0.75f },
	{1100,SCREEN_WIDTH,SCREEN_HEIGHT * 0.2f },
	{1100,SCREEN_WIDTH,SCREEN_HEIGHT * 0.3f },
	{1100,SCREEN_WIDTH,SCREEN_HEIGHT * 0.4f },
	{1100,SCREEN_WIDTH,SCREEN_HEIGHT * 0.5f },
	{1100,SCREEN_WIDTH,SCREEN_HEIGHT * 0.6f },
	{1500,SCREEN_WIDTH,SCREEN_HEIGHT * 0.5f },
	{1520,SCREEN_WIDTH,SCREEN_HEIGHT * 0.2f },
	{1540,SCREEN_WIDTH,SCREEN_HEIGHT * 0.25f },
	{1560,SCREEN_WIDTH,SCREEN_HEIGHT * 0.5f },
	{1580,SCREEN_WIDTH,SCREEN_HEIGHT * 0.75f },
	{1620,SCREEN_WIDTH,SCREEN_HEIGHT * 0.2f },
	{1640,SCREEN_WIDTH,SCREEN_HEIGHT * 0.3f },
	{1660,SCREEN_WIDTH,SCREEN_HEIGHT * 0.4f },
	{1680,SCREEN_WIDTH,SCREEN_HEIGHT * 0.5f },
	{1720,SCREEN_WIDTH,SCREEN_HEIGHT * 0.6f },
	};
}

void Spawn::Uninit()
{

}

void Spawn::Update()
{
	frame++;

	if (frame > 3000) {
		//Manager::SetScene<Result>();
	}

	for (int i = 0; i < max; i++) {

	}

}

void Spawn::Draw()
{
}
