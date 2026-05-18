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
	m_Radius = 50;
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
void EnemyBase::Step()
{
	// 存在していなかったらこれ以上先に行かない
	if (!m_isActive)return;

	switch (m_State)
	{
	case EnemyBase::Idel:
		IdelMove();
		break;
	case EnemyBase::Chase:
		ChaseMove();
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

void EnemyBase::IdelMove() {
}
void EnemyBase::ChaseMove() {
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