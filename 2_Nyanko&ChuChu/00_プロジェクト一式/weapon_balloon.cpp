//=======================================
//
// 武器のふきだしのメイン処理[weapon_balloon.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "weapon_balloon.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

//=======================================
// マクロ定義
//=======================================


//=========================
// コンストラクタ
//=========================
CWeaponBalloon::CWeaponBalloon() : CBillboard(CObject::TYPE_WEAPONBALLOON, CObject::PRIORITY_PLAYER)
{
	// 全ての値をクリアする
}

//=========================
// デストラクタ
//=========================
CWeaponBalloon::~CWeaponBalloon()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CWeaponBalloon::Init(void)
{
	if (FAILED(CBillboard::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する

	// 成功を返す
	return S_OK;
}

//=========================
// 終了処理
//=========================
void CWeaponBalloon::Uninit(void)
{
	// 終了
	CBillboard::Uninit();
}

//=========================
// 更新処理
//=========================
void CWeaponBalloon::Update(void)
{
	
}

//=========================
// 描画処理
//=========================
void CWeaponBalloon::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	//αブレンディングを加算処理に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// 描画処理
	CBillboard::DrawLightOff();

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=========================
// 情報の設定処理
//=========================
void CWeaponBalloon::SetData(const D3DXVECTOR3& pos, const char* pFileName)
{
	// スクロールの設定処理
	SetPos(pos);			// 位置設定
	SetPosOld(pos);			// 前回の位置設定
	SetSize(D3DXVECTOR3(140.0f, 140.0f, 0.0f));	// サイズ設定

	// 頂点情報の初期化
	SetVertex();

	// テクスチャの読み込み処理
	BindTexture(CManager::Get()->GetTexture()->Regist(pFileName));
}

//=========================
// 生成処理
//=========================
CWeaponBalloon* CWeaponBalloon::Create(const D3DXVECTOR3& pos, const char* pFileName)
{
	// ローカルオブジェクトを生成
	CWeaponBalloon* pBalloon = nullptr;		// ふきだしのインスタンスを生成

	if (pBalloon == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pBalloon = new CWeaponBalloon;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pBalloon != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pBalloon->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pBalloon->SetData(pos, pFileName);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// ふきだしのポインタを返す
	return pBalloon;
}