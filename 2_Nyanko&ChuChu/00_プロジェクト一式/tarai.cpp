//===========================================
//
// たらいメイン処理[tarai.cpp]
// Author 坂本翔唯
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "tarai.h"
#include "useful.h"
#include "texture.h"

#include "object3D.h"
#include "Himo.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define GEAR_CYCLE_SPEED		(0.1f)		// 回る速度

//==============================
// コンストラクタ
//==============================
CTarai::CTarai() : CModel(CObject::TYPE_NONE, CObject::PRIORITY_BLOCK)
{
	m_pHimo = nullptr;			// 紐のポインタ(生成はしない)
	m_move = NONE_D3DXVECTOR3;
	m_nIndex = -1;
	m_pShadow = NULL;
}

//==============================
// デストラクタ
//==============================
CTarai::~CTarai()
{

}

//==============================
// 破片の初期化処理
//==============================
HRESULT CTarai::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // 初期化処理に失敗した場合

	  // 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	m_pHimo = nullptr;			// 紐のポインタ(生成はしない)

	// 値を返す
	return S_OK;
}

//========================================
// 破片の終了処理
//========================================
void CTarai::Uninit(void)
{
	if (m_pHimo != nullptr)
	{ // 紐のポインタが NULL じゃない場合

		// 紐を NULL にする
		m_pHimo = nullptr;
	}

	// 終了処理
	CModel::Uninit();

	if (m_pShadow != NULL)
	{
		// 描画処理
		m_pShadow->Uninit();
		m_pShadow = NULL;
	}
}

//=====================================
// 破片の更新処理
//=====================================
void CTarai::Update(void)
{
	// 位置を取得する
	D3DXVECTOR3 pos = GetPos();

	// 位置を加算する
	m_move.y -= 0.8f;

	if (pos.y < 0.0f)
	{
		m_pHimo->NULLTarai(m_nIndex);
		Uninit();
		return;
	}

	// 位置更新
	pos.y += m_move.y;

	// 位置を設定する
	SetPos(pos);

	if (m_pShadow != NULL)
	{
		// 更新処理
		m_pShadow->Update();
	}
}

//=====================================
// 破片の描画処理
//=====================================
void CTarai::Draw(void)
{
	// 描画処理
	CModel::Draw();

	if (m_pShadow != NULL)
	{
		// デバイスの取得
		LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

		//αブレンディングを加算処理に設定
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		// 描画処理
		m_pShadow->Draw();

		//αブレンディングを元に戻す
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CTarai::SetData(const D3DXVECTOR3& pos, CHimo* pHimo)
{
	// 情報の設定処理
	SetPos(pos);								// 位置
	SetPosOld(pos);								// 前回の位置
	SetRot(NONE_D3DXVECTOR3);					// 向き
	SetScale(NONE_SCALE);						// 拡大率
	SetFileData(CXFile::TYPE_TARAI);			// モデル情報

	if (m_pShadow == NULL)
	{
		m_pShadow = CObject3D::Create(CObject::TYPE_NONE, PRIORITY_BG);
		m_pShadow->SetPos(D3DXVECTOR3(pos.x, 0.0f, pos.z));			// 位置
		m_pShadow->SetPosOld(D3DXVECTOR3(pos.x, 0.0f, pos.z));		// 前回の位置
		m_pShadow->SetRot(D3DXVECTOR3(D3DX_PI * 0.0f, 0.0f, 0.0f));	// 向き
		m_pShadow->SetSize(D3DXVECTOR3(150.0f, 0.0f, 150.0f));		// サイズ
		m_pShadow->SetVtxColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));	// 色
		m_pShadow->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\shadow.jpg"));		// テクスチャの割り当て処理

		// 頂点座標の設定処理
		m_pShadow->SetVertex();
	}

	if (m_pHimo == nullptr)
	{ // 紐が NULL の場合

		// 紐のポインタを入れる
		m_pHimo = pHimo;
	}
}

//=======================================
// 生成処理
//=======================================
CTarai* CTarai::Create(const D3DXVECTOR3& pos, CHimo* pHimo)
{
	// ローカルオブジェクトを生成
	CTarai* pTarai = nullptr;	// インスタンスを生成

	if (pTarai == nullptr)
	{ // オブジェクトが NULL の場合

	  // インスタンスを生成
		pTarai = new CTarai;
	}
	else
	{ // オブジェクトが NULL じゃない場合

	  // 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pTarai != nullptr)
	{ // オブジェクトが NULL じゃない場合

	  // 初期化処理
		if (FAILED(pTarai->Init()))
		{ // 初期化に失敗した場合

		  // 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pTarai->SetData(pos, pHimo);
	}
	else
	{ // オブジェクトが NULL の場合

	  // 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// たらいのギアのポインタを返す
	return pTarai;
}