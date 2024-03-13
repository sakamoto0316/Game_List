//===================================
//
// ���ԃw�b�_�[[car_gear.h]
// Author ��������
//
//===================================
#ifndef _CAR_GEAR_H_
#define _CAR_GEAR_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �N���X��`(����)
//-----------------------------------
class CCarGear : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	CCarGear();			// �R���X�g���N�^
	~CCarGear();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CCarGear* Create(const D3DXVECTOR3& pos);	// ��������

private:		// ���������A�N�Z�X�ł���
	bool m_bSe;		// SE�Đ���

};

#endif