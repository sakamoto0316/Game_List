//===================================
//
// �v���C���[�w�b�_�[[player.h]
// Author ��������
//
//===================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "character.h"
#include "item.h"
#include "log.h"

#define LOG_MAX (16)

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CMotion;				// ���[�V����
class CPlayerID;			// �v���C���[��ID
class CStun;				// �C��
class CRatGhost;			// �H��l�Y�~
class CRessrectionFan;		// �~�͈̔�
class CRecoveringUI;		// �񕜒���UI
class CSpeechMessage;		// �`�B���b�Z�[�W
class CDeathArrow;			// ���S���

//--------------------------------------------
// �N���X(�v���C���[�N���X)
//--------------------------------------------
class CPlayer : public CCharacter
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_CAT = 0,		// �l�R
		TYPE_RAT,			// �l�Y�~
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	// �񋓌^��`(�C��p���)
	enum STUNSTATE
	{
		STUNSTATE_NONE = 0,	// �����
		STUNSTATE_SMASH,	// ������я��
		STUNSTATE_STUN,		// �C����
		STUNSTATE_WAIT,		// ���G���
		STUNSTATE_MAX,		// ���̗񋓌^�̑���
	};

	// �񋓌^��`(�ʏ�p���)
	enum STATE
	{
		STATE_NONE = 0,		// �����
		STATE_INVINCIBLE,	// ���G���
		STATE_DEATH,		// �����
		STATE_MAX			// ���̗񋓌^�̑���
	};

	CPlayer();				// �R���X�g���N�^
	CPlayer(CObject::TYPE type, PRIORITY priority = PRIORITY_PLAYER);				// �I�[�o�[���[�h�R���X�g���N�^
	virtual ~CPlayer();		// �f�X�g���N�^
	void Box(void);			// �R���X�g���N�^�̔�

	// �����o�֐�
	virtual HRESULT Init(void);		// ����������
	virtual void Uninit(void);		// �I������
	virtual void Update(void);		// �X�V����
	virtual void Draw(void);		// �`�揈��

	virtual void Hit(void) = 0;						// �q�b�g����
	void Smash(const float fAngle);					// ������я��
	bool Stun(int StunTime);						// �C����
	virtual void MotionManager(void) = 0;			// ���[�V�����}�l�[�W���[
	virtual void GetItem(const CItem::TYPE type);	// �A�C�e���̎擾����
	virtual int GetItemCount(void) const;			// �A�C�e���̎擾����
	virtual void SetEnableJump(const bool bJump);	// �W�����v�̐ݒ菈��

	virtual void SetData(const D3DXVECTOR3& pos, const int nID, const TYPE type);		// ���̐ݒ菈��
	void CameraUpdate(void);			// �J�������̍X�V

	// �Z�b�g�E�Q�b�g�֌W
	void SetMotion(CMotion* pMotion);			// ���[�V�����̐ݒ菈��
	CMotion* GetMotion(void) const;				// ���[�V�����̎擾����

	CPlayerID* GetPlayerID(void) const;			// �v���C���[ID�̏��̎擾����

	void SetStun(const D3DXVECTOR3& pos);		// �C�≉�o�̐ݒ菈��
	CStun* GetStun(void) const;					// �C�≉�o�̎擾����
	void DeleteStun(void);						// �C�≉�o�̏�������

	void SetRatGhost(const D3DXVECTOR3& pos);	// �H��l�Y�~�̐ݒ菈��
	CRatGhost* GetRatGhost(void);				// �H��l�Y�~�̎擾����
	void DeleteRatGhost(void);					// �H��l�Y�~�̏�������

	void SetRessrectionFan(const D3DXVECTOR3& pos, const D3DXCOLOR& col);	// �~�͈̔͂̐ݒ菈��
	CRessrectionFan* GetRessrectionFan(void);	// �~�͈̔͂̎擾����
	void DeleteRessrectionFan(void);			// �~�͈̔͂̏�������

	void SetRecoveringUI(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld);	// �񕜒�UI�̐ݒ菈��
	CRecoveringUI* GetRecoveringUI(void);		// �񕜒�UI�̎擾����
	void DeleteRecoveringUI(void);				// �񕜒�UI�̏�������

	void SetSpeechMessage(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const int nLife, const int type);				// �`�B���b�Z�[�W�̐ݒ菈��
	CSpeechMessage* GetSpeechMessage(void);		// �`�B���b�Z�[�W�̎擾����
	void DeleteSpeechMessage(void);				// �`�B���b�Z�[�W�̏�������

	void SetDeathArrow(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& rot, const int nIdx, const int PlayerIdx);		// ���S���̐ݒ菈��
	CDeathArrow* GetDeathArrow(const int nIdx);			// ���S���̎擾����
	void DeleteDeathArrow(const int nIdx);				// ���S���̏�������

	//void SetMove(const D3DXVECTOR3& move);		// �ړ��ʂ̐ݒ菈��
	//D3DXVECTOR3 GetMove(void) const;			// �ړ��ʂ̎擾����

	void SetSizeColl(const D3DXVECTOR3& size);	// �����蔻��T�C�Y�̐ݒ菈��
	D3DXVECTOR3 GetSizeColl(void) const;		// �����蔻��T�C�Y�̎擾����

	void SetType(const TYPE type);				// ��ނ̐ݒ菈��
	TYPE GetType(void) const;					// ��ނ̎擾����

	int GetPlayerIdx(void) const;				// �v���C���[��ID�̎擾����

	void SetSpeed(const float fSpeed);			// ���x�̐ݒ菈��
	float GetSpeed(void) const;					// ���x�̎擾����

	void SetSpeedCopy(const float fSpeed);		// ���x�̃R�s�[�̐ݒ菈��
	float GetSpeedCopy(void) const;				// ���x�̃R�s�[�̎擾����

	void SetStunHeight(const float fHeight);	// �C��̏o�鍂���̐ݒ菈��

	void SetEnableAttack(const bool bAttack);	// �U������̐ݒ菈��
	bool IsAttack(void) const;					// �U������̎擾����

	void SetEnableMove(const bool bMove);		// �ړ��󋵂̐ݒ菈��
	bool IsMove(void) const;					// �ړ��󋵂̎擾����

	void SetTutorial(const bool bTutorial) { m_bTutorial = bTutorial; }	// �ړ��󋵂̐ݒ菈��
	bool GetTutorial(void) { return m_bTutorial; }						// �ړ��󋵂̎擾����

	void SetResurrectionTime(const int nRezTime);	// ���񂾃l�Y�~�̕������Ԃ̍��v�ݒ�
	void AddResurrectionTime(const int nRezTime);	// ���񂾃l�Y�~�̕������Ԃ̍��v�ǉ�
	int GetResurrectionTime(void);					// ���񂾃l�Y�~�̕������Ԃ̍��v�擾

	void SetStunState(STUNSTATE StunState) { m_StunState = StunState; }	// �C���Ԃ̐ݒ菈��
	STUNSTATE GetStunState(void) { return m_StunState; }				// �C���Ԃ̎擾����

	void SetDispRecoveringUI(const bool bRez);	// �񕜒�UI�̕\������
	bool IsDispRecoveringUI(void);				// �񕜒�UI�̕\���擾

	void SetState(STATE State);							// ��Ԃ̐ݒ菈��
	STATE GetState(void) { return m_State; }			// ��Ԃ̎擾����

	void SetLogPlayer(int LogPlayer) { m_nLogPlayer = LogPlayer; }		// ��Ԃ̐ݒ菈��
	int GetLogPlayer(void) { return m_nLogPlayer; }						// ��Ԃ̎擾����

	void SetSE(bool bSe);			// SE�̍Đ��ݒ�
	bool GetSE(void);				// SE�̍Đ��擾

	//�`���[�g���A���p�Q�b�g�֐�-----------------------------------------
	void SetBMove(bool Set) { m_bMove = Set; }			// �ړ���Ԃ̐ݒ菈��
	bool GetBMove(void) { return m_bMove; }				// �ړ���Ԃ̎擾����
	virtual bool GetAttack_Jump(void) { return false; }	// �A�^�b�N�W�����v��Ԃ̎擾����
	void SetRatKill(bool Set) { m_bKill = Set; }		// �L���̐ݒ菈��
	bool GetRatKill(void) { return m_bKill; }			// �L���̎擾����
	void SetRatStun(bool Set) { m_bStun = Set; }		// �X�^���̐ݒ菈��
	bool GetRatStun(void) { return m_bStun; }			// �X�^���̎擾����
	void SetRatRescue(bool Set) { m_bRescue = Set; }	// �~���̐ݒ菈��
	bool GetRatRescue(void) { return m_bRescue; }		// �~���̎擾����
	void SetUseAction(bool Set) { m_bAction = Set; }	// �N���̐ݒ菈��
	bool GetUseAction(void) { return m_bAction; }		// �N���̎擾����
	virtual bool GetItem_MultiAction(void) { return false; }	// �A�C�e���g�p�ƘA�g�N���̎擾����
	//-------------------------------------------------------------------

	void SetStateCount(const int nCount) { m_StateCount = nCount; };		// ��ԃJ�E���g�̐ݒ菈��

	void SetLog(int PlayerIdx, CLog::TYPE Type);				// ���O�̐����Ɛ����ԍ��̉��Z
	void DelLogNumber(int nLogIdex);			// ���O�̐����ԍ��̌��Z

	// �ÓI�����o�֐�
	static CPlayer* Create(const D3DXVECTOR3& pos, const int nID, const TYPE type);		// ��������

