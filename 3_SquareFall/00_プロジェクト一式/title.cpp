//============================================
//
//	タイトル画面 [title.cpp]
//	Author:sakamoto kai
//
//============================================
#include "title.h"
#include "manager.h"
#include "fade.h"
#include "input.h"
#include "object2D.h"
#include "texture.h"
#include "player3D.h"
#include "break_block3D.h"
#include "BlockUI.h"
#include "ranking.h"
#include "TitleUI.h"
#include "particle.h"
#include "sound.h"

//静的メンバ変数宣言
CPlayer3D *CTitle::m_pPlayer3D = NULL;
CBreak_Block3D *CTitle::m_pBlock3D = NULL;
CObject2D *CTitle::m_pTitle = NULL;
CBlockUI *CTitle::m_pSelect[MAX_SELECT] = {};
CTitleUI *CTitle::m_pTitleUI[MAX_TITLEUI] = {};
int CTitle::m_nSelect = 1;
int CTitle::m_CreateCount = 0;
//====================================================================
//コンストラクタ
//====================================================================
CTitle::CTitle()
{
	m_nSelect = 1;
	m_CreateCount = 0;
}

//====================================================================
//デストラクタ
//====================================================================
CTitle::~CTitle()
{

}

//====================================================================
//初期化処理
//====================================================================
HRESULT CTitle::Init(void)
{
	CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_BGM_TITLE);

	//m_pTitle = CObject2D::Create();
	//m_pTitle->SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	//m_pTitle->SetWight(1280.0f);
	//m_pTitle->SetHeight(720.0f);
	//CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	//m_pTitle->SetIdx(pTexture->Regist("data\\TEXTURE\\Title.png"));

	//for (int nCnt = 0; nCnt < 10; nCnt++)
	//{
	//	m_pBlock3D = CBreak_Block3D::Create();
	//	m_pBlock3D->bUseSet();
	//	m_pBlock3D->SetPos(D3DXVECTOR3(-240.0f + nCnt * 40.0f, 0.0f, 0.0f));
	//	m_pBlock3D->SetWNumber(5);
	//}

	for (int nCntObjHeight = 0; nCntObjHeight < SET_BLOCK_HEIGHT; nCntObjHeight++)
	{
		for (int nCntObjWight = 0 + 1; nCntObjWight < SET_BLOCK_WIGHT + 1; nCntObjWight++)
		{
			if (nCntObjWight == 1 || nCntObjWight == 2)
			{
				m_pBlock3D = CBreak_Block3D::Create();
				m_pBlock3D->SetPos(D3DXVECTOR3(-480.0f + 40.f * nCntObjWight, 500.0f - 40.0f * nCntObjHeight, 0.0f));
				m_pBlock3D->SetCNumber(0);
				m_pBlock3D->SetWNumber(nCntObjWight);
				m_pBlock3D->SetHNumber(nCntObjHeight);
				m_pBlock3D->SetUse(0, nCntObjWight, nCntObjHeight, true);
			}
			else if(nCntObjWight == 18 || nCntObjWight == 19)
			{
				m_pBlock3D = CBreak_Block3D::Create();
				m_pBlock3D->SetPos(D3DXVECTOR3(-300.0f + 40.f * nCntObjWight, 500.0f - 40.0f * nCntObjHeight, 0.0f));
				m_pBlock3D->SetCNumber(0);
				m_pBlock3D->SetWNumber(nCntObjWight);
				m_pBlock3D->SetHNumber(nCntObjHeight);
				m_pBlock3D->SetUse(0, nCntObjWight, nCntObjHeight, true);
			}
		}
		m_pBlock3D->SetUse(0, 0, nCntObjHeight, true);
		m_pBlock3D->SetUse(0, 20, nCntObjHeight, true);
	}

	//
	for (int nCnt = 0; nCnt < MAX_TITLEUI; nCnt++)
	{
		m_pTitleUI[nCnt] = CTitleUI::Create();
		m_pTitleUI[nCnt]->SetPos(D3DXVECTOR3(0.0f, 250.0f + nCnt * -40.0f, 50.0f + nCnt * -10.0f));
	}

	m_pTitleUI[0]->SetMatColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
	m_pTitleUI[1]->SetMatColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f));
	m_pTitleUI[2]->SetMatColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//3Dプレイヤーモデルの生成
	m_pPlayer3D = CPlayer3D::Create();
	m_pPlayer3D->SetPos(D3DXVECTOR3(0.0f, 500.0f, 0.0f));

	for (int nCnt = 0; nCnt < MAX_SELECT; nCnt++)
	{
		m_pSelect[nCnt] = CBlockUI::Create();
		m_pSelect[nCnt]->SetPos(D3DXVECTOR3(-260.0f + nCnt * 280.0f, 0.0f, 0.0f));
		m_pSelect[nCnt]->SetMatColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f));
		m_pSelect[nCnt]->SetMyCount(nCnt);
	}

	////BGMの再生
	//m_pSound->PlaySoundA(CSound::SOUND_LABEL_BGM_TITLE);

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CTitle::Uninit(void)
{
	//全てのオブジェクトの破棄
	CObject::ReleaseAll();
}

//====================================================================
//更新処理
//====================================================================
void CTitle::Update(void)
{
	//選択処理
	Select();

	m_CreateCount++;

	if (m_CreateCount % 2 == 0)
	{
		CParticle::Create
		(
			D3DXVECTOR3(m_pPlayer3D->GetPos().x, m_pPlayer3D->GetPos().y, m_pPlayer3D->GetPos().z),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			300,
			10.0f,
			3
		);
	}

	for (int nCnt = 0; nCnt < MAX_SELECT; nCnt++)
	{
		if (m_nSelect == nCnt)
		{
			m_pSelect[nCnt]->SetMatColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}
		else
		{
			m_pSelect[nCnt]->SetMatColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f));
		}
	}
}

//====================================================================
//描画処理
//====================================================================
void CTitle::Draw(void)
{

}

//====================================================================
//選択処理
//====================================================================
void CTitle::Select(void)
{
	if (m_pPlayer3D->GetPos().y <= -400)
	{
		switch (m_nSelect)
		{
		case 0:
			CManager::GetInstance()->SetTutorialStart(false);
			CFade::SetFade(CScene::MODE_GAME);
			break;

		case 1:
			CManager::GetInstance()->SetTutorialStart(true);
			CFade::SetFade(CScene::MODE_GAME);
			break;

		case 2:
			CRanking::ChangeRanking(false);
			CManager::GetInstance()->SetSetScoreResult(false);
			CFade::SetFade(CScene::MODE_RESULT);
			break;

		default:
			break;
		}
	}
}

//====================================================================
//選択項目のカラー変更処理
//====================================================================
void CTitle::SetSelectColor(int nCnt)
{
	m_nSelect = nCnt;
}