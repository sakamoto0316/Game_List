//===========================================
//
// 回復中UIメイン処理[recoveringUI.cpp]
// Author 佐藤根詩音
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "recoveringUI.h"
#include "model.h"
#include "texture.h"
#include "player.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define SIZE_UI		(D3DXVECTOR3(50.0f, 50.0f, 0.0f))		// UIの大きさ
#define SUB_ALPHA	(0.025f)			// 透明度減算する数

//-------------------------------------------
// 静的メンバ変数宣言
//-------------------------------------------

//==============================
// コンストラクタ
//==============================
CRecoveringUI::CRecoveringUI() : CBillboard(CObject::TYPE_RECOVERINGUI, CObject::PRIORITY_PLAYER)
{
	// 全ての値をクリアする
	m_bDisp = false;			// UIを表示するか
	m_fAlpha = 1.0f;			// 透明度
	m_alpha = ALPHA_OPACITY;	// 透明度の状態
}

//==============================
// デストラクタ
//==============================
CRecoveringUI::~CRecoveringUI()
{

}

//==============================
// 回復中UIの初期化処理
//==============================
HRESULT CRecoveringUI::Init(void)
{
	if (FAILED(CBillboard::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	m_bDisp = false;			// UIを表示するか
	m_fAlpha = 1.0f;			// 透明度
	m_alpha = ALPHA_OPACITY;	// 透明度の状態

	// 値を返す
	return S_OK;
}

//========================================
// 回復中UIの終了処理
//========================================
void CRecoveringUI::Uninit(void)
{
	// 終了処理
	CBillboard::Uninit();
}

//=====================================
// 回復中UIの更新処理
//=====================================
void CRecoveringUI::Update(void)
{
	if (m_bDisp == true)
	{ // UIを表示する状態の時

		// 透明度変更
		switch (m_alpha)
		{
		case CRecoveringUI::ALPHA_OPACITY:		// 不透明

				// 透明にしていく
				m_fAlpha -= SUB_ALPHA;

				if (m_fAlpha <= 0.0f)
				{ // 透明になったら

					// 透明状態にする
					m_alpha = ALPHA_TRANSPARENT;
				}

			break;

		case CRecoveringUI::ALPHA_TRANSPARENT:	// 透明

			// 不透明にしていく
			m_fAlpha += SUB_ALPHA;

			if (m_fAlpha >= 1.0f)
			{ // 不透明になったら

				// 不透明状態にする
				m_alpha = ALPHA_OPACITY;
			}

			break;

		default:

			// 停止する
			assert(false);

			break;
		}
	}
	else if (m_bDisp == false && m_alpha != ALPHA_OPACITY)
	{ // 表示する状態じゃないとき

		m_fAlpha = 1.0f;
		m_alpha = ALPHA_OPACITY;

	}

	// 色設定
	SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha));
}

//=====================================
// 回復中UIの描画処理
//=====================================
void CRecoveringUI::Draw(void)
{
	if (m_bDisp == true)
	{ // UIを表示する状態のとき

		// 描画処理
		CBillboard::DrawLightOff();
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CRecoveringUI::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld)
{
	// 設定処理に便利なマクロ定義
	//NONE_D3DXVECTOR3					// 向きを傾けない時とかに使用する
	// 情報の設定処理

	//==========================================================================
	// ビルボード
	//==========================================================================
	SetPos(pos);			// 位置
	SetPosOld(posOld);		// 前回の位置
	SetSize(SIZE_UI);	// サイズ
	BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\rez_keep.png"));		// テクスチャの割り当て処理

	// 頂点座標の設定処理
	SetVertex();
}

//=======================================
// 生成処理
//=======================================
CRecoveringUI* CRecoveringUI::Create(const D3DXVECTOR3& pos, const  D3DXVECTOR3& posOld)
{
	// ローカルオブジェクトを生成
	CRecoveringUI* pRecoveringUI = nullptr;	// サンプルのインスタンスを生成

	if (pRecoveringUI == nullptr)
	{ // オブジェクトが NULL の場合

		// インスタンスを生成
		pRecoveringUI = new CRecoveringUI;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pRecoveringUI != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pRecoveringUI->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pRecoveringUI->SetData(pos, posOld);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// サンプルのポインタを返す
	return pRecoveringUI;
}

//=======================================
// UIの表示状態の設定
//=======================================
void CRecoveringUI::SetDisplayUI(bool bRez)
{
	// UIの表示状態を設定
	m_bDisp = bRez;
}

//=======================================
// UIの表示状態の取得
//=======================================
bool CRecoveringUI::GetDisplayUI(void)
{
	// UIの表示状態を返す
	return m_bDisp;
}