//===========================================
//
// 扇風機のファンのメイン処理[fan_blade.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "fan_blade.h"
#include "useful.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define ROT_MOVE_CORRECT		(0.01f)		// 向きの移動量の補正量

//==============================
// コンストラクタ
//==============================
CFanBlade::CFanBlade() : CModel(CObject::TYPE_NONE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	m_fRotMove = 0.0f;			// 向きの移動量
	m_fRotMoveDest = 0.0f;		// 目的の向きの移動量
}

//==============================
// デストラクタ
//==============================
CFanBlade::~CFanBlade()
{

}

//==============================
// 破片の初期化処理
//==============================
HRESULT CFanBlade::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値をクリアする
	m_fRotMove = 0.0f;			// 向きの移動量
	m_fRotMoveDest = 0.0f;		// 目的の向きの移動量

	// 値を返す
	return S_OK;
}

//========================================
// 破片の終了処理
//========================================
void CFanBlade::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}

//=====================================
// 破片の更新処理
//=====================================
void CFanBlade::Update(void)
{
	// 向きを取得する
	D3DXVECTOR3 rot = GetRot();

	// 向きの補正処理
	useful::RotCorrect(m_fRotMoveDest, &m_fRotMove, ROT_MOVE_CORRECT);

	// 向きを加算する
	rot.z += m_fRotMove;

	// 向きを適用する
	SetRot(rot);
}

//=====================================
// 破片の描画処理
//=====================================
void CFanBlade::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=====================================
// 破片の描画処理
//=====================================
void CFanBlade::Draw(const float fAlpha)
{
	// 描画処理
	CModel::Draw(fAlpha);
}

//=====================================
// 情報の設定処理
//=====================================
void CFanBlade::SetData(const D3DXVECTOR3& pos)
{
	// 情報の設定処理
	SetPos(pos);								// 位置
	SetPosOld(pos);								// 前回の位置
	SetRot(NONE_D3DXVECTOR3);					// 向き
	SetScale(NONE_SCALE);						// 拡大率
	SetFileData(CXFile::TYPE_FANBLADE);			// モデル情報
}

//=======================================
// 生成処理
//=======================================
CFanBlade* CFanBlade::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CFanBlade* pFanBlade = nullptr;	// インスタンスを生成

	if (pFanBlade == nullptr)
	{ // オブジェクトが NULL の場合

		// インスタンスを生成
		pFanBlade = new CFanBlade;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pFanBlade != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pFanBlade->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pFanBlade->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 扇風機のファンのポインタを返す
	return pFanBlade;
}

//=======================================
// 目的の向きの移動量の設定処理
//=======================================
void CFanBlade::SetRotMoveDest(const float fRotMove)
{
	// 目的の向きの移動量を設定する
	m_fRotMoveDest = fRotMove;
}