#include"EnemyBase.h"

//----------------------
// コンストラクタ
//----------------------
EnemyBase::EnemyBase()
{
	Init();
}

//----------------------
// デストラクタ
//----------------------
//EnemyBase::~EnemyBase()
//{
//	Exit();
//}

//----------------------
// 初期化
//----------------------
void EnemyBase::Init()
{
	m_HpHndl = -1;

	m_State = Idel;
	m_isActive = true;
	m_Radius = 13;

	m_MoveDelay = 120;

	m_AtPos = ZERO;
	m_AtCoolTime = 0;
	m_AtTime = 0;

	m_Len = 0.0f;

	m_Attack = false;
}

//----------------------
// ロード
//----------------------
void EnemyBase::Load(int originhndl,int hphndl)
{
	if (m_Hndl == -1)
	{
		// 複数出てくるためこの関数
		m_Hndl = MV1DuplicateModel(originhndl);
	}
	if (m_HpHndl == -1)
	{
		m_HpHndl = MV1DuplicateModel(hphndl);
	}
}

//----------------------
// 全処理
//----------------------
void EnemyBase::Step(VECTOR pos)
{
	// 存在していなかったらこれ以上先に行かない
	if (!m_isActive)return;

	if (m_Hp <= 0)
		m_isActive = false;
	// 毎フレーム引いていく
	m_MoveDelay--;

	// プレイヤーとの距離を計算する
	float Len = 0.0f;

	// 距離の計算
	Len = (pos.x - m_Pos.x) * (pos.x - m_Pos.x) + (pos.z - m_Pos.z) * (pos.z - m_Pos.z); // それぞれの 終点-始点 を計算する
	Len = sqrtf(Len); // √をとってフロート型にするためにsqrtfをする
	AttackMove(pos);

	// 一定距離以内に来たらプレイヤーに近づいてくる
	if (Len <= 100)
		m_State = Chase;
	else
		m_State = Idel;

	if (Len <= ENE_ATTACK)
	{
		m_State = Attack;
	}


	switch (m_State)
	{
	case EnemyBase::Idel:
	{
		int CoolTime = 0;
		IdelMove();
		break;
	}
	case EnemyBase::Chase:
		ChaseMove(pos);
		break;
	case EnemyBase::Attack:
		m_AtCoolTime++;

		PlRotAns(pos);
		if (m_AtCoolTime >= 60)
		{
			m_Attack = true;
			m_AtCoolTime = 0;
		}
		if (Len >= ENE_ATTACK)
		{
			m_State = Chase;
		}
		break;
	case EnemyBase::Dead:
		break;
	}
}

//----------------------
// 描画
//----------------------
void EnemyBase::Draw()
{
	if (m_isActive)
	{
		MV1DrawModel(m_Hndl);
		DrawSphere3D(GetCenter(), 10.0f, m_Radius, RED, GetColor(255, 0, 255), true);
	}
}

//----------------------
// Hpバー描画
//----------------------
void EnemyBase::DrawHpBar()
{
	if (m_isActive)
	{
		VECTOR Pos = GetCenter();
		Pos.y += 50.0f;

		SetUseZBuffer3D(TRUE);
		SetWriteZBuffer3D(TRUE);
		DrawBillboard3D(Pos, 0.5f, 0.1f, 0.0f, 0.0f, m_HpHndl, TRUE);
	}
}

bool EnemyBase::Request()
{
	// すでに出現したウサギは生成失敗
	if (m_isActive)return false;

	// 必要な情報を渡していく
	m_isActive = true;

	return true;
}

void EnemyBase::IdelMove()
{
	// 待機状態では範囲内をランダムで移動させる

	float Speed = 0.0f;
	Speed -= IDEL_WALK_SPEED; // 実際の移動速度

	if (m_MoveDelay <= 0)
	{
		m_Rot.y = GetRand(360);
		m_MoveDelay = GetRand(100) + 120; // +の値は止まる時間の下限の値
	}

	// 止まる時間
	if (m_MoveDelay <= 120)
	{
		// 移動計算
		m_Speed.x = sinf(m_Rot.y) * Speed;
		m_Speed.z = cosf(m_Rot.y) * Speed;
		m_Pos = VAdd(m_Pos, m_Speed);
	}
}

void EnemyBase::ChaseMove(VECTOR pos)
{
	float x = pos.x;
	float z = pos.z;

	// 進む距離を計算する
	m_Speed.x = x - m_Pos.x;
	m_Speed.z = z - m_Pos.z;
	m_Rot.y = atan2(-m_Speed.x, -m_Speed.z);
	// 方向ベクトルの長さを計算
	m_Speed.x = -sinf(m_Rot.y) * WALK_SPEED;
	m_Speed.z = -cosf(m_Rot.y) * WALK_SPEED;
	m_Pos = VAdd(m_Pos, m_Speed);
}
void EnemyBase::AttackMove(VECTOR pos)
{
	// プレイヤーに近づく距離を計算する
	m_AtPos.x = sinf(m_Rot.y) * -ENE_ATTACK; // sinfでX方向の成分を計算（プレイヤーの後をついていくために-RBPL_LENをかける）
	m_AtPos.y = 0.0f;
	m_AtPos.z = cosf(m_Rot.y) * -ENE_ATTACK; // cosfでZ方向の成分を計算（プレイヤーの後をついていくために-RBPL_LENをかける）
	m_AtPos = VAdd(m_Pos, m_AtPos); // 今のポスに足す
}

int EnemyBase::Death()
{
	if (!m_isActive)
	{
		return m_Exp;
	}
}

void EnemyBase::PlRotAns(VECTOR Pos)
{
	float x = Pos.x;
	float z = Pos.z;

	// 進む距離を計算する
	m_Speed.x = x - m_Pos.x;
	m_Speed.z = z - m_Pos.z;
	m_Rot.y = atan2(-m_Speed.x, -m_Speed.z);
}
