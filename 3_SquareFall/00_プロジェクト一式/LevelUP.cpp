//============================================
//
//	レベルアップ処理 [LevelUP.cpp]
//	Author:sakamoto kai
//
//============================================
#include "LevelUP.h"
#include "LevelUPUI.h"
#include "manager.h"
#include "game.h"
#include "input.h"
#include "texture.h"
#include "sound.h"

//静的メンバ変数宣言
CLevelUPUI *CLevelUP::m_pLevelUPText = NULL;
CLevelUPUI *CLevelUP::m_pLevelUPTutorial = NULL;
CLevelUPUI *CLevelUP::m_pLevelUPBG = NULL;
CLevelUPUI *CLevelUP::m_pLevelUPUI[3] = {};
CLevelUPUI *CLevelUP::m_pLevelUPCursor = NULL;
int CLevelUP::m_nCursorNumber = 0;
CPlayer3D::SHOT_TYPE CLevelUP::m_BulletType = CPlayer3D::SHOT_NORMAL;

//====================================================================
//コンストラクタ
//====================================================================
CLevelUP::CLevelUP(int nLevelUP, CPlayer3D::SHOT_TYPE type)
{
	LevelUpCount = nLevelUP;
	m_bLevelUp = false;
	m_BulletType = type;
	LevelUpMax = 0;
}

//====================================================================
//デストラクタ
//====================================================================
CLevelUP::~CLevelUP()
{

}

//====================================================================
//生成処理
//====================================================================
CLevelUP *CLevelUP::Create(int nLevelUP, CPlayer3D::SHOT_TYPE type)
{
	CLevelUP *pLevelUP = NULL;

	if (pLevelUP == NULL)
	{
		//敵の生成
		pLevelUP = new CLevelUP(nLevelUP, type);
	}

	//オブジェクトの初期化処理
	if (FAILED(pLevelUP->Init()))
	{//初期化処理が失敗した場合
		return NULL;
	}

	return pLevelUP;
}

