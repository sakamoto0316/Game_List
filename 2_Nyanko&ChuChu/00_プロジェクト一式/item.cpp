//===========================================
//
// アイテムのメイン処理[item.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "item.h"
#include "item_manager.h"
#include "useful.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define ROT_MOVE		(0.01f)		// 向きの移動量
#define EXTEND_SCALE	(1.05f)		// 拡大時の拡大率
#define SHRINK_SCALE	(0.95f)		// 拡縮時の拡大率

//==============================
// コンストラクタ
//==============================
CItem::CItem() : CModel(CObject::TYPE_ITEM, CObject::PRIORITY_ENTITY)
{
	// 全ての値をクリアする
	m_type = TYPE_MOUSETRAP;		// 種類
	m_state = STATE_NONE;			// 状態
	m_fScaleDest = 0.0f;			// 目的の拡大率
	m_pPrev = nullptr;				// 前のへのポインタ
	m_pNext = nullptr;				// 次のへのポインタ

	if (CItemManager::Get() != nullptr)
	{ // マネージャーが存在していた場合

		// マネージャーへの登録処理
		CItemManager::Get()->Regist(this);
	}
}

//==============================
// デストラクタ
//==============================
CItem::~CItem()
{

}

//============================
// 前のポインタの設定処理
//============================
void CItem::SetPrev(CItem* pPrev)
{
	// 前のポインタを設定する
	m_pPrev = pPrev;
}

//============================
// 後のポインタの設定処理
//============================
void CItem::SetNext(CItem* pNext)
{
	// 次のポインタを設定する
	m_pNext = pNext;
}

//============================
// 前のポインタの設定処理
//============================
CItem* CItem::GetPrev(void) const
{
	// 前のポインタを返す
	return m_pPrev;
}

//============================
// 次のポインタの設定処理
//============================
CItem* CItem::GetNext(void) const
{
	// 次のポインタを返す
	return m_pNext;
}

//==============================
// 初期化処理
//==============================
HRESULT CItem::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	m_type = TYPE_MOUSETRAP;	// 種類
	m_state = STATE_STANDBY;	// 状態
	m_fScaleDest = 0.0f;		// 目的の拡大率

	// 値を返す
	return S_OK;
}

//========================================
// 終了処理
//========================================
void CItem::Uninit(void)
{
	// 終了処理
	CModel::Uninit();

	if (CItemManager::Get() != nullptr)
	{ // マネージャーが存在していた場合

		// リスト構造の引き抜き処理
		CItemManager::Get()->Pull(this);
	}

	// リスト構造関係のポインタを NULL にする
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//=====================================
// 更新処理
//=====================================
void CItem::Update(void)
{
	// 回転処理
	Cycle();

	// 拡縮処理
	Scaling();
}

//=====================================
// 描画処理
//=====================================
void CItem::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CItem::SetData(const D3DXVECTOR3& pos, const TYPE type)
{
	// 情報の設定処理
	SetPos(pos);							// 位置
	SetPosOld(pos);							// 前回の位置
	SetRot(NONE_D3DXVECTOR3);				// 向き
	SetScale(D3DXVECTOR3(0.0f,0.0f,0.0f));	// 拡大率
	SetFileData(CXFile::TYPE_TRAPITEM);		// モデルの情報

	// 全ての値を設定する
	m_type = type;					// 種類
	m_fScaleDest = EXTEND_SCALE;	// 目的の拡大率
}

//=====================================
// 生成処理
//=====================================
CItem* CItem::Create(const D3DXVECTOR3& pos, const TYPE type)
{
	// ローカルオブジェクトを生成
	CItem* pItem = nullptr;	// インスタンスを生成

	if (pItem == nullptr)
	{ // オブジェクトが NULL の場合

		// 毬を生成する
		pItem = new CItem;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pItem != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pItem->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pItem->SetData(pos, type);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// アイテムのポインタを返す
	return pItem;
}

//=====================================
// 種類の設定処理
//=====================================
void CItem::SetType(const TYPE type)
{
	// 種類を設定する
	m_type = type;
}

//=====================================
// 状態の設定処理
//=====================================
void CItem::SetState(const STATE state)
{
	// 状態を設定する
	m_state = state;
}

//=====================================
// 種類の取得処理
//=====================================
CItem::TYPE CItem::GetType(void) const
{
	// 種類を返す
	return m_type;
}

//=====================================
// 種類の取得処理
//=====================================
CItem::STATE CItem::GetState(void) const
{
	// 状態を返す
	return m_state;
}

//=====================================
// 回転処理
//=====================================
void CItem::Cycle(void)
{
	// 向きを取得する
	D3DXVECTOR3 rot = GetRot();		// 向きを取得する

	// 向きを加算する
	rot.y += ROT_MOVE;

	// 向きを適用する
	SetRot(rot);
}

//=====================================
// 拡縮処理
//=====================================
void CItem::Scaling(void)
{
	// 拡大率を取得する
	D3DXVECTOR3 scale = GetScale();

	switch (m_state)
	{
	case CItem::STATE_NONE:		// 何もしない

		// 拡大率の補正処理
		if (useful::FrameCorrect(m_fScaleDest, &scale.x, 0.002f) == true ||
			useful::FrameCorrect(m_fScaleDest, &scale.y, 0.002f) == true ||
			useful::FrameCorrect(m_fScaleDest, &scale.z, 0.002f) == true)
		{ // 目的の値になった場合

			// 目的の拡大率を設定する
			m_fScaleDest = (m_fScaleDest >= EXTEND_SCALE) ? SHRINK_SCALE : EXTEND_SCALE;
		}

		break;

	case CItem::STATE_STANDBY:	// 待機

		// 拡大率の補正処理
		if (useful::FrameCorrect(m_fScaleDest, &scale.x, 0.05f) == true ||
			useful::FrameCorrect(m_fScaleDest, &scale.y, 0.05f) == true ||
			useful::FrameCorrect(m_fScaleDest, &scale.z, 0.05f) == true)
		{ // 目的の値になった場合

			m_state = STATE_NONE;		// 何もしない状態にする
		}

		break;

	default:

		// 停止する
		assert(false);

		break;
	}

	// 拡大率を適用する
	SetScale(scale);
}