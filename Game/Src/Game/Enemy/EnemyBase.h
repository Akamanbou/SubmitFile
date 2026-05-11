#pragma once
#include"../../Lib/Object/Object.h"
#include"../Common.h"

static const int WALK_SPEED = 1.0f;

class EnemyBase : public Object
{
private:
	enum  tagState {
		Idel, // 待機
		Chase, // 追跡
		Attack, // 攻撃
		Dead, // 死亡
	};

	tagState m_State;

	int m_Hp;
	int m_Power;
	int m_Exp;

	void IdelMove(); // 待機状態の動き
	void ChaseMove(); // 追跡状態の動き
	void AttackMove(); // 攻撃の動き

public:
	// コンストラクタ・デストラクタ
	EnemyBase();
	~EnemyBase();
	// 初期化
	void Init();
	// ロード
	void Load(int originhndl);
	// 全処理
	void Step();
	// 描画
	void Draw();

	int SetHp(int hp) { m_Hp = hp; }
	int SetPower(int power) { m_Power = power; }
	int SetExp(int exp) { m_Exp = exp; }
};