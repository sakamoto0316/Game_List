//=======================================
//
// 扇風機の風処理[fan_wind.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "fan_wind.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

//=========================
// コンストラクタ
//=========================
CFanWind::CFanWind() : CObject3D(CObject::TYPE_NONE, CObject::PRIORITY_BLOCK)
{

}

//=========================
// デストラクタ
//=========================
CFanWind::~CFanWind()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CFanWind::Init(void)
{
	if (FAILED(CObject3D::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//=========================
// 終了処理
//=========================
void CFanWind::Uninit(void)
{
	// 終了
	CObject3D::Uninit();
}

//=========================
// 更新処理
//=========================
void CFanWind::Update(void)
{

}

//=========================
// 描画処理
//=========================
void CFanWind::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	// カリングの設定をOFFにする
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// 描画処理
	CObject3D::DrawLightOff();

	// カリングの設定をONにする
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//=========================
// 情報の設定処理
//=========================
void CFanWind::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
	// スクロールの設定処理
	SetPos(pos);					// 位置設定
	SetPosOld(pos);					// 前回の位置設定
	SetRot(NONE_D3DXVECTOR3);		// 向き設定
	SetSize(size);					// サイズ設定

	// 頂点座標の設定処理
	SetVertex();
}

//=========================
// 生成処理
//=========================
CFanWind* CFanWind::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
	// ローカルオブジェクトを生成
	CFanWind* pWind = nullptr;		// 風のインスタンスを生成

	if (pWind == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pWind = new CFanWind;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pWind != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pWind->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pWind->SetData(pos, size);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 扇風機の風のポインタを返す
	return pWind;
}