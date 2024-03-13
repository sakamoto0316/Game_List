//===========================================
//
// �{�̃��C������[hairball.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "hairball.h"
#include "collision.h"
#include "useful.h"
#include "sound.h"

#include "objectElevation.h"
#include "elevation_manager.h"
#include "block.h"
#include "block_manager.h"
#include "map.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define GRAVITY		(0.5f)		// �d��

//==============================
// �R���X�g���N�^
//==============================
CHairBall::CHairBall() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_state = STATE_STOP;			// ���
	SetCatDisp(true);				// �L���̉�ʂ̕s�����x�������I��1.0f�ɂ���
}

//==============================
// �f�X�g���N�^
//==============================
CHairBall::~CHairBall()
{

}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CHairBall::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_state = STATE_STOP;			// ���

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �j�Ђ̏I������
//========================================
void CHairBall::Uninit(void)
{
	// �I������
	CObstacle::Uninit();
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CHairBall::Update(void)
{
	// �O��̈ʒu��ݒ肷��
	SetPosOld(GetPos());

	switch (m_state)
	{
	case STATE_STOP:

		// ���ɂȂ�

		break;

	case STATE_SMASH:

		// �ړ�����
		Move();

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	// �d�͏���
	Gravity();

	// �N���n�ʂƂ̓����蔻��
	Elevation();

	// �u���b�N�Ƃ̓����蔻��
	Block();

	// ���@�̕Ǐ���
	MagicWall();
}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CHairBall::Draw(void)
{
	// �`�揈��
	CObstacle::Draw(1.0f);
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CHairBall::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos,rot, type);

	// �S�Ă̒l��ݒ肷��
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_state = STATE_STOP;			// ���
}

//=====================================
// �����蔻�菈��
//=====================================
bool CHairBall::Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// �ʒu���擾����
	D3DXVECTOR3 pos = pPlayer->GetPos();

	if (pos.y <= GetPos().y + GetFileData().vtxMax.y &&
		pos.y + collSize.y >= GetPos().y + GetFileData().vtxMin.y)
	{ // �{�ƏՓ˂����ꍇ

		// �~���̓����蔻�菈��
		useful::CylinderCollision(&pos, GetPos(), GetFileData().fRadius + collSize.x);
	}

	// �ʒu��K�p����
	pPlayer->SetPos(pos);

	// false �̏ꍇ
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CHairBall::Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// �^�[�Q�b�g�̈ʒu�ƕ�����錾
	D3DXVECTOR3 Targetpos = pPlayer->GetPos();
	float fAngle = 0.0f;

	if (pPlayer->GetType() == CPlayer::TYPE_CAT)
	{ // �l�R�̏ꍇ

		if (Targetpos.y <= GetPos().y + GetFileData().vtxMax.y &&
			Targetpos.y + collSize.y >= GetPos().y + GetFileData().vtxMin.y &&
			useful::CylinderInner(Targetpos, GetPos(), GetFileData().fRadius + collSize.x) == true)
		{ // �{�ƏՓ˂����ꍇ

			// �܂��SE�炷
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_HAIRBALL);

			// ������΂���Ԃɂ���
			m_state = STATE_SMASH;
			SetFileData((CXFile::TYPE)(CXFile::TYPE_RED_HAIRBALL));
			SetAction(true);

			// ������ݒ肷��
			fAngle = atan2f((GetPos().x - Targetpos.x), (GetPos().z - Targetpos.z));

			// �ړ��ʂ�ݒ肷��
			m_move.x = sinf(fAngle) * 15.0f;
			m_move.y = 15.0f;
			m_move.z = cosf(fAngle) * 15.0f;

			// true ��Ԃ�
			return false;
		}
		else
		{ // ��L�ȊO

			// false ��Ԃ�
			return false;
		}
	}
	else
	{ // ��L�ȊO

		if (m_state == STATE_SMASH &&
			Targetpos.y <= GetPos().y + GetFileData().vtxMax.y &&
			Targetpos.y + collSize.y >= GetPos().y + GetFileData().vtxMin.y &&
			useful::CylinderCollision(&Targetpos, GetPos(), GetFileData().fRadius + collSize.x) == true)
		{ // �{�ƏՓ˂����ꍇ

			// true ��Ԃ�
			return true;
		}
		else
		{ // ��L�ȊO

			// false ��Ԃ�
			return false;
		}
	}
}

//=====================================
// �ړ�����
//=====================================
void CHairBall::Move(void)
{
	// �ʒu���擾����
	D3DXVECTOR3 pos = GetPos();

	// �ʒu���ړ�����
	pos.x += m_move.x;
	pos.z += m_move.z;

	// �ʒu��K�p����
	SetPos(pos);
}

//=====================================
// �d�͏���
//=====================================
void CHairBall::Gravity(void)
{
	// �ʒu���擾����
	D3DXVECTOR3 pos = GetPos();

	// �d�͏���
	useful::Gravity(&m_move.y, &pos.y, GRAVITY);
	
	// �ʒu��ݒ肷��
	SetPos(pos);
}

