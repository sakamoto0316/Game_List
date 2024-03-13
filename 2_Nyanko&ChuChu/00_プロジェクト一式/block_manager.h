//============================================
//
// �u���b�N�}�l�[�W���[�w�b�_�[[block_manager.h]
// Author�F��������
//
//============================================
#ifndef _BLOCK_MANAGER_H_		// ���̃}�N����`������Ă��Ȃ�������
#define _BLOCK_MANAGER_H_		// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "main.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CBlock;		// �u���b�N

//--------------------------------------------
// �N���X(�u���b�N�}�l�[�W���[�N���X)
//--------------------------------------------
class CBlockManager
{
public:				// �N�ł��A�N�Z�X�ł���

	CBlockManager();			// �R���X�g���N�^
	~CBlockManager();		// �f�X�g���N�^

	// �����o�֐�
	void Regist(CBlock* pThis);		// �o�^����
	void Uninit(void);					// �I������
	void UninitAll(void);				// ALL�I������
	
	CBlock* GetTop(void);				// �擪�̎擾����
	void Pull(CBlock* pThis);			// ���X�g�\���̈�����������

	// �ÓI�����o�֐�
	static CBlockManager* Create(void);	// ��������
	static CBlockManager* Get(void);		// �擾����

private:			// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CBlock* m_pTop;		// �擪�̃I�u�W�F�N�g
	int m_nNumAll;		// �I�u�W�F�N�g�̑���

	// �ÓI�����o�ϐ�
	static CBlockManager* m_pManager;		// �}�l�[�W���[�̕ϐ�
};

#endif