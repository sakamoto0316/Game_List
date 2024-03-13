//============================================
//
// ゲームのメイン処理[game.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "input.h"
#include "game.h"
#include "fade.h"
#include "file.h"
#include "renderer.h"
#include "log.h"

#include "pause.h"
#include "debugproc.h"
#include "sound.h"

#include "objectElevation.h"
#include "map.h"
#include "skybox.h"
#include "rat.h"
#include "Cat.h"
#include "game_timer.h"
#include "edit.h"
#include "weapon_selectUI.h"
#include "block.h"
#include "countdown.h"
#include "item.h"
#include "resurrection_fan.h"
#include "player.h"
#include "entry.h"
#include "game_finish.h"

#include "obstacle_manager.h"
#include "chara_infoUI.h"
#include "screen_frame.h"

//--------------------------------------------
// 無名名前空間
//--------------------------------------------
namespace
{
	const int MAX_ITEM_POS = 3;					// アイテム出現位置の最大数

	// プレイヤーUIの位置
	const D3DXVECTOR3 PLAYERUI_POS[MAX_PLAY] =
	{
		D3DXVECTOR3(90.0f, SCREEN_HEIGHT * 0.5f - 80.0f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH - 90.0f, SCREEN_HEIGHT * 0.5f - 80.0f, 0.0f),
		D3DXVECTOR3(90.0f, SCREEN_HEIGHT - 80.0f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH - 90.0f, SCREEN_HEIGHT - 80.0f, 0.0f),
	};

	// アイテムの出現位置
	const D3DXVECTOR3 ITEM_SPAWN_POS[MAX_ITEM_POS] =
	{
		D3DXVECTOR3(-1100.0f, 0.0f, 100.0f),
		D3DXVECTOR3(1000.0f, 0.0f, 450.0f),
		D3DXVECTOR3(1250.0f, 0.0f, -800.0f),
	};

	// 読み込むファイルの番号(ブロック)
	const CFile::TYPE FILETYPE_BLOCK[MAP_TYPE] =
	{
		CFile::TYPE_MAP_BLOCK1,
		CFile::TYPE_MAP_BLOCK2,
		CFile::TYPE_MAP_BLOCK3,
	};

	// 読み込むファイルの番号(障害物)
	const CFile::TYPE FILETYPE_OBSTACLE[MAP_TYPE] =
	{
		CFile::TYPE_MAP_OBSTACLE1,
		CFile::TYPE_MAP_OBSTACLE2,
		CFile::TYPE_MAP_OBSTACLE3,
	};

	// ネコの初期位置
	const D3DXVECTOR3 FILETYPE_CATPOS[MAP_TYPE] =
	{
		D3DXVECTOR3(1200.0f, 0.0f, 700.0f),
		D3DXVECTOR3(-1200.0f,0.0f,850.0f),
		D3DXVECTOR3(-200.0f,0.0f,-600.0f),
	};

	// ネズミの初期位置
	const D3DXVECTOR3 FILETYPE_RATPOS[MAP_TYPE] =
	{
		D3DXVECTOR3(-500.0f, 0.0f, -300.0f),
		D3DXVECTOR3(1000.0f,0.0f,-650.0f),
		D3DXVECTOR3(1450.0f,0.0f,200.0f),
	};

	const int TRANS_COUNT = 80;				// 遷移カウント
	const int START_COUNT = 30;				// 開始のカウント
	const int MAX_ITEM = 3;					// アイテムの最大数
	const int ATEMSPAWN_CONT = (60 - 25) / MAX_ITEM * 60;	// アイテム出現カウント
}

//--------------------------------------------
// 静的メンバ変数宣言
//--------------------------------------------
CPause* CGame::m_pPause = nullptr;							// ポーズの情報
CPlayer* CGame::m_apPlayer[MAX_PLAY] = {};					// プレイヤーの情報
CGame::STATE CGame::m_GameState = CGame::STATE_START;		// ゲームの進行状態
int CGame::m_nFinishCount = 0;								// 終了カウント
int CGame::m_nItemSpawnCount = 0;							// アイテム出現カウンター
int CGame::m_nNumItem = 0;									// アイテムの数
CGameFinish* CGame::m_pFinish = nullptr;					// フィニッシュの情報
bool CGame::m_bCountDown = false;							// カウントダウンが使用されているか
bool CGame::m_bItemSpawn = false;							// アイテムが出現しているかどうか
int CGame::m_nMapNumber = 0;								// アイテムが出現しているかどうか

