//===========================================
//
// ネズミ捕りの鉄部分のメイン処理[mousetrap_iron.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "mousetrap_iron.h"
#include "renderer.h"
#include "useful.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define ROT_MOVE	(0.3f)		// 向きの移動量

//==============================
// コンストラクタ
//==============================
CTrapIron::CTrapIron() : CModel(CObject::TYPE_NONE, CObject::PRIORITY_BLOCK)
{

}

//==============================
// デストラクタ
//==============================
CTrapIron::~CTrapIron()
{

}

//==============================
// 破片の初期化処理
//==============================
HRESULT CTrapIron::Init(void)
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
void CTrapIron::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}

//=====================================
// 破片の更新処理
//=====================================
void CTrapIron::Update(void)
{

}

//=====================================
// 破片の描画処理
//=====================================
void CTrapIron::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CTrapIron::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// 情報の設定処理
	SetPos(pos);								// 位置
	SetPosOld(pos);								// 前回の位置
	SetRot(rot);								// 向き
	SetScale(NONE_SCALE);						// 拡大率
	SetFileData(CXFile::TYPE_TRAPIRON);			// モデル情報
}

//=======================================
// 生成処理
//=======================================
CTrapIron* CTrapIron::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// ローカルオブジェクトを生成
	CTrapIron* pIron = nullptr;	// インスタンスを生成

	if (pIron == nullptr)
	{ // オブジェクトが NULL の場合

		// インスタンスを生成
		pIron = new CTrapIron;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pIron != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pIron->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pIron->SetData(pos, rot);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// ネズミ捕りの鉄部分のポインタを返す
	return pIron;
}

//=======================================
// 移動処理
//=======================================
bool CTrapIron::Move(void)
{
	// 向きを取得する
	D3DXVECTOR3 rot = GetRot();

	// 向きを加算する
	rot.z += ROT_MOVE;

	if (rot.z >= D3DX_PI)
	{ // 向きが一定数の場合

		// 向きの正規化
		useful::RotNormalize(&rot.z);

		// 向きを適用する
		SetRot(rot);

		// true を返す
		return true;
	}
	else
	{ // 上記以外

		// 向きの正規化
		useful::RotNormalize(&rot.z);

		// 向きを適用する
		SetRot(rot);

		// false を返す
		return false;
	}
}