//============================================
//
//	チュートリアル時のUI設定 [TutorialUI.cpp]
//	Author:sakamoto kai
//
//============================================
#include "TutorialUI.h"
#include "manager.h"
#include "game.h"
#include "object2D.h"
#include "input.h"
#include "sound.h"

//静的メンバ変数宣言

//====================================================================
//コンストラクタ
//====================================================================
CTutorialUI::CTutorialUI(int TutorialNumber)
{
	m_TurorialNumber = TutorialNumber;
	m_SetColor = 0.0f;
	m_SetColorHlaf = 0.0f;
	m_bColor = true;

	switch (TutorialNumber)
	{
	case 1:
		m_PushNumber = 1;
		break;
	case 4:
		m_PushNumber = 1;
		break;
	default:
		m_PushNumber = 0;
		break;
	}

	m_pScreenBG = NULL;
	m_pChatBG = NULL;
	m_pPlayerBG = NULL;
	m_pChat = NULL;
	m_pTurorialText = NULL;
	m_pArrorw = NULL;
}

//====================================================================
//デストラクタ
//====================================================================
CTutorialUI::~CTutorialUI()
{

}

//====================================================================
//生成処理
//====================================================================
CTutorialUI *CTutorialUI::Create(int TutorialNumber)
{
	CTutorialUI *pTutorialUI = NULL;

	if (pTutorialUI == NULL)
	{
		//オブジェクト2Dの生成
		pTutorialUI = new CTutorialUI(TutorialNumber);
	}

	//オブジェクトの初期化処理
	if (FAILED(pTutorialUI->Init()))
	{//初期化処理が失敗した場合
		return NULL;
	}

	return pTutorialUI;
}

