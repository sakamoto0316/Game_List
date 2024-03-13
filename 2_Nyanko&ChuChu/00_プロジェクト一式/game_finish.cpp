//============================================
//
// ゲームフィニッシュ処理[game_finish.cpp]
// Author：堀川萩大
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "game.h"
#include "game_finish.h"
#include "object2D.h"
#include "texture.h"
#include "useful.h"
#include "game_timer.h"
#include "countdown.h"
#include "sound.h"

//--------------------------------------------
// マクロ定義
//--------------------------------------------
#define FINISH_TEXTURE		"data\\TEXTURE\\FinishLogo.png"						// 「FINISH」のテクスチャ
#define FINISH_SIZE			(D3DXVECTOR3(300.0f, 100.0f, 0.0f))					// 「FINISH」のサイズ
#define INIT_FINISH_POS		(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 360.0f, 0.0f))	// 「FINISH」の初期位置
#define NORMAL_SIZE			(1.0f)								// 通常サイズ
#define VISIBLE_COLOR		(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// 通常カラー
#define FINISH_COUNT		(60)								// フィニッシュカウント

//--------------------------------------------
// 静的メンバ変数
//--------------------------------------------
CGameTime* CGameFinish::m_pGameTime = nullptr;		// ゲームタイムの情報
CCountdown* CGameFinish::m_pCountdown = nullptr;	// カウントダウンの情報

//============================
// コンストラクタ
//============================
CGameFinish::CGameFinish() : CObject(CObject::TYPE_FINISHUI, PRIORITY_UI)
{
	// 全ての値をクリアする
	m_pFinish = nullptr;		// フィニッシュの情報
	m_pGameTime = nullptr;		// ゲームタイムの情報
	m_pCountdown = nullptr;		// カウントダウンの情報
	m_fSize = NORMAL_SIZE;		// サイズ
	m_bFinish = false;			// 終了したか
	m_bSe = false;				// SE再生状況
}

//============================
// デストラクタ
//============================
CGameFinish::~CGameFinish()
{

}

//============================
// 初期化処理
//============================
HRESULT CGameFinish::Init(void)
{
	// 全ての値を初期化する
	m_fSize = NORMAL_SIZE * 4.0f;
	m_pFinish = nullptr;
	m_bFinish = false;
	m_bSe = false;				// SE再生状況

	if (m_pFinish == nullptr)
	{ // フィニッシュの情報が NULL の場合

		// フィニッシュを生成する
		m_pFinish = CObject2D::Create(CObject2D::TYPE_NONE, CObject::TYPE_NONE, PRIORITY_PAUSE);

		if (m_pFinish != nullptr)
		{ // 情報が入っている場合

			if (FAILED(m_pFinish->Init()))
			{ // 初期化に失敗した場合

				// 停止
				assert(false);

				// 失敗を返す
				return E_FAIL;
			}
		}
	}
	else
	{ // 上記以外

		// 停止
		assert(false);

		// 失敗を返す
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//============================
// 終了処理
//============================
void CGameFinish::Uninit(void)
{
	// 全ての値をクリアする
	m_pGameTime = nullptr;
	m_pCountdown = nullptr;

	if (m_pFinish != nullptr)
	{ // 終了のポリゴンが NULL じゃない場合

		// 終了のポリゴンの終了処理
		m_pFinish->Uninit();
		m_pFinish = nullptr;
	}

	// 本体の終了処理
	Release();
}

//============================
// 更新処理
//============================
void CGameFinish::Update(void)
{
	//終了カウント処理
	{
		m_pGameTime = CGameTime::Get();
		if (m_pGameTime != nullptr)
		{
			if (m_pCountdown == nullptr && m_pGameTime->GetSeconds() == 5)
			{// 残り５秒＆カウントダウンポインターがnullの時
				m_pCountdown = CCountdown::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(50.0f, 80.0f, 0.0f), FINISH_COUNT, true);
				CGame::SetCountDown(true);
			}
			if (m_pGameTime->GetSeconds() == 0)
			{// カウントダウンが0になった時
				if (CGame::GetState() != CGame::STATE_CAT_WIN)
				{// 猫が勝っている状態じゃない時
					m_bFinish = true;
				}
			}
			if (m_bFinish == true)
			{// 終了状態になった時

				if (m_bSe == false)
				{ // SEが再生されてないとき

					// ピッピー！再生
					CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_FINISH);

					m_bSe = true;
				}

				m_fSize -= 0.2f;
				if (m_fSize < 1.0f)
				{
					m_fSize = 1.0f;
				}

				//設定処理
				SetData();
			}
		}
	}
}

//============================
// 描画処理
//============================
void CGameFinish::Draw(void)
{
	if (m_bFinish == false)
	{// 終了してない場合
		return;
	}
	else
	{
		m_pFinish->Draw();

	}
}

//============================
// 情報の設定処理
//============================
void CGameFinish::SetData(void)
{
	if (m_pFinish != nullptr)
	{	//NULLじゃない場合

		// 情報を設定する
		m_pFinish->SetPos(INIT_FINISH_POS);			// 位置
		m_pFinish->SetSize(FINISH_SIZE * m_fSize);	// サイズ

		// テクスチャの割り当て処理
		m_pFinish->BindTexture(CManager::Get()->GetTexture()->Regist(FINISH_TEXTURE));

		m_pFinish->SetRot(NONE_D3DXVECTOR3);	// 向き
		m_pFinish->SetAngle();					// 方向
		m_pFinish->SetLength();					// 長さ
		
		// 頂点座標の設定処理
		m_pFinish->SetVertex();

		// 頂点カラーの設定処理
		m_pFinish->SetVtxColor(VISIBLE_COLOR);
	}
	else
	{ // 上記以外

		//　停止
		assert(false);
	}
}

//============================
//生成処理
//============================
CGameFinish* CGameFinish::Create(void)
{
	// ゲームフィニッシュのポインタを生成
	CGameFinish* pFinish = nullptr;

	if (pFinish == nullptr)
	{ // オブジェクトが NULL の場合

	  // オブジェクトを生成
		pFinish = new CGameFinish;
	}
	else
	{ // オブジェクトが NULL じゃない場合

	  // 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pFinish != nullptr)
	{ // オブジェクトが NULL じゃない場合

	  // 初期化処理
		if (FAILED(pFinish->Init()))
		{ // 初期化に失敗した場合

		  // 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pFinish->SetData();
	}
	else
	{ // オブジェクトが NULL の場合

	  // 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// ゲームフィニッシュのポインタを返す
	return pFinish;
}

//============================
//終了の設定処理
//============================
void CGameFinish::SetFinish(bool bFinish)
{
	m_bFinish = bFinish;
}