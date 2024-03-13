//============================================
//
// オブジェクト3Dファンのメイン処理[object3Dfan.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "object3Dfan.h"
#include "renderer.h"
#include "manager.h"
#include "useful.h"

//=========================================
// コンストラクタ
//=========================================
CObject3DFan::CObject3DFan() : CObject(CObject::TYPE_3DPOLYGON, CObject::PRIORITY_BG)
{
	// コンストラクタの箱
	Box();
}

//=========================================
// オーバーロードコンストラクタ
//=========================================
CObject3DFan::CObject3DFan(CObject::TYPE type, PRIORITY priority) : CObject(type, priority)
{
	// コンストラクタの箱
	Box();
}

//=========================================
// デストラクタ
//=========================================
CObject3DFan::~CObject3DFan()
{

}

//==============================
// コンストラクタの箱
//==============================
void CObject3DFan::Box(void)
{
	// 全ての値をクリアする
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 位置
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 前回の位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 向き
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// サイズ
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// 色
	m_pVtxBuff = nullptr;							// 頂点バッファのポインタ
	ZeroMemory(&m_mtxWorld, sizeof(m_mtxWorld));	// ワールドマトリックス
	m_nNumAngle = 0;								// 角度の数
	m_fRadius = 0.0f;								// 半径
	m_nTexIdx = NONE_TEXIDX;						// テクスチャのインデックス
}

//===========================================
// オブジェクト3Dの初期化処理
//===========================================
HRESULT CObject3DFan::Init(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumAngle * 3,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL)))
	{ // バッファの生成に失敗した場合

		// 停止
		assert(false);

		// 失敗を返す
		return E_FAIL;
	}

	// ローカル変数宣言
	float fAngle = D3DX_PI / m_nNumAngle;	// 角度
	VERTEX_3D * pVtx;						//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < m_nNumAngle; nCnt++)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 角度を算出する
		fAngle = ((float)((D3DX_PI * 2) / m_nNumAngle) * nCnt) - (D3DX_PI * 2);

		// 向きの正規化
		useful::RotNormalize(&fAngle);

		pVtx[1].pos = D3DXVECTOR3(sinf(fAngle) * m_fRadius, 0.0f, cosf(fAngle) * m_fRadius);

		// 角度を算出する
		fAngle = ((float)((D3DX_PI * 2) / m_nNumAngle) * (nCnt + 1)) - (D3DX_PI * 2);

		// 向きの正規化
		useful::RotNormalize(&fAngle);

		pVtx[2].pos = D3DXVECTOR3(sinf(fAngle) * m_fRadius, 0.0f, cosf(fAngle) * m_fRadius);

		// 法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// 頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);
		pVtx[1].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);
		pVtx[2].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);

		// 頂点データを3つ分進める
		pVtx += 3;
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	if (m_pVtxBuff == nullptr)
	{ // 頂点バッファのポインタがNULLの場合

		// 停止
		assert(false);

		// 失敗を返す
		return E_FAIL;
	}

	// 値を返す
	return S_OK;
}

//===========================================
// オブジェクト3Dの終了処理
//===========================================
void CObject3DFan::Uninit(void)
{
	if (m_pVtxBuff != nullptr)
	{ // 頂点バッファの破棄

		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	// 破棄処理
	Release();
}

//===========================================
// オブジェクト3Dの更新処理
//===========================================
void CObject3DFan::Update(void)
{
	// 頂点の設定処理
	SetVertex();
}

//===========================================
// オブジェクト3Dの描画処理
//===========================================
void CObject3DFan::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;			// 計算用マトリックス
	D3DXMATRIX mtxView;						// ビューマトリックス取得用

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ライティングをOFFにする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0,
		m_pVtxBuff,									// 頂点バッファへのポインタ
		0,
		sizeof(VERTEX_3D));							// 頂点情報構造体のサイズ

	// テクスチャの設定
	pDevice->SetTexture(0, NULL);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLELIST,		// プリミティブの種類
		0,											// 描画する最初の頂点インデックス
		m_nNumAngle);								// 描画するプリミティブ数

	// ライティングをONにする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//===========================================
