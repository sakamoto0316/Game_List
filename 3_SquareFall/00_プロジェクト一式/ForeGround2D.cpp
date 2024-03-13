//============================================
//
//	前景の処理 [ForeGround2D.cpp]
//	Author:sakamoto kai
//
//============================================
#include "ForeGround2D.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"

//マクロ定義
#define NUMBER_WIGHT (1280.0f)		//横幅
#define NUMBER_HEIGHT (720.0f)		//縦幅

//====================================================================
//コンストラクタ
//====================================================================
CFG::CFG(int Cnt, int nType, int nPriority) : CObject2D(nPriority)
{
	SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	SetWight(NUMBER_WIGHT);
	SetHeight(NUMBER_HEIGHT);
	m_nLife = Cnt;
	m_nType = nType;
	m_bColorSet = false;
}

//====================================================================
//デストラクタ
//====================================================================
CFG::~CFG()
{

}

//====================================================================
//生成処理
//====================================================================
CFG *CFG::Create(int nCnt, int nType)
{
	CFG *pNumber = NULL;

	if (pNumber == NULL)
	{
		//オブジェクト2Dの生成
		pNumber = new CFG(nCnt, nType);
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
HRESULT CFG::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\Test.jpg");

	CObject2D::Init();

	SetType(CObject::TYPE_FG);

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CFG::Uninit(void)
{
	CObject2D::Uninit();
}

//====================================================================
//更新処理
//====================================================================
void CFG::Update(void)
{
	if (m_ColorCount > 0)
	{
		m_ColorCount--;
	}
	else
	{
		m_bColorSet = m_bColorSet ? false : true;
		m_ColorCount = 5;
	}

	switch (m_nType)
	{
	case 1:
		if (m_bColorSet == true)
		{
			SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.3f));
		}
		else
		{
			SetColor(D3DXCOLOR(0.8f, 0.8f, 0.8f, 0.3f));
		}
		break;
	default:
		break;
	}

	CObject2D::Update();

	if (m_nLife > 0)
	{
		m_nLife--;
	}
	else
	{
		Uninit();
	}
}

//====================================================================
//描画処理
//====================================================================
void CFG::Draw(void)
{
	CObject2D::Draw();
}