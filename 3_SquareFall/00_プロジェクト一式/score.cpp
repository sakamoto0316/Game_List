//============================================
//
//	スコアの処理 [score.cpp]
//	Author:sakamoto kai
//
//============================================
#include "score.h"
#include "number.h"

//マクロ定義
#define SPACE_SCORE (50.0f)		//スコア同士の隙間
#define NUMBER_WIGHT (100.0f)	//数字の横幅
#define NUMBER_HEIGHT (100.0f)	//数字の縦幅

//静的メンバ変数宣言

//====================================================================
//コンストラクタ
//====================================================================
CScore::CScore()
{
	for (int nCnt = 0; nCnt < NUM_SCORE; nCnt++)
	{
		m_apObject[nCnt] = NULL;
		m_nNumber[nCnt] = 0;
	}

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nScore = 0;
	m_nWight = NUMBER_WIGHT;
	m_Height = NUMBER_HEIGHT;
}

//====================================================================
//デストラクタ
//====================================================================
CScore::~CScore()
{

}

//====================================================================
//生成処理
//====================================================================
CScore *CScore::Create()
{
	CScore *pMultiBG = NULL;

	if (pMultiBG == NULL)
	{
		//オブジェクト2Dの生成
		pMultiBG = new CScore();
	}

	//オブジェクトの初期化処理
	if (FAILED(pMultiBG->Init()))
	{//初期化処理が失敗した場合
		return NULL;
	}

	return pMultiBG;
}

//====================================================================
//スコアの初期化
//====================================================================
HRESULT CScore::Init(void)
{
	SetType(CObject::TYPE_SCORE);

	for (int nCntObject = 0; nCntObject < NUM_SCORE; nCntObject++)
	{
		if (m_apObject[nCntObject] == NULL)
		{
			//数字の生成
			m_apObject[nCntObject] = CNumber::Create();
			m_apObject[nCntObject]->SetPos(D3DXVECTOR3(m_pos.x + (nCntObject * m_nWight * 0.6f), m_pos.y, m_pos.z));
			m_apObject[nCntObject]->SetWight(m_nWight);
			m_apObject[nCntObject]->SetHeight(m_Height);
			m_apObject[nCntObject]->SetNumber(0);
		}
	}
	return S_OK;
}

//====================================================================
//スコアの終了
//====================================================================
void CScore::Uninit(void)
{
	SetDeathFlag(true);
}

//====================================================================
//終了処理
//====================================================================
void CScore::SetNULL(void)
{
	for (int nCntObject = 0; nCntObject < NUM_SCORE; nCntObject++)
	{
		if (m_apObject[nCntObject] != NULL)
		{
			//数字の生成
			m_apObject[nCntObject] = NULL;
		}
	}
}

//====================================================================
//スコアの更新
//====================================================================
void CScore::Update(void)
{
	for (int nCntObject = 0; nCntObject < NUM_SCORE; nCntObject++)
	{
		if (m_apObject[nCntObject] != NULL)
		{
			m_apObject[nCntObject]->SetPos(D3DXVECTOR3(m_pos.x + (nCntObject * m_nWight * 0.6f), m_pos.y, m_pos.z));
			m_apObject[nCntObject]->SetWight(m_nWight);
			m_apObject[nCntObject]->SetHeight(m_Height);
		}
	}
}

//====================================================================
//スコアの描画
//====================================================================
void CScore::Draw(void)
{

}

//====================================================================
//スコアの設定処理
//====================================================================
void CScore::SetScore(int Score)
{
	m_nScore = Score;

	m_nNumber[0] = m_nScore % 100000000 / 10000000;
	m_nNumber[1] = m_nScore % 10000000 / 1000000;
	m_nNumber[2] = m_nScore % 1000000 / 100000;
	m_nNumber[3] = m_nScore % 100000 / 10000;
	m_nNumber[4] = m_nScore % 10000 / 1000;
	m_nNumber[5] = m_nScore % 1000 / 100;
	m_nNumber[6] = m_nScore % 100 / 10;
	m_nNumber[7] = m_nScore % 10 / 1;

	for (int nCntObject = 0; nCntObject < NUM_SCORE; nCntObject++)
	{
		m_apObject[nCntObject]->SetNumber(m_nNumber[nCntObject]);
	}
}

//====================================================================
//スコアの設定処理
//====================================================================
void CScore::AddScore(int Add)
{
	m_nScore += Add;

	m_nNumber[0] = m_nScore % 100000000 / 10000000;
	m_nNumber[1] = m_nScore % 10000000 / 1000000;
	m_nNumber[2] = m_nScore % 1000000 / 100000;
	m_nNumber[3] = m_nScore % 100000 / 10000;
	m_nNumber[4] = m_nScore % 10000 / 1000;
	m_nNumber[5] = m_nScore % 1000 / 100;
	m_nNumber[6] = m_nScore % 100 / 10;
	m_nNumber[7] = m_nScore % 10 / 1;

	for (int nCntObject = 0; nCntObject < NUM_SCORE; nCntObject++)
	{
		m_apObject[nCntObject]->SetNumber(m_nNumber[nCntObject]);
	}
}