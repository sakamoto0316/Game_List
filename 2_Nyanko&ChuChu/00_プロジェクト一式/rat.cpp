//===========================================
//
// ���b�g�̃��C������[rat.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "rat.h"
#include "player.h"
#include "game.h"
#include "tutorial.h"
#include "result.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "useful.h"

#include "motion.h"
#include "player_idUI.h"
#include "stun.h"
#include "collision.h"
#include "elevation_manager.h"
#include "objectElevation.h"
#include "obstacle_manager.h"
#include "obstacle.h"
#include "Particle.h"
#include "rat_ghost.h"
#include "resurrection_fan.h"
#include "object3Dfan.h"
#include "recoveringUI.h"
#include "speech_message.h"
#include "sound.h"

//-------------------------------------------
// �������O���
//-------------------------------------------
namespace
{
	const D3DXVECTOR3 COLLSIZE = D3DXVECTOR3(30.0f, 50.0f, 30.0f);		// �����蔻��ł̃T�C�Y
	const float GRAVITY = 1.2f;					// �d��
	const float ADD_MOVE_Y = 25.0f;				// �W�����v��
	const float ATTACK_DISTANCE = 80.0f;			// �U���͈͂܂ł̋���
	const float MOVE_SPEED = 15.0f;				// ���x
	const float ARROW_DISTANCE = 100.0f;			// ���̃l�Y�~�̖��̋���
	const float STUN_HEIGHT = 80.0f;				// �C�≉�o���o�Ă��鍂��
	const float ID_HEIGHT = 110.0f;				// ID���o�Ă��鍂��
	const int INVINCIBLE_COUNT = 60;				// ���G�J�E���g
	const WORD DEATH_VIBRATE = 50000;			// ���񂾂Ƃ��̃o�C�u���[�V�����̋��x
	const int DEATH_VIBRATE_COUNT = 20;			// ���񂾂Ƃ��̃o�C�u���[�V�����̃J�E���g��
}

//--------------------------------------------
// �ÓI�����o�ϐ��錾
//--------------------------------------------
bool CRat::m_bResurrection = false;		// ���������Ă�̂�

//==============================
// �R���X�g���N�^
//==============================
CRat::CRat() : CPlayer(CObject::TYPE_PLAYER, CObject::PRIORITY_PLAYER)
{
	// �S�Ă̒l���N���A����
	m_nRezCounter = 0;					// �񕜂���܂ł̃J�E���^�[
	m_bJump = false;					// �W�����v��
	m_bSe = false;						// SE�Đ���
}

//==============================
// �f�X�g���N�^
//==============================
CRat::~CRat()
{

}

