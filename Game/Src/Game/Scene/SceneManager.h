#pragma once
#include"PlayScene.h"
#include"TitleScene.h"
#include"ResultScene.h"
#include"../../Lib/Input/Input.h"
#include"../../Lib/Input/PadInput.h"

class SceneManager
{
private:
	// ゲームの処理の流れ
	enum tagScene {
		INIT,
		TITLE,
		GAME,
		RESULT
	};

	PlayScene m_Play;
	TitleScene m_Title;
	ResultScene m_Result;
	tagScene m_SceneID; // シーン保存

public:
	// コンストラクタ
	SceneManager();

	// 実行処理
	int Loop();
	// 描画処理
	void Draw();
};