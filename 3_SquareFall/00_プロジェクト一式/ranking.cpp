//============================================
//
//	ランキングの処理 [ranking.cpp]
//	Author:sakamoto kai
//
//============================================
#include "manager.h"
#include "ranking.h"
#include "number.h"

//マクロ定義
#define SPACE_TIME (50.0f)		//タイム同士の隙間
#define TIME_POS (D3DXVECTOR3(1000.0f, 200.0f, 0.0f))		//タイムの位置

//静的メンバ変数宣言
CNumber *CRanking::m_apObject[NUM_TIME][MAX_RANK] = {};
D3DXVECTOR3 CRanking::m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
int CRanking::m_nTime[MAX_RANK] = { 80000,40000,20000,10000,5000 };
int CRanking::m_nCount = 0;
int CRanking::m_StartTime = 0;
int CRanking::m_nNumber[NUM_TIME][MAX_RANK] = { 0 };
bool CRanking::m_StopTime = false;
bool CRanking::m_SetRanking = false;

//====================================================================
//コンストラクタ
//====================================================================
CRanking::CRanking()
{

}

//====================================================================
//デストラクタ
//====================================================================
CRanking::~CRanking()
{

}

//====================================================================
//生成処理
//====================================================================
CRanking *CRanking::Create()
{
	CRanking *pMultiBG = NULL;

	if (pMultiBG == NULL)
	{
		//オブジェクト2Dの生成
		pMultiBG = new CRanking();
	}

	//オブジェクトの初期化処理
	if (FAILED(pMultiBG->Init()))
	{//初期化処理が失敗した場合
		return NULL;
	}

	return pMultiBG;
}

//====================================================================
//ランキングの初期化
//====================================================================
HRESULT CRanking::Init(void)
{
	SetType(CObject::TYPE_TIME);

	SetPos(TIME_POS);

	for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (int nCntObject = 0; nCntObject < NUM_TIME; nCntObject++)
		{
			if (m_apObject[nCntObject][nCntRank] == NULL)
			{
				//数字の生成
				m_apObject[nCntObject][nCntRank] = CNumber::Create();
				m_apObject[nCntObject][nCntRank]->SetNumber(0);
				m_apObject[nCntObject][nCntRank]->SetPos(D3DXVECTOR3(m_pos.x + (nCntObject * 60.0f), m_pos.y + (nCntRank * 100.0f), m_pos.z));
				m_apObject[nCntObject][nCntRank]->SetWight(100.0f);
				m_apObject[nCntObject][nCntRank]->SetHeight(100.0f);
			}
		}
	}

	LoadRanking();

	return S_OK;
}

//====================================================================
//タイムの終了
//====================================================================
void CRanking::Uninit(void)
{

}

//====================================================================
//タイムの終了
//====================================================================
void CRanking::SetNULL(void)
{
	for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (int nCntObject = 0; nCntObject < NUM_TIME; nCntObject++)
		{
			if (m_apObject[nCntObject][nCntRank] != NULL)
			{
				m_apObject[nCntObject][nCntRank]->Uninit();
				m_apObject[nCntObject][nCntRank] = NULL;
			}
		}
	}
}


//====================================================================
//タイムの更新
//====================================================================
void CRanking::Update(void)
{
	for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		for (int nCntObject = 0; nCntObject < NUM_TIME; nCntObject++)
		{
			if (m_apObject[nCntObject] != NULL)
			{
				m_apObject[nCntObject][nCntRank]->SetPos(D3DXVECTOR3(m_pos.x + (nCntObject * 60.0f), m_pos.y + (nCntRank * 85.0f), m_pos.z));
			}
		}
	}

	for (int nCntRank = 0; nCntRank < MAX_RANK; nCntRank++)
	{
		m_nNumber[0][nCntRank] = m_nTime[nCntRank] % 100000000 / 10000000;
		m_nNumber[1][nCntRank] = m_nTime[nCntRank] % 10000000 / 1000000;
		m_nNumber[2][nCntRank] = m_nTime[nCntRank] % 1000000 / 100000;
		m_nNumber[3][nCntRank] = m_nTime[nCntRank] % 100000 / 10000;
		m_nNumber[4][nCntRank] = m_nTime[nCntRank] % 10000 / 1000;
		m_nNumber[5][nCntRank] = m_nTime[nCntRank] % 1000 / 100;
		m_nNumber[6][nCntRank] = m_nTime[nCntRank] % 100 / 10;
		m_nNumber[7][nCntRank] = m_nTime[nCntRank] % 10 / 1;

		for (int nCntObject = 0; nCntObject < NUM_TIME; nCntObject++)
		{
			m_apObject[nCntObject][nCntRank]->SetNumber(m_nNumber[nCntObject][nCntRank]);
			//m_apObject[nCntObject][nCntRank]->SetNumber(nCntObject * 2 + nCntRank * 2);
		}
	}
}

//====================================================================
//タイムの描画
//====================================================================
void CRanking::Draw(void)
{

}

//====================================================================
//タイムの描画
//====================================================================
void CRanking::FloatSetTime(int Time)
{
	if (m_StopTime == false)
	{
		m_nTime[0] = Time - m_StartTime;
	}
}

//====================================================================
//ランキングの設定処理
//====================================================================
void CRanking::SetRanking(int nRanKing)
{
	int nCount1;
	int nCount2;
	int nData;

	if (nRanKing > m_nTime[MAX_RANK - 1])
	{
		m_nTime[MAX_RANK - 1] = nRanKing;

		for (nCount1 = 0; nCount1 < MAX_RANK; nCount1++)
		{
			for (nCount2 = nCount1; nCount2 < MAX_RANK; nCount2++)
			{
				if (m_nTime[nCount1] < m_nTime[nCount2])
				{
					nData = m_nTime[nCount1];
					m_nTime[nCount1] = m_nTime[nCount2];
					m_nTime[nCount2] = nData;
				}
			}
		}
	}
}

//====================================================================
//保存処理
//====================================================================
void CRanking::SaveRanking(void)
{
	FILE *pFile; //ファイルポインタを宣言

	//ファイルを開く
	pFile = fopen("data\\TXT\\Ranking", "w");

	if (pFile != NULL)
	{//ファイルが開けた場合

		for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
		{
			fprintf(pFile, "%d\n", m_nTime[nCnt]);
		}

		fclose(pFile);
	}
	else
	{//ファイルが開けなかった場合
		printf("***ファイルを開けませんでした***\n");
	}
}

//====================================================================
//マップを全て埋めて生成
//====================================================================
void CRanking::LoadRanking(void)
{
	FILE *pFile; //ファイルポインタを宣言

	//ファイルを開く
	pFile = fopen("data\\TXT\\Ranking", "r");

	if (pFile != NULL)
	{//ファイルが開けた場合

		for (int nCnt = 0; nCnt < MAX_RANK; nCnt++)
		{
			fscanf(pFile, "%d", &m_nTime[nCnt]);
		}
		fclose(pFile);
	}
	else
	{//ファイルが開けなかった場合
		printf("***ファイルを開けませんでした***\n");
	}
}