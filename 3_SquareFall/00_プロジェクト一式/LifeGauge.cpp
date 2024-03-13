//============================================
//
//	ライフゲージ [LifeGauge.cpp]
//	Author:sakamoto kai
//
//============================================
#include "LifeGauge.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"

//マクロ定義
#define GAUGE_POS (D3DXVECTOR3(5.0f, 5.0f, 0.0f))		//ゲージの位置
#define GAUGE_WIGHT (200.0f)	//ゲージの横幅
#define GAUGE_HEIGHT (50.0f)	//ゲージの縦幅
#define GAUGE_TILT (10.0f)		//ゲージの傾き

//====================================================================
//コンストラクタ
//====================================================================
CLifeGauge::CLifeGauge(bool Vertical, bool NumberUI, int nPriority) : CGauge(nPriority)
{
	m_nIdxTexture = -1;
	//m_nLifeMax = 0;
	//m_nLife = 0;

	SetPos(GAUGE_POS);
	SetWight(GAUGE_WIGHT);
	SetHeight(GAUGE_HEIGHT);
	SetTilt(GAUGE_TILT);
	SetVertical(Vertical);
	SetNumberUI(NumberUI);
}

//====================================================================
//デストラクタ
//====================================================================
CLifeGauge::~CLifeGauge()
{

}

//====================================================================
//生成処理
//====================================================================
CLifeGauge *CLifeGauge::Create(bool Vertical, bool NumberUI)
{
	CLifeGauge *pGauge = NULL;

	if (pGauge == NULL)
	{
		//オブジェクト2Dの生成
		pGauge = new CLifeGauge(Vertical, NumberUI);
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
HRESULT CLifeGauge::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\Test.jpg");

	CGauge::Init();

	SetAnim(D3DXVECTOR2(0.2f, 0.2f));

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CLifeGauge::Uninit(void)
{
	CGauge::Uninit();
}

//====================================================================
//更新処理
//====================================================================
void CLifeGauge::Update(void)
{
	//頂点情報の更新
	CGauge::Update();
}

//====================================================================
//描画処理
//====================================================================
void CLifeGauge::Draw(void)
{
	CGauge::Draw();
}