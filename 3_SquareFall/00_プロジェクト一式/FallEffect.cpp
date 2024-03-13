//============================================
//
//	最高速度落下時の演出ポリゴンの処理 [FallEffect.cpp]
//	Author:sakamoto kai
//
//============================================
#include "FallEffect.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"

//マクロ定義
#define NUMBER_WIGHT (2.0f)		//横幅
#define NUMBER_HEIGHT (20.0f)	//縦幅

//====================================================================
//コンストラクタ
//====================================================================
CFallEffect::CFallEffect(int nPriority) : CObjectBillboard(nPriority)
{
	SetWight(NUMBER_WIGHT);
	SetHeight(NUMBER_HEIGHT);

	m_MoveUP = (float)((rand() % 5) + 16);
	m_nLife = 0;
}

//====================================================================
//デストラクタ
//====================================================================
CFallEffect::~CFallEffect()
{

}

//====================================================================
//生成処理
//====================================================================
CFallEffect *CFallEffect::Create(void)
{
	CFallEffect *pNumber = NULL;

	if (pNumber == NULL)
	{
		//オブジェクト2Dの生成
		pNumber = new CFallEffect();
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
HRESULT CFallEffect::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\Test.jpg");

	SetType(CObject::TYPE_FALLEFFECT);

	CObjectBillboard::Init();

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CFallEffect::Uninit(void)
{
	CObjectBillboard::Uninit();
}

//====================================================================
//更新処理
//====================================================================
void CFallEffect::Update(void)
{
	D3DXVECTOR3 Pos = GetPos();

	Pos.y += m_MoveUP;

	SetPos(Pos);

	//頂点情報の更新
	CObjectBillboard::Update();

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
void CFallEffect::Draw(void)
{
	CObjectBillboard::Draw();
}