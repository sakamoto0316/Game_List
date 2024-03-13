//===========================================
//
// タイトルの壁のメイン処理[title_wall.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "title_wall.h"

//==============================
// コンストラクタ
//==============================
CTitleWall::CTitleWall() : CModel(CObject::TYPE_TITLEWALL, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
}

//==============================
// デストラクタ
//==============================
CTitleWall::~CTitleWall()
{

}

//==============================
// 破片の初期化処理
//==============================
HRESULT CTitleWall::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 値を返す
	return S_OK;
}

//========================================
// 破片の終了処理
//========================================
void CTitleWall::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}

//=====================================
// 破片の更新処理
//=====================================
void CTitleWall::Update(void)
{

}

//=====================================
// 破片の描画処理
//=====================================
void CTitleWall::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CTitleWall::SetData(void)
{
	// 情報の設定処理
	SetPos(NONE_D3DXVECTOR3);				// 位置
	SetPosOld(NONE_D3DXVECTOR3);			// 前回の位置
	SetRot(NONE_D3DXVECTOR3);				// 向き
	SetScale(NONE_SCALE);					// 拡大率
	SetFileData(CXFile::TYPE_TITLEWALL);	// モデル情報
}

//=======================================
// 生成処理
//=======================================
CTitleWall* CTitleWall::Create(void)
{
	// ローカルオブジェクトを生成
	CTitleWall* pTitle = nullptr;	// インスタンスを生成

	if (pTitle == nullptr)
	{ // オブジェクトが NULL の場合

		// インスタンスを生成
		pTitle = new CTitleWall;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pTitle != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pTitle->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pTitle->SetData();
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// タイトルの壁のポインタを返す
	return pTitle;
}