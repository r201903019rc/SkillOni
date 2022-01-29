// �X�^�b�t���[��

#include "Utilities.h" // �K�v�Ȃ���
#include "Credit.h" // �X�^�b�t���[��

/*
�e�d���ɒN���������Ă��邩�̃f�[�^��int�^�z���programer,graphicer,composer�Ɏ��[����Ă��܂��̂ŁA��E�ɕύX������Ƃ��͂������������Ă��������B
�e�d���ɏ�������l�����ς��Ƃ��ɂ́A�e��E�̐l�����L�^����Ă���PROGREMER_NAM,GRAPHICER_NUM,COMPOSER_NUM�������ɏ��������Ă��������B

�\�������l����ς������Ƃ���name[CREATERS][16]�̒��g���������Ă��������B
*/
namespace Credit {
	const int CREATERS = 11;//���̃Q�[���̐��상���o�[�̑S�̐�
	const int WORKS = 4;//3�̎d��(�v���O���},�O���t�B�b�J,�R���|�[�U)+�X�y�V�����T���N�X

	const int PROGRAMER_NUM = 8;//�v���O���}�̐l��
	const int GRAPHICER_NUM = 6;//�O���t�B�b�J�[�̐l��
	const int COMPOSER_NUM = 1;//�R���|�[�U�[�̐l��
	const int SPECIAL_NUM = 2;//�X�y�V�����T���N�X�̐�

	//�����o�[�Ǘ��penum
	enum {
		// 4�N
		Exe,
		Rodita,
		// 3�N
		Agu,
		Arumiker,
		Nonobe,
		Raim,
		Rayan,
		// 2�N
		Aohi,
		TKG,
		Vea,
		Yuya,
	};
	//�e�d���̃����o�[(�S�����Ă���d����ς������Ƃ��͂�����ς���A��̊Ǘ��penum�̒l�����Ă��������B�e��E�̐l���ɕω�������Ƃ��͏��const int�̒l��)
		//�v���O���}�̕��X
	int programer[PROGRAMER_NUM] = {
	Arumiker,Exe,Nonobe,Rodita,Raim,Rayan,TKG,Vea
	};
	//�O���t�B�b�J�\�̕��X
	int graphicer[GRAPHICER_NUM] = {
	Agu,Aohi,Yuya,Vea,Arumiker,Raim
	};
	//�R���|�[�U�[�̕��X
	int composer[COMPOSER_NUM] = {
	Aohi
	};
	//�\������閼�O(�e�l�̖��O��ύX�������Ƃ��͂�����ς���)
	char name[CREATERS][16] = {
		// 4�N
			"Exe",
			"Robita",
			// 3�N
				"Agu",
				"����݂��[",
				"Nonobe",
				"�炢��",
				"Rayan",
				// 2�N
					"Aohi",
					"TKG",
					"Vea",
					"Yuya",
	};//���상���o�[
	//�d����
	char work[WORKS][32] = {
		"�v���O���}","�O���t�B�b�J","�R���|�[�U","�X�y�V�����T���N�X"
	};
	//�X�y�V�����T���N�X�ꗗ
	char sp_thanks[SPECIAL_NUM][16] = { "�_�ސ��w","GCC" };

	//�G���ȕϐ���萔����
	const int space = 50;//����
	const int WHITE = GetColor(255, 255, 255);//�����F�A��
	const int BLACK = GetColor(0, 0, 0);//�����F�A��
	const int move_speed = 3;//�����̓������x

	int move_name = 150;//���O���o�̏����\���ʒu
	int move_work = -100;//�d�����o�̏����\���ʒu
	int skeleton = 50;//�����̏������ߓx(0.���S�ɓ����`255.���߂Ȃ�)
	int back_handle;//�w�i�p�n���h��
	int block_handle;//�w�i�p�n���h��
}
using namespace Credit;

// ������
void Credit_Initialize() {
	//�s��Ŗ��O�����܂��Ă��Ȃ��l���������p�Ɉꉞ������
	for (int i = 0; i < CREATERS; i++) {
		if (name[i][0] == NULL) { sprintfDx(name[i], "�������̌����q"); }
	}
	//�w�i�摜�̃n���h���擾
	back_handle = LoadGraph("Graphics/gallery/back.png");
	block_handle = LoadGraph("Graphics/gallery/window.png");
	//�t�H���g�̕ύX
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);
	SetFontSize(32);
}
// �I������
void Credit_Finalize() {
	Credit_reset();
	//�t�H���g���f�t�H���g��
	ChangeFontType(DX_FONTTYPE_NORMAL);
	SetFontSize(16);
}
// �X�V
void Credit_Update() {
	// X�Ŗ߂�
	if (Keyboard_Get(KEY_INPUT_X) == 1) {
		SE_Play(MUSIC::SE_cancel);
		SceneMgr_Change(S_Menu); //�V�[�������j���[�ɖ߂�
	}
	else if (Keyboard_Get(KEY_INPUT_Z) == 1) {
		SE_Play(MUSIC::SE_decision);
		//������x�Đ�
		Credit_reset();
	}

	//�����̈ړ�����
	if (move_work < 50) { move_work += move_speed; }
	if (move_name > 0) { move_name -= move_speed; }
	//�����̓��߂����񂾂񔖂�����
	skeleton += 5;
}
// �`��
void Credit_Draw() {
	//�w�i�`��
	DrawExtendGraph(0, 0, SCREEN_SIZE_WIDTH, SCREEN_SIZE_HEIGHT, back_handle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);//���ߏ����I��
	DrawExtendGraph(0, 0, SCREEN_SIZE_WIDTH, SCREEN_SIZE_HEIGHT, block_handle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//���ߏ����I�t
//�����`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);//���ߏ����I��
	DrawString(20, 20,
		"[X] �߂�\n����҂̖��O������܂��B",WHITE);
	DrawString(50, 100, "������育�����@����X�^�b�t", WHITE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//���ߏ����I�t

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, skeleton);//���ߏ����I��
	//�d����
	DrawString(move_work, 145, work[0], WHITE);//�v���O���}
	DrawString(200 + move_work, 145, work[1], WHITE);//�O���t�B�b�J
	DrawString(200 + move_work, 145 + (1 * space) + (GRAPHICER_NUM * space), work[2], WHITE);//�R���|�[�U
	DrawString(450 + move_work, 145, work[3], WHITE);//�X�y�V�����T���N�X

	//�v���O���}�̕��X
	for (int i = 0; i < PROGRAMER_NUM; i++) {
		DrawString(75 + move_name, 180 + (i * space), name[programer[i]], WHITE);
	}
	//�O���t�B�b�J�̕��X
	for (int i = 0; i < GRAPHICER_NUM; i++) {
		DrawString(275 + move_name, 180 + (i * space), name[graphicer[i]], WHITE);
	}
	//�R���|�[�U�̕��X
	for (int i = 0; i < COMPOSER_NUM; i++) {
		DrawString(275 + move_name, 180 + (1 * space) + (GRAPHICER_NUM * space) + (i * space), name[composer[i]], WHITE);
	}
	//�X�y�V�����T���N�X
	for (int i = 0; i < SPECIAL_NUM; i++) {
		DrawString(525 + move_name, 180 + (i * space), sp_thanks[i], WHITE);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//���ߏ����I�t

	

}
//�ϐ��̃��Z�b�g
void Credit_reset() {
	move_work = -100;
	move_name = 150;
	skeleton = 50;
	return;
}