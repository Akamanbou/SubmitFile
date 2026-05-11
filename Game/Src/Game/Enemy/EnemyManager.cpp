#include"EnemyManager.h"


// コンストラクタ
EnemyManager::EnemyManager()
{
	Init();
}

// デストラクタ
EnemyManager::~EnemyManager()
{
	Exit();
}

// 初期化
void EnemyManager::Init()
{
	for (auto e : m_Data->GetEnemyData())
	{
		m_Base.Init();
	}
}

// ロード
void EnemyManager::Load()
{
}