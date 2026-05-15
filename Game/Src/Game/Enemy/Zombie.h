#pragma once
#include"EnemyBase.h"

static const char;

class Zombie : public EnemyBase
{
private:

public:
	Zombie();
	~Zombie();

	// 初期化
	void Init();
	// 全行動を処理する
	void Step();
	// ヒット後の処理
	void HitCale();
};