#include"PlayScene.h"

//-----------------------------------
// コンストラクタ
//-----------------------------------
PlayScene::PlayScene()
{
	m_State = INIT;
}

//-----------------------------------
// デストラクタ
//-----------------------------------
PlayScene::~PlayScene()
{
	Exit();
}

//-----------------------------------
// 毎フレーム呼ぶ処理
//-----------------------------------
int PlayScene::Loop()
{
	// ゲームが終了したかを外部に伝えるため
	int Result = -1;

	switch (m_State)
	{
	case PlayScene::INIT:
		Init();
		m_State = LOAD; // 次へ進む
		break;
	case PlayScene::LOAD:
		Load();
		m_State = MAIN; // 次へ進む
		break;
	case PlayScene::MAIN:
		Step();
		break;
	case PlayScene::END:
		Exit();
		m_State = INIT; // 次へ進む
		Result = 0;
		break;
	case PlayScene::PLAY_SCENE_NUM:
		break;

	default:
		break;
	}

	// 本編が終了したかどうかを外部に伝える	
	return Result;
}

//-----------------------------------
// 描画処理
//-----------------------------------
void PlayScene::Draw()
{
	m_Player.Draw();
	m_Field.Draw();
}

//-----------------------------------
// 初期化
//-----------------------------------
void PlayScene::Init()
{
	m_Player.Init();
	m_Camera.Init();
	m_Field.Init();
}

//-----------------------------------
// データロード
//-----------------------------------
void PlayScene::Load()
{
	m_Player.Load();
	m_Field.Load();
	m_Enemy.Load();
}

//-----------------------------------
// 毎フレーム呼ぶ処理
//-----------------------------------
void PlayScene::Step()
{
	m_Player.Step(m_Camera);
	m_Camera.Step(m_Player.GetCenter(), m_Player.GetRotation().y);
	m_Field.Step();
	m_Enemy.Step();

	// 当たり判定-----------------------
	m_Player.Collision(m_Collision.CheckHitPlToField(m_Player, m_Field.GetHndl()));

	// 更新処理
	m_Player.Update();
	m_Camera.Updata();
	m_Field.Updata();
	m_Enemy.Update();
}

//-----------------------------------
// 終了処理
//-----------------------------------
void PlayScene::Exit()
{
	m_Player.Exit();
	m_Field.Exit();
	m_Enemy.Exit();
}