// �I�v�V�������

#include "Utilities.h" // �K�v�ȕ�
#include "Option.h" // �I�v�V�������

using namespace MUSIC;//���y�֌W�ϐ��̐錾

namespace Option {//�f�o�b�O�p
	int back_handle;//�w�i�p�n���h��
	int block_handle;//�w�i�p�n���h��

	int select_now = 0;//�I�𒆂̍���
	bool file_load_ok = true;//�t�@�C�����ǂݍ��߂����ǂ���
	char filename[] = "SaveData/OptionData.txt";

	const int first_BGM_volume = 30;//BGM�̉��ʏ����l
	const int first_SE_volume = 50;//SE�̉��ʏ����l
	const int first_Move_Speed = 12;//�L�������x�̏����l

	int Move_Speed=12;//�L�������x�̕ύX
}
using namespace Option;
// ������
void Option_Initialize() {
	MUSIC_Initialize();
	BGM_Play(BGM_running_witches);//���y����
	//�t�@�C���ǂݍ���
	//���łɃI�v�V������ʂɈ�x�A�N�Z�X���Ă��āA���łɃt�@�C�����J���Ȃ��Ƃ킩���Ă���Ƃ��͊J���Ȃ�
	//���̍ۂ̓Q�[�����N�����Ă���Ԃ����͉��ʂ��ێ�����邪�A�l�͕ۑ�����Ȃ��̂ŃQ�[�����������珉���l�ɖ߂�
	if (file_load_ok == true) {Option_Read();}
	
	//�摜�擾
	back_handle = LoadGraph("Graphics/gallery/back.png");
	block_handle = LoadGraph("Graphics/gallery/window.png");
	//�t�H���g�̕ύX
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);
	SetFontSize(32);
}

// �I������
void Option_Finalize() {
	MUSIC_Finalize();
	Volume_Change();
	//�t�@�C�������݂���Ƃ��̂ݕۑ�����
	if (file_load_ok == true) { Option_Save(); }
	//�t�H���g���f�t�H���g��
	ChangeFontType(DX_FONTTYPE_NORMAL);
	SetFontSize(16);
}

// �X�V
void Option_Update() {
	// X�Ń��j���[�ɖ߂�
	if (Keyboard_Get(KEY_INPUT_X) == 1) {
		SE_Play(MUSIC::SE_cancel);
		SceneMgr_Change(S_Menu); //�V�[�������j���[�ɖ߂�
	}

	//���ڑI��
	if (Keyboard_Get(KEY_INPUT_UP) == 1) {
		if (select_now > 0) { select_now--; }
		SE_Play(SE_cursor);
	}
	else if (Keyboard_Get(KEY_INPUT_DOWN) == 1) {
		if (select_now < 2) { select_now++; }
		SE_Play(SE_cursor);
	}
	
	//�e���ڂ̏���
	switch (select_now) {
	case 0://BGM�̃{�����[����ς���
		if (Keyboard_Get(KEY_INPUT_LEFT) == 1) {
			if (BGM_VOLUME - 10 >= 0) { BGM_VOLUME -= 10; Volume_Change(); }
			SE_Play(SE_cursor);
		}
		else if (Keyboard_Get(KEY_INPUT_RIGHT) == 1) {
			if (BGM_VOLUME+10 < 255) { BGM_VOLUME+=10;  Volume_Change();}
			SE_Play(SE_cursor);
		}
		break;
	case 1://SE�̃{�����[����ς���
		if (Keyboard_Get(KEY_INPUT_LEFT) == 1) {
			if (SE_VOLUME-10 >= 0) {
				SE_VOLUME-=10;//����������
				Volume_Change();//���ʂ̕ύX��K��
			}
			SE_Play(SE_cursor);
		}
		else if (Keyboard_Get(KEY_INPUT_RIGHT) == 1) {
			if (SE_VOLUME+10 < 250) { 
				SE_VOLUME+=10;//����傫��
				Volume_Change();//���ʂ̕ύX��K��
			}
			SE_Play(SE_cursor);
		}
		break;
	case 2://�L�����̑��x��ς���
		if (Keyboard_Get(KEY_INPUT_LEFT) == 1) {
			if (Move_Speed - 1 >= 0) {
				Move_Speed -= 1;//���x��������
			}
			SE_Play(SE_cursor);
		}
		else if (Keyboard_Get(KEY_INPUT_RIGHT) == 1) {
			if (Move_Speed + 1 < 64) {
				Move_Speed += 1;//��������
			}
			SE_Play(SE_cursor);
		}
	default:
		break;
	}

}

