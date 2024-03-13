//===========================================
//
// �l�Y�~���J�̃��C������[toycar.cpp]
// Author �x�씋��
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "ratmecha.h"
#include "useful.h"
#include "player_idUI.h"
#include "player.h"
#include "collision.h"
#include "map.h"
#include "block.h"
#include "block_manager.h"
#include "obstacle.h"
#include "obstacle_manager.h"
#include "game.h"
#include "input.h"
#include "sound.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define CAR_SPEED			(-7.5f)			// �Ԃ̑��x
#define CAR_CURVE_SPEED		(0.08f)			// �Ԃ̋Ȃ��鑬�x
#define CAR_DEST_ROT_SHIFT	(0.1f)			// �ړI�̌����̕␳�̋��e�͈�
#define CAR_BRAKE_COUNT		(6)				// �u���[�L�J�E���g��
#define ROTDEST_MAGNI_MIN	(8)				// �ړI�̌����̔{���̍ŏ��l
#define ROTDEST_MAGNI_RANGE	(11)			// �ړI�̌����̔{���͈̔�
#define ATTACK_SIZE		(D3DXVECTOR3(95.0f, 150.0f, 95.0f))		// �U���̔���̑傫��

//-------------------------------------------
// �ÓI�����o�ϐ�
//-------------------------------------------
int CRatMecha::m_nBgmAll = 0;				// BGM��炵�����̑���

//==============================
// �R���X�g���N�^
//==============================
CRatMecha::CRatMecha() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_state = STATE_DRIVE;			// ���
	m_nBrakeCount = 0;				// �u���[�L�J�E���g
	m_fRotDest = 0.0f;				// �ړI�̌���
	m_fRotMagni = 0.0f;				// �����̔{��
	m_bRight = true;				// �E������
	m_bMove = false;				// �����Ă��邩
	m_pPlayerID = nullptr;			// ID�̃|�C���^
	m_nIdnumber = -1;				// �v���C���[ID�ԍ�

	// �g�p����
	SetRatUse(true);
}

//==============================
// �f�X�g���N�^
//==============================
CRatMecha::~CRatMecha()
{

}

//==============================
// �l�Y�~���J�̏���������
//==============================
HRESULT CRatMecha::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // �����������Ɏ��s�����ꍇ

	  // ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_move = NONE_D3DXVECTOR3;		// �ړ���
	m_state = STATE_DRIVE;			// ���
	m_nBrakeCount = 0;				// �u���[�L�J�E���g
	m_fRotDest = 0.0f;				// �ړI�̌���
	m_fRotMagni = 0.0f;				// �����̔{��
	m_bRight = true;				// �E������
	m_pPlayerID = nullptr;			// ID�̃|�C���^

	// �g�p����
	SetRatUse(true);
	SetCatUse(false);

									// �l��Ԃ�
	return S_OK;
}

//========================================
// �l�Y�~���J�̏I������
//========================================
void CRatMecha::Uninit(void)
{
	if (m_pPlayerID != nullptr)
	{
		m_pPlayerID->Uninit();
		m_pPlayerID = nullptr;
	}

	// �I������
	CObstacle::Uninit();

	// BGM��炵�����������Z����
	m_nBgmAll--;

	if (m_nBgmAll <= 0)
	{ // ������0�����ɂȂ����ꍇ

		// ������␳����
		m_nBgmAll = 0;

		// �l�Y�~���J�̑��s�����~�߂�
		CManager::Get()->GetSound()->Stop(CSound::SOUND_LABEL_SE_RATMECHA_RUN);
	}
}

//=====================================
// �l�Y�~���J�̍X�V����
//=====================================
void CRatMecha::Update(void)
{
	// �O��̈ʒu��ݒ肷��
	SetPosOld(GetPos());
	if (m_bMove == true)
	{
		if (m_pPlayerID != nullptr)
		{
			m_pPlayerID->SetData(D3DXVECTOR3(GetPos().x, GetPos().y+120.0f, GetPos().z), m_nIdnumber);


		}
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
			}

			break;

		default:

			// ��~
			assert(false);

			break;
		}

	}
}

