#pragma once
#include"EnemyBase.h"

class Robot :public EnemyBase
{
private:

public:
	Robot();
	~Robot();
	// 初期化
	void Init();
	// 全行動を処理する
	void Step();
	// ヒット後の処理
	void HitCale();
};