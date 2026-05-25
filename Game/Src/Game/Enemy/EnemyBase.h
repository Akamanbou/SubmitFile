#pragma once
#include"../../Lib/Object/Object.h"
#include"../Common.h"

static const char HP_BAR_IMAGE[] = { "../Data/Image/HpBar.png" };
static const int WALK_SPEED = 1.0f;
static const float IDEL_WALK_SPEED = 0.5f;
// 攻撃幅
static const int ENE_ATTACK = 20;

class EnemyBase : public Object
{
public:
	enum  EnemyState {
		Idel, // 待機
		Chase, // 追跡
		Attack, // 攻撃
		Dead, // 死亡
	};
private:
	EnemyState m_State;
	int m_HpHndl;

	int m_Type;
	int m_Hp;
	int m_Power;
	int m_Exp;
	int m_MoveDelay; // 動きに遅延をかける変数

	VECTOR m_AtPos;
	int m_AtTime;
	int m_AtCoolTime;

	float m_Len;

	bool m_Attack;

	void IdelMove(); // 待機状態の動き
	void ChaseMove(VECTOR pos); // 追跡状態の動き
	void AttackMove(VECTOR pos); // 攻撃の動き

	void PlRotAns(VECTOR pos);

public:
	// コンストラクタ・デストラクタ
	EnemyBase();
	virtual ~EnemyBase() = default;	// 初期化

	void Init();
	// ロード
	void Load(int originhndl,int hphandl);
	// 全処理
	void Step(VECTOR pos);
	// 描画
	void Draw();
	void DrawHpBar();

	bool Request();
	int Death(); // 死亡時に行う処理


	int GetType() { return m_Type; }
	int GetExp() { return m_Exp; }
	int GetHp() { return m_Hp; }
	int GetPower() { return m_Power; }

	bool GetAttack() { return m_Attack; }
	void SetAttack(bool at) { m_Attack = at; }

	VECTOR GetAtPos() { return m_AtPos; }

	void SetType(int type) { m_Type = type; }
	void SetHp(int hp) { m_Hp = hp; }
	void SetPower(int power) { m_Power = power; }
	void SetExp(int exp) { m_Exp = exp; }

	EnemyState GetState() { return m_State; }

};