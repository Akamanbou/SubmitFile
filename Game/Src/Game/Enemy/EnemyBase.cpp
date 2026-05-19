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
	m_State = Idel;
	m_isActive = true;
	m_Radius = 30;

	m_MoveDelay = 120;
}

//----------------------
// ロード
//----------------------
void EnemyBase::Load(int originhndl)
{
	if (m_Hndl == -1)
	{
		// 複数出てくるためこの関数
		m_Hndl = MV1DuplicateModel(originhndl);
	}
}

//----------------------
// 全処理
//----------------------
void EnemyBase::Step(VECTOR pos)
{
	// 存在していなかったらこれ以上先に行かない
	if (!m_isActive)return;

	// 毎フレーム引いていく
	m_MoveDelay--;

	// プレイヤーとの距離を計算する
	float Len = 0.0f;

	// 距離の計算
	Len = (pos.x - m_Pos.x) * (pos.x - m_Pos.x) + (pos.z - m_Pos.z) * (pos.z - m_Pos.z); // それぞれの 終点-始点 を計算する
	Len = sqrtf(Len); // √をとってフロート型にするためにsqrtfをする

	// 一定距離以内に来たらプレイヤーに近づいてくる
	if (Len <= 100)
		m_State = Chase;
	else
		m_State = Idel;

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
		AttackMove();
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
		//DrawSphere3D(GetCenter(), m_Radius, 16, RED, GetColor(255, 0, 255), true);
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
		m_MoveDelay = GetRand(100) + 60; // +の値は止まる時間の下限の値
	}

	// 止まる時間
	if (m_MoveDelay <= 60)
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
void EnemyBase::AttackMove() {

}

int EnemyBase::Death()
{
	if (!m_isActive)
	{
		return m_Exp;
	}
}