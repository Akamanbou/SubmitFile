#include"SceneManager.h"

//-----------------------------------
// コンストラクタ
//-----------------------------------
SceneManager::SceneManager()
{
	m_SceneID = INIT;
	CInput::InitInput();
	CGamePad::InitGamePad();
	CGamePad::GetPadNumState();
}

//-----------------------------------
// 毎フレーム呼ぶ処理
//-----------------------------------
int SceneManager::Loop()
{
	// ゲームが終了したかを外部に伝えるため
	int Result = -1;

	// キーマウとコントローラーのステップ
	CInput::StepInput();
	CGamePad::StepGamePad();

	// ここでシーンを管理する
	switch (m_SceneID)
	{
	case SceneManager::INIT:
		m_SceneID = TITLE;
		break;
		// タイトル
	case SceneManager::TITLE:
		m_Title.Loop();
		// 左クリックをするか、Bボタンを押したらゲームへ進む
		if (CInput::IsPush(MOUSE_LEFT) || CGamePad::IsPadPush(DX_INPUT_PAD1, BUTTON_B))
			m_SceneID = GAME;
		break;
		// メインゲーム
	case SceneManager::GAME:
		// ループが終わったら次へ
		// 左クリックをするか、Bボタンを押したらゲームへ進む
		if (m_Play.Loop() != -1)
			m_SceneID = RESULT;
		break;
		// リザルト
	case SceneManager::RESULT:
		m_Result.Loop();
		// 左クリックをするか、Bボタンを押したらInitへ進む
		if (CInput::IsPush(MOUSE_LEFT) || CGamePad::IsPadPush(DX_INPUT_PAD1, BUTTON_B))
			m_SceneID = INIT;
		break;
	}

	// 本編が終了したかどうかを外部に伝える
	return Result;
}

//-----------------------------------
// 描画処理
//-----------------------------------
void SceneManager::Draw()
{
	// それぞれのシーンで描画するもの
	switch (m_SceneID)
	{
	case SceneManager::INIT:
		break;
	case SceneManager::TITLE:
		m_Title.Draw();
		break;
	case SceneManager::GAME:
		m_Play.Draw();
		break;
	case SceneManager::RESULT:
		m_Result.Draw();
		break;
	}
}
