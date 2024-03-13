//===================================
//
// �����Ԃ�̉~�͈̔̓w�b�_�[[resurrection_fan.h]
// Author ����������
//
//===================================
#ifndef _RESURRECTION_FAN_H_
#define _RESURRECTION_FAN_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "object3Dfan.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define NUM_REZ_ANGLE		(120)		// �p�x�̐�

//-----------------------------------
// �N���X��`(�T���v��)
//-----------------------------------
class CRessrectionFan : public CObject3DFan
{
public:			// �N�ł��A�N�Z�X�ł���

	CRessrectionFan();			// �R���X�g���N�^
	~CRessrectionFan();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXCOLOR& col);		// ���̐ݒ菈��

	// �Z�b�g�E�Q�b�g�֐�
	void SetResurrectionFan(int nFan);			// �p�x�̐ݒ�
	int GetResurrectionFan(void);				// �p�x�̎擾

	// �ÓI�����o�֐�
	static CRessrectionFan* Create(const D3DXVECTOR3& pos, const D3DXCOLOR& col);		// ��������

private:		// ���������A�N�Z�X�ł���
	int m_nRezTime;			// �񕜎���
	bool m_bRez;			// �񕜂��Ă邩

};

#endif