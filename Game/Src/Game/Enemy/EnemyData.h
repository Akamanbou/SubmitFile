#pragma once
#include"EnemyBase.h"
#include"Zombie.h"
#include"Robot.h"
#include<vector>
#include<DxLib.h>

using namespace std;

static const char ENEMY_CSV[] =  "../Data/CSV/Enemy.csv" ;

class EnemyData
{
private:
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
	~EnemyData();

	void SetEnemyData();
	// クラスの中身を変更せず、コピーなし、変更禁止で返す関数
	const vector<EnemyBase*>& GetEnemyData()const;
};