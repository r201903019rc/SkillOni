#include"Music.h"
#include"Dxlib.h"

namespace MUSIC {
	//SE�̃��X�g
	int SE_list[SE_MAX];
	//BGM�̃��X�g
	int BGM_list[BGM_MAX];
	//����
	int SE_VOLUME = 70;
	int BGM_VOLUME = 30;
	//���ʂ̍ő�ŏ�
	const int VOLUME_MIN = 0;
	const int VOLUME_MAX = 250;
}
using namespace MUSIC;

void MUSIC_Initialize() {
	//SE���������֓ǂݍ���
	SE_list[SE_break] = LoadSoundMem("Sound/SE/break.wav");
	SE_list[SE_cancel] = LoadSoundMem("Sound/SE/cancel.wav");
	SE_list[SE_cursor] = LoadSoundMem("Sound/SE/cursor.wav");
	SE_list[SE_decision] = LoadSoundMem("Sound/SE/decision.wav");
	SE_list[SE_magic] = LoadSoundMem("Sound/SE/magic.wav");
	SE_list[SE_pickup] = LoadSoundMem("Sound/SE/pickup.wav");
	SE_list[SE_put] = LoadSoundMem("Sound/SE/put.wav");

	//BGM���������֓ǂݍ���
	BGM_list[BGM_running_witches] = LoadSoundMem("Sound/BGM/Running_Witches.wav");

	//�Đ��{�����[���̒���
	Volume_Change();
}
void MUSIC_Finalize() {
	//���y���i�[���ꂽ�������̊J��(�܂��ꉞ)
	InitSoundMem();
}

void SE_Play(int num) {
	//�Đ�
	PlaySoundMem(SE_list[num], DX_PLAYTYPE_BACK);
	return;
}
void BGM_Play(int num) {
	//BGM���d�Ȃ�Ȃ��悤�A���ׂĂ�BGM���~�߂�
	for (int i = 0; i < BGM_MAX; i++) {
		StopSoundMem(BGM_list[i]);
	}
	//���[�v�Đ�
	PlaySoundMem(BGM_list[num], DX_PLAYTYPE_LOOP);
	return;
}
void Volume_Change() {
	if ((VOLUME_MIN <= SE_VOLUME) && (SE_VOLUME <= VOLUME_MAX)) {
		//SE�̃{�����[����ύX
		for (int i = 0; i < SE_MAX; i++) {
			ChangeVolumeSoundMem(SE_VOLUME, SE_list[i]);
		}
	}
	if ((VOLUME_MIN <= BGM_VOLUME) && (BGM_VOLUME <= VOLUME_MAX)) {
		//BGM�̃{�����[����ύX
		for (int i = 0; i < BGM_MAX; i++) {
			ChangeVolumeSoundMem(BGM_VOLUME, BGM_list[i]);
		}
	}
	return;
}