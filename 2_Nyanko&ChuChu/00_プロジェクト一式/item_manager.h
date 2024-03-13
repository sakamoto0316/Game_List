//============================================
//
// �A�C�e���}�l�[�W���[�w�b�_�[[item_manager.h]
// Author�F��������
//
//============================================
#ifndef _ITEM_MANAGER_H_		// ���̃}�N����`������Ă��Ȃ�������
#define _ITEM_MANAGER_H_		// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "main.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CItem;		// �A�C�e��

//--------------------------------------------
// �N���X(�A�C�e���}�l�[�W���[�N���X)
//--------------------------------------------
class CItemManager
{
public:				// �N�ł��A�N�Z�X�ł���

	CItemManager();			// �R���X�g���N�^
	~CItemManager();		// �f�X�g���N�^

	// �����o�֐�
	void Regist(CItem* pThis);		// �o�^����
	void Uninit(void);					// �I������
	
	CItem* GetTop(void);				// �擪�̎擾����
	void Pull(CItem* pThis);			// ���X�g�\���̈�����������

	// �ÓI�����o�֐�
	static CItemManager* Create(void);	// ��������
	static CItemManager* Get(void);		// �擾����

private:			// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CItem* m_pTop;	// �擪�̃I�u�W�F�N�g
	int m_nNumAll;			// �I�u�W�F�N�g�̑���

	// �ÓI�����o�ϐ�
	static CItemManager* m_pManager;		// �}�l�[�W���[�̕ϐ�
};

#endif