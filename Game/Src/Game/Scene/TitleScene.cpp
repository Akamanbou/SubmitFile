#include"TitleScene.h"

//-----------------------------------
// コンストラクタ
//-----------------------------------
TitleScene::TitleScene()
{
	m_State = INIT;
}

//-----------------------------------
// デストラクタ
//-----------------------------------
TitleScene::~TitleScene()
{
	Exit();
}

//-----------------------------------
// 毎フレーム呼ぶ処理
//-----------------------------------
int TitleScene::Loop()
{
	// ゲームが終了したかを外部に伝えるため
	int Result = -1;

	switch (m_State)
	{
	case TitleScene::INIT:
		Init();
		m_State = LOAD; // 次へ進む
		break;
	case TitleScene::LOAD:
		Load();
		m_State = MAIN; // 次へ進む
		break;
	case TitleScene::MAIN:
		Step();
		m_State = END; // 次へ進む
		break;
	case TitleScene::END:
		Exit();
		m_State = INIT; //次へ進む
		Result = 0;
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
void TitleScene::Draw()
{
	// タイトル中にタイトルと描画するようにする
	DrawFormatString(20, 45, WHITE, "タイトル");
}

//-----------------------------------
// 初期化
//-----------------------------------
void TitleScene::Init()
{
}

//-----------------------------------
// データロード
//-----------------------------------
void TitleScene::Load()
{
}

//-----------------------------------
// 毎フレーム呼ぶ処理
//-----------------------------------
void TitleScene::Step()
{
}

//-----------------------------------
// 終了処理
//-----------------------------------
void TitleScene::Exit()
{
}