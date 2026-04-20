#pragma once
#include<DxLib.h>
#include<math.h>
#include"../../Lib/Object/Object.h"
#include"../../Lib/MyMath/MyMath.h"
#include"../../Lib/input/Input.h"
#include"../Camera/CameraManager.h"


// プレイヤーのモデルのパス
static const char PLAYER_MODEL_PATH[] = "../Data/Model/Player/PlayerMove.mv1";
// プレイヤーの回転速度
static const float PL_ROTATION_SPEED = 0.1f;
// プレイヤーの進む速度
static const float PL_WALK_SPEED = 2.3f;// 1.5f
// 右斜め前移動の角度
static const int PL_RIGHT_FRONT = 45;
// 右斜め後移動の角度
static const int PL_RIGHT_BACK = 135;
// 左斜め後移動の角度
static const int PL_LEFT_BACK = 225;
// 左斜め前移動の角度
static const int PL_LEFT_FRONT = 315;
// 上移動の角度
static const int PL_FRONT = 0;
// 下移動の角度
static const int PL_BACK = 180;
// 右移動の角度
static const int PL_RIGHT = 90;
// 左移動の角度
static const int PL_LEFT = 270;

class Player : public Object {
public:
	enum  PlayerState {
		MoveState,	 // 動いている状態

		PLSTATE_NUM		// 状態の総数
	};
private:
	PlayerState m_State; // プレイヤーの状態

	float m_JumpPow;		// ジャンプ力

	// 移動
	void Move(CameraManager& camera);
	void PadMove(CameraManager& camera);
	void Gravity();
	void Jump();

public:
	// コンストラクタ・デストラクタ
	Player();
	~Player();

	// 初期化
	void Init();
	// モデルデータのロード
	void Load();
	// 全行動を処理する
	void Step(CameraManager& Camera);
	// 描画処理
	void Draw();
	// ヒット後の処理
	void HitCale();

	void Collision(bool hitField);


	PlayerState GetState() { return m_State; }
	void SetState(PlayerState state) { m_State = state; }
};