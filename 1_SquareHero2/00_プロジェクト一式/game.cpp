//============================================
//
//	�Q�[����� [game.cpp]
//	Author:sakamoto kai
//
//============================================
#include "game.h"
#include "manager.h"
#include "fade.h"
#include "input.h"
#include "object.h"
#include "object2D.h"
#include "object3D.h"
#include "objectBillboard.h"
#include "objectX.h"
#include "objmeshField.h"
#include "objmeshWall.h"
#include "objmeshCylinder.h"
#include "objmeshDome.h"
#include "CubeBlock.h"
#include "CubeDamage.h"
#include "player.h"
#include "boss.h"
#include "Pause.h"
#include "camera.h"
#include "game.h"
#include "sound.h"
#include "time.h"
#include "debugproc.h"
#include "Xmodel.h"
#include "texture.h"
#include "numberBillboard.h"
#include "numberFall.h"
#include "enemy.h"
#include "effect.h"
#include "Edit.h"
#include "log.h"
#include "objGauge2D.h"

//�ÓI�����o�ϐ��錾
CTutorialUI *CGame::m_pTutorialUI = nullptr;
CEdit *CGame::m_pEdit = nullptr;
CPause *CGame::m_pPause = nullptr;
CScore *CGame::m_pScore = nullptr;
CTime *CGame::m_pTime = nullptr;
CObject2D* CGame::m_p2DSample = nullptr;
CObject2D* CGame::m_pEventBG[2] = {};
CObject2D *CGame::m_p2DUI_Attack = nullptr;		//�U����2DUI
CObject2D *CGame::m_p2DUI_Jump = nullptr;			//�W�����v��2DUI
CObject2D *CGame::m_p2DUI_Dodge = nullptr;			//�����2DUI
CObject2D* CGame::m_p2DUI_Attention = nullptr;		//���ڂ�2DUI
CObject2D *CGame::m_p2DUI_AttentionOK = nullptr;	//���ڂ�2DUI
CObject3D* CGame::m_p3DSample = nullptr;
CObject3D* CGame::m_p3DEventBG = nullptr;			//�C�x���g����3D�w�i
CObject2D *CGame::m_p2DBossName = nullptr;
CObjectBillboard* CGame::m_pBillboardSample = nullptr;
CObjectX* CGame::m_pXModelSample = nullptr;
CObjmeshField* CGame::m_pMeshFieldSample = nullptr;
CObjmeshWall* CGame::m_pMeshWallSample = nullptr;
CObjmeshCylinder* CGame::m_pMeshCylinderSample = nullptr;
CObjmeshDome* CGame::m_pMeshDomeUp = nullptr;
CObjmeshDome* CGame::m_pMeshDomeDown = nullptr;
CCubeBlock* CGame::m_pCubeBlock = nullptr;
CPlayer* CGame::m_pPlayer = nullptr;
CBoss*CGame::m_pBoss = nullptr;
bool CGame::m_bGameEnd = false;
bool CGame::m_bEvent = false;
bool CGame::m_bEventEnd = false;
int CGame::m_nEnemyNum = 0;
int CGame::m_nTutorialWave = 0;
int CGame::m_nEventCount = 0;
float CGame::m_EventHeight = 0.0f;
float CGame::m_NameColorA = 0.0f;
float CGame::m_BGColorA = 1.0f;
D3DXVECTOR3 CGame::m_EventPos = D3DXVECTOR3(0.0f, 300.0f, 0.0f);
D3DXVECTOR3 CGame::m_BGRot = INITVECTOR3;

//====================================================================
//�R���X�g���N�^
//====================================================================
CGame::CGame()
{
	m_nEnemyNum = 0;
	m_bGameEnd = false;
	m_bEvent = false;
	m_bEventEnd = false;
	m_EventHeight = 0.0f;
	m_nEventCount = 0;
	m_BGColorA = 1.0f;
	m_nTutorialWave = 0;
	CManager::GetInstance()->GetCamera()->SetBib(false);
	CManager::GetInstance()->GetCamera()->SetCameraMode(CCamera::CAMERAMODE_FOLLOW);
}

//====================================================================
//�f�X�g���N�^
//====================================================================
CGame::~CGame()
{

}

