#include"ResultScene.h"

//-----------------------------------
// コンストラクタ
//-----------------------------------
ResultScene::ResultScene()
{
	m_State = INIT;
}

//-----------------------------------
// デストラクタ
//-----------------------------------
ResultScene::~ResultScene()
{
	Exit();
}

//-----------------------------------
// 毎フレーム呼ぶ処理
//-----------------------------------
int ResultScene::Loop()
{
	// ゲームが終了したかを外部に伝えるため
	int Result = -1;

	switch (m_State)
	{
	case ResultScene::INIT:
		Init();
		m_State = LOAD; // 次へ進む
		break;
	case ResultScene::LOAD:
		Load();
		m_State = MAIN; // 次へ進む
		break;
	case ResultScene::MAIN:
		Step();
		m_State = END; // 次へ進む
		break;
	case ResultScene::END:
		Exit();
		m_State = INIT; // 次へ進む
		Result = 0;
		break;
	default:
		break;
	}

	// 本編が終了したかを外部に伝える
	return Result;
}

//-----------------------------------
// 描画処理
//-----------------------------------
void ResultScene::Draw()
{
	DrawFormatString(20, 45, WHITE, "リザルト");
}

//-----------------------------------
// 初期化
//-----------------------------------
void ResultScene::Init()
{
}

//-----------------------------------
// データロード
//-----------------------------------
void ResultScene::Load()
{
}

//-----------------------------------
// 毎フレーム呼ぶ処理
//-----------------------------------
void ResultScene::Step()
{
}

//-----------------------------------
// 終了処理
//-----------------------------------
void ResultScene::Exit()
{
}