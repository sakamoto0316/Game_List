//===========================================
//
// �v���C���[�̃��C������[player.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "player.h"
#include "game.h"
#include "tutorial.h"
#include "result.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "useful.h"
#include "MultiCamera.h"
#include "sound.h"

#include "motion.h"
#include "player_idUI.h"
#include "stun.h"
#include "rat_ghost.h"
#include "resurrection_fan.h"
#include "collision.h"
#include "recoveringUI.h"
#include "speech_message.h"
#include "death_arrow.h"

#include "Cat.h"
#include "rat.h"

//-------------------------------------------
// �������O���
//-------------------------------------------
namespace
{
	const D3DXVECTOR3 SMASH_MOVE = D3DXVECTOR3(8.0f, 20.0f, 8.0f);		// ������я�Ԃ̈ړ���
	const D3DXCOLOR SMASH_COLOR = D3DXCOLOR(0.9f, 0.0f, 0.1f, 0.7f);		// ������я�Ԃ̎��̐F
	const float CAT_CAMERA_HEIGHT = 250.0f;		// �L�̃J�����̍���
	const float CAT_CAMERA_DIS = 50.0f;			// �L�̃J�����̎��_�ƒ����_�̍����̍���(�p�x)
	const float RAT_CAMERA_HEIGHT = 100.0f;		// �L�̃J�����̍���
	const float RAT_CAMERA_DIS = 60.0f;			// �l�Y�~�̃J�����̎��_�ƒ����_�̍����̍���(�p�x)
	const float DIFF_ROT = 0.2f;					// �p�x�ɑ��������̊���
	const float CAMERA_ROT_MOVE = 0.032f;		// �J�����̌����̈ړ���
	const float ADD_ACTION_RADIUS = 40.0f;		// �T�[�`���̔��a�̒ǉ���
	const int NONE_PLAYERIDX = -1;				// �v���C���[�̔ԍ��̏����l
	const int CAT_SMASH_STUN = 120;				// �l�R�̃X�^������
	const int RAT_SMASH_STUN = 90;				// �l�Y�~�̃X�^������
	const int STUN_WAIT = 120;					// �I�u�W�F�N�g�����̑ҋ@����
	const int DEATH_WAIT = 120;					// ���S���̑ҋ@����
	const int SMASH_WAIT = 40;					// ������я�Ԃ̃J�E���g��
	const int STUN_FLASH_INTERVAL = 12;			// �v���C���[�̓_�ŊԊu
	const int DEATH_FLASH_INTERVAL = 4;			// �v���C���[�̓_�ŊԊu
	const WORD SMASH_VIBRATE = 30000;			// ������񂾎��̃o�C�u���[�V����
	const WORD STUN_VIBRATE = 20000;				// �C�₵���Ƃ��̃o�C�u���[�V����
}

//==============================
// �R���X�g���N�^
//==============================
CPlayer::CPlayer() : CCharacter(CObject::TYPE_PLAYER, CObject::PRIORITY_PLAYER)
{
	// �R���X�g���N�^�̔�
	Box();
}

//==============================
// �I�[�o�[���[�h�R���X�g���N�^
//==============================
CPlayer::CPlayer(CObject::TYPE type, PRIORITY priority) : CCharacter(type, priority)
{
	// �R���X�g���N�^�̔�
	Box();
}

//==============================
// �f�X�g���N�^
//==============================
CPlayer::~CPlayer()
{

}

//==============================
// �R���X�g���N�^�̔�
//==============================
void CPlayer::Box(void)
{
	// �S�Ă̒l���N���A����
	m_pMotion = nullptr;				// ���[�V�����̏��
	m_pPlayerID = nullptr;				// �v���C���[��ID�\��
	m_pStun = nullptr;					// �C��̏��
	m_pRatGhost = nullptr;				// �H��l�Y�~�̏��
	m_pRessrectionFan = nullptr;		// �~�͈̔͂̏��
	m_pRecoveringUI = nullptr;			// �񕜒���UI�̏��
	m_pSpeechMessage = nullptr;			// �`�B���b�Z�[�W�̏��
	m_sizeColl = NONE_D3DXVECTOR3;		// �����蔻��̃T�C�Y
	m_col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);				// �F
	m_type = TYPE_CAT;					// ���
	m_nPlayerIdx = NONE_PLAYERIDX;		// �v���C���[�̃C���f�b�N�X
	m_fSpeed = 0.0f;					// ���x
	m_fSpeedCopy = 0.0f;				// ���x�̃R�s�[
	m_fRotDest = 0.0f;					// �ڕW
	m_fStunHeight = 0.0f;				// �C�₪�o�鍂��
	m_bAttack = false;					// �U��������
	m_bMove = false;					// �ړ����Ă��邩
	m_bDisp = true;						// �\�����邩
	m_bDispSmash = false;				// ������їp�̕\�����邩
	m_CameraRot = NONE_D3DXVECTOR3;		// �J�����̌���
	m_nResurrectionTime = 0;			// ��������܂ł̎���
	m_bTutorial = false;
	m_bKill = false;
	m_bSe = false;						// SE�Đ��������ǂ���
	m_bCatSe = false;					// �l�R�pSE�Đ���
	m_bRatSe = false;					// �l�Y�~�pSE�Đ���

	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		m_pDeathArrow[nCnt] = nullptr;
	}

	for (int nCnt = 0; nCnt < LOG_MAX; nCnt++)
	{
		m_apLog[nCnt] = nullptr;
	}
	m_nLogNumber = 0;
}

