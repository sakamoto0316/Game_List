//============================================
//
//	�v���C���[�̏��� [playerlevel.cpp]
//	Author:sakamoto kai
//
//============================================
#include "player.h"
#include "playerEffect.h"
#include "object.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "motion.h"
#include "input.h"
#include "sound.h"
#include "Effect.h"
#include "game.h"
#include "time.h"
#include "camera.h"
#include "objGauge2D.h"
#include "objmeshCube.h"
#include "boss.h"
#include "number.h"
#include "numberFall.h"
#include "camera.h"
#include "object3D.h"
#include "CubeBlock.h"
#include "enemy.h"
#include "fade.h"
#include "log.h"
#include "CubeEffect.h"
#include "debugproc.h"

#define PLAYER_ROT_SPEED (0.2f)		//�v���C���[�̉�]�X�s�[�h
#define PLAYER_SPEED (10.0f)		//�v���C���[�̑���
#define PLAYER_JAMPPOWER (15.0f)	//�v���C���[�̃W�����v��
#define PLAYER_JAMPWALL (4.0f)		//�W�����v�܂ł̗͂̐U�蕝
#define JAMP_ACTIONNOT (4)			//�W�����v����s���o����܂�
#define COLLISION_SIZE (D3DXVECTOR3(20.0f,80.0f,20.0f))		//���̓����蔻��
#define ATTACK1_DAMAGE (200.0f)		//�n��U���P�̍U����
#define ATTACK2_DAMAGE (150.0f)		//�n��U���Q�̍U����
#define ATTACK3_DAMAGE (600.0f)		//�n��U���R�̍U����
#define SKY_ATTACK_DAMAGE (300.0f)	//�󒆍U���̍U����
#define DODGE_FRAME (10)			//����t���[��
#define DODGE_COOL (10)				//����̃N�[���^�C��
#define DODGE_EFFECTINTERVAL (3)	//����̎c���Ԋu
#define DODGE_SPEED (55.0f)			//����̈ړ����x
#define BOSS_DAMAGE (60.0f)			//�{�X�ɔ�e�����ۂ̃_���[�W
#define ENEMY_DAMAGE (30.0f)		//�G�ɔ�e�����ۂ̃_���[�W
#define FALL_DAMAGE (100.0f)		//���������ۂ̃_���[�W
#define WAIT_TIME (60)				//���G����
#define DAMAGE_TIME (10)			//�_���[�W�̃��A�N�V��������
#define REVIVAL_TIME (300)			//��������

//====================================================================
//�R���X�g���N�^
//====================================================================
CPlayer::CPlayer(int nPriority) :CObject(nPriority)
{
	SetWight(COLLISION_SIZE.x);
	SetHeight(COLLISION_SIZE.y);
	m_CameraPos = INITVECTOR3;
	m_pos = INITVECTOR3;
	m_move = INITVECTOR3;
	m_Objmove = INITVECTOR3;
	m_rot = D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f);
	m_bWallJump = false;
	m_bJump = false;
	m_nActionCount = 0;
	m_Action = ACTION_WAIT;
	m_AtkAction = ACTION_WAIT;
	m_nAttackHit = false;
	m_nAttackDamage = 0.0f;
	m_nAttackCount = 0;
	m_nAttackCountMax = 0;
	m_nAttackChainFrame = 0;
	m_nDodgeCount = 0;
	m_nDodgeCoolTime = 0;
	m_State = STATE_NORMAL;
	m_nStateCount = 0;
	m_ReSpownPos = D3DXVECTOR3(0.0f, 350.0f, 0.0f);
	m_GameEnd = false;
	m_pLifeGauge = nullptr;
	m_pLifeGaugeBG = nullptr;
	m_fLife = PLAYER_LIFE;
	m_fLifeMax = m_fLife;
	m_AtkPos = INITVECTOR3;
	m_bRight = true;
	CameraDiffMove = false;
	CameraDiffTime = 0;
	m_pShadow = nullptr;
	m_nBossDamageCount = 0;
	m_fDamage = 0;

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_pLifeNumber[nCnt] = nullptr;
	}
}

//====================================================================
//�f�X�g���N�^
//====================================================================
CPlayer::~CPlayer()
{

}

//====================================================================
//��������
//====================================================================
CPlayer* CPlayer::Create()
{
	CPlayer* pPlayer = NULL;

	if (pPlayer == NULL)
	{
		//�v���C���[�̐���
		pPlayer = new CPlayer();
	}

	//�I�u�W�F�N�g�̏���������
	if (FAILED(pPlayer->Init()))
	{//���������������s�����ꍇ
		return NULL;
	}

	return pPlayer;
}

//====================================================================
//����������
//====================================================================
HRESULT CPlayer::Init(void)
{
	//���f���̐���
	LoadLevelData("data\\TXT\\motion_player.txt");

	//���[�V�����̐���
	if (m_pMotion == NULL)
	{
		//���[�V�����̐���
		m_pMotion = new CMotion;
	}

	//����������
	m_pMotion->SetModel(&m_apModel[0], m_nNumModel);
	m_pMotion->LoadData("data\\TXT\\motion_player.txt");

	//��ސݒ�
	SetType(CObject::TYPE_PLAYER3D);

	switch (CScene::GetMode())
	{
	case CScene::MODE_TITLE:
		m_pMotion->Set(ACTION_TITLE, 0);
		break;

	case CScene::MODE_GAME:
		//�������ێ�����I�u�W�F�N�g�̐���
		MyObjCreate();

		//���C�t�̕����ݒ�
		SetLifeUI();
		break;

	case CScene::MODE_RESULT:
		break;
	}

	return S_OK;
}

//====================================================================
//�������ێ�����I�u�W�F�N�g�̐���
//====================================================================
void CPlayer::MyObjCreate(void)
{
	//���C�t�Q�[�W�̐���
	if (m_pLifeGaugeBG == nullptr)
	{
		m_pLifeGaugeBG = CObjGauge2D::Create();
		m_pLifeGaugeBG->SetPos(D3DXVECTOR3(1000.0f, 500.0f, 0.0f));
		m_pLifeGaugeBG->SetWight(250.0f);
		m_pLifeGaugeBG->SetHeight(10.0f);
		m_pLifeGaugeBG->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));
		m_pLifeGaugeBG->SetGaugeWight(m_fLifeMax, m_fLife);
	}

	//���C�t�Q�[�W�̐���
	if (m_pLifeGauge == nullptr)
	{
		m_pLifeGauge = CObjGauge2D::Create();
		m_pLifeGauge->SetPos(D3DXVECTOR3(1000.0f, 500.0f, 0.0f));
		m_pLifeGauge->SetWight(250.0f);
		m_pLifeGauge->SetHeight(10.0f);
		m_pLifeGauge->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		m_pLifeGauge->SetGaugeWight(m_fLifeMax, m_fLife);
	}

	//�e�̐���
	if (m_pShadow == nullptr)
	{
		m_pShadow = CObject3D::Create();
		m_pShadow->SetPos(m_pos);
		m_pShadow->SetRot(D3DXVECTOR3(D3DX_PI * 0.5f, m_rot.y, 0.0f));
		m_pShadow->SetColor(D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
		m_pShadow->SetTexture("data\\TEXTURE\\Effect000.jpg");
		m_pShadow->SetAddDorw(true);
	}

	//���C�t�p����UI�̐���
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_pLifeNumber[nCnt] = CNumber::Create();
		m_pLifeNumber[nCnt]->SetPos(D3DXVECTOR3(1200.0f + nCnt * 15.0f, 530.0f, 0.0f));
		m_pLifeNumber[nCnt]->SetWight(20.0f);
		m_pLifeNumber[nCnt]->SetHeight(20.0f);
	}
}