//=====================================
// �l�Y�~���J�̕`�揈��
//=====================================
void CRatMecha::Draw(void)
{
	// �`�揈��
	CObstacle::Draw(1.0f);

	if (m_bMove == true)
	{
		m_pPlayerID->Draw();
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CRatMecha::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos, rot, type);

	// �S�Ă̒l��ݒ肷��
	m_move = D3DXVECTOR3(sinf(rot.y) * CAR_SPEED, 0.0f, cosf(rot.y) * CAR_SPEED);	// �ړ���
	m_state = STATE_DRIVE;			// ���
	m_nBrakeCount = 0;				// �u���[�L�J�E���g
	m_fRotDest = 0.0f;				// �ړI�̌���
	m_fRotMagni = (float)((rand() % ROTDEST_MAGNI_RANGE + ROTDEST_MAGNI_MIN) * 0.1f);		// �����̔{��
	m_bRight = true;				// �E������

	if (m_pPlayerID == nullptr)
	{ // �v���C���[��ID�\���� NULL �̏ꍇ

	  // �v���C���[��ID�\���̐�������
		m_pPlayerID = CPlayerID::Create(pos, 1);
	}
}

//=====================================
// �����蔻�菈��
//=====================================
bool CRatMecha::Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CRatMecha::Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
 	if (m_bMove == true)
	{ // �l�Y�~���J�������Ă�����

		if (pPlayer->GetType() == CPlayer::TYPE_CAT)
		{
			if (pPlayer->GetAttack_Jump() == true)
			{ // �l�R���U�����Ă�����

				//	�l�R�̍U��������o��
				if (useful::RectangleCollisionXZ(
					D3DXVECTOR3(pPlayer->GetPos().x + sinf(pPlayer->GetRot().y) * -100.0f, pPlayer->GetPos().y, pPlayer->GetPos().z + cosf(pPlayer->GetRot().y) * -100.0f),
					GetPos(),
					ATTACK_SIZE, 
					D3DXVECTOR3(10.0f, 50.0f, 10.0f),
					D3DXVECTOR3(-ATTACK_SIZE.x, -ATTACK_SIZE.y, -ATTACK_SIZE.z),
					D3DXVECTOR3(-10.0f, -50.0f, -10.0f)) == true)
				{ // XZ�̋�`�ɓ������Ă���

					// �l�Y�~���J�̔j�󉹂�炷
					CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_RATMECHA_BREAK);

					// true ��Ԃ�
					return true;
				}
			}
		}
	}
	// false ��Ԃ�
	return false;
}

//=====================================
// ���s����
//=====================================
void CRatMecha::Drive(void)
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
void CRatMecha::Curve(void)
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
void CRatMecha::RotCalc(void)
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
bool CRatMecha::Block(void)
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
bool CRatMecha::Obstacle(void)
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
bool CRatMecha::MagicWall(void)
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

//=====================================
// �M�~�b�N�N������
//=====================================
void CRatMecha::Action(void)
{
	// �v���C���[�̃|�C���^��錾
	CPlayer* pPlayer;

	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		// �v���C���[���擾����
		pPlayer = CGame::GetPlayer(nCnt);

		if (pPlayer->GetType() == CPlayer::TYPE_RAT)
		{ // �l�Y�~�̏ꍇ
			if (useful::CircleCollisionXZ(pPlayer->GetPos(), GetPos(), 70.0f, GetFileData().fRadius) == true)
			{//�~�͈͓̔��̏ꍇtrue��Ԃ�

				if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_B, nCnt) == true ||
					CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_E) == true)
				{ // �{�^���������ꂽ�Ƃ�

					// �������v���C���[��ID���擾���ĕۑ�����
					m_nIdnumber = nCnt;

					if (m_nBgmAll <= 0)
					{ // ������0�ȉ��̏ꍇ

						// �l�Y�~���J�̑��s����炷
						CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_RATMECHA_RUN);
					}

					// ���s����炵���������Z����
					m_nBgmAll++;
				}
			
			}
		}
	}


	if (m_bMove == false)
	{ // �l�Y�~���J�𓮂����A�~�߂��Ȃ��悤�ɂ���
		m_bMove = !m_bMove;
		SetAction(true);
	}
}

//=====================================
// �q�b�g����
//=====================================
bool CRatMecha::HitCircle(CPlayer* pPlayer, const float Radius)
{
	if (useful::CircleCollisionXZ(pPlayer->GetPos(), GetPos(), Radius, GetFileData().fRadius) == true)
	{//�~�͈͓̔��̏ꍇtrue��Ԃ�
		return true;
	}

	// false ��Ԃ�
	return false;
}