//====================================================================
//����������
//====================================================================
HRESULT CGame::Init(void)
{
	CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_BGM_TUTORIAL);

	//m_p2DSample = CObject2D::Create();
	//m_p2DSample->SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	//m_p2DSample->SetWight(100.0f);
	//m_p2DSample->SetHeight(100.0f);
	//m_p2DSample->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	//m_p3DSample = CObject3D::Create();
	//m_p3DSample->SetPos(D3DXVECTOR3(200.0f, 0.0f, 0.0f));
	//m_p3DSample->SetRot(D3DXVECTOR3(1.57f, 0.0f, 0.0f));
	//m_p3DSample->SetWight(100.0f);
	//m_p3DSample->SetHeight(100.0f);

	//m_pBillboardSample = CObjectBillboard::Create();
	//m_pBillboardSample->SetPos(INITVECTOR3);

	//m_pXModelSample = CObjectX::Create("data\\MODEL\\player00.x");
	//m_pXModelSample->SetPos(D3DXVECTOR3(-200.0f, 0.0f, 0.0f));

	//m_pMeshFieldSample = CObjmeshField::Create();
	//m_pMeshFieldSample->SetPos(D3DXVECTOR3(0.0f, 0.0f, 200.0f));

	//m_pMeshWallSample = CObjmeshWall::Create();
	//m_pMeshWallSample->SetPos(D3DXVECTOR3(0.0f, 0.0f, 300.0f));

	//m_pMeshCylinderSample = CObjmeshCylinder::Create();

	m_pMeshDomeUp = CObjmeshDome::Create();
	m_pMeshDomeUp->SetTexture("data\\TEXTURE\\SkyBG.jpg");

	m_pMeshDomeDown = CObjmeshDome::Create();
	m_pMeshDomeDown->SetTexture("data\\TEXTURE\\SkyBG.jpg");
	m_pMeshDomeDown->SetRot(D3DXVECTOR3(D3DX_PI, 0.0f, 0.0f));

	//SetStageBlock();
	LoadStageBlock();

	CCubeDamage* pCubeD = CCubeDamage::Create();
	pCubeD->SetPos(D3DXVECTOR3(100.0f, 150.0f, -2800.0f));
	pCubeD->SetCubeType(CCubeDamage::CUBETYPE_BREAK);
	pCubeD->SetDamage(10);

	pCubeD = CCubeDamage::Create();
	pCubeD->SetPos(D3DXVECTOR3(-100.0f, 150.0f, -2800.0f));
	pCubeD->SetCubeType(CCubeDamage::CUBETYPE_NORMAL);
	pCubeD->SetDamage(10);

	//m_pCubeBlock = CCubeBlock::Create();
	//m_pCubeBlock->SetPos(D3DXVECTOR3(150.0f, 250.0f, -150.0f));
	//m_pCubeBlock->SetSize(D3DXVECTOR3(100.0f, 10.0f, 100.0f));
	//m_pCubeBlock->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//m_pCubeBlock = CCubeBlock::Create();
	//m_pCubeBlock->SetPos(D3DXVECTOR3(-150.0f, 250.0f, 150.0f));
	//m_pCubeBlock->SetSize(D3DXVECTOR3(100.0f, 10.0f, 100.0f));
	//m_pCubeBlock->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pPlayer = CPlayer::Create();
	m_pPlayer->SetPos(D3DXVECTOR3(0.0f, 150.0f, -3820.0f));
	m_pPlayer->SetReSpownPos(D3DXVECTOR3(0.0f, 300.0f, -3820.0f));

	m_pBoss = CBoss::Create("data\\MODEL\\boss.x");
	m_pBoss->SetPos(D3DXVECTOR3(0.0f, 5000.0f, 0.0f));

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_pEventBG[nCnt] = CObject2D::Create();
		m_pEventBG[nCnt]->SetPos(D3DXVECTOR3(640.0f, nCnt * 720.0f, 0.0f));
		m_pEventBG[nCnt]->SetWight(1280.0f);
		m_pEventBG[nCnt]->SetHeight(0.0f);
		m_pEventBG[nCnt]->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
		m_pEventBG[nCnt]->SetTexture("data\\TEXTURE\\Test.jpg");
	}

	m_p2DUI_Attention = CObject2D::Create();
	m_p2DUI_Attention->SetPos(D3DXVECTOR3(130.0f, 600.0f, 0.0f));
	m_p2DUI_Attention->SetWight(150.0f);
	m_p2DUI_Attention->SetHeight(40.0f);
	m_p2DUI_Attention->SetTexture("data\\TEXTURE\\UI_Attention.png");

	m_p2DUI_AttentionOK = CObject2D::Create();
	m_p2DUI_AttentionOK->SetPos(D3DXVECTOR3(130.0f, 650.0f, 0.0f));
	m_p2DUI_AttentionOK->SetWight(100.0f);
	m_p2DUI_AttentionOK->SetHeight(100.0f);
	m_p2DUI_AttentionOK->SetTexture("data\\TEXTURE\\UI_AttentionOFF.png");

	m_p2DUI_Dodge = CObject2D::Create();
	m_p2DUI_Dodge->SetPos(D3DXVECTOR3(1120.0f, 550.0f, 0.0f));
	m_p2DUI_Dodge->SetWight(150.0f);
	m_p2DUI_Dodge->SetHeight(40.0f);
	m_p2DUI_Dodge->SetTexture("data\\TEXTURE\\UI_Dodge.png");

	m_p2DUI_Jump = CObject2D::Create();
	m_p2DUI_Jump->SetPos(D3DXVECTOR3(1170.0f, 600.0f, 0.0f));
	m_p2DUI_Jump->SetWight(150.0f);
	m_p2DUI_Jump->SetHeight(40.0f);
	m_p2DUI_Jump->SetTexture("data\\TEXTURE\\UI_Jump.png");

	m_p2DUI_Attack = CObject2D::Create();
	m_p2DUI_Attack->SetPos(D3DXVECTOR3(1120.0f, 650.0f, 0.0f));
	m_p2DUI_Attack->SetWight(150.0f);
	m_p2DUI_Attack->SetHeight(40.0f);
	m_p2DUI_Attack->SetTexture("data\\TEXTURE\\UI_Attack.png");

	//�^�C���̐���
	m_pTime = CTime::Create();

	//�|�[�Y�̐���
	if (m_pPause == nullptr)
	{
		m_pPause = CPause::Create();
	}

	m_bGameEnd = false;
	CManager::GetInstance()->GetInstance()->SetStop(false);

