//============================================
//
//	破壊可能ブロックの処理 [break_block3D.cpp]
//	Author:sakamoto kai
//
//============================================
#include "break_block3D.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "map2D.h"
#include "texture.h"
#include "DebugNumber3D.h"
#include "XModel.h"
#include "score.h"
#include "Break.h"

//マクロ定義
#define BLOCK_WIGHT (40.0f)		//横幅
#define BLOCK_HEIGHT (40.0f)	//縦幅
#define BLOCK_WAVE (90)	//振動時間

bool CBreak_Block3D::m_bUse[100][SET_BLOCK_WIGHT + 2][SET_BLOCK_HEIGHT] = {};
LPD3DXMESH CBreak_Block3D::m_pMesh = NULL;				//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER CBreak_Block3D::m_pBuffMat = NULL;			//マテリアルへのポインタ
DWORD CBreak_Block3D::m_dwNumMat = NULL;					//マテリアルの数
int CBreak_Block3D::m_nIdxXModel = NULL;					//マテリアルの数
//====================================================================
//コンストラクタ
//====================================================================
CBreak_Block3D::CBreak_Block3D(int nPriority) : CObjectXtex(nPriority)
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
CBreak_Block3D::~CBreak_Block3D()
{

}

//====================================================================
//生成処理
//====================================================================
CBreak_Block3D *CBreak_Block3D::Create()
{
	CBreak_Block3D *pPlayer = NULL;

	if (pPlayer == NULL)
	{
		//オブジェクト2Dの生成
		pPlayer = new CBreak_Block3D();
	}

	//Xファイルの割り当て
	CXModel *pXModel = CManager::GetInstance()->GetXModel();
	m_nIdxXModel = pXModel->Regist("data\\MODEL\\block00.x");
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
HRESULT CBreak_Block3D::Init(void)
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

	CObjectXtex::Init();

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CBreak_Block3D::Uninit(void)
{
	if (CGame::GetEventStart() == false)
	{
		m_bUse[m_CreateNumber][m_WightNumber][m_HeightNumber] = false;

		CObjectXtex::Uninit();
	}
}

//====================================================================
//更新処理
//====================================================================
void CBreak_Block3D::Update(void)
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

	if (Break() == true)
	{
		return;
	}

	if (m_bWave == true)
	{
		Wave();
	}

	//頂点情報の更新
	CObjectXtex::Update();

	//m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\1.png");
}

//====================================================================
//描画処理
//====================================================================
void CBreak_Block3D::Draw(void)
{
	SetMatColor(m_BlockColor);

	CObjectXtex::Draw();
}

//====================================================================
//振動処理
//====================================================================
void CBreak_Block3D::Wave(void)
{
	D3DXVECTOR3 pos = GetPos();
	SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z + sinf((BLOCK_WAVE / ((float)m_nWaveCount * 2.0f)) * 4.5f) * m_nWavePower));

	m_nWaveCount--;

	if (m_nWaveCount <= 0)
	{
		m_bWave = false;
	}
}

//====================================================================
//ダメージヒット処理
//====================================================================
void CBreak_Block3D::Hit(D3DXVECTOR3 pos, int Damage)
{
	if (CGame::GetEventStart() == false)
	{
		//スコアの加算
		CGame::GetScore()->AddScore(30);

		if (m_bWave == false)
		{
			BreakCountSet(5);

			if (Damage >= 10)
			{
				m_nWavePower = 5.0f;
			}
			else
			{
				m_nWavePower = 2.0f;
			}
		}
	}
}

//====================================================================
//ブロックの破壊処理
//====================================================================
bool CBreak_Block3D::Break(void)
{
	if (m_nBreakCount > 0)
	{
		m_nBreakCount--;
	}

	if (m_bBreak == true
		&& m_nBreakCount <= 0)
	{
		m_bBreak = false;

		//スコアの加算
		CGame::GetScore()->AddScore(30);

		CBreak *pPiece = CBreak::Create(GetPos());

		m_bUse[m_CreateNumber][m_WightNumber][m_HeightNumber] = false;

		CObjectXtex::Uninit();

		return true;
	}

	return false;
}