//====================================================================
//�I������
//====================================================================
void CPlayer::Uninit(void)
{
	for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		m_apModel[nCntModel]->Uninit();
		delete m_apModel[nCntModel];
		m_apModel[nCntModel] = NULL;
	}

	//���[�V�����̏I������
	if (m_pMotion != NULL)
	{
		//���[�V�����̔j��
		delete m_pMotion;
		m_pMotion = NULL;
	}

	SetDeathFlag(true);
}

//====================================================================
//�X�V����
//====================================================================
void CPlayer::Update(void)
{
	switch (CScene::GetMode())
	{
	case CScene::MODE_TITLE:
		TitleUpdate();
		break;
	case CScene::MODE_GAME:

		if (CGame::GetEvent() == false)
		{
			GameUpdate();
		}

		break;
	case CScene::MODE_RESULT:
		break;
	}
}

//====================================================================
//�^�C�g���ł̍X�V����
//====================================================================
void CPlayer::TitleUpdate(void)
{
	//���[�V�����̍X�V
	m_pMotion->Update();
}

//====================================================================
//�Q�[���ł̍X�V����
//====================================================================
void CPlayer::GameUpdate(void)
{
	if (m_State != STATE_DEATH && m_State != STATE_REVIVAL)
	{
		//�L�[�{�[�h�̎擾
		CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

		//�ߋ��̈ʒu���L�^����
		m_posOld = m_pos;

		//�����蔻���L���ɂ���
		m_bHit = false;

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

		if (CManager::GetInstance()->GetCamera()->GetCameraMode() == CCamera::CAMERAMODE_SIDEVIEW)
		{
			m_pos.z = 0.0f;

			//�ړ�����
			Move2D();

			//�ړ���������
			Rot2D();

			//�������
			Dodge2D();
		}
		else
		{
			//�ړ�����
			Move();

			//�ړ���������
			Rot();

			//�������
			Dodge();
		}

		//�U������
		Attack();

		if (m_nAttackCount > 0)
		{
			AttackCollision();
		}

		//�W�����v����
		Jump();

		//�s���s�\���Ԃ̃J�E���g
		m_nActionNotCount--;

		//�����W��
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

		//�����蔻��̏���
		if (m_State == STATE_NORMAL)
		{
			if (m_nDodgeCount <= 0)
			{
				CollisionDamageCube(m_pos);
				CollisionBoss();

				if (CGame::GetEventEnd() == false)
				{
					CollisionBossEvent();
				}
			}
		}

		//�e�̍X�V
		CollisionShadow();

		//�J�����ʒu�̍X�V
		m_CameraPos.x = m_pos.x;
		m_CameraPos.z = m_pos.z;
		if (m_bJump == false)
		{
			if (m_CameraPos.y > m_pos.y + 50.0f ||
				m_CameraPos.y < m_pos.y - 50.0f)
			{
				CameraDiffMove = true;
				CameraDiffTime = 30;
			}
			m_CameraPos.y = m_pos.y;
		}

		//�J�����̕␳�ݒ�
		CameraDiff();

		//��ʊO����
		if (m_pos.y < 0.0f)
		{
			FallDamage();
		}
	}

	//���[�V�����̊Ǘ�
	ActionState();

	//��Ԃ̊Ǘ�
	StateManager();

	//���[�V�����̍X�V
	m_pMotion->Update();

	//�f�o�b�O�\���̎擾
	CDebugProc* pDebugProc = CManager::GetInstance()->GetDebugProc();
	pDebugProc->Print("%f:%f:%f\n", GetPos().x, GetPos().y, GetPos().z);
}

//====================================================================
//���C�tUI�̍X�V
//====================================================================
void CPlayer::SetLifeUI(void)
{
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		if (m_pLifeNumber[nCnt] == nullptr)
		{
			return;
		}
	}

	m_pLifeNumber[0]->SetNumber((int)m_fLife % 10000 / 1000);
	m_pLifeNumber[1]->SetNumber((int)m_fLife % 1000 / 100);
	m_pLifeNumber[2]->SetNumber((int)m_fLife % 100 / 10);
	m_pLifeNumber[3]->SetNumber((int)m_fLife % 10 / 1);
}

