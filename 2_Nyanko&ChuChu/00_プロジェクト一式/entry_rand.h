//===================================
//
// �G���g���[��ʂ̃����_���w���w�b�_�[[entry_rand.h]
// Author ��������
//
//===================================
#ifndef _ENTRY_RANDOM_H_
#define _ENTRY_RANDOM_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "object2D.h"

//-----------------------------------
// �N���X(�G���g���[��ʂ̃����_���w��)
//-----------------------------------
class CEntryRandom : public CObject2D
{
public:			// �N�ł��A�N�Z�X�ł���

	CEntryRandom();			// �R���X�g���N�^
	~CEntryRandom();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(void);		// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CEntryRandom* Create(void);		// ��������

private:		// ���������A�N�Z�X�ł���


};

#endif