//====================================================================
//壊れるブロックの処理
//====================================================================
void CBreak_Block3D::BreakCountSet(int nCount)
{
	if (CGame::GetEventStart() == false)
	{
		//テクスチャの取得
		CTexture *pTexture = CManager::GetInstance()->GetTexture();

		if (m_bBreak == false)
		{
			if (strcmp("data\\TEXTURE\\5.png", pTexture->GetTextureName(m_nIdxTexture)) != 0)
			{
				m_bBreak = true;
				m_nBreakCount = nCount;
			}
			else
			{
				m_bWave = true;
				m_nWaveCount = BLOCK_WAVE;
			}
		}
	}
}

//====================================================================
//壊れるブロックの処理
//====================================================================
void CBreak_Block3D::CreateMapBlocks(int CreateNumber, D3DXVECTOR3 pos)
{
	for (int nCntObjHeight = 0; nCntObjHeight < SET_BLOCK_HEIGHT; nCntObjHeight++)
	{
		for (int nCntObjWight = 0 + 1; nCntObjWight < SET_BLOCK_WIGHT + 1; nCntObjWight++)
		{
			if (CBreak_Block3D::GetCheckUse(CreateNumber, nCntObjWight, nCntObjHeight) == true)
			{
				CBreak_Block3D *m_pBreakBlock3D = CBreak_Block3D::Create();
				if (CScene::GetMode() == CScene::MODE_GAME)
				{
					m_pBreakBlock3D->SetPos(D3DXVECTOR3(pos.x + 40.0f * nCntObjWight, ((float)((int)CGame::GetMap2D()->GetDepth() / 1000.0f) * 1000.0f) + pos.y - (40.0f * nCntObjHeight), pos.z));
				}
				else
				{
					m_pBreakBlock3D->SetPos(D3DXVECTOR3(pos.x + 40.0f * nCntObjWight,pos.y - (40.0f * nCntObjHeight), pos.z));
				}
				m_pBreakBlock3D->SetCNumber(CreateNumber);
				m_pBreakBlock3D->SetWNumber(nCntObjWight);
				m_pBreakBlock3D->SetHNumber(nCntObjHeight);
				m_pBreakBlock3D->SetUse(CreateNumber, nCntObjWight, nCntObjHeight, true);
			}
		}
	}
}

//====================================================================
//当たり判定処理
//====================================================================
bool CBreak_Block3D::Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool bX)
{
	bool bOn = false;

	float myWight = GetWight() * 0.5f;
	float myHeight = GetHeight() * 0.5f;
	D3DXVECTOR3 mtPos = GetPos();


	if (bX == false)
	{
		if (
			(pPos->y - fHeight < mtPos.y + myHeight &&
				pPosOld.y - fHeight >= mtPos.y + myHeight) &&
			pPos->x + fWidth > mtPos.x - myWight &&
			pPos->x - fWidth < mtPos.x + myWight
			)
		{//上からめり込んだ時
			bOn = true;
			pPos->y = mtPos.y + myHeight + fHeight;		//ブロックのうえにたたせる
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
			pPos->y - fHeight < mtPos.y + myHeight
			)
		{//左からめり込んだ時
			pPos->x = mtPos.x - myHeight - fWidth;		//ブロックの左で止める
			pMove->x = 0.0f;					//移動量を０にする
		}

		if (
			(pPos->x - fWidth < mtPos.x + myWight &&
				pPosOld.x - fWidth >= mtPos.x + myWight) &&
			pPos->y + fHeight > mtPos.y - myHeight &&
			pPos->y - fHeight< mtPos.y + myHeight
			)
		{//右からめり込んだ時
			pPos->x = mtPos.x + myHeight + fWidth;		//ブロックの右で止める
			pMove->x = 0.0f;					//移動量を０にする
		}
	}

	return bOn;
}

