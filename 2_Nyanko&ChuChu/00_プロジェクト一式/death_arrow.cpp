//===========================================
//
// 死亡矢印のメイン処理[death_arrow.cpp]
// Author 佐藤根詩音
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "death_arrow.h"
#include "objectX.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------

//-------------------------------------------
// 静的メンバ変数宣言
//-------------------------------------------

//==============================
// コンストラクタ
//==============================
CDeathArrow::CDeathArrow() : CModel(CObject::TYPE_DEATHARROW, CObject::PRIORITY_PLAYER)
{
	// 全ての値をクリアする
	m_pos = NONE_D3DXVECTOR3;		// 位置
	m_rot = NONE_D3DXVECTOR3;		// 向き
	m_nPlayerIdx = -1;
}

//==============================
// デストラクタ
//==============================
CDeathArrow::~CDeathArrow()
{

}

//==============================
// 死亡矢印の初期化処理
//==============================
HRESULT CDeathArrow::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	m_pos = NONE_D3DXVECTOR3;		// 位置
	m_rot = NONE_D3DXVECTOR3;		// 向き

	// 値を返す
	return S_OK;
}

//========================================
// 死亡矢印の終了処理
//========================================
void CDeathArrow::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}

//=====================================
// 死亡矢印の更新処理
//=====================================
void CDeathArrow::Update(void)
{

}

//=====================================
// 死亡矢印の描画処理
//=====================================
void CDeathArrow::Draw(void)
{
	if (m_nPlayerIdx == CObject::GetDrawIdx())
	{
		// 描画処理
		CModel::Draw();
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CDeathArrow::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& rot, const int nIdx)
{
	// 設定処理に便利なマクロ定義
	//NONE_D3DXVECTOR3					// 向きを傾けない時とかに使用する
	//NONE_SCALE						// 拡大率を変更しないときとかに使う

	// 情報の設定処理
	SetPos(pos);					// 位置
	SetPosOld(posOld);				// 前回の位置
	SetRot(rot);					// 向き
	SetScale(NONE_SCALE);			// 拡大率
	SetFileData(CXFile::TYPE_DEATHARROW);	// モデルの情報
	m_nPlayerIdx = nIdx;
}

//=======================================
// 生成処理
//=======================================
CDeathArrow* CDeathArrow::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& rot, const int nIdx)
{
	// ローカルオブジェクトを生成
	CDeathArrow* pDeathArrow = nullptr;	// 死亡矢印のインスタンスを生成

	if (pDeathArrow == nullptr)
	{ // オブジェクトが NULL の場合

		// インスタンスを生成
		pDeathArrow = new CDeathArrow;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pDeathArrow != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pDeathArrow->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pDeathArrow->SetData(pos, posOld, rot, nIdx);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// サンプルのポインタを返す
	return pDeathArrow;
}