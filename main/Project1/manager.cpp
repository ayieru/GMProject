#include "main.h"
#include "scene.h"
#include "manager.h"
#include "renderer.h"
#include "audio.h"

#include "game.h"
#include "title.h"

Scene* Manager::scene = nullptr;

void Manager::Init()
{
	Renderer::Init();
	Audio::InitMaster();

	//SetScene<Title>();
	SetScene<Game>();
}

void Manager::Uninit()
{
	scene->Uninit();
	delete scene;

	Audio::UninitMaster();
	Renderer::Uninit();
}

void Manager::Update()
{
	scene->Update();
}

void Manager::Draw()
{
	Renderer::Begin();

	scene->Draw();

	Renderer::End();
}
