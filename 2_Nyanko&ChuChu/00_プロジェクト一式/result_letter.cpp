//===========================================
//
// 結果の文字の処理[result_letter.h]
// Author 佐藤根詩音
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "result_letter.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------

//-------------------------------------------
// 静的メンバ変数宣言
//-------------------------------------------

//==============================
// コンストラクタ
//==============================
CResultLetter::CResultLetter() : CModel(CObject::TYPE_3DTEXT, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
}

//==============================
// デストラクタ
//==============================
CResultLetter::~CResultLetter()
{

}

//==============================
// 破片の初期化処理
//==============================
HRESULT CResultLetter::Init(void)
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
void CResultLetter::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}

//=====================================
// 破片の更新処理
//=====================================
void CResultLetter::Update(void)
{

}

//=====================================
// 破片の描画処理
//=====================================
void CResultLetter::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CResultLetter::SetData(const D3DXVECTOR3& pos, const CXFile::TYPE& type)
{
	// 設定処理に便利なマクロ定義
	//NONE_D3DXVECTOR3					// 向きを傾けない時とかに使用する
	//NONE_SCALE						// 拡大率を変更しないときとかに使う
	// 情報の設定処理

	//==========================================================================
	// モデル
	//==========================================================================
	SetPos(pos);					// 位置
	SetPosOld(GetPos());			// 前回の位置
	SetRot(NONE_D3DXVECTOR3);		// 向き
	SetScale(NONE_SCALE);			// 拡大率
	SetFileData(type);				// モデルの情報
}

//=======================================
// 生成処理
//=======================================
CResultLetter* CResultLetter::Create(const D3DXVECTOR3& pos, const CXFile::TYPE& type)
{
	// ローカルオブジェクトを生成
	CResultLetter* pResultLetter = nullptr;	// サンプルのインスタンスを生成

	if (pResultLetter == nullptr)
	{ // オブジェクトが NULL の場合

		// インスタンスを生成
		pResultLetter = new CResultLetter;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pResultLetter != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pResultLetter->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pResultLetter->SetData(pos, type);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// サンプルのポインタを返す
	return pResultLetter;
}