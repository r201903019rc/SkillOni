#pragma once
namespace MUSIC {//���y�֌W�̊Ǘ�
	//���ʉ��̖��O
	//���ʉ����{���@https://soundeffect-lab.info/sound/anime/
	typedef enum {
		SE_break,
		SE_cancel,
		SE_cursor,
		SE_decision,
		SE_magic,
		SE_pickup,
		SE_put,
		SE_MAX,
	};

	//BGM�̖��O
	//���������(mp3���ƂȂ�����Ȃ������̂�wav�ɕϊ����Ă܂�)�@https://maoudamashii.jokersounds.com/music_bgm.html
	typedef enum {
		BGM_running_witches,
		BGM_MAX,
	};

	//SE�̃��X�g
	extern int SE_list[];
	//BGM�̃��X�g
	extern int BGM_list[];
	//����
	extern int SE_VOLUME;
	extern int BGM_VOLUME;
}

void MUSIC_Initialize();//namespace MUSIC���̕ϐ��̏������A���̃w�b�_��include�������x�g���܂��傤
void MUSIC_Finalize();//�������J�������A���̃w�b�_��include����cpp�̏I���̍ۂɂ͎��s���܂��傤

void SE_Play(int);//SE�̖��O(SE_�Z�Z)��������SE�𗬂��܂�
void BGM_Play(int);//BGM�̖��O(BGM_�Z�Z)��������BGM�𗬂��܂�
void Volume_Change();//SE_VOLUME��BGM_VOLUME�̕ω���K�����܂�(����2�̕ϐ��̒l�������ύX���Ă��{�����[���͕ς��܂���)