//====================================================================
//初期化処理
//====================================================================
HRESULT CLevelUP::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_nCursorNumber = 0;

	CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_LEVELUP);


	m_pLevelUPBG = CLevelUPUI::Create();
	m_pLevelUPBG->SetPos(D3DXVECTOR3(640.0f, 380.0f, 0.0f));
	m_pLevelUPBG->SetWight(1280.0f);
	m_pLevelUPBG->SetHeight(540.0f);
	m_pLevelUPBG->SetColor(D3DXCOLOR(0.8f, 0.8f, 0.8f, 0.8f));
	m_pLevelUPBG->SetLevelUI(true);

	m_pLevelUPTutorial = CLevelUPUI::Create();
	m_pLevelUPTutorial->SetPos(D3DXVECTOR3(640.0f, 580.0f, 0.0f));
	m_pLevelUPTutorial->SetWight(800.0f);
	m_pLevelUPTutorial->SetHeight(200.0f);
	m_pLevelUPTutorial->SetLevelUI(true);
	m_pLevelUPTutorial->SetIdx(pTexture->Regist("data\\TEXTURE\\LevelUPTutorial.png"));

	m_pLevelUPText = CLevelUPUI::Create();
	m_pLevelUPText->SetPos(D3DXVECTOR3(640.0f, 170.0f, 0.0f));
	m_pLevelUPText->SetWight(400.0f);
	m_pLevelUPText->SetHeight(200.0f);
	m_pLevelUPText->SetLevelUI(true);
	m_pLevelUPText->SetIdx(pTexture->Regist("data\\TEXTURE\\LEVELUP.png"));

	if (LevelUpCount == 0)
	{
		LevelUpMax = 3;

		//レベルアップUIの生成と設定
		m_pLevelUPCursor = CLevelUPUI::Create();
		m_pLevelUPCursor->SetPos(D3DXVECTOR3(400.0f + (m_nCursorNumber * 300.0f), 390.0f, 0.0f));
		m_pLevelUPCursor->SetWight(300.0f);
		m_pLevelUPCursor->SetHeight(300.0f);
		m_pLevelUPCursor->SetColor(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
		m_pLevelUPCursor->SetLevelUI(true);
		if (CManager::GetInstance()->GetSetTutorialPad() == false)
		{
			m_pLevelUPCursor->SetIdx(pTexture->Regist("data\\TEXTURE\\LevelUPSelect.png"));
		}
		else
		{
			m_pLevelUPCursor->SetIdx(pTexture->Regist("data\\TEXTURE\\LevelUPSelectPad.png"));
		}

		for (int nCnt = 0; nCnt < LevelUpMax; nCnt++)
		{
			m_pLevelUPUI[nCnt] = CLevelUPUI::Create();
			m_pLevelUPUI[nCnt]->SetPos(D3DXVECTOR3(400.0f + (300.0f * nCnt), 360.0f, 0.0f));
			m_pLevelUPUI[nCnt]->SetWight(200.0f);
			m_pLevelUPUI[nCnt]->SetHeight(200.0f);
			m_pLevelUPUI[nCnt]->SetLevelUI(true);
		}
		m_pLevelUPUI[0]->SetIdx(pTexture->Regist("data\\TEXTURE\\Bullet_3WAY.png"));
		m_pLevelUPUI[1]->SetIdx(pTexture->Regist("data\\TEXTURE\\Bullet_Burst.png"));
		m_pLevelUPUI[2]->SetIdx(pTexture->Regist("data\\TEXTURE\\Bullet_Explosion.png"));
	}
	else
	{
		LevelUpMax = 2;

		//レベルアップUIの生成と設定
		m_pLevelUPCursor = CLevelUPUI::Create();
		m_pLevelUPCursor->SetPos(D3DXVECTOR3(500.0f + (m_nCursorNumber * 300.0f), 360.0f, 0.0f));
		m_pLevelUPCursor->SetWight(300.0f);
		m_pLevelUPCursor->SetHeight(300.0f);
		m_pLevelUPCursor->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		m_pLevelUPCursor->SetLevelUI(true);
		if (CManager::GetInstance()->GetSetTutorialPad() == false)
		{
			m_pLevelUPCursor->SetIdx(pTexture->Regist("data\\TEXTURE\\LevelUPSelect.png"));
		}
		else
		{
			m_pLevelUPCursor->SetIdx(pTexture->Regist("data\\TEXTURE\\LevelUPSelectPad.png"));
		}

		for (int nCnt = 0; nCnt < LevelUpMax; nCnt++)
		{
			m_pLevelUPUI[nCnt] = CLevelUPUI::Create();
			m_pLevelUPUI[nCnt]->SetPos(D3DXVECTOR3(500.0f + (300.0f * nCnt), 360.0f, 0.0f));
			m_pLevelUPUI[nCnt]->SetWight(200.0f);
			m_pLevelUPUI[nCnt]->SetHeight(200.0f);
			m_pLevelUPUI[nCnt]->SetLevelUI(true);
		}

		switch (m_BulletType)
		{
		case CPlayer3D::SHOT_3WAY:
			m_pLevelUPUI[0]->SetIdx(pTexture->Regist("data\\TEXTURE\\Bullet_Triple3WAY.png"));
			m_pLevelUPUI[1]->SetIdx(pTexture->Regist("data\\TEXTURE\\Bullet_8WAY.png"));
			break;
		case CPlayer3D::SHOT_BURST:
			m_pLevelUPUI[0]->SetIdx(pTexture->Regist("data\\TEXTURE\\Bullet_Leser.png"));
			m_pLevelUPUI[1]->SetIdx(pTexture->Regist("data\\TEXTURE\\Bullet_Muchinegun.png"));
			break;
		case CPlayer3D::SHOT_EXPLOSION:
			m_pLevelUPUI[0]->SetIdx(pTexture->Regist("data\\TEXTURE\\Bullet_Spread_Explosion.png"));
			m_pLevelUPUI[1]->SetIdx(pTexture->Regist("data\\TEXTURE\\Bullet_Continue_Explosion.png"));
			break;
		}
	}

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CLevelUP::Uninit(void)
{
	if (m_pLevelUPCursor != NULL)
	{
		m_pLevelUPCursor->Uninit();
	}

	for (int nCnt = 0; nCnt < LevelUpMax; nCnt++)
	{
		if (m_pLevelUPUI[nCnt] != NULL)
		{
			m_pLevelUPUI[nCnt]->Uninit();
		}
	}

	if (this != NULL)
	{
		CManager::GetInstance()->SetLevelUP(NULL);

		//敵の削除
		delete this;
	}
}

//====================================================================
//終了処理
//====================================================================
void CLevelUP::SetNULL(void)
{
	if (m_pLevelUPCursor != NULL)
	{
		m_pLevelUPCursor = NULL;
	}

	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		if (m_pLevelUPUI[nCnt] != NULL)
		{
			m_pLevelUPUI[nCnt] = NULL;
		}
	}
}