//==============================
// �l�Y�~�̏���������
//==============================
HRESULT CRat::Init(void)
{
	if (FAILED(CPlayer::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �x�^�ł�
	SetNumModel(6);

	// �f�[�^�̐ݒ菈��
	CCharacter::SetData();

	// ���[�V�����̃|�C���^��錾
	CMotion* pMotion = nullptr;

	if (pMotion == nullptr)
	{ // ���[�V������ NULL �������ꍇ

		// ���[�V�����̐�������
		pMotion = CMotion::Create();
	}
	else
	{ // �|�C���^�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);
	}

	if (pMotion != nullptr)
	{ // �|�C���^�� NULL ����Ȃ��ꍇ

		// ���[�V�����̏����擾����
		pMotion->SetModel(GetHierarchy(), GetNumModel());

		// ���[�h����
		pMotion->Load(CMotion::TYPE_RAT);
	}
	else
	{ // �|�C���^�� NULL ����Ȃ��ꍇ

	  // ��~
		assert(false);
	}

	// ���[�V�����̐ݒ菈��
	pMotion->Set(MOTIONTYPE_NEUTRAL);

	// ���[�V�����̏���ݒ肷��
	SetMotion(pMotion);

	// �S�Ă̒l������������
	m_bJump = false;				// �W�����v��
	m_bSe = false;						// SE�Đ���

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �l�Y�~�̏I������
//========================================
void CRat::Uninit(void)
{
	// �I������
	CPlayer::Uninit();
}

//=====================================
// �l�Y�~�̍X�V����
//=====================================
void CRat::Update(void)
{
	// �O��̈ʒu��ݒ肷��
	SetPosOld(GetPos());

	if (CPlayer::GetStunState() != CPlayer::STUNSTATE_STUN &&
		CPlayer::GetState() != CPlayer::STATE_DEATH)
	{ // �C����or���S��Ԃ���Ȃ��ꍇ

		if (GetTutorial() != true)
		{
			// �W�����v����
			Jump();

			if (GetStunState() != STUNSTATE_SMASH)
			{ // ������я�Ԃ̏ꍇ

				// �ړ����쏈��
				MoveControl();
			}

			//// �U������
			//Attack();

			// �����Ԃ�̓����蔻��
			ResurrectionCollision();

			//�ړ�����
			Move();
		}

		// ���[�V�����̐ݒ菈��
		MotionManager();
	}
	else
	{
		// �ړ��ʂ�����������
		SetMove(NONE_D3DXVECTOR3);
	}

	// �d�͏���
	Gravity();

	// ���S���̏���
	DeathArrow();

	// �N���n�ʂ̓����蔻��
	Elevation();

	// �p�x�̐��K��
	RotNormalize();

	// �v���C���[�̍X�V����
	CPlayer::Update();

	// ��Q���Ƃ̏Փ˔���
	if (collision::ObstacleCollision(this, GetSizeColl().x, GetSizeColl().y, GetSizeColl().z) == true)
	{ // ��ɏ�����ꍇ

		// �W�����v�󋵂� false �ɂ���
		m_bJump = false;
	}

	// �u���b�N�Ƃ̓����蔻��
	if (collision::BlockCollision(this, GetSizeColl()) == true)
	{ // ��ɏ�����ꍇ

		// �W�����v�󋵂� false �ɂ���
		m_bJump = false;
	}

	if (GetMove().y <= -GRAVITY)
	{ // �d�͂����ȏ゠�����ꍇ(���ƂŏC�U�\��)

		// �W�����v���Ă���
		m_bJump = true;
	}

	if (GetPlayerID() != nullptr)
	{ // �v���C���[��ID�\���� NULL ����Ȃ��ꍇ

		// �ʒu��ݒ肷��
		GetPlayerID()->SetPos(D3DXVECTOR3(GetPos().x, GetPos().y + ID_HEIGHT, GetPos().z));
		GetPlayerID()->Update();
	}

	// �f�o�b�O�\��
	CManager::Get()->GetDebugProc()->Print("�h���J�E���g�F%d\n", CPlayer::GetResurrectionTime());
}

//=====================================
// �l�Y�~�̕`�揈��
//=====================================
void CRat::Draw(void)
{
	// �`�揈��
	CPlayer::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CRat::MotionManager(void)
{
	// ���[�V�����̎�ނ��擾����
	int nMotionType = GetMotion()->GetType();

	if (CManager::Get()->GetMode() == CScene::MODE_RESULT)
	{ // ���U���g

		if (CResult::GetState() == CGame::STATE_RAT_WIN)
		{ // �˂��݂̂���

			if (nMotionType != MOTIONTYPE_WIN)
			{
				nMotionType = MOTIONTYPE_WIN;

				// ���[�V�����̐ݒ菈��
				GetMotion()->Set(nMotionType);
			}
		}
		else if (CResult::GetState() == CGame::STATE_CAT_WIN)
		{ // �˂��̂���

			if (nMotionType != MOTIONTYPE_DEATH)
			{
				nMotionType = MOTIONTYPE_DEATH;

				// ���[�V�����̐ݒ菈��
				GetMotion()->Set(nMotionType);
			}
		}
	}
	else
	{ // ���U���g�ȊO�̂Ƃ�

		if (GetStunState() == STUNSTATE_SMASH)
		{
			if (nMotionType != MOTIONTYPE_KNOCKBACK)
			{
				nMotionType = MOTIONTYPE_KNOCKBACK;

				// ���[�V�����̐ݒ菈��
				GetMotion()->Set(nMotionType);
			}
		}
		else if (GetStunState() == STUNSTATE_STUN)
		{
			if (nMotionType != MOTIONTYPE_STUN)
			{
				nMotionType = MOTIONTYPE_STUN;

				// ���[�V�����̐ݒ菈��
				GetMotion()->Set(nMotionType);
			}
		}
		else if (m_bJump == true)
		{
			if (nMotionType != MOTIONTYPE_JUMP)
			{
				nMotionType = MOTIONTYPE_JUMP;

				// ���[�V�����̐ݒ菈��
				GetMotion()->Set(nMotionType);

				// �W�����v�Đ�
				CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_JUMP);
			}
		}
		else if (GetMove().x > 0.05f || GetMove().x < -0.05f ||
			GetMove().z > 0.05f || GetMove().z < -0.05f)
		{
			if (nMotionType != MOTIONTYPE_MOVE)
			{
				nMotionType = MOTIONTYPE_MOVE;

				// ���[�V�����̐ݒ菈��
				GetMotion()->Set(nMotionType);
			}
		}
		else if (m_bResurrection == true)
		{
			if (nMotionType != MOTIONTYPE_RESURRECTION)
			{
				nMotionType = MOTIONTYPE_RESURRECTION;

				// ���[�V�����̐ݒ菈��
				GetMotion()->Set(nMotionType);
			}
		}
		else
		{
			if (nMotionType != MOTIONTYPE_NEUTRAL)
			{
				nMotionType = MOTIONTYPE_NEUTRAL;

				// ���[�V�����̐ݒ菈��
				GetMotion()->Set(nMotionType);
			}
		}
	}
}

//=====================================
// �W�����v�󋵂̐ݒ菈��
//=====================================
void CRat::SetEnableJump(const bool bJump)
{
	// �W�����v�󋵂�ݒ肷��
	m_bJump = bJump;
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CRat::SetData(const D3DXVECTOR3& pos, const int nID, const TYPE type)
{
	// ���̐ݒ菈��
	CPlayer::SetData(pos, nID, type);

	if (GetPlayerID() != nullptr)
	{ // �v���C���[��ID�� NULL ����Ȃ��ꍇ

		// �ʒu��ݒ肷��
		GetPlayerID()->SetPos(D3DXVECTOR3(pos.x, pos.y + ID_HEIGHT, pos.z));
	}

	// �C�₪�o�鍂���̐ݒ�
	SetStunHeight(STUN_HEIGHT);

	// �����蔻��̃T�C�Y�̐ݒ�
	SetSizeColl(COLLSIZE);

	// �ړ��ʂ�ݒ肷��
	SetSpeed(MOVE_SPEED);
	SetSpeedCopy(GetSpeed());

	// ����ݒ肷��
	m_bJump = false;				// �W�����v������

	for (int nCntData = 0; nCntData < GetNumModel(); nCntData++)
	{
		// ����������
		GetHierarchy(nCntData)->SetPos(pos);										// �ʒu
		GetHierarchy(nCntData)->SetPosOld(pos);										// �O��̈ʒu
		GetHierarchy(nCntData)->SetRot(NONE_D3DXVECTOR3);							// ����
		GetHierarchy(nCntData)->SetScale(NONE_SCALE);								// �g�嗦
		GetHierarchy(nCntData)->SetFileData(CXFile::TYPE(INIT_RAT + nCntData));		// �f�[�^�̐ݒ菈��
	}

	// ���[�V�����̐ݒ菈��
	GetMotion()->Set(MOTIONTYPE_NEUTRAL);

	// �������[�V��������
	GetMotion()->SetForcibly();

	// ���[�V�����̍X�V����(���Ȃ���鳖��鲂��a������)
	GetMotion()->Update();
}

//=======================================
// �W�����v����
//=======================================
void CRat::Jump(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 move = GetMove();

	if ((CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_SPACE) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, GetPlayerIdx()) == true) &&
		GetStunState() != STUNSTATE_SMASH &&
		m_bJump == false)
	{ // A�{�^�����������ꍇ

		move.y = ADD_MOVE_Y;	// ���͑��

		m_bJump = true;		// �W�����v���Ă��Ԃɂ���
	}

	// ����K�p����
	SetMove(move);
}

//=======================================
// �d�͏���
//=======================================
void CRat::Gravity(void)
{
	// �ړ��ʂ��擾����
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 move = GetMove();

	// �d�͂����Z����
	move.y -= GRAVITY;

	// �ʒu���ړ�����
	pos.y += move.y;

	// �ړ��ʂ�K�p����
	SetPos(pos);
	SetMove(move);
}

//=======================================
// �U������
//=======================================
void CRat::Attack(void)
{
	// ���[�J���ϐ��錾
	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();		// �擪�̏�Q�����擾����
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_B, GetPlayerIdx()) == true)
	{ // B�{�^�����������ꍇ

		while (pObstacle != nullptr)
		{ // �u���b�N�̏�� NULL ����Ȃ��ꍇ

			if (useful::RectangleCollisionXY(D3DXVECTOR3(pos.x + sinf(rot.y) * ATTACK_DISTANCE, pos.y, pos.z + cosf(rot.y) * ATTACK_DISTANCE), pObstacle->GetPos(),
				COLLSIZE, pObstacle->GetFileData().vtxMax,
				-COLLSIZE, pObstacle->GetFileData().vtxMin) == true)
			{ // XY�̋�`�ɓ������Ă���

				if (useful::RectangleCollisionXZ(D3DXVECTOR3(pos.x + sinf(rot.y) * ATTACK_DISTANCE, pos.y, pos.z + cosf(rot.y) * ATTACK_DISTANCE), pObstacle->GetPos(),
					COLLSIZE, pObstacle->GetFileData().vtxMax,
					-COLLSIZE, pObstacle->GetFileData().vtxMin) == true)
				{ // XZ�̋�`�ɓ������Ă���

					// ��Q���̏I������
					pObstacle->Uninit();
				}
			}

			// ���̃I�u�W�F�N�g��������
			pObstacle = pObstacle->GetNext();
		}
	}
}

