//===========================================
//
// ���O�̃��C������[log.cpp]
// Author ��{�ėB
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "log.h"
#include "player.h"
#include "object2D.h"
#include "texture.h"

int CLog::m_CreateMax = -1;
//-------------------------------------------
// �}�N����`
//-------------------------------------------
namespace
{
	const D3DXVECTOR3 LOGSIZE_BG = D3DXVECTOR3(200.0f, 100.0f, 0.0f);		// ���O�̔w�i�̑傫��

	const D3DXVECTOR3 LOGSIZE_PLAYERID = D3DXVECTOR3(100.0f, 100.0f, 0.0f);		// ���O�̃v���C���[ID�̑傫��
	const D3DXVECTOR3 LOGSIZE_MESSAGE[CLog::TYPE_MAX] =			// ���O�̃��b�Z�[�W�̑傫��
	{
		D3DXVECTOR3(250.0f, 250.0f, 0.0f),
		D3DXVECTOR3(250.0f, 250.0f, 0.0f),
		D3DXVECTOR3(250.0f, 250.0f, 0.0f),
		D3DXVECTOR3(250.0f, 250.0f, 0.0f),
		D3DXVECTOR3(250.0f, 250.0f, 0.0f),
		D3DXVECTOR3(250.0f, 250.0f, 0.0f),
		D3DXVECTOR3(250.0f, 250.0f, 0.0f),
		D3DXVECTOR3(250.0f, 250.0f, 0.0f),
		D3DXVECTOR3(250.0f, 250.0f, 0.0f),
		D3DXVECTOR3(250.0f, 250.0f, 0.0f),
		D3DXVECTOR3(250.0f, 250.0f, 0.0f),
		D3DXVECTOR3(250.0f, 250.0f, 0.0f),
	};
	const float LOGDISTANCE_PLAYERID = -65.0f;	// ���O�̃v���C���[ID��X�ʒu

	const D3DXVECTOR2 LOGDISTANCE_MESSAGE[CLog::TYPE_MAX] =		// ���O�̃��b�Z�[�W��X�ʒu
	{
		D3DXVECTOR2(50.0f, 20.0f),
		D3DXVECTOR2(80.0f, 20.0f),
		D3DXVECTOR2(10.0f, 20.0f),
		D3DXVECTOR2(80.0f, 20.0f),
		D3DXVECTOR2(70.0f, 20.0f),
		D3DXVECTOR2(60.0f, 20.0f),
		D3DXVECTOR2(70.0f, 20.0f),
		D3DXVECTOR2(60.0f, 20.0f),
		D3DXVECTOR2(60.0f, 20.0f),
		D3DXVECTOR2(80.0f, 20.0f),
		D3DXVECTOR2(80.0f, 20.0f),
		D3DXVECTOR2(60.0f, 20.0f),
	};
	const int LOGTIME = 500;				// ���O�̕\������
	const float LOGSPEED_IN = 10.0f;		// ���O�̓o�ꑬ�x
	const float LOGSPEED_DOWN = 3.0f;		// ���O�̗������x
	const float LOGSPEED_OUT = 10.0f;		// ���O�̑ޏꑬ�x
	const float LOGPOS_IN = 100.0f;			// ���O�̓o��ʒu
	const float LOGPOS_DOWN = 350.0f;		// ���O�̒�~�ʒu
}

//==============================
// �R���X�g���N�^
//==============================
CLog::CLog(int nPriority) : CObject(nPriority)
{
	// �S�Ă̒l���N���A����
	LogPos = INITVECTOR3;
	m_CreateNumber = -1;
	m_State = STATE_IN;
	m_nLife = 0;
	m_Type = TEXT_00;
	m_nLogIdx = -1;
	m_fLogStopPosY = 0.0f;
	m_pLogBG = nullptr;
	m_pLogPlayerBG = nullptr;
	m_pLogMessage = nullptr;
	m_pMain = nullptr;			// �����̎����g�p���Ă���I�u�W�F�N�g�̃|�C���^
}

