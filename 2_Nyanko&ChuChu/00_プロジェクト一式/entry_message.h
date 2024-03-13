//===================================
//
// �G���g���[��ʂ̑�������w�b�_�[[entry_message.h]
// Author ����������
//
//===================================
#ifndef _ENTRY_MESSAGE_H_
#define _ENTRY_MESSAGE_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "object2D.h"

//-----------------------------------
// �N���X(�G���g���[��ʂ̑�������N���X)
//-----------------------------------
class CEntryMessage : public CObject2D
{
public:			// �N�ł��A�N�Z�X�ł���

	CEntryMessage();			// �R���X�g���N�^
	~CEntryMessage();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& size);		// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CEntryMessage* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& size);		// ��������

private:		// ���������A�N�Z�X�ł���

	int m_nScaleSwitchCounter;		// �X�P�[���̑����ύX�J�E���^�[
	int m_nScaleSwitch;				// �X�P�[���̑����ύX

};

#endif