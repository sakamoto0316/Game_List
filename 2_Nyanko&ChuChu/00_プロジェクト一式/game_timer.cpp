//============================================
//
// 時間処理[time.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "game_timer.h"
#include "manager.h"
#include "game.h"
#include "renderer.h"
#include "texture.h"

#include "number.h"
#include "pause.h"

//--------------------------------------------------
// 静的メンバ変数宣言
//--------------------------------------------------
CGameTime* CGameTime::m_pGameTimer = nullptr;		// ゲームタイマーの情報

//--------------------------------------------------
// マクロ定義
//--------------------------------------------------
#define TIME_COUNTDOWN		(120)	// 秒数
#define ONE_SECOND			(60)	// 1秒のフレーム数
#define TIME_POS			(D3DXVECTOR3(618.0f, SCREEN_HEIGHT * 0.5f, 0.0f))		// ゲームタイマーの位置
#define TIME_SIZE			(D3DXVECTOR3(25.0f, 40.0f, 0.0f))		// ゲームタイマーのサイズ
#define TIME_CORON_POS		(D3DXVECTOR3(618.0f, SCREEN_HEIGHT * 0.5f, 0.0f))		// ゲームタイマーのコロンの位置
#define TIME_CORON_SIZE		(D3DXVECTOR3(15.0f, 30.0f, 0.0f))		// ゲームタイマーのコロンのサイズ
#define TIME_BG_POS			(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f))		// ゲームタイマーの背景の位置
#define TIME_BG_SIZE		(D3DXVECTOR3(90.0f, 40.0f, 0.0f))		// ゲームタイマーの背景のサイズ
#define TIME_SHIFT			(23.0f)									// ゲームタイマーのずらす幅
#define TIME_CORON_SHIFT	(15.0f)									// ゲームタイマーのコロンのずらす幅
#define NUMBER_TEXTURE		"data\\TEXTURE\\Number.png"				// 数字のテクスチャ
#define CORON_TEXTURE		"data\\TEXTURE\\time_koron.png"			// コロンのテクスチャ
#define BG_TEXTURE		"data\\TEXTURE\\timebg.jpg"					// ゲームタイマーの背景のテクスチャ

//========================
// コンストラクタ
//========================
CGameTime::CGameTime() : CObject(CObject::TYPE_TIME, CObject::PRIORITY_UI)
{
	// 全ての値を初期化する
	for (int nCnt = 0; nCnt < GAME_TIME_DIGIT; nCnt++)
	{
		m_apNumber[nCnt] = nullptr;		// 数字の情報
	}
	m_pColon = nullptr;					// コロン
	m_pBG = nullptr;					// 背景
	m_nSeconds = TIME_COUNTDOWN;		// 秒数
	m_nFrame = 0;						// フレーム数
}

//========================
// デストラクタ
//========================
CGameTime::~CGameTime()
{

}

//========================
// 初期化処理
//========================
HRESULT CGameTime::Init(void)
{
	// 全ての値を初期化する
	m_nSeconds = TIME_COUNTDOWN;		// 秒数
	m_nFrame = 0;						// フレーム数

	for (int nCnt = 0; nCnt < GAME_TIME_DIGIT; nCnt++)
	{
		if (m_apNumber[nCnt] == nullptr)
		{ // 数字の情報が NULL の場合

			// 数字を生成する
			m_apNumber[nCnt] = new CNumber(CObject::TYPE_NONE, CObject::PRIORITY_UI);

			if (m_apNumber[nCnt] != nullptr)
			{ // 数字の情報が NULL じゃない場合

				if (FAILED(m_apNumber[nCnt]->Init()))
				{ // 初期化処理に失敗した場合

					// 停止
					assert(false);

					// 失敗を返す
					return E_FAIL;
				}
			}
			else
			{ // 上記以外

				// 停止
				assert(false);

				// 失敗を返す
				return E_FAIL;
			}
		}
	}

	if (m_pColon == nullptr)
	{ // コロンが NULL の場合

		// コロンを生成する
		m_pColon = CObject2D::Create(CObject2D::TYPE_NONE, TYPE_NONE, PRIORITY_UI);
	}

	if (m_pBG == nullptr)
	{ // 背景が NULL の場合

		// 背景を生成する
		m_pBG = CObject2D::Create(CObject2D::TYPE_NONE, TYPE_NONE, PRIORITY_UI);
	}


	// 成功を返す
	return S_OK;
}

