#pragma once
// �I�v�V�������
namespace Option {
	extern int Move_Speed;//���\�[�X�t�@�C���Ŏg�p�ł���悤�Ƀw�b�_���Ő錾
}

void Option_Initialize(); // ������
void Option_Finalize(); // �I������
void Option_Update(); // �X�V
void Option_Draw(); // �`��

void Option_Save();//�f�[�^�̕ۑ�
void Option_Read();//�f�[�^�̓ǂݎ��
void Option_Reset();//�t�@�C���̌`�������������������Ƀ��Z�b�g����
