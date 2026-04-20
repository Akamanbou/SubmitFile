#pragma once
#include<iostream>
#include<DxLib.h>
#include"../../Game/Common.h"

// 基底クラス
class Object {
protected:
	VECTOR m_Pos;			// 座標
	VECTOR m_Rot;			// 回転角度
	VECTOR m_Speed;			// 速度
	VECTOR m_Scale;			// モデルのスケール
	bool m_isActive;		// 生存フラグ
	bool m_isHitGround;		// 地面との当たり判定
	float m_Radius;			// 半径
	int m_Hndl;				// 生存フラグ

public:
	// コンストラクタ・デストラクタ
	Object();
	virtual ~Object();

	// 初期化
	void Init();
	// 終了時のデータ破棄など
	void Exit();
	// 当たり判定の座標系
	VECTOR GetCenter();
	// 更新処理
	// すべての行動が終わったらDxLibに情報を流す
	void Update();

	// 生存情報取得・設定
	bool IsActive() { return m_isActive; }
	void SetActive(bool active) { m_isActive = active; }
	// 当たり判定の半径サイズを取得
	float GetRadius() { return m_Radius; }
	// 座標の取得・設定
	VECTOR GetPosition() { return m_Pos; }
	void SetPosition(VECTOR pos) { m_Pos = pos; }
	void SetRotation(VECTOR rot) { m_Rot = rot; }
	// 回転角度を取得
	VECTOR GetRotation() { return m_Rot; }

	// 地面に当たっているかを渡す
	bool GetHitGround() { return m_isHitGround; }
	// 地面に当たっているかをセットする
	void SetHitGround(bool hit) { m_isHitGround = hit; }
};