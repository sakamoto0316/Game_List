//===========================================
//
// ��������̎Ԃ̃��C������[toycar.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "toycar.h"
#include "useful.h"

#include "car_gear.h"
#include "collision.h"
#include "map.h"
#include "block.h"
#include "block_manager.h"
#include "obstacle.h"
#include "obstacle_manager.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define CAR_GEAR_SHIFT		(D3DXVECTOR3(0.0f, 40.0f, 0.0f))		// �Ԃ̎��Ԃ̂��炷��
#define CAR_SPEED			(-11.0f)		// �Ԃ̑��x
#define CAR_CURVE_SPEED		(0.08f)			// �Ԃ̋Ȃ��鑬�x
#define CAR_DEST_ROT_SHIFT	(0.1f)			// �ړI�̌����̕␳�̋��e�͈�
#define CAR_BRAKE_COUNT		(40)			// �u���[�L�J�E���g��
#define ROTDEST_MAGNI_MIN	(8)				// �ړI�̌����̔{���̍ŏ��l
#define ROTDEST_MAGNI_RANGE	(11)			// �ړI�̌����̔{���͈̔�

//==============================
// �R���X�g���N�^
//==============================
CToyCar::CToyCar() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	m_pGear = nullptr;				// ���Ԃ̏��
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_state = STATE_DRIVE;			// ���
	m_nBrakeCount = 0;				// �u���[�L�J�E���g
	m_fRotDest = 0.0f;				// �ړI�̌���
	m_fRotMagni = 0.0f;				// �����̔{��
	m_bRight = true;				// �E������
}

//==============================
// �f�X�g���N�^
//==============================
CToyCar::~CToyCar()
{

}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CToyCar::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_pGear = nullptr;				// ���Ԃ̒l
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_state = STATE_DRIVE;			// ���
	m_nBrakeCount = 0;				// �u���[�L�J�E���g
	m_fRotDest = 0.0f;				// �ړI�̌���
	m_fRotMagni = 0.0f;				// �����̔{��
	m_bRight = true;				// �E������

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �j�Ђ̏I������
//========================================
void CToyCar::Uninit(void)
{
	if (m_pGear != nullptr)
	{ // ���Ԃ̏�� NULL ����Ȃ��ꍇ

		// �I������
		m_pGear->Uninit();
		m_pGear = nullptr;
	}

	// �I������
	CObstacle::Uninit();
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CToyCar::Update(void)
{
	// �O��̈ʒu��ݒ肷��
	SetPosOld(GetPos());

	switch (m_state)
	{
	case STATE_DRIVE:

		// ���s����
		Drive();

		if (MagicWall() == true ||
			Block() == true)
		{ // ���@�ǂ܂��́A�u���b�N�̓����蔻�肪 true �̏ꍇ

			// �J�[�u��Ԃɂ���
			m_state = STATE_CURVE;
			SetFileData((CXFile::TYPE)(CXFile::TYPE_TOYCARBODY));
			m_pGear->SetFileData((CXFile::TYPE)(CXFile::TYPE_TOYCARSCREW));

			// �����̌v�Z����
			RotCalc();
		}

		break;

	case STATE_CURVE:

		// �J�[�r���O����
		Curve();
		
		break;

	case STATE_BRAKE:

		// �u���[�L�J�E���g�����Z����
		m_nBrakeCount++;

		if (m_nBrakeCount % CAR_BRAKE_COUNT == 0)
		{ // �u���[�L�J�E���g����萔�ɂȂ����ꍇ

			// �u���[�L�J�E���g������������
			m_nBrakeCount = 0;

			// �h���C�u��Ԃɂ���
			m_state = STATE_DRIVE;
			SetFileData((CXFile::TYPE)(CXFile::TYPE_RED_TOYCARBODY));
			m_pGear->SetFileData((CXFile::TYPE)(CXFile::TYPE_RED_TOYCARSCREW));
		}

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	if (m_pGear != nullptr)
	{ // ���Ԃ� NULL ����Ȃ��ꍇ

		// �ʒu�����肷��
		m_pGear->SetPos(GetPos() + CAR_GEAR_SHIFT);

		// �X�V����
		m_pGear->Update();
	}
}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CToyCar::Draw(void)
{
	// �`�揈��
	CObstacle::Draw();

	if (m_pGear != nullptr)
	{ // ���Ԃ� NULL ����Ȃ��ꍇ

		// �`�揈��
		m_pGear->Draw();
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CToyCar::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos, rot, type);

	if (m_pGear == nullptr)
	{ // ���Ԃ̏�� NULL �̏ꍇ

		// ���Ԃ̐���
		m_pGear = CCarGear::Create(GetPos() + CAR_GEAR_SHIFT);
	}

	// �S�Ă̒l��ݒ肷��
	m_move = D3DXVECTOR3(sinf(rot.y) * CAR_SPEED, 0.0f, cosf(rot.y) * CAR_SPEED);	// �ړ���
	m_state = STATE_DRIVE;			// ���
	m_nBrakeCount = 0;				// �u���[�L�J�E���g
	m_fRotDest = 0.0f;				// �ړI�̌���
	m_fRotMagni = (float)((rand() % ROTDEST_MAGNI_RANGE + ROTDEST_MAGNI_MIN) * 0.1f);		// �����̔{��
	m_bRight = true;				// �E������
}

//=====================================
// �����蔻�菈��
//=====================================
bool CToyCar::Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// �ʒu�ƍŏ��l�ƍő�l��錾
	D3DXVECTOR3 pos = pPlayer->GetPos();
	D3DXVECTOR3 move = pPlayer->GetMove();
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);;
	D3DXVECTOR3 vtxMax = collSize;
	collision::SCollision coll = { false,false,false,false,false,false };

	if (pPlayer->GetType() == CPlayer::TYPE_RAT)
	{ // �l�Y�~�̏ꍇ

		// �Z�ʑ̂̓����蔻��
		coll = collision::HexahedronClush(&pos, GetPos(), pPlayer->GetPosOld(), GetPosOld(), vtxMin, GetFileData().vtxMin, vtxMax, GetFileData().vtxMax);

		// �ʒu��K�p����
		pPlayer->SetPos(pos);

		if (coll.bTop == true)
		{ // ��ɏ�����ꍇ

			// �ړ��ʂ�����������
			move.y = 0.0f;

			// �ړ��ʂ�K�p����
			pPlayer->SetMove(move);

			// true ��Ԃ�
			return true;
		}
	}

	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CToyCar::Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// �ŏ��l�ƍő�l��錾
	D3DXVECTOR3 pos = pPlayer->GetPos();
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);
	D3DXVECTOR3	vtxMax = collSize;

	if (pPlayer->GetType() == CPlayer::TYPE_RAT &&
		m_state == STATE_DRIVE)
	{ // �l�Y�~���A�h���C�u��Ԃ̏ꍇ

		if (collision::HexahedronCollision
		(
			&pos,
			GetPos(),
			pPlayer->GetPosOld(),
			GetPosOld(),
			vtxMin,
			GetFileData().vtxMin,
			vtxMax,
			GetFileData().vtxMax
		) == true)
		{ // �Ԃɓ��������ꍇ

			// true ��Ԃ�
			return true;
		}
	}

	// false ��Ԃ�
	return false;
}

