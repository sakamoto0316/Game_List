//===================================
//
// �G���g���[��ID�w�b�_�[[entry_ID.h]
// Author ��������
//
//===================================
#ifndef _ENTRY_ID_H_
#define _ENTRY_ID_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "object2D.h"

//-----------------------------------
// �N���X��`(CEntryID)
//-----------------------------------
class CEntryID : public CObject2D
{
public:			// �N�ł��A�N�Z�X�ł���

	CEntryID();			// �R���X�g���N�^
	~CEntryID();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const int nID);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CEntryID* Create(const D3DXVECTOR3& pos, const int nID);		// ��������

private:		// ���������A�N�Z�X�ł���

};

#endif