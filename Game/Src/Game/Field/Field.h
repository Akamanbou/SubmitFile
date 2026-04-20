#pragma once
#include"../../Lib/Object/Object.h"

class Field :public Object {
private:
	int m_DemoHndl;

	VECTOR m_SkyPos;
	VECTOR m_SkyScale;
	int m_SkyHndl;


public:
	// コンストラクタ・デストラクタ
	Field();
	~Field();

	// 初期化
	void Init();
	// モデルのロード
	void Load();
	// 終了処理
	void Exit();
	// 全行動を処理する
	void Step();
	// 更新処理
	void Updata();
	// 描画処理
	void Draw();

	int GetHndl() { return m_Hndl; }
};