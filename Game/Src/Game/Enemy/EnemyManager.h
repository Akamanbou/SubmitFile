#pragma once
#include"EnemyBase.h"
#include"EnemyData.h"
#include"../Path.h"

class EnemyManager
{
private:
	EnemyData* m_Data;
	EnemyBase m_Base;
public:
	EnemyManager();
	~EnemyManager();

	void Init();
	void Load();
	void Step();
	void Draw();
	void Exit();

	void Request();
};