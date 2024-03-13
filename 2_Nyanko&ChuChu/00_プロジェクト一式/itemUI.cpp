//============================================
//
// アイテムUI処理[itemUI.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "itemUI.h"
#include "texture.h"
#include "useful.h"

#include "item_mark.h"
#include "item_frame.h"

//--------------------------------------------
// 無名名前空間
//--------------------------------------------
namespace
{
	const D3DXVECTOR3 FRAME_POS_SHIFT_BACK = D3DXVECTOR3(-40.0f, 20.0f, 0.0f);		// 後ろの枠の位置のずらす幅
	const D3DXVECTOR3 FRAME_SIZE[CItemUI::ORDER_MAX] =								// 枠のサイズ
	{
		D3DXVECTOR3(30.0f, 30.0f, 0.0f),			// 後ろ
		D3DXVECTOR3(50.0f, 50.0f, 0.0f),			// 前
	};
	const D3DXVECTOR3 MARK_SIZE[CItemUI::ORDER_MAX] =								// 枠のサイズ
	{
		D3DXVECTOR3(15.0f, 15.0f, 0.0f),			// 後ろ
		D3DXVECTOR3(30.0f, 30.0f, 0.0f),			// 前
	};
}

//========================
// コンストラクタ
//========================
CItemUI::CItemUI() : CObject(TYPE_ITEMUI, PRIORITY_UI)
{
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < ORDER_MAX; nCnt++)
	{
		m_aItemUI[nCnt].pMark = nullptr;				// マークの情報
		m_aItemUI[nCnt].pFrame = nullptr;				// 枠の情報
	}
}

//========================
// デストラクタ
//========================
CItemUI::~CItemUI()
{

}

//========================
// 初期化処理
//========================
HRESULT CItemUI::Init(void)
{
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < ORDER_MAX; nCnt++)
	{
		m_aItemUI[nCnt].pMark = nullptr;				// マークの情報
		m_aItemUI[nCnt].pFrame = nullptr;				// 枠の情報
	}

	// 成功を返す
	return S_OK;
}

//========================
// 終了処理
//========================
void CItemUI::Uninit(void)
{
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < ORDER_MAX; nCnt++)
	{
		if (m_aItemUI[nCnt].pMark != nullptr)
		{ // マークが NULL じゃない場合

			// マークの終了処理
			m_aItemUI[nCnt].pMark->Uninit();
			m_aItemUI[nCnt].pMark = nullptr;
		}

		if (m_aItemUI[nCnt].pFrame != nullptr)
		{ // 枠が NULL じゃない場合

			// 枠の終了処理
			m_aItemUI[nCnt].pFrame->Uninit();
			m_aItemUI[nCnt].pFrame = nullptr;
		}
	}

	// 本体の終了処理
	Release();
}

//========================
// 更新処理
//========================
void CItemUI::Update(void)
{
	for (int nCnt = 0; nCnt < ORDER_MAX; nCnt++)
	{
		if (m_aItemUI[nCnt].pFrame != nullptr)
		{ // 枠が NULL じゃない場合

			// 枠の更新処理
			m_aItemUI[nCnt].pFrame->Update();
		}

		if (m_aItemUI[nCnt].pMark != nullptr)
		{ // マークが NULL じゃない場合

			// マークの更新処理
			m_aItemUI[nCnt].pMark->Update();
		}
	}
}

//========================
// 描画処理
//========================
void CItemUI::Draw(void)
{
	for (int nCnt = 0; nCnt < ORDER_MAX; nCnt++)
	{
		if (m_aItemUI[nCnt].pFrame != nullptr)
		{ // 枠が NULL じゃない場合

			// 枠の描画処理
			m_aItemUI[nCnt].pFrame->Draw();
		}

		if (m_aItemUI[nCnt].pMark != nullptr)
		{ // マークが NULL じゃない場合

			// マークの描画処理
			m_aItemUI[nCnt].pMark->Draw();
		}
	}
}

//========================
// 情報の設定処理
//========================
void CItemUI::SetData(const D3DXVECTOR3& pos)
{
	for (int nCnt = 0; nCnt < ORDER_MAX; nCnt++)
	{
		switch (nCnt)
		{
		case ORDER_BACK:		// 後ろ

			// 枠を生成する
			m_aItemUI[nCnt].pFrame = CItemFrame::Create(pos + FRAME_POS_SHIFT_BACK, FRAME_SIZE[nCnt], CPlayer::TYPE::TYPE_CAT);

			break;

		case ORDER_FRONT:		// 前

			// 枠を生成する
			m_aItemUI[nCnt].pFrame = CItemFrame::Create(pos, FRAME_SIZE[nCnt], CPlayer::TYPE::TYPE_CAT);

			break;

		default:

			// 停止
			assert(false);

			break;
		}
	}
}

//========================
// 情報のソート処理
//========================
void CItemUI::SortInfo(void)
{
	// 終了処理
	m_aItemUI[ORDER_FRONT].pMark->Uninit();
	m_aItemUI[ORDER_FRONT].pMark = nullptr;

	if (m_aItemUI[ORDER_BACK].pMark != nullptr)
	{ // マークが NULL じゃない場合

		// 後半のマークを設定する
		m_aItemUI[ORDER_FRONT].pMark = CItemMark::Create(m_aItemUI[ORDER_FRONT].pFrame->GetPos(), MARK_SIZE[ORDER_FRONT], m_aItemUI[ORDER_BACK].pMark->GetType());

		// 終了処理
		m_aItemUI[ORDER_BACK].pMark->Uninit();
		m_aItemUI[ORDER_BACK].pMark = nullptr;
	}
}

//========================
// 生成処理
//========================
CItemUI* CItemUI::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CItemUI* pItemUI = nullptr;		// キャラクター情報UIのインスタンスを生成

	if (pItemUI == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pItemUI = new CItemUI;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pItemUI != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pItemUI->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pItemUI->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// アイテムUIのポインタを返す
	return pItemUI;
}

//========================
// マークの生成処理
//========================
void CItemUI::SetMark(const CItem::TYPE type, const ORDER order)
{
	if (m_aItemUI[order].pMark == nullptr)
	{ // マークの情報が NULL の場合

		// アイテムUIのマークを設定する
		m_aItemUI[order].pMark = CItemMark::Create(m_aItemUI[order].pFrame->GetPos(), MARK_SIZE[order], type);
	}
}

//========================
// アイテムUIの取得処理
//========================
CItemUI::SItemUI CItemUI::GetItemUI(const ORDER order) const
{
	// アイテムUIの情報を返す
	return m_aItemUI[order];
}