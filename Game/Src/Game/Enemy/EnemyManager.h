#pragma once
#include"EnemyData.h"
#include"../Path.h"

class EnemyManager
{
private:
	EnemyData* m_Data;
public:
	EnemyManager();
	~EnemyManager();

	void Init();
	void Load();
	void Step();
	void Draw();
	void Exit();

	void Update();
	void Request();
};