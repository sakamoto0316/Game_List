//============================================
//
// ���U���g�w�b�_�[[result.h]
// Author�F��������
//
//============================================
#ifndef _RESULT_H_			//���̃}�N����`������Ă��Ȃ�������
#define _RESULT_H_			//2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "main.h"
#include "scene.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CPlayer;				// �v���C���[

//--------------------------------------------
// �N���X(���U���g��ʃN���X)
//--------------------------------------------
class CResult : public CScene
{
public:				// �N�ł��A�N�Z�X�ł���

	CResult();		// �R���X�g���N�^
	~CResult();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);					// ����������
	void Uninit(void);					// �I������
	void Update(void);					// �X�V����
	void Draw(void);					// �`�揈��

	static int GetState(void);					// �Q�[���̏��擾

private:					// ���������A�N�Z�X�ł���

	void CreateConfetti(void);			// ������̐���

	// �ÓI�����o�ϐ�(�ŏ�����K�v�ȕ���z�u���Ă���)
	static CPlayer* m_apPlayer[MAX_PLAY];	// �v���C���[�̏��
	static int m_nGameState;				// �Q�[���̏��

};

#endif