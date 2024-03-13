//============================================
//
// マネージャーのメイン処理[manager.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "result.h"
#include "input.h"
#include "fade.h"
#include "Objectmesh.h"

#include "entry.h"
#include "file.h"
#include "camera.h"
#include "skybox.h"
#include "result_letter.h"
#include "objectElevation.h"
#include "player.h"
#include "confetti.h"
#include "sound.h"
#include "entry_BG.h"

//--------------------------------------------
// マクロ定義
//--------------------------------------------
#define MAX_CONFETTI_X		(10)		// 紙吹雪の最大数X
#define MAX_CONFETTI_Y		(20)		// 紙吹雪の最大数Y
#define GRAVITY_CONFETTI	(15 + 7)	// 紙吹雪の重力
#define LIFE_CONFETTI		(100)		// 紙吹雪の寿命
#define INTERVAL_CONFETTI	(120.0f)	// 紙吹雪の出現間隔

//--------------------------------------------
// 静的メンバ変数宣言
//--------------------------------------------
CPlayer* CResult::m_apPlayer[MAX_PLAY] = {};							// ネズミの情報
int CResult::m_nGameState = 0;			// ゲームの情報

//=========================================
// コンストラクタ
//=========================================
CResult::CResult() : CScene(TYPE_SCENE, PRIORITY_BG)
{

}

//=========================================
// デストラクタ
//=========================================
CResult::~CResult()
{

}

//=========================================
//初期化処理
//=========================================
HRESULT CResult::Init(void)
{
	// シーンの初期化
	CScene::Init();

	// スカイボックスの生成処理
	CSkyBox::Create();

	// 背景の生成処理
	CEntryBG::Create();

	// テキスト読み込み処理
	CElevation::TxtSet();

	// ゲームの状態を取得する
	m_nGameState = CGame::GetState();

	// 3Dテキスト生成
	if (m_nGameState == CGame::STATE_CAT_WIN)
	{ // ネコが勝ったら

		CResultLetter::Create(D3DXVECTOR3(0.0f, 370.0f, 0.0f), CXFile::TYPE_WINCAT_TEXT);		// ねこのかち
	}
	else if (m_nGameState == CGame::STATE_RAT_WIN)
	{ // ネズミが勝ったら

		CResultLetter::Create(D3DXVECTOR3(0.0f, 370.0f, 0.0f), CXFile::TYPE_WINRAT_TEXT);		// ねずみのかち
	}

	// 勝利音を流す
	CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_VICTORY);
	
	int nCatIdx = CEntry::GetCatIdx();// ネコのインデックスを取得する
	int nRatCount = 0;		// ネズミのカウント

	// ネズミの生成
	for (int nCntRat = 0; nCntRat < MAX_PLAY; nCntRat++)
	{
		if (nCntRat == nCatIdx)
		{ // ネコのインデックスの場合

			if (m_nGameState == CGame::STATE_CAT_WIN)
			{ // ネコが勝った場合

				// ネコの生成
				m_apPlayer[nCntRat] = CPlayer::Create(D3DXVECTOR3(-300.0f, 0.0f, -200.0f), nCntRat, CPlayer::TYPE_CAT);
			}
			else
			{ // 上記以外

				// ネコの生成
				m_apPlayer[nCntRat] = CPlayer::Create(D3DXVECTOR3(-300.0f, 0.0f, -100.0f), nCntRat, CPlayer::TYPE_CAT);
			}
		}
		else
		{ // 上記以外

			if (m_nGameState == CGame::STATE_RAT_WIN)
			{ // ネズミが勝った場合

				// ネズミの生成
				m_apPlayer[nCntRat] = CPlayer::Create(D3DXVECTOR3(150.0f * nRatCount + 100.0f, 0.0f, -280.0f), nCntRat, CPlayer::TYPE_RAT);
			}
			else
			{ // 上記以外

				// ネズミの生成
				m_apPlayer[nCntRat] = CPlayer::Create(D3DXVECTOR3(150.0f * nRatCount + 100.0f, 0.0f, -100.0f), nCntRat, CPlayer::TYPE_RAT);
			}

			// ネズミのカウントを加算する
			nRatCount++;
		}
	}

	// 紙吹雪の生成
	CreateConfetti();

	// 成功を返す
	return S_OK;
}

//=============================================
//終了処理
//=============================================
void CResult::Uninit(void)
{
	// 破棄処理
	Release();
}

//======================================
//更新処理
//======================================
void CResult::Update(void)
{

#ifdef _DEBUG	// 紙吹雪テスト用

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_M) == true)
	{ // Mキーを押したとき

		// 紙吹雪の生成
		CreateConfetti();
	}

#endif

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A,0) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_START, 0) == true)
	{ // ENTERキーを押した場合

		// ランキングに遷移する
		CManager::Get()->GetFade()->SetFade(CScene::MODE_TITLE);

		// この先の処理を行わない
		return;
	}

	if (CManager::Get()->GetRenderer() != nullptr)
	{ // レンダラーが NULL じゃない場合

		// 更新処理
		CManager::Get()->GetRenderer()->Update();
	}
}

//======================================
//描画処理
//======================================
void CResult::Draw(void)
{

}

//======================================
//ゲームの情報取得処理
//======================================
int CResult::GetState(void)
{
	return m_nGameState;
}

//======================================
//紙吹雪の生成処理
//======================================
void CResult::CreateConfetti(void)
{
	// ローカル変数
	D3DXCOLOR color;		// 色
	D3DXVECTOR3 rotMove;	// 向き
	D3DXVECTOR3 size;		// サイズ
	float fGravity;			// 重力
	float fPosX = 0.0f;			// 初期値X

	// 位置の設定
	switch (m_nGameState)
	{
	case CGame::STATE_CAT_WIN:		// ねこのかち

		fPosX = 0.0f;

		break;

	case CGame::STATE_RAT_WIN:		// ねずみのかち

		fPosX = 1000.0f;

		break;

	default:

		assert(false);

		break;
	}

	for (int nCntConfettiX = 0; nCntConfettiX < MAX_CONFETTI_X; nCntConfettiX++)
	{ // X軸
		for (int nCntConfettiY = 0; nCntConfettiY < MAX_CONFETTI_Y; nCntConfettiY++)
		{ // Y軸

			// 向き
			rotMove.x = rand() % 10 * 0.01f;
			rotMove.y = rand() % 10 * 0.01f;
			rotMove.z = rand() % 10 * 0.01f;

			// 色
			color.r = rand() % 10 * 0.1f;
			color.g = rand() % 10 * 0.1f;
			color.b = rand() % 10 * 0.1f;

			// サイズ
			size.x = float(rand() % 17 + 10);
			size.y = float(rand() % 17 + 10);
			size.z = float(rand() % 17 + 10);

			// 重力
			fGravity = float(rand() % GRAVITY_CONFETTI);

			// 紙吹雪生成
			CConfetti::Create(D3DXVECTOR3(fPosX + (nCntConfettiX * -INTERVAL_CONFETTI),
				300.0f + (nCntConfettiY * INTERVAL_CONFETTI),
				-230.0f),
				D3DXVECTOR3(size.x, size.y, size.z),		// サイズ
				D3DXVECTOR3(rotMove.x, rotMove.y, rotMove.z),	// 向き
				fGravity,							// 重力
				D3DXCOLOR(color.r, color.g, color.b, 1.0f),	// 色
				LIFE_CONFETTI + (LIFE_CONFETTI * nCntConfettiY));								// 寿命
		}
	}
}