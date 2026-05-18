#include"Player.h"

//----------------------
// コンストラクタ
//----------------------
Player::Player()
{
	Init();
}

//----------------------
// デストラクタ
//----------------------
Player::~Player()
{
	Exit();
}

//----------------------
// 初期化
//----------------------
void Player::Init()
{
	m_Pos = { 0.0f,0.0f,-1500.0f };
	m_Radius = 20.0f;
	m_isActive = true;

	m_isHitGround = true;

	m_JumpPow = 0.0f;

	m_State = NormalState;

	m_Level = 1;
	m_Power = 1;
	m_WantExp = 20;

	m_AtPos = { 0.0f,0.0f,-1500.0f };
	m_AtCoolTime = 0;
	m_AtTime = 0;
}

//--------------------------
// モデルデータのロード
//--------------------------
void Player::Load()
{
	// ロードされていなければする
	if (m_Hndl = -1)
	{
		m_Hndl = MV1LoadModel(PLAYER_MODEL_PATH);
	}
}

//------------------------
// プレイヤーの動き
//------------------------
void Player::Step(CameraManager& camera)
{

	// 地面に触れていて
	if (m_isHitGround)
	{
		// ジャンプしてもよい
		Jump();
	}

	Level();

	// 地面に触れていたら
	if (m_isHitGround)
		// ジャンプ力をゼロにする
		m_JumpPow = 0.0f;

	// 地面に触れていなければ
	if (!m_isHitGround)
		// 重力を動かす
		Gravity();

	// プレイヤーの高さにジャンプ力をプラスする
	m_Pos.y += m_JumpPow;
	m_AtPos = m_Pos;

	m_AtCoolTime++;
	if (CInput::IsPush(MOUSE_RIGHT) && m_AtCoolTime >= 60)
		m_State = AttackState;

	switch (m_State)
	{
	case NormalState:
		// 移動
		Move(camera);
		PadMove(camera);
		break;
	case AttackState:
		m_Rot.y = camera.GetCamera().GetRotation().y;
		// 移動
		Move(camera);
		PadMove(camera);
		if (m_AtTime < PL_AT_TIME)
			Attack(camera);
		else
		{
			m_AtCoolTime = 0;
			m_AtTime = 0;
			m_State = NormalState;
		}
		break;
	}
}

//------------------------
// 重力
//------------------------
void Player::Gravity()
{
	if (m_JumpPow >= -100.0f)
		m_JumpPow -= GRAVITY;
}

//------------------------
// ジャンプ
//------------------------
void Player::Jump()
{
	if (CInput::IsPush(KEY_SPACE))
	{
		m_JumpPow = 2.5f;
		m_isHitGround = false;
	}

	if (CGamePad::IsPadPush(BUTTON_A, BUTTON_A) != 0)
	{
		m_JumpPow = 2.5f;
		m_isHitGround = false;
	}
}

//------------------------
// 移動
//------------------------
void Player::Move(CameraManager& camera)
{
	float Speed = 0.0f; // 実際の進むスピード

	// 移動
	// 右斜め前
	if (CInput::IsCont(KEY_W) && CInput::IsCont(KEY_D))
	{
		// Dキーを押したときに右へ向きを変える
		m_Rot.y = camera.GetCamera().GetRotation().y;
		Speed = PL_WALK_SPEED;
		float Deg = PL_RIGHT_FRONT; // ディグリー角で値を入れる
		float Rad = Deg * RAD; // ラジアン角に直す
		m_Rot.y += Rad; // 角度にプラスする

		// 移動計算
		m_Speed.x = sinf(m_Rot.y) * Speed;
		m_Speed.z = cosf(m_Rot.y) * Speed;
	}

	// 右斜め後
	else if (CInput::IsCont(KEY_S) && CInput::IsCont(KEY_D))
	{
		// Dキーを押したときに右へ向きを変える
		m_Rot.y = camera.GetCamera().GetRotation().y;
		Speed = PL_WALK_SPEED;
		float Deg = PL_RIGHT_BACK; // ディグリー角で値を入れる
		float Rad = Deg * RAD;
		m_Rot.y += Rad; // 角度にプラスする

		// 移動計算
		m_Speed.x = sinf(m_Rot.y) * Speed;
		m_Speed.z = cosf(m_Rot.y) * Speed;
	}

	// 左斜め後
	else if (CInput::IsCont(KEY_S) && CInput::IsCont(KEY_A))
	{
		// Aキーを押したときに左へ向きを変える
		m_Rot.y = camera.GetCamera().GetRotation().y;
		Speed = PL_WALK_SPEED;
		float Deg = PL_LEFT_BACK; // ディグリー角で値を入れる
		float Rad = Deg * RAD;
		m_Rot.y += Rad; // 角度にプラスする

		// 移動計算
		m_Speed.x = sinf(m_Rot.y) * Speed;
		m_Speed.z = cosf(m_Rot.y) * Speed;
	}

	// 左斜め前
	else if (CInput::IsCont(KEY_W) && CInput::IsCont(KEY_A))
	{
		// Aキーを押したときに左へ向きを変える
		m_Rot.y = camera.GetCamera().GetRotation().y;
		Speed = PL_WALK_SPEED;
		float Deg = PL_LEFT_FRONT; // ディグリー角で値を入れる
		float Rad = Deg * RAD;
		m_Rot.y += Rad; // 角度にプラスする

		// 移動計算
		m_Speed.x = sinf(m_Rot.y) * Speed;
		m_Speed.z = cosf(m_Rot.y) * Speed;
	}

	// 上移動
	else if (CInput::IsCont(KEY_W))
	{
		// Wキーを押したときにカメラの向いているほうへ向きを変える
		m_Rot.y = camera.GetCamera().GetRotation().y;
		Speed = PL_WALK_SPEED;
		float Deg = PL_FRONT; // ディグリー角で値を入れる
		float Rad = Deg * RAD;
		m_Rot.y += Rad; // 角度にプラスする

		// 移動計算
		m_Speed.x = sinf(m_Rot.y) * Speed;
		m_Speed.z = cosf(m_Rot.y) * Speed;
	}

	// 下移動
	else if (CInput::IsCont(KEY_S))
	{
		// Sキーを押したときにカメラの向いているほうへ向きを変える
		m_Rot.y = camera.GetCamera().GetRotation().y;
		Speed = PL_WALK_SPEED;
		float Deg = PL_BACK; // ディグリー角で値を入れる
		float Rad = Deg * RAD;
		m_Rot.y += Rad; // 角度にプラスする

		// 移動計算
		m_Speed.x = sinf(m_Rot.y) * Speed;
		m_Speed.z = cosf(m_Rot.y) * Speed;
	}

	// 右移動
	else if (CInput::IsCont(KEY_D))
	{
		// Dキーを押したときにカメラの向いている方向へ向きを変える
		m_Rot.y = camera.GetCamera().GetRotation().y;
		Speed = PL_WALK_SPEED;
		float Deg = PL_RIGHT; // ディグリー角で値を入れる
		float Rad = Deg * RAD;
		m_Rot.y += Rad; // 角度にプラスする

		// 移動計算
		m_Speed.x = sinf(m_Rot.y) * Speed;
		m_Speed.z = cosf(m_Rot.y) * Speed;
	}

	// 左移動
	else if (CInput::IsCont(KEY_A))
	{
		// Aキーを押したときにカメラの向いている方向へ向きを変える
		m_Rot.y = camera.GetCamera().GetRotation().y;
		Speed = PL_WALK_SPEED;
		float Deg = PL_LEFT; // ディグリー角で値を入れる
		float Rad = Deg * RAD;
		m_Rot.y += Rad; // 角度にプラスする

		// 移動計算
		m_Speed.x = sinf(m_Rot.y) * Speed;
		m_Speed.z = cosf(m_Rot.y) * Speed;
	}

	else m_Speed = ZERO;

	m_Pos = VAdd(m_Pos, m_Speed);
}

