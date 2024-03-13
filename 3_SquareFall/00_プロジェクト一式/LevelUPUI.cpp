//============================================
//
//	レベルアップ時のUIの処理 [LevelUPUI.cpp]
//	Author:sakamoto kai
//
//============================================
#include "LevelUPUI.h"
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
CLevelUPUI::CLevelUPUI(int nPriority) : CObject2D(nPriority)
{
	SetWight(NUMBER_WIGHT);
	SetHeight(NUMBER_HEIGHT);
}

//====================================================================
//デストラクタ
//====================================================================
CLevelUPUI::~CLevelUPUI()
{

}

//====================================================================
//生成処理
//====================================================================
CLevelUPUI *CLevelUPUI::Create(void)
{
	CLevelUPUI *pNumber = NULL;

	if (pNumber == NULL)
	{
		//オブジェクト2Dの生成
		pNumber = new CLevelUPUI();
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
HRESULT CLevelUPUI::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\Test.jpg");

	CObject2D::Init();

	SetType(CObject::TYPE_LEVELUI);

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CLevelUPUI::Uninit(void)
{
	CObject2D::Uninit();
}

//====================================================================
//更新処理
//====================================================================
void CLevelUPUI::Update(void)
{
	//頂点情報の更新
	CObject2D::Update();
}

//====================================================================
//描画処理
//====================================================================
void CLevelUPUI::Draw(void)
{
	CObject2D::Draw();
}