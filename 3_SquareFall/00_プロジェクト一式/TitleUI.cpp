//============================================
//
//	タイトルのUIの処理 [TitleUI.cpp]
//	Author:sakamoto kai
//
//============================================
#include "TitleUI.h"
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

LPD3DXMESH CTitleUI::m_pMesh = NULL;				//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER CTitleUI::m_pBuffMat = NULL;			//マテリアルへのポインタ
DWORD CTitleUI::m_dwNumMat = NULL;					//マテリアルの数
int CTitleUI::m_nIdxXModel = NULL;					//マテリアルの数

//====================================================================
//コンストラクタ
//====================================================================
CTitleUI::CTitleUI(int nPriority) : CObjectXtex(nPriority)
{
	SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	SetWight(NUMBER_WIGHT);
	SetHeight(NUMBER_HEIGHT);
}

//====================================================================
//デストラクタ
//====================================================================
CTitleUI::~CTitleUI()
{

}

//====================================================================
//生成処理
//====================================================================
CTitleUI *CTitleUI::Create()
{
	CTitleUI *pNumber = NULL;

	if (pNumber == NULL)
	{
		//オブジェクト2Dの生成
		pNumber = new CTitleUI();
	}

	//Xファイルの割り当て
	CXModel *pXModel = CManager::GetInstance()->GetXModel();
	m_nIdxXModel = pXModel->Regist("data\\MODEL\\SquareFall.x");
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
HRESULT CTitleUI::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\SquareFall.png");

	SetType(CObject::TYPE_BG);

	CObjectXtex::Init();

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CTitleUI::Uninit(void)
{
	CObjectXtex::Uninit();
}

//====================================================================
//更新処理
//====================================================================
void CTitleUI::Update(void)
{
	CObjectXtex::Update();
}

//====================================================================
//描画処理
//====================================================================
void CTitleUI::Draw(void)
{
	CObjectXtex::Draw();
}