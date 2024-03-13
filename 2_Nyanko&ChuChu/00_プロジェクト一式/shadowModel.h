//===================================
//
// ���f���e�w�b�_�[[shadowModel.h]
// Author ��������
//
//===================================
#ifndef _SHADOWMODEL_H_				//���̃}�N����`������Ă��Ȃ�������
#define _SHADOWMODEL_H_				//2�d�C���N���[�h�h�~�̃}�N�����`����

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "main.h"
#include "model.h"

//-----------------------------------
// �N���X��`(�e)
//-----------------------------------
class CShadowModel : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	CShadowModel();			// �R���X�g���N�^
	~CShadowModel();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);			// ����������
	void Uninit(void);			// �I������
	void Update(void);			// �X�V����
	void Draw(void);			// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& scale, const CXFile::TYPE& type, const D3DXMATRIX& mtx);		// ���̐ݒ菈��

	static void SetPosRot(int nIdx, const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);		// �e�̈ʒu�ݒ菈��

	// �ÓI�����o�֐�
	static CShadowModel* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& scale, const CXFile::TYPE& type, const D3DXMATRIX& mtx);	// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	D3DXMATRIX m_mtxParent;		// �e�̃}�g���b�N�X
};


#endif