//==============================
// �v���C���[�̏���������
//==============================
HRESULT CPlayer::Init(void)
{
	if (FAILED(CCharacter::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_pMotion = nullptr;				// ���[�V�����̏��
	m_pPlayerID = nullptr;				// �v���C���[��ID�\��
	m_pStun = nullptr;					// �C��̏��
	m_pRatGhost = nullptr;				// �H��l�Y�~�̏��
	m_pRessrectionFan = nullptr;		// �~�͈̔͂̏��
	m_pRecoveringUI = nullptr;			// �񕜒���UI�̏��
	m_pSpeechMessage = nullptr;			// �`�B���b�Z�[�W�̏��
	//m_move = NONE_D3DXVECTOR3;			// �ړ���
	m_sizeColl = NONE_D3DXVECTOR3;		// �����蔻��̃T�C�Y
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);				// �F
	m_type = TYPE_CAT;					// ���
	m_nPlayerIdx = NONE_PLAYERIDX;		// �v���C���[�̃C���f�b�N�X
	m_fSpeed = 0.0f;					// ���x
	m_fSpeedCopy = 0.0f;				// ���x�̃R�s�[
	m_fRotDest = 0.0f;					// �ڕW
	m_fStunHeight = 0.0f;				// �C�₪�o�鍂��
	m_bAttack = false;					// �U��������
	m_bMove = false;					// �ړ����Ă��邩
	m_bDisp = true;						// �\�����邩
	m_bDispSmash = false;				// ������їp�̕\�����邩
	m_bCatSe = false;					// �l�R�pSE�Đ���
	m_bRatSe = false;					// �l�Y�~�pSE�Đ���
	m_nResurrectionTime = 0;			// ��������܂ł̎���
	m_nLogPlayer = 0;

	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{// ���S���̏��
		m_pDeathArrow[nCnt] = nullptr;
	}

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �v���C���[�̏I������
//========================================
void CPlayer::Uninit(void)
{
	if (m_pMotion != nullptr)
	{ // ���[�V������ NULL ����Ȃ��ꍇ

		// ���[�V�����̃��������J������
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	if (m_pPlayerID != nullptr)
	{ // �v���C���[��ID�\���� NULL ����Ȃ��ꍇ

		// �v���C���[��ID�\���̏I������
		m_pPlayerID->Uninit();
		m_pPlayerID = nullptr;
	}

	if (m_pStun != nullptr)
	{ // �C�≉�o�� NULL ����Ȃ��ꍇ

		// �C�≉�o�̏I������
		m_pStun->Uninit();
		m_pStun = nullptr;
	}

	if (m_pRatGhost != nullptr)
	{ // �H��l�Y�~�� NULL ����Ȃ��ꍇ

		//�H��l�Y�~�̏I������
		m_pRatGhost->Uninit();
		m_pRatGhost = nullptr;
	}

	if (m_pRessrectionFan != nullptr)
	{ // �~�͈̔͂� NULL ����Ȃ��ꍇ

		//�~�͈̔͂̏I������
		m_pRessrectionFan = nullptr;
	}

	if (m_pRecoveringUI != nullptr)
	{ // �񕜒���UI�� NULL ����Ȃ��ꍇ

		//�񕜒���UI�̏I������
		m_pRecoveringUI->Uninit();
		m_pRecoveringUI = nullptr;
	}

	if (m_pSpeechMessage != nullptr)
	{ // �`�B���b�Z�[�W�� NULL ����Ȃ��Ƃ�

		//�`�B���b�Z�[�W�̏I������
		m_pSpeechMessage = nullptr;
	}

	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		if (m_pDeathArrow[nCnt] != nullptr)
		{ // ���S��� NULL ����Ȃ��Ƃ�

			//���S���̏I������
			m_pDeathArrow[nCnt]->Uninit();
			m_pDeathArrow[nCnt] = nullptr;
		}
	}

	for (int nCnt = 0; nCnt < LOG_MAX; nCnt++)
	{
		if (m_apLog[nCnt] != NULL)
		{
			m_apLog[nCnt]->Uninit();
			m_apLog[nCnt] = NULL;
		}
	}

	if (CManager::Get()->GetMode() == CScene::MODE_TUTORIAL)
	{
		// �v���C���[����������
		CTutorial::DeletePlayer(m_nPlayerIdx);
	}
	else
	{
		// �v���C���[����������
		CGame::DeletePlayer(m_nPlayerIdx);
	}

	// �I������
	CCharacter::Uninit();
}

//=====================================
// �v���C���[�̍X�V����
//=====================================
void CPlayer::Update(void)
{
	// ��Q���Ƃ̓����蔻��
	collision::ObstacleHit(this, m_sizeColl.x, m_sizeColl.y, m_sizeColl.z);

	// �C���Ԃ̊Ǘ�
	StunStateManager();

	// ��Ԃ̊Ǘ�
	StateManager();

	// �N���\��Q����x�����o����Q���̃T�[�`
	collision::ObstacleSearch(this, m_sizeColl.x + ADD_ACTION_RADIUS);

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_E) ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_B, m_nPlayerIdx) == true)
	{ // �A�N�V�����L�[���������ꍇ

		if (m_State != STATE_DEATH &&
			m_StunState != STUNSTATE_SMASH &&
			m_StunState != STUNSTATE_STUN)
		{ // �A�N�V�������N������ꍇ

			// ��Q���̃A�N�V��������
			collision::ObstacleAction(this, m_sizeColl.x + ADD_ACTION_RADIUS);
		}
	}

#if CAMERA != 0
	//�J�������̍X�V
	CameraUpdate();
#endif // CAMERA

#ifdef _DEBUG

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_1))
	{
		SetLog(m_nPlayerIdx, CLog::TYPE::TYPE_DEATH);
	}

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_2))
	{
		SetLog(m_nPlayerIdx, CLog::TYPE::TYPE_STUN);
	}

#endif // _DEBUG

	if (m_pMotion != nullptr)
	{ // ���[�V������ NULL ����Ȃ��ꍇ

		// ���[�V�����̍X�V����
		m_pMotion->Update();
	}

	for (int nCnt = 0; nCnt < LOG_MAX; nCnt++)
	{
		if (m_apLog[nCnt] != NULL)
		{
			m_apLog[nCnt]->Update();
		}
	}

	// �ǂ̓����蔻��
	collision::WallCollision(this, m_sizeColl);

	// �f�o�b�O�\��
	CManager::Get()->GetDebugProc()->Print("�ʒu�F%f %f %f\n�����F%f %f %f\n", GetPos().x, GetPos().y, GetPos().z, GetRot().x, GetRot().y, GetRot().z);
}

//=====================================
// �v���C���[�̕`�揈��
//=====================================
void CPlayer::Draw(void)
{
	if (m_bDisp == true)
	{ // �\����Ԃ̂Ƃ�

		if (m_bDispSmash == true)
		{ // ������΂���Ă�Ƃ�

			// �`�揈��(�F)
			CCharacter::Draw(m_col);
		}
		else
		{ // ����ȊO�̂Ƃ�

			// �`�揈��
			CCharacter::Draw();
		}
	}

	for (int nCnt = 0; nCnt < LOG_MAX; nCnt++)
	{
		if (m_apLog[nCnt] != NULL)
		{
			m_apLog[nCnt]->Draw();
		}
	}

	if (m_pPlayerID != nullptr)
	{ // �v���C���[��ID�\���� NULL ����Ȃ��ꍇ

		if (m_nPlayerIdx != CObject::GetDrawIdx() && (CManager::Get()->GetMode() == CScene::MODE_GAME || CManager::Get()->GetMode() == CScene::MODE_TUTORIAL))
		{
			m_pPlayerID->Draw();
		}
	}
}

