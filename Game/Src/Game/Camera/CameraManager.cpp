#include"CameraManager.h"

//----------------------
// コンストラクタ
//----------------------
CameraManager::CameraManager()
{
	// 初期カメラはプレイカメラ
	m_ID = ID_PLAY;
}

//----------------------
// 初期化
//----------------------
void CameraManager::Init()
{
	// それぞれのカメラを初期化
	m_Camera.Init();

	// ニアー・ファー設定
	SetCameraNearFar(1.0f, 100000.0f);
}

//----------------------
// カメラの座標計算
//----------------------
void CameraManager::Step(VECTOR forcus, float rotY)
{
	switch (m_ID)
	{
	case CameraManager::ID_PLAY:
		m_Camera.Step(forcus, rotY);
		break;
	}
}

//----------------------
//	カメラの更新
//----------------------
void CameraManager::Updata()
{
	switch (m_ID)
	{
	case CameraManager::ID_PLAY:
		m_Camera.Update();
		break;
	}
}