//=======================================
//
// 武器選択UIのメイン処理[weapon_selectUI.cpp]
// Author 小原立暉
//
//=======================================
#include "main.h"
#include "manager.h"
#include "weapon_selectUI.h"
#include "object2D.h"
#include "texture.h"

#include "weapon_cage.h"
#include "weapon_balloon.h"

//---------------------------------------
// マクロ定義
//---------------------------------------
#define BALLOON_TEXTURE		"data\\TEXTURE\\Balloon.png"		// ふきだしのテクスチャ

//==========================================
// コンストラクタ
//==========================================
CWeaponSelectUI::CWeaponSelectUI() : CObject(TYPE_WEAPONSELECTUI, PRIORITY_PLAYER)
{
	// 全ての値をクリアする
	m_pos = NONE_D3DXVECTOR3;	// 位置
	m_pCage = nullptr;			// 武器小屋の情報
	m_pBalloon = nullptr;		// ふきだしの情報
}

//==========================================
// デストラクタ
//==========================================
CWeaponSelectUI::~CWeaponSelectUI()
{

}

//==========================================
// ポーズの初期化処理
//==========================================
HRESULT CWeaponSelectUI::Init(void)
{
	// 全ての値を初期化する
	m_pos = NONE_D3DXVECTOR3;	// 位置

	if (m_pCage == nullptr)
	{ // 武器小屋の情報が NULL の場合

		// 武器小屋を生成する
		m_pCage = CWeaponCage::Create(m_pos);
	}

	if (m_pBalloon == nullptr)
	{ // ふきだしの情報が NULL の場合

		// ふきだしを生成する
		m_pBalloon = CWeaponBalloon::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z), BALLOON_TEXTURE);
	}

	// 成功を返す
	return S_OK;
}

//========================================
// ポーズの終了処理
//========================================
void CWeaponSelectUI::Uninit(void)
{
	if (m_pCage != nullptr)
	{ // 武器小屋が NULL じゃない場合

		// 武器小屋の終了処理
		m_pCage->Uninit();
		m_pCage = nullptr;
	}

	if (m_pBalloon != nullptr)
	{ // ふきだしが NULL じゃない場合

		// ふきだしの終了処理
		m_pBalloon->Uninit();
		m_pBalloon = nullptr;
	}

	// 本体の終了処理
	Release();
}

//========================================
// ポーズの更新処理
//========================================
void CWeaponSelectUI::Update(void)
{
	
}

//=====================================
// ポーズの描画処理
//=====================================
void CWeaponSelectUI::Draw(void)
{
	if (m_pCage != nullptr)
	{ // 武器小屋が NULL じゃない場合

		// 描画処理
		m_pCage->Draw();
	}

	if (m_pBalloon != nullptr)
	{ // ふきだしが NULL じゃない場合

		// 描画処理
		m_pBalloon->Draw();
	}
}

//=====================================
// 生成処理
//=====================================
CWeaponSelectUI* CWeaponSelectUI::Create(void)
{
	// ローカルオブジェクトを生成
	CWeaponSelectUI* pWeapon = nullptr;	// プレイヤーのインスタンスを生成

	if (pWeapon == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pWeapon = new CWeaponSelectUI;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pWeapon != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pWeapon->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 武器選択UIのポインタを返す
	return pWeapon;
}