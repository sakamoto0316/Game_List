//===================================
//
// ������w�b�_�[[confetti.h]
// Author ��������
//
//===================================
#ifndef _CONFETTI_H_
#define _CONFETTI_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "object3D.h"

//-----------------------------------
// �N���X��`(CConfetti)
//-----------------------------------
class CConfetti : public CObject3D
{
public:

	CConfetti();			// �R���X�g���N�^
	~CConfetti();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const D3DXVECTOR3& rotMove, const float fGravity, const D3DXCOLOR& col, const int nLife);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CConfetti* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const D3DXVECTOR3& rotMove, const float fGravity, const D3DXCOLOR& col, const int nLife);		// ��������

private:

	// �����o�ϐ�
	D3DXVECTOR3 m_rotMove;		// �����̈ړ���
	int m_nLife;				// ����
	float m_fGravity;			// �d��
};

#endif