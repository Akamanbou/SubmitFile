#include"EnemyFactory.h"

Enemy* EnemyFactory::CreateEnemy(const string& type, int x, int z)
{
	// newでクラスのインスタンスを作る
	if (type == "Normal")return new Enemy(x, z);

	// 存在していなかったら
	return nullptr;
}