#pragma once
#include<vector>
#include<DxLib.h>
using namespace std;


class SoundManager {
public:
	enum tagSoundID {
		SOUND_BGM,

		SOUND_NUM
	};
private:
	static vector<int> m_hndl;//音楽ハンドル
public:

	static void Init();
	static void Load();
	static void Exit();
	//音楽再生
	//@id :	再生する音楽
	//@type : DX_PLAYTYPE
	static bool Play(tagSoundID id, int type=DX_PLAYTYPE_BACK,bool isStart=true);
	static void Stop(tagSoundID id);
	static void AllStop();
	//音楽を再生中か
	static bool IsPlay(tagSoundID id);

};