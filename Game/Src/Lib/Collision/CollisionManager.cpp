#include"CollisionManager.h"

bool CollisionManager::CheckHitPlToField(Player player, int hndl)
{
	VECTOR Result = { 0.0f };
	VECTOR Center = player.GetCenter();
	float Radius = player.GetRadius();
	// 当たり判定情報が格納される構造体
	MV1_COLL_RESULT_POLY_DIM Col;


	VECTOR Pos = MV1GetPosition(hndl);

	// ポリゴンと球の当たり判定
	Col = MV1CollCheck_Sphere(hndl, -1, Center, Radius);
	// ポリゴンと当たっていた
	if (Col.HitNum != 0)
	{
		// 当たったデータすべてをチェックする
		for (int i = 0; i < Col.HitNum; i++)
		{
			// まずは中心点から最近点を引き算
			VECTOR v = VSub(Center, Col.Dim[i].HitPosition);
			// 取得したベクトルを三平方の定理で長さに変換
			float Len = VSize(v);
			// 実際にめり込んだ距離を計算
			Len = Radius - Len;
			// 法線をめり込んだ距離分掛け算する
			v = VScale(Col.Dim[i].Normal, Len);
			// 計算結果を合成していく
			Result = VAdd(Result, v);

			// 地面判定
			if (Col.Dim[i].Normal.y >= 0.5f)
			{
				// 毎回データを削除
				MV1CollResultPolyDimTerminate(Col);

				Result.y -= 0.1;

				player.SetPosition(VAdd(player.GetPosition(), Result));

				return true;
			}
		}
		// 毎回データを削除
		MV1CollResultPolyDimTerminate(Col);

		player.SetPosition(VAdd(player.GetPosition(), Result));
	}
	return false;
}

// プレイヤーの攻撃と敵の当たり判定
void CollisionManager::CheckHitPlAttackToEnemy(Player& player, EnemyManager& enemy)
{
	for (int EnemyID = 0;EnemyID < enemy.GetNum();EnemyID++)
	{
		EnemyBase* OneEnemy = enemy.GetEnemyData(EnemyID);
		if (!OneEnemy->IsActive())continue;

		VECTOR EnemyPos = OneEnemy->GetCenter();
		float EnemyRad = OneEnemy->GetRadius();
		VECTOR PlayerPos = player.GetAtPos();
		float PlayerRad = player.GetRadius();

		bool isHit = Collision::CheckHitSphereToSphere(PlayerPos, PlayerRad, EnemyPos, EnemyRad);

		if (isHit && player.GetState() == Player::AttackState)
		{
			OneEnemy->SetHp(OneEnemy->GetHp() - player.GetPower());

			if (OneEnemy->GetHp() <= 0)
				player.AddExp(OneEnemy->GetExp());
			player.SetState(Player::NormalState);
		}
	}
}

// 敵の攻撃とプレイヤーの当たり判定
void CollisionManager::CheckHitEnemyAttackToPl(Player& player, EnemyManager& enemy)
{
	for (int EnemyID = 0;EnemyID < enemy.GetNum();EnemyID++)
	{
		EnemyBase* OneEnemy = enemy.GetEnemyData(EnemyID);
		if (!OneEnemy->IsActive())continue;

		VECTOR EnemyAtPos = OneEnemy->GetAtPos();
		float EnemyAtRad = OneEnemy->GetRadius();
		VECTOR PlayerPos = player.GetAtPos();
		float PlayerRad = player.GetRadius();

		bool isHit = Collision::CheckHitSphereToSphere(PlayerPos, PlayerRad, EnemyAtPos, EnemyAtRad);

		if (isHit && OneEnemy->GetAttack() == true)
		{
			player.HitCale(OneEnemy->GetPower());
			OneEnemy->SetAttack(false);
		}
	}
}

// 敵同士の弾き判定
void CollisionManager::CheckHitEnemyToEnemyPick(EnemyManager& enemy, Player& player)
{
	int HitIndex1 = -1;
	int HitIndex2 = -1;

	for (int i = 0; i < enemy.GetNum(); i++)
	{
		// ウサギ一体分の情報を取得し、生存確認
		EnemyBase* OneEnemy = enemy.GetEnemyData(i);
		if (!OneEnemy->IsActive())continue;

		for (int j = 0; j < enemy.GetNum(); j++)
		{
			// 最初のループと同じ数だったら比べない
			if (i == j)continue;

			// ウサギ一体分の情報を取得し、生存確認
			EnemyBase* TwoEnemy = enemy.GetEnemyData(j);
			if (!TwoEnemy->IsActive())continue;

			// それぞれの座標と半径
			VECTOR OneEnemyPos = OneEnemy->GetCenter();
			float OneEnemyRadius = OneEnemy->GetRadius();
			VECTOR TwoEnemyPos = TwoEnemy->GetCenter();
			float TwoEnemyRadius = TwoEnemy->GetRadius();

			// 当たり判定開始
			bool isHit = Collision::CheckHitSphereToSphere(OneEnemyPos, OneEnemyRadius, TwoEnemyPos, TwoEnemyRadius);

			// 当たった時に先に誕生したウサギと後に誕生したウサギがどちらもはじき処理を行うように
			if (HitIndex1 == j && HitIndex2 == i)
			{
				isHit = true;
				HitIndex1 = -1;
				HitIndex2 = -1;
			}
			if (isHit)
			{
				HitIndex1 = j;
				HitIndex2 = i;
				// 当たっていたら、各軸のめりこんでいる距離を出す
				VECTOR v = VSub(OneEnemy->GetPosition(), TwoEnemy->GetPosition());
				v.x = 1.0f - fabsf(v.x);
				v.z = 1.0f - fabsf(v.z);

				// 各軸の押し戻し方向を確定
				if (OneEnemy->GetPosition().x > TwoEnemy->GetPosition().x)v.x *= -1.0f;
				if (OneEnemy->GetPosition().z > TwoEnemy->GetPosition().z)v.z *= -1.0f;

				// ウサギが弾き処理を行うときにプレイヤーの方向を向かせる
				float x = player.GetPosition().x;
				float z = player.GetPosition().z;
				VECTOR Rot = ZERO;

				Rot.x = x - OneEnemy->GetPosition().x;
				Rot.y = 0.0f;
				Rot.z = z - OneEnemy->GetPosition().z;
				OneEnemy->SetRotation(VGet(OneEnemy->GetRotation().x, atan2(-Rot.x, -Rot.z), OneEnemy->GetRotation().z));

				// 動いていないとき弾きの強さ
				if (!OneEnemy->GetState() == EnemyBase::Idel)
				{
					v.x *= 0.08f;
					v.z *= 0.08f;
				}
				// 動いているときの弾きの強さ
				if (OneEnemy->GetState() == EnemyBase::Chase || OneEnemy->GetState() == EnemyBase::Attack)
				{
					v.x *= 0.3f;
					v.z *= 0.3f;
				}

				// 押し戻した距離を加算
				v.y = 0.0f;
				OneEnemy->SetPosition(VAdd(OneEnemy->GetPosition(), v));
			}
		}
	}
}
