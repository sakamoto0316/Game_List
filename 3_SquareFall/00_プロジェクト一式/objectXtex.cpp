//============================================
//
//	オブジェクトXファイル [objectXtex.cpp]
//	Author:sakamoto kai
//
//============================================
#include "objectXtex.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "texture.h"
#include "player3D.h"

#define POLYDON_SIZE (10.0f)

//====================================================================
//コンストラクタ
//====================================================================
CObjectXtex::CObjectXtex(int nPriority) :CObject(nPriority)
{
	m_pBuffMat = NULL;
	m_pMesh = NULL;
	m_Wight = POLYDON_SIZE;
	m_Height = POLYDON_SIZE;
	m_dwNumMat = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_MatColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_bTexOne = false;
}

//====================================================================
//デストラクタ
//====================================================================
CObjectXtex::~CObjectXtex()
{

}

//====================================================================
//生成処理
//====================================================================
CObjectXtex *CObjectXtex::Create(void)
{
	CObjectXtex *pObjectXtex = NULL;

	if (pObjectXtex == NULL)
	{
		//オブジェクト3Dの生成
		pObjectXtex = new CObjectXtex();
	}

	//オブジェクトの初期化処理
	if (FAILED(pObjectXtex->Init()))
	{//初期化処理が失敗した場合
		return NULL;
	}

	return pObjectXtex;
}

//====================================================================
//初期化処理
//====================================================================
HRESULT CObjectXtex::Init(void)
{
	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CObjectXtex::Uninit(void)
{
	SetDeathFlag(true);
}

//====================================================================
//更新処理
//====================================================================
void CObjectXtex::Update(void)
{
	CPlayer3D *pPlayer = CGame::GetPlayer3D();

	if (CScene::GetMode() == CScene::MODE_GAME)
	{
		if (pPlayer->GetPos().y + 400.0f < m_pos.y &&
			CGame::GetTutorial() == false &&
			CGame::GetEventStart() == false)
		{
			Uninit();
			return;
		}
	}
}

//====================================================================
//描画処理
//====================================================================
void CObjectXtex::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ

									//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルを所得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを所得する
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		//マテリアルの設定
		pMat[nCntMat].MatD3D.Diffuse = m_MatColor;
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		CTexture *pTexture = CManager::GetInstance()->GetTexture();

		assert(GetIdx() != -1);		//テクスチャの番号を入れ忘れた場合エラーを吐く

		if (m_bTexOne == false)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, pTexture->GetAddress(GetIdx()));
		}
		else
		{
			if (nCntMat == 0)
			{
				//テクスチャの設定
				pDevice->SetTexture(0, pTexture->GetAddress(GetIdx()));
			}
			else
			{
				//テクスチャの設定
				pDevice->SetTexture(0, NULL);
			}
		}

		//モデル(パーツ)の描画
		m_pMesh->DrawSubset(nCntMat);
	}
	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//====================================================================
//モデル情報の割り当て
//====================================================================
void CObjectXtex::BindFile(LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD pdwNumMat)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//情報の割り当て
	m_pMesh = pMesh;
	m_pBuffMat = pBuffMat;
	m_dwNumMat = pdwNumMat;
}