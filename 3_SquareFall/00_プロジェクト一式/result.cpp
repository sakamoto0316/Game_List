//============================================
//
//	リザルト画面 [result.cpp]
//	Author:sakamoto kai
//
//============================================
#include "result.h"
#include "manager.h"
#include "fade.h"
#include "input.h"
#include "object2D.h"
#include "texture.h"
#include "ranking.h"
#include "sound.h"
#include "score.h"
#include "break_block3D.h"

//マクロ定義
#define START_OK ("STARTSETSTAGE")	//スタートメッセージがあるかどうかの確認
#define END_SET_OK ("ENDSETSTAGE")	//エンドメッセージがあるかどうかの確認
#define SCORE_POSX (300.0f)
#define SCORE_MOVEX (20.1f)

//静的メンバ変数宣言
CObject2D *CResult::m_pResult = NULL;
CRanking *CResult::m_pRanking = NULL;
CScore *CResult::m_NormalScore = NULL;
CScore *CResult::m_MaxConbo = NULL;
CScore *CResult::m_MaxFall = NULL;
CScore *CResult::m_Depth = NULL;
CScore *CResult::m_TotalScore = NULL;
CObject2D *CResult::m_NormalScoreText = NULL;
CObject2D *CResult::m_MaxConboText = NULL;
CObject2D *CResult::m_MaxFallText = NULL;
CObject2D *CResult::m_DepthText = NULL;
CObject2D *CResult::m_TotalScoreText = NULL;
CObject2D *CResult::m_RankText = NULL;
CObject2D *CResult::m_ResultText = NULL;
CObject2D *CResult::m_RankingText = NULL;
float CResult::m_NormalScorePosX = -1000.0f;
float CResult::m_MaxConboPosX = -1000.0f;
float CResult::m_MaxFallPosX = -1000.0f;
float CResult::m_DepthPosX = -1000.0f;
float CResult::m_TotalScorePosX = SCORE_POSX;
float CResult::m_ResultPosX = 640.0f;
float CResult::RankingPosX = 1500.0f;
bool CResult::m_Appear = false;
int CResult::m_AddScoreCount = 0;
int CResult::m_AddTotalScore = 0;

//====================================================================
//コンストラクタ
//====================================================================
CResult::CResult()
{
	m_NormalScorePosX = -1000.0f;
	m_MaxConboPosX = -1000.0f;
	m_MaxFallPosX = -1000.0f;
	m_DepthPosX = -1000.0f;

	if (CManager::GetInstance()->GetSetScoreResult() == true)
	{
		m_TotalScorePosX = SCORE_POSX;
		m_ResultPosX = 640.0f;
		RankingPosX = 1550.0f;
		m_Appear = true;
		m_AddScoreCount = 0;
	}
	else
	{
		m_TotalScorePosX = -1000.0f;
		m_ResultPosX = -1000.0;
		RankingPosX = 500.0f;
		m_Appear = false;
		m_AddScoreCount = 6;
	}

	m_AddTotalScore = 0;
}

//====================================================================
//デストラクタ
//====================================================================
CResult::~CResult()
{

}

