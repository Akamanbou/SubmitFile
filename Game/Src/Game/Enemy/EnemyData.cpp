#include"EnemyData.h"

const vector<EnemyData>& EnemyData::GetEnemyData()
{
	// CSVƒtƒ@ƒCƒ‹‚ð“ü‚ê‚é
	int hndl = FileRead_open(ENEMY_CSV);

	// ‚O‚ð“ü‚ê‚Ä‚¢‚­
	ReadData tmp = { 0 };

	// ‚O‚É‚È‚é‚Ü‚Å‰ñ‚è‘±‚¯‚é
	while (FileRead_scanf(hndl, "%c,%f,%f,%f,%d,%d,%d", &tmp.m_Type, &tmp.m_Pos.x, &tmp.m_Pos.y, &tmp.m_Pos.z,
		&tmp.m_Hp, &tmp.m_Power, &tmp.m_Exp) != EOF) 
	{
		EnemyBase* temp = nullptr;

		m_Base.SetPosition(tmp.m_Pos);
		m_Base.SetHp(tmp.m_Hp);
		m_Base.SetPower(tmp.m_Power);
		m_Base.SetExp(tmp.m_Exp);
	}
}