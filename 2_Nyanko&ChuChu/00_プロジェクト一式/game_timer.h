//============================================
//
// �Q�[���̎��ԃw�b�_�[[game_time.h]
// Author�F��������
//
//============================================
#ifndef _GAME_TIME_H_					// ���̃}�N����`������Ă��Ȃ�������
#define _GAME_TIME_H_					// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "object.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define GAME_TIME_DIGIT		(3)		// �Q�[���^�C�}�[�̌���

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CNumber;			// ����
class CObject2D;		// 2D�|���S��

//--------------------------------------------
// �N���X��`(�Q�[���^�C��)
//--------------------------------------------
class CGameTime : public CObject
{
public:				// �N�ł��A�N�Z�X�ł���

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(void);		// ���̐ݒ菈��
	int GetSeconds(void);	// �c��b���̎擾����

	// �ÓI�����o�ϐ�
	static CGameTime* Get(void);			// �擾����
	static CGameTime* Create(void);			// ��������

private:			// ���������A�N�Z�X�ł���

	CGameTime();			// �R���X�g���N�^
	~CGameTime();			// �f�X�g���N�^

	// �����o�֐�
	void Calculate(void);		// �v�Z����

	// �����o�ϐ�
	CNumber* m_apNumber[GAME_TIME_DIGIT];	// �ԍ��̏��
	CObject2D* m_pColon;					// �R����
	CObject2D* m_pBG;						// �w�i
	int m_nSeconds;							// �b��
	int m_nFrame;							// �t���[����

	// �ÓI�����o�ϐ�
	static CGameTime* m_pGameTimer;		// �Q�[���^�C�}�[�̏��
};

#endif