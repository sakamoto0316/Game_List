//============================================
//
//	�G�̏��� [enemy.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "objectX.h"

//�O���錾
class CObjGauge2D;
class CNumber;
class CCubeSpin;
class CObject2D;

//�I�u�W�F�N�g�v���C���[�N���X
class CEnemy : public CObjectX
{
public:

	CEnemy(int nPriority = 3);
	~CEnemy();

	//�{�X�̏��
	enum STATE
	{
		STATE_NORMAL = 0,	//�ʏ�
		STATE_MAX,
	};

	//�{�X�̍s��
	enum ACTION
	{
		ACTION_NORMAL = 0,	//�ʏ�
		ACTION_ATTACK,		//�U��
		ACTION_EVENT,		//�C�x���g��
		ACTION_PARTICLE,	//�o�ꉉ�o��
		ACTION_MAX,
	};

	//�{�X�̍U��
	enum ATTACK
	{
		ATTACK_NOT = 0,		//�U�����Ȃ�
		ATTACK_RUSH,		//�ːi
		ATTACK_MAX,

	};

	static CEnemy* Create(char* pModelName);

	HRESULT Init(char* pModelName);
	void Uninit(void);
	void Update(void);
	void TitleUpdate(void);
	void GameUpdate(void);
	void Draw(void);

	int GetIdx(void) { return m_nIdxTexture; }
	int GetIdxXModel(void) { return -1; }
	bool Collision(D3DXVECTOR3* pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3* pMove, float fHeight, float fWidth, bool* bJumpMove, bool* bHit, bool bX);
	void HitDamage(float Damage);
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	void SetAction(ACTION Action) { m_Action = Action; }
	ACTION GetAction(void) { return m_Action; }

private:
	void ActionManager(void);	//�s���Ǘ�
	void StateManager(void);	//��ԊǗ�
	void AttackUpdate(void);	//�U���X�V����
	void AttackRush(void);		//�U���p�^�[���ːi
	void AttackCollision(void);	//�I�u�W�F�N�g�Ƃ̓����蔻��
	bool CollisionBlock(D3DXVECTOR3* pos, COLLISION XYZ);	//�I�u�W�F�N�g�Ƃ̓����蔻��

	int m_nIdxXModel;				//X���f���̔ԍ�
	D3DXVECTOR3 m_CollisionPos;		//�����蔻��p�̍��W
	bool m_bCollision;				//�����蔻��p�̍��W
	int m_nIdxTexture;				//�e�N�X�`���̔ԍ�
	STATE m_State;					//���
	ACTION m_Action;				//�s��
	int m_nStateCount;				//��ԊǗ��p�ϐ�
	float m_ColorA;					//�s�����x
	ATTACK m_AttackPattern;			//�U���p�^�[��
	int m_AttackCount;				//�U���Ɏg���J�E���g
	int m_AttackWave;				//�U���i�K
	int m_AttackCoolTime;			//�U���Ɏg���J�E���g
	float m_Scaling;				//�傫��
	bool m_bRevivalColorSwitch;		//�h�����̐F�̕ω�
	D3DXVECTOR3 m_pos;				//�ʒu	
	D3DXVECTOR3 m_posOld;			//�ߋ��̈ʒu	
	D3DXVECTOR3 m_move;				//�ړ���	
	D3DXVECTOR3 m_Objmove;			//�I�u�W�F�N�g����󂯂�ړ���	
	D3DXVECTOR3 m_rot;				//����	
	bool m_bJump;					//�W�����v�������ǂ���
	int m_nParticleCount;			//�p�[�e�B�N���J�E���g
	float m_fColorA;				//�s�����x
};
#endif