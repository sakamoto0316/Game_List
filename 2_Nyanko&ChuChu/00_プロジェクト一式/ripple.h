//===================================
//
// �g��w�b�_�[[ripple.h]
// Author�F��������
//
//===================================
#ifndef _RIPPLE_H_			// ���̃}�N����`������Ă��Ȃ�������
#define _RIPPLE_H_			// 2�d�C���N���[�h�h�~�̃}�N�����`����

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �N���X��`(���n�̔g��)
//-----------------------------------
class CRipple : public CModel
{
public:		// �N�ł��A�N�Z�X�ł���

	CRipple();			// �R���X�g���N�^
	~CRipple();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);			// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CRipple* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);		// ��������

private:	// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	float m_fAlpha;								// �����x
};

#endif