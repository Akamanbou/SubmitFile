#include"Field.h"

//----------------------
// コンストラクタ
//----------------------
Field::Field()
{
	Init();
}

//----------------------
// デストラクタ
//----------------------
Field::~Field()
{
	Exit();
}

//----------------------
// 初期化
//----------------------
void Field::Init()
{
	m_Pos = ZERO;
	m_Scale = { 1.2f,1.0f,1.2f };

	m_DemoHndl = -1;
	m_SkyPos = ZERO;
	m_SkyScale = { 50.0f,50.0f,50.0f };
	m_SkyHndl = -1;
}

//----------------------
// ロード
//----------------------
void Field::Load()
{
	if (m_Hndl == -1)
	{
		m_Hndl = MV1LoadModel("../Data/Field/Field.mv1");
	}

	MV1SetPosition(m_Hndl, m_Pos);
	MV1SetScale(m_Hndl, m_Scale);
	MV1SetupCollInfo(m_Hndl);

	MV1SetPosition(m_DemoHndl, m_Pos);
	MV1SetScale(m_DemoHndl, m_Scale);
	MV1SetupCollInfo(m_DemoHndl);


	if (m_SkyHndl == -1)
	{
		m_SkyHndl = MV1LoadModel("../Data/Sky/sky.mv1");
	}
}

//--------------------------
// 終了時の破棄
//--------------------------
void Field::Exit()
{
	if (m_Hndl != -1)
	{
		MV1DeleteModel(m_Hndl);
		MV1DeleteModel(m_SkyHndl);

		m_Hndl = -1;
		m_SkyHndl = -1;
	}
}

//--------------------------
// 全行動を処理する
//--------------------------
void Field::Step()
{
	m_Rot.y += 0.001f;
}

//--------------------------
// 更新処理
//--------------------------
void Field::Updata()
{
	// 移動結果を設定
	MV1SetPosition(m_Hndl, m_Pos);
	MV1SetPosition(m_SkyHndl, m_SkyPos);

	MV1SetScale(m_Hndl, m_Scale);
	MV1SetScale(m_SkyHndl, m_SkyScale);


	VECTOR Rot = { 0.0f,m_Rot.y,0.0f };
	MV1SetRotationXYZ(m_SkyHndl, Rot);
}

//--------------------------
// 描画処理
//--------------------------
void Field::Draw()
{
	// モデル表示
	MV1DrawModel(m_Hndl);
	MV1DrawModel(m_SkyHndl);
}