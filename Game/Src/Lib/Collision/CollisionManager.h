#pragma once
#include"Collision.h"
#include"../../Game/Player/Player.h"
#include"../../Game/Field/Field.h"
#include"../../Game/Enemy/EnemyManager.h"

class CollisionManager {
public:
	// プレイヤーとフィールドの当たり判定
	bool CheckHitPlToField(Player player, int  hndl);

	// プレイヤーの攻撃と敵の当たり判定
	void CheckHitPlAttackToEnemy(Player& player, EnemyManager& enemy);
};