//=====================================
// ������я��
//=====================================
void CPlayer::Smash(const float fAngle)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();		// �ʒu���擾����
	D3DXVECTOR3 move = GetMove();	// �ړ��ʂ��擾����

	if (m_State == STATE_NONE &&
		m_StunState == STUNSTATE_NONE)
	{ // �_���[�W�󂯂��Ԃ������ꍇ

		// �o�C�u���[�V������ݒ肷��
		CManager::Get()->GetInputGamePad()->GetRightVibration(GetPlayerIdx(), SMASH_VIBRATE, SMASH_WAIT);
		CManager::Get()->GetInputGamePad()->GetLeftVibration(GetPlayerIdx(), SMASH_VIBRATE, SMASH_WAIT);

		// �ړ��ʂ��Z�o����
		move.x = sinf(fAngle) * SMASH_MOVE.x;
		move.y = SMASH_MOVE.y;
		move.z = cosf(fAngle) * SMASH_MOVE.z;

		m_fRotDest = fAngle;

		// �ʒu���Z
		pos += move;

		// �ړ��ʐݒ�
		SetMove(move);

		// �ʒu�ݒ�
		SetPos(pos);

		if (m_type == TYPE_RAT)
		{
			// �`���b�Đ�
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_CHU);
			m_bRatSe = true;
		}
		else if (m_type == TYPE_CAT)
		{
			// �ɂ�`��Đ�
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_CATDAMAGE);
			m_bCatSe = true;


		}

		// ������я�Ԃɂ���
		m_StunState = STUNSTATE_SMASH;

		// �C���ԃJ�E���g��ݒ肷��
		m_StunStateCount = SMASH_WAIT;
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CPlayer::SetData(const D3DXVECTOR3& pos, const int nID, const TYPE type)
{
	// ���̐ݒ菈��
	SetPos(pos);					// �ʒu
	SetPosOld(pos);					// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);		// ����
	SetScale(NONE_SCALE);			// �g�嗦

	// �S�Ă̒l���N���A����
	m_pStun = nullptr;					// �C��̏��
	//m_move = NONE_D3DXVECTOR3;			// �ړ���
	m_sizeColl = NONE_D3DXVECTOR3;		// �����蔻��̃T�C�Y
	m_type = type;						// ���
	m_nPlayerIdx = nID;					// �v���C���[�̃C���f�b�N�X
	m_fSpeed = 0.0f;					// ���x
	m_fSpeedCopy = 0.0f;				// ���x�̃R�s�[
	m_bAttack = false;					// �U��������
	m_bMove = false;					// �ړ����Ă��邩

	if (m_pPlayerID == nullptr)
	{ // �v���C���[��ID�\���� NULL �̏ꍇ

		// �v���C���[��ID�\���̐�������
		m_pPlayerID = CPlayerID::Create(pos, nID);
	}
}

//=======================================
// ��������
//=======================================
CPlayer* CPlayer::Create(const D3DXVECTOR3& pos, const int nID, const TYPE type)
{
	// �v���C���[�̃|�C���^
	CPlayer* pPlayer = nullptr;

	if (pPlayer == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		switch (type)
		{
		case TYPE::TYPE_CAT:		// �l�R

			// �l�R�𐶐�
			pPlayer = new CCat;

			break;

		case TYPE::TYPE_RAT:		// �l�Y�~

			// �l�Y�~�𐶐�
			pPlayer = new CRat;

			break;

		default:					// ��L�ȊO

			// ��~
			assert(false);

			break;
		}
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pPlayer != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pPlayer->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pPlayer->SetData(pos, nID, type);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �v���C���[�̃|�C���^��Ԃ�
	return pPlayer;
}

//=======================================
// �ړ����쏈��
//=======================================
void CPlayer::MoveControl(void)
{
	if (CManager::Get()->GetMode() == CScene::MODE_GAME || CManager::Get()->GetMode() == CScene::MODE_TUTORIAL)
	{
		// ���[�J���ϐ��錾
		//D3DXVECTOR3 rot = GetRot();

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_D) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLXPress(m_nPlayerIdx) > 0)
		{ // �E���������ꍇ

			if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true ||
				CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nPlayerIdx) > 0)
			{ // ����������ꍇ

				// ������ݒ肷��
				//rot.y = m_CameraRot.y + D3DX_PI * -0.75f;
				m_fRotDest = m_CameraRot.y + D3DX_PI * -0.75f;
			}
			else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true ||
				CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nPlayerIdx) < 0)
			{ // �����������ꍇ

				// ������ݒ肷��
				//rot.y = m_CameraRot.y + D3DX_PI * -0.25f;
				m_fRotDest = m_CameraRot.y + D3DX_PI * -0.25f;
			}
			else
			{ // ��L�ȊO

				// ������ݒ肷��
				//rot.y = m_CameraRot.y + D3DX_PI * -0.5f;
				m_fRotDest = m_CameraRot.y + D3DX_PI * -0.5f;

			}
			m_bMove = true;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_A) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLXPress(m_nPlayerIdx) < 0)
		{ // �����������ꍇ

			if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true ||
				CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nPlayerIdx) > 0)
			{ // ����������ꍇ

				// ������ݒ肷��
				//rot.y = m_CameraRot.y + D3DX_PI * 0.75f;
				m_fRotDest = m_CameraRot.y + D3DX_PI * 0.75f;

			}
			else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true ||
				CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nPlayerIdx) < 0)
			{ // �����������ꍇ

				// ������ݒ肷��
				//rot.y = m_CameraRot.y + D3DX_PI * 0.25f;
				m_fRotDest = m_CameraRot.y + D3DX_PI * 0.25f;
			}
			else
			{ // ��L�ȊO

				// ������ݒ肷��
				//rot.y = m_CameraRot.y + D3DX_PI * 0.5f;
				m_fRotDest = m_CameraRot.y + D3DX_PI * 0.5f;
			}
			m_bMove = true;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nPlayerIdx) > 0)
		{ // ����������ꍇ

			// ������ݒ肷��
			//rot.y = m_CameraRot.y + D3DX_PI * 1.0f;
			m_fRotDest = m_CameraRot.y + D3DX_PI * 1.0f;
			m_bMove = true;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nPlayerIdx) < 0)
		{ // �����������ꍇ

			// ������ݒ肷��
			//rot.y = m_CameraRot.y + D3DX_PI * 0.0f;
			m_fRotDest = m_CameraRot.y + D3DX_PI * 0.0f;
			m_bMove = true;
		}
		else
		{ // ��L�ȊO
			m_bMove = false;
			// ���x��ݒ肷��
			m_fSpeed = 0.0f;
		}
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nPlayerIdx) > 0)
	{ // ����������ꍇ

		// ������ݒ肷��
		//rot.y = m_CameraRot.y + D3DX_PI * 1.0f;
		m_fRotDest = m_CameraRot.y + D3DX_PI * 1.0f;
		m_bMove = true;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nPlayerIdx) < 0)
	{ // �����������ꍇ

		// ������ݒ肷��
		//rot.y = m_CameraRot.y + D3DX_PI * 0.0f;
		m_fRotDest = m_CameraRot.y + D3DX_PI * 0.0f;
		m_bMove = true;
	}
	else
	{ // ��L�ȊO

		// �ړ��󋵂� false �ɂ���
		m_bMove = false;

		// ���x��ݒ肷��
		m_fSpeed = 0.0f;
	}
}