protected:		// �����Ɣh���N���X�������A�N�Z�X�ł���

	// �����o�֐�
	void MoveControl(void);		// �ړ����쏈��
	void Move(void);			// �ړ�����
	void RotNormalize(void);	// �����̕␳����

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void StunStateManager(void);		// �C���Ԃ̊Ǘ�
	void StateManager(void);			// ��Ԃ̊Ǘ�

	// �����o�ϐ�
	CMotion* m_pMotion;			// ���[�V�����̏��
	CPlayerID* m_pPlayerID;		// �v���C���[��ID
	CStun* m_pStun;				// �C��̏��
	CRatGhost* m_pRatGhost;		// �H��l�Y�~�̏��
	CRessrectionFan* m_pRessrectionFan;		// �~�͈̔͂̏��
	CRecoveringUI* m_pRecoveringUI;			// �񕜒���UI�̏��
	CSpeechMessage* m_pSpeechMessage;		// �`�B���b�Z�[�W�̏��
	CDeathArrow* m_pDeathArrow[MAX_PLAY];	// ���S���̏��
	D3DXVECTOR3 m_sizeColl;		// �����蔻��̃T�C�Y
	D3DXCOLOR m_col;			// �F
	TYPE m_type;				// ���
	int m_nPlayerIdx;			// �v���C���[�̃C���f�b�N�X
	float m_fSpeed;				// ���x
	float m_fSpeedCopy;			// ���x�̃R�s�[
	float m_fRotDest;			// �ڕW
	float m_fStunHeight;		// �C�₪�o�鍂��
	bool m_bAttack;				// �U��������
	bool m_bMove;				// �ړ����Ă��邩
	bool m_bDeath;				// ���S���Ă��邩
	bool m_bDisp;				// �\�����邩
	bool m_bDispSmash;			// ������їp�̕\�����邩
	STUNSTATE m_StunState;		// �C��̏�ԊǗ�
	int m_StunStateCount;		// ��ԊǗ��p�J�E���g
	STATE m_State;				// ��ԊǗ�
	int m_StateCount;			// ��ԊǗ��p�J�E���g
	D3DXVECTOR3 m_CameraRot;	// �J�����̌���
	int m_nResurrectionTime;	// ��������܂ł̎���
	CLog *m_apLog[LOG_MAX];		// ���O
	int m_nLogPlayer;			// ���O�ɕ\������v���C���[�̔ԍ�
	int m_nLogNumber;			// ���O�̐����ԍ�
	bool m_bTutorial;			// �`���[�g���A����Ԃ��ǂ���
	bool m_bStun;				// �X�^�����s�������ǂ���
	bool m_bKill;				// �L�����s�������ǂ���
	bool m_bRescue;				// �~�����s�������ǂ���
	bool m_bAction;				// �N�����s�������ǂ���
	bool m_bSe;					// SE�Đ��������ǂ���
	bool m_bCatSe;				// �l�R�pSE�Đ���
	bool m_bRatSe;				// �l�Y�~�pSE�Đ���
};

#endif