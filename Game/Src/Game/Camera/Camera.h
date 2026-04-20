#pragma once
#include<DxLib.h>
#include<math.h>
#include"../../Lib/Object/Object.h"
#include"../../Lib/Input/Input.h"
#include"../../Lib/Input/PadInput.h"
#include"../../Lib/MyMath/MyMath.h"
#include"../Common.h"

// カメラの高さ
static const int CAMERA_HEIGHT = 1.5f;
// カメラの感度
static const int MOUSE_SENSITIVITY = 90;
// カメラの上の移動上限
static const int MAX_UP = 30;
// カメラの下の移動上限
static const int MAX_DOWN = -70;
// カメラのパッドでの移動速度
static const float PAD_SPEED = 0.05f;
// カメラの回転速度
#define CAMERA_ROT_SPEED (0.052f)


class Camera :public Object {
private:
	VECTOR m_TargetPos;		// 注視点
	VECTOR m_UpVec;			// カメラの上方向

public:
	// コンストラクタ
	Camera();

	// 初期化
	void Init();
	// ニアー・ファー設定
	void SetNearFar(float n, float f);
	// カメラの座標計算
	// @forcus : プレイヤーの座標
	// @rotY   : プレイヤーの角度
	void Step(VECTOR forcus, float rotY);
	// カメラの更新
	void Update();

	VECTOR GetTargetPos() { return m_TargetPos; }
};