//============================================
//
// �T���v���}�l�[�W���[�w�b�_�[[sample_manager.h]
// Author�F��������
//
//============================================
#ifndef _SAMPLE_MANAGER_H_		// ���̃}�N����`������Ă��Ȃ�������
#define _SAMPLE_MANAGER_H_		// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "main.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CListSample;		// �T���v��

//--------------------------------------------
// �N���X(�T���v���}�l�[�W���[�N���X)
//--------------------------------------------
class CSampleManager
{
public:				// �N�ł��A�N�Z�X�ł���

	CSampleManager();			// �R���X�g���N�^
	~CSampleManager();			// �f�X�g���N�^

	// �����o�֐�
	void Regist(CListSample* pThis);		// �o�^����
	void Uninit(void);					// �I������
	
	CListSample* GetTop(void);				// �擪�̎擾����
	void Pull(CListSample* pThis);			// ���X�g�\���̈�����������

	// �ÓI�����o�֐�
	static CSampleManager* Create(void);	// ��������
	static CSampleManager* Get(void);		// �擾����

private:			// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CListSample* m_pTop;	// �擪�̃I�u�W�F�N�g
	int m_nNumAll;			// �I�u�W�F�N�g�̑���

	// �ÓI�����o�ϐ�
	static CSampleManager* m_pManager;		// �}�l�[�W���[�̕ϐ�
};

#endif