//====================================================================
//初期化処理
//====================================================================
HRESULT CResult::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_BGM_RESULT);

	LoadBlock("data\\TXT\\Result02", D3DXVECTOR3(-440.0f - 700.0f, 400.0f, 200.0f));
	LoadBlock("data\\TXT\\Result02", D3DXVECTOR3(-440.0f + 700.0f, 400.0f, 200.0f));

	m_pRanking = CRanking::Create();
	//m_pResult = CObject2D::Create();
	//m_pResult->SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	//m_pResult->SetWight(1280.0f);
	//m_pResult->SetHeight(720.0f);

	m_NormalScore = CScore::Create();
	m_NormalScore->SetPos(D3DXVECTOR3(m_NormalScorePosX + 150.0f, 250.0f, 0.0f));
	m_NormalScore->SetScore(CManager::GetInstance()->GetEndScore());

	m_MaxConbo = CScore::Create();
	m_MaxConbo->SetPos(D3DXVECTOR3(m_MaxConboPosX + 150.0f, 350.0f, 0.0f));
	m_MaxConbo->SetScore(CManager::GetInstance()->GetEndCombo() * 1000);

	m_MaxFall = CScore::Create();
	m_MaxFall->SetPos(D3DXVECTOR3(m_MaxFallPosX + 150.0f, 450.0f, 0.0f));
	m_MaxFall->SetScore((CManager::GetInstance()->GetEndFall() / 60) * 1000);

	m_Depth = CScore::Create();
	m_Depth->SetPos(D3DXVECTOR3(m_DepthPosX + 150.0f, 550.0f, 0.0f));
	m_Depth->SetScore((int)(CManager::GetInstance()->GetEndDepth()));

	m_TotalScore = CScore::Create();
	m_TotalScore->SetPos(D3DXVECTOR3(m_TotalScorePosX + 150.0f, 670.0f, 0.0f));
	m_TotalScore->SetScore(0);

	m_NormalScoreText = CObject2D::Create();
	m_NormalScoreText->SetPos(D3DXVECTOR3(m_NormalScorePosX, 250.0f, 0.0f));
	m_NormalScoreText->SetWight(400.0f);
	m_NormalScoreText->SetHeight(150.0f);
	m_NormalScoreText->SetTexture("data\\TEXTURE\\NormalScore.png");

	m_MaxConboText = CObject2D::Create();
	m_MaxConboText->SetPos(D3DXVECTOR3(m_MaxConboPosX, 350.0f, 0.0f));
	m_MaxConboText->SetWight(400.0f);
	m_MaxConboText->SetHeight(150.0f);
	m_MaxConboText->SetTexture("data\\TEXTURE\\ComboScore.png");

	m_MaxFallText = CObject2D::Create();
	m_MaxFallText->SetPos(D3DXVECTOR3(m_MaxFallPosX, 450.0f, 0.0f));
	m_MaxFallText->SetWight(400.0f);
	m_MaxFallText->SetHeight(150.0f);
	m_MaxFallText->SetTexture("data\\TEXTURE\\FallScore.png");

	m_DepthText = CObject2D::Create();
	m_DepthText->SetPos(D3DXVECTOR3(m_DepthPosX, 550.0f, 0.0f));
	m_DepthText->SetWight(400.0f);
	m_DepthText->SetHeight(150.0f);
	m_DepthText->SetTexture("data\\TEXTURE\\DepthScore.png");

	m_TotalScoreText = CObject2D::Create();
	m_TotalScoreText->SetPos(D3DXVECTOR3(m_TotalScorePosX, 670.0f, 0.0f));
	m_TotalScoreText->SetWight(400.0f);
	m_TotalScoreText->SetHeight(150.0f);
	m_TotalScoreText->SetTexture("data\\TEXTURE\\TotalScore.png");

	m_RankText = CObject2D::Create();
	m_RankText->SetPos(D3DXVECTOR3(RankingPosX, 670.0f, 0.0f));
	m_RankText->SetWight(220.0f);
	m_RankText->SetHeight(450.0f);
	m_RankText->SetTexture("data\\TEXTURE\\RANKING_TEXT.png");

	m_ResultText = CObject2D::Create();
	m_ResultText->SetPos(D3DXVECTOR3(640.0f, 100.0f, 0.0f));
	m_ResultText->SetWight(600.0f);
	m_ResultText->SetHeight(420.0f);
	m_ResultText->SetTexture("data\\TEXTURE\\RESULT_TEXT.png");

	m_RankingText = CObject2D::Create();
	m_RankingText->SetPos(D3DXVECTOR3(RankingPosX, 100.0f, 0.0f));
	m_RankingText->SetWight(700.0f);
	m_RankingText->SetHeight(400.0f);
	m_RankingText->SetTexture("data\\TEXTURE\\RANKING_TEXT01.png");

	//m_pResult->SetIdx(pTexture->Regist("data\\TEXTURE\\Result.png"));

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CResult::Uninit(void)
{
	//全てのオブジェクトの破棄
	CObject::ReleaseAll();
}

