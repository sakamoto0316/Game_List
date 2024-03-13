//===================================
//
// �l�Y�~�߂�̓S�����w�b�_�[[mousetrap_iron.h]
// Author ��������
//
//===================================
#ifndef _MOUSETRAP_IRON_H_
#define _MOUSETRAP_IRON_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �N���X��`(�l�Y�~�߂�̓S����)
//-----------------------------------
class CTrapIron : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	CTrapIron();			// �R���X�g���N�^
	~CTrapIron();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);				// ���̐ݒ菈��
	bool Move(void);		// �ړ�����

	// �ÓI�����o�֐�
	static CTrapIron* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);	// ��������

private:		// ���������A�N�Z�X�ł���

};

#endif