#if _DEBUG
	if (m_pEdit == nullptr)
	{
		m_pEdit = CEdit::Create();
	}
#endif

	CLog::InitCreateMax();

	//�������O�̕\��
	CLog::Create(CLog::TEXT_09);

	return S_OK;
}

//====================================================================
//�I������
//====================================================================
void CGame::Uninit(void)
{
	//�S�ẴI�u�W�F�N�g�̔j��
	CObject::ReleaseAll();

	if (m_pPause != nullptr)
	{
		delete m_pPause;
		m_pPause = nullptr;
	}

#if _DEBUG
	if (m_pEdit != nullptr)
	{
		m_pEdit->Uninit();
		delete m_pEdit;
		m_pEdit = nullptr;
	}
#endif
}

//====================================================================
//�I������
//====================================================================
void CGame::DeleteTutorial(void)
{

}

//====================================================================
//�X�V����
//====================================================================
void CGame::Update(void)
{
	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputJoypad* pInputJoypad = CManager::GetInstance()->GetInputJoyPad();

#if _DEBUG
	if (CManager::GetInstance()->GetEdit() == true)
	{
		CManager::GetInstance()->GetCamera()->SetCameraMode(CCamera::CAMERAMODE_CONTROL);
		m_pEdit->Update();
	}

#endif

	CEnemy* pEnemy = nullptr;

	switch (m_nTutorialWave)
	{
	case 0:
		if (m_pPlayer->GetPos().z > -3720.0f)
		{
			CLog::Create(CLog::TEXT_10);
			m_nTutorialWave++;
		}
		break;
	case 1:
		if (m_pPlayer->GetPos().z > -3100.0f)
		{
			CLog::Create(CLog::TEXT_04);
			m_nTutorialWave++;
		}
		break;
	case 2:
		if (m_pPlayer->GetPos().z > -2300.0f)
		{
			CLog::Create(CLog::TEXT_11);

			pEnemy = CEnemy::Create("data\\MODEL\\enemy.x");
			pEnemy->SetPos(D3DXVECTOR3(200.0f, 300.0f, -1800.0f));
			pEnemy->SetAction(CEnemy::ACTION_PARTICLE);

			pEnemy = CEnemy::Create("data\\MODEL\\enemy.x");
			pEnemy->SetPos(D3DXVECTOR3(0.0f, 300.0f, -1800.0f));
			pEnemy->SetAction(CEnemy::ACTION_PARTICLE);

			pEnemy = CEnemy::Create("data\\MODEL\\enemy.x");
			pEnemy->SetPos(D3DXVECTOR3(-200.0f, 300.0f, -1800.0f));
			pEnemy->SetAction(CEnemy::ACTION_PARTICLE);

			m_pCubeBlock = CCubeBlock::Create();
			m_pCubeBlock->SetPos(D3DXVECTOR3(0.0f, 300.0f, -1700.0f));
			m_pCubeBlock->SetSize(D3DXVECTOR3(500.0f, 200.0f, 10.0f));
			m_pCubeBlock->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

			m_nTutorialWave++;
		}

		break;

	case 3:
		if (EnemyCheck() == false)
		{
			if (m_pCubeBlock != nullptr)
			{
				m_pCubeBlock->Uninit();
				m_pCubeBlock = nullptr;
			}
			m_nTutorialWave++;
		}

		break;

	default:
		break;
	}

	if (m_pBoss != nullptr)
	{
		if (m_pBoss->GetBossForm() == 0)
		{
			m_BGRot.x += 0.00f;
			m_BGRot.y += 0.0005f;
			m_BGRot.z = 0.0f;

			if (m_pMeshDomeUp != nullptr)
			{
				m_pMeshDomeUp->SetRot(D3DXVECTOR3(m_BGRot.x, m_BGRot.y, m_BGRot.z));
			}
			if (m_pMeshDomeDown != nullptr)
			{
				m_pMeshDomeDown->SetRot(D3DXVECTOR3(D3DX_PI + m_BGRot.x, m_BGRot.y, -m_BGRot.z));
			}
		}
		else if(m_pBoss->GetBossForm() == 1)
		{
			m_BGRot.x += 0.00f;
			m_BGRot.y += 0.01f;
			m_BGRot.z = D3DX_PI * 0.5f;

			if (m_pMeshDomeUp != nullptr)
			{
				m_pMeshDomeUp->SetRot(D3DXVECTOR3(m_BGRot.x, m_BGRot.y, m_BGRot.z));
				m_pMeshDomeUp->SetScroll(D3DXVECTOR2(m_BGRot.y, m_BGRot.y));
				m_pMeshDomeUp->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_BGColorA));
			}
			if (m_pMeshDomeDown != nullptr)
			{
				m_pMeshDomeDown->SetRot(D3DXVECTOR3(D3DX_PI + m_BGRot.x, m_BGRot.y, -m_BGRot.z));
				m_pMeshDomeDown->SetScroll(D3DXVECTOR2(m_BGRot.y, m_BGRot.y));
				m_pMeshDomeDown->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_BGColorA));
			}
		}
	}

	//���ڂ̐؂�ւ�
	if (CManager::GetInstance()->GetCamera()->GetCameraMode() == CCamera::CAMERAMODE_FOLLOW)
	{
		if (CManager::GetInstance()->GetCamera()->GetAttention() == true)
		{
			m_p2DUI_AttentionOK->SetTexture("data\\TEXTURE\\UI_AttentionON.png");
		}
		else
		{
			m_p2DUI_AttentionOK->SetTexture("data\\TEXTURE\\UI_AttentionOFF.png");
		}
	}

	//�|�[�Y�̍X�V����
	m_pPause->Update();

	//�C�x���g�������̃|���S���ړ�
	if (m_bEvent == false)
	{
		if (m_EventHeight > 0.0f)
		{
			m_EventHeight -= 5.0f;
		}
	}
	else
	{
		//�C�x���g�̍X�V
		EventUpdate();
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pEventBG[nCnt] != nullptr)
		{
			m_pEventBG[nCnt]->SetHeight(m_EventHeight);
		}
	}

	if (m_bGameEnd == true)
	{
		CFade::SetFade(CScene::MODE_RESULT);

		if (CManager::GetInstance()->GetGameClear() == true)
		{
			CManager::GetInstance()->SetEndScore(m_pPlayer->GetDamage());
			CManager::GetInstance()->SetEndTime(m_pTime->GetTimeNumber());
		}
	}
}