//=======================================
// �ړ�����
//=======================================
void CPlayer::Move(void)
{
	if (CManager::Get()->GetMode() == CScene::MODE_GAME || CManager::Get()->GetMode() == CScene::MODE_TUTORIAL)
	{
		// �ʒu���擾����
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 move = GetMove();

		// �ړ��ʂ�ݒ肷��
		move.x = -sinf(m_fRotDest) * m_fSpeed;
		move.z = -cosf(m_fRotDest) * m_fSpeed;

		// �ړ��ʂ����Z����
		pos.x += move.x;
		pos.z += move.z;

		// �ړ��ʂ�K�p����
		SetMove(move);

		// �ʒu��K�p����
		SetPos(pos);
	}
}

//=======================================
// ���ꂼ��̃v���C���[�̃J�����̍X�V
//=======================================
void CPlayer::CameraUpdate(void)
{
#ifdef _DEBUG

	if (CManager::Get()->GetMode() == CScene::MODE::MODE_GAME)
	{
		if (CGame::GetEditbool() == false)
		{
			CMultiCamera *pCamera = CManager::Get()->GetMlutiCamera(m_nPlayerIdx);
			D3DXVECTOR3 Pos = GetPos();

			if (m_type == TYPE::TYPE_CAT)
			{ //�L�̃J�����̈ʒu
				pCamera->SetPosR(D3DXVECTOR3(
					Pos.x,
					Pos.y + CAT_CAMERA_HEIGHT,
					Pos.z
				));
				pCamera->SetPosV(D3DXVECTOR3(
					Pos.x + sinf(m_CameraRot.y + (D3DX_PI * 1.0f)) * 200.0f,
					Pos.y + CAT_CAMERA_HEIGHT + CAT_CAMERA_DIS,
					Pos.z + cosf(m_CameraRot.y + (D3DX_PI * 1.0f)) * 200.0f));
			}
			else
			{ //�l�Y�~�̃J�����̈ʒu
				pCamera->SetPosR(D3DXVECTOR3(
					Pos.x,
					Pos.y + RAT_CAMERA_HEIGHT,
					Pos.z
				));
				pCamera->SetPosV(D3DXVECTOR3(
					Pos.x + sinf(m_CameraRot.y + (D3DX_PI * 1.0f)) * 200.0f,
					Pos.y + RAT_CAMERA_HEIGHT + RAT_CAMERA_DIS,
					Pos.z + cosf(m_CameraRot.y + (D3DX_PI * 1.0f)) * 200.0f));
			}

			if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LSHIFT) == true ||
				CManager::Get()->GetInputGamePad()->GetGameStickRXPress(m_nPlayerIdx) < 0)
			{ // �E�X�e�B�b�N���E�ɓ|�����ꍇ

			  // �J�����̌��������Z����
				m_CameraRot.y -= CAMERA_ROT_MOVE;
			}
			if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_RSHIFT) == true ||
				CManager::Get()->GetInputGamePad()->GetGameStickRXPress(m_nPlayerIdx) > 0)
			{ // �E�X�e�B�b�N���E�ɓ|�����ꍇ

			  // �J�����̌��������Z����
				m_CameraRot.y += CAMERA_ROT_MOVE;
			}

			// �����̐��K��
			useful::RotNormalize(&m_CameraRot.y);
		}
	}
	else
	{
		CMultiCamera *pCamera = CManager::Get()->GetMlutiCamera(m_nPlayerIdx);
		D3DXVECTOR3 Pos = GetPos();

		if (m_type == TYPE::TYPE_CAT)
		{ //�L�̃J�����̈ʒu
			pCamera->SetPosR(D3DXVECTOR3(
				Pos.x,
				Pos.y + CAT_CAMERA_HEIGHT,
				Pos.z
			));
			pCamera->SetPosV(D3DXVECTOR3(
				Pos.x + sinf(m_CameraRot.y + (D3DX_PI * 1.0f)) * 200.0f,
				Pos.y + CAT_CAMERA_HEIGHT + CAT_CAMERA_DIS,
				Pos.z + cosf(m_CameraRot.y + (D3DX_PI * 1.0f)) * 200.0f));
		}
		else
		{ //�l�Y�~�̃J�����̈ʒu
			pCamera->SetPosR(D3DXVECTOR3(
				Pos.x,
				Pos.y + RAT_CAMERA_HEIGHT,
				Pos.z
			));
			pCamera->SetPosV(D3DXVECTOR3(
				Pos.x + sinf(m_CameraRot.y + (D3DX_PI * 1.0f)) * 200.0f,
				Pos.y + RAT_CAMERA_HEIGHT + RAT_CAMERA_DIS,
				Pos.z + cosf(m_CameraRot.y + (D3DX_PI * 1.0f)) * 200.0f));
		}

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LSHIFT) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickRXPress(m_nPlayerIdx) < 0)
		{ // �E�X�e�B�b�N���E�ɓ|�����ꍇ

			// �J�����̌��������Z����
			m_CameraRot.y -= CAMERA_ROT_MOVE;
		}
		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_RSHIFT) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickRXPress(m_nPlayerIdx) > 0)
		{ // �E�X�e�B�b�N���E�ɓ|�����ꍇ

			// �J�����̌��������Z����
			m_CameraRot.y += CAMERA_ROT_MOVE;
		}

		// �����̐��K��
		useful::RotNormalize(&m_CameraRot.y);
	}
#endif // _DEBUG

	CMultiCamera *pCamera = CManager::Get()->GetMlutiCamera(m_nPlayerIdx);
	D3DXVECTOR3 Pos = GetPos();

	if (m_type == TYPE::TYPE_CAT)
	{ //�L�̃J�����̈ʒu
		pCamera->SetPosR(D3DXVECTOR3(
			Pos.x,
			Pos.y + CAT_CAMERA_HEIGHT,
			Pos.z
		));
		pCamera->SetPosV(D3DXVECTOR3(
			Pos.x + sinf(m_CameraRot.y + (D3DX_PI * 1.0f)) * 200.0f,
			Pos.y + CAT_CAMERA_HEIGHT + CAT_CAMERA_DIS,
			Pos.z + cosf(m_CameraRot.y + (D3DX_PI * 1.0f)) * 200.0f));
	}
	else
	{ //�l�Y�~�̃J�����̈ʒu
		pCamera->SetPosR(D3DXVECTOR3(
			Pos.x,
			Pos.y + RAT_CAMERA_HEIGHT,
			Pos.z
		));
		pCamera->SetPosV(D3DXVECTOR3(
			Pos.x + sinf(m_CameraRot.y + (D3DX_PI * 1.0f)) * 200.0f,
			Pos.y + RAT_CAMERA_HEIGHT + RAT_CAMERA_DIS,
			Pos.z + cosf(m_CameraRot.y + (D3DX_PI * 1.0f)) * 200.0f));
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LSHIFT) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickRXPress(m_nPlayerIdx) < 0)
	{ // �E�X�e�B�b�N���E�ɓ|�����ꍇ

	  // �J�����̌��������Z����
		m_CameraRot.y -= CAMERA_ROT_MOVE;
	}
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_RSHIFT) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickRXPress(m_nPlayerIdx) > 0)
	{ // �E�X�e�B�b�N���E�ɓ|�����ꍇ

	  // �J�����̌��������Z����
		m_CameraRot.y += CAMERA_ROT_MOVE;
	}

	// �����̐��K��
	useful::RotNormalize(&m_CameraRot.y);
}

