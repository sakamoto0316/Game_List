//===================================
//
// �Q�[���t�B�j�b�V���w�b�_�[[game_finish.h]
// Author �x�씋��
//
//===================================
#ifndef _GAME_FINISH_H_
#define _GAME_FINISH_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "object.h"

//-----------------------------------
// �O���錾
//-----------------------------------
class CObject2D;		// 2D�|���S��
class CGameTime;		// �Q�[���^�C��
class CCountdown;		// �J�E���g�_�E��

//-----------------------------------
// �N���X��`(GAMEFINISH)
//-----------------------------------
class CGameFinish : public CObject
{
public:			// �N�ł��A�N�Z�X�ł���

	CGameFinish();			// �R���X�g���N�^
	~CGameFinish();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	// �ݒ�擾�����֐�
	void SetData(void);				// ���̐ݒ菈��
	void SetFinish(bool bFinish);	// �I���̐ݒ菈��

	// �ÓI�����o�֐�
	static CGameFinish* Create(void);	// ��������

private:		// ���������A�N�Z�X�ł���

	float m_fSize;				// �g�嗦
	CObject2D* m_pFinish;		// �|���S���̏��
	bool m_bFinish;				// �I��������
	bool m_bSe;					// SE�Đ���
	// �ÓI�����o�ϐ�
	static CGameTime* m_pGameTime;		// �Q�[���^�C���̏��
	static CCountdown* m_pCountdown;	// �J�E���g�_�E���̏��
};

#endif