//========================
// 終了処理
//========================
void CGameTime::Uninit(void)
{
	for (int nCnt = 0; nCnt < GAME_TIME_DIGIT; nCnt++)
	{
		if (m_apNumber[nCnt] != nullptr)
		{ // 数字の情報が NULL じゃない場合

			// 数字の終了処理
			m_apNumber[nCnt]->Uninit();
			m_apNumber[nCnt] = nullptr;
		}
	}

	if (m_pColon != nullptr)
	{ // コロンの情報が NULL じゃない場合

		// コロンの終了処理
		m_pColon->Uninit();
		m_pColon = nullptr;
	}

	if (m_pBG != nullptr)
	{ // 背景の情報が NULL じゃない場合

		// 背景の終了処理
		m_pBG->Uninit();
		m_pBG = nullptr;
	}

	// 本体の終了処理
	Release();

	// ゲームタイマーを NULL にする
	m_pGameTimer = nullptr;
}

//========================
// 更新処理
//========================
void CGameTime::Update(void)
{
	if ((CGame::GetPause() != nullptr &&
		CGame::GetPause()->GetPause() == false) &&
		CGame::GetState() != CGame::STATE_START)
	{ // 一定の状態以外の場合

		// 計算処理
		Calculate();
	}
}

//========================
// 描画処理
//========================
void CGameTime::Draw(void)
{
	if (CGame::GetState() != CGame::STATE_START && CGame::GetCountDown() == false)
	{ // 一定の状態以外の場合

		if (m_pBG != nullptr)
		{ // 背景の情報が NULL じゃない場合

			// 描画処理
			m_pBG->Draw();
		}

		for (int nCnt = 0; nCnt < GAME_TIME_DIGIT; nCnt++)
		{
			if (m_apNumber[nCnt] != nullptr)
			{ // 数字が NULL じゃない場合

				// 描画処理
				m_apNumber[nCnt]->Draw();
			}
		}

		if (m_pColon != nullptr)
		{ // コロンの情報が NULL じゃない場合

			// 描画処理
			m_pColon->Draw();
		}
	}
}

