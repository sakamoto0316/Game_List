//===================================
//
// ���b�g�w�b�_�[[rat.h]
// Author ��������
//
//===================================
#ifndef _RAT_H_
#define _RAT_H_

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "player.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------


//--------------------------------------------
// �N���X(�l�Y�~�N���X)
//--------------------------------------------
class CRat : public CPlayer
{
public:			// �N�ł��A�N�Z�X�ł���

	CRat();			// �R���X�g���N�^
	~CRat();			// �f�X�g���N�^

	//************************************************************
	//	�񋓌^��`(���[�V�����̎��)
	//************************************************************
	enum MOTIONTYPE
	{
		MOTIONTYPE_NEUTRAL = 0,		// �ҋ@
		MOTIONTYPE_MOVE,			// �ړ�
		MOTIONTYPE_JUMP,			// �W�����v
		MOTIONTYPE_KNOCKBACK,		// �������
		MOTIONTYPE_DEATH,			// ���S
		MOTIONTYPE_RESURRECTION,	// �h��
		MOTIONTYPE_STUN,			// �C��
		MOTIONTYPE_WIN,				// ����
		MOTIONTYPE_MAX				// ���̗񋓌^�̑���
	};

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void Hit(void);					// �q�b�g����
	void MotionManager(void);		// ���[�V�����̊Ǘ�

	bool GetAttack_Jump(void) { return m_bJump; }	// �A�^�b�N�W�����v��Ԃ̎擾����
	void SetEnableJump(const bool bJump) override;	// �W�����v�󋵂̐ݒ菈��

	void SetData(const D3DXVECTOR3& pos, const int nID, const TYPE type);	// ���̐ݒ菈��

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void Jump(void);				// �W�����v����
	void Gravity(void);				// �d�͏���
	void Attack(void);				// �U������
	void DeathArrow(void);			// ���S���̏���
	void Elevation(void);			// �N���n�ʂ̓����蔻��
	void ResurrectionCollision(void);		// �����Ԃ�̓����蔻��

	// �����o�ϐ�
	int m_nRezCounter;				// �񕜂���܂ł̃J�E���^�[
	bool m_bJump;					// �W�����v��
	bool m_bSe;						// SE�Đ���

	// �ÓI�����o�֐�
	static bool m_bResurrection;	// ���������Ă�̂�
};

#endif