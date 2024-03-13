//=======================================
//
// アイテムの枠のメイン処理[item_frame.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "item_frame.h"
#include "texture.h"
#include "useful.h"

//=======================================
// マクロ定義
//=======================================
#define CAT_TEXTURE			"data\\TEXTURE\\Cat_Frame.png"		// ネコの枠のテクスチャ
#define RAT_TEXTURE			"data\\TEXTURE\\Rat_Frame.png"		// ネズミの枠のテクスチャ

//=========================
// コンストラクタ
//=========================
CItemFrame::CItemFrame() : CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_UI)
{

}

//=========================
// デストラクタ
//=========================
CItemFrame::~CItemFrame()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CItemFrame::Init(void)
{
	if (FAILED(CObject2D::Init()))
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
void CItemFrame::Uninit(void)
{
	// 終了
	CObject2D::Uninit();
}

//=========================
// 更新処理
//=========================
void CItemFrame::Update(void)
{

}

//=========================
// 描画処理
//=========================
void CItemFrame::Draw(void)
{
	// 描画処理
	CObject2D::Draw();
}

//=========================
// 情報の設定処理
//=========================
void CItemFrame::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const CPlayer::TYPE type)
{
	// スクロールの設定処理
	SetPos(pos);				// 位置設定
	SetRot(NONE_D3DXVECTOR3);	// 向き設定
	SetSize(size);				// サイズ設定
	SetLength();				// 長さ設定
	SetAngle();					// 方向設定

	switch (type)
	{
	case CPlayer::TYPE_CAT:		// ネコ

		// テクスチャの割り当て処理
		BindTexture(CManager::Get()->GetTexture()->Regist(CAT_TEXTURE));

		break;

	case CPlayer::TYPE_RAT:		// ネズミ

		// テクスチャの割り当て処理
		BindTexture(CManager::Get()->GetTexture()->Regist(RAT_TEXTURE));

		break;

	default:					// 上記以外

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
CItemFrame* CItemFrame::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const CPlayer::TYPE type)
{
	// ローカルオブジェクトを生成
	CItemFrame* pItemFrame = nullptr;		// プレイヤーのインスタンスを生成

	if (pItemFrame == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pItemFrame = new CItemFrame;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pItemFrame != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pItemFrame->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pItemFrame->SetData(pos, size, type);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// アイテム枠のポインタを返す
	return pItemFrame;
}