//====================================================================
//ブロックの使用番号設定
//====================================================================
void CBreak_Block3D::bUseSet(void)
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

//====================================================================
//使用番号を使ったブロックの破壊
//====================================================================
void CBreak_Block3D::UseBreak(int Create, int Wight, int Height)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//オブジェクトを取得
		CObject *pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			CObject *pObjNext = pObj->GetNext();

			CObject::TYPE type = pObj->GetType();				//種類を取得

			if (type == TYPE_BREAKBLOCK3D)
			{//種類がブロックの時
				CBreak_Block3D *m_pBBlock = (CBreak_Block3D*)pObj;

				if (m_pBBlock->GetCNumber() == Create &&
					m_pBBlock->GetWNumber() == Wight &&
					m_pBBlock->GetHNumber() == Height)
				{
					pObj->Uninit();
				}
			}

			pObj = pObjNext;
		}
	}
}

//====================================================================
//ブロックの色変更処理
//====================================================================
void CBreak_Block3D::ChangeColor(int Level)
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

//====================================================================
//ブロックの色変更処理
//====================================================================
void CBreak_Block3D::CleanBlockUse(void)
{
	for (int nCntCreate = 0; nCntCreate < 100; nCntCreate++)
	{
		for (int nCntObjHeight = 0; nCntObjHeight < SET_BLOCK_HEIGHT; nCntObjHeight++)
		{
			for (int nCntObjWight = 0; nCntObjWight < SET_BLOCK_WIGHT + 2; nCntObjWight++)
			{
				m_bUse[nCntCreate][nCntObjWight][nCntObjHeight] = false;
			}
		}
	}
}

