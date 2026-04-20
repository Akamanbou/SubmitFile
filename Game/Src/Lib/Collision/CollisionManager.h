#pragma once
#include"Collision.h"
#include"../../Game/Player/Player.h"
#include"../../Game/Field/Field.h"

class CollisionManager {
public:
	// プレイヤーとフィールドの当たり判定
	bool CheckHitPlToField(Player player, int  hndl);
};
