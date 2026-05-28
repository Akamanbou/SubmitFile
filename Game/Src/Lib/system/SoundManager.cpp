#include"SoundManager.h"
#include<DxLib.h>
//定義関連--------------------------------
static const int WAIT_TIME = 60;
vector<int> SoundManager::m_hndl;
//----------------------------------------
void SoundManager::Init() {
	//中身を空にする
	m_hndl.clear();
}
void SoundManager::Load() {
	const char* filePath[SOUND_NUM] = {
		"../Data/Bgm/Spiki.mp3",
	};
	for (int i = 0; i < SOUND_NUM; i++)
	{
		int hndl = LoadSoundMem(filePath[i]);

		m_hndl.push_back(hndl);
		
		ChangeVolumeSoundMem(120,m_hndl[i]);
	}
}
void SoundManager::Exit() {
	for (int i = 0; i < SOUND_NUM; i++) {
		if (m_hndl[i] != -1) {
			DeleteSoundMem(m_hndl[i]);
			m_hndl[i] = -1;
		}
	}
}
//-----------------------------------
//音楽再生
//-----------------------------------
bool SoundManager::Play(tagSoundID id, int type, bool isStart) {
	for (int i = 0; i < SOUND_NUM; i++) {
		if (i != id)continue;
		int ret = PlaySoundMem(m_hndl[i], type, isStart);
		if (ret == -1)return false;
		else return true;
	}
}

//-----------------------------------
//音楽停止
//-----------------------------------
void SoundManager::Stop(tagSoundID id) {
	StopSoundMem(id);
}
//-----------------------------------
//音楽全停止
//-----------------------------------
void SoundManager::AllStop() {
	for (int i = 0; i < SOUND_NUM; i++) {
		StopSoundMem(i);
	}
}
//-----------------------------------
//音楽再生中か
//-----------------------------------
bool SoundManager::IsPlay(tagSoundID id) {
	return CheckSoundMem(m_hndl[id]) == 1 ? true : false;
}