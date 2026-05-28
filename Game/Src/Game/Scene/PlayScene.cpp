#include"PlayScene.h"

//-----------------------------------
// コンストラクタ
//-----------------------------------
PlayScene::PlayScene()
{
	m_State = INIT;
}

//-----------------------------------
// デストラクタ
//-----------------------------------
PlayScene::~PlayScene()
{
	Exit();
}

//-----------------------------------
// 毎フレーム呼ぶ処理
//-----------------------------------
int PlayScene::Loop()
{
	// ゲームが終了したかを外部に伝えるため
	int Result = -1;

	switch (m_State)
	{
	case PlayScene::INIT:
		Init();
		m_State = LOAD; // 次へ進む
		break;
	case PlayScene::LOAD:
		Load();
		m_Sound.Play(SoundManager::SOUND_BGM, DX_PLAYTYPE_LOOP, TRUE);
		m_State = MAIN; // 次へ進む
		break;
	case PlayScene::MAIN:
		Step();
		break;
	case PlayScene::END:
		Exit();
		m_Sound.AllStop();
		Result = 0;
		m_Enemy.ReStart(); // 敵のリスタート時の初期化
		m_State = INIT; // 次へ進む
		break;
	case PlayScene::PLAY_SCENE_NUM:
		break;

	default:
		break;
	}

	// 本編が終了したかどうかを外部に伝える	
	return Result;
}

//-----------------------------------
// 描画処理
//-----------------------------------
void PlayScene::Draw()
{
	m_Field.Draw();
	m_Enemy.Draw();
	m_Player.Draw();

}

//-----------------------------------
// 初期化
//-----------------------------------
void PlayScene::Init()
{
	m_Player.Init();
	m_Camera.Init();
	m_Field.Init();
	m_Enemy.Init();
	m_Sound.Init();
}

//-----------------------------------
// データロード
//-----------------------------------
void PlayScene::Load()
{
	m_Player.Load();
	m_Field.Load();
	m_Enemy.Load();
	m_Sound.Load();
}

//-----------------------------------
// 毎フレーム呼ぶ処理
//-----------------------------------
void PlayScene::Step()
{
	m_Player.Step(m_Camera);
	m_Camera.Step(m_Player.GetCenter(), m_Player.GetRotation().y);
	m_Field.Step();
	m_Enemy.Step(m_Player.GetPosition());

	// 当たり判定-----------------------
	m_Player.Collision(m_Collision.CheckHitPlToField(m_Player, m_Field.GetHndl()));

	m_Collision.CheckHitPlAttackToEnemy(m_Player, m_Enemy);
	m_Collision.CheckHitEnemyAttackToPl(m_Player, m_Enemy);
	m_Collision.CheckHitEnemyToEnemyPick(m_Enemy, m_Player);

	if (!m_Player.IsActive())
		m_State = END;

	// 更新処理
	m_Player.Update();
	m_Camera.Updata();
	m_Field.Updata();
	m_Enemy.Update();
}

//-----------------------------------
// 終了処理
//-----------------------------------
void PlayScene::Exit()
{
	m_Player.Exit();
	m_Field.Exit();
	m_Enemy.Exit();
	m_Sound.Exit();
}