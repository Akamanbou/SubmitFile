#include"EnemyManager.h"


// コンストラクタ
EnemyManager::EnemyManager()
{
	// コンストラクタでm_Dataにnewしておく
	m_Data = new EnemyData();
}

// デストラクタ
EnemyManager::~EnemyManager()
{
	/*Exit();*/
}

void EnemyManager::ReStart()
{
	m_Data = new EnemyData();
}

// 初期化
void EnemyManager::Init()
{
	for (auto e : m_Data->GetEnemyData())
	{
		m_Data = new EnemyData();
	}
}

// ロード
void EnemyManager::Load()
{
	// まずは何も入れない
	int Hndl = -1;
	int HpHndl = -1;

	m_Data->SetEnemyData();

	// ベースで受け取ったタイプの数字によってロードするモデルを変える
	for (const auto& e : m_Data->GetEnemyData())
	{
		switch (e->GetType())
		{
		case 0:
			Hndl = MV1LoadModel(MODEL_PATH[e->GetType()]);
			break;
		case 1:
			Hndl = MV1LoadModel(MODEL_PATH[e->GetType()]);
			break;
		}
		e->Init();
		e->Load(Hndl);
	}
	MV1DeleteModel(Hndl);
}

// 全行動
void EnemyManager::Step(VECTOR pos)
{
	for (auto e : m_Data->GetEnemyData())
	{
		e->Step(pos);
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
	}
	delete m_Data;
}

// 更新処理
void EnemyManager::Update()
{
	for (auto e : m_Data->GetEnemyData())
	{
		e->Update();
	}
}

// リクエスト
void EnemyManager::Request()
{
	for (auto e : m_Data->GetEnemyData())
	{
		e->Request();
	}
}