//====================================================================
//更新処理
//====================================================================
void CLevelUP::Update(void)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputJoypad *pInputJoypad = CManager::GetInstance()->GetInputJoyPad();
	CPlayer3D *pPlayer = CGame::GetPlayer3D();

	if (pInputKeyboard->GetTrigger(DIK_A) == true ||
		pInputKeyboard->GetTrigger(DIK_LEFT) == true ||
		pInputJoypad->GetTrigger(CInputJoypad::BUTTON_LEFT, 0) == true || 
		pInputJoypad->Get_LStick_Trigger(CInputJoypad::LSTICK_LEFT, 0) == true)
	{
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_SELECT_PUSH);

		m_nCursorNumber--;
		
		if (m_nCursorNumber < 0)
		{
			m_nCursorNumber = LevelUpMax - 1;
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_D) == true ||
		pInputKeyboard->GetTrigger(DIK_RIGHT) == true ||
		pInputJoypad->GetTrigger(CInputJoypad::BUTTON_RIGHT, 0) == true ||
		pInputJoypad->Get_LStick_Trigger(CInputJoypad::LSTICK_RIGHT, 0) == true)
	{
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_SELECT_PUSH);

		m_nCursorNumber++;

		if (m_nCursorNumber > LevelUpMax - 1)
		{
			m_nCursorNumber = 0;
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true ||
		pInputJoypad->GetTrigger(CInputJoypad::BUTTON_B, 0) == true)
	{
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_ENTER_PUSH);

		m_pLevelUPCursor->SetLevelStop(false);

		BulletChange();

		pPlayer->SetBullet(m_BulletType);

		Uninit();

		return;
	}

	if (LevelUpCount == 0)
	{
		m_pLevelUPCursor->SetPos(D3DXVECTOR3(400.0f + (m_nCursorNumber * 300.0f), 390.0f, 0.0f));
	}
	else
	{
		m_pLevelUPCursor->SetPos(D3DXVECTOR3(500.0f + (m_nCursorNumber * 300.0f), 390.0f, 0.0f));
	}
}

//====================================================================
//描画処理
//====================================================================
void CLevelUP::Draw(void)
{

}

//====================================================================
//銃切り替え処理
//====================================================================
void CLevelUP::BulletChange(void)
{
	CPlayer3D *pPlayer = CGame::GetPlayer3D();

	switch (m_BulletType)
	{
	case CPlayer3D::SHOT_NORMAL:
		switch (m_nCursorNumber)
		{
		case 0:
			m_BulletType = CPlayer3D::SHOT_3WAY;
			pPlayer->SetBulletTypeUI("data\\TEXTURE\\Bullet_3WAY.png", CPlayer3D::SHOT_3WAY);
			break;
		case 1:
			m_BulletType = CPlayer3D::SHOT_BURST;
			pPlayer->SetBulletTypeUI("data\\TEXTURE\\Bullet_Burst.png", CPlayer3D::SHOT_BURST);
			break;
		case 2:
			m_BulletType = CPlayer3D::SHOT_EXPLOSION;
			pPlayer->SetBulletTypeUI("data\\TEXTURE\\Bullet_Explosion.png", CPlayer3D::SHOT_EXPLOSION);
			break;
		}
		break;

	case CPlayer3D::SHOT_3WAY:
		switch (m_nCursorNumber)
		{
		case 0:
			m_BulletType = CPlayer3D::SHOT_TRIPLE_3WAY;
			pPlayer->SetBulletTypeUI("data\\TEXTURE\\Bullet_Triple3WAY.png", CPlayer3D::SHOT_TRIPLE_3WAY);
			break;
		case 1:
			m_BulletType = CPlayer3D::SHOT_8WAY;
			pPlayer->SetBulletTypeUI("data\\TEXTURE\\Bullet_8WAY.png", CPlayer3D::SHOT_8WAY);
			break;
		}
		break;

	case CPlayer3D::SHOT_BURST:
		switch (m_nCursorNumber)
		{
		case 0:
			m_BulletType = CPlayer3D::SHOT_LESER;
			pPlayer->SetBulletTypeUI("data\\TEXTURE\\Bullet_Leser.png", CPlayer3D::SHOT_LESER);
			break;
		case 1:
			m_BulletType = CPlayer3D::SHOT_MACHINEGUN;
			pPlayer->SetBulletTypeUI("data\\TEXTURE\\Bullet_Muchinegun.png", CPlayer3D::SHOT_MACHINEGUN);
			break;
		}
		break;

	case CPlayer3D::SHOT_EXPLOSION:
		switch (m_nCursorNumber)
		{
		case 0:
			m_BulletType = CPlayer3D::SHOT_SPREAD_EXPLOSION;
			pPlayer->SetBulletTypeUI("data\\TEXTURE\\Bullet_Spread_Explosion.png", CPlayer3D::SHOT_SPREAD_EXPLOSION);
			break;
		case 1:
			m_BulletType = CPlayer3D::SHOT_CONTINUE_EXPLOSION;
			pPlayer->SetBulletTypeUI("data\\TEXTURE\\Bullet_Continue_Explosion.png", CPlayer3D::SHOT_CONTINUE_EXPLOSION);
			break;
		}
		break;
	}
}
