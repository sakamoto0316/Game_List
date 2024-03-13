//===========================================
//
// エントリー画面のランダム指示処理[entry_rand.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "entry_rand.h"
#include "manager.h"
#include "texture.h"

//-------------------------------------------
// 無名名前空間
//-------------------------------------------
namespace
{
	const D3DXVECTOR3 RAND_POS = D3DXVECTOR3(1150.0f, 680.0f, 0.0f);	// 位置
	const D3DXVECTOR3 RAND_SIZE = D3DXVECTOR3(120.0f, 30.0f, 0.0f);		// サイズ
	const char* RAND_TEXTURE = "data\\TEXTURE\\entry_random.png";		// テクスチャの名前
}

//==============================
// コンストラクタ
//==============================
CEntryRandom::CEntryRandom() : CObject2D(CObject::TYPE_ENTRYRANDOM, CObject::PRIORITY_UI)
{

}

//==============================
// デストラクタ
//==============================
CEntryRandom::~CEntryRandom()
{

}

//==============================
// エントリー画面の操作説明の初期化処理
//==============================
HRESULT CEntryRandom::Init(void)
{
	if (FAILED(CObject2D::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 値を返す
	return S_OK;
}

//========================================
// エントリー画面の操作説明の終了処理
//========================================
void CEntryRandom::Uninit(void)
{
	// 終了処理
	CObject2D::Uninit();
}

//=====================================
// エントリー画面の操作説明の更新処理
//=====================================
void CEntryRandom::Update(void)
{

}

//=====================================
// エントリー画面の操作説明の描画処理
//=====================================
void CEntryRandom::Draw(void)
{
	// 描画処理
	CObject2D::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CEntryRandom::SetData(void)
{
	// 情報の設定処理
	SetPos(RAND_POS);			// 位置
	SetPosOld(RAND_POS);		// 前回の位置
	SetRot(NONE_D3DXVECTOR3);	// 向き
	SetSize(RAND_SIZE);			// サイズ
	SetLength();				// 長さ
	SetAngle();					// 方向
	BindTexture(CManager::Get()->GetTexture()->Regist(RAND_TEXTURE));		// テクスチャの割り当て処理

	// 頂点座標の設定処理
	SetVertex();
}

//=======================================
// 生成処理
//=======================================
CEntryRandom* CEntryRandom::Create(void)
{
	// ローカルオブジェクトを生成
	CEntryRandom* pEntryRandom = nullptr;		// UIのインスタンスを生成

	if (pEntryRandom == nullptr)
	{ // オブジェクトが NULL の場合

		// インスタンスを生成
		pEntryRandom = new CEntryRandom;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pEntryRandom != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pEntryRandom->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pEntryRandom->SetData();
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// UIのポインタを返す
	return pEntryRandom;
}