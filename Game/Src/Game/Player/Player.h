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
// 攻撃幅
static const int PL_ATTACK = 20;
// 攻撃時間
static const int PL_AT_TIME = 60;

class Player : public Object {
public:
	enum  PlayerState {
		NormalState,	 // 動いている状態
		AttackState,
		PLSTATE_NUM		// 状態の総数
	};
private:
	PlayerState m_State; // プレイヤーの状態

	float m_JumpPow;		// ジャンプ力
	int m_Level;	// レベル
	int m_Power;	// 攻撃力
	int m_MaxHp;
	int m_Hp;
	int m_NowExp;	// 現在の経験量
	int m_WantExp;	// 必要経験値量

	VECTOR m_AtPos;
	int m_AtTime;
	int m_AtCoolTime;

	// 移動
	void Move(CameraManager& camera);
	void PadMove(CameraManager& camera);
	void Gravity();
	void Jump();
	void Attack();

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
	void HitCale(int power);

	void LevelUp();
	int GetPower() { return m_Power; }

	void Collision(bool hitField);

	VECTOR GetAtPos() { return m_AtPos; }

	void AddExp(int exp) { m_NowExp += exp; }

	PlayerState GetState() { return m_State; }
	void SetState(PlayerState state) { m_State = state; }
};