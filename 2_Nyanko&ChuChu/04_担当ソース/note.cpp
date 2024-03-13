//===========================================
//
// 音符メイン処理[note.cpp]
// Author 坂本翔唯
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "note.h"
#include "useful.h"
#include "speaker.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define NOTE_CYCLE_SPEED	(0.05f)			// 回る速度
#define NOTE_UD_HEIGHT		(100.0f)		// 上下移動の幅

//==============================
// コンストラクタ
//==============================
CNote::CNote() : CModel(CObject::TYPE_NONE, CObject::PRIORITY_BLOCK)
{
	m_move = NONE_D3DXVECTOR3;
	m_nLife = 10;
	m_nRandHeight = 0;
	m_StartPosY = 0.0f;		// 初期位置の高さ
	m_nIndex = -1;			// 使用番号
	m_Main = nullptr;		// 自分の事を使用しているオブジェクト
}

//==============================
// デストラクタ
//==============================
CNote::~CNote()
{

}

//==============================
// 破片の初期化処理
//==============================
HRESULT CNote::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // 初期化処理に失敗した場合

	  // 失敗を返す
		return E_FAIL;
	}

	m_move = NONE_D3DXVECTOR3;
	m_nLife = 10;
	m_nRandHeight = 0;
	m_StartPosY = 0.0f;		// 初期位置の高さ
	m_nIndex = -1;			// 使用番号
	m_Main = nullptr;		// 自分の事を使用しているオブジェクト

	// 値を返す
	return S_OK;
}

//========================================
// 破片の終了処理
//========================================
void CNote::Uninit(void)
{
	//本体にある自身のポインタ削除処理
	m_Main->NULLNote(m_nIndex);
	m_Main->MySetIdx(m_nIndex);

	// 終了処理
	CModel::Uninit();
}

//=====================================
// 破片の更新処理
//=====================================
void CNote::Update(void)
{
	// 位置と向きをを取得する
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	// 位置を加算する
	m_nLife--;
	rot.y += NOTE_CYCLE_SPEED;
	pos.y = m_StartPosY + sinf(m_nLife * 0.1f) * NOTE_UD_HEIGHT;

	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}

	// 位置更新
	pos += m_move;

	// 位置と向きを設定する
	SetPos(pos);
	SetRot(rot);
}

//=====================================
// 破片の描画処理
//=====================================
void CNote::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CNote::SetData(const D3DXVECTOR3& pos)
{
	// 情報の設定処理
	SetPos(pos);								// 位置
	SetPosOld(pos);								// 前回の位置
	SetRot(NONE_D3DXVECTOR3);					// 向き
	SetScale(NONE_SCALE);						// 拡大率

	m_nRandHeight = rand() % 3;
	switch (m_nRandHeight)
	{
	case 0:
		SetFileData(CXFile::TYPE_RED_NOTE4);			// モデル情報
		break;
	case 1:
		SetFileData(CXFile::TYPE_RED_NOTE8);			// モデル情報
		break;
	case 2:
		SetFileData(CXFile::TYPE_RED_NOTE16);			// モデル情報
		break;
	}
	m_StartPosY = pos.y;
}

//=======================================
// 生成処理
//=======================================
CNote* CNote::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CNote* pTarai = nullptr;	// インスタンスを生成

	if (pTarai == nullptr)
	{ // オブジェクトが NULL の場合

	  // インスタンスを生成
		pTarai = new CNote;
	}
	else
	{ // オブジェクトが NULL じゃない場合

	  // 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pTarai != nullptr)
	{ // オブジェクトが NULL じゃない場合

	  // 初期化処理
		if (FAILED(pTarai->Init()))
		{ // 初期化に失敗した場合

		  // 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pTarai->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

	  // 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// たらいのギアのポインタを返す
	return pTarai;
}