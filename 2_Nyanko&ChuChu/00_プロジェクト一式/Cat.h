//============================================
//
// �L�w�b�_�[[Cat.h]
// Author�F��{�ėB
//
//============================================
#ifndef _CAT_H_					// ���̃}�N����`������Ă��Ȃ�������
#define _CAT_H_					// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "player.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CItemUI;			// �A�C�e��UI

//--------------------------------------------
// �N���X(�v���C���[�N���X)
//--------------------------------------------
class CCat : public CPlayer
{
public:			// �N�ł��A�N�Z�X�ł���

	//************************************************************
	//	�񋓌^��`(���[�V�����̎��)
	//************************************************************
	enum MOTIONTYPE
	{
		MOTIONTYPE_NEUTRAL = 0,		// �ҋ@
		MOTIONTYPE_MOVE,			// �ړ�
		MOTIONTYPE_ATTACK,			// �U��
		MOTIONTYPE_KNOCKBACK,		// �������
		MOTIONTYPE_STUN,			// �C��
		MOTIONTYPE_WIN,				// ����
		MOTIONTYPE_LOSE,			// �s�k
		MOTIONTYPE_MAX				// ���̗񋓌^�̑���
	};

	enum ATTACKSTATE
	{
		ATTACKSTATE_MOVE = 0,		// �ړ�
		ATTACKSTATE_STANDBY,		// �X�^���o�C
		ATTACKSTATE_ATTACK,			// �U����
		ATTACKSTATE_MAX				// ���̗񋓌^�̑���
	};

	CCat();				// �R���X�g���N�^
	~CCat();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void Hit(void);							// �q�b�g����
	void MotionManager(void);				// ���[�V�����}�l�[�W���[
	void GetItem(const CItem::TYPE type);	// �A�C�e���̎擾����

	// �Z�b�g�E�Q�b�g�֐�
	void SetItemUI(void);					// �A�C�e��UI�̐ݒ菈��
	CItemUI* GetItemUI(void) const;			// �A�C�e��UI�̎擾����
	void DeleteItemUI(void);				// �A�C�e��UI�̏�������
	int GetItemCount(void) const override;	// �A�C�e���̑����̎擾����

	bool GetAttack_Jump(void) { return m_bAttack; }	// �A�^�b�N�W�����v��Ԃ̎擾����
	bool GetItem_MultiAction(void) { return m_bItem; }

	void SetData(const D3DXVECTOR3& pos, const int nID, const TYPE type);		// ���̐ݒ菈��

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void Gravity(void);				// �d�͏���
	void Attack(void);				// �U������
	void AttackStateManager(void);	// �U����ԃ}�l�[�W���[
	void AttackBlock(void);			// �u���b�N�ւ̍U������
	void Elevation(void);			// �N���n�ʂ̓����蔻��
	void ItemSet(void);				// �l�R�̃A�C�e���ݒu����
	void DebugMessage(void);		// �f�o�b�O���b�Z�[�W����

	// �����o�ϐ�
	CItemUI* m_pItemUI;				// �A�C�e��UI�̏��
	D3DXVECTOR3 m_AttackPos;		// �U���̈ʒu
	D3DXVECTOR3 m_posDest;			// �ړI�̈ʒu
	D3DXVECTOR3 m_rotDest;			// �ړI�̌���
	int m_nShadowIdx;				// �e�̃C���f�b�N�X
	int m_nItemCount;				// �A�C�e���̏�����

	ATTACKSTATE m_AttackState;		// �U���̏��
	int m_nAtkStateCount;			// �U���̏�Ԃ̃J�E���g
	int m_nAtkTime;					// �U�����o�Ă��鎞��
	bool m_bAttack;					// �U�������Ă��邩�ǂ���
	bool m_bItem;					// �A�C�e�����g�p���Ă��邩
	bool m_bSE;						// SE�Đ����Ă邩
};

#endif