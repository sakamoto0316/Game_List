//===========================================
//
// �S�~���̃��C������[garbage.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "garbagecan.h"
#include "renderer.h"
#include "useful.h"
#include "sound.h"

#include "player.h"
#include "block.h"
#include "block_manager.h"
#include "obstacle_manager.h"
#include "collision.h"
#include "fraction.h"
#include "map.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define SPEED		(4.0f)		// ���x
#define GRAVITY		(0.4f)		// �d��
#define ROT_MOVE	(0.05f)		// �����̈ړ���
#define CAT_SIZE	(D3DXVECTOR3(70.0f, 280.0f, 70.0f))		// �����蔻��̃T�C�Y

//==============================
// �R���X�g���N�^
//==============================
CGarbage::CGarbage() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	m_State = STATE_GARBAGECAN;		// ���
	m_Slide = SLIDE_STOP;
	m_pPlayer = NULL;
	m_move = NONE_D3DXVECTOR3;
	m_SlideMove = NONE_D3DXVECTOR3;
	m_PlayerPos = NONE_D3DXVECTOR3;

	// �l�Y�~������������悤�ɂ���
	SetCatUse(false);
	SetRatUse(true);
}

//==============================
// �f�X�g���N�^
//==============================
CGarbage::~CGarbage()
{

}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CGarbage::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �j�Ђ̏I������
//========================================
void CGarbage::Uninit(void)
{
	// �I������
	CObstacle::Uninit();
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CGarbage::Update(void)
{
	//��ԊǗ�
	StateManager();

	if (m_Slide == SLIDE_ON)
	{
		D3DXVECTOR3 pos = GetPos();
		SetPosOld(pos);
		D3DXVECTOR3 posold = GetPosOld();

		pos += m_SlideMove;
		m_pPlayer->SetPos(pos + m_PlayerPos);

		if (Collision(m_pPlayer, GetFileData().vtxMax) == true || 
			MagicWall() == true ||
			((m_SlideMove.x <= 1.0f && m_SlideMove.x >= -1.0f) && (m_SlideMove.z <= 1.0f && m_SlideMove.z >= -1.0f)))
		{
			m_Slide = SLIDE_BREAK;
			m_SlideMove = D3DXVECTOR3(-m_SlideMove.x * 0.1f, 30.0f, -m_SlideMove.z * 0.1f);
		}

		SetPos(pos);
	}
	else if(m_Slide == SLIDE_BREAK)
	{
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 rot = GetRot();
		SetPosOld(pos);
		D3DXVECTOR3 posold = GetPosOld();

		m_SlideMove.y -= 1.0f;
		rot.x += 0.1f;
		rot.z += 0.3f;

		pos += m_SlideMove;

		SetPos(pos);
		SetRot(rot);

		if (pos.y < 0.0f)
		{
			Uninit();
		}
	}
}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CGarbage::Draw(void)
{
	// �`�揈��
	CObstacle::Draw(1.0f);
}

//=====================================
// ��ԊǗ�
//=====================================
void CGarbage::StateManager(void)
{
	// �ʒu�ƌ�����ݒ肷��
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	switch (m_State)
	{
	case STATE_GARBAGECAN:		// �S�~��

		break;

	case STATE_FALL:			// �������

		// �ړ��ʂ����Z����
		m_move.y -= GRAVITY;

		// �ʒu���ړ�����
		pos += m_move;

		// �������ړ�����
		rot.z += ROT_MOVE;

		// �����̐��K��
		useful::RotNormalize(&rot.z);

		if (pos.y <= 0.0f)
		{ // �n�ʈȉ��ɂȂ����ꍇ

			// �ʒu��␳����
			pos.y = 0.0f;

			// �ړ��ʂ�����������
			m_move = NONE_D3DXVECTOR3;

			// ����������������
			rot.z = 0.0f;

			// �o�i�i�̔��Ԃɂ���
			m_State = STATE_BANANA_NORMAL;

			// ���f���̏���ݒ肷��
			SetFileData(CXFile::TYPE_GARBAGE);

			// �o�i�i�����鉹�Đ�
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_BANANADOWN);
		}

		break;

	case STATE_BANANA_NORMAL:	// �o�i�i�̔�

		break;

	case STATE_BANANA_SLIDE:	// �o�i�i����

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	// �ʒu��������K�p����
	SetPos(pos);
	SetRot(rot);
}

//=====================================
// ���@�̕�
//=====================================
bool CGarbage::MagicWall(void)
{
	// �ʒu���擾����
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 Max = GetFileData().vtxMax;
	D3DXVECTOR3 Min = GetFileData().vtxMin;

	if (pos.x + Min.x <= -MAP_SIZE.x)
	{ // �ʒu��������o�����ȏꍇ

		// �ʒu��ݒ肷��
		pos.x = -MAP_SIZE.x - Min.x;

		// true ��Ԃ�
		return true;
	}

	if (pos.x + Max.x >= MAP_SIZE.x)
	{ // �ʒu���E����o�����ȏꍇ

		// �ʒu��ݒ肷��
		pos.x = MAP_SIZE.x - Max.x;

		// true ��Ԃ�
		return true;
	}

	if (pos.z + Min.z <= -MAP_SIZE.z)
	{ // �ʒu���E����o�����ȏꍇ

		// �ʒu��ݒ肷��
		pos.z = -MAP_SIZE.z - Min.z;

		// true ��Ԃ�
		return true;
	}

	if (pos.z + Max.z >= MAP_SIZE.z)
	{ // �ʒu���E����o�����ȏꍇ

		// �ʒu��ݒ肷��
		pos.z = MAP_SIZE.z - Max.z;

		// true ��Ԃ�
		return true;
	}

	// �ʒu��K�p����
	SetPos(pos);

	// false ��Ԃ�
	return false;
}

//=====================================
// �j�󎞏���
//=====================================
void CGarbage::SlideOn(D3DXVECTOR3 pos, D3DXVECTOR3 move, CPlayer *pPlayer)
{
	m_Slide = SLIDE_ON;
	m_State = STATE_BANANA_SLIDE;
	m_PlayerPos = pos - GetPos();
	m_SlideMove = move;
	m_pPlayer = pPlayer;

	// �o�i�i���鉹�Đ�
	CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_BANANATURUTURU);
}

