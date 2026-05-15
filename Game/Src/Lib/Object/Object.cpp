#include"Object.h"

//----------------------
// コンストラクタ
//----------------------
Object::Object()
{
	Init();
}

//----------------------
// デストラクタ
//----------------------
Object::~Object()
{
	Exit();
}

//----------------------
// 初期化
//----------------------
void Object::Init()
{
	m_Pos = ZERO;
	m_Rot = ZERO;
	m_Speed = ZERO;
	m_Scale = { 1.0f,1.0f,1.0f };
	m_isActive = false;
	m_isHitGround = false;
	m_Radius = 0.0f;
	m_Hndl = -1;
}

//----------------------
// 終了時の破棄
//----------------------
void Object::Exit()
{
	//if (m_Hndl != -1)
	//{
	//	MV1DeleteModel(m_Hndl);
	//	m_Hndl = -1;
	//}
}

//------------------------
// 当たり判定の座標系
//------------------------
VECTOR Object::GetCenter()
{
	// 基本は物体の座標の位置
	VECTOR Res = m_Pos;
	// 高さだけ足元から球の半径分挙げる
	Res.y += m_Radius;

	return Res;
}

//----------------------
// 更新
//----------------------
void Object::Update()
{
	// 座標回転角度を設定する
	MV1SetRotationXYZ(m_Hndl, m_Rot);
	MV1SetPosition(m_Hndl, m_Pos);
	MV1SetScale(m_Hndl, m_Scale);
}