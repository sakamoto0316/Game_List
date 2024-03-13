//============================================
//
//	コンボ処理 [combo.cpp]
//	Author:sakamoto kai
//
//============================================
#include "combo.h"
#include "manager.h"
#include "game.h"
#include "DebugNumber3D.h"
#include "comboUI.h"

//静的メンバ変数宣言

//====================================================================
//コンストラクタ
//====================================================================
CCombo::CCombo()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nComboNumber = 0;
}

//====================================================================
//デストラクタ
//====================================================================
CCombo::~CCombo()
{

}

//====================================================================
//生成処理
//====================================================================
CCombo *CCombo::Create(void)
{
	CCombo *pCombo = NULL;

	if (pCombo == NULL)
	{
		//敵の生成
		pCombo = new CCombo();
	}

	//オブジェクトの初期化処理
	if (FAILED(pCombo->Init()))
	{//初期化処理が失敗した場合
		return NULL;
	}

	return pCombo;
}

//====================================================================
//初期化処理
//====================================================================
HRESULT CCombo::Init(void)
{
	m_pNumber1 = CDebugNumber3D::Create();
	m_pNumber1->SetPos(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z));
	m_pNumber1->SetWight(15.0f);
	m_pNumber1->SetHeight(15.0f);

	m_pNumber10 = CDebugNumber3D::Create();
	m_pNumber10->SetPos(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z));
	m_pNumber10->SetWight(15.0f);
	m_pNumber10->SetHeight(15.0f);

	m_pComboUI = CComboUI::Create();
	m_pComboUI->SetPos(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z));
	m_pComboUI->SetWight(45.0f);
	m_pComboUI->SetHeight(25.0f);

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CCombo::Uninit(void)
{
	if (m_pNumber1 != NULL)
	{
		m_pNumber1->Uninit();
		m_pNumber1->SetDeathFlag(true);
	}
	if (m_pNumber10 != NULL)
	{
		m_pNumber10->Uninit();
		m_pNumber10->SetDeathFlag(true);
	}

	if (m_pComboUI != NULL)
	{
		m_pComboUI->Uninit();
		m_pComboUI->SetDeathFlag(true);
	}

	if (this != NULL)
	{
		//敵の削除
		delete this;
	}
}

//====================================================================
//終了処理
//====================================================================
void CCombo::SetNULL(void)
{
	if (m_pNumber1 != NULL)
	{
		m_pNumber1 = NULL;
	}
	if (m_pNumber10 != NULL)
	{
		m_pNumber10 = NULL;
	}

	if (m_pComboUI != NULL)
	{
		m_pComboUI = NULL;
	}
}

//====================================================================
//更新処理
//====================================================================
void CCombo::Update(void)
{
	if (m_nComboNumber > 0)
	{
		m_pNumber1->SetPos(D3DXVECTOR3(m_pos.x - 25.0f, m_pos.y - 20.0f, m_pos.z));
		m_pComboUI->SetPos(D3DXVECTOR3(m_pos.x + 5.0f, m_pos.y - 20.0f, m_pos.z));

		m_pNumber1->SetAppear(true);
		m_pComboUI->SetAppear(true);

		m_pNumber10->SetNumber(m_nComboNumber / 10);
		m_pNumber1->SetNumber(m_nComboNumber);
	}
	else
	{
		m_pNumber1->SetAppear(false);
		m_pComboUI->SetAppear(false);
	}

	if (m_nComboNumber >= 10)
	{
		m_pNumber10->SetPos(D3DXVECTOR3(m_pos.x - 35.0f, m_pos.y - 20.0f, m_pos.z));
		m_pNumber10->SetAppear(true);
	}
	else
	{
		m_pNumber10->SetAppear(false);
	}
}

//====================================================================
//描画処理
//====================================================================
void CCombo::Draw(void)
{

}