//====================================================================
//初期化処理
//====================================================================
HRESULT CTutorialUI::Init(void)
{
	m_pScreenBG = CObject2D::Create(7);
	m_pScreenBG->SetType(CObject::TYPE_TUTORIALUI);

	m_pChatBG = CObject2D::Create(7);
	m_pChatBG->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	m_pChatBG->SetType(CObject::TYPE_TUTORIALUI);
	m_pChatBG->SetTexture("data\\TEXTURE\\TutorialBG00.png");

	m_pPlayerBG = CObject2D::Create(7);
	m_pPlayerBG->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	m_pPlayerBG->SetType(CObject::TYPE_TUTORIALUI);
	m_pPlayerBG->SetTexture("data\\TEXTURE\\TutorialPlayer.png");

	m_pChat = CObject2D::Create(7);
	m_pChat->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	m_pChat->SetType(CObject::TYPE_TUTORIALUI);
	m_pChat->SetTexture("data\\TEXTURE\\TutorialChat.png");

	m_pTurorialText = CObject2D::Create(7);
	m_pTurorialText->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	m_pTurorialText->SetType(CObject::TYPE_TUTORIALUI);

	m_pArrorw = CObject2D::Create(7);
	m_pArrorw->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	m_pArrorw->SetType(CObject::TYPE_TUTORIALUI);
	m_pArrorw->SetTexture("data\\TEXTURE\\Arrorw.png");

	switch (m_TurorialNumber)
	{
	case 0:
		m_pScreenBG->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		m_pScreenBG->SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
		m_pScreenBG->SetWight(1280.0f);
		m_pScreenBG->SetHeight(720.0f);
		m_pScreenBG->SetTexture("data\\TEXTURE\\Test.jpg");

		m_pChatBG->SetPos(D3DXVECTOR3(640.0f, 200.0f, 0.0f));
		m_pChatBG->SetWight(2000.0f);
		m_pChatBG->SetHeight(800.0f);

		m_pPlayerBG->SetPos(D3DXVECTOR3(300.0f, 500.0f, 0.0f));
		m_pPlayerBG->SetWight(600.0f);
		m_pPlayerBG->SetHeight(600.0f);

		m_pChat->SetPos(D3DXVECTOR3(900.0f, 200.0f, 0.0f));
		m_pChat->SetWight(1000.0f);
		m_pChat->SetHeight(500.0f);

		m_pTurorialText->SetPos(D3DXVECTOR3(930.0f, 225.0f, 0.0f));
		m_pTurorialText->SetWight(500.0f);
		m_pTurorialText->SetHeight(400.0f);
		m_pTurorialText->SetTexture("data\\TEXTURE\\TutorialText000.png");

		m_pArrorw->SetPos(D3DXVECTOR3(-1000.0f, -1000.0f, 0.0f));
		m_pArrorw->SetWight(0.0f);
		m_pArrorw->SetHeight(0.0f);


		break;
	case 1:
		m_pScreenBG->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pScreenBG->SetPos(D3DXVECTOR3(200.0f, 75.0f, 0.0f));
		m_pScreenBG->SetWight(18000.0f);
		m_pScreenBG->SetHeight(5000.0f);
		m_pScreenBG->SetTexture("data\\TEXTURE\\shadow003.png");

		m_pChatBG->SetPos(D3DXVECTOR3(-1000.0f, -1000.0f, 0.0f));
		m_pChatBG->SetWight(0.0f);
		m_pChatBG->SetHeight(0.0f);

		m_pPlayerBG->SetPos(D3DXVECTOR3(400.0f, 620.0f, 0.0f));
		m_pPlayerBG->SetWight(400.0f);
		m_pPlayerBG->SetHeight(400.0f);

		m_pChat->SetPos(D3DXVECTOR3(900.0f, 500.0f, 0.0f));
		m_pChat->SetWight(1000.0f);
		m_pChat->SetHeight(500.0f);

		m_pTurorialText->SetPos(D3DXVECTOR3(930.0f, 525.0f, 0.0f));
		m_pTurorialText->SetWight(500.0f);
		m_pTurorialText->SetHeight(400.0f);
		m_pTurorialText->SetTexture("data\\TEXTURE\\Tutorial_Sample00.png");

		m_pArrorw->SetPos(D3DXVECTOR3(520.0f, 290.0f, 0.0f));
		m_pArrorw->SetWight(1000.0f);
		m_pArrorw->SetHeight(300.0f);
		m_pArrorw->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 0.78f));
		break;

	case 4:
		m_pScreenBG->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		m_pScreenBG->SetPos(D3DXVECTOR3(200.0f, 75.0f, 0.0f));
		m_pScreenBG->SetWight(18000.0f);
		m_pScreenBG->SetHeight(5000.0f);
		m_pScreenBG->SetTexture("data\\TEXTURE\\shadow003.png");

		m_pChatBG->SetPos(D3DXVECTOR3(-1000.0f, -1000.0f, 0.0f));
		m_pChatBG->SetWight(0.0f);
		m_pChatBG->SetHeight(0.0f);

		m_pPlayerBG->SetPos(D3DXVECTOR3(200.0f, 620.0f, 0.0f));
		m_pPlayerBG->SetWight(400.0f);
		m_pPlayerBG->SetHeight(400.0f);

		m_pChat->SetPos(D3DXVECTOR3(700.0f, 500.0f, 0.0f));
		m_pChat->SetWight(1000.0f);
		m_pChat->SetHeight(500.0f);

		m_pTurorialText->SetPos(D3DXVECTOR3(730.0f, 545.0f, 0.0f));
		m_pTurorialText->SetWight(500.0f);
		m_pTurorialText->SetHeight(400.0f);
		m_pTurorialText->SetTexture("data\\TEXTURE\\Tutorial_Sample00.png");

		m_pArrorw->SetPos(D3DXVECTOR3(720.0f, 290.0f, 0.0f));
		m_pArrorw->SetWight(1000.0f);
		m_pArrorw->SetHeight(300.0f);
		m_pArrorw->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 0.78f));
		break;

	default:
		m_pScreenBG->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		m_pScreenBG->SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
		m_pScreenBG->SetWight(1280.0f);
		m_pScreenBG->SetHeight(720.0f);
		m_pScreenBG->SetTexture("data\\TEXTURE\\Test.jpg");

		m_pChatBG->SetPos(D3DXVECTOR3(640.0f, 200.0f, 0.0f));
		m_pChatBG->SetWight(2000.0f);
		m_pChatBG->SetHeight(800.0f);

		m_pPlayerBG->SetPos(D3DXVECTOR3(300.0f, 500.0f, 0.0f));
		m_pPlayerBG->SetWight(600.0f);
		m_pPlayerBG->SetHeight(600.0f);

		m_pChat->SetPos(D3DXVECTOR3(900.0f, 200.0f, 0.0f));
		m_pChat->SetWight(1000.0f);
		m_pChat->SetHeight(500.0f);

		m_pTurorialText->SetPos(D3DXVECTOR3(930.0f, 525.0f, 0.0f));
		m_pTurorialText->SetWight(500.0f);
		m_pTurorialText->SetHeight(400.0f);
		m_pTurorialText->SetTexture("data\\TEXTURE\\Tutorial_Sample00.png");

		m_pArrorw->SetPos(D3DXVECTOR3(-1000.0f, -1000.0f, 0.0f));
		m_pArrorw->SetWight(0.0f);
		m_pArrorw->SetHeight(0.0f);
		break;
	}

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CTutorialUI::Uninit(void)
{
	CGame::DeleteTutorial();
}

