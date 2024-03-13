//============================================
//
//	左右のブロックの処理 [SideBlock3D.cpp]
//	Author:sakamoto kai
//
//============================================
#include "Sideblock3D.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "map2D.h"
#include "texture.h"
#include "DebugNumber3D.h"
#include "XModel.h"
#include "score.h"

//マクロ定義
#define BLOCK_WIGHT (400.0f)	//横幅
#define BLOCK_HEIGHT (2000.0f)	//縦幅

LPD3DXMESH CSide_Block3D::m_pMesh = NULL;				//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER CSide_Block3D::m_pBuffMat = NULL;			//マテリアルへのポインタ
DWORD CSide_Block3D::m_dwNumMat = NULL;					//マテリアルの数
int CSide_Block3D::m_nIdxXModel = NULL;					//マテリアルの数
//====================================================================
//コンストラクタ
//====================================================================
CSide_Block3D::CSide_Block3D(int nPriority) : CObjectXtex(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量
	m_nIdxTexture = 0;						//テクスチャの番号
	SetWight(BLOCK_WIGHT);					//縦の番号
	SetHeight(BLOCK_HEIGHT);				//縦の番号

	if (CScene::GetMode() == CScene::MODE_GAME)
	{
		switch (CGame::GetMap2D()->GetMapLevel() % 3 + 1)
		{
		case 1:
			m_BlockColor = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
			break;

		case 2:
			m_BlockColor = D3DXCOLOR(0.9f, 0.3f, 0.0f, 1.0f);
			break;

		case 3:
			m_BlockColor = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			break;

		default:
			m_BlockColor = D3DXCOLOR(0.9f, 0.3f, 0.0f, 1.0f);
			break;
		}
	}
	else
	{
		m_BlockColor = D3DXCOLOR(0.9f, 0.3f, 0.0f, 1.0f);
	}
	//m_BlockColor = D3DXCOLOR(0.21f, 0.76f, 0.24f, 1.0f);
	m_bColorChange = false;
}

//====================================================================
//デストラクタ
//====================================================================
CSide_Block3D::~CSide_Block3D()
{

}

//====================================================================
//生成処理
//====================================================================
CSide_Block3D *CSide_Block3D::Create()
{
	CSide_Block3D *pPlayer = NULL;

	if (pPlayer == NULL)
	{
		//オブジェクト2Dの生成
		pPlayer = new CSide_Block3D();
	}

	//Xファイルの割り当て
	CXModel *pXModel = CManager::GetInstance()->GetXModel();
	m_nIdxXModel = pXModel->Regist("data\\MODEL\\SideBlock00.x");
	pXModel->GetXModelInfo(&m_pBuffMat, &m_dwNumMat, &m_pMesh, m_nIdxXModel);
	pPlayer->BindFile(m_pMesh, m_pBuffMat, m_dwNumMat);

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
HRESULT CSide_Block3D::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\5.png");

	SetType(CObject::TYPE_SIDEBLOCK3D);

	CObjectXtex::Init();

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CSide_Block3D::Uninit(void)
{
	CObjectXtex::Uninit();
}

//====================================================================
//更新処理
//====================================================================
void CSide_Block3D::Update(void)
{
	//頂点情報の更新
	CObjectXtex::Update();
}

//====================================================================
//描画処理
//====================================================================
void CSide_Block3D::Draw(void)
{
	SetMatColor(m_BlockColor);

	CObjectXtex::Draw();
}

//====================================================================
//ブロックの色変更処理
//====================================================================
void CSide_Block3D::ChangeColor(int Level)
{
	switch (Level % 3)
	{
	case 0:
		m_BlockColor = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		break;

	case 1:
		m_BlockColor = D3DXCOLOR(0.9f, 0.3f, 0.0f, 1.0f);
		break;

	case 2:
		m_BlockColor = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		break;

	default:
		m_BlockColor = D3DXCOLOR(0.9f, 0.3f, 0.0f, 1.0f);
		break;
	}
}