//=======================================
// �����̕␳����
//=======================================
void CPlayer::RotNormalize(void)
{
	// �������擾����
	D3DXVECTOR3 rot = GetRot();

	// �����̕␳����
	useful::RotCorrect(m_fRotDest, &rot.y, DIFF_ROT);

	// ������K�p����
	SetRot(rot);
}

////=======================================
//// �U������
////=======================================
//void CPlayer::Attack(void)
//{
//	// ���[�J���ϐ��錾
//	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();		// �擪�̏�Q�����擾����
//	D3DXVECTOR3 pos = GetPos();
//	D3DXVECTOR3 rot = GetRot();
//
//	if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_B,m_nRatIdx) == true/* && m_bAttack == false*/)
//	{ // B�{�^�����������ꍇ
//
//		while (pObstacle != nullptr)
//		{ // �u���b�N�̏�� NULL ����Ȃ��ꍇ
//
//			if (useful::RectangleCollisionXY(D3DXVECTOR3(pos.x + sinf(rot.y) * ATTACK_DISTANCE, pos.y, pos.z + cosf(rot.y) * ATTACK_DISTANCE), pObstacle->GetPos(),
//				SIZE, pObstacle->GetFileData().vtxMax,
//				-SIZE, pObstacle->GetFileData().vtxMin) == true)
//			{ // XY�̋�`�ɓ������Ă���
//
//				if (useful::RectangleCollisionXZ(D3DXVECTOR3(pos.x + sinf(rot.y) * ATTACK_DISTANCE, pos.y, pos.z + cosf(rot.y) * ATTACK_DISTANCE), pObstacle->GetPos(),
//					SIZE, pObstacle->GetFileData().vtxMax,
//					-SIZE, pObstacle->GetFileData().vtxMin) == true)
//				{ // XZ�̋�`�ɓ������Ă���
//
//					// ��Q���̏I������
//					pObstacle->Uninit();
//				}
//			}
//
//			// ���̃I�u�W�F�N�g��������
//			pObstacle = pObstacle->GetNext();
//		}
//
//		//m_bAttack = true;		// �U��������Ԃɂ���
//	}
//}

//=======================================
// �C�⏈��
//=======================================
bool CPlayer::Stun(int StunTime)
{
	if (m_StunState == STUNSTATE_NONE &&
		m_State == STATE_NONE)
	{ // �ʏ��Ԃ������ꍇ

		// �o�C�u���[�V������ݒ肷��
		CManager::Get()->GetInputGamePad()->GetRightVibration(GetPlayerIdx(), STUN_VIBRATE, StunTime);
		CManager::Get()->GetInputGamePad()->GetLeftVibration(GetPlayerIdx(), STUN_VIBRATE, StunTime);

		// �C���Ԃɂ���
		m_StunState = STUNSTATE_STUN;
		m_StunStateCount = StunTime;

		if (CManager::Get()->GetMode() == CScene::MODE_TUTORIAL)
		{
			for (int nCnt = 0; nCnt < 4; nCnt++)
			{
				CTutorial::GetPlayer(nCnt)->SetLog(m_nPlayerIdx, CLog::TYPE::TYPE_STUN);
			}
		}
		else if (CManager::Get()->GetMode() == CScene::MODE_GAME)
		{
			for (int nCnt = 0; nCnt < 4; nCnt++)
			{
				CGame::GetPlayer(nCnt)->SetLog(m_nPlayerIdx, CLog::TYPE::TYPE_STUN);
			}
		}

		// �C�≉�o�̐ݒ菈��
		SetStun(GetPos());

		// true(�C��ł���) ��Ԃ�
		return true;
	}
	else
	{ // ��L�ȊO

		// false(�C�⎸�s) ��Ԃ�
		return false;
	}

	////�L�ƃl�Y�~�ŋC��̎d�l��ς���ꍇ�͎g����
	//if (m_type == TYPE_CAT)
	//{ // �L�̏ꍇ
	//}
	//else if (m_type == TYPE_RAT)
	//{ // �l�Y�~�̏ꍇ
	//}
}

//=======================================
// �A�C�e���̎擾����
//=======================================
void CPlayer::GetItem(const CItem::TYPE type)
{

}

//=======================================
// �A�C�e���̑����̎擾����
//=======================================
int CPlayer::GetItemCount(void) const
{
	// ��~
	assert(false);

	// 0��Ԃ�
	return 0;
}

//=======================================
// �W�����v�̐ݒ菈��
//=======================================
void CPlayer::SetEnableJump(const bool bJump)
{

}

