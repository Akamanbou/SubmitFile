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
		// 左クリックをするか、Bボタンを押したらゲームへ進む
		if (CInput::IsPush(MOUSE_LEFT) || CGamePad::IsPadPush(DX_INPUT_PAD1, BUTTON_B))
			m_State = END;
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
	DrawRotaGraph(WINDOW_SIZE_X / 2, WINDOW_SIZE_Y / 2, 1.0f, 0.0f, m_Hndl, true);
	DrawFormatString(20, 45, WHITE, "タイトル");

}

//-----------------------------------
// 初期化
//-----------------------------------
void TitleScene::Init()
{
	m_Hndl = -1;
}

//-----------------------------------
// データロード
//-----------------------------------
void TitleScene::Load()
{
	if (m_Hndl == -1)
		m_Hndl = LoadGraph(TITLE_IMAGE);
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