// デバッグ版
#ifdef _DEBUG
CEdit* CGame::m_pEdit = nullptr;							// エディットの情報
bool CGame::m_bEdit = false;								// エディット状況
#endif

//=========================================
// コンストラクタ
//=========================================
CGame::CGame() : CScene(TYPE_SCENE, PRIORITY_BG)
{
	// 全ての値をクリアする
	m_pPause = nullptr;			// ポーズ
	m_pFinish = nullptr;		// フィニッシュ
	m_nFinishCount = 0;			// 終了カウント
	m_nItemSpawnCount = 0;		// アイテム出現カウント
	m_nNumItem = 0;				// アイテムの数
	m_GameState = STATE_START;	// 状態
	m_bCountDown = false;
	m_bItemSpawn = false;		// アイテムが出現しているかどうか
	m_nMapNumber = 0;

	for (int nCntPlay = 0; nCntPlay < MAX_PLAY; nCntPlay++)
	{
		m_apPlayer[nCntPlay] = nullptr;		// ネズミの情報
	}

// デバッグ版
#ifdef _DEBUG
	m_pEdit = nullptr;			// エディット
	m_bEdit = false;			// エディット状況
#endif
}

//=========================================
// デストラクタ
//=========================================
CGame::~CGame()
{

}

//=========================================
//初期化処理
//=========================================
HRESULT CGame::Init(void)
{
	// シーンの初期化
	CScene::Init();

	// 画面の枠の生成
	CScreenFrame::Create();

	// テキスト読み込み処理
	CElevation::TxtSet();

	// メッシュの読み込み処理
	//CMesh::TxtSet();

	// マップの番号をランダムで算出
	m_nMapNumber = rand() % MAP_TYPE;

	// マップの情報をロードする
	CManager::Get()->GetFile()->FalseSuccess();

	//CObstacle::Create(D3DXVECTOR3(300.0f, 0.0f, -300.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_TV);
	//CObstacle::Create(D3DXVECTOR3(-800.0f, 0.0f, 200.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_CUP);
	//CObstacle::Create(D3DXVECTOR3(-800.0f, 0.0f, 400.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_CUP);
	//CObstacle::Create(D3DXVECTOR3(-800.0f, 0.0f, 600.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_CUP);
	//CObstacle::Create(D3DXVECTOR3(200.0f, 0.0f, 200.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_PIN);
	//CObstacle::Create(D3DXVECTOR3(200.0f, 0.0f, 300.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_PIN);
	//CObstacle::Create(D3DXVECTOR3(200.0f, 0.0f, 400.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_PIN);
	//CObstacle::Create(D3DXVECTOR3(200.0f, 0.0f, 500.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_PIN);

	CManager::Get()->GetFile()->Load(FILETYPE_OBSTACLE[m_nMapNumber]);
	CManager::Get()->GetFile()->Load(FILETYPE_BLOCK[m_nMapNumber]);
	//CManager::Get()->GetFile()->Load(CFile::TYPE_MAP_BLOCKSAMPLE);
	//CManager::Get()->GetFile()->Load(CFile::TYPE_MAP_OBSTACLESAMPLE);

	// マップの設定処理
	CManager::Get()->GetFile()->SetMap();

	// カウントダウンの生成処理
	CCountdown::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(200.0f, 250.0f, 0.0f), START_COUNT, false);

	// メッシュのテキスト読み込み
	//CMesh::TxtSet();

	// スカイボックスの生成処理
	CSkyBox::Create();

	//マップの生成
	CMap::Create();

