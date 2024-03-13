//============================================
//
//	エディット用ブロックの処理 [EditBlock3D.cpp]
//	Author:sakamoto kai
//
//============================================
#include "EditBlock3D.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "DebugNumber3D.h"
#include "XModel.h"
#include "score.h"

//マクロ定義
#define BLOCK_WIGHT (40.0f)		//横幅
#define BLOCK_HEIGHT (40.0f)	//縦幅
#define BLOCK_WAVE (90)	//振動時間

bool CEdit_Block3D::m_bUse[100][SET_BLOCK_WIGHT + 2][SET_BLOCK_HEIGHT] = {};
LPD3DXMESH CEdit_Block3D::m_pMesh = NULL;				//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER CEdit_Block3D::m_pBuffMat = NULL;			//マテリアルへのポインタ
DWORD CEdit_Block3D::m_dwNumMat = NULL;					//マテリアルの数
int CEdit_Block3D::m_nIdxXModel = NULL;					//マテリアルの数
//====================================================================
//コンストラクタ
//====================================================================
CEdit_Block3D::CEdit_Block3D(int nPriority) : CObjectXtex(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量
	m_nIdxTexture = 0;					//テクスチャの番号
	m_CreateNumber = 0;					//生成の番号
	m_WightNumber = 0;					//横の番号
	m_HeightNumber = 0;					//縦の番号
	SetWight(BLOCK_WIGHT);				//縦の番号
	SetHeight(BLOCK_HEIGHT);			//縦の番号
	m_nWaveCount = 0;
	m_bBreak = false;
	m_bWave = false;
	m_nBreakCount = 0;
	m_nWavePower = 0.0f;
}

//====================================================================
//デストラクタ
//====================================================================
CEdit_Block3D::~CEdit_Block3D()
{

}

//====================================================================
//生成処理
//====================================================================
CEdit_Block3D *CEdit_Block3D::Create()
{
	CEdit_Block3D *pBlock = NULL;

	if (pBlock == NULL)
	{
		//オブジェクト2Dの生成
		pBlock = new CEdit_Block3D();
	}

	//Xファイルの割り当て
	CXModel *pXModel = CManager::GetInstance()->GetXModel();
	m_nIdxXModel = pXModel->Regist("data\\MODEL\\block00.x");
	pXModel->GetXModelInfo(&m_pBuffMat, &m_dwNumMat, &m_pMesh, m_nIdxXModel);
	pBlock->BindFile(m_pMesh, m_pBuffMat, m_dwNumMat);

	//オブジェクトの初期化処理
	if (FAILED(pBlock->Init()))
	{//初期化処理が失敗した場合
		return NULL;
	}

	return pBlock;
}

//====================================================================
//初期化処理
//====================================================================
HRESULT CEdit_Block3D::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\block001.png");

	SetType(CObject::TYPE_EDITBLOCK3D);

	CObjectXtex::Init();

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CEdit_Block3D::Uninit(void)
{
	m_bUse[m_CreateNumber][m_WightNumber][m_HeightNumber] = false;

	CObjectXtex::Uninit();
}

//====================================================================
//更新処理
//====================================================================
void CEdit_Block3D::Update(void)
{
	SetPos(D3DXVECTOR3(-400.0f + 40.0f * m_WightNumber,400.0f - 40.0f * m_HeightNumber, -5.0f));

	//頂点情報の更新
	CObjectXtex::Update();
}

//====================================================================
//描画処理
//====================================================================
void CEdit_Block3D::Draw(void)
{
	SetMatColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f));

	CObjectXtex::Draw();
}

//====================================================================
//ブロックの使用番号設定
//====================================================================
void CEdit_Block3D::bUseSet(void)
{
	for (int nCntCreate = 0; nCntCreate < 100; nCntCreate++)
	{
		for (int nCntObjHeight = 0; nCntObjHeight < SET_BLOCK_HEIGHT; nCntObjHeight++)
		{
			for (int nCntObjWight = 0; nCntObjWight < 2; nCntObjWight++)
			{
				m_bUse[nCntCreate][nCntObjWight * (SET_BLOCK_WIGHT + 1)][nCntObjHeight] = true;
			}
		}
	}
}