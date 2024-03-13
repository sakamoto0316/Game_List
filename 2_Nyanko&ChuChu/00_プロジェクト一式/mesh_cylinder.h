//=====================================================
//
// ���b�V���V�����_�[�w�b�_�[ [mesh_cylinder.h]
// Author�F��������
//
//=====================================================
#ifndef _MESH_CYLINDER_H_			// ���̃}�N����`������Ă��Ȃ��ꍇ
#define _MESH_CYLINDER_H_			// ��d�C���N���[�h�h�~�̃}�N�����`����

//*****************************************************
// �C���N���[�h�t�@�C��
//*****************************************************
#include "Objectmesh.h"

//-----------------------------------------------------
// �N���X��`(���b�V��)
//-----------------------------------------------------
class CMeshCylinder : public CMesh
{
public:		// �N�ł��A�N�Z�X�ł���

	CMeshCylinder();				// �R���X�g���N�^
	CMeshCylinder(CObject::TYPE type, CObject::PRIORITY priority = PRIORITY_BG);		// �I�[�o�[���[�h�R���X�g���N�^
	virtual ~CMeshCylinder();		// �f�X�g���N�^

	// �����o�֐�
	virtual HRESULT Init(void);		// ����������
	virtual void Uninit(void);		// �I������
	virtual void Update(void);		// �X�V����
	virtual void Draw(void);		// �`�揈��

private:		// ���������A�N�Z�X�ł���

};


#endif