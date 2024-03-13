//===========================================
//
// コンセントのメイン処理[consent.cpp]
// Author 坂本翔唯
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "consent.h"
#include "useful.h"
#include "cup.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define NOTE_CYCLE_SPEED		(0.05f)		// 回る速度
#define NOTE_UD_HEIGHT		(100.0f)		// 上下移動の幅

//==============================
// コンストラクタ
//==============================
CConsent::CConsent() : CModel(CObject::TYPE_NONE, CObject::PRIORITY_BLOCK)
{
	m_pMain = NULL;
	m_move = NONE_D3DXVECTOR3;
	m_nLife = 10;
}

//==============================
// デストラクタ
//==============================
CConsent::~CConsent()
{

}

//==============================
// コンセントの初期化処理
//==============================
HRESULT CConsent::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // 初期化処理に失敗した場合

	  // 失敗を返す
		return E_FAIL;
	}

	// 値を返す
	return S_OK;
}

//========================================
// コンセントの終了処理
//========================================
void CConsent::Uninit(void)
{
	//本体にある自身のポインタ削除処理
	m_pMain->NULLConsent();

	// 終了処理
	CModel::Uninit();
}

//=====================================
// コンセントの更新処理
//=====================================
void CConsent::Update(void)
{
	// 位置と向きをを取得する
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	// 位置更新
	pos += m_move;

	// 位置と向きを設定する
	SetPos(pos);
	SetRot(rot);
}

//=====================================
// コンセントの描画処理
//=====================================
void CConsent::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=====================================
// コンセントの描画処理
//=====================================
void CConsent::Draw(const float fAlpha)
{
	// 描画処理
	CModel::Draw(fAlpha);
}

//=====================================
// 情報の設定処理
//=====================================
void CConsent::SetData(const D3DXVECTOR3& pos)
{
	// 情報の設定処理
	SetPos(pos);								// 位置
	SetPosOld(pos);								// 前回の位置
	SetRot(NONE_D3DXVECTOR3);					// 向き
	SetScale(NONE_SCALE);						// 拡大率
	SetFileData(CXFile::TYPE_CONSENT);			// モデル情報
}

//=======================================
// 生成処理
//=======================================
CConsent* CConsent::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CConsent* pTarai = nullptr;	// インスタンスを生成

	if (pTarai == nullptr)
	{ // オブジェクトが NULL の場合

	  // インスタンスを生成
		pTarai = new CConsent;
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
		pTarai->SetData(pos);
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