#ifdef _DEBUG	//障害物テスト用

	//CObstacle *pObstacle = NULL;

	//// ルンバの生成処理
	//CObstacle::Create(D3DXVECTOR3(-280.0f, 200.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CObstacle::TYPE::TYPE_GARBAGECAN);
	//CObstacle::Create(D3DXVECTOR3(600.0f, 0.0f, 400.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_ROOMBA);

	//// ひもの生成処理
	//CObstacle::Create(D3DXVECTOR3(-600.0f, 650.0f, 0.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_HIMO);

	//// スピーカーの生成処理
	//CObstacle::Create(D3DXVECTOR3(900.0f, 0.0f, 900.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.25f, 0.0f), CObstacle::TYPE::TYPE_SPEAKER);

	//pObstacle = CObstacle::Create(D3DXVECTOR3(1000.0f, 0.0f, 900.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_SPEAKER);
	//pObstacle->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f));

	//// リードの生成処理
	//pObstacle = CObstacle::Create(D3DXVECTOR3(400.0f, 0.0f, -600.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_LEASH);
	//pObstacle->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));

	//// 画鋲の生成処理
	//CObstacle::Create(D3DXVECTOR3(-200.0f, 200.0f, -120.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_PIN);

	//// 扇風機の生成処理
	//CObstacle::Create(D3DXVECTOR3(0.0f, 200.0f, 900.0f), NONE_D3DXVECTOR3, CObstacle::TYPE::TYPE_FAN);

	//// コップの生成処理
	//CObstacle::Create(D3DXVECTOR3(-200.0f, 200.0f, 100.0f), NONE_D3DXVECTOR3, CObstacle::TYPE::TYPE_CUP);
	//pObstacle = CObstacle::Create(D3DXVECTOR3(400.0f, 200.0f, 100.0f), D3DXVECTOR3(0.0f, D3DX_PI * 1.0f, 0.0f), CObstacle::TYPE::TYPE_CUP);
	//pObstacle->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 1.0f, 0.0f));

	////ゴミ箱の生成
	//CObstacle::Create(D3DXVECTOR3(-100.0f, 200.0f, -500.0f), NONE_D3DXVECTOR3, CObstacle::TYPE::TYPE_GARBAGECAN);

	//CObstacle::Create(D3DXVECTOR3(-400.0f, 0.0f, 400.0f), NONE_D3DXVECTOR3, CObstacle::TYPE::TYPE_PETBOTTLE);
	//
	//CObstacle::Create(D3DXVECTOR3(-400.0f, 0.0f, 400.0f), NONE_D3DXVECTOR3, CObstacle::TYPE::TYPE_TOYCAR);

	//CObstacle::Create(D3DXVECTOR3(-200.0f, 0.0f, 100.0f), NONE_D3DXVECTOR3, CObstacle::TYPE::TYPE_REDKATEN);

	//// ひもの生成処理
	//CObstacle::Create(D3DXVECTOR3(-600.0f, 650.0f, 0.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_HIMO);

#endif // _DEBUG

	{ // キャラの生成処理

		// ネコのインデックスを取得する
		int nCat = CEntry::GetCatIdx();

		// ネズミの生成
		for (int nCntPlay = 0; nCntPlay < MAX_PLAY; nCntPlay++)
		{
			if (nCntPlay == nCat)
			{ // ネコ担当のプレイヤーの場合

				// プレイヤーの生成
				m_apPlayer[nCntPlay] = CPlayer::Create(FILETYPE_CATPOS[m_nMapNumber], nCntPlay, CPlayer::TYPE_CAT);
			}
			else
			{ // 上記以外

				// プレイヤーの生成
				m_apPlayer[nCntPlay] = CPlayer::Create(D3DXVECTOR3(FILETYPE_RATPOS[m_nMapNumber].x, FILETYPE_RATPOS[m_nMapNumber].y, 100.0f * nCntPlay + FILETYPE_RATPOS[m_nMapNumber].z), nCntPlay, CPlayer::TYPE_RAT);
			}
		}
	}

	// 生成処理
	CGameTime::Create();
	m_pFinish = CGameFinish::Create();

	// キャラクターUIの生成処理
	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		CCharaInfoUI::Create(PLAYERUI_POS[nCnt], nCnt, m_apPlayer[nCnt]->GetType());
	}

	//// 武器選択UIを生成
	//CWeaponSelectUI::Create();

	// 情報の初期化
	m_nFinishCount = 0;				// 終了カウント
	m_GameState = STATE_START;		// 状態

	// 成功を返す
	return S_OK;
}