//=====================================
// �j�󎞏���
//=====================================
void CGarbage::Break(void)
{
	if (m_State == STATE_GARBAGECAN)
	{ // �S�~����Ԃ̏ꍇ

		m_State = STATE_FALL;

		// �ړ��ʂ�ݒ肷��
		m_move.x = sinf(GetRot().y + (D3DX_PI * -0.5f)) * SPEED;
		m_move.y = 0.0f;
		m_move.z = cosf(GetRot().y + (D3DX_PI * -0.5f)) * SPEED;
	}

	// �A�N�V�����󋵂� true �ɂ���
	SetAction(true);
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CGarbage::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos,rot, type);
}

//=====================================
// �����蔻�菈��
//=====================================
bool CGarbage::Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// �ʒu�ƍő�l�ƍŏ��l��ݒ肷��
	D3DXVECTOR3 pos = pPlayer->GetPos();
	D3DXVECTOR3 move = pPlayer->GetMove();
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(collSize.x, collSize.y, collSize.z);
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);
	collision::SCollision coll = { false,false,false,false,false,false };

	if (m_State == STATE_GARBAGECAN)
	{ //�S�~����Ԃ̏ꍇ

		// �Z�ʑ̂̓����蔻��
		coll = collision::HexahedronClush(&pos, GetPos(), pPlayer->GetPosOld(), GetPosOld(), vtxMin, GetFileData().vtxMin, vtxMax, GetFileData().vtxMax);

		// �ʒu��K�p����
		pPlayer->SetPos(pos);

		if(coll.bTop == true)
		{ // ��ɏ�����ꍇ

			// �ړ��ʂ�����������
			move.y = 0.0f;

			// �ړ��ʂ�ݒ肷��
			pPlayer->SetMove(move);

			// true ��Ԃ�
			return true;
		}
	}
	else if(m_Slide == SLIDE_ON)
	{
		// �擪�̃u���b�N�̏����擾����
		CBlock* pBlock = CBlockManager::Get()->GetTop();

		while (pBlock != nullptr)
		{ // �u���b�N�� NULL �̏ꍇ

			if (collision::HexahedronCollision(&pos, pBlock->GetPos(), pPlayer->GetPosOld(), pBlock->GetPosOld(), vtxMin, pBlock->GetFileData().vtxMin, vtxMax, pBlock->GetFileData().vtxMax) == true)
			{ // �Z�ʑ̂̓����蔻�肪 true �̏ꍇ

				// �ʒu��K�p����
				pPlayer->SetPos(pos);

				// true ��Ԃ�
				return true;
			}

			// ���̃u���b�N�̏����擾����
			pBlock = pBlock->GetNext();
		}

		// �擪�̏�Q���̏����擾����
		CObstacle* pObstacle = CObstacleManager::Get()->GetTop();

		while (pObstacle != nullptr)
		{ // ��Q���� NULL �̏ꍇ

			if (pObstacle->GetType() != CObstacle::TYPE::TYPE_GARBAGECAN &&
				pObstacle->Collision(pPlayer, CAT_SIZE) == true)
			{ // �Z�ʑ̂̓����蔻�肪 true �̏ꍇ

				// �ʒu��K�p����
				pPlayer->SetPos(pos);

				// true ��Ԃ�
				return true;
			}

			// ���̏�Q���̏����擾����
			pObstacle = pObstacle->GetNext();
		}
	}

	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CGarbage::Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(collSize.x, collSize.y, collSize.z);		// �T�C�Y�̍ő�l
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);		// �T�C�Y�̍ŏ��l

	if (m_State == STATE_BANANA_NORMAL &&
		pPlayer->GetType() == CPlayer::TYPE_CAT &&
		useful::RectangleCollisionXY(GetPos(), pPlayer->GetPos(), GetFileData().vtxMax, vtxMax, GetFileData().vtxMin, vtxMin) == true &&
		useful::RectangleCollisionXZ(GetPos(), pPlayer->GetPos(), GetFileData().vtxMax, vtxMax, GetFileData().vtxMin, vtxMin) == true &&
		useful::RectangleCollisionYZ(GetPos(), pPlayer->GetPos(), GetFileData().vtxMax, vtxMax, GetFileData().vtxMin, vtxMin) == true)
	{ // �l�R���o�i�i�̔�Ɉ������������ꍇ

		// true ��Ԃ�
		return true;
	}

	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g�̉~����
//=====================================
bool CGarbage::HitCircle(CPlayer* pPlayer, const float Radius)
{
	if (GetAction() == false &&
		useful::CircleCollisionXZ(pPlayer->GetPos(), GetPos(), Radius, GetFileData().fRadius) == true)
	{ // �͈͓��ɓ����Ă���ꍇ

		// true ��Ԃ�
		return true;
	}

	// false ��Ԃ�
	return false;
}

//=====================================
// �M�~�b�N�N������
//=====================================
void CGarbage::Action(void)
{
	//�j�󎞏���
	Break();
}