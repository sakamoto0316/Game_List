//============================================
//
//	ブロックのUIの処理 [BlockUI.cpp]
//	Author:sakamoto kai
//
//============================================
#include "BlockUI.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "XModel.h"
#include "debugproc.h"
#include "title.h"

//マクロ定義
#define NUMBER_WIGHT (200.0f)		//横幅
#define NUMBER_HEIGHT (50.0f)		//縦幅

LPD3DXMESH CBlockUI::m_pMesh = NULL;				//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER CBlockUI::m_pBuffMat = NULL;			//マテリアルへのポインタ
DWORD CBlockUI::m_dwNumMat = NULL;					//マテリアルの数
int CBlockUI::m_nIdxXModel = NULL;					//マテリアルの数

//====================================================================
//コンストラクタ
//====================================================================
CBlockUI::CBlockUI(int nPriority) : CObjectXtex(nPriority)
{
	SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	SetWight(NUMBER_WIGHT);
	SetHeight(NUMBER_HEIGHT);
	SetTexOne(true);
}

//====================================================================
//デストラクタ
//====================================================================
CBlockUI::~CBlockUI()
{

}

//====================================================================
//生成処理
//====================================================================
CBlockUI *CBlockUI::Create()
{
	CBlockUI *pNumber = NULL;

	if (pNumber == NULL)
	{
		//オブジェクト2Dの生成
		pNumber = new CBlockUI();
	}

	//Xファイルの割り当て
	CXModel *pXModel = CManager::GetInstance()->GetXModel();
	m_nIdxXModel = pXModel->Regist("data\\MODEL\\BlockUI01.x");
	pXModel->GetXModelInfo(&m_pBuffMat, &m_dwNumMat, &m_pMesh, m_nIdxXModel);
	pNumber->BindFile(m_pMesh, m_pBuffMat, m_dwNumMat);

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
HRESULT CBlockUI::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\Test.jpg");

	SetType(CObject::TYPE_BLOCKUI);

	CObjectXtex::Init();

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CBlockUI::Uninit(void)
{
	CObjectXtex::Uninit();
}

//====================================================================
//更新処理
//====================================================================
void CBlockUI::Update(void)
{
	//テクスチャの取得
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	switch (m_MyCount)
	{
	case 0:
		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\GameStart.png");
		break;

	case 1:
		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\TUTORIAL.png");
		break;

	case 2:
		m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\RANKING.png");
		break;

	default:
		break;
	}

	CObjectXtex::Update();

	//デバッグ表示
	CManager::GetInstance()->GetDebugProc()->Print("ブロックのX:[%f]\n", GetPos().x);
	CManager::GetInstance()->GetDebugProc()->Print("ブロックのY:[%f]\n", GetPos().y);
}

//====================================================================
//描画処理
//====================================================================
void CBlockUI::Draw(void)
{
	CObjectXtex::Draw();
}

//====================================================================
//当たり判定処理
//====================================================================
bool CBlockUI::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool bX)
{
	bool bOn = false;

	float myWight = GetWight() * 0.5f;
	float myHeight = GetHeight() * 0.5f;
	D3DXVECTOR3 myPos = GetPos();


	if (bX == false)
	{
		if (
			(pPos->y - fHeight < myPos.y + myHeight &&
				pPosOld.y - fHeight >= myPos.y + myHeight) &&
			pPos->x + fWidth > myPos.x - myWight &&
			pPos->x - fWidth < myPos.x + myWight
			)
		{//上からめり込んだ時
			bOn = true;
			pPos->y = myPos.y + myHeight + fHeight;		//ブロックのうえにたたせる
			pMove->y = 0.0f;					//移動量を０にする
		}

		if (
			(pPos->y + fHeight > myPos.y - myHeight &&
				pPosOld.y + fHeight <= myPos.y - myHeight) &&
			pPos->x + fWidth > myPos.x - myWight &&
			pPos->x - fWidth < myPos.x + myWight
			)
		{//下からめり込んだ時
			pPos->y = myPos.y - myHeight - fHeight;		//ブロックの下で止める
			pMove->y = 0.0f;					//移動量を０にする
		}
	}
	else
	{
		if (
			(pPos->x + fWidth > myPos.x - myWight &&
				pPosOld.x + fWidth <= myPos.x - myWight) &&
			pPos->y + fHeight > myPos.y - myHeight &&
			pPos->y - fHeight < myPos.y + myHeight
			)
		{//左からめり込んだ時
			pPos->x = myPos.x - myWight - fWidth;		//ブロックの左で止める
			pMove->x = 0.0f;					//移動量を０にする
		}

		if (
			(pPos->x - fWidth < myPos.x + myWight &&
				pPosOld.x - fWidth >= myPos.x + myWight) &&
			pPos->y + fHeight > myPos.y - myHeight &&
			pPos->y - fHeight< myPos.y + myHeight
			)
		{//右からめり込んだ時
			pPos->x = myPos.x + myWight + fWidth;		//ブロックの右で止める
			pMove->x = 0.0f;					//移動量を０にする
		}
	}

	return bOn;
}

//====================================================================
//当たり判定処理
//====================================================================
void CBlockUI::Hit(D3DXVECTOR3 pos, int Damage)
{
	CTitle::SetSelectColor(m_MyCount);
}