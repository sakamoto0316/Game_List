//============================================
//
//	ゲージビルボード [GaugeBillboard.cpp]
//	Author:sakamoto kai
//
//============================================
#include "GaugeBillboard.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "number.h"

//====================================================================
//コンストラクタ
//====================================================================
CGaugeBillboard::CGaugeBillboard(int nPriority) :CObject(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_Tilt = 0.0f;
	m_Height = 0.0f;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_pNumberMax = NULL;
	m_pNumber = NULL;
}

//====================================================================
//デストラクタ
//====================================================================
CGaugeBillboard::~CGaugeBillboard()
{

}

//====================================================================
//生成処理
//====================================================================
CGaugeBillboard *CGaugeBillboard::Create(void)
{
	CGaugeBillboard *pObject2D = NULL;

	if (pObject2D == NULL)
	{
		//オブジェクト2Dの生成
		pObject2D = new CGaugeBillboard();
	}

	//オブジェクトの初期化処理
	if (FAILED(pObject2D->Init()))
	{//初期化処理が失敗した場合
		return NULL;
	}

	return pObject2D;
}

//====================================================================
//初期化処理
//====================================================================
HRESULT CGaugeBillboard::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\Test.jpg");

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL)))
	{
		return E_FAIL;
	}

	//ゲージの割合を出す
	float fRatio = 0.0f;

	if (m_Gauge != 0)
	{
		fRatio = ((float)m_Gauge / (float)m_GaugeMax);
	}

	VERTEX_3D*pVtx;	//頂点ポインタを所得

					//頂点バッファをロックし、両店情報へのポインタを所得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定 
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_Wight * fRatio), m_pos.y, m_pos.z);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + m_Tilt, m_pos.y + m_Height, m_pos.z);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_Tilt + (m_Wight * fRatio), m_pos.y + m_Height, m_pos.z);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CGaugeBillboard::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	Release();
}

//====================================================================
//更新処理
//====================================================================
void CGaugeBillboard::Update(void)
{
	SetVerTex();
}

//====================================================================
//描画処理
//====================================================================
void CGaugeBillboard::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	D3DXMATRIX mtxTrans;	//計算用マトリックス
	D3DXMATRIX mtxView;	//ビューマトリックス所得用

	//Zテストを無効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//アルファテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//ライティングをオフにする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//ビューマトリックスを所得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//ポリゴンをカメラに対して正面を向ける
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);	//逆行列を求める
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	assert(GetIdx() != -1);		//テクスチャの番号を入れ忘れた場合エラーを吐く

	//テクスチャの設定
	pDevice->SetTexture(0, pTexture->GetAddress(GetIdx()));

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
		0,										//プリミティブ(ポリゴン)数
		2);

	//ライティングをオンにする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//アルファテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//Zテストを有効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//====================================================================
//テクスチャの割り当て
//====================================================================
void CGaugeBillboard::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//====================================================================
//頂点座標の設定
//====================================================================
void CGaugeBillboard::SetVerTex(void)
{
	//ゲージの割合を出す
	float fRatio = 0.0f;

	if (m_Gauge != 0)
	{
		fRatio = ((float)m_Gauge / (float)m_GaugeMax);
	}

	VERTEX_3D*pVtx;	//頂点ポインタを所得

	//頂点バッファをロックし、両店情報へのポインタを所得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定 
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f + (m_Wight * fRatio), 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Tilt, -m_Height, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Tilt + (m_Wight * fRatio),-m_Height, 0.0f);

	////頂点座標の設定 
	//pVtx[0].pos = D3DXVECTOR3(-m_Wight * 0.5f, +m_Height * 0.5f, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(+m_Wight * 0.5f, +m_Height * 0.5f, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(-m_Wight * 0.5f, -m_Height * 0.5f, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(+m_Wight * 0.5f, -m_Height * 0.5f, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//====================================================================
//テクスチャ座標の設定
//====================================================================
void CGaugeBillboard::SetAnim(D3DXVECTOR2 Tex)
{
	VERTEX_3D*pVtx;	//頂点ポインタを所得

	//頂点バッファをロックし、両店情報へのポインタを所得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(Tex.x, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, Tex.y);
	pVtx[3].tex = D3DXVECTOR2(Tex.x, Tex.y);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//====================================================================
//頂点カラーの設定
//====================================================================
void CGaugeBillboard::SetColor(D3DXCOLOR col)
{
	VERTEX_3D*pVtx;	//頂点ポインタを所得

					//頂点バッファをロックし、両店情報へのポインタを所得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの設定
	pVtx[0].col =
		pVtx[1].col =
		pVtx[2].col =
		pVtx[3].col = col;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}