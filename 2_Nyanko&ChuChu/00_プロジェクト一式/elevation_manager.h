//============================================
//
// �N���}�l�[�W���[�w�b�_�[[elevation_manager.h]
// Author�F��������
//
//============================================
#ifndef _ELEVATION_MANAGER_H_		// ���̃}�N����`������Ă��Ȃ�������
#define _ELEVATION_MANAGER_H_		// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "main.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CElevation;		// �N��

//--------------------------------------------
// �N���X(�N���}�l�[�W���[�N���X)
//--------------------------------------------
class CElevationManager
{
public:				// �N�ł��A�N�Z�X�ł���

	CElevationManager();			// �R���X�g���N�^
	~CElevationManager();			// �f�X�g���N�^

	// �����o�֐�
	void Regist(CElevation* pThis);		// �o�^����
	void Uninit(void);						// �I������
	
	CElevation* GetTop(void);				// �擪�̎擾����
	void Pull(CElevation* pThis);			// ���X�g�\���̈�����������

	// �ÓI�����o�֐�
	static CElevationManager* Create(void);		// ��������
	static CElevationManager* Get(void);		// �擾����

private:			// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CElevation* m_pTop;		// �擪�̃I�u�W�F�N�g
	int m_nNumAll;			// �I�u�W�F�N�g�̑���

	// �ÓI�����o�ϐ�
	static CElevationManager* m_pManager;		// �}�l�[�W���[�̕ϐ�
};

#endif