//=======================================
// �C���Ԃ̊Ǘ�
//=======================================
void CPlayer::StunStateManager(void)
{
	switch (m_StunState)
	{
	case STUNSTATE_NONE:	// �����

		break;

	case STUNSTATE_SMASH:	// ������я��

		// �F�̐ݒ�
		m_col = SMASH_COLOR;

		if (m_StunStateCount >= 38)
		{ // ��莞�Ԉȏゾ������

			m_bDispSmash = true;
		}
		else if (m_bDispSmash == true)
		{ // �F�t���ŕ\�����Ă���

			// �F��\�����Ȃ���Ԃɂ���
			m_bDispSmash = false;
		}

		// �J�E���g�����Z����
		m_StunStateCount--;

		if (m_StunStateCount <= 0)
		{ // �J�E���g����萔�ȉ��ɂȂ����ꍇ

			// �C���Ԃɂ���
			m_StunState = STUNSTATE_STUN;
			SetRatStun(true);

			if (m_type == TYPE_CAT && m_bCatSe == false)
			{
				// �ɂ�`��Đ�
				CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_CATDAMAGE);

				m_bCatSe = true;
			}

			// �X�^�����Ԃ̐ݒ�
			if (m_type == TYPE::TYPE_CAT)
			{// �l�R�̏ꍇ
				m_StunStateCount = CAT_SMASH_STUN;

				// �o�C�u���[�V������ݒ肷��
				CManager::Get()->GetInputGamePad()->GetRightVibration(GetPlayerIdx(), STUN_VIBRATE, CAT_SMASH_STUN);
				CManager::Get()->GetInputGamePad()->GetLeftVibration(GetPlayerIdx(), STUN_VIBRATE, CAT_SMASH_STUN);
			}
			else if (m_type == TYPE::TYPE_RAT)
			{// �l�Y�~�̏ꍇ
				m_StunStateCount = RAT_SMASH_STUN;

				// �o�C�u���[�V������ݒ肷��
				CManager::Get()->GetInputGamePad()->GetRightVibration(GetPlayerIdx(), STUN_VIBRATE, RAT_SMASH_STUN);
				CManager::Get()->GetInputGamePad()->GetLeftVibration(GetPlayerIdx(), STUN_VIBRATE, RAT_SMASH_STUN);
			}

			if (CManager::Get()->GetMode() == CScene::MODE_TUTORIAL)
			{
				for (int nCnt = 0; nCnt < 4; nCnt++)
				{
					CTutorial::GetPlayer(nCnt)->SetLog(m_nPlayerIdx, CLog::TYPE::TYPE_STUN);
				}
			}
			else if (CManager::Get()->GetMode() == CScene::MODE_GAME)
			{
				for (int nCnt = 0; nCnt < 4; nCnt++)
				{
					CGame::GetPlayer(nCnt)->SetLog(m_nPlayerIdx, CLog::TYPE::TYPE_STUN);
				}
			}

			// �C�≉�o�̐ݒ菈��
			SetStun(GetPos());
		}

		// �ړ��󋵂� false �ɂ���
		m_bMove = false;

		break;

	case STUNSTATE_STUN:	//�C����

		if (m_pStun != NULL)
		{
			m_pStun->SetPos(D3DXVECTOR3(GetPos().x, GetPos().y + m_fStunHeight, GetPos().z));
		}

		if (m_type == TYPE_RAT && m_bRatSe == false)
		{
			// �`���b�Đ�
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_CHU);
			m_bRatSe = true;
		}
		else if (m_type == TYPE_CAT && m_bCatSe == false)
		{
			// �ɂ�`��Đ�
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_CATDAMAGE);

			m_bCatSe = true;
		}

		// �J�E���g�����Z����
		m_StunStateCount--;

		if (m_StunStateCount <= 0)
		{ // �J�E���g����萔�ȉ��ɂȂ����ꍇ

			// ���G��Ԃɂ���
			m_StunState = STUNSTATE_WAIT;
			m_StunStateCount = STUN_WAIT;
			m_bSe = false;

			if (m_type == TYPE_RAT)
			{
				m_bRatSe = false;

			}
			else if (m_type == TYPE_CAT)
			{
				m_bCatSe = false;

			}

			if (m_pStun != nullptr)
			{ // �C�≉�o�� NULL �̏ꍇ

				// �C�≉�o���폜����
				m_pStun->Uninit();
				m_pStun = nullptr;
			}
		}
		else
		{
			if (m_bSe == false)
			{ // SE�Đ����ĂȂ�
				// �s���s���Đ�
				CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_PIYOPIYO);
				m_bSe = true;
			}
		}

		// �ړ��󋵂� false �ɂ���
		m_bMove = false;

		break;

	case STUNSTATE_WAIT:	//��Q���̂ݖ��G���

		if ((m_StunStateCount % STUN_FLASH_INTERVAL) == 0)
		{ // ��莞�Ԍo������

			// �\����Ԑ؂�ւ�
			m_bDisp = m_bDisp ? false : true;
		}

		m_StunStateCount--;

		if (m_StunStateCount <= 0)
		{ // �J�E���g����萔�ȉ��ɂȂ����ꍇ
			m_StunState = STUNSTATE_NONE;
			m_bDisp = true;		// �\�������Ԃɂ���
		}

		break;

	default:

		// ��~
		assert(false);

		break;
	}
}

//=======================================
// ��Ԃ̊Ǘ�
//=======================================
void CPlayer::StateManager(void)
{
	switch (m_State)
	{
	case STATE_NONE:

		break;

	case STATE_INVINCIBLE:	//���G���

		// �J�E���g�����Z����
		m_StateCount--;

		if ((m_StateCount % DEATH_FLASH_INTERVAL) == 0)
		{ // ��莞�Ԍo������

			// �\����Ԑ؂�ւ�
			m_bDisp = m_bDisp ? false : true;
		}

		if (m_StateCount <= 0)
		{ // �J�E���g����萔�ȉ��ɂȂ����ꍇ
			
			// ����Ԃɂ���
			m_State = STATE_NONE;
			m_bDisp = true;		// �\�������Ԃɂ���
		}
		break;

	case STATE_DEATH:	//���S���

		D3DXVECTOR3 pos = GetPos();		// �ʒu�擾

		m_bDisp = false;		// �\�����Ȃ���Ԃɂ���

		if (m_pRatGhost != nullptr)
		{ // �H��l�Y�~�� NULL ����Ȃ��Ƃ�

			// �H��l�Y�~�̈ʒu�ݒ�
			m_pRatGhost->SetPos(pos);
		}

		if (m_pRessrectionFan != nullptr)
		{ // �~�͈̔͂� NULL ����Ȃ��Ƃ�

			// �~�͈̔͂̈ʒu�ݒ�
			m_pRessrectionFan->SetPos(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z));
		}

		if (m_pRecoveringUI != nullptr)
		{ // �񕜒�UI�� NULL ����Ȃ��Ƃ�

			// �񕜒�UI�̈ʒu�ݒ�
			m_pRecoveringUI->SetPos(D3DXVECTOR3(pos.x + 80.0f, pos.y + 100.0f, pos.z));

			// �񕜒�UI�̑O��̈ʒu�ݒ�
			m_pRecoveringUI->SetPosOld(GetPosOld());

		}

		if (m_pSpeechMessage != nullptr)
		{ // �`�B���b�Z�[�W�� NULL ����Ȃ��Ƃ�

			// �`�B���b�Z�[�W�̈ʒu�ݒ�
			m_pSpeechMessage->SetPos(D3DXVECTOR3(pos.x, pos.y + 120.0f, pos.z));
		}

		break;
	}
}

//=======================================
// ���O�̐����ԍ��̉��Z
//=======================================
void CPlayer::SetLog(int PlayerIdx, CLog::TYPE Type)
{
	for (int nCnt = 0; nCnt < LOG_MAX; nCnt++)
	{
		if (m_apLog[nCnt] == NULL)
		{
			m_apLog[nCnt] = CLog::Create(m_nPlayerIdx, PlayerIdx, m_nLogNumber, Type);
			m_apLog[nCnt]->SetLogIdx(nCnt);
			m_apLog[nCnt]->SetMain(this);
			break;
		}
	}

	m_nLogNumber++;
}

//=======================================
// ���O�̐����ԍ��̌��Z
//=======================================
void CPlayer::DelLogNumber(int nLogIdex)
{
	m_nLogNumber--;

	if (m_apLog[nLogIdex] != NULL)
	{
		m_apLog[nLogIdex]->Uninit();
		m_apLog[nLogIdex] = NULL;
	}

	for (int nCnt = 0; nCnt < LOG_MAX; nCnt++)
	{
		if (m_apLog[nCnt] != NULL)
		{
			m_apLog[nCnt]->DelCreateNumber();
		}
	}
}

