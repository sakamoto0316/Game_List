//=======================================
//
// エントリーUI処理[entry_UI.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "entry_UI.h"
#include "input.h"
#include "texture.h"

#include "entry_frame.h"
#include "entry_team.h"
#include "entry_ID.h"

//=======================================
// マクロ定義
//=======================================
#define TEAM_SHIFT			(240.0f)		// チームのずらす高さ
#define ID_SHIFT			(230.0f)		// IDのずらす高さ
#define NONE_ID				(-1)			// インデックスの初期数

//=========================
// コンストラクタ
//=========================
CEntryUI::CEntryUI() : CObject(CObject::TYPE_ENTRYUI, CObject::PRIORITY_UI)
{
	// 全ての値をクリアする
	m_pFrame = nullptr;			// 枠の情報
	m_pTeam = nullptr;			// チームの情報
	m_pID = nullptr;			// プレイヤーIDの情報
	m_nID = NONE_ID;			// インデックス
}

//=========================
// デストラクタ
//=========================
CEntryUI::~CEntryUI()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CEntryUI::Init(void)
{
	// 全ての値をクリアする
	m_pFrame = nullptr;			// 枠の情報
	m_pTeam = nullptr;			// チームの情報
	m_pID = nullptr;			// プレイヤーIDの情報
	m_nID = NONE_ID;			// インデックス

	// 成功を返す
	return S_OK;
}

//=========================
// 終了処理
//=========================
void CEntryUI::Uninit(void)
{
	if (m_pFrame != nullptr)
	{ // 枠の情報が NULL じゃない場合

		// 枠の終了処理
		m_pFrame->Uninit();
		m_pFrame = nullptr;
	}

	if (m_pTeam != nullptr)
	{ // チームの情報が NULL じゃない場合

		// チームの終了処理
		m_pTeam->Uninit();
		m_pTeam = nullptr;
	}

	if (m_pID != nullptr)
	{ // IDの情報が NULL じゃない場合

		// IDの終了処理
		m_pID->Uninit();
		m_pID = nullptr;
	}

	// 本体の終了処理
	Release();
}

//=========================
// 更新処理
//=========================
void CEntryUI::Update(void)
{
	if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_LEFT, m_nID) == true)
	{ // Dキーを押した場合

	}

	if (m_pFrame != nullptr)
	{ // 枠の情報が NULL じゃない場合

		// 枠の更新処理
		m_pFrame->Update();
	}

	if (m_pTeam != nullptr)
	{ // チームの情報が NULL じゃない場合

		// チームの更新処理
		m_pTeam->Update();
	}

	if (m_pID != nullptr)
	{ // IDの情報が NULL じゃない場合

		// IDの更新処理
		m_pID->Update();
	}
}

//=========================
// 描画処理
//=========================
void CEntryUI::Draw(void)
{
	if (m_pFrame != nullptr)
	{ // 枠の情報が NULL じゃない場合

		// 枠の描画処理
		m_pFrame->Draw();
	}

	if (m_pTeam != nullptr)
	{ // チームの情報が NULL じゃない場合

		// チームの描画処理
		m_pTeam->Draw();
	}

	if (m_pID != nullptr)
	{ // IDの情報が NULL じゃない場合

		// IDの描画処理
		m_pID->Draw();
	}
}

//=========================
// 情報の設定処理
//=========================
void CEntryUI::SetData(const D3DXVECTOR3& pos, const int nID, const CPlayer::TYPE type)
{
	if (m_pFrame == nullptr)
	{ // 枠の情報が NULL の場合

		// 枠を生成する
		m_pFrame = CEntryFrame::Create(pos);
	}
	else
	{ // 上記以外

		// 停止
		assert(false);
	}

	if (m_pTeam == nullptr)
	{ // チームの情報が NULL の場合

		// チームを生成する
		m_pTeam = CEntryTeam::Create(D3DXVECTOR3(pos.x, pos.y - TEAM_SHIFT, 0.0f), type);
	}
	else
	{ // 上記以外

		// 停止
		assert(false);
	}

	if (m_pID == nullptr)
	{ // チームの情報が NULL の場合

		// チームを生成する
		m_pID = CEntryID::Create(D3DXVECTOR3(pos.x, pos.y + ID_SHIFT, 0.0f), nID);
	}
	else
	{ // 上記以外

		// 停止
		assert(false);
	}
}

//=========================
// 生成処理
//=========================
CEntryUI* CEntryUI::Create(const D3DXVECTOR3& pos, const int nID, const CPlayer::TYPE type)
{
	// ローカルオブジェクトを生成
	CEntryUI* pEntry = nullptr;	// プレイヤーのインスタンスを生成

	if (pEntry == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pEntry = new CEntryUI;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pEntry != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pEntry->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pEntry->SetData(pos, nID, type);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// エントリーUIのポインタを返す
	return pEntry;
}

//=========================
// チームの取得処理
//=========================
CEntryTeam* CEntryUI::GetTeam(void)
{
	// チームのポインタを返す
	return m_pTeam;
}