//=======================================
// �q�b�g����
//=======================================
void CRat::Hit(void)
{
	// ���[�J���ϐ��錾
	CPlayer *pPlayer;						// �l�Y�~�̏��
	D3DXVECTOR3 pos = GetPos();				// �ʒu���擾����
	STATE state = GetState();				// ��Ԃ��擾����
	int nCntDeath = 0;						// ���S������

	if (state == STATE_NONE)
	{ // �_���[�W�󂯂��Ԃ������ꍇ

		// �o�C�u���[�V������ݒ肷��
		CManager::Get()->GetInputGamePad()->GetRightVibration(GetPlayerIdx(), DEATH_VIBRATE, DEATH_VIBRATE_COUNT);
		CManager::Get()->GetInputGamePad()->GetLeftVibration(GetPlayerIdx(), DEATH_VIBRATE, DEATH_VIBRATE_COUNT);

		CParticle::Create(pos, CParticle::TYPE_ENEMYDEATH); //�p�[�e�B�N��

		SetState(STATE_DEATH);				// ���S��Ԃɂ���

		// �����Ԃ�̉~�͈̔͐���
		CPlayer::SetRessrectionFan(pos, D3DXCOLOR(1.0f, 0.0f, 0.1f, 0.5f));

		// �l�Y�~�̗H��̐���
		CPlayer::SetRatGhost(pos);

		// �񕜒�UI�̐���
		CPlayer::SetRecoveringUI(pos, GetPosOld());

		// �`�B���b�Z�[�W�̕\��
		CPlayer::SetSpeechMessage(D3DXVECTOR3(pos.x, pos.y + 120.0f, pos.z), D3DXVECTOR3(50.0f, 50.0f, 0.0f), -1, CSpeechMessage::TYPE_HELP);

		for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
		{
			if (CManager::Get()->GetMode() == CScene::MODE_TUTORIAL)
			{
				// �v���C���[�̏����擾����
				pPlayer = CTutorial::GetPlayer(nCnt);
			}
			else
			{
				// �v���C���[�̏����擾����
				pPlayer = CGame::GetPlayer(nCnt);
			}

			if (pPlayer != nullptr &&
				pPlayer->GetType() == TYPE_RAT && 
				pPlayer->GetState() == STATE_DEATH)
			{ // ���S���Ă�l�Y�~�̎�

				nCntDeath++;
			}
		}

		if (nCntDeath >= (MAX_PLAY - 1))
		{ // �l�Y�~�S�C���񂾂�

			// �l�R������������Ԃɂ���
			CGame::SetState(CGame::STATE_CAT_WIN);
		}

		// �U���̃q�b�g����炷
		CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_CATATTACK_HIT);
	}
}

