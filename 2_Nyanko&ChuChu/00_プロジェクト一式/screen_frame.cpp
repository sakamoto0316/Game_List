//============================================
//
// 画面の枠処理[screen_frame.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "screen_frame.h"
#include "object2D.h"
#include "texture.h"

//--------------------------------------------
// 無名名前空間
//--------------------------------------------
namespace
{
	const D3DXVECTOR3 FRAME_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);		// 位置
	const D3DXVECTOR3 FRAME_SIZE[CScreenFrame::TYPE_MAX] =			// サイズ
	{
		D3DXVECTOR3(5.0f, SCREEN_HEIGHT * 0.5f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 5.0f, 0.0f),
	};
}

//============================
// コンストラクタ
//============================
CScreenFrame::CScreenFrame() : CObject(TYPE_SCREENFRAME, PRIORITY_UI)
{
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_apFrame[nCnt] = nullptr;		// 枠
	}
}

//============================
// デストラクタ
//============================
CScreenFrame::~CScreenFrame()
{

}

//============================
// 初期化処理
//============================
HRESULT CScreenFrame::Init(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_apFrame[nCnt] = nullptr;		// 枠
	}

	// 成功を返す
	return S_OK;
}

//============================
// 終了処理
//============================
void CScreenFrame::Uninit(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if(m_apFrame[nCnt] != nullptr)
		{ // 枠が NULL じゃない場合

			// 枠の終了処理
			m_apFrame[nCnt]->Uninit();
			m_apFrame[nCnt] = nullptr;
		}
	}

	// 本体の終了処理
	Release();
}

//============================
// 更新処理
//============================
void CScreenFrame::Update(void)
{

}

//============================
// 描画処理
//============================
void CScreenFrame::Draw(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apFrame[nCnt] != nullptr)
		{ // 枠が NULL じゃない場合

			// 枠の描画処理
			m_apFrame[nCnt]->Draw();
		}
	}
}

//============================
// 情報の設定処理
//============================
void CScreenFrame::SetData(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apFrame[nCnt] == nullptr)
		{ // 枠が NULL の場合

			// 枠を生成する
			m_apFrame[nCnt] = CObject2D::Create(CObject2D::TYPE_NONE, TYPE_NONE, PRIORITY_UI);

			// スクロールの設定処理
			m_apFrame[nCnt]->SetPos(FRAME_POS);				// 位置設定
			m_apFrame[nCnt]->SetRot(NONE_D3DXVECTOR3);		// 向き設定
			m_apFrame[nCnt]->SetSize(FRAME_SIZE[nCnt]);		// サイズ設定
			m_apFrame[nCnt]->SetLength();					// 長さ設定
			m_apFrame[nCnt]->SetAngle();					// 方向設定

			// 頂点情報の初期化
			m_apFrame[nCnt]->SetVertex();

			// 頂点カラーの設定処理
			m_apFrame[nCnt]->SetVtxColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
		}
	}
}

//============================
//生成処理
//============================
CScreenFrame* CScreenFrame::Create(void)
{
	// ローカルオブジェクトを生成
	CScreenFrame* pScreen = nullptr;	// 画面の枠のインスタンスを生成

	if (pScreen == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pScreen = new CScreenFrame;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pScreen != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pScreen->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pScreen->SetData();
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 画面の枠のポインタを返す
	return pScreen;
}