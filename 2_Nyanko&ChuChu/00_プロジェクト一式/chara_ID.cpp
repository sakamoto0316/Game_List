//=======================================
//
// キャラクターのIDのメイン処理[chara_ID.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "chara_ID.h"
#include "texture.h"
#include "useful.h"

//=======================================
// マクロ定義
//=======================================
#define ID_PATTERN		((float)(1.0f / 4.0f))					// IDの1面ごとのサイズ
#define ID_SIZE			(D3DXVECTOR3(40.0f, 25.0f, 0.0f))		// IDのサイズ
#define ID_TEXTURE		"data\\TEXTURE\\PlayerID.png"			// IDのテクスチャ

//=========================
// コンストラクタ
//=========================
CCharaID::CCharaID() : CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_UI)
{

}

//=========================
// デストラクタ
//=========================
CCharaID::~CCharaID()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CCharaID::Init(void)
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
void CCharaID::Uninit(void)
{
	// 終了
	CObject2D::Uninit();
}

//=========================
// 更新処理
//=========================
void CCharaID::Update(void)
{

}

//=========================
// 描画処理
//=========================
void CCharaID::Draw(void)
{
	// 描画処理
	CObject2D::Draw();
}

//=========================
// 情報の設定処理
//=========================
void CCharaID::SetData(const D3DXVECTOR3& pos, const int nID)
{
	// スクロールの設定処理
	SetPos(pos);				// 位置設定
	SetRot(NONE_D3DXVECTOR3);	// 向き設定
	SetSize(ID_SIZE);			// サイズ設定
	SetLength();				// 長さ設定
	SetAngle();					// 方向設定

	// 頂点情報の初期化
	SetVertex();

	// テクスチャの読み込み処理
	BindTexture(CManager::Get()->GetTexture()->Regist(ID_TEXTURE));

	// テクスチャ座標の設定処理
	SetVtxTextureAnim(ID_PATTERN, nID);
}

//=========================
// 生成処理
//=========================
CCharaID* CCharaID::Create(const D3DXVECTOR3& pos, const int nID)
{
	// ローカルオブジェクトを生成
	CCharaID* pCharaImage = nullptr;	// プレイヤーのインスタンスを生成

	if (pCharaImage == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pCharaImage = new CCharaID;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pCharaImage != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pCharaImage->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pCharaImage->SetData(pos, nID);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// キャラクター画像のポインタを返す
	return pCharaImage;
}