//=======================================
// ���S���̏���
//=======================================
void CRat::DeathArrow(void)
{
	CPlayer *pPlayer;						// �l�Y�~�̏��
	STATE state = GetState();				// ��Ԃ��擾����
	D3DXVECTOR3 pos = GetPos();				// �ʒu�擾
	D3DXVECTOR3 posOld = GetPosOld();		// �O��̈ʒu�擾
	bool abRez[MAX_PLAY];					// �������Ă邩

	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		if (CManager::Get()->GetMode() == CScene::MODE_TUTORIAL)
		{
			// �v���C���[�̏����擾����
			pPlayer = CTutorial::GetPlayer(nCnt);
		}
		else
		{
			// �v���C���[�̏����擾����
			pPlayer = CGame::GetPlayer(nCnt);
		}

		abRez[nCnt] = false;

		if (pPlayer != nullptr &&
			pPlayer->GetType() == TYPE_RAT &&
			GetPlayerIdx() != pPlayer->GetPlayerIdx())
		{ // ���삵�Ă�l�Y�~����Ȃ��Ƃ�

			if (pPlayer->GetState() == STATE_DEATH && state != STATE_DEATH)
			{ // ���̃l�Y�~�����S��Ԃ̎�

				D3DXVECTOR3 DestPos = pos - pPlayer->GetPos();		// �ړI�̈ʒu
				D3DXVECTOR3 DestRot = NONE_D3DXVECTOR3;				// �ړI�̌���

				// �ړI�̌��������߂�
				DestRot.y = atan2f(-DestPos.z, DestPos.x);

				// ���S��󐶐�
				SetDeathArrow(D3DXVECTOR3(pos.x + sinf(DestRot.y + -D3DX_PI * 0.5f) * ARROW_DISTANCE,
					pos.y - 1.0f,
					pos.z + cosf(DestRot.y + -D3DX_PI * 0.5f) * ARROW_DISTANCE),
					posOld, DestRot, nCnt, GetPlayerIdx());

				// �񕜂����Ă��Ԃɂ���
				abRez[nCnt] = true;
			}

			if (abRez[nCnt] == false)
			{ // �����Ԃ�����

				// ���S������
				DeleteDeathArrow(nCnt);
			}
		}
	}
}