//=======================================
// ��Ԃ̐ݒ菈��
//=======================================
void CPlayer::SetState(STATE State)
{
	m_State = State;

	if (CManager::Get()->GetMode() == CScene::MODE_TUTORIAL)
	{
		if (State == STATE_DEATH)
		{
			for (int nCnt = 0; nCnt < 4; nCnt++)
			{
				CTutorial::GetPlayer(nCnt)->SetLog(m_nPlayerIdx, CLog::TYPE::TYPE_DEATH);
			}
		}
		else if (State == STATE_INVINCIBLE)
		{
			for (int nCnt = 0; nCnt < 4; nCnt++)
			{
				CTutorial::GetPlayer(nCnt)->SetLog(m_nPlayerIdx, CLog::TYPE::TYPE_REVIVAL);
			}
		}
	}
	else if (CManager::Get()->GetMode() == CScene::MODE_GAME)
	{
		if (State == STATE_DEATH)
		{
			for (int nCnt = 0; nCnt < 4; nCnt++)
			{
				CGame::GetPlayer(nCnt)->SetLog(m_nPlayerIdx, CLog::TYPE::TYPE_DEATH);
			}
		}
		else if (State == STATE_INVINCIBLE)
		{
			for (int nCnt = 0; nCnt < 4; nCnt++)
			{
				CGame::GetPlayer(nCnt)->SetLog(m_nPlayerIdx, CLog::TYPE::TYPE_REVIVAL);
			}
		}

	}
}

//=======================================
// ���[�V�����̐ݒ菈��
//=======================================
void CPlayer::SetMotion(CMotion* pMotion)
{
	// ���[�V�����̏���ݒ肷��
	m_pMotion = pMotion;
}

//=======================================
// ���[�V�����̎擾����
//=======================================
CMotion* CPlayer::GetMotion(void) const
{
	// ���[�V�����̏���Ԃ�
	return m_pMotion;
}

//=======================================
// �v���C���[��ID�̎擾����
//=======================================
CPlayerID* CPlayer::GetPlayerID(void) const
{
	// �v���C���[��ID�̏���Ԃ�
	return m_pPlayerID;
}

//=======================================
// �C�≉�o�̐ݒ菈��
//=======================================
void CPlayer::SetStun(const D3DXVECTOR3& pos)
{
	if (m_pStun == nullptr)
	{ // �C�≉�o�� NULL �̏ꍇ

		// �C�≉�o�𐶐�����
		m_pStun = CStun::Create(D3DXVECTOR3(pos.x, pos.y + m_fStunHeight, pos.z));
	}
}

//=======================================
// �C�≉�o�̎擾����
//=======================================
CStun* CPlayer::GetStun(void) const
{
	// �C��̏���Ԃ�
	return m_pStun;
}

//=======================================
// �C�≉�o�̏�������
//=======================================
void CPlayer::DeleteStun(void)
{
	if (m_pStun != nullptr)
	{ // �C��̏�� NULL ����Ȃ��ꍇ

		// �C��̏I������
		m_pStun->Uninit();
		m_pStun = nullptr;
	}
}

//=======================================
// �H��l�Y�~�̐ݒ菈��
//=======================================
void CPlayer::SetRatGhost(const D3DXVECTOR3& pos)
{
	if (m_pRatGhost == nullptr)
	{ // �H��l�Y�~�� NULL �̂Ƃ�

		// �l�Y�~�̗H��̐���
		m_pRatGhost = CRatGhost::Create(pos);
	}
}

//=======================================
// �H��l�Y�~�̏��擾����
//=======================================
CRatGhost* CPlayer::GetRatGhost(void)
{
	// �H��l�Y�~�̏���Ԃ�
	return m_pRatGhost;
}

//=======================================
// �H��l�Y�~�̏���������
//=======================================
void CPlayer::DeleteRatGhost(void)
{
	if (m_pRatGhost != nullptr)
	{ // �H��l�Y�~�� NULL ����Ȃ��ꍇ

		//�H��l�Y�~�̏I������
		m_pRatGhost->Uninit();
		m_pRatGhost = nullptr;
	}
}

//=======================================
// �~�͈̔͂̐ݒ菈��
//=======================================
void CPlayer::SetRessrectionFan(const D3DXVECTOR3& pos, const D3DXCOLOR& col)
{
	if (m_pRessrectionFan == nullptr)
	{ // �~�͈̔͂� NULL �̂Ƃ�

		// �����Ԃ�̉~�͈̔͐���
		m_pRessrectionFan = CRessrectionFan::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z), col);
	}
}

//=======================================
// �~�͈̔͂̏��擾����
//=======================================
CRessrectionFan* CPlayer::GetRessrectionFan(void)
{
	// �~�͈̔͂̏���Ԃ�
	return m_pRessrectionFan;
}

//=======================================
// �~�͈̔͂̏���������
//=======================================
void CPlayer::DeleteRessrectionFan(void)
{
	if (m_pRessrectionFan != nullptr)
	{ // �~�͈̔͂� NULL ����Ȃ��ꍇ

		//�~�͈̔͂̏I������
		m_pRessrectionFan->Uninit();
		m_pRessrectionFan = nullptr;
	}
}

//=======================================
// �񕜒�UI�̐ݒ菈��
//=======================================
void CPlayer::SetRecoveringUI(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld)
{
	if (m_pRecoveringUI == nullptr)
	{ // �񕜒�UI�� NULL �̂Ƃ�

		// �񕜒�UI�͈̔͐���
		m_pRecoveringUI = CRecoveringUI::Create(D3DXVECTOR3(pos.x + 80.0f, pos.y + 100.0f, pos.z), posOld);
	}
}

//=======================================
// �񕜒�UI�̏��擾����
//=======================================
CRecoveringUI* CPlayer::GetRecoveringUI(void)
{
	// �񕜒�UI�̏���Ԃ�
	return m_pRecoveringUI;
}

//=======================================
// �񕜒�UI�̏���������
//=======================================
void CPlayer::DeleteRecoveringUI(void)
{
	if (m_pRecoveringUI != nullptr)
	{ // �񕜒�UI�� NULL ����Ȃ��ꍇ

		//�񕜒�UI�̏I������
		m_pRecoveringUI->Uninit();
		m_pRecoveringUI = nullptr;
	}
}

//=======================================
// �`�B���b�Z�[�W�̐ݒ菈��
//=======================================
void CPlayer::SetSpeechMessage(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const int nLife, const int type)
{
	if (m_pSpeechMessage == nullptr)
	{ // �`�B���b�Z�[�W�� NULL�̂Ƃ�

		m_pSpeechMessage = CSpeechMessage::Create(pos, size, nLife, (CSpeechMessage::TYPE)type,(int)m_nPlayerIdx);
	}
}

//=======================================
// �`�B���b�Z�[�W�̎擾����
//=======================================
CSpeechMessage* CPlayer::GetSpeechMessage(void)
{
	// �`�B���b�Z�[�W��Ԃ�
	return m_pSpeechMessage;
}

//=======================================
// �`�B���b�Z�[�W�̏�������
//=======================================
void CPlayer::DeleteSpeechMessage(void)
{
	if (m_pSpeechMessage != nullptr)
	{ // �`�B���b�Z�[�W�� NULL ����Ȃ��Ƃ�

		// �`�B���b�Z�[�W�̏I������
		m_pSpeechMessage->Uninit();
		m_pSpeechMessage = nullptr;
	}
}