//------------------------
// パッドでの移動
//------------------------
void Player::PadMove(CameraManager& camera)
{
	float Speed = 0.0f;

	float move_vec = CGamePad::StickRot(STICK_LEFT);
	if (CGamePad::Stick(STICK_LX_POS) != 0
		|| CGamePad::Stick(STICK_LX_NEG) != 0
		|| CGamePad::Stick(STICK_LY_POS) != 0
		|| CGamePad::Stick(STICK_LY_NEG) != 0) {
		m_Rot.y = camera.GetCamera().GetRotation().y;
		Speed = -PL_WALK_SPEED;
		m_Speed.x = -sinf(m_Rot.y + move_vec) * Speed;
		m_Speed.y = 0.0f;
		m_Speed.z = -cosf(m_Rot.y + move_vec) * Speed;
		m_Pos = VAdd(m_Pos, VScale(m_Speed, -1));

		m_Rot.y = atan2f(m_Speed.x, m_Speed.z);
	}
}

//------------------------
// 当たり判定
//------------------------
void Player::Collision(bool hitField)
{
	if (hitField)
		m_isHitGround = true;
}


//------------------------
// 描画
//------------------------
void Player::Draw()
{
	//MV1DrawModel(m_Hndl);

	DrawFormatString(20, 120, RED, "%.2f,%.2f,%.2f", m_Pos.x, m_Pos.y, m_Pos.z);
	//DrawSphere3D(GetCenter(), m_Radius, 16, RED, RED, FALSE);
	if (m_isHitGround)
	{
		DrawFormatString(20, 140, RED, "TRUE");
	}
	else
		DrawFormatString(20, 140, RED, "FALSE");

	if (CInput::IsPush(MOUSE_RIGHT) && m_AtCoolTime >= 60)
		DrawSphere3D(m_AtPos, m_Radius, 16, RED, RED, FALSE);

	DrawFormatString(20, 160, RED, "%.2f,%.2f,%.2f", m_AtPos.x, m_AtPos.y, m_AtPos.z);


	float ExpBar = (900 - 380);
	ExpBar = ExpBar / m_WantExp;
	ExpBar = ExpBar * m_NowExp + 380;
	DrawBox(376, 626, 904, 654, WHITE, true);
	DrawBox(380, 630, (int)ExpBar, 650, GetColor(0, 255, 0), true);
}

//------------------------
	// ヒット後の処理
//------------------------
void Player::HitCale()
{
}

//------------------------
// レベルアップ処理
//------------------------
void Player::Level()
{
	if (m_NowExp >= m_WantExp)
	{
		m_Level += 1;
		m_NowExp -= m_WantExp;
		m_WantExp += 20;
	}
}

//------------------------
// 攻撃処理
//------------------------
void Player::Attack(CameraManager& camera)
{
	int Attack = 0;

	Attack = PL_ATTACK;

	m_AtTime++;

	m_AtPos.x = sinf(m_Rot.y) * Attack;
	m_AtPos.y = 0.0f;
	m_AtPos.z = cosf(m_Rot.y) * Attack;
	m_AtPos = VAdd(m_Pos, m_AtPos);
}