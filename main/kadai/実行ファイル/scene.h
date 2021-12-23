#pragma once

#define LISTMAX 3

#include <list>
#include <vector>
#include <typeinfo>

#include "gameobject.h"

class Scene
{
public:
	Scene(){}
	virtual ~Scene(){}

	template<typename T>  //�e���v���[�g�֐��@�w�b�_�ɂ������Ȃ�
	T* AddGameObject(const int listcount)
	{
		T* gameobject = new T();
		gameobject->Init();
		Object[listcount].push_back(gameobject);

		return gameobject;
	}


	template<typename T>
	T* GetGameObject(const int listcount)
	{
		for (GameObject* gameobject : Object[listcount]) {
			if (typeid(*gameobject) == typeid(T)) { //�^�𒲂ׂ�(RTTI���I�^���)
				return (T*)gameobject;
			}
		}
		return nullptr;
	}

	template<typename T> 
	std::vector<T*> GetGameObjects(const int listcount)
	{
		std::vector<T*> objects;
		for (GameObject* gameobject : Object[listcount]) {
			if (typeid(*gameobject) == typeid(T)) { 
				objects.push_back((T*)gameobject);
			}
		}
		return objects;
	}

	virtual void Init() = 0;

	virtual void Uninit()
	{
		for (int i = 0; i < LISTMAX; i++) {
			for (GameObject* gameobject : Object[i]) {
				gameobject->Uninit();
				delete gameobject;
			}
			Object[i].clear();
		}
	}

	virtual void Update()
	{
		for (int i = 0; i < LISTMAX; i++) {
			for (GameObject* gameobject : Object[i]) {
				gameobject->Update();
			}

			//�����_��
			Object[i].remove_if([](GameObject* gameobject) {return gameobject->Destroy(); });
		}
	}

	virtual void Draw()
	{
		for (int i = 0; i < LISTMAX; i++) {
			for (GameObject* gameobject : Object[i]) {
				gameobject->Draw();
			}
		}
	}


private:

protected:
	std::list<GameObject*> Object[LISTMAX];
};