#pragma once

#include "gameobject.h"
#include <sstream> 
#include <fstream>

using namespace std;


class SpawnLoad :public GameObject
{
public:
	void Init() {};
	void Uninit() {};
	void Update() {};
	void Draw() {};



	struct EnemySpawn
	{
		float spawn_frame;
		float x, y;
		BWMode mode;
		EnemyState state;
	};

	static list<SpawnLoad::EnemySpawn> SpawnLoad::LoadData(const char* f) {

		vector<SpawnLoad::EnemySpawn> DataTable;
		list<SpawnLoad::EnemySpawn> PushData;

		ifstream fileStream(f);
		assert(fileStream);

		int i = 0;

		while (!fileStream.eof())
		{
			i++;
			string bufferString;
			fileStream >> bufferString;

			//１行目をスキップ
			if (i <= 1)continue;

			istringstream stringStream(bufferString);
			vector<string> datas;
			string tmp;
			while (getline(stringStream, tmp, ',')) datas.push_back(tmp);
			if (datas.size() == 0) continue;

			EnemySpawn data;
			data.spawn_frame = strtof(datas[0].c_str(), NULL);
			data.x = strtof(datas[1].c_str(), NULL);
			data.y = strtof(datas[2].c_str(), NULL);

			auto mode = datas[3];
			if (mode == "w") data.mode = BWMode::ewhite;
			if (mode == "b") data.mode = BWMode::eblack;

			auto state = datas[4];
			if (state == "a") data.state = EnemyState::A;
			if (state == "b") data.state = EnemyState::B;
			if (state == "c") data.state = EnemyState::C;
			if (state == "d") data.state = EnemyState::D;
			if (state == "s") data.state = EnemyState::boss;
			
			DataTable.push_back(data);
		}
		fileStream.close();

		list<EnemySpawn> l(DataTable.begin(), DataTable.end());
		for (list<EnemySpawn>::iterator it = l.begin(); it != l.end(); it++) {
			PushData.push_back(*it);
		}
		return PushData;
	}
};