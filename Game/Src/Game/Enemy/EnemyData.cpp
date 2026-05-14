#include"EnemyData.h"

EnemyData::~EnemyData() {
	for (auto enemy : m_VEnemyData)
	{
		delete enemy;
	}

	m_VEnemyData.clear();
}

void EnemyData::SetEnemyData()
{

	printf("%p\n", this);

	int hndl = FileRead_open(ENEMY_CSV);

	if (hndl == -1)
	{
		return;
	}

	ReadData tmp = { 0 };

	while (FileRead_scanf(hndl,
	    "%d,%f,%f,%f,%d,%d,%d",
	    &tmp.m_Type,
	    &tmp.m_Pos.x,
	    &tmp.m_Pos.y,
	    &tmp.m_Pos.z,
	    &tmp.m_Hp,
	    &tmp.m_Power,
	    &tmp.m_Exp) != EOF)
	{
	    EnemyBase* temp = nullptr;

	    switch (tmp.m_Type)
	    {
	    case 0:
	        temp = new Zombie();
	        break;
	    }

	    temp->SetType(tmp.m_Type);
	    temp->SetPosition(tmp.m_Pos);
	    temp->SetHp(tmp.m_Hp);
	    temp->SetPower(tmp.m_Power);
	    temp->SetExp(tmp.m_Exp);

	    m_VEnemyData.push_back(temp);
	}
}

const vector<EnemyBase*>& EnemyData::GetEnemyData()const
{
	return m_VEnemyData;
}