//=======================================
// ���S���̐ݒ菈��
//=======================================
void CPlayer::SetDeathArrow(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& rot, const int nIdx, const int PlayerIdx)
{
	if (m_pDeathArrow[nIdx] == nullptr)
	{ // ���S��� NULL �̎�

	  // ���S���̐���
		m_pDeathArrow[nIdx] = CDeathArrow::Create(pos, posOld, rot, PlayerIdx);
	}
	else if (m_pDeathArrow[nIdx] != nullptr)
	{ // ���S��� NULL ����Ȃ��Ƃ�

		m_pDeathArrow[nIdx]->SetPos(pos);			// �ʒu�ݒ�
		m_pDeathArrow[nIdx]->SetPosOld(posOld);		// �O��̈ʒu�ݒ�
		m_pDeathArrow[nIdx]->SetRot(rot);			// �����ݒ�
	}
}

//=======================================
// ���S���̎擾����
//=======================================
CDeathArrow* CPlayer::GetDeathArrow(const int nIdx)
{
	// ���S���̏���Ԃ�
	return m_pDeathArrow[nIdx];
}

//=======================================
// ���S���̏�������
//=======================================
void CPlayer::DeleteDeathArrow(const int nIdx)
{
	if (m_pDeathArrow[nIdx] != nullptr)
	{ // ���S��� NULL ����Ȃ���

	  // ���S���̏I������
		m_pDeathArrow[nIdx]->Uninit();
		m_pDeathArrow[nIdx] = nullptr;
	}
}

//=======================================
// �ړ��ʂ̐ݒ菈��
//=======================================
//void CPlayer::SetMove(const D3DXVECTOR3& move)
//{
//	// �ړ��ʂ�ݒ肷��
//	m_move = move;
//}

//=======================================
// �ړ��ʂ̎擾����
//=======================================
//D3DXVECTOR3 CPlayer::GetMove(void) const
//{
//	// �ړ��ʂ�Ԃ�
//	return m_move;
//}

//=======================================
// �����蔻��T�C�Y�̐ݒ菈��
//=======================================
void CPlayer::SetSizeColl(const D3DXVECTOR3& size)
{
	// �����蔻��̃T�C�Y��ݒ肷��
	m_sizeColl = size;
}

//=======================================
// �����蔻��T�C�Y�̎擾����
//=======================================
D3DXVECTOR3 CPlayer::GetSizeColl(void) const
{
	// �����蔻��T�C�Y��Ԃ�
	return m_sizeColl;
}

//=======================================
// ��ނ̐ݒ菈��
//=======================================
void CPlayer::SetType(const TYPE type)
{
	// ��ނ�ݒ肷��
	m_type = type;
}

//=======================================
// ��ނ̎擾����
//=======================================
CPlayer::TYPE CPlayer::GetType(void) const
{
	// ��ނ�Ԃ�
	return m_type;
}

//=======================================
// �v���C���[��ID�̎擾����
//=======================================
int CPlayer::GetPlayerIdx(void) const
{
	// �v���C���[�̃C���f�b�N�X��Ԃ�
	return m_nPlayerIdx;
}

//=======================================
// ���x�̐ݒ菈��
//=======================================
void CPlayer::SetSpeed(const float fSpeed)
{
	// ���x��ݒ肷��
	m_fSpeed = fSpeed;
}

//=======================================
// ���x�̎擾����
//=======================================
float CPlayer::GetSpeed(void) const
{
	// ���x��Ԃ�
	return m_fSpeed;
}

//=======================================
// ���x�̃R�s�[�̐ݒ菈��
//=======================================
void CPlayer::SetSpeedCopy(const float fSpeed)
{
	// ���x�̃R�s�[��ݒ肷��
	m_fSpeedCopy = fSpeed;
}

//=======================================
// ���x�̃R�s�[�̎擾����
//=======================================
float CPlayer::GetSpeedCopy(void) const
{
	// ���x�̃R�s�[��Ԃ�
	return m_fSpeedCopy;
}

//=======================================
// �C��̏o�鍂���̐ݒ菈��
//=======================================
void CPlayer::SetStunHeight(const float fHeight)
{
	// �C��̏o�鍂����ݒ肷��
	m_fStunHeight = fHeight;
}

//=======================================
// �U������̐ݒ菈��
//=======================================
void CPlayer::SetEnableAttack(const bool bAttack)
{
	// �U�������ݒ肷��
	m_bAttack = bAttack;
}

//=======================================
// �U������̎擾����
//=======================================
bool CPlayer::IsAttack(void) const
{
	// �U�������Ԃ�
	return m_bAttack;
}

//=======================================
// �ړ��󋵂̐ݒ菈��
//=======================================
void CPlayer::SetEnableMove(const bool bMove)
{
	// �ړ��󋵂�ݒ肷��
	m_bMove = bMove;
}

//=======================================
// �ړ��󋵂̎擾����
//=======================================
bool CPlayer::IsMove(void) const
{
	// �ړ��󋵂�Ԃ�
	return m_bMove;
}

//=======================================
// ���񂾃l�Y�~�̕������Ԃ̍��v�ݒ�
//=======================================
void CPlayer::SetResurrectionTime(const int nRezTime)
{
	// �������Ԃ̍��v�ݒ�
	m_nResurrectionTime = nRezTime;
}

//=======================================
// ���񂾃l�Y�~�̕������Ԃ̍��v�ǉ�
//=======================================
void CPlayer::AddResurrectionTime(const int nRezTime)
{
	// �������Ԃ̍��v���Z
	m_nResurrectionTime += nRezTime;
}

//=======================================
// ���񂾃l�Y�~�̕������Ԃ̍��v�擾
//=======================================
int CPlayer::GetResurrectionTime(void)
{
	// �������Ԃ̍��v��Ԃ�
	return m_nResurrectionTime;
}

//=======================================
// �񕜒��\���̔���
//=======================================
void CPlayer::SetDispRecoveringUI(const bool bRez)
{
	if (m_pRecoveringUI != nullptr)
	{ // �񕜒�UI�� NULL����Ȃ�������

		// �񕜏�Ԃ�ݒ肷��
		m_pRecoveringUI->SetDisplayUI(bRez);
	}
}

//=======================================
// �񕜒��\���̎擾
//=======================================
bool CPlayer::IsDispRecoveringUI(void)
{
	// �񕜏�Ԃ�Ԃ�
	return m_pRecoveringUI->GetDisplayUI();
}

//=======================================
// SE�̍Đ��ݒ�
//=======================================
void CPlayer::SetSE(bool bSe)
{
	if (m_StunState != STUNSTATE_STUN)
	{
		m_bSe = bSe;

	}
}

//=======================================
// SE�̍Đ��擾
//=======================================
bool CPlayer::GetSE(void)
{ 
	return m_bSe; 
}