//====================================================================
//��ԊǗ�
//====================================================================
void CPlayer::StateManager(void)
{
	switch (m_State)
	{
	case STATE_NORMAL:
		break;

	case STATE_DEATH:
		m_pos.y += 1.0f;

		if (m_nStateCount <= 0)
		{
			m_State = STATE_REVIVAL;
			m_nStateCount = 60;
			m_pos = D3DXVECTOR3(m_ReSpownPos.x, 110.0f, m_ReSpownPos.z);
			m_CameraPos = m_pos;

			m_fLife = PLAYER_LIFE;
			SetLifeUI();

			if (m_pLifeGauge != nullptr)
			{
				m_pLifeGauge->SetGaugeWight(m_fLifeMax, m_fLife);
			}

			for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
			{
				m_apModel[nCnt]->SetColorChange(true);
				m_apModel[nCnt]->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
			}

			CCubeEffect* pCEffect = CCubeEffect::Create();
			pCEffect->SetPos(D3DXVECTOR3(m_ReSpownPos.x, 110.0f + 400.0f, m_ReSpownPos.z));
			pCEffect->SetSize(D3DXVECTOR3(30.0f, 400.0f, 30.0f));
			pCEffect->SetColor(D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.5));
			pCEffect->SetLife(60);

			pCEffect = CCubeEffect::Create();
			pCEffect->SetPos(D3DXVECTOR3(m_ReSpownPos.x, 110.0f + 1200.0f, m_ReSpownPos.z));
			pCEffect->SetMove(D3DXVECTOR3(0.0f, -1200.0f / 60.0f, 0.0f));
			pCEffect->SetSize(D3DXVECTOR3(31.0f, 30.0f, 31.0f));
			pCEffect->SetColor(D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
			pCEffect->SetLife(60);
		}
		break;

	case STATE_REVIVAL:

		if (m_nStateCount <= 0)
		{
			m_State = STATE_WAIT;
			m_nStateCount = WAIT_TIME + WAIT_TIME;

			for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
			{
				m_apModel[nCnt]->SetColorChange(true);
				m_apModel[nCnt]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

				int a = 3;
				for (int nCntX = -a; nCntX <= a; nCntX++)
				{
					for (int nCntZ = -a; nCntZ <= a; nCntZ++)
					{
						CCubeEffect* pCEffect = CCubeEffect::Create();
						pCEffect->SetPos(D3DXVECTOR3(GetPos().x + (10.0f * nCntX), 110.0f, GetPos().z + (10.0f * nCntZ)));
						pCEffect->SetMove(D3DXVECTOR3((1.0f * nCntX), 0.0f, (1.0f * nCntZ)));
						pCEffect->SetSize(D3DXVECTOR3(5.0f, 5.0f, 5.0f));
						pCEffect->SetColor(D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
						pCEffect->SetDel(0.08f);
					}
				}
			}
		}
		break;

	case STATE_WAIT:
		if (m_nStateCount <= 0)
		{
			m_State = STATE_NORMAL;
			m_nStateCount = 0;

			for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
			{
				m_apModel[nCnt]->SetColorChange(false);
			}
		}
		break;

	case STATE_DAMAGE:
		if (m_nStateCount <= 0)
		{
			m_State = STATE_WAIT;
			m_nStateCount = WAIT_TIME;

			for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
			{
				m_apModel[nCnt]->SetColorChange(true);
				m_apModel[nCnt]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			}
		}
		break;
	}

	if (m_nStateCount > 0)
	{
		m_nStateCount--;
	}
}

//====================================================================
//�ړ�����
//====================================================================
void CPlayer::Move2D(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputJoypad* pInputJoypad = CManager::GetInstance()->GetInputJoyPad();
	D3DXVECTOR3 CameraRot = CManager::GetInstance()->GetCamera()->GetRot();

	D3DXVECTOR3 NormarizeMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�L�[�{�[�h�̈ړ�����
	if (pInputKeyboard->GetPress(DIK_A) == true)
	{
		NormarizeMove.x += -1.0f * cosf(CameraRot.y) * PLAYER_SPEED;

	}
	if (pInputKeyboard->GetPress(DIK_D) == true)
	{
		NormarizeMove.x += 1.0f * cosf(CameraRot.y) * PLAYER_SPEED;
	}

	if (pInputKeyboard->GetPress(DIK_A) == false && pInputKeyboard->GetPress(DIK_D) == false)
	{
		//���X�e�B�b�N�ɂ�鍶�E�ړ�
		m_move.x += pInputJoypad->Get_Stick_Left(0).x * cosf(CameraRot.y) * PLAYER_SPEED;
	}

	if (pInputKeyboard->GetPress(DIK_A) == true || pInputKeyboard->GetPress(DIK_D) == true)
	{
		float JunpPawer = NormarizeMove.y;
		NormarizeMove.y = 0.0f;

		D3DXVec3Normalize(&NormarizeMove, &NormarizeMove);

		NormarizeMove.x *= PLAYER_SPEED;
		NormarizeMove.y = JunpPawer;
		NormarizeMove.z *= PLAYER_SPEED;
	}

	m_move += NormarizeMove;

}

//====================================================================
//�ړ���������
//====================================================================
void CPlayer::Rot2D(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputJoypad* pInputJoypad = CManager::GetInstance()->GetInputJoyPad();
	D3DXVECTOR3 CameraRot = CManager::GetInstance()->GetCamera()->GetRot();

	//�ړ������Ɍ��������킹�鏈��
	float fRotMove, fRotDest, fRotDiff;

	fRotMove = m_rot.y;
	fRotDest = CManager::GetInstance()->GetCamera()->GetRot().y;

	if (pInputKeyboard->GetPress(DIK_D) == true || pInputJoypad->Get_Stick_Left(0).x > 0.1f)
	{
		fRotMove = atan2f(sinf(m_rot.y), cosf(m_rot.y));
		fRotDest = atan2f(sinf(CameraRot.y), cosf(CameraRot.y)) + D3DX_PI * -0.5f;
	}
	else if (pInputKeyboard->GetPress(DIK_A) == true || pInputJoypad->Get_Stick_Left(0).x < -0.1f)
	{
		fRotMove = atan2f(sinf(m_rot.y), cosf(m_rot.y));
		fRotDest = atan2f(sinf(CameraRot.y), cosf(CameraRot.y)) + D3DX_PI * 0.5f;
	}

	fRotDiff = fRotDest - fRotMove;

	if (fRotDiff > D3DX_PI * 1.0f)
	{
		fRotDiff -= D3DX_PI * 2.0f;
	}
	else if (fRotDiff < -D3DX_PI * 1.0f)
	{
		fRotDiff += D3DX_PI * 2.0f;
	}

	fRotMove += fRotDiff * PLAYER_ROT_SPEED;

	if (fRotMove > D3DX_PI * 1.0f)
	{
		fRotMove -= D3DX_PI * 2.0f;
	}
	else if (fRotMove < -D3DX_PI * 1.0f)
	{
		fRotMove += D3DX_PI * 2.0f;
	}

	if (m_nAttackChainFrame <= 0 && m_nAttackCount <= 0)
	{
		if (pInputKeyboard->GetPress(DIK_A) == true || pInputKeyboard->GetPress(DIK_D) == true || pInputJoypad->Get_Stick_Left(0).x != 0.0f)
		{
			m_rot.y = fRotMove;
		}
	}

	if (m_move.x > 0.1f)
	{
		m_bRight = true;
	}
	else if (m_move.x < -0.1f)
	{
		m_bRight = false;
	}
}

//====================================================================
//�������
//====================================================================
void CPlayer::Dodge2D(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputJoypad* pInputJoypad = CManager::GetInstance()->GetInputJoyPad();
	CInputMouse* pInputMouse = CManager::GetInstance()->GetInputMouse();

	if (
		(pInputKeyboard->GetTrigger(DIK_N) == true ||
			pInputJoypad->GetTrigger(CInputJoypad::BUTTON_R, 0) == true ||
			pInputMouse->GetTrigger(CInputMouse::PUSH_RIGHT) == true) &&
		m_nDodgeCoolTime <= 0
		)
	{
		//�Q�[����SE���Đ�����
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_DODGE);

		m_nDodgeCount = DODGE_FRAME;
		m_nDodgeCoolTime = DODGE_COOL;
	}

	if (m_nDodgeCount > 0)
	{
		if (m_nDodgeCount % DODGE_EFFECTINTERVAL == 0)
		{
			CPlayerEffect* pPlayerEffect = CPlayerEffect::Create();
			pPlayerEffect->SetPos(m_pos);
			pPlayerEffect->SetRot(m_rot);
			pPlayerEffect->SetAllPose(m_pMotion->GetType(), m_pMotion->GetKey(), m_pMotion->GetCounter());
		}

		if (m_bRight == true)
		{
			m_move.x = DODGE_SPEED;
		}
		else
		{
			m_move.x = -DODGE_SPEED;
		}
		m_move.y = 0.0f;
		m_Objmove.y = 0.0f;

		m_nDodgeCount--;
	}
	else
	{
		if (m_nDodgeCoolTime > 0)
		{
			m_nDodgeCoolTime--;
		}
	}
}

//====================================================================
//�ړ�����
//====================================================================
void CPlayer::Move(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputJoypad* pInputJoypad = CManager::GetInstance()->GetInputJoyPad();
	D3DXVECTOR3 CameraRot = CManager::GetInstance()->GetCamera()->GetRot();

	D3DXVECTOR3 NormarizeMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�L�[�{�[�h�̈ړ�����
	if (pInputKeyboard->GetPress(DIK_B) == true)
	{
		CPlayerEffect* pPlayerEffect = CPlayerEffect::Create();
		pPlayerEffect->SetPos(m_pos);
		pPlayerEffect->SetRot(m_rot);
		pPlayerEffect->SetAllPose(m_pMotion->GetType(), m_pMotion->GetKey(), m_pMotion->GetCounter());
	}

	//�L�[�{�[�h�̈ړ�����
	if (pInputKeyboard->GetPress(DIK_V) == true)
	{
		CPlayerEffect* pPlayerEffect = CPlayerEffect::Create();
		pPlayerEffect->SetPos(m_pos);
		pPlayerEffect->SetRot(m_rot);
		pPlayerEffect->SetPose(m_pMotion->GetType(), m_pMotion->GetKey(), m_pMotion->GetCounter(), 2);
	}

	if (pInputKeyboard->GetPress(DIK_8) == true)
	{
		m_fLife -= 1.0f;

		if (m_pLifeGauge != nullptr)
		{
			m_pLifeGauge->SetGaugeWight(m_fLifeMax, m_fLife);
		}
	}

	if (pInputKeyboard->GetPress(DIK_9) == true)
	{
		m_fLife += 1.0f;

		if (m_pLifeGauge != nullptr)
		{
			m_pLifeGauge->SetGaugeWight(m_fLifeMax, m_fLife);
		}
	}

	//�L�[�{�[�h�̈ړ�����
	if (pInputKeyboard->GetPress(DIK_W) == true)
	{
		NormarizeMove.z += 1.0f * cosf(CameraRot.y) * PLAYER_SPEED;
		NormarizeMove.x += 1.0f * sinf(CameraRot.y) * PLAYER_SPEED;

	}
	if (pInputKeyboard->GetPress(DIK_S) == true)
	{
		NormarizeMove.z += -1.0f * cosf(CameraRot.y) * PLAYER_SPEED;
		NormarizeMove.x += -1.0f * sinf(CameraRot.y) * PLAYER_SPEED;
	}
	if (pInputKeyboard->GetPress(DIK_A) == true)
	{
		NormarizeMove.x += -1.0f * cosf(CameraRot.y) * PLAYER_SPEED;
		NormarizeMove.z -= -1.0f * sinf(CameraRot.y) * PLAYER_SPEED;

	}
	if (pInputKeyboard->GetPress(DIK_D) == true)
	{
		NormarizeMove.x += 1.0f * cosf(CameraRot.y) * PLAYER_SPEED;
		NormarizeMove.z -= 1.0f * sinf(CameraRot.y) * PLAYER_SPEED;
	}

	if (pInputKeyboard->GetPress(DIK_W) == false && pInputKeyboard->GetPress(DIK_A) == false && pInputKeyboard->GetPress(DIK_S) == false && pInputKeyboard->GetPress(DIK_D) == false)
	{
		//���X�e�B�b�N�ɂ��O��ړ�	
		m_move.z += pInputJoypad->Get_Stick_Left(0).y * cosf(CameraRot.y) * PLAYER_SPEED;
		m_move.x += pInputJoypad->Get_Stick_Left(0).y * sinf(CameraRot.y) * PLAYER_SPEED;

		//���X�e�B�b�N�ɂ�鍶�E�ړ�
		m_move.x += pInputJoypad->Get_Stick_Left(0).x * cosf(CameraRot.y) * PLAYER_SPEED;
		m_move.z -= pInputJoypad->Get_Stick_Left(0).x * sinf(CameraRot.y) * PLAYER_SPEED;
	}

	if (pInputKeyboard->GetPress(DIK_W) == true || pInputKeyboard->GetPress(DIK_A) == true || pInputKeyboard->GetPress(DIK_S) == true || pInputKeyboard->GetPress(DIK_D) == true)
	{
		float JunpPawer = NormarizeMove.y;
		NormarizeMove.y = 0.0f;

		D3DXVec3Normalize(&NormarizeMove, &NormarizeMove);

		NormarizeMove.x *= PLAYER_SPEED;
		NormarizeMove.y = JunpPawer;
		NormarizeMove.z *= PLAYER_SPEED;
	}

	m_move += NormarizeMove;

}

//====================================================================
//�ړ���������
//====================================================================
void CPlayer::Rot(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputJoypad* pInputJoypad = CManager::GetInstance()->GetInputJoyPad();
	D3DXVECTOR3 CameraRot = CManager::GetInstance()->GetCamera()->GetRot();

	//�ړ������Ɍ��������킹�鏈��
	float fRotMove, fRotDest, fRotDiff;

	fRotMove = m_rot.y;
	fRotDest = CManager::GetInstance()->GetCamera()->GetRot().y;

	if (pInputKeyboard->GetPress(DIK_E) == true)
	{
		m_rot.y += 0.1f;
	}
	if (pInputKeyboard->GetPress(DIK_Q) == true)
	{
		m_rot.y -= 0.1f;
	}

	if (pInputKeyboard->GetPress(DIK_W) == true || pInputJoypad->Get_Stick_Left(0).y > 0.1f)
	{
		if (pInputKeyboard->GetPress(DIK_D) == true || pInputJoypad->Get_Stick_Left(0).x > 0.1f)
		{
			fRotMove = atan2f(sinf(m_rot.y), cosf(m_rot.y));
			fRotDest = atan2f(sinf(CameraRot.y), cosf(CameraRot.y)) + D3DX_PI * -0.75f;
		}
		else if (pInputKeyboard->GetPress(DIK_A) == true || pInputJoypad->Get_Stick_Left(0).x < -0.1f)
		{
			fRotMove = atan2f(sinf(m_rot.y), cosf(m_rot.y));
			fRotDest = atan2f(sinf(CameraRot.y), cosf(CameraRot.y)) + D3DX_PI * 0.75f;
		}
		else
		{
			fRotMove = atan2f(sinf(m_rot.y), cosf(m_rot.y));
			fRotDest = atan2f(sinf(CameraRot.y), cosf(CameraRot.y)) + D3DX_PI;
		}
	}
	else if (pInputKeyboard->GetPress(DIK_S) == true || pInputJoypad->Get_Stick_Left(0).y < -0.1f)
	{
		if (pInputKeyboard->GetPress(DIK_D) == true || pInputJoypad->Get_Stick_Left(0).x > 0.1f)
		{
			fRotMove = atan2f(sinf(m_rot.y), cosf(m_rot.y));
			fRotDest = atan2f(sinf(CameraRot.y), cosf(CameraRot.y)) + D3DX_PI * -0.25f;
		}
		else if (pInputKeyboard->GetPress(DIK_A) == true || pInputJoypad->Get_Stick_Left(0).x < -0.1f)
		{
			fRotMove = atan2f(sinf(m_rot.y), cosf(m_rot.y));
			fRotDest = atan2f(sinf(CameraRot.y), cosf(CameraRot.y)) + D3DX_PI * 0.25f;
		}
		else
		{
			fRotMove = atan2f(sinf(m_rot.y), cosf(m_rot.y));
			fRotDest = atan2f(sinf(CameraRot.y), cosf(CameraRot.y));
		}
	}
	else if (pInputKeyboard->GetPress(DIK_D) == true || pInputJoypad->Get_Stick_Left(0).x > 0.1f)
	{
		fRotMove = atan2f(sinf(m_rot.y), cosf(m_rot.y));
		fRotDest = atan2f(sinf(CameraRot.y), cosf(CameraRot.y)) + D3DX_PI * -0.5f;
	}
	else if (pInputKeyboard->GetPress(DIK_A) == true || pInputJoypad->Get_Stick_Left(0).x < -0.1f)
	{
		fRotMove = atan2f(sinf(m_rot.y), cosf(m_rot.y));
		fRotDest = atan2f(sinf(CameraRot.y), cosf(CameraRot.y)) + D3DX_PI * 0.5f;
	}

	////���X�e�B�b�N�ɂ��O��ړ�	
	//m_move.z += pInputJoypad->Get_Stick_Left(0).y * cosf(CameraRot.y) * PLAYER_SPEED;
	//m_move.x += pInputJoypad->Get_Stick_Left(0).y * sinf(CameraRot.y) * PLAYER_SPEED;

	////���X�e�B�b�N�ɂ�鍶�E�ړ�
	//m_move.x += pInputJoypad->Get_Stick_Left(0).x * cosf(CameraRot.y) * PLAYER_SPEED;
	//m_move.z -= pInputJoypad->Get_Stick_Left(0).x * sinf(CameraRot.y) * PLAYER_SPEED;

	//fRotMove = atan2f(sinf(m_rot.y), cosf(m_rot.y));
	//fRotDest = atan2f(sinf(CameraRot.y), cosf(CameraRot.y) + D3DX_PI * pInputJoypad->Get_Stick_Left(0).x);

	fRotDiff = fRotDest - fRotMove;

	if (fRotDiff > D3DX_PI * 1.0f)
	{
		fRotDiff -= D3DX_PI * 2.0f;
	}
	else if (fRotDiff < -D3DX_PI * 1.0f)
	{
		fRotDiff += D3DX_PI * 2.0f;
	}

	fRotMove += fRotDiff * PLAYER_ROT_SPEED;

	if (fRotMove > D3DX_PI * 1.0f)
	{
		fRotMove -= D3DX_PI * 2.0f;
	}
	else if (fRotMove < -D3DX_PI * 1.0f)
	{
		fRotMove += D3DX_PI * 2.0f;
	}

	if (m_nAttackChainFrame <= 0 && m_nAttackCount <= 0)
	{
		if (pInputKeyboard->GetPress(DIK_W) == true || pInputKeyboard->GetPress(DIK_A) == true || pInputKeyboard->GetPress(DIK_S) == true || pInputKeyboard->GetPress(DIK_D) == true || pInputJoypad->Get_Stick_Left(0).y != 0.0f || pInputJoypad->Get_Stick_Left(0).x != 0.0f)
		{
			m_rot.y = fRotMove;
		}
	}
}

//====================================================================
//�������
//====================================================================
void CPlayer::Dodge(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputJoypad* pInputJoypad = CManager::GetInstance()->GetInputJoyPad();
	CInputMouse* pInputMouse = CManager::GetInstance()->GetInputMouse();

	if (
		(pInputKeyboard->GetTrigger(DIK_N) == true ||
			pInputJoypad->GetTrigger(CInputJoypad::BUTTON_R, 0) == true ||
			pInputMouse->GetTrigger(CInputMouse::PUSH_RIGHT) == true) &&
		m_nDodgeCoolTime <= 0
		)
	{
		m_nDodgeCount = DODGE_FRAME;
		m_nDodgeCoolTime = DODGE_COOL;

		//�Q�[����SE���Đ�����
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_DODGE);
	}

	if (m_nDodgeCount > 0)
	{
		if (m_nDodgeCount % DODGE_EFFECTINTERVAL == 0)
		{
			CPlayerEffect* pPlayerEffect = CPlayerEffect::Create();
			pPlayerEffect->SetPos(m_pos);
			pPlayerEffect->SetRot(m_rot);
			pPlayerEffect->SetAllPose(m_pMotion->GetType(), m_pMotion->GetKey(), m_pMotion->GetCounter());
		}

		m_move.x = sinf(m_rot.y + D3DX_PI) * DODGE_SPEED;
		m_move.z = cosf(m_rot.y + D3DX_PI) * DODGE_SPEED;
		m_move.y = 0.0f;
		m_Objmove.y = 0.0f;

		m_nDodgeCount--;
	}
	else
	{
		if (m_nDodgeCoolTime > 0)
		{
			m_nDodgeCoolTime--;
		}
	}
}

//====================================================================
//�W�����v����
//====================================================================
void CPlayer::Jump(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputJoypad* pInputJoypad = CManager::GetInstance()->GetInputJoyPad();

	if (
		(pInputKeyboard->GetTrigger(DIK_SPACE) == true ||
			pInputJoypad->GetTrigger(CInputJoypad::BUTTON_B, 0) == true) &&
		m_bJump == false)
	{//�W�����v�g�p��Ԃ���Ȃ����ɃW�����v�{�^�����������Ƃ�

		//�Q�[����SE���Đ�����
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_JUMP);

		m_move.y = 20.0f;
		m_bJump = true;

		//�W�����v����͍U���Ȃǂ̃A�N�V�������s���Ȃ�
		m_nActionNotCount = JAMP_ACTIONNOT;
	}
}

//====================================================================
//�U������
//====================================================================
void CPlayer::Attack(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputJoypad* pInputJoypad = CManager::GetInstance()->GetInputJoyPad();
	CInputMouse* pInputMouse = CManager::GetInstance()->GetInputMouse();

	if (
		(pInputKeyboard->GetTrigger(DIK_RETURN) == true ||
			pInputJoypad->GetTrigger(CInputJoypad::BUTTON_A, 0) == true ||
			pInputMouse->GetTrigger(CInputMouse::PUSH_LEFT) == true) &&
		m_nAttackCount <= 0
		)
	{//�U��������Ȃ����ɃW�����v�{�^�����������Ƃ�

		if (m_bJump == true)
		{//�󒆂ɂ��鎞
			if (m_bAirAttack == false)
			{//�󒆍U�����s���Ă��Ȃ��Ƃ�

				//�Q�[����SE���Đ�����
				CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_ATTACK_SKY);

				//�U�����[�V����
				if (m_Action != ACTION_SKYATTACK)
				{
					m_Action = ACTION_SKYATTACK;
					m_pMotion->Set(ACTION_SKYATTACK, 3);
					m_bAirAttack = true;

					m_nAttackCount = 20;
					m_nAttackDamage = SKY_ATTACK_DAMAGE + (rand() % (int)SKY_ATTACK_DAMAGE) * 0.1f;
					m_nAttackCountMax = m_nAttackCount;
					m_nAttackChainFrame = 1;

					if (m_move.y <= 10.0f)
					{
						m_move.y = 10.0f;
					}
				}
			}
		}
		else
		{//�n��ɂ��鎞

			//�Q�[����SE���Đ�����
			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_ATTACK_NORMAL);

			switch (m_AtkAction)
			{
			default:
				//�U�����[�V����
				if (m_Action != ACTION_ATTACK1)
				{
					m_Action = ACTION_ATTACK1;
					m_pMotion->Set(ACTION_ATTACK1, 3);
					m_AtkAction = ACTION_ATTACK1;

					m_nAttackDamage = ATTACK1_DAMAGE + (rand() % (int)ATTACK1_DAMAGE) * 0.1f;
					m_nAttackCount = 20;
					m_nAttackCountMax = m_nAttackCount;
					m_nAttackChainFrame = 30;
				}

				break;

			case ACTION_ATTACK1:

				//�U�����[�V����
				if (m_Action != ACTION_ATTACK2)
				{
					m_Action = ACTION_ATTACK2;
					m_pMotion->Set(ACTION_ATTACK2, 3);
					m_AtkAction = ACTION_ATTACK2;

					m_nAttackDamage = ATTACK2_DAMAGE + (rand() % (int)ATTACK2_DAMAGE) * 0.1f;
					m_nAttackCount = 20;
					m_nAttackCountMax = m_nAttackCount;
					m_nAttackChainFrame = 30;
				}

				break;

			case ACTION_ATTACK2:

				//�U�����[�V����
				if (m_Action != ACTION_ATTACK3)
				{
					m_Action = ACTION_ATTACK3;
					m_pMotion->Set(ACTION_ATTACK3, 3);
					m_AtkAction = ACTION_WAIT;

					m_nAttackDamage = ATTACK3_DAMAGE + (rand() % (int)ATTACK3_DAMAGE) * 0.1f;
					m_nAttackCount = 40;
					m_nAttackCountMax = m_nAttackCount;
					m_nAttackChainFrame = 0;
				}

				break;
			}
		}

		////SE
		//CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_PLAYER_JUMP);

		//�W�����v����͍U���Ȃǂ̃A�N�V�������s���Ȃ�
		m_nActionNotCount = JAMP_ACTIONNOT;

		m_nAttackHit = false;
	}

	if (m_bJump == false)
	{
		m_bAirAttack = false;
	}

	if (m_nAttackCount > 0)
	{
		m_nAttackCount--;
	}
	else
	{
		if (m_nAttackChainFrame > 0)
		{
			m_nAttackChainFrame--;
		}
		else
		{
			m_AtkAction = ACTION_WAIT;
		}
	}

	//�U���ʒu�̐ݒ�
	m_AtkPos = m_apModel[3]->GetWorldPos();

	if (m_nAttackCount > 0)
	{
		CPlayerEffect* pPlayerEffect = CPlayerEffect::Create();
		pPlayerEffect->SetPos(m_pos);
		pPlayerEffect->SetRot(m_rot);
		pPlayerEffect->SetColor(D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
		pPlayerEffect->SetDel(0.05f);
		pPlayerEffect->SetPose(m_pMotion->GetType(), m_pMotion->GetKey(), m_pMotion->GetCounter(), 2);
	}
	else if (m_nAttackChainFrame > 0)
	{
		CPlayerEffect* pPlayerEffect = CPlayerEffect::Create();
		pPlayerEffect->SetPos(m_pos);
		pPlayerEffect->SetRot(m_rot);
		pPlayerEffect->SetColor(D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
		pPlayerEffect->SetDel(0.4f);
		pPlayerEffect->SetPose(m_pMotion->GetType(), m_pMotion->GetKey(), m_pMotion->GetCounter(), 2);
	}
}

//====================================================================
//�U�����菈��
//====================================================================
void CPlayer::AttackCollision(void)
{
	if (m_nAttackHit == false)
	{
		for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
		{
			//�I�u�W�F�N�g���擾
			CObject* pObj = CObject::GetTop(nCntPriority);

			while (pObj != NULL)
			{
				CObject* pObjNext = pObj->GetNext();

				CObject::TYPE type = pObj->GetType();			//��ނ��擾

				if (type == TYPE_BOSS)
				{//��ނ��{�X�̎�

					CBoss* pBoss = (CBoss*)pObj;

					if (pBoss->GetState() == CBoss::STATE_NORMAL)
					{
						if (CollisionCircle(m_AtkPos, pObj->GetPos(), 100.0f) == true)
						{
							pObj->HitDamage(m_nAttackDamage);
							m_nAttackHit = true;

							for (int nCnt = 0; nCnt < 3; nCnt++)
							{
								CNumberFall* pNumber = CNumberFall::Create();
								pNumber->SetDigit(nCnt);
								pNumber->SetPos(D3DXVECTOR3(
									pObj->GetPos().x,
									pObj->GetPos().y,
									pObj->GetPos().z));
								switch (nCnt)
								{
								case 0:
									pNumber->SetNumber((int)m_nAttackDamage % 1000 / 100);
									break;
								case 1:
									pNumber->SetNumber((int)m_nAttackDamage % 100 / 10);
									break;
								case 2:
									pNumber->SetNumber((int)m_nAttackDamage % 10 / 1);
									break;
								}
							}
						}
					}
				}
				else if (type == TYPE_ENEMY3D)
				{//��ނ��{�X�̎�

					if (CollisionCircle(m_AtkPos, pObj->GetPos(), 100.0f) == true)
					{
						pObj->HitDamage(m_nAttackDamage);
					}
				}

				pObj = pObjNext;
			}
		}
	}
}

//====================================================================
//�~�̓����蔻��
//====================================================================
bool CPlayer::CollisionCircle(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float nRadiusOut)
{
	bool nHit = false;

	if (sqrtf((pos1.x - pos2.x) * (pos1.x - pos2.x)
		+ (pos1.y - pos2.y) * (pos1.y - pos2.y)) <= nRadiusOut)
	{//�~�̔��肪��������
		if (sqrtf((pos1.x - pos2.x) * (pos1.x - pos2.x)
			+ (pos1.z - pos2.z) * (pos1.z - pos2.z)) <= nRadiusOut)
		{//�~�̔��肪��������
			nHit = true;
		}
	}

	return nHit;
}

//====================================================================
//�U�����󂯂����̏���
//====================================================================
void CPlayer::FallDamage(void)
{
	HitDamage(FALL_DAMAGE);
	CEffect* pEffect = CEffect::Create();
	pEffect->SetPos(m_pos);
	pEffect->SetRadius(500.0f);
	pEffect->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
}

//====================================================================
//�U�����󂯂����̏���
//====================================================================
void CPlayer::HitDamage(float Damage)
{
	if (m_State == STATE_NORMAL)
	{
		m_State = STATE_DAMAGE;
		m_nStateCount = DAMAGE_TIME;
		m_Action = ACTION_WAIT;
		m_nAttackCount = 0;
		m_pMotion->Set(ACTION_WAIT, 5);
		m_fLife -= Damage;
		m_fDamage += Damage;

		int a = 2;
		for (int nCntX = -a; nCntX <= a; nCntX++)
		{
			for (int nCntY = -a; nCntY <= a; nCntY++)
			{
				for (int nCntZ = -a; nCntZ <= a; nCntZ++)
				{
					CCubeEffect* pCEffect = CCubeEffect::Create();
					pCEffect->SetPos(D3DXVECTOR3(GetPos().x + (10.0f * nCntX), GetPos().y + (10.0f * nCntY), GetPos().z + (10.0f * nCntZ)));
					pCEffect->SetMove(D3DXVECTOR3((4.0f * nCntX), (4.0f * nCntY), (4.0f * nCntZ)));
					pCEffect->SetSize(D3DXVECTOR3(2.5f, 2.5f, 2.5f));
					pCEffect->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
					pCEffect->SetDel(0.08f);
				}
			}
		}

		//�J���[�ݒ�
		for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
		{
			m_apModel[nCnt]->SetColorChange(true);
			m_apModel[nCnt]->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}

		//�������Ɏ��S���Ă��Ȃ�������X�e�[�W�ɖ߂�
		if (m_pos.y < 0.0f)
		{
			if (m_fLife > 0)
			{
				m_pos = D3DXVECTOR3(m_ReSpownPos.x, m_ReSpownPos.y + -100.0f, m_ReSpownPos.z);
			}
		}

		if (m_fLife > 0)
		{
			//�Q�[����SE���Đ�����
			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_DAMAGE_PLAYER);
		}
		else
		{
			m_fLife = 0.0f;

			m_State = STATE_DEATH;
			m_nStateCount = REVIVAL_TIME;
			CCubeEffect* pEffect = CCubeEffect::Create();
			pEffect->SetPos(D3DXVECTOR3(m_pos.x, m_pos.y + 230.0f, m_pos.z));
			pEffect->SetSize(D3DXVECTOR3(30.0f, 230.0f, 30.0f));
			pEffect->SetColorType(0);
			pEffect->SetLife(REVIVAL_TIME);

			//�J���[�ݒ�
			for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
			{
				m_apModel[nCnt]->SetColorChange(true);
				m_apModel[nCnt]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			}
		}

		SetLifeUI();

		if (m_pLifeGauge != nullptr)
		{
			m_pLifeGauge->SetGaugeWight(m_fLifeMax, m_fLife);
		}
	}
}

//====================================================================
//���[�V�����Ə�Ԃ̊Ǘ�
//====================================================================
void CPlayer::ActionState(void)
{
	if (m_nAttackCount <= 0)
	{
		//������[�V����
		if (m_nDodgeCount > 0)
		{
			if (m_Action != ACTION_EVASION)
			{
				m_Action = ACTION_EVASION;
				m_pMotion->Set(ACTION_EVASION, 1);
			}
		}
		//�W�����v���[�V����
		else if (m_bJump == true)
		{
			if (m_Action != ACTION_JAMP)
			{
				m_Action = ACTION_JAMP;
				m_pMotion->Set(ACTION_JAMP, 5);
			}
		}
		//�ړ����[�V����
		else if (m_move.x > 0.1f || m_move.x < -0.1f || m_move.z > 0.1f || m_move.z < -0.1f)
		{
			if (m_Action != ACTION_MOVE)
			{
				m_Action = ACTION_MOVE;
				m_pMotion->Set(ACTION_MOVE, 5);
			}
		}
		//�j���[�g�������[�V����
		else
		{
			if (m_Action != ACTION_WAIT)
			{
				m_Action = ACTION_WAIT;
				m_pMotion->Set(ACTION_WAIT, 5);
			}
		}
	}
}

//====================================================================
//UI�̕\����Ԑݒ�
//====================================================================
void CPlayer::DispUI(bool Set)
{
	m_pLifeGauge->SetAppear(Set);
	m_pLifeGaugeBG->SetAppear(Set);
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_pLifeNumber[nCnt]->SetAppear(Set);
	}
}

//====================================================================
//�I�u�W�F�N�g�Ƃ̓����蔻�菈��
//====================================================================
void CPlayer::CameraDiff(void)
{
	if (CameraDiffMove == true)
	{
		if (CameraDiffTime > 0)
		{
			CameraDiffTime--;
		}
		else
		{
			CameraDiffMove = false;
		}
	}
}

//====================================================================
//�L���[�u�u���b�N�Ƃ̓����蔻�菈��
//====================================================================
bool CPlayer::CollisionBlock(D3DXVECTOR3* pos, COLLISION XYZ)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//�I�u�W�F�N�g���擾
		CObject* pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			CObject* pObjNext = pObj->GetNext();

			CObject::TYPE type = pObj->GetType();			//��ނ��擾

			if (m_State != STATE_DEATH)
			{
				if (type == TYPE_CUBEBLOCK)
				{//��ނ��u���b�N�̎�

					if (pObj->GetSize().y >= 20.0f)
					{
						if (pObj->CollisionBlock(pos, m_posOld, &m_move, &m_Objmove, COLLISION_SIZE * 0.5f, &m_bJump, XYZ) == true)
						{
							m_bJump = false;
							m_bAirAttack = false;
							m_move.y = 0.0f;

							return true;
						}
					}
					else
					{
						if (pObj->CollisionBlockUp(pos, m_posOld, &m_move, &m_Objmove, COLLISION_SIZE * 0.5f, &m_bJump, XYZ) == true)
						{
							m_bJump = false;
							m_bAirAttack = false;
							m_move.y = 0.0f;

							return true;
						}
					}

					if (m_bHit == true)
					{
						return true;
					}
				}
			}

			pObj = pObjNext;
		}
	}

	return false;
}