//====================================================================
//更新処理
//====================================================================
void CResult::Update(void)
{
	switch (m_AddScoreCount)
	{
	case 0:
		if (m_NormalScorePosX > SCORE_POSX)
		{
			m_NormalScorePosX = SCORE_POSX;
			m_AddScoreCount++;
		}
		else if(m_NormalScorePosX < SCORE_POSX)
		{
			m_NormalScorePosX += SCORE_MOVEX;
		}
		break;
	case 1:
		if (m_MaxConboPosX > SCORE_POSX)
		{
			m_MaxConboPosX = SCORE_POSX;
			m_AddScoreCount++;
		}
		else if (m_MaxConboPosX < SCORE_POSX)
		{
			m_MaxConboPosX += SCORE_MOVEX;
		}
		break;
	case 2:
		if (m_MaxFallPosX > SCORE_POSX)
		{
			m_MaxFallPosX = SCORE_POSX;
			m_AddScoreCount++;
		}
		else if (m_MaxFallPosX < SCORE_POSX)
		{
			m_MaxFallPosX += SCORE_MOVEX;
		}
		break;
	case 3:
		if (m_DepthPosX > SCORE_POSX)
		{
			m_DepthPosX = SCORE_POSX;
			m_AddScoreCount++;
		}
		else if (m_DepthPosX < SCORE_POSX)
		{
			m_DepthPosX += SCORE_MOVEX;
		}
		break;
	case 5:
		if (m_NormalScorePosX < -1000.0f)
		{
			m_NormalScorePosX = -1000.0f;
		}
		else if (m_NormalScorePosX > -1000.0f)
		{
			m_NormalScorePosX -= SCORE_MOVEX;
			m_MaxConboPosX -= SCORE_MOVEX;
			m_MaxFallPosX -= SCORE_MOVEX;
			m_DepthPosX -= SCORE_MOVEX;
			m_ResultPosX -= SCORE_MOVEX;
		}

		if (RankingPosX < 500.0f)
		{
			RankingPosX = 500.0f;
			m_AddScoreCount++;
		}
		else if (RankingPosX > 500.0f)
		{
			RankingPosX -= SCORE_MOVEX;
		}
		break;
	}

	switch (m_AddScoreCount)
	{
	case 0:
		if (m_AddTotalScore > m_NormalScore->GetScore())
		{
			m_AddTotalScore = m_NormalScore->GetScore();
		}
		else if (m_AddTotalScore < m_NormalScore->GetScore())
		{
			m_AddTotalScore += 507;
		}
		break;
	case 1:
		if (m_AddTotalScore > m_NormalScore->GetScore() + m_MaxConbo->GetScore())
		{
			m_AddTotalScore = m_NormalScore->GetScore() + m_MaxConbo->GetScore();
		}
		else if (m_AddTotalScore < m_NormalScore->GetScore() + m_MaxConbo->GetScore())
		{
			m_AddTotalScore += 507;
		}
		break;
	case 2:
		if (m_AddTotalScore > m_NormalScore->GetScore() + m_MaxConbo->GetScore() + m_MaxFall->GetScore())
		{
			m_AddTotalScore = m_NormalScore->GetScore() + m_MaxConbo->GetScore() + m_MaxFall->GetScore();
		}
		else if (m_AddTotalScore < m_NormalScore->GetScore() + m_MaxConbo->GetScore() + m_MaxFall->GetScore())
		{
			m_AddTotalScore += 507;
		}
		break;
	case 3:
		if (m_AddTotalScore > m_NormalScore->GetScore() + m_MaxConbo->GetScore() + m_MaxFall->GetScore() + m_Depth->GetScore())
		{
			m_AddTotalScore = m_NormalScore->GetScore() + m_MaxConbo->GetScore() + m_MaxFall->GetScore() + m_Depth->GetScore();
		}
		else if (m_AddTotalScore < m_NormalScore->GetScore() + m_MaxConbo->GetScore() + m_MaxFall->GetScore() + m_Depth->GetScore())
		{
			m_AddTotalScore += 507;
		}
		break;
	default:
		if (m_AddTotalScore > m_NormalScore->GetScore() + m_MaxConbo->GetScore() + m_MaxFall->GetScore() + m_Depth->GetScore())
		{
			m_AddTotalScore = m_NormalScore->GetScore() + m_MaxConbo->GetScore() + m_MaxFall->GetScore() + m_Depth->GetScore();
		}
		else if (m_AddTotalScore < m_NormalScore->GetScore() + m_MaxConbo->GetScore() + m_MaxFall->GetScore() + m_Depth->GetScore())
		{
			m_AddTotalScore += 507;
		}
		break;
	}
	m_TotalScore->SetScore(m_AddTotalScore);

	if (CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true ||
		CManager::GetInstance()->GetInputJoyPad()->GetTrigger(CInputJoypad::BUTTON_A, 0) == true ||
		CManager::GetInstance()->GetInputJoyPad()->GetTrigger(CInputJoypad::BUTTON_B, 0) == true)
	{
		switch (m_AddScoreCount)
		{
		case 0:
			m_AddTotalScore = m_NormalScore->GetScore();
			m_NormalScorePosX = SCORE_POSX;
			m_AddScoreCount++;
			break;
		case 1:
			m_MaxConboPosX = SCORE_POSX;
			m_AddScoreCount++;
			m_AddTotalScore = m_NormalScore->GetScore() + m_MaxConbo->GetScore();
			break;
		case 2:
			m_MaxFallPosX = SCORE_POSX;
			m_AddScoreCount++;
			m_AddTotalScore = m_NormalScore->GetScore() + m_MaxConbo->GetScore() + m_MaxFall->GetScore();
			break;
		case 3:
			m_DepthPosX = SCORE_POSX;
			m_AddScoreCount++;
			m_AddTotalScore = m_NormalScore->GetScore() + m_MaxConbo->GetScore() + m_MaxFall->GetScore() + m_Depth->GetScore();
			break;
		case 4:
			m_AddScoreCount++;
			m_AddTotalScore = m_NormalScore->GetScore() + m_MaxConbo->GetScore() + m_MaxFall->GetScore() + m_Depth->GetScore();
			m_pRanking->SetRanking(m_AddTotalScore);
			break;
		case 5:
			m_NormalScorePosX = -1000.0f;
			m_MaxConboPosX = -1000.0f;
			m_MaxFallPosX = -1000.0f;
			m_DepthPosX = -1000.0f;
			m_ResultPosX = -1000.0f;
			RankingPosX = 500.0f;
			m_AddScoreCount++;
			break;
		default:
			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_ENTER_PUSH);
			CRanking::SaveRanking();
			CFade::SetFade(CScene::MODE_TITLE);
			break;
		}
	}

	//スコア情報の位置設定
	m_NormalScore->SetPos(D3DXVECTOR3(m_NormalScorePosX + 150.0f, 250.0f, 0.0f));
	m_MaxConbo->SetPos(D3DXVECTOR3(m_MaxConboPosX + 150.0f, 350.0f, 0.0f));
	m_MaxFall->SetPos(D3DXVECTOR3(m_MaxFallPosX + 150.0f, 450.0f, 0.0f));
	m_Depth->SetPos(D3DXVECTOR3(m_DepthPosX + 150.0f, 550.0f, 0.0f));
	m_TotalScore->SetPos(D3DXVECTOR3(m_TotalScorePosX + 150.0f, 670.0f, 0.0f));
	m_NormalScoreText->SetPos(D3DXVECTOR3(m_NormalScorePosX, 250.0f, 0.0f));
	m_MaxConboText->SetPos(D3DXVECTOR3(m_MaxConboPosX - 80.0f, 350.0f, 0.0f));
	m_MaxFallText->SetPos(D3DXVECTOR3(m_MaxFallPosX - 90.0f, 450.0f, 0.0f));
	m_DepthText->SetPos(D3DXVECTOR3(m_DepthPosX - 90.0f, 550.0f, 0.0f));
	m_TotalScoreText->SetPos(D3DXVECTOR3(m_TotalScorePosX, 670.0f, 0.0f));
	m_ResultText->SetPos(D3DXVECTOR3(m_ResultPosX, 100.0f, 0.0f));

	m_pRanking->SetPos(D3DXVECTOR3(RankingPosX - 40.0f, 200.0f, 0.0f));
	m_RankText->SetPos(D3DXVECTOR3(RankingPosX - 150.0f, 370.0f, 0.0f));
	m_RankingText->SetPos(D3DXVECTOR3(RankingPosX + 100.0f, 100.0f, 0.0f));
}

