#include"Camera.h"

//----------------------
// コンストラクタ
//----------------------
Camera::Camera()
{
	Init();
}

//----------------------
// 初期化
//----------------------
void Camera::Init()
{
	m_TargetPos = ZERO;
	m_UpVec = { 0.0f,1.0f,0.0f };
	SetMousePoint(WINDOW_SIZE_X / 2, WINDOW_SIZE_Y / 2); // マウスの位置は画面の中央に設定する
}

//----------------------
//	ニアーファー設定
//----------------------
void Camera::SetNearFar(float n, float f)
{
	SetCameraNearFar(n, f);
}

//------------------------
// カメラの座標計算
//------------------------
void Camera::Step(VECTOR forcus, float rotY)
{
	int MouseX, MouseY;
	// 今のマウスの位置をそれぞれ入れる
	GetMousePoint(&MouseX, &MouseY);

	float x, y;
	// 中心を基準にどのくらい移動したかを入れる
	x = WINDOW_SIZE_X / 2 - MouseX;
	y = WINDOW_SIZE_Y / 2 - MouseY;

	// マイナスにならないようにする
	if (x <= 0)x *= -1;
	if (y <= 0)y *= -1;

	// マウスの位置をベクター型で入れる（ベクター型にするためにフロート型に変換）
	VECTOR MousePos = VGet(float(MouseX), (float)(MouseY), 0.0f);

	// カメラの上下移動--------------------------------------------------------------
	// マウスの上下の移動速度（感度）
	float SpeedY = y / (WINDOW_SIZE_Y / 2);
	SpeedY *= MOUSE_SENSITIVITY;

	// マウスの高さが画面の半分以下だったら
	if (MousePos.y <= WINDOW_SIZE_Y / 2)
	{
		float Rad = MAX_UP * RAD; // カメラの上限を値にしていれる
		// 上限より小さかったら
		if (m_Rot.x < Rad)
		{
			m_Rot.x += SpeedY * RAD; // カメラを感度分上に向ける
		}
		else
		{
			m_Rot.x = Rad; // 上限だったらそれ以上いかないようにする
		}
		// 回転角が大きくなりすぎたら戻す処理（-2πから2π内に収めるため）
		if (m_Rot.x > 2.0f * DX_PI_F)
			m_Rot.x -= 2.0f * DX_PI_F;
	}

	// マウスの高さが画面の半分より大きかったら
	if (MousePos.y > WINDOW_SIZE_Y / 2)
	{
		float Rad = MAX_DOWN * RAD; // カメラの下限を値にしていれる
		// 下限より大きかったら
		if (m_Rot.x > Rad)
		{
			m_Rot.x -= SpeedY * RAD; // カメラを感度分下に向ける
		}
		else
		{
			m_Rot.x = Rad; // 下限以下だとそれ以下いかないよにする
		}

		// 回転角が小さくなりすぎたら戻す処理（-2πから2π内に収めるため）
		if (m_Rot.x < -2.0f * DX_PI_F)
			m_Rot.x += 2.0f * DX_PI_F;
	}

	// パッドのスティックの上方向
	// 右スティックの上方向が入力されていたら
	if (CGamePad::Stick(STICK_RY_NEG) != 0)
	{
		float Rad = MAX_UP * RAD; // カメラの上限を値にしていれる
		// 上限より小さかったら
		if (m_Rot.x < Rad)
		{
			m_Rot.x += PAD_SPEED;
		}
		// 回転角が大きくなりすぎたら戻す処理（-2πから2π内に収めるため）
		if (m_Rot.x > 2.0f * DX_PI_F)
			m_Rot.x -= 2.0f * DX_PI_F;
	}
	// パッドのスティックの下方向
	// 右スティックの下方向が入力されていたら
	if (CGamePad::Stick(STICK_RY_POS) != 0)
	{
		float Rad = MAX_DOWN * RAD; // カメラの下限を値にしていれる
		// 下限より大きかったら
		if (m_Rot.x > Rad)
		{
			m_Rot.x -= PAD_SPEED;
		}
		// 回転角が小さくなりすぎたら戻す処理（-2πから2π内に収めるため）
		if (m_Rot.x < -2.0f * DX_PI_F)
			m_Rot.x += 2.0f * DX_PI_F;
	}
	//-----------------------------------------------------------------------------

	// カメラの左右移動-----------------------------------------------------------
	// マウスの左右の移動速度（感度）
	float SpeedX = x / (WINDOW_SIZE_X / 2);
	SpeedX *= MOUSE_SENSITIVITY;

	// マウスの位置が左よりだったら
	if (MousePos.x < WINDOW_SIZE_X / 2)
	{
		m_Rot.y -= SpeedX * RAD; // 左回転する
	}
	// マウスの位置が右よりだったら
	if (MousePos.x > WINDOW_SIZE_X / 2)
	{
		m_Rot.y += SpeedX * RAD; // 右回転する
	}

	// パッドのスティックの右入力
	// 右スティックの右方向が入力されていたら
	if (CGamePad::Stick(STICK_RX_POS) != 0)
	{
		m_Rot.y += PAD_SPEED;
	}
	// パッドのスティックの左入力
	// 右スティックの左方向が入力されていたら
	if (CGamePad::Stick(STICK_RX_NEG) != 0)
	{
		m_Rot.y -= PAD_SPEED;
	}

	// カメラの計算----------------------------------------------------
	MATRIX XRot;
	XRot = GetPitchMatrix(m_Rot.x);

	// カメラのY軸回転行列を作成
	MATRIX YRot;
	YRot = GetYawMatrix(m_Rot.y);

	// カメラの位置（高さを上げる）
	m_Pos = VGet(forcus.x, forcus.y + CAMERA_HEIGHT, forcus.z);

	// 前方向
	VECTOR Forward;
	Forward.x = cosf(m_Rot.x) * sinf(m_Rot.y);
	Forward.y = sinf(m_Rot.x);
	Forward.z = cosf(m_Rot.x) * cosf(m_Rot.y);

	// ターゲットに今の位置プラス視線方向を入れる
	m_TargetPos = VAdd(m_Pos, Forward);

	// 基本的にマウスの位置は真ん中になるようにする
	SetMousePoint(WINDOW_SIZE_X / 2, WINDOW_SIZE_Y / 2);
}

//------------------------
// カメラの更新
//------------------------
void Camera::Update()
{
	SetCameraPositionAndTargetAndUpVec(m_Pos, m_TargetPos, m_UpVec);
}