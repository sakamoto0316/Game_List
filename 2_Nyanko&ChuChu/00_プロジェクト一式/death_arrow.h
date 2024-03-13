//===================================
//
// ���S���w�b�_�[[death_arrow.h]
// Author ����������
//
//===================================
#ifndef _DEATH_ARROW_H_
#define _DEATH_ARROW_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �N���X(���S���N���X)
//-----------------------------------
class CDeathArrow : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	CDeathArrow();			// �R���X�g���N�^
	~CDeathArrow();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& rot, const int nIdx);		// ���̐ݒ菈��

	//�Z�b�g�E�Q�b�g�֌W

	// �ÓI�����o�֐�
	static CDeathArrow* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& rot, const int nIdx);		// ��������

private:		// ���������A�N�Z�X�ł���
	D3DXVECTOR3 m_pos;		// �ʒu
	D3DXVECTOR3 m_rot;		// ����
	int m_nPlayerIdx;		// �v���C���[�ԍ�

};

#endif