// �`��
void Option_Draw() {
	//�w�i�`��
	DrawExtendGraph(0, 0, SCREEN_SIZE_WIDTH, SCREEN_SIZE_HEIGHT, back_handle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);//���ߏ����I��
	DrawExtendGraph(0, 0, SCREEN_SIZE_WIDTH, SCREEN_SIZE_HEIGHT, block_handle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//���ߏ����I�t
	//�����`��
	DrawString(50, 40,
		"[X] ���j���[��ʂɖ߂�",
		GetColor(255, 255, 255));
	DrawString(50, 90,
		"�I�v�V�������", GetColor(255, 255, 255));

	//���ݑI�𒆂̍���
	DrawString(150, 150 + (select_now * 50), "��",
		GetColor(255, 255, 255));
	//�{�����[���ύX
	DrawFormatString(200, 150, GetColor(255, 255, 255), "BGM�̉��� : %d", BGM_VOLUME);
	DrawFormatString(200, 200, GetColor(255, 255, 255), "SE�̉���  : %d", SE_VOLUME);
	DrawFormatString(200, 250, GetColor(255, 255, 255), "�f�o�b�O�p-�L�����̑��x : %d\n(�������������قǑ����Ȃ�܂�)", Move_Speed);

}

//�f�[�^�ǂݍ���
void Option_Read() {
	FILE* fp;
	//�t�@�C�����J��
	if ((fopen_s(&fp,filename, "r")) != 0) {
		//�ǂݍ��߂Ȃ������ꍇ��return(�I�v�V�����̋@�\���͎̂g���邪�Q�[�����������珉���l�ɖ߂�)
		file_load_ok = false;
		printfDx("error about read of option.");
		return;
	}
	else{ file_load_ok = true; }

	//�t�@�C���ɕۑ�����Ă���f�[�^��ǂݍ���
	//�ǂݍ��݂̍ہA�f�[�^�����܂��ǂݍ��߂Ȃ��A�������̓f�[�^�̒l��0������250�ȏ�Ȃ�f�[�^�����Z�b�g����
	
	if (((fscanf_s(fp, ("%d %d %d"), &BGM_VOLUME, &SE_VOLUME,&Move_Speed))==-1)||
		((BGM_VOLUME < 0) || (BGM_VOLUME > 250)) ||
		((SE_VOLUME < 0) || (SE_VOLUME > 250))||
		((Move_Speed<0)||(Move_Speed>64))
		) {
			fclose(fp);//��������t�@�C�������
			printfDx("data_error. Data Reset\n");//�G���[��
			Option_Reset(); 
			Volume_Change();//�Q�[�����ɔ��f
			return;
	
	}
	Volume_Change();//�f�[�^���Q�[�����ɔ��f
	fclose(fp);
	return;
}
//�f�[�^�����o��
void Option_Save() {
	FILE* fp;
	//�t�@�C�����J��
	fopen_s(&fp, filename, "w");
	//�f�[�^����������
	fprintf_s(fp, ("%d %d %d"), BGM_VOLUME, SE_VOLUME,Move_Speed);
	fclose(fp);
	return;
}

//�f�[�^�t�@�C���̃��Z�b�g
void Option_Reset() {
	//�t�@�C�����J��
	FILE* fp;
	fopen_s(&fp, filename, "w");
	//��������
	fprintf_s(fp, "%d %d %d", first_BGM_volume, first_SE_volume,first_Move_Speed);
	//�ϐ���������
	BGM_VOLUME = first_BGM_volume;
	SE_VOLUME = first_SE_volume;
	Move_Speed = first_Move_Speed;
	//�t�@�C�������
	fclose(fp);
	return;
}