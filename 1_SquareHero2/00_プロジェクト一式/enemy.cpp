//============================================
//
//	�G�̏��� [enemy.cpp]
//	Author:sakamoto kai
//
//============================================
#include "enemy.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "texture.h"
#include "XModel.h"
#include "player.h"
#include "Particle.h"
#include "CubeBlock.h"
#include "sound.h"
#include "modelEffect.h"
#include "CubeEffect.h"
#include "camera.h"

//�}�N����`
#define COLLISION_SIZE (D3DXVECTOR3(20.0f,20.0f,20.0f))		//�����蔻��
#define MOVE_SPEED (3.0f)									//�ړ����x
#define MOVE_COLLISION (250.0f)								//�U�������͈�
//====================================================================
//�R���X�g���N�^
//====================================================================
CEnemy::CEnemy(int nPriority) : CObjectX(nPriority)
{
	SetWight(COLLISION_SIZE.x);
	SetHeight(COLLISION_SIZE.y);
	m_nIdxXModel = NULL;			//�}�e���A���̐�
	m_CollisionPos = INITVECTOR3;
	m_bCollision = false;
	m_State = STATE_NORMAL;
	m_Action = ACTION_NORMAL;
	m_nStateCount = 0;
	m_ColorA = 1.0f;
	m_AttackCount = 0;
	m_AttackWave = 0;
	m_AttackCoolTime = 0;
	m_Scaling = 1.0f;
	m_bRevivalColorSwitch = false;
	m_AttackPattern = ATTACK_RUSH;
	m_nParticleCount = 0;
	m_fColorA = 0.0f;
}

//====================================================================
//�f�X�g���N�^
//====================================================================
CEnemy::~CEnemy()
{

}

//====================================================================
//��������
//====================================================================
CEnemy* CEnemy::Create(char* pModelName)
{
	CEnemy* pBlock = NULL;

	if (pBlock == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pBlock = new CEnemy();
	}

	//�I�u�W�F�N�g�̏���������
	if (FAILED(pBlock->Init(pModelName)))
	{//���������������s�����ꍇ
		return NULL;
	}

	return pBlock;
}

//====================================================================
//����������
//====================================================================
HRESULT CEnemy::Init(char* pModelName)
{
	SetType(CObject::TYPE_ENEMY3D);

	CObjectX::Init(pModelName);

	switch (CScene::GetMode())
	{
	case CScene::MODE_TITLE:
		break;

	case CScene::MODE_GAME:
		break;

	case CScene::MODE_RESULT:
		break;
	}


	return S_OK;
}

//====================================================================
//�I������
//====================================================================
void CEnemy::Uninit(void)
{
	for (int nCntX = -1; nCntX <= 1; nCntX++)
	{
		for (int nCntY = -1; nCntY <= 1; nCntY++)
		{
			for (int nCntZ = -1; nCntZ <= 1; nCntZ++)
			{
				CCubeEffect* pCEffect = CCubeEffect::Create();
				pCEffect->SetPos(D3DXVECTOR3(GetPos().x + (10.0f * nCntX) , GetPos().y + (10.0f * nCntY), GetPos().z + (10.0f * nCntZ)));
				pCEffect->SetMove(D3DXVECTOR3((1.0f * nCntX), (1.0f * nCntY) + 10.0f, (1.0f * nCntZ)));
				pCEffect->SetSize(D3DXVECTOR3(10.0f, 10.0f, 10.0f));
				pCEffect->SetFall(true);
			}
		}
	}

	CObjectX::Uninit();
}

//====================================================================
//�X�V����
//====================================================================
void CEnemy::Update(void)
{
	switch (CScene::GetMode())
	{
	case CScene::MODE_TITLE:
		TitleUpdate();
		break;

	case CScene::MODE_GAME:
		GameUpdate();
		break;

	case CScene::MODE_RESULT:
		break;
	}
}

