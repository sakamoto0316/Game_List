//===================================
//
// 2D�c���w�b�_�[[locus2D.h]
// Author ��������
//
//===================================
#ifndef _LOCUS2D_H_
#define _LOCUS2D_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "object2D.h"

//-----------------------------------
// �N���X��`(CLocus2D)
//-----------------------------------
class CLocus2D : public CObject2D
{
public:			// �N�ł��A�N�Z�X�ł���

	CLocus2D();				// �R���X�g���N�^
	~CLocus2D();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& size, const float fAlpha, const int nLife, const int nTexIdx);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CLocus2D* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& size, const float fAlpha, const int nLife, const int nTexIdx);	// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	int m_nLife;			// ����
	float m_fSub;			// �����x�̌�����
	float m_fAlpha;			// �����x
};

#endif