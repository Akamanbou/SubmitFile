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

	int m_Type;
	int m_Hp;
	int m_Power;
	int m_Exp;

	void IdelMove(); // 待機状態の動き
	void ChaseMove(); // 追跡状態の動き
	void AttackMove(); // 攻撃の動き


public:
	// コンストラクタ・デストラクタ
	EnemyBase();
	virtual ~EnemyBase() = default;	// 初期化

	void Init();
	// ロード
	void Load(int originhndl);
	// 全処理
	void Step();
	// 描画
	void Draw();

	bool Request();
	int Death(); // 死亡時に行う処理


	int GetType() { return m_Type; }
	int GetExp() { return m_Exp; }

	void SetType(int type) { m_Type = type; }
	void SetHp(int hp) { m_Hp = hp; }
	void SetPower(int power) { m_Power = power; }
	void SetExp(int exp) { m_Exp = exp; }

};