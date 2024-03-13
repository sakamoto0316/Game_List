//=======================================
//
// エントリーの枠のメイン処理[entry_frame.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "entry_frame.h"
#include "texture.h"

//=======================================
// マクロ定義
//=======================================
#define FRAME_SIZE		(D3DXVECTOR3(155.0f, 310.0f, 0.0f))		// 枠のサイズ
#define FRAME_TEXTURE	"data\\TEXTURE\\EntryFrame.png"			// 枠のテクスチャ

//=========================
// コンストラクタ
//=========================
CEntryFrame::CEntryFrame() : CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_UI)
{

}

//=========================
// デストラクタ
//=========================
CEntryFrame::~CEntryFrame()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CEntryFrame::Init(void)
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
void CEntryFrame::Uninit(void)
{
	// 終了
	CObject2D::Uninit();
}

//=========================
// 更新処理
//=========================
void CEntryFrame::Update(void)
{

}

//=========================
// 描画処理
//=========================
void CEntryFrame::Draw(void)
{
	// 描画処理
	CObject2D::Draw();
}

//=========================
// 情報の設定処理
//=========================
void CEntryFrame::SetData(const D3DXVECTOR3& pos)
{
	// スクロールの設定処理
	SetPos(pos);				// 位置設定
	SetRot(NONE_D3DXVECTOR3);	// 向き設定
	SetSize(FRAME_SIZE);		// サイズ設定
	SetLength();				// 長さ設定
	SetAngle();					// 方向設定

	// テクスチャの読み込み処理
	BindTexture(CManager::Get()->GetTexture()->Regist(FRAME_TEXTURE));

	// 頂点情報の初期化
	SetVertex();
}

//=========================
// 生成処理
//=========================
CEntryFrame* CEntryFrame::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CEntryFrame* pEntryFrame = nullptr;	// プレイヤーのインスタンスを生成

	if (pEntryFrame == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pEntryFrame = new CEntryFrame;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pEntryFrame != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pEntryFrame->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pEntryFrame->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// エントリーの枠のポインタを返す
	return pEntryFrame;
}