//====================================================================
//�L���[�u�_���[�W�Ƃ̓����蔻�菈��
//====================================================================
bool CPlayer::CollisionDamageCube(D3DXVECTOR3 pos)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//�I�u�W�F�N�g���擾
		CObject* pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			CObject* pObjNext = pObj->GetNext();

			CObject::TYPE type = pObj->GetType();			//��ނ��擾

			if (type == TYPE_CUBEDAMEGE)
			{//��ނ��u���b�N�̎�

				float fDamage = 0.0f;

				if (pObj->CollisionDamageBlock(pos, COLLISION_SIZE, &fDamage) == true)
				{
					HitDamage(fDamage);

					return true;
				}
			}

			pObj = pObjNext;
		}
	}

	return false;
}

//====================================================================
//�}�b�v�̍폜����
//====================================================================
void CPlayer::DeleteMap(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//�I�u�W�F�N�g���擾
		CObject* pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			CObject* pObjNext = pObj->GetNext();

			CObject::TYPE type = pObj->GetType();			//��ނ��擾

			if (type == TYPE_MAPCHECKPOINT)
			{//��ނ��u���b�N�̎�

				D3DXVECTOR3 ObjPos = pObj->GetPos();

				if (ObjPos.x <= 18800.0f)
				{
					pObj->Uninit();
				}
			}

			pObj = pObjNext;
		}
	}
}

