//============================================
//
// キャラクターの情報UI処理[chara_infoUI.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "chara_infoUI.h"
#include "texture.h"
#include "useful.h"

#include "chara_icon.h"
#include "chara_ID.h"
#include "chara_state.h"

//========================
// コンストラクタ
//========================
CCharaInfoUI::CCharaInfoUI() : CObject(TYPE_CHARAINFO, PRIORITY_UI)
{
	// 全ての値をクリアする
	m_pIcon = nullptr;		// アイコンの情報
	m_pID = nullptr;		// IDの情報
	m_pState = nullptr;		// 状態の情報
}

//========================
// デストラクタ
//========================
CCharaInfoUI::~CCharaInfoUI()
{

}

//========================
// 初期化処理
//========================
HRESULT CCharaInfoUI::Init(void)
{
	// 全ての値を初期化する
	m_pIcon = nullptr;		// アイコンの情報
	m_pID = nullptr;		// IDの情報
	m_pState = nullptr;		// 状態の情報

	// 成功を返す
	return S_OK;
}

//========================
// 終了処理
//========================
void CCharaInfoUI::Uninit(void)
{
	if (m_pIcon != nullptr)
	{ // アイコンが NULL じゃない場合

		// アイコンの終了処理
		m_pIcon->Uninit();
		m_pIcon = nullptr;
	}

	if (m_pID != nullptr)
	{ // IDが NULL じゃない場合

		// IDの終了処理
		m_pID->Uninit();
		m_pID = nullptr;
	}

	if (m_pState != nullptr)
	{ // 状態が NULL じゃない場合

		// 状態の終了処理
		m_pState->Uninit();
		m_pState = nullptr;
	}

	// 本体の終了処理
	Release();
}

//========================
// 更新処理
//========================
void CCharaInfoUI::Update(void)
{
	if (m_pIcon != nullptr)
	{ // アイコンが NULL じゃない場合

		// アイコンの更新処理
		m_pIcon->Update();
	}

	if (m_pID != nullptr)
	{ // IDが NULL じゃない場合

		// IDの更新処理
		m_pID->Update();
	}

	if (m_pState != nullptr)
	{ // 状態が NULL じゃない場合

		// 状態の更新処理
		m_pState->Update();
	}
}

//========================
// 描画処理
//========================
void CCharaInfoUI::Draw(void)
{
	if (m_pIcon != nullptr)
	{ // アイコンが NULL じゃない場合

		// アイコンの描画処理
		m_pIcon->Draw();
	}

	if (m_pID != nullptr)
	{ // IDが NULL じゃない場合

		// IDの描画処理
		m_pID->Draw();
	}

	if (m_pState != nullptr)
	{ // 状態が NULL じゃない場合

		// 状態の描画処理
		m_pState->Draw();
	}
}

//========================
// 情報の設定処理
//========================
void CCharaInfoUI::SetData(const D3DXVECTOR3& pos, const int nPlayerID, const CPlayer::TYPE type)
{
	if (m_pIcon == nullptr)
	{ // アイコンが NULL の場合

		// アイコンを生成する
		m_pIcon = CCharaIcon::Create(pos, type);
	}

	if (m_pID == nullptr)
	{ // IDが NULL の場合

		// IDの位置を設定
		D3DXVECTOR3 posID = D3DXVECTOR3(pos.x + 40.0f, pos.y + 50.0f, pos.z);

		// IDを生成する
		m_pID = CCharaID::Create(posID, nPlayerID);
	}

	if (m_pState == nullptr)
	{ // IDが NULL の場合

		// IDの位置を設定
		D3DXVECTOR3 posState = D3DXVECTOR3(pos.x, pos.y - 40.0f, pos.z);

		// IDを生成する
		m_pState = CCharaState::Create(posState, nPlayerID);
	}
}

//========================
// 生成処理
//========================
CCharaInfoUI* CCharaInfoUI::Create(const D3DXVECTOR3& pos, const int nPlayerID, const CPlayer::TYPE type)
{
	// ローカルオブジェクトを生成
	CCharaInfoUI* pInfoUI = nullptr;		// キャラクター情報UIのインスタンスを生成

	if (pInfoUI == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pInfoUI = new CCharaInfoUI;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pInfoUI != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pInfoUI->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pInfoUI->SetData(pos, nPlayerID, type);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// キャラクターの情報UIのポインタを返す
	return pInfoUI;
}