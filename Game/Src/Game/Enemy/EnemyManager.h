#pragma once
#include"EnemyData.h"
#include"EnemyBase.h"
#include"../Path.h"

class EnemyManager
{
private:
	EnemyData* m_Data;
	EnemyBase* m_Base;
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

	int GetNum() { return m_Data->GetEnemyData().size(); }
	EnemyBase* GetEnemyData(int id) { return m_Data->GetEnemyData()[id]; }
};