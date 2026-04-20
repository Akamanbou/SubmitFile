#include<DxLib.h>

// これも追加しておくと、フレームレート事態の変更が可能になる
// このフレームで固定
#define FRAME_RATE (60)
// 上のフレームレートだと一フレームに何ミリ秒かかるか
#define FRAME_RATE_MILI_SECOND (1000/FRAME_RATE)

// FPSを表示するのに使用するデータがまとまった構造体

typedef struct {
	float m_FrameRate;	// 今のフレームレートを保存
	int m_NowTime;		// 現在時間
	int m_PrevTime;		// ひとつ前の時間
	int m_Count;		// カウント用

	int m_PredDrawTime;	// 1つ前にFPSを表示した時間
}FpsData;

FpsData g_Fps; // 実際にFPS表示に使用する関数

// 初期化関数
void InitFps()
{
	// 基本的に０で初期化
	g_Fps.m_FrameRate = 0.0f;
	g_Fps.m_NowTime = GetNowCount();
	g_Fps.m_PrevTime = 0;
	g_Fps.m_Count = 0;
	g_Fps.m_PredDrawTime = 0;
}

bool IsNextFame()
{
	// 現在の時間を取得
	g_Fps.m_NowTime = GetNowCount();
	// 前回の時間と今回の時間を取得
	int DefTime = g_Fps.m_NowTime - g_Fps.m_PrevTime;

	// 沿うてしている１フレにかかる時間を超えたら
	if (DefTime > FRAME_RATE_MILI_SECOND)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void StepFps()
{
	// ひとつ前の時間を更新
	g_Fps.m_PrevTime = g_Fps.m_NowTime;
}