//=======================================
//
// エントリーの背景処理[entry_BG.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "renderer.h"
#include "entry_BG.h"

#include "model.h"

//---------------------------------------
// 無名名前空間
//---------------------------------------
namespace
{
	const D3DXVECTOR3 BG_POS[CEntryBG::TYPE_MAX] =		// 背景の位置
	{
		D3DXVECTOR3(0.0f, 0.0f, 2650.0f),
		D3DXVECTOR3(900.0f, -200.0f, 200.0f),
		D3DXVECTOR3(700.0f, 0.0f, -150.0f),
		D3DXVECTOR3(0.0f, 0.0f, 1100.0f),
		D3DXVECTOR3(0.0f, 0.0f, 1200.0f),
		D3DXVECTOR3(0.0f, -30.0f, -250.0f),
		D3DXVECTOR3(-900.0f, -30.0f, 450.0f),
		D3DXVECTOR3(700.0f, 270.0f,0.0f),
		D3DXVECTOR3(700.0f, 20.0f,0.0f),
		D3DXVECTOR3(700.0f, 140.0f,0.0f),
	};

	const D3DXVECTOR3 BG_ROT[CEntryBG::TYPE_MAX] =		// 背景の位置
	{
		NONE_D3DXVECTOR3,
		NONE_D3DXVECTOR3,
		NONE_D3DXVECTOR3,
		NONE_D3DXVECTOR3,
		NONE_D3DXVECTOR3,
		NONE_D3DXVECTOR3,
		NONE_D3DXVECTOR3,
		D3DXVECTOR3(D3DX_PI * 0.0f,-1.0f,0.0f),
		D3DXVECTOR3(D3DX_PI * 0.0f,-1.0f,0.0f),
		D3DXVECTOR3(D3DX_PI * 0.0f,-1.0f,0.0f),
	};
}

//=========================
// コンストラクタ
//=========================
CEntryBG::CEntryBG() : CObject(CObject::TYPE_ENTRYBG, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_apModel[nCnt] = nullptr;			// モデルの情報
	}
}

//=========================
// デストラクタ
//=========================
CEntryBG::~CEntryBG()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CEntryBG::Init(void)
{
	// 全ての値を初期化する
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apModel[nCnt] == nullptr)
		{ // モデルの情報が NULL の場合

			// モデルを生成する
			m_apModel[nCnt] = CModel::Create(TYPE_NONE, PRIORITY_BLOCK);
		}
	}

	// 成功を返す
	return S_OK;
}

//=========================
// 終了処理
//=========================
void CEntryBG::Uninit(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{ // モデルの情報が NULL じゃない場合

			// モデルの終了処理
			m_apModel[nCnt]->Uninit();
			m_apModel[nCnt] = nullptr;
		}
	}

	// 本体の終了処理
	Release();
}

//=========================
// 更新処理
//=========================
void CEntryBG::Update(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{ // モデルの情報が NULL じゃない場合

			// モデルの更新処理
			m_apModel[nCnt]->Update();
		}
	}
}

//=========================
// 描画処理
//=========================
void CEntryBG::Draw(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{ // モデルの情報が NULL じゃない場合

			// モデルの描画処理
			m_apModel[nCnt]->Draw();
		}
	}
}

//=========================
// 情報の設定処理
//=========================
void CEntryBG::SetData(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{ // モデルの情報が NULL の場合

			// 情報を設定する
			m_apModel[nCnt]->SetPos(BG_POS[nCnt]);								// 位置
			m_apModel[nCnt]->SetPosOld(BG_POS[nCnt]);							// 前回の位置
			m_apModel[nCnt]->SetRot(BG_ROT[nCnt]);							// 向き
			m_apModel[nCnt]->SetScale(NONE_SCALE);								// 拡大率
			m_apModel[nCnt]->SetFileData((CXFile::TYPE)(INIT_ENTRANCE + nCnt));	// モデルの情報
		}
		
	}
}

//=========================
// 生成処理
//=========================
CEntryBG* CEntryBG::Create(void)
{
	// ローカルオブジェクトを生成
	CEntryBG* pEntry = nullptr;		// エントリーの背景のインスタンスを生成

	if (pEntry == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pEntry = new CEntryBG;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pEntry != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pEntry->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pEntry->SetData();
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// エントリーの背景のポインタを返す
	return pEntry;
}