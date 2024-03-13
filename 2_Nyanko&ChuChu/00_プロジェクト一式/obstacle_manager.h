//============================================
//
// ��Q���}�l�[�W���[�w�b�_�[[obstacle_manager.h]
// Author�F��������
//
//============================================
#ifndef _OBSTACLE_MANAGER_H_		// ���̃}�N����`������Ă��Ȃ�������
#define _OBSTACLE_MANAGER_H_		// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "main.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CObstacle;		// ��Q��

//--------------------------------------------
// �N���X(��Q���}�l�[�W���[�N���X)
//--------------------------------------------
class CObstacleManager
{
public:				// �N�ł��A�N�Z�X�ł���

	CObstacleManager();			// �R���X�g���N�^
	~CObstacleManager();		// �f�X�g���N�^

	// �����o�֐�
	void Regist(CObstacle* pThis);		// �o�^����
	void Uninit(void);					// �I������
	
	CObstacle* GetTop(void);				// �擪�̎擾����
	void Pull(CObstacle* pThis);			// ���X�g�\���̈�����������

	// �ÓI�����o�֐�
	static CObstacleManager* Create(void);	// ��������
	static CObstacleManager* Get(void);		// �擾����

private:			// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CObstacle* m_pTop;	// �擪�̃I�u�W�F�N�g
	int m_nNumAll;			// �I�u�W�F�N�g�̑���

	// �ÓI�����o�ϐ�
	static CObstacleManager* m_pManager;		// �}�l�[�W���[�̕ϐ�
};

#endif