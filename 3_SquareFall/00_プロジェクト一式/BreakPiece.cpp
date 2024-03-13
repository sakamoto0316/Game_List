//============================================
//
//	破壊されたブロックの処理 [breakPiece.cpp]
//	Author:sakamoto kai
//
//============================================
#include "BreakPiece.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "texture.h"
#include "DebugNumber3D.h"
#include "XModel.h"
#include "player3D.h"
#include "Map2D.h"

//マクロ定義
#define BLOCK_WIGHT (40.0f)		//横幅
#define BLOCK_HEIGHT (40.0f)	//縦幅
#define BLOCK_WAVE (90)	//振動時間

LPD3DXMESH CBreak_Piece::m_pMesh = NULL;				//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER CBreak_Piece::m_pBuffMat = NULL;			//マテリアルへのポインタ
DWORD CBreak_Piece::m_dwNumMat = NULL;					//マテリアルの数
int CBreak_Piece::m_nIdxXModel = NULL;					//マテリアルの数

//====================================================================
//コンストラクタ
//====================================================================
CBreak_Piece::CBreak_Piece(int nPriority) : CObjectXtex(nPriority)
{
	m_ColorA = 1.0f;

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

	m_move.x = sinf((float)(rand() % 731 - (731 - 1) / 2) / 100.0f + D3DX_PI * -0.5f)*(float)((rand() % 100) / 10.0f) + 2.0f;
	m_move.y = 7.5f;
	m_move.z = -0.75f;

	m_rot.x = (float)(rand() % 9 - 4) * 0.1f;
	m_rot.y = (float)(rand() % 9 - 4) * 0.1f;
	m_rot.z = (float)(rand() % 9 - 4) * 0.1f;
}

//====================================================================
//デストラクタ
//====================================================================
CBreak_Piece::~CBreak_Piece()
{

}

//====================================================================
//生成処理
//====================================================================
CBreak_Piece *CBreak_Piece::Create()
{
	CBreak_Piece *pPlayer = NULL;

	if (pPlayer == NULL)
	{
		//オブジェクト2Dの生成
		pPlayer = new CBreak_Piece();
	}

	//Xファイルの割り当て
	CXModel *pXModel = CManager::GetInstance()->GetXModel();

	int nRandModel = rand() % 3;

	switch (nRandModel)
	{
	case 0:
		m_nIdxXModel = pXModel->Regist("data\\MODEL\\break00.x");
		break;
	case 1:
		m_nIdxXModel = pXModel->Regist("data\\MODEL\\break01.x");
		break;
	case 2:
		m_nIdxXModel = pXModel->Regist("data\\MODEL\\break02.x");
		break;
	}

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
HRESULT CBreak_Piece::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");

	SetType(CObject::TYPE_EFFECT);

	CObjectXtex::Init();

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CBreak_Piece::Uninit(void)
{
	CObjectXtex::Uninit();
}

//====================================================================
//更新処理
//====================================================================
void CBreak_Piece::Update(void)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	//プレイヤーの位置を取得する
	CPlayer3D *pPlayer = CGame::GetPlayer3D();
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

	if (m_ColorA > 0.0f)
	{
		m_ColorA -= 0.02f;
	}
	m_BlockColor.a = m_ColorA;

	//重力
	m_move.y -= 0.98f;

	//減衰係数
	m_move.x = m_move.x * 0.98f;

	//位置設定
	pos += m_move;

	rot += m_rot;

	SetPos(pos);
	SetRot(rot);

	//頂点情報の更新
	CObjectXtex::Update();

	if (pos.y < PlayerPos.y - 400.0f)
	{
		Uninit();
	}
}

//====================================================================
//描画処理
//====================================================================
void CBreak_Piece::Draw(void)
{
	SetMatColor(m_BlockColor);

	CObjectXtex::Draw();
}