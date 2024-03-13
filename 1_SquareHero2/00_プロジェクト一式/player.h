//============================================
//
//	�v���C���[�̏��� [playerlevel.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _PLAYERLEVEL_H_
#define _PLAYERLEVEL_H_

#include "object.h"

#define PLAYER_LIFE (500.0f)		//�v���C���[�̏������C�t

//�O���錾
class CModel;
class CMotion;
class CObjGauge2D;
class CObjmeshCube; 
class CNumber; 
class CObject3D; 

//�I�u�W�F�N�g�v���C���[�N���X
class CPlayer : public CObject
{
public:
	CPlayer(int nPriority = 3);
	~CPlayer();

	//�v���C���[�̃��[�V����
	enum ACTION_TYPE
	{
		ACTION_WAIT = 0,
		ACTION_MOVE,
		ACTION_ATTACK1,
		ACTION_ATTACK2,
		ACTION_ATTACK3,
		ACTION_SKYATTACK,
		ACTION_JAMP,
		ACTION_EVASION,
		ACTION_TITLE,
		ACTION_MAX,

	};

	//�v���C���[�̏��
	enum STATE
	{
		STATE_NORMAL = 0,
		STATE_DEATH,
		STATE_WAIT,
		STATE_DAMAGE,
		STATE_EVENT,
		STATE_REVIVAL,
		STATE_MAX,
		
	};

	D3DMATRIX GetMtxWorld(void) { return m_mtxWorld; }
	static CPlayer *Create();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void TitleUpdate(void);
	void GameUpdate(void);
	void Draw(void);

	void LoadLevelData(const char *pFilename);
	void SetCameraPos(D3DXVECTOR3 pos) { m_CameraPos = pos; }
	D3DXVECTOR3 GetCameraPos(void) { return m_CameraPos; }
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	D3DXVECTOR3 GetMove(void) { return m_move; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	void SetWight(float Wight) { m_fWight = Wight; }
	float GetWight(void) { return m_fWight; }
	void SetHeight(float Height) { m_fHeight = Height; }
	float GetHeight(void) { return m_fHeight; }
	void SetLife(float Life) { m_fLife = Life; }
	int GetLife(void) { return (int)m_fLife; }
	void SetDamage(float Damage) { m_fDamage = Damage; }
	int GetDamage(void) { return (int)m_fDamage; }
	void SetReSpownPos(D3DXVECTOR3 pos) { m_ReSpownPos = pos; }
	D3DXVECTOR3 GetReSpownPos(void) { return m_ReSpownPos; }
	STATE GetState(void) { return m_State; }
	bool GetJump(void) { return m_bJump; }
	bool GetCameraDiff(void) { return CameraDiffMove; }
	int GetDodgeCount(void) { return m_nDodgeCount; }
	void HitDamage(float Damage);								//�U�����󂯂����̏���
	void SetLifeUI(void);
	CObjGauge2D* GetLifeGauge(void) { return m_pLifeGauge; }
	void DispUI(bool Set);

private:
	void MyObjCreate(void);								//�������ێ�����I�u�W�F�N�g�̐���
	void FallDamage(void);								//�����������̏���
	void StateManager(void);							//��ԊǗ�
	void Move2D(void);									//�ړ�����
	void Rot2D(void);									//�ړ���������
	void Dodge2D(void);									//�������
	void Move(void);									//�ړ�����
	void Rot(void);										//�ړ���������
	void Jump(void);									//�W�����v����
	void Dodge(void);									//�������
	void Attack(void);									//�U������
	void AttackCollision(void);							//�U�����菈��
	void ActionState(void);								//���[�V�����Ə�Ԃ̊Ǘ�
	bool CollisionBlock(D3DXVECTOR3* pos, COLLISION XYZ);	//�I�u�W�F�N�g�Ƃ̓����蔻��
	bool CollisionDamageCube(D3DXVECTOR3 pos);			//�I�u�W�F�N�g�Ƃ̓����蔻��
	void CollisionBoss(void);							//�{�X�Ƃ̓����蔻��
	void CollisionBossEvent(void);						//�C�x���g�����̓����蔻��
	void DeleteMap(void);								//�}�b�v�̍폜
	void CameraDiff(void);								//�J�����̕␳�ݒ�
	bool CollisionCircle(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float nRadiusOut);	//�~�̓����蔻��
	bool CollisionShadow(void);	//�I�u�W�F�N�g�Ƃ̓����蔻��
	
	ACTION_TYPE m_Action;
	ACTION_TYPE m_AtkAction;	//�U����ԋL�^�p�ϐ�
	D3DXVECTOR3 m_CameraPos;	//�J�����ʒu
	D3DXVECTOR3 m_pos;			//�ʒu
	D3DXVECTOR3 m_posOld;		//�ߋ��̈ʒu
	D3DXVECTOR3 m_ReSpownPos;	//�����n�_
	D3DXVECTOR3 m_move;			//�ړ���
	D3DXVECTOR3 m_Objmove;		//�I�u�W�F�N�g����e�������ړ���
	D3DXVECTOR3 m_rot;			//����
	D3DXVECTOR3 m_AtkPos;		//�U���ʒu
	D3DXMATRIX m_mtxWorld;		//���[���h�}�g���b�N�X
	bool m_bWallJump;			//�ǐ����W�����v
	bool m_bAirAttack;			//�󒆂ōU�����������ǂ���
	bool m_bJump;				//�W�����v���������ǂ���
	int m_nActionCount;			//��Ԃ̃J�E���g
	bool m_nAttackHit;			//�U���������������ǂ���
	float m_nAttackDamage;		//�U����
	int m_nAttackCount;			//�U���̃J�E���g
	int m_nAttackCountMax;		//�U���̃J�E���g�ő�
	int m_nDodgeCount;			//����̃J�E���g
	int m_nDodgeCoolTime;		//����̃N�[���^�C��
	int m_nAttackChainFrame;	//�A���U���̗P�\�t���[��
	int m_nWallMoveCount;		//�ړ��̃J�E���g
	int m_nActionNotCount;		//�s���s�\�̃J�E���g
	float m_fWight;				//��
	float m_fHeight;			//����
	STATE m_State;				//���
	int m_nStateCount;			//��ԊǗ��p�J�E���g
	bool m_bHit;				//�U��������������ǂ���
	bool m_GameEnd;				//�Q�[�����I��������ǂ���
	bool m_bRight;				//2D��ʂ̍ۂɍŌ�ɓ��͂����������E���ǂ���
	float m_fLife;				//�v���C���[�̃��C�t
	float m_fLifeMax;			//�v���C���[�̃��C�t�̍ő�l
	float m_fDamage;			//��������_���[�W��
	CObjGauge2D* m_pLifeGauge;	//���C�t�Q�[�W�̃|�C���^
	CObjGauge2D *m_pLifeGaugeBG;//���C�t�Q�[�W�̑O�ʃ|���S��
	bool CameraDiffMove;		//�J�����̏㉺�����ړ����ɂ₩���ۂ�
	int CameraDiffTime;			//�J�����̏㉺�����ړ����ɂ₩�Ȏ���
	CNumber* m_pLifeNumber[4];	//���C�t�pUI
	CObject3D* m_pShadow;		//�e
	int m_nBossDamageCount;		//�{�X�ڐG���̔�e�J�E���g

	CModel *m_apModel[64];
	CMotion *m_pMotion;
	char *m_aModelName[64];
	int m_nNumModel;
};

#endif