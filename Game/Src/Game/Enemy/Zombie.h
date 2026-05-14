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
	// モデルデータのロード
	void Load(int originhdnl);
	// 全行動を処理する
	void Step();
	// 描画処理
	void Draw();
	// ヒット後の処理
	void HitCale();
};