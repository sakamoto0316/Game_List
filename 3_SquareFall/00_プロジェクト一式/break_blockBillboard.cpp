//============================================
//
//	破壊可能ブロックの処理 [break_blockBillboard.cpp]
//	Author:sakamoto kai
//
//============================================
#include "break_blockBillboard.h"
#include "renderer.h"
#include "manager.h"
//#include "map2D.h"
#include "texture.h"
#include "DebugNumber3D.h"

//マクロ定義
#define BLOCK_WIGHT (40.0f)		//横幅
#define BLOCK_HEIGHT (40.0f)	//縦幅

bool CBreak_BlockBillboard::m_bUse[100][SET_BLOCK_WIGHT][SET_BLOCK_HEIGHT] = {};
//====================================================================
//コンストラクタ
//====================================================================
CBreak_BlockBillboard::CBreak_BlockBillboard(int nPriority) : CObjectBillboard(nPriority)
{
	SetWight(BLOCK_WIGHT);
	SetHeight(BLOCK_HEIGHT);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//====================================================================
//デストラクタ
//====================================================================
CBreak_BlockBillboard::~CBreak_BlockBillboard()
{

}

//====================================================================
//生成処理
//====================================================================
CBreak_BlockBillboard *CBreak_BlockBillboard::Create()
{
	CBreak_BlockBillboard *pPlayer = NULL;

	if (pPlayer == NULL)
	{
		//オブジェクト2Dの生成
		pPlayer = new CBreak_BlockBillboard();
	}

	//オブジェクトの初期化処理
	if (FAILED(pPlayer->Init()))
	{//初期化処理が失敗した場合
		return NULL;
	}

	return pPlayer;
}

//====================================================================
//初期化処理
//====================================================================
HRESULT CBreak_BlockBillboard::Init(void)
{
#if NUM == 1
	m_pWNumber = CDebugNumber3D::Create();
	m_pWNumber->SetWight(20.0f);
	m_pWNumber->SetHeight(20.0f);
	m_pWNumber->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	m_pHNumber = CDebugNumber3D::Create();
	m_pHNumber->SetWight(20.0f);
	m_pHNumber->SetHeight(20.0f);
	m_pHNumber->SetColor(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));

	m_pCNumber = CDebugNumber3D::Create();
	m_pCNumber->SetWight(20.0f);
	m_pCNumber->SetHeight(20.0f);
	m_pCNumber->SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));

	m_pBNumber = CDebugNumber3D::Create();
	m_pBNumber->SetWight(20.0f);
	m_pBNumber->SetHeight(20.0f);
	m_pBNumber->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
#endif // NUM

	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\block001.png");

	SetType(CObject::TYPE_BREAKBLOCK3D);

	CObjectBillboard::Init();

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CBreak_BlockBillboard::Uninit(void)
{
	m_bUse[m_CreateNumber][m_WightNumber][m_HeightNumber] = false;

	CObjectBillboard::Uninit();
}

//====================================================================
//更新処理
//====================================================================
void CBreak_BlockBillboard::Update(void)
{
#if NUM == 1
	if (m_pWNumber != NULL)
	{
		D3DXVECTOR3 pos = GetPos();
		m_pWNumber->SetNumber(m_WightNumber);
		m_pWNumber->SetPos(D3DXVECTOR3(pos.x - 10.0f, pos.y - 10.0f, pos.z));
	}

	if (m_pHNumber != NULL)
	{
		D3DXVECTOR3 pos = GetPos();
		m_pHNumber->SetNumber(m_HeightNumber);
		m_pHNumber->SetPos(D3DXVECTOR3(pos.x + 10.0f, pos.y + 10.0f, pos.z));
	}

	if (m_pCNumber != NULL)
	{
		D3DXVECTOR3 pos = GetPos();
		m_pCNumber->SetNumber(m_CreateNumber);
		m_pCNumber->SetPos(D3DXVECTOR3(pos.x + 10.0f, pos.y - 10.0f, pos.z));
	}

	if (m_pBNumber != NULL)
	{
		D3DXVECTOR3 pos = GetPos();
		if (m_bUse[m_CreateNumber][m_WightNumber][m_HeightNumber] == true)
		{
			m_pBNumber->SetNumber(1);
		}
		else
		{
			m_pBNumber->SetNumber(0);
		}
		m_pBNumber->SetPos(D3DXVECTOR3(pos.x - 10.0f, pos.y + 10.0f, pos.z));
	}
#endif // NUM

	SetTexture();

	//頂点情報の更新
	CObjectBillboard::Update();

	//m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\1.png");
}

//====================================================================
//描画処理
//====================================================================
void CBreak_BlockBillboard::Draw(void)
{
	CObjectBillboard::Draw();
}

//====================================================================
//当たり判定処理
//====================================================================
bool CBreak_BlockBillboard::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool bX)
{
	bool bOn = false;

	float myWight = GetWight() * 0.5f;
	float myHeight = GetHeight() * 0.5f;
	D3DXVECTOR3 mtPos = GetPos();


	if (bX == false)
	{
		if (
			(pPos->y < mtPos.y + myHeight &&
				pPosOld.y >= mtPos.y + myHeight) &&
			pPos->x + fWidth > mtPos.x - myWight &&
			pPos->x - fWidth < mtPos.x + myWight
			)
		{//上からめり込んだ時
			bOn = true;
			pPos->y = mtPos.y + myHeight;		//ブロックのうえにたたせる
			pMove->y = 0.0f;					//移動量を０にする
		}

		if (
			(pPos->y + fHeight > mtPos.y - myHeight &&
				pPosOld.y + fHeight <= mtPos.y - myHeight) &&
			pPos->x + fWidth > mtPos.x - myWight &&
			pPos->x - fWidth < mtPos.x + myWight
			)
		{//下からめり込んだ時
			pPos->y = mtPos.y - myHeight - fHeight;		//ブロックの下で止める
			pMove->y = 0.0f;					//移動量を０にする
		}
	}
	else
	{
		if (
			(pPos->x + fWidth > mtPos.x - myWight &&
				pPosOld.x + fWidth <= mtPos.x - myWight) &&
			pPos->y + fHeight > mtPos.y - myHeight &&
			pPos->y < mtPos.y + myHeight
			)
		{//左からめり込んだ時
			pPos->x = mtPos.x - myHeight - fWidth;		//ブロックの左で止める
			pMove->x = 0.0f;					//移動量を０にする
		}

		if (
			(pPos->x - fWidth < mtPos.x + myWight &&
				pPosOld.x - fWidth >= mtPos.x + myWight) &&
			pPos->y + fHeight > mtPos.y - myHeight &&
			pPos->y < mtPos.y + myHeight
			)
		{//右からめり込んだ時
			pPos->x = mtPos.x + myHeight + fWidth;		//ブロックの右で止める
			pMove->x = 0.0f;					//移動量を０にする
		}
	}

	return bOn;
}

//====================================================================
//テクスチャの設定処理
//====================================================================
void CBreak_BlockBillboard::SetTexture(void)
{
	//テクスチャの取得
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;

	if (m_bUse[m_CreateNumber][(m_WightNumber + 1) % SET_BLOCK_WIGHT][(m_HeightNumber) % SET_BLOCK_HEIGHT] == true)
	{
		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\3.png");
	}
	else
	{
		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\block001.png");
	}
}