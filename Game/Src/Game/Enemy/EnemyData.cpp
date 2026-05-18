#include"EnemyData.h"

EnemyData::~EnemyData() {
	// 念のためデストラクタでクリアしておく
	m_VEnemyData.clear();
}

void EnemyData::SetEnemyData()
{
	// CSVファイルを開く
	int hndl = FileRead_open(ENEMY_CSV);

	// 何も入っていなかったらリターン
	if (hndl == -1)
	{
		return;
	}

	// 初期化
	ReadData Data = { 0 };

	// 文字が入っていると動き続ける
	while (FileRead_scanf(hndl,
	    "%d,%f,%f,%f,%d,%d,%d",
	    &Data.m_Type,
	    &Data.m_Pos.x,
	    &Data.m_Pos.y,
	    &Data.m_Pos.z,
	    &Data.m_Hp,
	    &Data.m_Power,
	    &Data.m_Exp) != EOF)
	{
		// ポインタを作り初期化
	    EnemyBase* temp = nullptr;

		// Typeに入っている数字で変える
	    switch (Data.m_Type)
	    {
	    case 0:
	        temp = new Zombie();
	        break;
		case 1:
			temp = new Robot();
			break;
		default:
			return;
	    }

		// それぞれ数値を入れていく
	    temp->SetType(Data.m_Type);
	    temp->SetPosition(Data.m_Pos);
	    temp->SetHp(Data.m_Hp);
	    temp->SetPower(Data.m_Power);
	    temp->SetExp(Data.m_Exp);

		// ここまで来たらプッシュバックして次へ
	    m_VEnemyData.push_back(temp);
	}
}

const vector<EnemyBase*> EnemyData::GetEnemyData()const
{
	return m_VEnemyData;
}
