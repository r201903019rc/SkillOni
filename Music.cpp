#include"Music.h"
#include"Dxlib.h"

namespace MUSIC {
	//SEのリスト
	int SE_list[SE_MAX];
	//BGMのリスト
	int BGM_list[BGM_MAX];
	//音量
	int SE_VOLUME = 70;
	int BGM_VOLUME = 30;
	//音量の最大最小
	const int VOLUME_MIN = 0;
	const int VOLUME_MAX = 250;
}
using namespace MUSIC;

void MUSIC_Initialize() {
	//SEをメモリへ読み込み
	SE_list[SE_break] = LoadSoundMem("Sound/SE/break.wav");
	SE_list[SE_cancel] = LoadSoundMem("Sound/SE/cancel.wav");
	SE_list[SE_cursor] = LoadSoundMem("Sound/SE/cursor.wav");
	SE_list[SE_decision] = LoadSoundMem("Sound/SE/decision.wav");
	SE_list[SE_magic] = LoadSoundMem("Sound/SE/magic.wav");
	SE_list[SE_pickup] = LoadSoundMem("Sound/SE/pickup.wav");
	SE_list[SE_put] = LoadSoundMem("Sound/SE/put.wav");

	//BGMをメモリへ読み込み
	BGM_list[BGM_running_witches] = LoadSoundMem("Sound/BGM/Running_Witches.wav");

	//再生ボリュームの調整
	Volume_Change();
}
void MUSIC_Finalize() {
	//音楽が格納されたメモリの開放(まあ一応)
	InitSoundMem();
}

void SE_Play(int num) {
	//再生
	PlaySoundMem(SE_list[num], DX_PLAYTYPE_BACK);
	return;
}
void BGM_Play(int num) {
	//BGMが重ならないよう、すべてのBGMを止める
	for (int i = 0; i < BGM_MAX; i++) {
		StopSoundMem(BGM_list[i]);
	}
	//ループ再生
	PlaySoundMem(BGM_list[num], DX_PLAYTYPE_LOOP);
	return;
}
void Volume_Change() {
	if ((VOLUME_MIN <= SE_VOLUME) && (SE_VOLUME <= VOLUME_MAX)) {
		//SEのボリュームを変更
		for (int i = 0; i < SE_MAX; i++) {
			ChangeVolumeSoundMem(SE_VOLUME, SE_list[i]);
		}
	}
	if ((VOLUME_MIN <= BGM_VOLUME) && (BGM_VOLUME <= VOLUME_MAX)) {
		//BGMのボリュームを変更
		for (int i = 0; i < BGM_MAX; i++) {
			ChangeVolumeSoundMem(BGM_VOLUME, BGM_list[i]);
		}
	}
	return;
}