//====================================================================
//�^�C�g���ł̍X�V����
//====================================================================
void CEnemy::TitleUpdate(void)
{
	D3DXVECTOR3 pos = GetPos();

	//�ʒu�X�V
	pos += m_move;

	SetPos(pos);

	//���_���̍X�V
	CObjectX::Update();
}

//====================================================================
//�Q�[���ł̍X�V����
//====================================================================
void CEnemy::GameUpdate(void)
{
	//�X�V�O�̈ʒu���ߋ��̈ʒu�Ƃ���
	m_posOld = m_pos;

	//�ʏ펞�̓���
	if (m_Action == ACTION_NORMAL)
	{
		D3DXVECTOR3 PlayerPos = CGame::GetPlayer()->GetPos();

		m_rot.y = atan2f(m_pos.x - PlayerPos.x, m_pos.z - PlayerPos.z);

		m_move.x = sinf(m_rot.y + D3DX_PI) * MOVE_SPEED;
		m_move.z = cosf(m_rot.y + D3DX_PI) * MOVE_SPEED;
	}

	if (m_Action != ACTION_PARTICLE)
	{
		//�d��
		m_move.y -= 0.98f;

		//�������x�����ȏ�ɂȂ����ꍇ�W�����v��s�\�ɂ���
		if (m_move.y < -5.0f)
		{
			if (m_bJump == false)
			{
				m_bJump = true;
			}
		}

		//�����W��
		if (m_bJump == false)
		{
			m_move.x = m_move.x * 0.5f;
			if (m_move.x <= 0.0001f && m_move.x >= -0.0001f)
			{
				m_move.x = 0.0f;
			}

			m_move.z = m_move.z * 0.5f;
			if (m_move.z <= 0.0001f && m_move.z >= -0.0001f)
			{
				m_move.z = 0.0f;
			}
		}

		if (m_bJump == true)
		{
			m_Objmove.x = m_Objmove.x * 0.25f;
			if (m_Objmove.x <= 0.0001f && m_Objmove.x >= -0.0001f)
			{
				m_Objmove.x = 0.0f;
			}

			m_Objmove.z = m_Objmove.z * 0.25f;
			if (m_Objmove.z <= 0.0001f && m_Objmove.z >= -0.0001f)
			{
				m_Objmove.z = 0.0f;
			}
		}

		if (CManager::GetInstance()->GetCamera()->GetCameraMode() == CCamera::CAMERAMODE_SIDEVIEW)
		{
			m_pos.z = 0.0f;
		}

		//Y���̈ʒu�X�V
		m_pos.y += m_move.y;
		m_pos.y += m_Objmove.y;

		CollisionBlock(&m_pos, COLLISION::COLLISION_Y);

		//X���̈ʒu�X�V
		m_pos.x += m_move.x;
		m_pos.x += m_Objmove.x;

		CollisionBlock(&m_pos, COLLISION::COLLISION_X);

		//Z���̈ʒu�X�V
		m_pos.z += m_move.z;
		m_pos.z += m_Objmove.z;

		CollisionBlock(&m_pos, COLLISION::COLLISION_Z);

		if (m_AttackCoolTime > 0)
		{
			m_AttackCoolTime--;
		}
		else
		{
			AttackCollision();
		}
	}

	CObjectX::SetPos(m_pos);
	CObjectX::SetRot(m_rot);

	//��ʊO����
	if (m_pos.y < 0.0f)
	{
		HitDamage(1.0f);
	}

	SetScaling(D3DXVECTOR3(m_Scaling, m_Scaling, m_Scaling));

	//�s���Ǘ�
	ActionManager();

	//��ԊǗ�
	StateManager();

	//���_���̍X�V
	CObjectX::Update();
}

//====================================================================
//�`�揈��
//====================================================================
void CEnemy::Draw(void)
{
	CObjectX::Draw();
}