//====================================================================
//UI削除処理
//====================================================================
void CTutorialUI::DeleteUI(void)
{
	if (m_pScreenBG != NULL)
	{
		m_pScreenBG->Uninit();
		m_pScreenBG = NULL;
	}
	if (m_pChatBG != NULL)
	{
		m_pChatBG->Uninit();
		m_pChatBG = NULL;
	}
	if (m_pPlayerBG != NULL)
	{
		m_pPlayerBG->Uninit();
		m_pPlayerBG = NULL;
	}
	if (m_pChat != NULL)
	{
		m_pChat->Uninit();
		m_pChat = NULL;
	}
	if (m_pTurorialText != NULL)
	{
		m_pTurorialText->Uninit();
		m_pTurorialText = NULL;
	}
	if (m_pArrorw != NULL)
	{
		m_pArrorw->Uninit();
		m_pArrorw = NULL;
	}
}

//====================================================================
//チュートリアル終了処理
//====================================================================
void CTutorialUI::DeleteTutorial(void)
{
	CManager::GetInstance()->SetStop(false);
	DeleteUI();
	Uninit();
}

//====================================================================
//更新処理
//====================================================================
void CTutorialUI::Update(void)
{
	switch (m_TurorialNumber)
	{
	case 0:
		m_pScreenBG->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, m_SetColorHlaf));
		break;
	case 1:
		m_pScreenBG->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_SetColorHlaf));
		break;
	default:
		m_pScreenBG->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, m_SetColorHlaf));
		break;
	}

	m_pChatBG->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_SetColor));
	m_pPlayerBG->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_SetColor));
	m_pChat->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_SetColor));
	m_pTurorialText->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_SetColor));
	m_pArrorw->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_SetColor));

	//何回目のチュートリアルか判断
	if (m_TurorialNumber == 1)
	{
		//会話の残り回数
		switch (m_PushNumber)
		{
		case 1:
			m_pScreenBG->SetPos(D3DXVECTOR3(200.0f, 55.0f, 0.0f));
			m_pScreenBG->SetWight(18000.0f);
			m_pScreenBG->SetHeight(5000.0f);

			m_pArrorw->SetPos(D3DXVECTOR3(520.0f, 290.0f, 0.0f));
			m_pArrorw->SetWight(1000.0f);
			m_pArrorw->SetHeight(300.0f);
			m_pArrorw->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 0.78f));

			m_pTurorialText->SetTexture("data\\TEXTURE\\TutorialText001.png");
			break;
		case 0:
			m_pScreenBG->SetPos(D3DXVECTOR3(200.0f, 150.0f, 0.0f));
			m_pScreenBG->SetWight(15000.0f);
			m_pScreenBG->SetHeight(2500.0f);

			m_pArrorw->SetPos(D3DXVECTOR3(520.0f, 340.0f, 0.0f));
			m_pArrorw->SetWight(850.0f);
			m_pArrorw->SetHeight(300.0f);
			m_pArrorw->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 0.85f));

			m_pTurorialText->SetTexture("data\\TEXTURE\\TutorialText002.png");
			break;
		}
	}
	else if (m_TurorialNumber == 2)
	{
		m_pTurorialText->SetPos(D3DXVECTOR3(930.0f, 275.0f, 0.0f));
		m_pTurorialText->SetWight(500.0f);
		m_pTurorialText->SetHeight(400.0f);
		m_pTurorialText->SetTexture("data\\TEXTURE\\TutorialText003.png");

		if (CManager::GetInstance()->GetSetTutorialPad() == false)
		{
			CGame::SetTutorialUnderText("data\\TEXTURE\\TutorialUnder001.png");
		}
		else
		{
			CGame::SetTutorialUnderText("data\\TEXTURE\\TutorialUnderPad001.png");
		}
	}
	else if (m_TurorialNumber == 3)
	{
		m_pTurorialText->SetPos(D3DXVECTOR3(930.0f, 225.0f, 0.0f));
		m_pTurorialText->SetWight(500.0f);
		m_pTurorialText->SetHeight(400.0f);
		m_pTurorialText->SetTexture("data\\TEXTURE\\TutorialText004.png");

		CGame::SetTutorialUnderText("data\\TEXTURE\\TutorialUnder002.png");
	}
	else if (m_TurorialNumber == 4)
	{
		//会話の残り回数
		switch (m_PushNumber)
		{
		case 1:
			m_pScreenBG->SetPos(D3DXVECTOR3(1230.0f, 360.0f, 0.0f));
			m_pScreenBG->SetWight(10000.0f);
			m_pScreenBG->SetHeight(18000.0f);

			m_pArrorw->SetPos(D3DXVECTOR3(1100.0f, 500.0f, 0.0f));
			m_pArrorw->SetWight(400.0f);
			m_pArrorw->SetHeight(300.0f);
			m_pArrorw->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 0.0f));

			m_pTurorialText->SetTexture("data\\TEXTURE\\TutorialText006.png");
			break;
		case 0:
			m_pScreenBG->SetPos(D3DXVECTOR3(200.0f, 100.0f, 0.0f));
			m_pScreenBG->SetWight(15000.0f);
			m_pScreenBG->SetHeight(2000.0f);

			m_pArrorw->SetPos(D3DXVECTOR3(400.0f, 290.0f, 0.0f));
			m_pArrorw->SetWight(750.0f);
			m_pArrorw->SetHeight(300.0f);
			m_pArrorw->SetRot(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 0.75f));

			m_pTurorialText->SetTexture("data\\TEXTURE\\TutorialText007.png");
			break;
		}
		CGame::SetTutorialUnderText("data\\TEXTURE\\TutorialUnder003.png");
	}
	else if (m_TurorialNumber == 5)
	{
		m_pScreenBG->SetPos(D3DXVECTOR3(200.0f, 200.0f, 0.0f));
		m_pScreenBG->SetWight(15000.0f);
		m_pScreenBG->SetHeight(2500.0f);

		m_pChatBG->SetPos(D3DXVECTOR3(640.0f, 200.0f, 0.0f));
		m_pChatBG->SetWight(2000.0f);
		m_pChatBG->SetHeight(800.0f);

		m_pPlayerBG->SetPos(D3DXVECTOR3(300.0f, 500.0f, 0.0f));
		m_pPlayerBG->SetWight(600.0f);
		m_pPlayerBG->SetHeight(600.0f);

		m_pChat->SetPos(D3DXVECTOR3(900.0f, 200.0f, 0.0f));
		m_pChat->SetWight(1000.0f);
		m_pChat->SetHeight(500.0f);

		m_pArrorw->SetWight(0.0f);
		m_pArrorw->SetHeight(0.0f);

		m_pTurorialText->SetPos(D3DXVECTOR3(930.0f, 240.0f, 0.0f));
		m_pTurorialText->SetWight(500.0f);
		m_pTurorialText->SetHeight(400.0f);
		m_pTurorialText->SetTexture("data\\TEXTURE\\TutorialText005.png");

		CGame::SetTutorialUnderText("data\\TEXTURE\\TutorialUnder003.png");
	}

	if (CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true ||
		CManager::GetInstance()->GetInputJoyPad()->GetTrigger(CInputJoypad::BUTTON_A, 0) == true)
	{
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_ENTER_PUSH);

		if (m_PushNumber > 0)
		{
			m_PushNumber--;
		}
		else
		{
			m_bColor = false;
		}
	}

	if (m_bColor == true)
	{
		if (m_SetColor < 1.0f)
		{
			m_SetColor += 0.05f;
		}

		if (m_SetColorHlaf < 0.75f)
		{
			m_SetColorHlaf += 0.0375f;
		}
	}
	else
	{
		if (m_SetColor > 0.0f)
		{
			m_SetColor -= 0.1f;
		}

		if (m_SetColorHlaf > 0.0f)
		{
			m_SetColorHlaf -= 0.075f;
		}
		else
		{
			DeleteTutorial();
		}
	}
}

//====================================================================
//描画処理
//====================================================================
void CTutorialUI::Draw(void)
{

}