//========================
// 情報の設定処理
//========================
void CGameTime::SetData(void)
{
	// ローカル変数宣言
	int aTexU[GAME_TIME_DIGIT];		// 時間のテクスチャ座標

	// 全ての値を初期化する
	m_nSeconds = TIME_COUNTDOWN;		// 秒数
	m_nFrame = 0;						// フレーム数

	//値の計算
	aTexU[0] = m_nSeconds / ONE_SECOND;
	aTexU[1] = m_nSeconds % ONE_SECOND / 10;
	aTexU[2] = m_nSeconds % 10;

	for (int nCnt = 0; nCnt < GAME_TIME_DIGIT; nCnt++)
	{
		if (m_apNumber[nCnt] != nullptr)
		{ // 数字の情報が NULL じゃない場合

			if (nCnt == 0)
			{ // 0以外の場合

				// 位置を設定する
				m_apNumber[nCnt]->SetPos(D3DXVECTOR3(TIME_POS.x - TIME_SHIFT - TIME_CORON_SHIFT, TIME_POS.y, TIME_POS.z));
			}
			else if (nCnt == 1)
			{ // 1

				// 位置を設定する
				m_apNumber[nCnt]->SetPos(D3DXVECTOR3(TIME_POS.x + TIME_SHIFT + TIME_CORON_SHIFT, TIME_POS.y, TIME_POS.z));
			}
			else
			{ // 2

				// 位置を設定する
				m_apNumber[nCnt]->SetPos(D3DXVECTOR3(TIME_POS.x + (3 * TIME_SHIFT) + TIME_CORON_SHIFT, TIME_POS.y, TIME_POS.z));
			}

			// 情報を設定する
			m_apNumber[nCnt]->SetRot(NONE_D3DXVECTOR3);		// 向き
			m_apNumber[nCnt]->SetSize(TIME_SIZE);			// サイズ
			m_apNumber[nCnt]->SetAngle();					// 方向
			m_apNumber[nCnt]->SetLength();					// 長さ

			m_apNumber[nCnt]->SetType(CNumber::TYPE_TIME);	// 番号の種類
			m_apNumber[nCnt]->SetNumber(aTexU[nCnt]);		// 番号を設定する

			// テクスチャの割り当て処理
			m_apNumber[nCnt]->BindTexture(CManager::Get()->GetTexture()->Regist(NUMBER_TEXTURE));

			// 頂点情報の設定処理
			m_apNumber[nCnt]->SetVertex();

			// テクスチャの設定処理(アニメーションバージョン)
			m_apNumber[nCnt]->SetVtxTextureAnim(NUMBER_TEXTURE_PATTERN, aTexU[nCnt]);
		}
	}

	if (m_pColon != nullptr)
	{ // コロンが NULL じゃない場合

		// 情報の設定処理
		m_pColon->SetPos(TIME_CORON_POS);		// 位置
		m_pColon->SetRot(NONE_D3DXVECTOR3);		// 向き
		m_pColon->SetSize(TIME_CORON_SIZE);		// サイズ
		m_pColon->SetAngle();					// 方向
		m_pColon->SetLength();					// 長さ

		// テクスチャの割り当て処理
		m_pColon->BindTexture(CManager::Get()->GetTexture()->Regist(CORON_TEXTURE));

		// 頂点座標の設定処理
		m_pColon->SetVertex();
	}

	if (m_pBG != nullptr)
	{ // 背景が NULL じゃない場合

		// 情報の設定処理
		m_pBG->SetPos(TIME_BG_POS);				// 位置
		m_pBG->SetPosOld(TIME_BG_POS);			// 前回の位置
		m_pBG->SetRot(NONE_D3DXVECTOR3);		// 向き
		m_pBG->SetSize(TIME_BG_SIZE);			// サイズ
		m_pBG->SetAngle();						// 方向
		m_pBG->SetLength();						// 長さ

		// 頂点座標の設定処理
		m_pBG->SetVertex();
		m_pBG->BindTexture(CManager::Get()->GetTexture()->Regist(BG_TEXTURE));
		// 頂点カラーの設定処理
		m_pBG->SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

//========================
// 取得処理
//========================
CGameTime* CGameTime::Get(void)
{
	if (m_pGameTimer != nullptr)
	{ // ゲームタイマーが NULL じゃなかった場合

		// ゲームタイムを返す
		return m_pGameTimer;
	}
	else
	{ // 上記以外

		// 生成して返す
		return m_pGameTimer = CGameTime::Create();
	}
}

//========================
// 生成処理
//========================
CGameTime* CGameTime::Create(void)
{
	if (m_pGameTimer == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		m_pGameTimer = new CGameTime;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (m_pGameTimer != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(m_pGameTimer->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		m_pGameTimer->SetData();
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 時間のポインタを返す
	return m_pGameTimer;
}

//========================
// 計算処理
//========================
void CGameTime::Calculate(void)
{
	// 各桁の数字を格納
	int aTexU[GAME_TIME_DIGIT];

	// 時間の経過を加算する
	m_nFrame++;

	if ((m_nFrame % ONE_SECOND) == 0)
	{ // 1秒経ったら

		// 1秒減らす
		m_nSeconds--;

		if (m_nSeconds <= 0)
		{ // 時間が0を超えた場合

			// 時間を補正する
			m_nSeconds = 0;

			// ネズミの勝利を設定する
			CGame::SetState(CGame::STATE_RAT_WIN);
		}

		// 値の計算
		aTexU[0] = m_nSeconds / ONE_SECOND;
		aTexU[1] = m_nSeconds % ONE_SECOND / 10;
		aTexU[2] = m_nSeconds % 10;

		for (int nCnt = 0; nCnt < GAME_TIME_DIGIT; nCnt++)
		{
			// 数字の設定処理
			m_apNumber[nCnt]->SetNumber(aTexU[nCnt]);

			// テクスチャの設定処理(アニメーションバージョン)
			m_apNumber[nCnt]->SetVtxTextureAnim(NUMBER_TEXTURE_PATTERN, aTexU[nCnt]);
		}
	}
}

//========================
// 残り秒数の取得処理
//========================
int CGameTime::GetSeconds(void)
{
	return m_nSeconds;
}