#pragma once
#include"Camera.h"

// 複数のカメラを管理する
class CameraManager {
public:
	// カメラのタイプ
	enum tagCAMERA_ID
	{
		ID_PLAY,

		ID_NUM
	};
private:
	Camera m_Camera;	// メインカメラ
	tagCAMERA_ID m_ID;	// 今のカメラ

public:
	// コンストラクタ
	CameraManager();

	// 初期化
	void Init();
	// カメラの座標計算
	// @forcus : プレイヤーの座標
	// @rotY   : プレイヤーの角度
	void Step(VECTOR forcus, float rotY);
	// カメラの更新
	void Updata();

	// カメラのタイプ切り替え
	void ChangeCamera(tagCAMERA_ID id) { m_ID = id; }
	// カメラのタイプ取得
	tagCAMERA_ID GetID() { return m_ID;}
	Camera& GetCamera() { return m_Camera; }
};
