#include"Zombie.h"

// コンストラクタ
Zombie::Zombie()
{
	Init();
}

// デストラクタ
Zombie::~Zombie()
{
	Exit();
}

// 初期化
void Zombie::Init()
{

}

// 全行動を処理する
void Zombie::Step()
{

}

// ヒット後の処理
void Zombie::HitCale()
{
	m_isActive = false;
}