//====================================================================
//描画処理
//====================================================================
void CResult::Draw(void)
{

}

//====================================================================
//マップを全て埋めて生成
//====================================================================
void CResult::LoadBlock(char *Name, D3DXVECTOR3 pos)
{
	FILE *pFile; //ファイルポインタを宣言

	//ファイルを開く
	pFile = fopen(Name, "r");

	if (pFile != NULL)
	{//ファイルが開けた場合

		int nCreateNumber = 0;
		int nWightNumber = 0;
		int nHeightNumber = 0;

		char aString[128] = {};			//ゴミ箱
		char aStartMessage[32] = {};	//スタートメッセージ
		char aSetMessage[32] = {};		//セットメッセージ
		char aEndMessage[32] = {};		//終了メッセージ
		char aType[32] = {};			//終了メッセージ

		fscanf(pFile, "%s", &aStartMessage[0]);
		if (strcmp(&aStartMessage[0], START_OK) == 0)
		{
			while (1)
			{
				fscanf(pFile, "%s", &aSetMessage[0]);
				if (strcmp(&aSetMessage[0], END_SET_OK) == 0)
				{
					break;
				}
				else if (strcmp(&aSetMessage[0], "STARTSETBLOCK") == 0)
				{
					fscanf(pFile, "%d", &nCreateNumber);
					fscanf(pFile, "%d", &nWightNumber);
					fscanf(pFile, "%d", &nHeightNumber);
					fscanf(pFile, "%s", &aSetMessage[0]);

					CBreak_Block3D::TrueUse(nCreateNumber, nWightNumber, nHeightNumber);
				}
			}
		}
		fclose(pFile);
	}
	else
	{//ファイルが開けなかった場合
		printf("***ファイルを開けませんでした***\n");
	}
	CBreak_Block3D::CreateMapBlocks(0, pos);
}
