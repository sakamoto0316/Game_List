//============================================
//
//	コンボUIの処理 [comboUI.cpp]
//	Author:sakamoto kai
//
//============================================
#include "comboUI.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"

//マクロ定義
#define NUMBER_WIGHT (100.0f)		//横幅
#define NUMBER_HEIGHT (100.0f)		//縦幅

//====================================================================
//コンストラクタ
//====================================================================
CComboUI::CComboUI(int nPriority) : CObjectBillboard(nPriority)
{
	SetWight(NUMBER_WIGHT);
	SetHeight(NUMBER_HEIGHT);
}

//====================================================================
//デストラクタ
//====================================================================
CComboUI::~CComboUI()
{

}

//====================================================================
//生成処理
//====================================================================
CComboUI *CComboUI::Create(void)
{
	CComboUI *pNumber = NULL;

	if (pNumber == NULL)
	{
		//オブジェクト2Dの生成
		pNumber = new CComboUI();
	}

	//オブジェクトの初期化処理
	if (FAILED(pNumber->Init()))
	{//初期化処理が失敗した場合
		return NULL;
	}

	return pNumber;
}

//====================================================================
//初期化処理
//====================================================================
HRESULT CComboUI::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\COMBO_UI.png");

	SetType(CObject::TYPE_LEVELUI);

	CObjectBillboard::Init();

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CComboUI::Uninit(void)
{
	CObjectBillboard::Uninit();
}

//====================================================================
//更新処理
//====================================================================
void CComboUI::Update(void)
{
	//頂点情報の更新
	CObjectBillboard::Update();
}

//====================================================================
//描画処理
//====================================================================
void CComboUI::Draw(void)
{
	CObjectBillboard::Draw();
}