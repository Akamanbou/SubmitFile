#pragma once
#include"../Player/Player.h"
#include"../Enemy/EnemyManager.h"
#include"../Camera/CameraManager.h"
#include"../Field/Field.h"
#include"../../Lib/Collision/CollisionManager.h"

class PlayScene
{
private:
	enum tagScene {
		INIT,
		LOAD,
		MAIN,
		END,

		PLAY_SCENE_NUM
	};

	tagScene m_State; // 現在の状態遷移

	CollisionManager m_Collision; // 当たり判定

	Player m_Player; // プレイヤーの処理
	CameraManager m_Camera; // カメラの処理
	Field m_Field; // フィールドの処理
	EnemyManager m_Enemy; // 敵の処理

public:
	// コンストラクタ・デストラクタ
	PlayScene();
	~PlayScene();

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