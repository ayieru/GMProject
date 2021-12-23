#pragma once

//‘S‘ÌŠÇ—ƒNƒ‰ƒX
class Manager
{
private:
	static class Scene* scene;

public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	static Scene* GetScene() {
		return scene;
	}

	template<typename T>
	static void SetScene()
	{
		if (scene) {
			scene->Uninit();
			delete scene;
		}

		scene = new T();
		scene->Init();
	}
};