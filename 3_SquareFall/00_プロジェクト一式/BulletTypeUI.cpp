//============================================
//
//	弾の種類のUIの処理 [BulletTypeUI.cpp]
//	Author:sakamoto kai
//
//============================================
#include "BulletTypeUI.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"

//マクロ定義
#define NUMBER_WIGHT (80.0f)		//横幅
#define NUMBER_HEIGHT (80.0f)		//縦幅

//====================================================================
//コンストラクタ
//====================================================================
CBulletTypeUI::CBulletTypeUI(int nPriority) : CObject2D(nPriority)
{
	SetWight(NUMBER_WIGHT);
	SetHeight(NUMBER_HEIGHT);
}

//====================================================================
//デストラクタ
//====================================================================
CBulletTypeUI::~CBulletTypeUI()
{

}

//====================================================================
//生成処理
//====================================================================
CBulletTypeUI *CBulletTypeUI::Create(void)
{
	CBulletTypeUI *pNumber = NULL;

	if (pNumber == NULL)
	{
		//オブジェクト2Dの生成
		pNumber = new CBulletTypeUI();
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
HRESULT CBulletTypeUI::Init(void)
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
void CBulletTypeUI::Uninit(void)
{
	CObject2D::Uninit();
}

//====================================================================
//更新処理
//====================================================================
void CBulletTypeUI::Update(void)
{
	//頂点情報の更新
	CObject2D::Update();
}

//====================================================================
//描画処理
//====================================================================
void CBulletTypeUI::Draw(void)
{
	CObject2D::Draw();
}