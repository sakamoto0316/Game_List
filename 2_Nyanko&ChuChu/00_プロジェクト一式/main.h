//============================================
//
// ���C���w�b�_�[[main.h]
// Author�F��������
//
//============================================
#ifndef _MAIN_H_//���̃}�N����`������Ă��Ȃ�������
#define _MAIN_H_//2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include <time.h>		// �����_���ɕK�v
#include "dinput.h"		// ���͏����ɕK�v
#include "xaudio2.h"	// �T�E���h�����ɕK�v
#include <assert.h>		// �A�T�[�g�����ɕK�v

//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")		// �`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")	// [d3d9.lib]
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")	// �V�X�e�������擾�ɕK�v
#pragma comment(lib,"dinput8.lib")	// ���͏����ɕK�v

//�}�N����`
#define SCREEN_WIDTH				(1280)								// �E�C���h�E�̕�
#define SCREEN_HEIGHT				(720)								// �E�C���h�E�̍���
#define FVF_VERTEX_2D				(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	// ���_�t�H�[�}�b�g[2D]
#define FVF_VERTEX_3D				(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)	//���_�t�H�[�}�b�g[3D]
#define MAX_STRING					(256)								// ������̍ő吔
#define INIT_SHADOW					(-1)								// �e�̏���������
#define NONE_TEXIDX					(-1)								// �e�N�X�`���̃C���f�b�N�X�̏����l
#define NONE_COLLIDX				(-1)								// �����蔻��|���S���̃C���f�b�N�X�̏����l
#define ALPHA_TEST_NUMBER			(0)									// �A���t�@�e�X�g��L���ɂ����Ƃ��̐��l
#define MAX_MATERIAL				(16)								// �}�e���A���̎��
#define NONE_PARENT					(-1)								// �e�����̐��l
#define NONE_D3DXVECTOR3			(D3DXVECTOR3(0.0f,0.0f,0.0f))		// D3DXVECTOR3�̏����l
#define NONE_D3DXCOLOR				(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))	// D3DXCOLOR�̏����l
#define MAX_PLAY					(4)									// �v���C���[�̐�

// ���_�f�[�^(2D)�̍\����
struct VERTEX_2D
{
	D3DXVECTOR3 pos;			//���_���W
	float rhw;					//���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;				//���_�J���[
	D3DXVECTOR2 tex;			//�e�N�X�`�����W
};

//���_���[3D]�̍\���̂��`
struct VERTEX_3D
{
	D3DXVECTOR3 pos;			//���_���W
	D3DXVECTOR3 nor;			//�@���x�N�g��
	D3DCOLOR col;				//���_�J���[
	D3DXVECTOR2 tex;			//�e�N�X�`�����W
};

// �v���g�^�C�v�錾
int GetFPS(void);				// FPS�̎擾����

#endif