//====================================================================
//�{�X�Ƃ̓����蔻�菈��
//====================================================================
void CPlayer::CollisionBoss(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//�I�u�W�F�N�g���擾
		CObject* pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			CObject* pObjNext = pObj->GetNext();

			CObject::TYPE type = pObj->GetType();			//��ނ��擾

			if (type == TYPE_BOSS)
			{//��ނ��u���b�N�̎�

				CBoss* pBoss = (CBoss*)pObj;

				D3DXVECTOR3 ObjPos = pBoss->GetPos();
				float ObjWight = pBoss->GetWight();

				if (pBoss->GetAction() == CBoss::ACTION_ATTACK)
				{
					if (CollisionCircle(m_pos, ObjPos, COLLISION_SIZE.x + ObjWight) == true)
					{
						HitDamage(BOSS_DAMAGE);
						m_nBossDamageCount++;

						if (m_nBossDamageCount >= 3)
						{//�O��ȏ�{�X�ƐڐG���ă_���[�W�����������

							//���Ӄ��O��\������
							m_nBossDamageCount = 0;
							CLog::Create(CLog::TEXT_00);
						}
					}
				}
			}
			else if (type == TYPE_ENEMY3D)
			{//��ނ��u���b�N�̎�

				CEnemy* pEnemy = (CEnemy*)pObj;

				D3DXVECTOR3 ObjPos = pEnemy->GetPos();
				float ObjWight = pEnemy->GetWight();

				if (pEnemy->GetAction() == CBoss::ACTION_ATTACK)
				{
					if (CollisionCircle(m_pos, ObjPos, COLLISION_SIZE.x + ObjWight) == true)
					{
						HitDamage(ENEMY_DAMAGE);
					}
				}
			}

			pObj = pObjNext;
		}
	}
}

