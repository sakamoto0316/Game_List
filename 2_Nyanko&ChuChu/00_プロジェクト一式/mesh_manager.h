//============================================
//
// ���b�V���}�l�[�W���[�w�b�_�[[mesh_manager.h]
// Author�F��������
//
//============================================
#ifndef _MESH_MANAGER_H_		// ���̃}�N����`������Ă��Ȃ�������
#define _MESH_MANAGER_H_		// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "main.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CMesh;		// �N��

//--------------------------------------------
// �N���X(�N���}�l�[�W���[�N���X)
//--------------------------------------------
class CMeshManager
{
public:				// �N�ł��A�N�Z�X�ł���

	CMeshManager();			// �R���X�g���N�^
	~CMeshManager();			// �f�X�g���N�^

	// �����o�֐�
	void Regist(CMesh* pThis);		// �o�^����
	void Uninit(void);						// �I������
	
	CMesh* GetTop(void);				// �擪�̎擾����
	void Pull(CMesh* pThis);			// ���X�g�\���̈�����������

	// �ÓI�����o�֐�
	static CMeshManager* Create(void);		// ��������
	static CMeshManager* Get(void);		// �擾����

private:			// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CMesh* m_pTop;		// �擪�̃I�u�W�F�N�g
	int m_nNumAll;			// �I�u�W�F�N�g�̑���

	// �ÓI�����o�ϐ�
	static CMeshManager* m_pManager;		// �}�l�[�W���[�̕ϐ�
};

#endif