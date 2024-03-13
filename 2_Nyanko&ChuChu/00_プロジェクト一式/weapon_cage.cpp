//===========================================
//
// 武器小屋のメイン処理[weapon_cage.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "weapon_cage.h"
#include "useful.h"

//==============================
// コンストラクタ
//==============================
CWeaponCage::CWeaponCage() : CModel(CObject::TYPE_WEAPONCAGE, CObject::PRIORITY_PLAYER)
{
	// 全ての値をクリアする
}

//==============================
// デストラクタ
//==============================
CWeaponCage::~CWeaponCage()
{

}

//==============================
// 破片の初期化処理
//==============================
HRESULT CWeaponCage::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する

	// 値を返す
	return S_OK;
}

//========================================
// 破片の終了処理
//========================================
void CWeaponCage::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}

//=====================================
// 破片の更新処理
//=====================================
void CWeaponCage::Update(void)
{

}

//=====================================
// 破片の描画処理
//=====================================
void CWeaponCage::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CWeaponCage::SetData(const D3DXVECTOR3& pos)
{
	// 情報の設定処理
	SetPos(pos);							// 位置
	SetPosOld(pos);							// 前回の位置
	SetRot(NONE_D3DXVECTOR3);				// 向き
	SetScale(NONE_SCALE);					// 拡大率
	SetFileData(CXFile::TYPE_WEAPONCAGE);	// モデル情報
}

//=======================================
// 生成処理
//=======================================
CWeaponCage* CWeaponCage::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CWeaponCage* pCage = nullptr;	// インスタンスを生成

	if (pCage == nullptr)
	{ // オブジェクトが NULL の場合

		// インスタンスを生成
		pCage = new CWeaponCage;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pCage != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pCage->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pCage->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// ケージのポインタを返す
	return pCage;
}