//====================================================================
//�s���Ǘ�
//====================================================================
void CEnemy::ActionManager(void)
{
	switch (m_Action)
	{
	case CEnemy::ACTION_NORMAL:
		break;

	case CEnemy::ACTION_ATTACK:
		AttackUpdate();
		break;

	case CEnemy::ACTION_EVENT:
		break;

	case CEnemy::ACTION_PARTICLE:
		m_nParticleCount++;

		m_fColorA += 0.008f;

		SetMatColor(D3DXCOLOR(m_fColorA, m_fColorA, m_fColorA, m_fColorA));

		if (m_nParticleCount % 5 == 0)
		{
			CParticle* Particle = CParticle::Create(
				m_pos,
				D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f),
				30,
				40.0f,
				2
			);
		}

		if (m_nParticleCount > 120)
		{
			SetDefColor();
			m_Action = ACTION_NORMAL;
		}
		break;

	default:
		break;
	}
}

//====================================================================
//��ԊǗ�
//====================================================================
void CEnemy::StateManager(void)
{
	switch (m_State)
	{
	case STATE_NORMAL:
		break;
	case ACTION_EVENT:
		break;
	}

	if (m_nStateCount > 0)
	{
		m_nStateCount--;
	}
}

//====================================================================
//�U���X�V����
//====================================================================
void CEnemy::AttackUpdate(void)
{
	SetMatColor(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));

	switch (m_AttackPattern)
	{
	case ATTACK_RUSH:
		AttackRush();
		break;
	}
}

//====================================================================
//�U��(�ːi)
//====================================================================
void CEnemy::AttackRush(void)
{
	D3DXVECTOR3 PlayerPos = CGame::GetPlayer()->GetPos();

	switch (m_AttackWave)
	{
	case 0:
		m_AttackCount++;

		if (m_AttackCount % 5 == 0)
		{
			m_Scaling += 0.02f;
		}
		else
		{
			m_Scaling -= 0.02f;
		}

		if (m_Scaling <= 0.5f)
		{
			m_Scaling = 1.0f;
			m_AttackWave++;
			m_AttackCount = 0;
		}

		break;

	case 1:

		m_rot.y = atan2f(m_pos.x - PlayerPos.x, m_pos.z - PlayerPos.z);

		m_move.x = sinf(m_rot.y + D3DX_PI) * MOVE_SPEED * 2.0f;
		m_move.y = 20.0f;
		m_move.z = cosf(m_rot.y + D3DX_PI) * MOVE_SPEED * 2.0f;
		m_bJump = true;

		m_AttackWave++;

		break;

	case 2:
		m_AttackCount++;

		if (m_AttackCount % 5 == 0)
		{
			//���f���G�t�F�N�g�̐���
			CModelEffect* pMEffect = CModelEffect::Create("data\\MODEL\\enemy.x");
			pMEffect->SetPos(m_pos);
			pMEffect->SetRot(m_rot);
			pMEffect->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}

		if (m_bJump == false)
		{
			m_AttackWave++;
		}

		break;

	default:
		m_move = INITVECTOR3;
		m_Action = ACTION_NORMAL;
		SetDefColor();
		m_AttackWave = 0;
		m_AttackCount = 0;
		m_AttackCoolTime = 60;
		break;
	}
}

//====================================================================
//�_���[�W����
//====================================================================
void CEnemy::HitDamage(float Damage)
{
	if (m_State == STATE_NORMAL)
	{
		//�Q�[����SE���Đ�����
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_DAMAGE_BOSS);

		//�폜
		Uninit();
	}
}