//=============================================
//終了処理
//=============================================
void CGame::Uninit(void)
{
	// ポインタを NULL にする
	m_pPause = nullptr;			// ポーズ
	m_pFinish = nullptr;		// フィニッシュ

	for (int nCntPlay = 0; nCntPlay < MAX_PLAY; nCntPlay++)
	{
		m_apPlayer[nCntPlay] = nullptr;		// ネズミの情報
	}

	// 終了カウントを初期化する
	m_nFinishCount = 0;

	// 再生中のサウンドの停止
	CManager::Get()->GetSound()->Stop();

	// 終了処理
	CScene::Uninit();
}

//======================================
//更新処理
//======================================
void CGame::Update(void)
{

// デバッグ版
#ifdef _DEBUG
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_F7) == true)
	{ // F7キーを押した場合

		// エディット状況を入れ替える
		m_bEdit = m_bEdit ? false : true;

		if (m_bEdit == true)
		{ // エディット状況が true の場合

			if (m_pEdit == nullptr)
			{ // エディット状況が NULL の場合

				// エディットの生成処理
				m_pEdit = CEdit::Create();
			}
		}
		else
		{ // 上記以外

			if (m_pEdit != nullptr)
			{ // エディット状況が NULL じゃない場合

				// 終了処理
				m_pEdit->Uninit();
				m_pEdit = nullptr;
			}
			else
			{ // 上記以外

				// 停止
				assert(false);
			}
		}
	}

#endif

	switch (m_GameState)
	{
	case CGame::STATE_START:

		break;

	case CGame::STATE_PLAY:

		if (m_pPause != nullptr)
		{ // ポーズが NULL じゃないとき

			if (m_pPause->GetPause() == false)
			{ // ポーズ状態じゃないとき

				// アイテム出現
				ItemSpawn();
			}
		}

		// ポーズ処理
		Pause();

		break;

	case CGame::STATE_RAT_WIN:

		// 遷移処理
		Transition();

		for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
		{
			if (m_apPlayer[nCnt] != nullptr)
			{ // プレイヤーが NULL じゃない場合

				// カメラの更新処理
				m_apPlayer[nCnt]->CameraUpdate();
			}
		}

		break;

	case CGame::STATE_CAT_WIN:

		// 遷移処理
		if (m_pFinish != nullptr)
		{
			m_pFinish->SetFinish(true);
		}
		Transition();

		for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
		{
			if (m_apPlayer[nCnt] != nullptr)
			{ // プレイヤーが NULL じゃない場合

				// カメラの更新処理
				m_apPlayer[nCnt]->CameraUpdate();
			}
		}

		break;

	default:

		// 停止
		assert(false);

		break;
	}

#ifdef _DEBUG

	if (m_bEdit == true)
	{ // エディット状況が true の場合

		if (m_pEdit != nullptr)
		{ // エディットが NULL じゃない場合

			// エディットの更新処理
			m_pEdit->Update();
		}

		for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
		{
			// 死亡判別処理
			CObject::DeathDecision(nCnt);
		}

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_F9) == true)
		{ // F9キーを押した場合

			// 情報をセーブする
			CManager::Get()->GetFile()->Save(FILETYPE_OBSTACLE[m_nMapNumber]);
			CManager::Get()->GetFile()->Save(FILETYPE_BLOCK[m_nMapNumber]);
			//CManager::Get()->GetFile()->Save(CFile::TYPE_MAP_BLOCKSAMPLE);
			//CManager::Get()->GetFile()->Save(CFile::TYPE_MAP_OBSTACLESAMPLE);
		}
	}
	else
	{ // 上記以外

		if (CManager::Get()->GetRenderer() != nullptr)
		{ // レンダラーが NULL じゃない場合

			// レンダラーの更新
			CManager::Get()->GetRenderer()->Update();
		}
	}

#else

	if (CManager::Get()->GetRenderer() != nullptr)
	{ // レンダラーが NULL じゃない場合

		// レンダラーの更新
		CManager::Get()->GetRenderer()->Update();
	}

#endif
		
	CManager::Get()->GetDebugProc()->Print("状態：%d", m_GameState);
}

//======================================
//描画処理
//======================================
void CGame::Draw(void)
{

}

//======================================
// 情報の設定処理
//======================================
void CGame::SetData(const MODE mode)
{
	// 情報の設定処理
	CScene::SetData(mode);

	if (m_pPause == nullptr)
	{ // ポーズへのポインタが NULL の場合

		// ポーズの生成処理
		m_pPause = CPause::Create();
	}

	// スタート状態にする
	m_GameState = STATE_START;

	// 情報の初期化
	m_nFinishCount = 0;				// 終了カウント
}

