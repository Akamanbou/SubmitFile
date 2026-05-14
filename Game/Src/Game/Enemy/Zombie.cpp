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

// モデルデータのロード
void Zombie::Load(int originhndl)
{
	// ロードされていなければする
	if (m_Hndl == -1)
	{
		// 複数体出てくるときはこの関数を使う
		m_Hndl = MV1DuplicateModel(originhndl);
	}
}

// 全行動を処理する
void Zombie::Step()
{

}

// 描画処理
void Zombie::Draw()
{
	MV1DrawModel(m_Hndl);
}

// ヒット後の処理
void Zombie::HitCale()
{
	m_isActive = false;
}