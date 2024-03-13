//=======================================
//
// アイテムのマークのメイン処理[item_mark.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "item_mark.h"
#include "texture.h"
#include "useful.h"

//=======================================
// マクロ定義
//=======================================
#define MOUSETRAP_TEXTURE	"data\\TEXTURE\\Mousetrap.png"		// ネズミ捕りのテクスチャ
#define DYNAMITE_TEXTURE	"data\\TEXTURE\\dynamite.png"		// ダイナマイトのテクスチャ
#define SMALL_MAGNI			(D3DXVECTOR3(0.9f, 1.1f, 0.0f))		// 小さい状態の倍率
#define BIG_MAGNI			(D3DXVECTOR3(1.1f, 0.9f, 0.0f))		// 大きい状態の倍率
#define SIZING_CORRECT		(0.05f)								// 拡縮の補正倍率
#define SIZING_BORDER		(0.1f)								// サイズの境界線

//=========================
// コンストラクタ
//=========================
CItemMark::CItemMark() : CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_UI)
{
	// 全ての値をクリアする
	m_sizeDest = NONE_D3DXVECTOR3;		// 目的のサイズ
	m_sizeCopy = NONE_D3DXVECTOR3;		// 初期のサイズ
	m_state = STATE_SMALL;				// 状態
	m_type = CItem::TYPE_MOUSETRAP;		// 種類
}

//=========================
// デストラクタ
//=========================
CItemMark::~CItemMark()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CItemMark::Init(void)
{
	if (FAILED(CObject2D::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	m_sizeDest = NONE_D3DXVECTOR3;		// 目的のサイズ
	m_sizeCopy = NONE_D3DXVECTOR3;		// 初期のサイズ
	m_state = STATE_SMALL;				// 状態
	m_type = CItem::TYPE_MOUSETRAP;		// 種類

	// 成功を返す
	return S_OK;
}

//=========================
// 終了処理
//=========================
void CItemMark::Uninit(void)
{
	// 終了
	CObject2D::Uninit();
}

//=========================
// 更新処理
//=========================
void CItemMark::Update(void)
{
	// サイズ設定処理
	Sizing();

	// 頂点座標の設定処理
	SetVertex();
}

//=========================
// 描画処理
//=========================
void CItemMark::Draw(void)
{
	// 描画処理
	CObject2D::Draw();
}

//=========================
// 情報の設定処理
//=========================
void CItemMark::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const CItem::TYPE type)
{
	// スクロールの設定処理
	SetPos(pos);				// 位置設定
	SetRot(NONE_D3DXVECTOR3);	// 向き設定
	SetSize(size);				// サイズ設定
	SetLength();				// 長さ設定
	SetAngle();					// 方向設定

	// 全ての値を設定する
	m_sizeDest.x = size.x * SMALL_MAGNI.x;			// 目的のサイズ(X軸)
	m_sizeDest.y = size.y * SMALL_MAGNI.y;			// 目的のサイズ(Y軸)
	m_sizeCopy = size;			// 初期のサイズ
	m_state = STATE_SMALL;		// 状態
	m_type = type;				// 種類

	switch (type)
	{
	case CItem::TYPE_MOUSETRAP:

		// テクスチャの割り当て処理
		BindTexture(CManager::Get()->GetTexture()->Regist(MOUSETRAP_TEXTURE));

		break;

	case CItem::TYPE_DYNAMITE:

		// テクスチャの割り当て処理
		BindTexture(CManager::Get()->GetTexture()->Regist(DYNAMITE_TEXTURE));

		break;

	default:

		// 停止
		assert(false);

		break;
	}

	// 頂点情報の初期化
	SetVertex();
}

//=========================
// 生成処理
//=========================
CItemMark* CItemMark::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const CItem::TYPE type)
{
	// ローカルオブジェクトを生成
	CItemMark* pItemMark = nullptr;		// プレイヤーのインスタンスを生成

	if (pItemMark == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pItemMark = new CItemMark;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pItemMark != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pItemMark->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pItemMark->SetData(pos, size, type);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// アイテムマークのポインタを返す
	return pItemMark;
}

//=========================
// 種類の取得処理
//=========================
CItem::TYPE CItemMark::GetType(void) const
{
	// 種類を返す
	return m_type;
}

//=========================
// サイズ設定処理
//=========================
void CItemMark::Sizing(void)
{
	// サイズを取得する
	D3DXVECTOR3 size = GetSize();

	// サイズの補正処理
	useful::Correct(m_sizeDest.x, &size.x, SIZING_CORRECT);
	useful::Correct(m_sizeDest.y, &size.y, SIZING_CORRECT);
	useful::Correct(m_sizeDest.z, &size.z, SIZING_CORRECT);

	switch (m_state)
	{
	case CItemMark::STATE_SMALL:

		if (m_sizeDest.x + SIZING_BORDER >= size.x)
		{ // 目的のサイズに一定量近づいた場合

			// 拡大状態にする
			m_state = STATE_BIG;

			// 目的のサイズを設定する
			m_sizeDest.x = m_sizeCopy.x * BIG_MAGNI.x;
			m_sizeDest.y = m_sizeCopy.y * BIG_MAGNI.y;
		}

		break;

	case CItemMark::STATE_BIG:

		if (m_sizeDest.x - SIZING_BORDER <= size.x)
		{ // 目的のサイズに一定量近づいた場合

			// 縮小状態にする
			m_state = STATE_SMALL;

			// 目的のサイズを設定する
			m_sizeDest.x = m_sizeCopy.x * SMALL_MAGNI.x;
			m_sizeDest.y = m_sizeCopy.y * SMALL_MAGNI.y;
		}

		break;

	default:

		// 停止
		assert(false);

		break;
	}

	// サイズを適用する
	SetSize(size);
}