//====================================================================
//�{�X��C�x���g�J�n���菈��
//====================================================================
void CPlayer::CollisionBossEvent(void)
{
	if (CGame::GetEvent() == false && CGame::GetEventEnd() == false)
	{
		if (CollisionCircle(m_pos, CGame::GetEventPos(), 300.0f) == true)
		{
			CGame::EventStart();
		}
	}
}

//====================================================================
//�e�̓����蔻�菈��
//====================================================================
bool CPlayer::CollisionShadow(void)
{
	float BlockPosY = -10000.0f;
	bool bShadow = false;;

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
				CCubeBlock* pBlock = (CCubeBlock*)pObj;

				D3DXVECTOR3 MyPos = GetPos();
				D3DXVECTOR3 MySize = COLLISION_SIZE * 2.0f;
				D3DXVECTOR3 BlockPos = pBlock->GetPos();
				D3DXVECTOR3 BlockSize = pBlock->GetSize();
				D3DXVECTOR3 BlockMove = pBlock->GetMove();

				if (BlockPos.y + BlockSize.y > BlockPosY)
				{
					if (BlockPos.x + BlockSize.x > MyPos.x &&
						BlockPos.x - BlockSize.x < MyPos.x &&
						BlockPos.z + BlockSize.z > MyPos.z &&
						BlockPos.z - BlockSize.z < MyPos.z &&
						BlockPos.y - BlockSize.y < MyPos.y)
					{
						m_pShadow->SetPos(D3DXVECTOR3(
							MyPos.x,
							BlockPos.y + BlockSize.y + BlockMove.y,
							MyPos.z));
						m_pShadow->SetWight(MySize.x * 2.0f);
						m_pShadow->SetHeight(MySize.z * 2.0f);

						BlockPosY = BlockPos.y + BlockSize.y;
						bShadow = true;
					}
				}
			}

			pObj = pObjNext;
		}
	}

	if (bShadow == false)
	{
		m_pShadow->SetWight(0.0f);
		m_pShadow->SetHeight(0.0f);
	}

	return false;
}

