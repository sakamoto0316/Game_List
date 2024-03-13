//============================================
//
//	�����L���O�̏��� [ranking.cpp]
//	Author:sakamoto kai
//
//============================================
#include "manager.h"
#include "ranking.h"
#include "number.h"

//�}�N����`
#define SPACE_TIME (50.0f)		//�����L���O���m�̌���
#define TIME_POS (D3DXVECTOR3(1000.0f, 200.0f, 0.0f))		//�����L���O�̈ʒu
#define RANKING_SIZE (D3DXVECTOR3(35.0f, 35.0f, 0.0f))		//�����L���O�̑傫��
#define NUMBER_DISTANCE (25.0f)		//�������m�̕�
#define RANKING_DISTANCE (48.0f)	//�����L���O���m�̕�

//�ÓI�����o�ϐ��錾

//====================================================================
//�R���X�g���N�^
//====================================================================
CRanking::CRanking(int nPriority) : CObject(nPriority)
{
	for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (int nCntTime = 0; nCntTime < NUM_TIME; nCntTime++)
		{
			m_apObject[nCntTime][nCntRank] = nullptr;
			m_nNumber[nCntTime][nCntRank] = 0;
		}
	}
	m_nTime[0] = 80000;
	m_nTime[1] = 40000;
	m_nTime[2] = 20000;
	m_nTime[3] = 10000;
	m_nTime[4] = 5000;

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCount = 0;
	m_StartTime = 0;
	m_StopTime = false;
	m_SetRanking = false;
	m_bTime = false;
}

//====================================================================
//�f�X�g���N�^
//====================================================================
CRanking::~CRanking()
{

}

//====================================================================
//��������
//====================================================================
CRanking *CRanking::Create(char* pModelName)
{
	CRanking *pMultiBG = nullptr;

	if (pMultiBG == nullptr)
	{
		//�I�u�W�F�N�g2D�̐���
		pMultiBG = new CRanking();
	}

	pMultiBG->SetTextName(pModelName);

	//�I�u�W�F�N�g�̏���������
	if (FAILED(pMultiBG->Init()))
	{//���������������s�����ꍇ
		return nullptr;
	}

	return pMultiBG;
}

//====================================================================
//�����L���O�̏�����
//====================================================================
HRESULT CRanking::Init(void)
{
	SetType(CObject::TYPE_TIME);

	SetPos(TIME_POS);

	for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (int nCntObject = 0; nCntObject < NUM_TIME; nCntObject++)
		{
			if (m_apObject[nCntObject][nCntRank] == nullptr)
			{
				//�����̐���
				m_apObject[nCntObject][nCntRank] = CNumber::Create();
				m_apObject[nCntObject][nCntRank]->SetNumber(0);
				m_apObject[nCntObject][nCntRank]->SetPos(D3DXVECTOR3(m_pos.x + (nCntObject * NUMBER_DISTANCE), m_pos.y + (nCntRank * RANKING_DISTANCE), m_pos.z));
				m_apObject[nCntObject][nCntRank]->SetWight(RANKING_SIZE.x);
				m_apObject[nCntObject][nCntRank]->SetHeight(RANKING_SIZE.y);
			}
		}
	}

	LoadRanking();

	return S_OK;
}

//====================================================================
//�����L���O�̏I��
//====================================================================
void CRanking::Uninit(void)
{

}

//====================================================================
//�����L���O�̏I��
//====================================================================
void CRanking::SetNULL(void)
{
	for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (int nCntObject = 0; nCntObject < NUM_TIME; nCntObject++)
		{
			if (m_apObject[nCntObject][nCntRank] != nullptr)
			{
				m_apObject[nCntObject][nCntRank]->Uninit();
				m_apObject[nCntObject][nCntRank] = nullptr;
			}
		}
	}
}

//====================================================================
//�����L���O�̏I��
//====================================================================
void CRanking::SetUseTime(bool Set)
{
	m_bTime = Set;

	if (m_bTime == true)
	{
		for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
		{
			for (int nCntObject = 0; nCntObject < NUM_TIME; nCntObject++)
			{
				if (m_apObject[nCntObject][nCntRank] != nullptr)
				{
					if (nCntObject < NUM_TIME - 4)
					{
						//�����̐���
						m_apObject[nCntObject][nCntRank]->SetPos(D3DXVECTOR3(m_pos.x + (nCntObject * NUMBER_DISTANCE - 4.0f), m_pos.y + (nCntRank * RANKING_DISTANCE), m_pos.z));
						m_apObject[nCntObject][nCntRank]->SetWight(RANKING_SIZE.x);
						m_apObject[nCntObject][nCntRank]->SetHeight(RANKING_SIZE.y);
					}
					else if (nCntObject < NUM_TIME - 2)
					{
						//�����̐���
						m_apObject[nCntObject][nCntRank]->SetPos(D3DXVECTOR3(m_pos.x + (nCntObject * NUMBER_DISTANCE), m_pos.y + (nCntRank * RANKING_DISTANCE), m_pos.z));
						m_apObject[nCntObject][nCntRank]->SetWight(RANKING_SIZE.x);
						m_apObject[nCntObject][nCntRank]->SetHeight(RANKING_SIZE.y);
					}
					else
					{
						//�����̐���
						m_apObject[nCntObject][nCntRank]->SetPos(D3DXVECTOR3(
							m_pos.x + (nCntObject * NUMBER_DISTANCE + RANKING_SIZE.x * 0.2f), 
							m_pos.y + (nCntRank * RANKING_DISTANCE + RANKING_SIZE.y * 0.2f), 
							m_pos.z));
						m_apObject[nCntObject][nCntRank]->SetWight(RANKING_SIZE.x * 0.8f);
						m_apObject[nCntObject][nCntRank]->SetHeight(RANKING_SIZE.y * 0.8f);
					}
				}
			}
		}
	}
}

