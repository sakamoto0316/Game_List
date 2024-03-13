//=====================================================
//
// ���b�V���h�[���w�b�_�[ [mesh_dome.h]
// Author�F��������
//
//=====================================================
#ifndef _MESH_DOME_H_			// ���̃}�N����`������Ă��Ȃ��ꍇ
#define _MESH_DOME_H_			// ��d�C���N���[�h�h�~�̃}�N�����`����

//*****************************************************
// �C���N���[�h�t�@�C��
//*****************************************************
#include "Objectmesh.h"

//-----------------------------------------------------
// �N���X��`(���b�V��)
//-----------------------------------------------------
class CMeshDome : public CMesh
{
public:		// �N�ł��A�N�Z�X�ł���

	CMeshDome();				// �R���X�g���N�^
	CMeshDome(CObject::TYPE type, CObject::PRIORITY priority = PRIORITY_BG);			// �I�[�o�[���[�h�R���X�g���N�^
	virtual ~CMeshDome();		// �f�X�g���N�^
	void Box(void);				// �R���X�g���N�^�̔�

	// �����o�֐�
	virtual HRESULT Init(void);		// ����������
	virtual void Uninit(void);		// �I������
	virtual void Update(void);		// �X�V����
	virtual void Draw(void);		// �`�揈��

private:		// ���������A�N�Z�X�ł���

};


#endif