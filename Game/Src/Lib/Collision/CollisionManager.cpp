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