#pragma once
#include"EnemyBase.h"
#include<vector>
#include<DxLib.h>

using namespace std;

static const char ENEMY_CSV[] = { "../Data/CSV/Enemy.csv" };

class EnemyData
{
private:
	EnemyBase m_Base;

	struct ReadData
	{
		int m_Type;
		VECTOR m_Pos;
		int m_Hp;
		int m_Power;
		int m_Exp;
	};

	ReadData m_ReadData;

	vector<EnemyBase*>m_VEnemyData;

public:
	// クラスの中身を変更せず、コピーなし、変更禁止で返す関数
	const vector<EnemyData>& GetEnemyData();
};