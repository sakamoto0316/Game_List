//============================================
//
//	ライフゲージのビルボード [LifeGaugeBillboard.cpp]
//	Author:sakamoto kai
//
//============================================
#include "LifeGaugeBillboard.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"

//マクロ定義
#define GAUGE_POS (D3DXVECTOR3(5.0f, 5.0f, 0.0f))		//ゲージの位置
#define GAUGE_WIGHT (80.0f)	//ゲージの横幅
#define GAUGE_HEIGHT (10.0f)	//ゲージの縦幅
#define GAUGE_TILT (5.0f)		//ゲージの傾き

//====================================================================
//コンストラクタ
//====================================================================
CLifeGaugeBillboard::CLifeGaugeBillboard(int nPriority) : CGaugeBillboard(nPriority)
{
	m_nIdxTexture = -1;
	//m_nLifeMax = 0;
	//m_nLife = 0;

	SetPos(GAUGE_POS);
	SetWight(GAUGE_WIGHT);
	SetHeight(GAUGE_HEIGHT);
	SetTilt(GAUGE_TILT);
}

//====================================================================
//デストラクタ
//====================================================================
CLifeGaugeBillboard::~CLifeGaugeBillboard()
{

}

//====================================================================
//生成処理
//====================================================================
CLifeGaugeBillboard *CLifeGaugeBillboard::Create(void)
{
	CLifeGaugeBillboard *pGauge = NULL;

	if (pGauge == NULL)
	{
		//オブジェクト2Dの生成
		pGauge = new CLifeGaugeBillboard();
	}

	//オブジェクトの初期化処理
	if (FAILED(pGauge->Init()))
	{//初期化処理が失敗した場合
		return NULL;
	}

	return pGauge;
}

//====================================================================
//初期化処理
//====================================================================
HRESULT CLifeGaugeBillboard::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\Test.jpg");

	CGaugeBillboard::Init();

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CLifeGaugeBillboard::Uninit(void)
{
	CGaugeBillboard::Uninit();
}

//====================================================================
//更新処理
//====================================================================
void CLifeGaugeBillboard::Update(void)
{
	//頂点情報の更新
	CGaugeBillboard::Update();
}

//====================================================================
//描画処理
//====================================================================
void CLifeGaugeBillboard::Draw(void)
{
	CGaugeBillboard::Draw();
}