//==============================
// �f�X�g���N�^
//==============================
CLog::~CLog()
{

}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CLog::Init(void)
{
	// �S�Ă̒l������������
	LogPos = INITVECTOR3;
	m_CreateNumber = -1;
	m_State = STATE_IN;
	m_nLife = 0;
	m_Type = TEXT_00;
	m_nLogIdx = -1;
	m_fLogStopPosY = 0.0f;
	m_pLogBG = NULL;
	m_pLogPlayerBG = NULL;
	m_pLogMessage = NULL;
	m_pMain = NULL;			// �����̎����g�p���Ă���I�u�W�F�N�g�̃|�C���^

	//��ސݒ�
	SetType(CObject::TYPE_LOG);

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �j�Ђ̏I������
//========================================
void CLog::Uninit(void)
{
	// �I������
	if (m_pLogBG != NULL)
	{
		m_pLogBG->Uninit();
		m_pLogBG = NULL;
	}

	if (m_pLogPlayerBG != NULL)
	{
		m_pLogPlayerBG->Uninit();
		m_pLogPlayerBG = NULL;
	}

	if (m_pLogMessage != NULL)
	{
		m_pLogMessage->Uninit();
		m_pLogMessage = NULL;
	}

	SetDeathFlag(true);
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CLog::Update(void)
{
	// �`�揈��
	if (m_pLogBG != NULL)
	{
		m_pLogBG->Update();
	}
	if (m_pLogPlayerBG != NULL)
	{
		m_pLogPlayerBG->Update();
	}
	if (m_pLogMessage != NULL)
	{
		m_pLogMessage->Update();
	}

	StateManager();

	if (m_pLogBG != NULL)
	{
		m_pLogBG->SetPos(D3DXVECTOR3(LogPos.x, LogPos.y, 0.0f));
	}
	if (m_pLogPlayerBG != NULL)
	{
		m_pLogPlayerBG->SetPos(D3DXVECTOR3(LogPos.x + LOGDISTANCE_PLAYERID, LogPos.y, 0.0f));
	}
	if (m_pLogMessage != NULL)
	{
		m_pLogMessage->SetPos(D3DXVECTOR3(LogPos.x + LOGDISTANCE_MESSAGE[m_Type].x, LogPos.y + LOGDISTANCE_MESSAGE[m_Type].y, 0.0f));
	}
}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CLog::Draw(void)
{
	if (CScene::GetMode() == CScene::MODE_GAME)
	{
		// �`�揈��
		if (m_pLogBG != NULL)
		{
			m_pLogBG->Draw();
		}
		if (m_pLogPlayerBG != NULL)
		{
			m_pLogPlayerBG->Draw();
		}
		if (m_pLogMessage != NULL)
		{
			m_pLogMessage->Draw();
		}
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CLog::StateManager(void)
{
	m_nLife--;

	switch (m_State)
	{
	case CLog::STATE_IN:
		if (LogPos.x < LOGSIZE_BG.x * 0.5f)
		{
			LogPos.x += LOGSPEED_IN;
		}
		else
		{
			LogPos.x = LOGSIZE_BG.x * 0.5f;
			m_State = STATE_DOWN;
		}
		break;
	case CLog::STATE_DOWN:

		if (LogPos.y < m_fLogStopPosY - (m_CreateNumber * LOGSIZE_BG.y))
		{
			LogPos.y += LOGSPEED_DOWN;
		}
		else
		{
			LogPos.y = m_fLogStopPosY - (m_CreateNumber * LOGSIZE_BG.y);
		}

		if (m_nLife <= 0)
		{
			m_State = STATE_OUT;
		}

		break;
	case CLog::STATE_OUT:
		if (LogPos.x > -LOGSIZE_BG.x * 0.5f)
		{
			LogPos.x -= LOGSPEED_OUT;
		}
		else
		{
			DelNumber();
			Uninit();
			return;
		}
		break;
	default:
		assert(false);
		break;
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CLog::SetData(CLog::TEXT Type)
{
	m_CreateMax++;
	m_CreateNumber = m_CreateMax;
	m_Type = Type;
	m_nLife = LOGTIME;

	if (m_pLogBG == NULL)
	{
		m_pLogBG = CObject2D::Create();
		m_pLogBG->SetPos(D3DXVECTOR3(LogPos.x, LogPos.y, 0.0f));
		m_pLogBG->SetWight(LOGSIZE_BG.x);
		m_pLogBG->SetHeight(LOGSIZE_BG.y);
		m_pLogBG->SetTexture("data\\TEXTURE\\Test.jpg");
		m_pLogBG->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	}
	if (m_pLogMessage == NULL)
	{
		m_pLogMessage = CObject2D::Create();
		m_pLogMessage->SetPos(D3DXVECTOR3(LogPos.x + LOGDISTANCE_MESSAGE[m_Type].x, LogPos.y + LOGDISTANCE_MESSAGE[m_Type].y, 0.0f));
		m_pLogMessage->SetRot(INITVECTOR3);
		m_pLogMessage->SetWight(LOGSIZE_MESSAGE[m_Type].x);
		m_pLogMessage->SetHeight(LOGSIZE_MESSAGE[m_Type].y);

		switch (m_Type)
		{
		case CLog::TEXT_00:
			m_pLogMessage->SetTexture("data\\TEXTURE\\Text00_PinkWarning.png");
			break;
		case CLog::TEXT_01:
			m_pLogMessage->SetTexture("data\\TEXTURE\\Text01_RedWarning.png");
			break;
		case CLog::TEXT_02:
			m_pLogMessage->SetTexture("data\\TEXTURE\\Text02_Trueflag.png");
			break;
		case CLog::TEXT_03:
			m_pLogMessage->SetTexture("data\\TEXTURE\\Text03_Attack.png");
			break;
		case CLog::TEXT_04:
			m_pLogMessage->SetTexture("data\\TEXTURE\\Text04_Damage.png");
			break;
		case CLog::TEXT_05:
			m_pLogMessage->SetTexture("data\\TEXTURE\\Text05_Dodge.png");
			break;
		case CLog::TEXT_06:
			m_pLogMessage->SetTexture("data\\TEXTURE\\Text06_BlockRun.png");
			break;
		case CLog::TEXT_07:
			m_pLogMessage->SetTexture("data\\TEXTURE\\Text07_MapBreak.png");
			break;
		case CLog::TEXT_08:
			m_pLogMessage->SetTexture("data\\TEXTURE\\Text08_Rain.png");
			break;
		case CLog::TEXT_09:
			m_pLogMessage->SetTexture("data\\TEXTURE\\Text09_Move.png");
			break;
		case CLog::TEXT_10:
			m_pLogMessage->SetTexture("data\\TEXTURE\\Text10_Jump.png");
			break;
		case CLog::TEXT_11:
			m_pLogMessage->SetTexture("data\\TEXTURE\\Text11_Enemy.png");
			break;
		default:
			break;
		}
	}
	if (m_pLogPlayerBG == NULL)
	{
		m_pLogPlayerBG = CObject2D::Create();
		m_pLogPlayerBG->SetPos(D3DXVECTOR3(LogPos.x + LOGDISTANCE_PLAYERID, LogPos.y, 0.0f));
		m_pLogPlayerBG->SetWight(LOGSIZE_PLAYERID.x);
		m_pLogPlayerBG->SetHeight(LOGSIZE_PLAYERID.y);
		m_pLogPlayerBG->SetTexture("data\\TEXTURE\\playerLog.png");
	}

	LogPos = D3DXVECTOR3(-200.0f, LOGPOS_IN + 160.0f, 0.0f);
	m_fLogStopPosY = LOGPOS_DOWN + 160.0f;
}

//=======================================
// ��������
//=======================================
CLog* CLog::Create(CLog::TEXT Type)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CLog* pSample = nullptr;	// �T���v���̃C���X�^���X�𐶐�

	if (pSample == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ
		pSample = new CLog;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ
		assert(false);
		return nullptr;
	}

	if (pSample != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

	  // ����������
		if (FAILED(pSample->Init()))
		{ // �������Ɏ��s�����ꍇ
			assert(false);
			return nullptr;
		}

		// ���̐ݒ菈��
		pSample->SetData(Type);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ
		assert(false);
		return nullptr;
	}

	return pSample;
}

//====================================================================
//�L���[�u�u���b�N�Ƃ̓����蔻�菈��
//====================================================================
bool CLog::DelNumber(void)
{
	m_CreateMax--;

	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//�I�u�W�F�N�g���擾
		CObject* pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			CObject* pObjNext = pObj->GetNext();

			CObject::TYPE type = pObj->GetType();			//��ނ��擾

			if (type == TYPE_LOG)
			{//��ނ��u���b�N�̎�
				CLog* pLog = (CLog*)pObj;

				pLog->DelCreateNumber();
			}
			pObj = pObjNext;
		}
	}

	return false;
}