//====================================================================
//�C�x���g�̍X�V
//====================================================================
void CGame::EventUpdate(void)
{
	if (m_EventHeight < 150.0f)
	{
		m_EventHeight += 5.0f;
	}

	//�e��I�u�W�F�N�g�̐����Ə�����
	if (m_nEventCount == 0)
	{
		CManager::GetInstance()->GetSound()->StopSound(CSound::SOUND_LABEL_BGM_TUTORIAL);

		DispUI(false);
		m_pPlayer->DispUI(false);

		CCubeBlock* pBlock;

		//�Q�[����SE���Đ�����
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_GOGOGOGO);

		for (int nCnt = 0; nCnt < 50; nCnt++)
		{
			float randX = (float)(rand() % 751);
			float randY = (float)(rand() % 201);

			pBlock = CCubeBlock::Create();
			pBlock->SetPos(D3DXVECTOR3(m_EventPos.x - 750.0f + randX - 250.0f, m_EventPos.y + randY - 100.0f, m_EventPos.z - 100.0f));
			pBlock->SetMove(D3DXVECTOR3(15.0f, 0.0f, 0.0f));
			pBlock->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
			pBlock->SetSize(D3DXVECTOR3(50.0f, 50.0f, 25.0f));
			pBlock->SetLife(120);
		}
	}
	else if (m_nEventCount == 30)
	{
		if (m_p3DEventBG == nullptr)
		{
			m_p3DEventBG = CObject3D::Create();
			m_p3DEventBG->SetWight(500.0f);
			m_p3DEventBG->SetHeight(250.0f);
			m_p3DEventBG->SetTexture("data\\TEXTURE\\BG_BOSS00.png");
		}

		if (m_p2DBossName == nullptr)
		{
			m_p2DBossName = CObject2D::Create();
			m_p2DBossName->SetPos(D3DXVECTOR3(640.0f, 600.0f, 0.0f));
			m_p2DBossName->SetWight(500.0f);
			m_p2DBossName->SetHeight(500.0f);
			m_p2DBossName->SetTexture("data\\TEXTURE\\BossName.png");
			m_NameColorA = 0.0f;
			m_p2DBossName->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_NameColorA));
		}

		if (m_pBoss != nullptr)
		{
			m_pBoss->SetPos(D3DXVECTOR3(0.0f, 300.0f, 0.0f));
		}
	}

	//�{�X�̓����Ǘ�
	if (m_pBoss != nullptr)
	{

	}

	//�J�����U���̊Ǘ�
	if (m_nEventCount == 60)
	{
		//�Q�[����SE���Đ�����
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_HOWL);
	}
	if (m_nEventCount == 120)
	{
		//�J�����̃o�C�u���[�V�������I���ɂ���
		CManager::GetInstance()->GetCamera()->SetBib(true);
	}
	else if (m_nEventCount == 240)
	{
		//�J�����̃o�C�u���[�V�������I�t�ɂ���
		CManager::GetInstance()->GetCamera()->SetBib(false);

		//�Q�[����SE���~����
		CManager::GetInstance()->GetSound()->StopSound(CSound::SOUND_LABEL_SE_HOWL);
	}

	if (m_nEventCount >= 120 && m_nEventCount < 240)
	{
		if (m_nEventCount % 5 == 0)
		{
			CEffect* pEffect = CEffect::Create();
			pEffect->SetTexName("data\\TEXTURE\\RingEffect.png");
			pEffect->SetPos(D3DXVECTOR3(m_pBoss->GetPos().x, m_pBoss->GetPos().y, m_pBoss->GetPos().x - 50.0f));
			pEffect->SetDel(-40.0f);
			pEffect->SetLife(60);
			pEffect->SetRadius(0.0f);
			pEffect->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}
	}

	//�C�x���g�w�i�̍X�V
	if (m_p3DEventBG != nullptr)
	{
		if (m_nEventCount < 60)
		{
			m_p3DEventBG->SetPos(D3DXVECTOR3(m_EventPos.x - 50.0f - ((float)60 - (float)m_nEventCount) * 50.0f, m_EventPos.y, m_EventPos.z));
		}
		else
		{
			m_p3DEventBG->SetPos(D3DXVECTOR3(m_EventPos.x - 50.0f, m_EventPos.y, m_EventPos.z));
		}
	}

	//�C�x���g�{�X�l�[���̍X�V
	if (m_p2DBossName != nullptr)
	{
		if (m_nEventCount >= 240)
		{
			m_NameColorA -= 0.02f;
			m_p2DBossName->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_NameColorA));
		}
		else if (m_nEventCount > 60)
		{
			m_NameColorA += 0.02f;

			if (m_NameColorA > 1.0f)
			{
				m_NameColorA = 1.0f;
			}

			m_p2DBossName->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_NameColorA));
		}
	}

	//�C�x���g�I���܂ł̃J�E���g
	if (m_nEventCount < 300)
	{
		m_nEventCount++;
	}
	else
	{//�C�x���g�I����
		CManager::GetInstance()->GetCamera()->SetCameraMode(CCamera::CAMERAMODE_FOLLOW);
		m_bEvent = false;
		m_bEventEnd = true;
		m_pTime->SetStartTime(timeGetTime());

		if (m_pPlayer != nullptr)
		{
			m_pPlayer->SetLife(PLAYER_LIFE);
			m_pPlayer->SetDamage(0.0f);
			m_pPlayer->SetLifeUI();
			m_pPlayer->GetLifeGauge()->SetGaugeWight(PLAYER_LIFE, PLAYER_LIFE);
		}

		if (m_p3DEventBG != nullptr)
		{
			m_p3DEventBG->SetDeathFlag(true);
			m_p3DEventBG = nullptr;
		}

		if (m_p2DBossName != nullptr)
		{
			m_p2DBossName->SetDeathFlag(true);
			m_p2DBossName = nullptr;
		}

		if (m_pBoss != nullptr)
		{
			m_pBoss->SetAction(CBoss::ACTION_NORMAL);
		}

		//�Q�[����SE���Đ�����
		CManager::GetInstance()->GetSound()->StopSound(CSound::SOUND_LABEL_SE_GOGOGOGO);

		//�Q�[����BGM���Đ�����
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_BGM_BOSS);

		m_pBoss->LifeGaugeCreate();
		DispUI(true);
		m_pPlayer->DispUI(true);
	}
}