//====================================================================
//テクスチャの設定処理
//====================================================================
void CBreak_Block3D::SetTexture(void)
{
	//テクスチャの取得
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	int CANumber = m_CreateNumber;
	int CDNumber = m_CreateNumber;
	int HANumber = m_HeightNumber + 1;
	int HDNumber = m_HeightNumber - 1;

	if (HDNumber < 0)
	{
		HDNumber = SET_BLOCK_HEIGHT - 1;
		CDNumber--;
		if (CDNumber < 0)
		{
			CDNumber = 0;
		}
	}
	else if (HANumber >= SET_BLOCK_HEIGHT)
	{
		HANumber = 0;
		CANumber++;
	}

	if (m_bUse[CDNumber][m_WightNumber + 1][HDNumber] == false)
	{//右上なし
		if (m_bUse[CANumber][m_WightNumber + 1][HANumber] == false)
		{//右下なし
			if (m_bUse[CANumber][m_WightNumber - 1][HANumber] == false)
			{//左下なし
				if (m_bUse[CDNumber][m_WightNumber - 1][HDNumber] == false)
				{//左上なし
					m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
				}
				else
				{//左上あり
					if (m_bUse[CDNumber][(m_WightNumber) % SET_BLOCK_WIGHT][HDNumber] == false)
					{//上なし
						m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
					}
					else
					{//上あり
						if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
						{//左なし
							m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
						}
						else
						{//左あり
							m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\12369.png");
						}
					}
				}
			}
			else
			{//左下あり
				if (m_bUse[CDNumber][m_WightNumber - 1][HDNumber] == false)
				{//左上なし
					if (m_bUse[CANumber][(m_WightNumber) % SET_BLOCK_WIGHT][HANumber] == false)
					{//下なし
						m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
					}
					else
					{//下あり
						if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
						{//左なし
							m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
						}
						else
						{//左あり
							m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\36789.png");
						}
					}
				}
				else
				{//左上あり
					if (m_bUse[CDNumber][(m_WightNumber) % SET_BLOCK_WIGHT][HDNumber] == false)
					{//上なし
						if (m_bUse[CANumber][(m_WightNumber) % SET_BLOCK_WIGHT][HANumber] == false)
						{//下なし
							m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
						}
						else
						{//下あり
							if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
							{//左なし
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
							}
							else
							{//左あり
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\36789.png");
							}
						}
					}
					else
					{//上あり
						if (m_bUse[CANumber][(m_WightNumber) % SET_BLOCK_WIGHT][HANumber] == false)
						{//下なし
							if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
							{//左なし
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
							}
							else
							{//左あり
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\12369.png");
							}
						}
						else
						{//下あり
							if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
							{//左なし
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
							}
							else
							{//左あり
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\369.png");
							}
						}
					}
				}
			}
		}
		else
		{//右下あり
			if (m_bUse[CANumber][m_WightNumber - 1][HANumber] == false)
			{//左下なし
				if (m_bUse[CDNumber][m_WightNumber - 1][HDNumber] == false)
				{//左上なし
					if (m_bUse[m_CreateNumber][m_WightNumber + 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
					{//右なし
						m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
					}
					else
					{//右あり
						if (m_bUse[CANumber][(m_WightNumber) % SET_BLOCK_WIGHT][HANumber] == false)
						{//下なし
							m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
						}
						else
						{//下あり
							m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\14789.png");
						}
					}
				}
				else
				{//左上あり
					if (m_bUse[CDNumber][(m_WightNumber) % SET_BLOCK_WIGHT][HDNumber] == false)
					{//上なし
						if (m_bUse[m_CreateNumber][m_WightNumber + 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
						{//右なし
							m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
						}
						else
						{//右あり
							if (m_bUse[CANumber][(m_WightNumber) % SET_BLOCK_WIGHT][HANumber] == false)
							{//下なし
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
							}
							else
							{//下あり
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\14789.png");
							}
						}
					}
					else
					{//上あり
						if (m_bUse[m_CreateNumber][m_WightNumber + 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
						{//右なし
							if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
							{//左なし
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
							}
							else
							{//左あり
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\12369.png");
							}
						}
						else
						{//右あり
							if (m_bUse[CANumber][(m_WightNumber) % SET_BLOCK_WIGHT][HANumber] == false)
							{//下なし
								if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
								{//左なし
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
								}
								else
								{//左あり
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\12369.png");
								}
							}
							else
							{//下あり
								if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
								{//左なし
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\14789.png");
								}
								else
								{//左あり
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\19.png");
								}
							}
						}
					}
				}
			}
			else
			{//左下あり
				if (m_bUse[CDNumber][m_WightNumber - 1][HDNumber] == false)
				{//左上なし
					if (m_bUse[m_CreateNumber][m_WightNumber + 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
					{//右なし
						if (m_bUse[CANumber][(m_WightNumber) % SET_BLOCK_WIGHT][HANumber] == false)
						{//下なし
							m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
						}
						else
						{//下あり
							if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
							{//左なし
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
							}
							else
							{//左あり
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\36789.png");
							}
						}
					}
					else
					{//右あり
						if (m_bUse[CANumber][(m_WightNumber) % SET_BLOCK_WIGHT][HANumber] == false)
						{//下なし
							m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
						}
						else
						{//下あり
							if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
							{//左なし
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\14789.png");
							}
							else
							{//左あり
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\789.png");
							}
						}
					}
				}
				else
				{//左上あり
					if (m_bUse[CDNumber][(m_WightNumber) % SET_BLOCK_WIGHT][HDNumber] == false)
					{//上なし
						if (m_bUse[m_CreateNumber][m_WightNumber + 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
						{//右なし
							if (m_bUse[CANumber][(m_WightNumber) % SET_BLOCK_WIGHT][HANumber] == false)
							{//下なし
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
							}
							else
							{//下あり
								if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
								{//左なし
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
								}
								else
								{//左あり
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\36789.png");
								}
							}
						}
						else
						{//右あり
							if (m_bUse[CANumber][(m_WightNumber) % SET_BLOCK_WIGHT][HANumber] == false)
							{//下なし
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
							}
							else
							{//下あり
								if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
								{//左なし
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\14789.png");
								}
								else
								{//左あり
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\789.png");
								}
							}
						}
					}
					else
					{//上あり
						if (m_bUse[m_CreateNumber][m_WightNumber + 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
						{//右なし
							if (m_bUse[CANumber][(m_WightNumber) % SET_BLOCK_WIGHT][HANumber] == false)
							{//下なし
								if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
								{//左なし
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
								}
								else
								{//左あり
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\12369.png");
								}
							}
							else
							{//下あり
								if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
								{//左なし
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
								}
								else
								{//左あり
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\369.png");
								}
							}
						}
						else
						{//右あり
							if (m_bUse[CANumber][(m_WightNumber) % SET_BLOCK_WIGHT][HANumber] == false)
							{//下なし
								if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
								{//左なし
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
								}
								else
								{//左あり
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\12369.png");
								}
							}
							else
							{//下あり
								if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
								{//左なし
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\14789.png");
								}
								else
								{//左あり
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\9.png");
								}
							}
						}
					}
				}
			}
		}
	}
	else
	{//右上あり
		if (m_bUse[CANumber][m_WightNumber + 1][HANumber] == false)
		{//右下なし
			if (m_bUse[CANumber][m_WightNumber - 1][HANumber] == false)
			{//左下なし
				if (m_bUse[CDNumber][m_WightNumber - 1][HDNumber] == false)
				{//左上なし
					if (m_bUse[CDNumber][(m_WightNumber) % SET_BLOCK_WIGHT][HDNumber] == false)
					{//上なし
						m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
					}
					else
					{//上あり
						if (m_bUse[m_CreateNumber][m_WightNumber + 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
						{//右なし
							m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
						}
						else
						{//右あり
							m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\12347.png");
						}
					}
				}
				else
				{//左上あり
					if (m_bUse[CDNumber][(m_WightNumber) % SET_BLOCK_WIGHT][HDNumber] == false)
					{//上なし
						m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
					}
					else
					{//上あり
						if (m_bUse[m_CreateNumber][m_WightNumber + 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
						{//右なし
							if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
							{//左なし
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
							}
							else
							{//左あり
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\12369.png");
							}
						}
						else
						{//右あり
							if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
							{//左なし
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\12347.png");
							}
							else
							{//左あり
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\123.png");
							}
						}
					}
				}
			}
			else
			{//左下あり
				if (m_bUse[CDNumber][m_WightNumber - 1][HDNumber] == false)
				{//左上なし
					if (m_bUse[CDNumber][(m_WightNumber) % SET_BLOCK_WIGHT][HDNumber] == false)
					{//上なし
						if (m_bUse[CANumber][(m_WightNumber) % SET_BLOCK_WIGHT][HANumber] == false)
						{//下なし
							m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
						}
						else
						{//下あり
							if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
							{//左なし
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
							}
							else
							{//左あり
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\36789.png");
							}
						}
					}
					else
					{//上あり
						if (m_bUse[m_CreateNumber][m_WightNumber + 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
						{//右なし
							if (m_bUse[CANumber][(m_WightNumber) % SET_BLOCK_WIGHT][HANumber] == false)
							{//下なし
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
							}
							else
							{//下あり
								if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
								{//左なし
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
								}
								else
								{//左あり
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\36789.png");
								}
							}
						}
						else
						{//右あり
							if (m_bUse[CANumber][(m_WightNumber) % SET_BLOCK_WIGHT][HANumber] == false)
							{//下なし
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\12347.png");
							}
							else
							{//下あり
								if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
								{//左なし
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\12347.png");
								}
								else
								{//左あり
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\37.png");
								}
							}
						}
					}
				}
				else
				{//左上あり
					if (m_bUse[CDNumber][(m_WightNumber) % SET_BLOCK_WIGHT][HDNumber] == false)
					{//上なし
						if (m_bUse[m_CreateNumber][m_WightNumber + 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
						{//右なし
							if (m_bUse[CANumber][(m_WightNumber) % SET_BLOCK_WIGHT][HANumber] == false)
							{//下なし
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
							}
							else
							{//下あり
								if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
								{//左なし
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
								}
								else
								{//左あり
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\36789.png");
								}
							}
						}
						else
						{//右あり
							if (m_bUse[CANumber][(m_WightNumber) % SET_BLOCK_WIGHT][HANumber] == false)
							{//下なし
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
							}
							else
							{//下あり
								if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
								{//左なし
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
								}
								else
								{//左あり
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\36789.png");
								}
							}
						}
					}
					else
					{//上あり
						if (m_bUse[m_CreateNumber][m_WightNumber + 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
						{//右なし
							if (m_bUse[CANumber][(m_WightNumber) % SET_BLOCK_WIGHT][HANumber] == false)
							{//下なし
								if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
								{//左なし
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
								}
								else
								{//左あり
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\12369.png");
								}
							}
							else
							{//下あり
								if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
								{//左なし
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
								}
								else
								{//左あり
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\369.png");
								}
							}
						}
						else
						{//右あり
							if (m_bUse[CANumber][(m_WightNumber) % SET_BLOCK_WIGHT][HANumber] == false)
							{//下なし
								if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
								{//左なし
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\12347.png");
								}
								else
								{//左あり
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\123.png");
								}
							}
							else
							{//下あり
								if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
								{//左なし
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\12347.png");
								}
								else
								{//左あり
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\3.png");
								}
							}
						}
					}
				}
			}
		}
		else
		{//右下あり
			if (m_bUse[CANumber][m_WightNumber - 1][HANumber] == false)
			{//左下なし
				if (m_bUse[CDNumber][m_WightNumber - 1][HDNumber] == false)
				{//左上なし
					if (m_bUse[CDNumber][(m_WightNumber) % SET_BLOCK_WIGHT][HDNumber] == false)
					{//上なし
						if (m_bUse[m_CreateNumber][m_WightNumber + 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
						{//右なし
							m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
						}
						else
						{//右あり
							if (m_bUse[CANumber][(m_WightNumber) % SET_BLOCK_WIGHT][HANumber] == false)
							{//下なし
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
							}
							else
							{//下あり
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\14789.png");
							}
						}
					}
					else
					{//上あり
						if (m_bUse[m_CreateNumber][m_WightNumber + 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
						{//右なし
							m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
						}
						else
						{//右あり
							if (m_bUse[CANumber][(m_WightNumber) % SET_BLOCK_WIGHT][HANumber] == false)
							{//下なし
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\12347.png");
							}
							else
							{//下あり
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\147.png");
							}
						}
					}
				}
				else
				{//左上あり
					if (m_bUse[CDNumber][(m_WightNumber) % SET_BLOCK_WIGHT][HDNumber] == false)
					{//上なし
						if (m_bUse[m_CreateNumber][m_WightNumber + 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
						{//右なし
							m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
						}
						else
						{//右あり
							if (m_bUse[CANumber][(m_WightNumber) % SET_BLOCK_WIGHT][HANumber] == false)
							{//下なし
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
							}
							else
							{//下あり
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\14789.png");
							}
						}
					}
					else
					{//上あり
						if (m_bUse[m_CreateNumber][m_WightNumber + 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
						{//右なし
							if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
							{//左なし
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
							}
							else
							{//左あり
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\12369.png");
							}
						}
						else
						{//右あり
							if (m_bUse[CANumber][(m_WightNumber) % SET_BLOCK_WIGHT][HANumber] == false)
							{//下なし
								if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
								{//左なし
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\12347.png");
								}
								else
								{//左あり
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\123.png");
								}
							}
							else
							{//下あり
								if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
								{//左なし
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\147.png");
								}
								else
								{//左あり
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\1.png");
								}
							}
						}
					}
				}
			}
			else
			{//左下あり
				if (m_bUse[CDNumber][m_WightNumber - 1][HDNumber] == false)
				{//左上なし
					if (m_bUse[CDNumber][(m_WightNumber) % SET_BLOCK_WIGHT][HDNumber] == false)
					{//上なし
						if (m_bUse[m_CreateNumber][m_WightNumber + 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
						{//右なし
							if (m_bUse[CANumber][(m_WightNumber) % SET_BLOCK_WIGHT][HANumber] == false)
							{//下なし
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
							}
							else
							{//下あり
								if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
								{//左なし
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
								}
								else
								{//左あり
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\36789.png");
								}
							}
						}
						else
						{//右あり
							if (m_bUse[CANumber][(m_WightNumber) % SET_BLOCK_WIGHT][HANumber] == false)
							{//下なし
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
							}
							else
							{//下あり
								if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
								{//左なし
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\14789.png");
								}
								else
								{//左あり
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\789.png");
								}
							}
						}
					}
					else
					{//上あり
						if (m_bUse[m_CreateNumber][m_WightNumber + 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
						{//右なし
							if (m_bUse[CANumber][(m_WightNumber) % SET_BLOCK_WIGHT][HANumber] == false)
							{//下なし
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
							}
							else
							{//下あり
								if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
								{//左なし
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
								}
								else
								{//左あり
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\36789.png");
								}
							}
						}
						else
						{//右あり
							if (m_bUse[CANumber][(m_WightNumber) % SET_BLOCK_WIGHT][HANumber] == false)
							{//下なし
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\12347.png");
							}
							else
							{//下あり
								if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
								{//左なし
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\147.png");
								}
								else
								{//左あり
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\7.png");
								}
							}
						}
					}
				}
				else
				{//左上あり
					if (m_bUse[CDNumber][(m_WightNumber) % SET_BLOCK_WIGHT][HDNumber] == false)
					{//上なし
						if (m_bUse[m_CreateNumber][m_WightNumber + 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
						{//右なし
							if (m_bUse[CANumber][(m_WightNumber) % SET_BLOCK_WIGHT][HANumber] == false)
							{//下なし
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
							}
							else
							{//下あり
								if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
								{//左なし
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
								}
								else
								{//左あり
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\36789.png");
								}
							}
						}
						else
						{//右あり
							if (m_bUse[CANumber][(m_WightNumber) % SET_BLOCK_WIGHT][HANumber] == false)
							{//下なし
								m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
							}
							else
							{//下あり
								if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
								{//左なし
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\14789.png");
								}
								else
								{//左あり
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\789.png");
								}
							}
						}
					}
					else
					{//上あり
						if (m_bUse[m_CreateNumber][m_WightNumber + 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
						{//右なし
							if (m_bUse[CANumber][(m_WightNumber) % SET_BLOCK_WIGHT][HANumber] == false)
							{//下なし
								if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
								{//左なし
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
								}
								else
								{//左あり
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\12369.png");
								}
							}
							else
							{//下あり
								if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
								{//左なし
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\0.png");
								}
								else
								{//左あり
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\369.png");
								}
							}
						}
						else
						{//右あり
							if (m_bUse[CANumber][(m_WightNumber) % SET_BLOCK_WIGHT][HANumber] == false)
							{//下なし
								if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
								{//左なし
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\12347.png");
								}
								else
								{//左あり
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\123.png");
								}
							}
							else
							{//下あり
								if (m_bUse[m_CreateNumber][m_WightNumber - 1][(m_HeightNumber) % SET_BLOCK_HEIGHT] == false)
								{//左なし
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\147.png");
								}
								else
								{//左あり
									m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\5.png");
								}
							}
						}
					}
				}
			}
		}
	}
}