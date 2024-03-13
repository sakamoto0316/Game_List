//=======================================
//
// エントリーのIDのメイン処理[entry_ID.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "entry_ID.h"
#include "texture.h"

//=======================================
// マクロ定義
//=======================================
#define ID_SIZE		(D3DXVECTOR3(120.0f, 60.0f, 0.0f))		// IDのサイズ
#define ID_TEXTURE	"data\\TEXTURE\\PlayerID.png"			// IDのテクスチャ
#define ID_PATTERN		(0.25f)								// IDのテクスチャのパターン数

//=========================
// コンストラクタ
//=========================
CEntryID::CEntryID() : CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_UI)
{

}

//=========================
// デストラクタ
//=========================
CEntryID::~CEntryID()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CEntryID::Init(void)
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
void CEntryID::Uninit(void)
{
	// 終了
	CObject2D::Uninit();
}

//=========================
// 更新処理
//=========================
void CEntryID::Update(void)
{

}

//=========================
// 描画処理
//=========================
void CEntryID::Draw(void)
{
	// 描画処理
	CObject2D::Draw();
}

//=========================
// 情報の設定処理
//=========================
void CEntryID::SetData(const D3DXVECTOR3& pos, const int nID)
{
	// スクロールの設定処理
	SetPos(pos);				// 位置設定
	SetRot(NONE_D3DXVECTOR3);	// 向き設定
	SetSize(ID_SIZE);		// サイズ設定
	SetLength();				// 長さ設定
	SetAngle();					// 方向設定

	// テクスチャの読み込み処理
	BindTexture(CManager::Get()->GetTexture()->Regist(ID_TEXTURE));

	// 頂点情報の初期化
	SetVertex();

	// テクスチャ座標の設定処理
	SetVtxTextureAnim(ID_PATTERN, nID);
}

//=========================
// 生成処理
//=========================
CEntryID* CEntryID::Create(const D3DXVECTOR3& pos, const int nID)
{
	// ローカルオブジェクトを生成
	CEntryID* pEntryId = nullptr;	// プレイヤーのインスタンスを生成

	if (pEntryId == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pEntryId = new CEntryID;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pEntryId != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pEntryId->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pEntryId->SetData(pos, nID);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// エントリーの枠のポインタを返す
	return pEntryId;
}