//====================================================================
//UI�̕\����Ԑݒ�
//====================================================================
void CGame::DispUI(bool Set)
{
	if (m_p2DBossName != nullptr)
	{
		m_p2DBossName->SetAppear(Set);
	}
	if (m_p2DUI_Attention != nullptr)
	{
		m_p2DUI_Attention->SetAppear(Set);
	}
	if (m_p2DUI_Attack != nullptr)
	{
		m_p2DUI_Attack->SetAppear(Set);
	}
	if (m_p2DUI_AttentionOK != nullptr)
	{
		m_p2DUI_AttentionOK->SetAppear(Set);
	}
	if (m_p2DUI_Dodge != nullptr)
	{
		m_p2DUI_Dodge->SetAppear(Set);
	}
	if (m_p2DUI_Jump != nullptr)
	{
		m_p2DUI_Jump->SetAppear(Set);
	}
}

//====================================================================
//�X�e�[�W�̃u���b�N�z�u
//====================================================================
void CGame::SetStageBlock(void)
{
	m_pCubeBlock = CCubeBlock::Create();
	m_pCubeBlock->SetPos(D3DXVECTOR3(0.0f, 100.0f, 0.0f));
	m_pCubeBlock->SetSize(D3DXVECTOR3(500.0f, 10.0f, 500.0f));
	m_pCubeBlock->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//====================================================================
//�ǂݍ��݃u���b�N�z�u
//====================================================================
void CGame::LoadStageBlock(void)
{
	FILE* pFile; //�t�@�C���|�C���^��錾

	//�t�@�C�����J��
	pFile = fopen("", "r");

	if (GetMode() == MODE_GAME)
	{
		//�t�@�C�����J��
		pFile = fopen(DATA_NAME,"r");
	}

	if (pFile != nullptr)
	{//�t�@�C�����J�����ꍇ

		char Getoff[32] = {};
		char boolLife[32] = {};
		char aString[128] = {};			//�S�~��
		char aStartMessage[32] = {};	//�X�^�[�g���b�Z�[�W
		char aSetMessage[32] = {};		//�Z�b�g���b�Z�[�W
		char aEndMessage[32] = {};		//�I�����b�Z�[�W

		fscanf(pFile, "%s", &aStartMessage[0]);
		if (strcmp(&aStartMessage[0], "STARTSETSTAGE") == 0)
		{
			while (1)
			{
				fscanf(pFile, "%s", &aSetMessage[0]);
				if (strcmp(&aSetMessage[0], "STARTSETBLOCK") == 0)
				{
					D3DXVECTOR3 pos;
					D3DXVECTOR3 Size;

					fscanf(pFile, "%s", &aString[0]);
					fscanf(pFile, "%f", &pos.x);
					fscanf(pFile, "%f", &pos.y);
					fscanf(pFile, "%f", &pos.z);

					fscanf(pFile, "%s", &aString[0]);
					fscanf(pFile, "%f", &Size.x);
					fscanf(pFile, "%f", &Size.y);
					fscanf(pFile, "%f", &Size.z);

					CCubeBlock* pBlock = CCubeBlock::Create();
					pBlock->SetPos(pos);
					pBlock->SetSize(Size);

					fscanf(pFile, "%s", &aEndMessage[0]);
					if (strcmp(&aEndMessage[0], "ENDSETBLOCK") != 0)
					{
						break;
					}
				}
				else if (strcmp(&aSetMessage[0], "ENDSETSTAGE") == 0)
				{
					break;
				}
			}
		}
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		printf("***�t�@�C�����J���܂���ł���***\n");
	}
}

//====================================================================
//�G�����邩���Ȃ����̔��f
//====================================================================
bool CGame::EnemyCheck(void)
{
	m_nEnemyNum = 0;

	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//�I�u�W�F�N�g���擾
		CObject* pObj = CObject::GetTop(nCntPriority);

		while (pObj != nullptr)
		{
			CObject* pObjNext = pObj->GetNext();

			CObject::TYPE type = pObj->GetType();			//��ނ��擾

			if (type == CObject::TYPE_ENEMY3D)
			{//��ނ��G�̎�
				m_nEnemyNum++;
			}

			pObj = pObjNext;
		}
	}
	if (m_nEnemyNum > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//====================================================================
//�G�����邩���Ȃ����̔��f
//====================================================================
void CGame::DeleteMap(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//�I�u�W�F�N�g���擾
		CObject* pObj = CObject::GetTop(nCntPriority);

		while (pObj != nullptr)
		{
			CObject* pObjNext = pObj->GetNext();

			CObject::TYPE type = pObj->GetType();			//��ނ��擾

			if (type == CObject::TYPE_CUBEBLOCK ||
				type == CObject::TYPE_CUBEDAMEGE)
			{//��ނ��}�b�v�֘A�̎�
				pObj->Uninit();
			}

			pObj = pObjNext;
		}
	}
}

//====================================================================
//�C�x���g�J�n����
//====================================================================
void CGame::EventStart(void)
{
	m_bEvent = true;
	DeleteMap();
	SetStageBlock();
	m_pPlayer->SetReSpownPos(D3DXVECTOR3(0.0f, 300.0f, 0.0f));
	CManager::GetInstance()->GetCamera()->SetCameraMode(CCamera::CAMERAMODE_EVENTBOSS);
}

//====================================================================
//���Z�b�g����
//====================================================================
void CGame::ReSetGame(void)
{

}

//====================================================================
//�`�揈��
//====================================================================
void CGame::Draw(void)
{

}