//====================================================================
//�L���[�u�u���b�N�Ƃ̓����蔻�菈��
//====================================================================
bool CEnemy::CollisionBlock(D3DXVECTOR3* pos, COLLISION XYZ)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//�I�u�W�F�N�g���擾
		CObject* pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			CObject* pObjNext = pObj->GetNext();

			CObject::TYPE type = pObj->GetType();			//��ނ��擾

			if (type == TYPE_CUBEBLOCK)
			{//��ނ��u���b�N�̎�

				if (pObj->CollisionBlock(pos, m_posOld, &m_move, &m_Objmove, COLLISION_SIZE * 0.5f, &m_bJump, XYZ) == true)
				{
					m_bJump = false;
					m_move.y = 0.0f;

					return true;
				}
			}

			pObj = pObjNext;
		}
	}

	return false;
}

//====================================================================
//�����蔻�菈��
//====================================================================
void CEnemy::AttackCollision(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//�I�u�W�F�N�g���擾
		CObject* pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			CObject* pObjNext = pObj->GetNext();

			CObject::TYPE type = pObj->GetType();			//��ނ��擾

			if (type == TYPE_PLAYER3D)
			{//��ނ��v���C���[�̎�
				if (sqrtf((pObj->GetPos().x - m_pos.x) * (pObj->GetPos().x - m_pos.x)
					+ (pObj->GetPos().z - m_pos.z) * (pObj->GetPos().z - m_pos.z)) <= MOVE_COLLISION)
				{//�~�̔��肪��������
					m_Action = ACTION_ATTACK;
				}
			}

			pObj = pObjNext;
		}
	}
}

//====================================================================
//�����蔻�菈��
//====================================================================
bool CEnemy::Collision(D3DXVECTOR3* pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3* pMove, float fHeight, float fWidth, bool* bJumpMove, bool* bHit, bool bX)
{
	bool bOn = false;

	float myWight = GetWight();
	float myHeight = GetHeight();
	D3DXVECTOR3 mtPos = GetPos();


	if (bX == false)
	{
		if (
			(pPos->y < mtPos.y + myHeight &&
				pPosOld.y >= mtPos.y + myHeight) &&
			pPos->x + fWidth > mtPos.x - myWight &&
			pPos->x - fWidth < mtPos.x + myWight
			)
		{//�ォ��߂荞�񂾎�
			bOn = true;
			pPos->y = mtPos.y + myHeight;		//�u���b�N�̂����ɂ�������
			pMove->y = 0.0f;					//�ړ��ʂ��O�ɂ���
			*bHit = true;
		}

		if (
			(pPos->y + fHeight > mtPos.y - myHeight &&
				pPosOld.y <= mtPos.y - myHeight) &&
			pPos->x + fWidth > mtPos.x - myWight &&
			pPos->x - fWidth < mtPos.x + myWight
			)
		{//������߂荞�񂾎�
			*bJumpMove = false;
			pPos->y = mtPos.y - myHeight - fHeight;		//�u���b�N�̉��Ŏ~�߂�
			pMove->y = 0.0f;					//�ړ��ʂ��O�ɂ���
			*bHit = true;
		}
	}
	else
	{
		if (
			(pPos->x + fWidth > mtPos.x - myWight &&
				pPosOld.x + fWidth <= mtPos.x - myWight) &&
			pPos->y + fHeight > mtPos.y - myHeight &&
			pPos->y < mtPos.y + myHeight
			)
		{//������߂荞�񂾎�
			pPos->x = mtPos.x - myWight - fWidth;		//�u���b�N�̍��Ŏ~�߂�
			pMove->x = 0.0f;					//�ړ��ʂ��O�ɂ���
			*bHit = true;
		}

		if (
			(pPos->x - fWidth < mtPos.x + myWight &&
				pPosOld.x - fWidth >= mtPos.x + myWight) &&
			pPos->y + fHeight > mtPos.y - myHeight &&
			pPos->y < mtPos.y + myHeight
			)
		{//�E����߂荞�񂾎�
			pPos->x = mtPos.x + myWight + fWidth;		//�u���b�N�̉E�Ŏ~�߂�
			pMove->x = 0.0f;					//�ړ��ʂ��O�ɂ���
			*bHit = true;
		}
	}

	return bOn;
}