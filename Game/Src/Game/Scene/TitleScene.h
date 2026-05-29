#pragma once
#include<DxLib.h>
#include"../Common.h"
#include"../../Lib/Input/Input.h"
#include"../../Lib/Input/PadInput.h"

static const char TITLE_IMAGE[] = { "../Data/Image/RPGTitle.png" };


class TitleScene
{
private:
	enum tagScene {
		INIT,
		LOAD,
		MAIN,
		END,

		TITLE_SCENE_NUM
	};

	tagScene m_State; // 現在の状態遷移

public:
	// コンストラクタ・デストラクタ
	TitleScene();
	~TitleScene();

	int m_Hndl;

	// 繰り返し行う処理
	int Loop();
	// 描画処理
	void Draw();

private:
	// 初期化
	void Init(void);
	// 終了処理
	void Exit();
	// データロード
	void Load();
	// 毎フレーム呼ぶ処理
	void Step();
};