//=====================================
// ���s����
//=====================================
void CToyCar::Drive(void)
{
	// �����擾����
	D3DXVECTOR3 pos = GetPos();		// �ʒu
	D3DXVECTOR3 rot = GetRot();		// ����

	// �ʒu���ړ�����
	pos += m_move;

	// �ʒu��K�p����
	SetPos(pos);
}

//=====================================
// �J�[�r���O����
//=====================================
void CToyCar::Curve(void)
{
	// �������擾����
	D3DXVECTOR3 rot = GetRot();		

	if (m_bRight == true)
	{ // �E�����̏ꍇ

		// ���������Z����
		rot.y += CAR_CURVE_SPEED;
	}
	else
	{ // ��L�ȊO

		// ���������Z����
		rot.y -= CAR_CURVE_SPEED;
	}

	// �����̐��K��
	useful::RotNormalize(&rot.y);

	if (fabsf(m_fRotDest - rot.y) <= CAR_DEST_ROT_SHIFT)
	{ // ���������܂ōs�����ꍇ

		// ������␳����
		rot.y = m_fRotDest;

		// �u���[�L��Ԃɂ���
		m_state = STATE_BRAKE;

		// �ړ��ʂ�ݒ肷��
		m_move.x = sinf(rot.y) * CAR_SPEED;
		m_move.z = cosf(rot.y) * CAR_SPEED;
	}

	// ������K�p����
	SetRot(rot);
}

