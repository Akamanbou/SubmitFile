#include"EnemyManager.h"


// コンストラクタ
EnemyManager::EnemyManager()
{
	//Init();
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
		e->Init();
	}
}

// ロード
void EnemyManager::Load()
{
	// まずは何も入れない
	int Hndl = -1;

	m_Data->SetEnemyData();

	// ベースで受け取ったタイプの数字によってロードするモデルを変える
	for (const auto& e : m_Data->GetEnemyData())
	{
		switch (e->GetType())
		{
		case 0:
			Hndl = MV1LoadModel(MODEL_PATH[e->GetType()]);
			e->Load(Hndl);
			break;
		}
	}
	MV1DeleteModel(Hndl);
}

// 全行動
void EnemyManager::Step()
{
	for (auto e : m_Data->GetEnemyData())
	{
		e->Step();
	}
}

// 描画処理
void EnemyManager::Draw()
{
	for (auto e : m_Data->GetEnemyData())
	{
		e->Draw();
	}
}

// 終了時の破棄
void EnemyManager::Exit()
{
	for (auto e : m_Data->GetEnemyData())
	{
		e->Exit();
		delete e;
	}
}

// 更新処理
void EnemyManager::Update()
{
	for (auto e : m_Data->GetEnemyData())
	{
		e->Update();
	}
}

void EnemyManager::Request()
{
	for (auto e : m_Data->GetEnemyData())
	{
		e->Request();
	}
}