//=======================================
// �N���n�ʂ̓����蔻��
//=======================================
void CRat::Elevation(void)
{
	// ���[�J���ϐ��錾
	CElevation* pMesh = CElevationManager::Get()->GetTop();		// �N���̐擪�̃I�u�W�F�N�g���擾����
	D3DXVECTOR3 pos = GetPos();				// �ʒu���擾����
	D3DXVECTOR3 move = GetMove();			// �ړ��ʂ��擾����
	float fHeight = 0.0f;					// ����

	while (pMesh != nullptr)
	{ // �n�ʂ̏�񂪂�������

		// �����蔻������
		fHeight = pMesh->ElevationCollision(pos);

		if (pos.y < fHeight)
		{ // �����蔻��̈ʒu�����������ꍇ

			// ������ݒ肷��
			pos.y = fHeight;

			move.y = 0.0f;

			m_bJump = false;		// �W�����v���ĂȂ���Ԃɂ���
		}

		// ���̃|�C���^���擾����
		pMesh = pMesh->GetNext();
	}

	// �ʒu�ƈړ��ʂ��X�V����
	SetPos(pos);
	SetMove(move);
}

//=======================================
// �����Ԃ�̓����蔻��
//=======================================
void CRat::ResurrectionCollision(void)
{
	CPlayer *pPlayer = nullptr;				// �l�Y�~�̏��
	bool bCollXY = false;					// XY�͈̔͂ɓ�������
	bool bCollXZ = false;					// XZ�͈̔͂ɓ�������
	bool abRez[MAX_PLAY];					// �񕜂��Ă邩
	STATE state = GetState();				// ��Ԃ��擾����
	STUNSTATE stunState = GetStunState();	// �C���Ԃ��擾����

	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		if (CManager::Get()->GetMode() == CScene::MODE_TUTORIAL)
		{
			// �v���C���[�̏����擾����
			pPlayer = CTutorial::GetPlayer(nCnt);
		}
		else
		{
			// �v���C���[�̏����擾����
			pPlayer = CGame::GetPlayer(nCnt);
		}
		abRez[nCnt] = false;

		if (pPlayer != nullptr &&
			pPlayer->GetType() == TYPE_RAT &&
			GetPlayerIdx() != pPlayer->GetPlayerIdx())
		{ // ���삵�Ă�l�Y�~����Ȃ��Ƃ�

			if (pPlayer->GetState() == STATE_DEATH &&
				state != STATE_DEATH && 
				stunState != STUNSTATE::STUNSTATE_SMASH &&
				stunState != STUNSTATE::STUNSTATE_STUN)
			{ // ���̃l�Y�~�����S��� && ���삵�Ă�l�Y�~��������������Ԃ̎�

				// �~�̓����蔻��(XY����)�擾
				bCollXY = useful::CircleCollisionXY(GetPos(), pPlayer->GetPos(), 30.0f, ATTACK_DISTANCE);

				// �~�̓����蔻��(XZ����)�擾
				bCollXZ = useful::CircleCollisionXZ(GetPos(), pPlayer->GetPos(), 30.0f, ATTACK_DISTANCE);

				// ���̃l�Y�~�Ƃ̓����蔻��
				if (bCollXY == true && bCollXZ == true)
				{ // �~�̓����蔻��(XY����)��(XZ����)�͈̔͂ɂ���ꍇ

					if (m_bResurrection == false)
					{ // ���������ĂȂ���Ԃ�������

						// ���������Ă��Ԃɂ���
						m_bResurrection = true;

						if (m_bSe == false)
						{
							// �񕜒��̉��Đ�
							CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_REVIVAL_SAVE);
							m_bSe = true;
						}
					}

					// �����p�[�e�B�N������
					CParticle::Create(pPlayer->GetPos(), CParticle::TYPE_RESURRECTION);

					// �񕜂����Ă��Ԃɂ���
					abRez[nCnt] = true;

					// ���݂̐����Ԃ�̎��Ԏ擾
					m_nRezCounter = pPlayer->GetResurrectionTime();
							
					// �����Ԃ�̃J�E���^�[���Z
					m_nRezCounter++;

					// �񕜒�UI�\���ݒ�
					pPlayer->SetDispRecoveringUI(abRez[nCnt]);

					pPlayer->SetResurrectionTime(m_nRezCounter);

					if (pPlayer->GetResurrectionTime() >= NUM_REZ_ANGLE)
					{ // ��莞�Ԍo������

						// ���G��Ԃɂ���
						pPlayer->SetState(STATE_INVINCIBLE);
						pPlayer->SetStateCount(INVINCIBLE_COUNT);
						SetRatRescue(true);

						// �~�͈̔͂̔j��
						pPlayer->DeleteRessrectionFan();

						// �H��l�Y�~�̔j��
						pPlayer->DeleteRatGhost();

						// �񕜒�UI�̔j��
						pPlayer->DeleteRecoveringUI();

						// �`�B���b�Z�[�W�̔j��
						pPlayer->DeleteSpeechMessage();

						// �����Ԃ�̃J�E���^�[������
						pPlayer->SetResurrectionTime(0);
						m_nRezCounter = 0;

						// ���������ĂȂ���Ԃɂ���
						m_bResurrection = false;

						// �񕜒��̉���~
						CManager::Get()->GetSound()->Stop(CSound::SOUND_LABEL_SE_REVIVAL_SAVE);
						m_bSe = false;

						// �񕜒��̉��Đ�
						CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_REVIVAL);
					}
				}
				else if (m_bResurrection == false && (bCollXY == false || bCollXZ == false))
				{ // ���������ĂȂ���� && �~�̓����蔻��(XY����)��(XZ����)�͈̔͂ɂ��Ȃ��ꍇ

					// �񕜒�UI�\���ݒ�
					pPlayer->SetDispRecoveringUI(false);

					// �񕜒��̉���~
					CManager::Get()->GetSound()->Stop(CSound::SOUND_LABEL_SE_REVIVAL_SAVE);
					m_bSe = false;

					if (pPlayer->GetResurrectionTime() > 0)
					{ // �����Ԃ�̃J�E���^�[�����Z����Ă���

						pPlayer->AddResurrectionTime(-1);		// �J�E���^�[���Z
					}
					else
					{ // �����Ԃ�̃J�E���^�[��0�ȉ���������

						// �����Ԃ�̃J�E���^�[������
						pPlayer->SetResurrectionTime(0);
					}
				}

				// �񕜂���͈͂̏��擾
				CRessrectionFan *pResurrectionFan = pPlayer->GetRessrectionFan();

				if (pResurrectionFan != nullptr)
				{ // �񕜂���͈͂� NULL�̂Ƃ�

					// �񕜂͈̔͂̎��Ԑݒ�
					pResurrectionFan->SetResurrectionFan(pPlayer->GetResurrectionTime());
				}
			}
		}
	}

	if (abRez[0] == false && abRez[1] == false && abRez[2] == false && abRez[3] == false)
	{ // �S�����N�������ĂȂ��Ƃ�

		// ���������ĂȂ���Ԃɂ���
		m_bResurrection = false;
	}
}