//====================================================================
//�`�揈��
//====================================================================
void CPlayer::Draw(void)
{
	if (m_State != STATE_REVIVAL)
	{
		//�f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
		D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		//���f���̕`��(�S�p�[�c)
		for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
		{
			m_apModel[nCntModel]->Draw();
		}
	}
}

//====================================================================
//���[�h����
//====================================================================
void CPlayer::LoadLevelData(const char* pFilename)
{
	FILE* pFile; //�t�@�C���|�C���^��錾

	//�t�@�C�����J��
	pFile = fopen(pFilename, "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

		int ModelParent = 0;
		D3DXVECTOR3 ModelPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 ModelRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		char ModelName[128] = {};
		int nCntModel = 0;
		int nCntParts = 0;
		int nCntMotion = 0;
		int nCntKeySet = 0;
		int nCntKey = 0;

		char aString[128] = {};				//�S�~��
		char aMessage[128] = {};			//�X�^�[�g�ƃG���h�̃��b�Z�[�W
		char aBool[128] = {};				//bool�ϊ��p���b�Z�[�W

		// �ǂݍ��݊J�n-----------------------------------------------------
		while (1)
		{//�uSCRIPT�v��T��
			fscanf(pFile, "%s", &aMessage[0]);
			if (strcmp(&aMessage[0], "SCRIPT") == 0)
			{
				// ���f�����ǂݍ���-----------------------------------------------------
				while (1)
				{//�uNUM_MODEL�v��T��
					fscanf(pFile, "%s", &aMessage[0]);
					if (strcmp(&aMessage[0], "NUM_MODEL") == 0)
					{
						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%d", &m_nNumModel);		//���f�����̐ݒ�
						break;
					}
				}

				//���f���t�@�C���̓ǂݍ���
				while (1)
				{//�uMODEL_FILENAME�v��T��
					fscanf(pFile, "%s", &aMessage[0]);
					if (strcmp(&aMessage[0], "MODEL_FILENAME") == 0)
					{
						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%s", &ModelName[0]);		//�ǂݍ��ރ��f���̃p�X���擾

						m_apModel[nCntModel] = CModel::Create(&ModelName[0]);
						nCntModel++;
					}
					if (nCntModel >= m_nNumModel)
					{
						nCntModel = 0;
						break;
					}
				}

				// �L�����N�^�[���ǂݍ���-----------------------------------------------------
				while (1)
				{//�uPARTSSET�v��T��
					fscanf(pFile, "%s", &aMessage[0]);
					if (strcmp(&aMessage[0], "PARTSSET") == 0)
					{
						while (1)
						{//�e��ϐ���T��
							fscanf(pFile, "%s", &aMessage[0]);
							if (strcmp(&aMessage[0], "INDEX") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%d", &nCntModel);	//�C���f�b�N�X��ݒ�
							}
							if (strcmp(&aMessage[0], "PARENT") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%d", &ModelParent);	//�e���f���̃C���f�b�N�X��ݒ�

								if (ModelParent == -1)
								{
									m_apModel[nCntModel]->SetParent(NULL);
								}
								else
								{
									m_apModel[nCntModel]->SetParent(m_apModel[ModelParent]);
								}
							}
							if (strcmp(&aMessage[0], "POS") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%f", &ModelPos.x);				//�ʒu(�I�t�Z�b�g)�̏����ݒ�
								fscanf(pFile, "%f", &ModelPos.y);				//�ʒu(�I�t�Z�b�g)�̏����ݒ�
								fscanf(pFile, "%f", &ModelPos.z);				//�ʒu(�I�t�Z�b�g)�̏����ݒ�

								m_apModel[nCntModel]->SetPos(ModelPos);
								m_apModel[nCntModel]->SetStartPos(ModelPos);
							}
							if (strcmp(&aMessage[0], "ROT") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%f", &ModelRot.x);				////�����̏����ݒ�
								fscanf(pFile, "%f", &ModelRot.y);				////�����̏����ݒ�
								fscanf(pFile, "%f", &ModelRot.z);				////�����̏����ݒ�

								m_apModel[nCntModel]->SetRot(ModelRot);
								m_apModel[nCntModel]->SetStartRot(ModelRot);
							}
							if (strcmp(&aMessage[0], "END_PARTSSET") == 0)
							{
								break;
							}
						}
						nCntModel++;
						if (nCntModel >= m_nNumModel)
						{
							break;
						}
					}
				}
			}
			if (strcmp(&aMessage[0], "END_SCRIPT") == 0)
			{
				break;
			}
		}
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		printf("***�t�@�C�����J���܂���ł���***\n");
	}
}