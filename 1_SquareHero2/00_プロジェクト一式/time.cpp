//============================================
//
//	�^�C���̏��� [time.cpp]
//	Author:sakamoto kai
//
//============================================
#include "time.h"
#include "number.h"

//�}�N����`
#define SPACE_TIME (15.0f)		//�^�C�����m�̌���
#define TIME_POS (D3DXVECTOR3(1168.0f, 430.0f, 0.0f))		//�^�C���̈ʒu

//�ÓI�����o�ϐ��錾
CNumber* CTime::m_apObject[NUM_TIME] = {};
D3DXVECTOR3 CTime::m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
int CTime::m_nTime = 0;
int CTime::m_nCount = 0;
int CTime::m_StartTime = 0;
int CTime::m_nNumber[NUM_TIME] = { 0 };
bool CTime::m_StopTime = false;

//====================================================================
//�R���X�g���N�^
//====================================================================
CTime::CTime(int nPriority) : CObject(nPriority)
{

}

//====================================================================
//�f�X�g���N�^
//====================================================================
CTime::~CTime()
{

}

//====================================================================
//��������
//====================================================================
CTime* CTime::Create()
{
	CTime* pMultiBG = nullptr;

	if (pMultiBG == nullptr)
	{
		//�I�u�W�F�N�g2D�̐���
		pMultiBG = new CTime();
	}

	//�I�u�W�F�N�g�̏���������
	if (FAILED(pMultiBG->Init()))
	{//���������������s�����ꍇ
		return nullptr;
	}

	return pMultiBG;
}

//====================================================================
//�^�C���̏�����
//====================================================================
HRESULT CTime::Init(void)
{
	SetType(CObject::TYPE_TIME);

	SetPos(TIME_POS);

	SetTime(0);

	for (int nCntObject = 0; nCntObject < NUM_TIME; nCntObject++)
	{
		if (m_apObject[nCntObject] == nullptr)
		{
			//�����̐���
			m_apObject[nCntObject] = CNumber::Create();
			m_apObject[nCntObject]->SetNumber(0);

			if (nCntObject < 2)
			{
				m_apObject[nCntObject]->SetPos(D3DXVECTOR3(m_pos.x + (nCntObject * SPACE_TIME) - 3.0f, m_pos.y, m_pos.z));
				m_apObject[nCntObject]->SetWight(20.0f);
				m_apObject[nCntObject]->SetHeight(20.0f);
			}
			else if (nCntObject < 4)
			{
				m_apObject[nCntObject]->SetPos(D3DXVECTOR3(m_pos.x + (nCntObject * SPACE_TIME), m_pos.y, m_pos.z));
				m_apObject[nCntObject]->SetWight(20.0f);
				m_apObject[nCntObject]->SetHeight(20.0f);
			}
			else
			{
				m_apObject[nCntObject]->SetPos(D3DXVECTOR3(m_pos.x + (nCntObject * (SPACE_TIME - 2.0f)) + 8.0f, m_pos.y + 2.0f, m_pos.z));
				m_apObject[nCntObject]->SetWight(18.0f);
				m_apObject[nCntObject]->SetHeight(18.0f);
			}

			m_apObject[nCntObject]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}
	}
	return S_OK;
}

//====================================================================
//�^�C���̏I��
//====================================================================
void CTime::Uninit(void)
{
	SetDeathFlag(true);
}

//====================================================================
//�����|�C���^�̏I��
//====================================================================
void CTime::SetNULL(void)
{
	for (int nCntObject = 0; nCntObject < NUM_TIME; nCntObject++)
	{
		m_apObject[nCntObject] = nullptr;
	}
}

//====================================================================
//�^�C���̍X�V
//====================================================================
void CTime::Update(void)
{
	int nTime = m_nTime / 1000;

	//��
	m_nNumber[0] = (nTime / 60) % 100 / 10;
	m_nNumber[1] = (nTime / 60) % 10 / 1;
	nTime %= 60;

	//�b
	m_nNumber[2] = (nTime) % 100 / 10;
	m_nNumber[3] = (nTime) % 10 / 1;

	//�~���b
	m_nNumber[4] = (m_nTime) % 1000 / 100;
	m_nNumber[5] = (m_nTime) % 100 / 10;

	//m_nNumber[0] = m_nTime % 10000000 / 1000000;
	//m_nNumber[1] = m_nTime % 1000000 / 100000;
	//m_nNumber[2] = m_nTime % 100000 / 10000;
	//m_nNumber[3] = m_nTime % 10000 / 1000;
	//m_nNumber[4] = m_nTime % 1000 / 100;
	//m_nNumber[5] = m_nTime % 100 / 10;

	for (int nCntObject = 0; nCntObject < NUM_TIME; nCntObject++)
	{
		m_apObject[nCntObject]->SetNumber(m_nNumber[nCntObject]);
	}
}

//====================================================================
//�^�C���̕`��
//====================================================================
void CTime::Draw(void)
{

}

//====================================================================
//�^�C���̕`��
//====================================================================
void CTime::FloatSetTime(int Time)
{
	if (m_StopTime == false)
	{
		m_nTime = Time - m_StartTime;
	}
}

//====================================================================
//�^�C���̕`��
//====================================================================
void CTime::SetStartTime(int Time)
{
	m_StartTime = Time;

	for (int nCntObject = 0; nCntObject < NUM_TIME; nCntObject++)
	{
		if (m_apObject[nCntObject] != nullptr)
		{
			m_apObject[nCntObject]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
}

//====================================================================
//�^�C���̏��擾
//====================================================================
int CTime::GetTimeNumber(void)
{
	int nTime = m_nTime / 1000;
	int ReturnTime = 0;

	//��
	ReturnTime += ((nTime / 60) % 100 / 10) * 100000;
	ReturnTime += ((nTime / 60) % 10 / 1) * 10000;
	nTime %= 60;

	//�b
	ReturnTime += ((nTime) % 100 / 10) * 1000;
	ReturnTime += ((nTime) % 10 / 1) * 100;

	//�~���b
	ReturnTime += ((m_nTime) % 1000 / 100) * 10;
	ReturnTime += ((m_nTime) % 100 / 10);

	return ReturnTime;
}