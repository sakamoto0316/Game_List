//===================================
//
// �G���g���[�̘g�w�b�_�[[entry_frame.h]
// Author ��������
//
//===================================
#ifndef _ENTRY_FRAME_H_
#define _ENTRY_FRAME_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "object2D.h"

//-----------------------------------
// �N���X��`(CEntryFrame)
//-----------------------------------
class CEntryFrame : public CObject2D
{
public:			// �N�ł��A�N�Z�X�ł���

	CEntryFrame();			// �R���X�g���N�^
	~CEntryFrame();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);					// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CEntryFrame* Create(const D3DXVECTOR3& pos);		// ��������

private:		// ���������A�N�Z�X�ł���

};

#endif