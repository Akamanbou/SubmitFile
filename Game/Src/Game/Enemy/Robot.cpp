#include"Robot.h"
// コンストラクタ
Robot::Robot()
{
	Init();
}

// デストラクタ
Robot::~Robot()
{
	Exit();
}

// 初期化
void Robot::Init()
{

}

// 全行動を処理する
void Robot::Step()
{

}

// ヒット後の処理
void Robot::HitCale()
{
	m_isActive = false;
}