//====================================================================
//�����L���O�̍X�V
//====================================================================
void CRanking::Update(void)
{
	if (m_bTime == true)
	{
		for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
		{
			for (int nCntObject = 0; nCntObject < NUM_TIME; nCntObject++)
			{
				if (m_apObject[nCntObject][nCntRank] != nullptr)
				{
					if (nCntObject < NUM_TIME - 4)
					{
						//�����̐���
						m_apObject[nCntObject][nCntRank]->SetPos(D3DXVECTOR3(m_pos.x + (nCntObject * NUMBER_DISTANCE - 4.0f), m_pos.y + (nCntRank * RANKING_DISTANCE), m_pos.z));
					}
					else if (nCntObject < NUM_TIME - 2)
					{
						m_apObject[nCntObject][nCntRank]->SetPos(D3DXVECTOR3(m_pos.x + (nCntObject * NUMBER_DISTANCE), m_pos.y + (nCntRank * RANKING_DISTANCE), m_pos.z));
					}
					else
					{
						m_apObject[nCntObject][nCntRank]->SetPos(D3DXVECTOR3(
							m_pos.x + (nCntObject * NUMBER_DISTANCE + RANKING_SIZE.x * 0.2f),
							m_pos.y + (nCntRank * RANKING_DISTANCE + RANKING_SIZE.y * 0.2f),
							m_pos.z));
					}
				}
			}
		}
	}
	else
	{
		for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
		{
			for (int nCntObject = 0; nCntObject < NUM_TIME; nCntObject++)
			{
				if (m_apObject[nCntObject] != nullptr)
				{
					m_apObject[nCntObject][nCntRank]->SetPos(D3DXVECTOR3(m_pos.x + (nCntObject * NUMBER_DISTANCE), m_pos.y + (nCntRank * RANKING_DISTANCE), m_pos.z));
				}
			}
		}
	}

	for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		m_nNumber[0][nCntRank] = m_nTime[nCntRank] % 1000000 / 100000;
		m_nNumber[1][nCntRank] = m_nTime[nCntRank] % 100000 / 10000;
		m_nNumber[2][nCntRank] = m_nTime[nCntRank] % 10000 / 1000;
		m_nNumber[3][nCntRank] = m_nTime[nCntRank] % 1000 / 100;
		m_nNumber[4][nCntRank] = m_nTime[nCntRank] % 100 / 10;
		m_nNumber[5][nCntRank] = m_nTime[nCntRank] % 10 / 1;

		for (int nCntObject = 0; nCntObject < NUM_TIME; nCntObject++)
		{
			m_apObject[nCntObject][nCntRank]->SetNumber(m_nNumber[nCntObject][nCntRank]);
			//m_apObject[nCntObject][nCntRank]->SetNumber(nCntObject * 2 + nCntRank * 2);
		}
	}
}

//====================================================================
//�����L���O�̕`��
//====================================================================
void CRanking::Draw(void)
{

}

//====================================================================
//�����L���O�̕`��
//====================================================================
void CRanking::FloatSetTime(int Time)
{
	if (m_StopTime == false)
	{
		m_nTime[0] = Time - m_StartTime;
	}
}

//====================================================================
//�����L���O�̐ݒ菈��
//====================================================================
void CRanking::SetRanking(int nRanKing)
{
	int nCount1;
	int nCount2;
	int nData;

	if (nRanKing < m_nTime[MAX_RANK - 1])
	{
		m_nTime[MAX_RANK - 1] = nRanKing;

		for (nCount1 = 0; nCount1 < MAX_RANK; nCount1++)
		{
			for (nCount2 = nCount1; nCount2 < MAX_RANK; nCount2++)
			{
				if (m_nTime[nCount1] > m_nTime[nCount2])
				{
					nData = m_nTime[nCount1];
					m_nTime[nCount1] = m_nTime[nCount2];
					m_nTime[nCount2] = nData;
				}
			}
		}
	}

	//if (nRanKing > m_nTime[MAX_RANK - 1])
	//{
	//	m_nTime[MAX_RANK - 1] = nRanKing;

	//	for (nCount1 = 0; nCount1 < MAX_RANK; nCount1++)
	//	{
	//		for (nCount2 = nCount1; nCount2 < MAX_RANK; nCount2++)
	//		{
	//			if (m_nTime[nCount1] < m_nTime[nCount2])
	//			{
	//				nData = m_nTime[nCount1];
	//				m_nTime[nCount1] = m_nTime[nCount2];
	//				m_nTime[nCount2] = nData;
	//			}
	//		}
	//	}
	//}
}

//====================================================================
//�ۑ�����
//====================================================================
void CRanking::SaveRanking(void)
{
	FILE *pFile; //�t�@�C���|�C���^��錾

	//�t�@�C�����J��
	pFile = fopen(m_cTextName, "w");
	
	if (pFile != nullptr)
	{//�t�@�C�����J�����ꍇ

		for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
		{
			fprintf(pFile, "%d\n", m_nTime[nCnt]);
		}

		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		printf("***�t�@�C�����J���܂���ł���***\n");
	}
}

//====================================================================
//�}�b�v��S�Ė��߂Đ���
//====================================================================
void CRanking::LoadRanking(void)
{
	FILE *pFile; //�t�@�C���|�C���^��錾

	//�t�@�C�����J��
	pFile = fopen(m_cTextName, "r");

	if (pFile != nullptr)
	{//�t�@�C�����J�����ꍇ

		for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
		{
			fscanf(pFile, "%d", &m_nTime[nCnt]);
		}
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		printf("***�t�@�C�����J���܂���ł���***\n");
	}
}