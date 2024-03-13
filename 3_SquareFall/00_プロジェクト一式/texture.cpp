//============================================
//
//	テクスチャの管理 [texture.cpp]
//	Author:sakamoto kai
//
//============================================
#include "texture.h"
#include "renderer.h"
#include "manager.h"
#include "Xmodel.h"

//静的メンバ変数宣言
int CTexture::m_NumAll = 0;
const char *CTexture::c_apTexturename[] = {};

//====================================================================
//コンストラクタ
//====================================================================
CTexture::CTexture()
{
	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		m_apTexture[nCntTex] = NULL;
	}
}

//====================================================================
//デストラクタ
//====================================================================
CTexture::~CTexture()
{

}

//====================================================================
//読み込み
//====================================================================
HRESULT CTexture::Load(void)
{
	////デバイスの取得
	//LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	//{
	//	//テクスチャの読み込み
	//	if (FAILED(D3DXCreateTextureFromFile(pDevice,
	//		c_apTexturename[nCntTex],
	//		&m_apTexture[nCntTex])))
	//	{
	//		if (c_apTexturename[nCntTex] == NULL)
	//		{
	//			m_NumAll = nCntTex;
	//			return S_OK;
	//		}
	//		else
	//		{
	//			return E_FAIL;
	//		}
	//	}
	//	else
	//	{
	//		int a = 0;
	//	}
	//}

	return S_OK;
}

//====================================================================
//破棄
//====================================================================
void CTexture::Unload(void)
{
	for (int nCntTex = 0; nCntTex < m_NumAll; nCntTex++)
	{
		//テクスチャの破棄
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}

//====================================================================
//テクスチャの番号指定
//====================================================================
int CTexture::Regist(const char *pFilename)
{
	for (int nCntTex = 0; nCntTex < m_NumAll; nCntTex++)
	{
		if (strcmp(c_apTexturename[nCntTex], pFilename) == 0)
		{
			return nCntTex;
		}
	}

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

		//テクスチャの読み込み
	if (SUCCEEDED(D3DXCreateTextureFromFile(pDevice,
		pFilename,
		&m_apTexture[m_NumAll])))
	{
		if (c_apTexturename[m_NumAll] == NULL)
		{
			c_apTexturename[m_NumAll] = pFilename;
			m_NumAll++;
			return m_NumAll - 1;
		}
		else
		{
			return -1;
		}
	}

	return -1;
}

//====================================================================
//テクスチャの番号指定
//====================================================================
void CTexture::XModelRegist(int *nTexIdx, int nXModelIdx)
{
	int nCheck = -1;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	D3DXMATERIAL *pMat;	//マテリアルへのポインタ

	//Xモデルの取得
	CXModel::XModel *pXmodel = CManager::GetInstance()->GetXModel()->GetXModel(nXModelIdx);

	//マテリアル情報に対するポインタを所得
	pMat = (D3DXMATERIAL*)pXmodel->m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)pXmodel->m_dwNumMat; nCntMat++)
	{
		nCheck = -1;
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			for (int nCntTex = 0; nCntTex < m_NumAll; nCntTex++)
			{
				if (strcmp(c_apTexturename[nCntTex], pMat[nCntMat].pTextureFilename) == 0)
				{
					nTexIdx[nCntMat] = nCntTex;
					nCheck = nCntTex;
				}
			}

			if (nTexIdx[nCntMat] != nCheck)
			{
				//テクスチャの読み込み
				if (SUCCEEDED(D3DXCreateTextureFromFile(pDevice,
					pMat[nCntMat].pTextureFilename,
					&m_apTexture[m_NumAll])))
				{
					c_apTexturename[m_NumAll] = pMat[nCntMat].pTextureFilename;
					m_NumAll++;
					nTexIdx[nCntMat] = m_NumAll - 1;
				}
			}
		}
		else
		{
			m_apTexture[m_NumAll] = NULL;
			nTexIdx[nCntMat] = -1;
		}
	}
}

//====================================================================
//指定のテクスチャを返す
//====================================================================
LPDIRECT3DTEXTURE9 CTexture::GetAddress(int nIdx)
{
	return m_apTexture[nIdx];
}