//======================================
// ポーズ処理
//======================================
void CGame::Pause(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_P) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_BACK, 0) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_START, 0) == true)
	{ // Pキーを押した場合

		if (CManager::Get()->GetFade()->GetFade() == CFade::FADE_NONE)
		{ // フェード無し状態かつ、終了以外の場合

			if (m_pPause->GetPause() == false)
			{ // ポーズが false だった場合

				// ポーズ状況を true にする
				m_pPause->SetPause(true);
			}
			else
			{ // ポーズが true だった場合

				// ポーズ状況を false にする
				m_pPause->SetPause(false);
			}

			// 決定音を鳴らす
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_DECIDE);
		}
	}
}

//======================================
// 遷移処理
//======================================
void CGame::Transition(void)
{
	// 終了カウントを加算する
	m_nFinishCount++;

	if (m_nFinishCount % TRANS_COUNT == 0)
	{ // 終了カウントが一定数を超えた場合

		// リザルトに遷移する
		CManager::Get()->GetFade()->SetFade(CScene::MODE_RESULT);
	}
}

//======================================
// アイテム出現処理
//======================================
void CGame::ItemSpawn(void)
{
	if (m_bItemSpawn == false)
	{ // アイテムが出現されてなかったら

		m_nItemSpawnCount++;		// アイテム出現カウント加算
	}
	else if (m_bItemSpawn == true)
	{ // アイテムが出現してたら

		m_nItemSpawnCount = 1;		// カウンター初期化

		CManager::Get()->GetDebugProc()->Print("\n-----------------------------------------------アイテム出現中-----------------------------------------------\n", m_GameState);
	}

	if ((m_nItemSpawnCount % ATEMSPAWN_CONT) == 0 && m_nNumItem < MAX_ITEM)
	{ // 一定時間経った

		int nItemPos;			// アイテムの出現位置選択

		nItemPos = rand() % MAX_ITEM_POS;		// アイテムの出現位置の設定

		// ネズミ捕りの生成
		CItem::Create(ITEM_SPAWN_POS[nItemPos], CItem::TYPE::TYPE_MOUSETRAP);

		m_nNumItem++;				// アイテムの数加算

		m_nItemSpawnCount = 0;		// カウンター初期化
		m_bItemSpawn = true;		// アイテムが出現している状態にする
	}
}


//======================================
// ポーズの取得処理
//======================================
CPause* CGame::GetPause(void)
{
	// ポーズの情報を返す
	return m_pPause;
}

//======================================
// ゲームの進行状態の設定処理
//======================================
void CGame::SetState(const STATE state)
{
	// ゲームの進行状態を設定する
	m_GameState = state;
}

//======================================
// ゲームの進行状態の取得処理
//======================================
CGame::STATE CGame::GetState(void)
{
	// ゲームの進行状態を返す
	return m_GameState;
}

//======================================
// プレイヤーの取得処理
//======================================
CPlayer* CGame::GetPlayer(const int nID)
{
	if (nID < MAX_PLAY)
	{ // インデックスが一定未満の場合

		// プレイヤーの情報を取得する
		return m_apPlayer[nID];
	}
	else
	{ // 上記以外

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}
}

//======================================
// ポーズのNULL化処理
//======================================
void CGame::DeletePause(void)
{
	// ポーズのポインタを NULL にする
	m_pPause = nullptr;
}

//======================================
// ネズミのNULL化処理
//======================================
void CGame::DeletePlayer(int nIdx)
{
	if (nIdx < MAX_PLAY)
	{ // 番号が最大数未満の場合

		// プレイヤーのポインタを NULL にする
		m_apPlayer[nIdx] = nullptr;
	}
	else
	{ // 上記以外

		// 停止
		assert(false);
	}
}

// デバッグ版
#ifdef _DEBUG
//======================================
// エディットの取得処理
//======================================
CEdit* CGame::GetEdit(void)
{
	// エディットの情報を返す
	return m_pEdit;
}

//======================================
// エディット状況の取得処理
//======================================
bool CGame::IsEdit(void)
{
	// エディット状況を返す
	return m_bEdit;
}

#endif