//=====================================
// �����̌v�Z����
//=====================================
void CToyCar::RotCalc(void)
{
	// �����擾����
	D3DXVECTOR3 pos = GetPos();		// �ʒu
	D3DXVECTOR3 rot = GetRot();		// ����
	float fRotDiff;					// �����̍���

	// �ړI�̌�����ݒ肷��
	m_fRotDest = rot.y + (D3DX_PI * m_fRotMagni);

	// �����̐��K��
	useful::RotNormalize(&m_fRotDest);

	// �����̍��������߂�
	fRotDiff = m_fRotDest - rot.y;

	// �����𐳋K������
	useful::RotNormalize(&fRotDiff);

	if (fRotDiff >= 0.0f)
	{ // �����̍������v���X�̒l�̏ꍇ

		// �E�����ɂ���
		m_bRight = true;
	}
	else
	{ // ��L�ȊO

		// �������ɂ���
		m_bRight = false;
	}
}

//=====================================
// �u���b�N�̓����蔻�菈��
//=====================================
bool CToyCar::Block(void)
{
	// ���[�J���ϐ��錾
	CBlock* pBlock = CBlockManager::Get()->GetTop();		// �u���b�N�̐擪���擾����
	D3DXVECTOR3 pos = GetPos();								// �ʒu���擾����
	bool bClush = false;									// �Փ˔���

	while (pBlock != nullptr)
	{ // �u���b�N�� NULL ����Ȃ��ꍇ��

		if (collision::HexahedronCollision
		(
			&pos,
			pBlock->GetPos(),
			GetPosOld(),
			pBlock->GetPosOld(),
			GetFileData().vtxMin,
			pBlock->GetVtxMin(),
			GetFileData().vtxMax,
			pBlock->GetVtxMax()
		) == true)
		{ // �Z�ʑ̂̓����蔻��ɓ��������ꍇ

			// �Փ˔���� true �ɂ���
			bClush = true;
		}

		// ���̃u���b�N���擾����
		pBlock = pBlock->GetNext();
	}

	// �ʒu��K�p����
	SetPos(pos);

	// �Փ˔����Ԃ�
	return bClush;
}

//=====================================
// ��Q���̓����蔻�菈��
//=====================================
bool CToyCar::Obstacle(void)
{
	// ���[�J���ϐ��錾
	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();	// ��Q���̐擪���擾����
	D3DXVECTOR3 pos = GetPos();									// �ʒu���擾����
	bool bClush = false;										// �Փ˔���

	while (pObstacle != nullptr)
	{ // ��Q���� NULL ����Ȃ��ꍇ��

		if (collision::HexahedronCollision
		(
			&pos,
			pObstacle->GetPos(),
			GetPosOld(),
			pObstacle->GetPosOld(),
			GetFileData().vtxMin,
			pObstacle->GetFileData().vtxMin,
			GetFileData().vtxMax,
			pObstacle->GetFileData().vtxMax
		) == true)
		{ // �Z�ʑ̂̓����蔻��ɓ��������ꍇ

			// �Փ˔���� true �ɂ���
			bClush = true;
		}

		// ���̏�Q�����擾����
		pObstacle = pObstacle->GetNext();
	}

	// �ʒu��K�p����
	SetPos(pos);

	// �Փ˔����Ԃ�
	return bClush;
}

//=====================================
// ���@�ǂ̓����蔻�菈��
//=====================================
bool CToyCar::MagicWall(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();					// �ʒu
	float fRadius = GetFileData().fRadius;		// ���a
	bool bClush = false;						// �Փˏ�

	if (pos.x - fRadius <= -MAP_SIZE.x)
	{ // �ʒu��������o�����ȏꍇ

		// �ʒu��ݒ肷��
		pos.x = -MAP_SIZE.x + fRadius;

		// �Փˏ󋵂� true �ɂ���
		bClush = true;
	}

	if (pos.x + fRadius >= MAP_SIZE.x)
	{ // �ʒu���E����o�����ȏꍇ

		// �ʒu��ݒ肷��
		pos.x = MAP_SIZE.x - fRadius;

		// �Փˏ󋵂� true �ɂ���
		bClush = true;
	}

	if (pos.z - fRadius <= -MAP_SIZE.z)
	{ // �ʒu����O����o�����ȏꍇ

		// �ʒu��ݒ肷��
		pos.z = -MAP_SIZE.z + fRadius;

		// �Փˏ󋵂� true �ɂ���
		bClush = true;
	}

	if (pos.z + fRadius >= MAP_SIZE.z)
	{ // �ʒu��������o�����ȏꍇ

		// �ʒu��ݒ肷��
		pos.z = MAP_SIZE.z - fRadius;

		// �Փˏ󋵂� true �ɂ���
		bClush = true;
	}

	// �ʒu��K�p����
	SetPos(pos);

	// �Փˏ󋵂�Ԃ�
	return bClush;
}