//=======================================
//
// キャラクターの画像のメイン処理[chara_image.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "chara_icon.h"
#include "texture.h"
#include "useful.h"

//=======================================
// マクロ定義
//=======================================
#define ICON_SIZE			(D3DXVECTOR3(50.0f, 50.0f, 0.0f))		// アイコンのサイズ
#define CAT_ICON_TEXTURE	"data\\TEXTURE\\Cat_Icon.png"			// ネコのアイコンのテクスチャ
#define RAT_ICON_TEXTURE	"data\\TEXTURE\\Rat_Icon.png"			// ネズミのアイコンのテクスチャ

//=========================
// コンストラクタ
//=========================
CCharaIcon::CCharaIcon() : CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_UI)
{

}

//=========================
// デストラクタ
//=========================
CCharaIcon::~CCharaIcon()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CCharaIcon::Init(void)
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
void CCharaIcon::Uninit(void)
{
	// 終了
	CObject2D::Uninit();
}

//=========================
// 更新処理
//=========================
void CCharaIcon::Update(void)
{

}

//=========================
// 描画処理
//=========================
void CCharaIcon::Draw(void)
{
	// 描画処理
	CObject2D::Draw();
}

//=========================
// 情報の設定処理
//=========================
void CCharaIcon::SetData(const D3DXVECTOR3& pos, const CPlayer::TYPE type)
{
	// スクロールの設定処理
	SetPos(pos);				// 位置設定
	SetRot(NONE_D3DXVECTOR3);	// 向き設定
	SetSize(ICON_SIZE);			// サイズ設定
	SetLength();				// 長さ設定
	SetAngle();					// 方向設定

	// 頂点情報の初期化
	SetVertex();

	switch (type)
	{
	case CPlayer::TYPE_CAT:

		// テクスチャの読み込み処理
		BindTexture(CManager::Get()->GetTexture()->Regist(CAT_ICON_TEXTURE));

		break;

	case CPlayer::TYPE_RAT:

		// テクスチャの読み込み処理
		BindTexture(CManager::Get()->GetTexture()->Regist(RAT_ICON_TEXTURE));

		break;

	default:

		// 停止
		assert(false);

		break;
	}
}

//=========================
// 生成処理
//=========================
CCharaIcon* CCharaIcon::Create(const D3DXVECTOR3& pos, const CPlayer::TYPE type)
{
	// ローカルオブジェクトを生成
	CCharaIcon* pCharaImage = nullptr;	// プレイヤーのインスタンスを生成

	if (pCharaImage == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pCharaImage = new CCharaIcon;
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
		pCharaImage->SetData(pos, type);
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