//=====================================
// �N���n�ʂ̓����蔻��
//=====================================
void CHairBall::Elevation(void)
{
	// ���[�J���ϐ��錾
	CElevation* pMesh = CElevationManager::Get()->GetTop();		// �N���̐擪�̃I�u�W�F�N�g���擾����
	D3DXVECTOR3 pos = GetPos();				// �ʒu���擾����
	float fHeight = 0.0f;					// ����
	bool bLand = false;						// ���n��

	while (pMesh != nullptr)
	{ // �n�ʂ̏�񂪂�������

		// �����蔻������
		fHeight = pMesh->ElevationCollision(pos);

		if (pos.y + GetFileData().vtxMin.y <= fHeight)
		{ // �����蔻��̈ʒu�����������ꍇ

			// ������ݒ肷��
			pos.y = fHeight - GetFileData().vtxMin.y;

			// �ړ��ʂ����Z����
			m_move.x *= 0.6f;
			m_move.y *= -0.6f;
			m_move.z *= 0.6f;

			if (m_move.y <= 5.0f)
			{ // �ړ��ʂ����ȉ��̏ꍇ

				// �d�͂�␳����
				m_move.y = 0.0f;

				// ���n����
				bLand = true;
			}
		}

		// ���̃|�C���^���擾����
		pMesh = pMesh->GetNext();
	}

	if (bLand == true)
	{ // ���n�󋵂� true �ɂ���

		// ��~��Ԃɂ���
		m_state = STATE_STOP;
		SetFileData((CXFile::TYPE)(CXFile::TYPE_HAIRBALL));
		SetAction(false);
	}
	else
	{ // ��L�ȊO

		// ������΂���Ԃɂ���
		m_state = STATE_SMASH;
	}

	// �ʒu���X�V����
	SetPos(pos);
}

//=====================================
// �u���b�N�̓����蔻��
//=====================================
void CHairBall::Block(void)
{
	// ���[�J���ϐ��錾
	CBlock* pBlock = CBlockManager::Get()->GetTop();		// �u���b�N�̐擪�̃I�u�W�F�N�g���擾����
	D3DXVECTOR3 pos = GetPos();				// �ʒu���擾����
	collision::SCollision coll = { false,false, false, false, false, false };		// �����蔻��̕ϐ�

	while (pBlock != nullptr)
	{ // �n�ʂ̏�񂪂�������

		// �����蔻��̕ϐ���������
		coll = collision::HexahedronClush(&pos, pBlock->GetPos(), GetPosOld(), pBlock->GetPosOld(), GetFileData().vtxMin, pBlock->GetFileData().vtxMin, GetFileData().vtxMax, pBlock->GetFileData().vtxMax);

		if (coll.bFar == true ||
			coll.bNear == true)
		{ // ����O�ɓ��������ꍇ

			// �ړ��ʂ��t�ɂ���
			m_move.z *= -1.0f;
		}

		if(coll.bLeft == true ||
			coll.bRight == true)
		{ // ���E�ɓ��������ꍇ

			// �ړ��ʂ��t�ɂ���
			m_move.x *= -1.0f;
		}

		if (coll.bTop == true)
		{ // ��ɓ��������ꍇ

			// �ړ��ʂ��t�ɂ���
			m_move.y *= -1.0f;
		}

		// ���̃|�C���^���擾����
		pBlock = pBlock->GetNext();
	}

	// �ʒu���X�V����
	SetPos(pos);
}

//=====================================
// ���@�̕�
//=====================================
void CHairBall::MagicWall(void)
{
	// �ʒu���擾����
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 Max = GetFileData().vtxMax;
	D3DXVECTOR3 Min = GetFileData().vtxMin;

	if (pos.x + Min.x <= -MAP_SIZE.x)
	{ // �ʒu��������o�����ȏꍇ

		// �ʒu��ݒ肷��
		pos.x = -MAP_SIZE.x - Min.x;

		// �ړ��ʂ��t�ɂ���
		m_move.x *= -1;
	}

	if (pos.x + Max.x >= MAP_SIZE.x)
	{ // �ʒu���E����o�����ȏꍇ

		// �ʒu��ݒ肷��
		pos.x = MAP_SIZE.x - Max.x;

		// �ړ��ʂ��t�ɂ���
		m_move.x *= -1;
	}

	if (pos.z + Min.z <= -MAP_SIZE.z)
	{ // �ʒu����O����o�����ȏꍇ

		// �ʒu��ݒ肷��
		pos.z = -MAP_SIZE.z - Min.z;

		// �ړ��ʂ��t�ɂ���
		m_move.z *= -1;
	}

	if (pos.z + Max.z >= MAP_SIZE.z)
	{ // �ʒu��������o�����ȏꍇ

		// �ʒu��ݒ肷��
		pos.z = MAP_SIZE.z - Max.z;

		// �ړ��ʂ��t�ɂ���
		m_move.z *= -1;
	}

	// �ʒu��K�p����
	SetPos(pos);
}