// 頂点情報の設定
//===========================================
void CObject3DFan::SetVertex(void)
{
	float fAngle;									// 角度

	VERTEX_3D * pVtx;											//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < m_nNumAngle; nCnt++)
	{
		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 角度を算出する
		fAngle = ((float)((D3DX_PI * 2) / m_nNumAngle) * nCnt) - (D3DX_PI * 2);

		// 向きの正規化
		useful::RotNormalize(&fAngle);

		pVtx[1].pos = D3DXVECTOR3(sinf(fAngle) * m_fRadius, 0.0f, cosf(fAngle) * m_fRadius);

		// 角度を算出する
		fAngle = ((float)((D3DX_PI * 2) / m_nNumAngle) * (nCnt + 1)) - (D3DX_PI * 2);

		// 向きの正規化
		useful::RotNormalize(&fAngle);

		pVtx[2].pos = D3DXVECTOR3(sinf(fAngle) * m_fRadius, 0.0f, cosf(fAngle) * m_fRadius);

		// 頂点データを3つ分進める
		pVtx += 3;
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//===========================================
// 頂点カラーの設定処理
//===========================================
void CObject3DFan::SetVtxColor(const D3DXCOLOR& col)
{
	VERTEX_3D * pVtx;											//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < m_nNumAngle; nCnt++)
	{
		// 頂点座標の設定
		pVtx[0].col = col;
		pVtx[1].col = col;
		pVtx[2].col = col;

		// 頂点データを3つ分進める
		pVtx += 3;
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//===========================================
// 頂点カラーの細かい設定処理
//===========================================
void CObject3DFan::SetVtxColor(const D3DXCOLOR& normalCol, const D3DXCOLOR& rezCol, int nEndResVtx)
{
	VERTEX_3D * pVtx;											//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < m_nNumAngle; nCnt++)
	{
		if (nCnt < nEndResVtx)
		{ // 回復してる範囲の頂点のとき

			// 頂点座標の設定
			pVtx[0].col = rezCol;
			pVtx[1].col = rezCol;
			pVtx[2].col = rezCol;
		}
		else
		{ // 回復してる範囲外

			// 頂点座標の設定
			pVtx[0].col = normalCol;
			pVtx[1].col = normalCol;
			pVtx[2].col = normalCol;
		}

		// 頂点データを3つ分進める
		pVtx += 3;
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//===========================================
// テクスチャの割り当て処理
//===========================================
void CObject3DFan::BindTexture(const int nIdx)
{
	// テクスチャを割り当てる
	m_nTexIdx = nIdx;
}

//===========================================
// 位置設定処理
//===========================================
void CObject3DFan::SetPos(const D3DXVECTOR3& pos)
{
	// 位置を設定する
	m_pos = pos;
}

//===========================================
// 位置取得処理
//===========================================
D3DXVECTOR3 CObject3DFan::GetPos(void) const
{
	// 位置を返す
	return m_pos;
}

//===========================================
// 前回の位置設定処理
//===========================================
void CObject3DFan::SetPosOld(const D3DXVECTOR3& posOld)
{
	// 前回の位置を設定する
	m_posOld = posOld;
}

//===========================================
// 前回の位置取得処理
//===========================================
D3DXVECTOR3 CObject3DFan::GetPosOld(void) const
{
	// 前回の位置を返す
	return m_posOld;
}

//===========================================
// 向き設定処理
//===========================================
void CObject3DFan::SetRot(const D3DXVECTOR3& rot)
{
	// 向きを設定する
	m_rot = rot;
}

//===========================================
// 向き取得処理
//===========================================
D3DXVECTOR3 CObject3DFan::GetRot(void) const
{
	// 向きを返す
	return m_rot;
}

//===========================================
// サイズ設定処理
//===========================================
void CObject3DFan::SetSize(const D3DXVECTOR3& size)
{
	// サイズを設定する
	m_size = size;
}

//===========================================
// サイズ取得処理
//===========================================
D3DXVECTOR3 CObject3DFan::GetSize(void) const
{
	// サイズを返す
	return m_size;
}

//===========================================
// 角度の総数の設定処理
//===========================================
void CObject3DFan::SetNumAngle(const int nNum)
{
	// 角度の総数の設定する
	m_nNumAngle = nNum;
}

//===========================================
// 角度の総数の取得処理
//===========================================
int CObject3DFan::GetNumAngle(void) const
{
	// 角度の総数を返す
	return m_nNumAngle;
}

//===========================================
// 半径の設定処理
//===========================================
void CObject3DFan::SetRadius(const float fRadius)
{
	// 半径を設定する
	m_fRadius = fRadius;
}

//===========================================
// 半径の取得処理
//===========================================
float CObject3DFan::GetRadius(void) const
{
	// 半径を返す
	return m_fRadius;
}
//===========================================
// 色の設定処理
//===========================================
void CObject3DFan::SetColor(const D3DXCOLOR col)
{
	// 色を設定する
	m_col = col;
}

//===========================================
// 色の取得処理
//===========================================
D3DXCOLOR CObject3DFan::GetColor(void) const
{
	// 色を返す
	return m_col;
}

//===========================================
// 生成処理
//===========================================
CObject3DFan* CObject3DFan::Create(void)
{
	// ローカルオブジェクトを生成
	CObject3DFan* pObject3DFan = nullptr;	// オブジェクト3Dのインスタンスを生成

	if (pObject3DFan == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pObject3DFan = new CObject3DFan;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pObject3DFan != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		pObject3DFan->Init();
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// オブジェクト3Dのポインタを返す
	return pObject3DFan;
}