//============================================
//
// チュートリアルのメイン処理[game.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "input.h"
#include "tutorial.h"
#include "fade.h"
#include "file.h"
#include "renderer.h"
#include "log.h"
#include "texture.h"

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

#include "answer.h"
#include "explanation.h"
#include "block_manager.h"

//--------------------------------------------
// 無名名前空間
//--------------------------------------------
namespace
{
	const D3DXVECTOR3 PLAYERUI_POS[MAX_PLAY] =								// プレイヤーUIの位置
	{
		D3DXVECTOR3(90.0f, SCREEN_HEIGHT * 0.5f - 80.0f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH - 90.0f, SCREEN_HEIGHT * 0.5f - 80.0f, 0.0f),
		D3DXVECTOR3(90.0f, SCREEN_HEIGHT - 80.0f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH - 90.0f, SCREEN_HEIGHT - 80.0f, 0.0f),
	};
	const int TRANS_COUNT = 80;				// 遷移カウント
}

#define SKIP_POS	(D3DXVECTOR3(1080.0f,50.0f,0.0f))					//スキップの位置
#define SKIP_SIZE	(D3DXVECTOR3(200.0f,50.0f,0.0f))					//スキップのサイズ
#define GAUGE_POS	(D3DXVECTOR3(880.0f,50.0f,0.0f))					//ゲージの位置
#define GAUGE_SIZE	(D3DXVECTOR3(0.0f,50.0f,0.0f))						//ゲージのサイズ

//--------------------------------------------
// 静的メンバ変数宣言
//--------------------------------------------
CPlayer* CTutorial::m_apPlayer[MAX_PLAY] = {};						// プレイヤーの情報
CTutorial::STATE CTutorial::m_GameState = CTutorial::STATE_START;	// チュートリアルの進行状態
int CTutorial::m_nFinishCount = 0;									// 終了カウント
CTutorial::TUTORIAL CTutorial::m_Tutorial = TUTORIAL_MOVE;			// チュートリアルの項目
bool CTutorial::m_bPlay = false;									// チュートリアルのプレイ中か否か
CAnswer*  CTutorial::m_pAnswer = nullptr;							// 返答リアクション
CExplanation*  CTutorial::m_pExplanation = nullptr;					// 説明
bool CTutorial::m_MultiAction = false;								// 連携起動の状態
CObject2D *CTutorial::m_apSkip[SKIP_MAX] = {};						// スキップのUI
float CTutorial::m_fSkipAlpha = D3DX_PI;							// スキップの不透明度
float CTutorial::m_fGauge = 0.0f;									// ゲージの数値
float CTutorial::m_fGaugeMax = SKIP_SIZE.x;							// ゲージの最大値

// デバッグ版
#ifdef _DEBUG
CEdit* CTutorial::m_pEdit = nullptr;								// エディットの情報
bool CTutorial::m_bEdit = false;									// エディット状況
#endif

//=========================================
// コンストラクタ
//=========================================
CTutorial::CTutorial() : CScene(TYPE_SCENE, PRIORITY_BG)
{
	// 全ての値をクリアする
	m_nFinishCount = 0;			// 終了カウント
	m_GameState = STATE_START;	// 状態
	m_Tutorial = TUTORIAL_MOVE;
	m_bPlay = false;
	m_pAnswer = nullptr;
	m_pExplanation = nullptr;
	m_MultiAction = false;

	for (int nCntPlay = 0; nCntPlay < MAX_PLAY; nCntPlay++)
	{
		m_apPlayer[nCntPlay] = nullptr;		// ネズミの情報
	}
	for (int nCnt = 0; nCnt < SKIP_MAX; nCnt++)
	{
		m_apSkip[nCnt] = NULL;
	}

	m_fSkipAlpha = D3DX_PI;

	// デバッグ版
#ifdef _DEBUG
	m_pEdit = nullptr;			// エディット
	m_bEdit = false;			// エディット状況
#endif
}

//=========================================
// デストラクタ
//=========================================
CTutorial::~CTutorial()
{

}

//=========================================
//初期化処理
//=========================================
HRESULT CTutorial::Init(void)
{
	// シーンの初期化
	CScene::Init();

	// テキスト読み込み処理
	CElevation::TxtSet();

	// メッシュの読み込み処理
	//CMesh::TxtSet();

	// マップの情報をロードする
	CManager::Get()->GetFile()->FalseSuccess();
	CManager::Get()->GetFile()->Load(CFile::TYPE_TUTORIAL_DEFULT);
	//CManager::Get()->GetFile()->Load(CFile::TYPE_TUTORIAL_TABLE);
	//CManager::Get()->GetFile()->Load(CFile::TYPE_TUTORIAL_KILL);
	//CManager::Get()->GetFile()->Load(CFile::TYPE_TUTORIAL_ACTION);

	// マップの設定処理
	CManager::Get()->GetFile()->SetMap();

	//// カウントダウンの生成処理
	//CCountdown::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(200.0f, 250.0f, 0.0f), 5);

	// メッシュのテキスト読み込み
	//CMesh::TxtSet();

	// スカイボックスの生成処理
	CSkyBox::Create();

	//マップの生成
	CMap::Create();

#ifdef _DEBUG	//障害物テスト用

	//CObstacle *pObstacle = NULL;

	//// ルンバの生成処理
	//CObstacle::Create(D3DXVECTOR3(-600.0f, 0.0f, -400.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_ROOMBA);
	//CObstacle::Create(D3DXVECTOR3(600.0f, 0.0f, 400.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_ROOMBA);

	//// ひもの生成処理
	//CObstacle::Create(D3DXVECTOR3(-600.0f, 650.0f, 0.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_HIMO);

	//// スピーカーの生成処理
	//pObstacle = CObstacle::Create(D3DXVECTOR3(900.0f, 0.0f, 900.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_SPEAKER);
	//pObstacle->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.25f, 0.0f));

	//pObstacle = CObstacle::Create(D3DXVECTOR3(1000.0f, 0.0f, 900.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_SPEAKER);
	//pObstacle->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f));

	//// リードの生成処理
	//pObstacle = CObstacle::Create(D3DXVECTOR3(400.0f, 0.0f, -600.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), CObstacle::TYPE_LEASH);

	//// 画鋲の生成処理
	//CObstacle::Create(D3DXVECTOR3(-200.0f, 200.0f, -120.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_PIN);

	//// 扇風機の生成処理
	//CObstacle::Create(D3DXVECTOR3(100.0f, 0.0f, 900.0f), NONE_D3DXVECTOR3, CObstacle::TYPE::TYPE_FAN);

	//CObstacle::Create(D3DXVECTOR3(-1000.0f, 650.0f, 360.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), CObstacle::TYPE_HIMO);

	//// コップの生成処理
	//CObstacle::Create(D3DXVECTOR3(-200.0f, 200.0f, 100.0f), NONE_D3DXVECTOR3, CObstacle::TYPE::TYPE_CUP);
	//pObstacle = CObstacle::Create(D3DXVECTOR3(400.0f, 200.0f, 100.0f), D3DXVECTOR3(0.0f, D3DX_PI * 1.0f, 0.0f), CObstacle::TYPE::TYPE_CUP);
	//pObstacle->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 1.0f, 0.0f));

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
				m_apPlayer[nCntPlay] = CPlayer::Create(D3DXVECTOR3(-500.0f, 0.0f, 0.0f), nCntPlay, CPlayer::TYPE_CAT);
			}
			else
			{ // 上記以外

			  // プレイヤーの生成
				m_apPlayer[nCntPlay] = CPlayer::Create(D3DXVECTOR3(250.0f * nCntPlay + 500.0f, 0.0f, 0.0f), nCntPlay, CPlayer::TYPE_RAT);
			}
		}
	}

	// キャラクターUIの生成処理
	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		CCharaInfoUI::Create(PLAYERUI_POS[nCnt], nCnt, m_apPlayer[nCnt]->GetType());
	}

	// 情報の初期化
	m_nFinishCount = 0;				// 終了カウント
	m_GameState = STATE_START;		// 状態

									// 成功を返す
	return S_OK;
}

//=============================================
//終了処理
//=============================================
void CTutorial::Uninit(void)
{
	for (int nCntPlay = 0; nCntPlay < MAX_PLAY; nCntPlay++)
	{
		m_apPlayer[nCntPlay] = nullptr;		// ネズミの情報
	}

	// 終了カウントを初期化する
	m_nFinishCount = 0;

	// 再生中のサウンドの停止
	CManager::Get()->GetSound()->Stop();

	if (m_pExplanation != NULL)
	{
		m_pExplanation->Uninit();
		m_pExplanation = NULL;
	}

	if (m_pAnswer != NULL)
	{
		m_pAnswer->Uninit();
		m_pAnswer = NULL;
	}

	for (int nCnt = 0; nCnt < SKIP_MAX; nCnt++)
	{
		if (m_apSkip[nCnt] != NULL)
		{
			m_apSkip[nCnt]->Uninit();
			m_apSkip[nCnt] = NULL;
		}
	}

	// 終了処理
	CScene::Uninit();
}

//======================================
//更新処理
//======================================
void CTutorial::Update(void)
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

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_F3) == true)
	{ // F3キーを押した場合
		CBlockManager::Get()->UninitAll();
	}

#endif

	if (m_bPlay == false)
	{
		//存在しない場合生成--------------------------------------------------------------------------
		if (m_pExplanation == NULL)
		{
			m_pExplanation = CExplanation::Create(m_Tutorial);

			// 吹き出しの出現音を鳴らす
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_TUTORIAL_BUBBLE);

			for (int nCnt = 0; nCnt < 4; nCnt++)
			{
				CTutorial::GetPlayer(nCnt)->SetTutorial(true);
			}
		}

		if (m_pAnswer == NULL)
		{
			m_pAnswer = CAnswer::Create();
		}

		//更新
		if (m_pExplanation != NULL)
		{
			m_pExplanation->Update();
		}

		if (m_pAnswer != NULL)
		{
			m_pAnswer->Update();
		}
	}
	else
	{
		if (m_pAnswer == NULL)
		{
			m_pAnswer = CAnswer::Create();
		}

		if (m_pAnswer != NULL)
		{
			m_pAnswer->Update();
		}

		//プレイ状態への移行
		PlayFalse();
	}

	switch (m_GameState)
	{
	case CTutorial::STATE_START:

		break;

	case CTutorial::STATE_PLAY:

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
			//CManager::Get()->GetFile()->Save(CFile::TYPE_TUTORIAL_DEFULT);	// ブロック
			//CManager::Get()->GetFile()->Save(CFile::TYPE_TUTORIAL_TABLE);		// ブロック
			//CManager::Get()->GetFile()->Save(CFile::TYPE_TUTORIAL_KILL);		// ブロック
			//CManager::Get()->GetFile()->Save(CFile::TYPE_TUTORIAL_ACTION);		// ブロック
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

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_0) == true ||
		CManager::Get()->GetInputGamePad()->GetPress(CInputGamePad::JOYKEY::JOYKEY_START, 0) ||
		CManager::Get()->GetInputGamePad()->GetPress(CInputGamePad::JOYKEY::JOYKEY_START, 1) ||
		CManager::Get()->GetInputGamePad()->GetPress(CInputGamePad::JOYKEY::JOYKEY_START, 2) ||
		CManager::Get()->GetInputGamePad()->GetPress(CInputGamePad::JOYKEY::JOYKEY_START, 3))
	{
		if (m_apSkip[0] != NULL)
		{
			m_fGauge += 1.5f;
			if (m_fGaugeMax <= m_fGauge)
			{
				// ゲームモードに遷移
				CManager::Get()->GetFade()->SetFade(CScene::MODE_GAME);
			}
		}
	}
	else
	{
		m_fGauge = 0.0f;
	}

	if (m_apSkip[0] != NULL)
	{
		m_apSkip[0]->SetPos(D3DXVECTOR3(880.0f + m_fGauge, 50.0f, 0.0f));
		m_apSkip[0]->SetSize(D3DXVECTOR3(m_fGauge, 50.0f, 0.0f));
		m_apSkip[0]->SetLength();					// 長さ
		m_apSkip[0]->SetAngle();						// 方向
		m_apSkip[0]->SetVertex();
	}

	if (m_apSkip[2] != NULL && m_bPlay == true)
	{
		if (sinf(m_fSkipAlpha) >= 0.5f)
		{
			m_fSkipAlpha += 0.02f;
		}
		else
		{
			m_fSkipAlpha += 0.4f;
		}
		m_apSkip[2]->SetVtxColor(D3DXCOLOR(1.0f, 1.01f, 1.0f, sinf(m_fSkipAlpha)));
	}

	for (int nCnt = 0; nCnt < SKIP_MAX; nCnt++)
	{
		if (m_apSkip[nCnt] != NULL)
		{
			m_apSkip[nCnt]->Update();
		}
	}

	CManager::Get()->GetDebugProc()->Print("状態：%d", m_GameState);
}

//======================================
//描画処理
//======================================
void CTutorial::Draw(void)
{
	if (m_pExplanation != NULL)
	{
		m_pExplanation->Draw();
	}

	if (m_pAnswer != NULL)
	{
		m_pAnswer->Draw();
	}

	for (int nCnt = 0; nCnt < SKIP_MAX; nCnt++)
	{
		if (m_apSkip[nCnt] != NULL)
		{
			m_apSkip[nCnt]->Draw();
		}
	}
}

//======================================
// プレイ状態への移行
//======================================
void CTutorial::PlayTrue(void)
{	
	if (m_Tutorial != CTutorial::TUTORIAL_LETS_GO)
	{// チュートリアルが最後じゃない時
		m_bPlay = true;

		if (m_pExplanation != NULL)
		{
			m_pExplanation->Uninit();
			m_pExplanation = NULL;
		}
		if (m_pAnswer != NULL)
		{
			m_pAnswer->Uninit();
			m_pAnswer = NULL;
		}
	}

	//チュートリアルの設定処理---------------------------------------------------------------
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		//プレイ状態をtrueにする
		m_bPlay = true;

		if (m_Tutorial == CTutorial::TUTORIAL_TABLESWING || m_Tutorial == CTutorial::TUTORIAL_CAT_KILL)
		{//ネコのキル説明の時

			//猫のみチュートリアル状態を解除しネズミのキル判定をfalseにしておく
			if (CTutorial::GetPlayer(nCnt)->GetType() == CPlayer::TYPE::TYPE_CAT)
			{
				CTutorial::GetPlayer(nCnt)->SetTutorial(false);
				CTutorial::GetPlayer(nCnt)->SetRatKill(false);
				CTutorial::GetPlayer(nCnt)->SetRatStun(false);
			}
		}
		else if (m_Tutorial == CTutorial::TUTORIAL_RAT_RESCUE)
		{//ネズミの蘇生説明の時

			//ネズミのみチュートリアル状態を解除しネズミの蘇生判定をfalseにしておく
			if (CTutorial::GetPlayer(nCnt)->GetType() == CPlayer::TYPE::TYPE_RAT)
			{
				CTutorial::GetPlayer(nCnt)->SetTutorial(false);
				CTutorial::GetPlayer(nCnt)->SetRatRescue(false);
			}
		}
		else if (m_Tutorial == CTutorial::TUTORIAL_ACTION)
		{//アクション起動説明の時

			//アクション使用状態をfalseにしておく
			CTutorial::GetPlayer(nCnt)->SetTutorial(false);
			CTutorial::GetPlayer(nCnt)->SetUseAction(false);
		}
		else
		{//それ以外の時

			//チュートリアル状態を解除する
			CTutorial::GetPlayer(nCnt)->SetTutorial(false);
		}
	}

	//マップの切り替え処理--------------------------------------------------------------------
	if (m_Tutorial == CTutorial::TUTORIAL_TABLESWING)
	{
		CBlockManager::Get()->UninitAll();
		CManager::Get()->GetFile()->Load(CFile::TYPE_TUTORIAL_TABLE);

		// マップの設定処理
		CManager::Get()->GetFile()->SetMap();

		RatPosTable();
	}
	else if (m_Tutorial == CTutorial::TUTORIAL_CAT_KILL)
	{
		CBlockManager::Get()->UninitAll();
		CManager::Get()->GetFile()->Load(CFile::TYPE_TUTORIAL_KILL);

		// マップの設定処理
		CManager::Get()->GetFile()->SetMap();

		RatPosReset();
	}
	else if (m_Tutorial == CTutorial::TUTORIAL_RAT_RESCUE)
	{
		CBlockManager::Get()->UninitAll();
		CManager::Get()->GetFile()->Load(CFile::TYPE_TUTORIAL_DEFULT);

		// マップの設定処理
		CManager::Get()->GetFile()->SetMap();
	}
	else if (m_Tutorial == CTutorial::TUTORIAL_ACTION)
	{
		CBlockManager::Get()->UninitAll();
		CManager::Get()->GetFile()->Load(CFile::TYPE_TUTORIAL_ACTION);

		// 画鋲と紐の生成処理
		CObstacle::Create(D3DXVECTOR3(0.0f, 200.0f, 360.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), CObstacle::TYPE_PIN);
		CObstacle::Create(D3DXVECTOR3(520.0f, 200.0f, 360.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), CObstacle::TYPE_PIN);
		CObstacle::Create(D3DXVECTOR3(970.0f, 200.0f, 360.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), CObstacle::TYPE_PIN);
		CObstacle::Create(D3DXVECTOR3(-1000.0f, 650.0f, 360.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), CObstacle::TYPE_HIMO);

		CatPosReset();
		RatPosReset();

		// マップの設定処理
		CManager::Get()->GetFile()->SetMap();
	}
	else if (m_Tutorial == CTutorial::TUTORIAL_ITEM_MULTI)
	{
		CBlockManager::Get()->UninitAll();
		CManager::Get()->GetFile()->Load(CFile::TYPE_TUTORIAL_ACTION);

		// リードの生成処理
		CObstacle::Create(D3DXVECTOR3(520.0f, 200.0f, -500.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f), CObstacle::TYPE_LEASH);

		// ネズミ捕りの生成
		CItem::Create(D3DXVECTOR3(-1100.0f, 0.0f, -800.0f), CItem::TYPE::TYPE_MOUSETRAP);
		CItem::Create(D3DXVECTOR3(-900.0f, 0.0f, -600.0f), CItem::TYPE::TYPE_MOUSETRAP);

		// マップの設定処理
		CManager::Get()->GetFile()->SetMap();
	}
	else if (m_Tutorial == CTutorial::TUTORIAL_LETS_GO)
	{
		// ゲームモードに遷移
		CManager::Get()->GetFade()->SetFade(CScene::MODE_GAME);
	}
}

//======================================
// 説明状態への移行
//======================================
void CTutorial::PlayFalse(void)
{
	switch (m_Tutorial)
	{
	case CTutorial::TUTORIAL_MOVE:

		// 移動したときにチュートリアル達成
		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			if (m_apPlayer[nCnt]->GetBMove() == true)
			{
				if (m_pAnswer != NULL)
				{
					m_pAnswer->SetAnswer(true, nCnt);

					// 実行完了音再生
					CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_TUTORIAL_OK);
				}
			}
		}

		break;
	case CTutorial::TUTORIAL_ATTACK_JAMP:

		// ネコは攻撃、ネズミはジャンプをするとチュートリアル達成
		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			if (m_apPlayer[nCnt]->GetAttack_Jump() == true)
			{
				if (m_pAnswer != NULL)
				{
					m_pAnswer->SetAnswer(true, nCnt);

					// 実行完了音再生
					CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_TUTORIAL_OK);
				}
			}
		}

		break;

	case CTutorial::TUTORIAL_TABLESWING:

		// ネコがネズミをキルするとチュートリアル達成
		for (int nCntPlaeyr = 0; nCntPlaeyr < 4; nCntPlaeyr++)
		{
			if (CTutorial::GetPlayer(nCntPlaeyr)->GetType() == CPlayer::TYPE::TYPE_RAT)
			{
				if (CTutorial::GetPlayer(nCntPlaeyr)->GetRatStun() == true)
				{
					for (int nCnt = 0; nCnt < 4; nCnt++)
					{
						if (m_pAnswer != NULL)
						{
							m_pAnswer->SetAnswer(true, nCnt);

							// 実行完了音再生
							CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_TUTORIAL_OK);
						}
					}
				}
			}
		}

		break;

	case CTutorial::TUTORIAL_CAT_KILL:

		// ネコがネズミをキルするとチュートリアル達成
		for (int nCntPlaeyr = 0; nCntPlaeyr < 4; nCntPlaeyr++)
		{
			if (CTutorial::GetPlayer(nCntPlaeyr)->GetType() == CPlayer::TYPE::TYPE_CAT)
			{
				if (CTutorial::GetPlayer(nCntPlaeyr)->GetRatKill() == true)
				{
					for (int nCnt = 0; nCnt < 4; nCnt++)
					{
						if (m_pAnswer != NULL)
						{
							m_pAnswer->SetAnswer(true, nCnt);

							// 実行完了音再生
							CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_TUTORIAL_OK);
						}
					}
				}
			}
		}

		break;

	case CTutorial::TUTORIAL_RAT_RESCUE:

		// ネズミをが他のネズミを蘇生するとチュートリアル達成
		for (int nCntPlaeyr = 0; nCntPlaeyr < 4; nCntPlaeyr++)
		{
			if (CTutorial::GetPlayer(nCntPlaeyr)->GetType() == CPlayer::TYPE::TYPE_RAT)
			{
				if (CTutorial::GetPlayer(nCntPlaeyr)->GetRatRescue() == true)
				{
					for (int nCnt = 0; nCnt < 4; nCnt++)
					{
						if (m_pAnswer != NULL)
						{
							m_pAnswer->SetAnswer(true, nCnt);

							// 実行完了音再生
							CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_TUTORIAL_OK);
						}
					}
				}
			}
		}

		break;
	case CTutorial::TUTORIAL_ACTION:

		// 障害物を起動したときにそれぞれチュートリアル達成
		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			if (CTutorial::GetPlayer(nCnt)->GetUseAction() == true)
			{
				if (m_pAnswer != NULL)
				{
					m_pAnswer->SetAnswer(true, nCnt);

					// チュートリアル達成時に動けないようチュートリアル状態にする
					m_apPlayer[nCnt]->SetTutorial(true);

					// 実行完了音再生
					CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_TUTORIAL_OK);
				}
			}
		}

		break;
	case CTutorial::TUTORIAL_ITEM_MULTI:

		// ネコはネズミ捕りの設置、ネズミはリードの起動でチュートリアル達成
		if (m_MultiAction == true)
		{
			for (int nCnt = 0; nCnt < 4; nCnt++)
			{
				if (m_apPlayer[nCnt]->GetType() == CPlayer::TYPE::TYPE_RAT)
				{
					if (m_pAnswer != NULL)
					{
						m_pAnswer->SetAnswer(true, nCnt);

						// 実行完了音再生
						CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_TUTORIAL_OK);
					}
				}
			}
		}

		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			if (CTutorial::GetPlayer(nCnt)->GetItem_MultiAction() == true)
			{
				if (m_pAnswer != NULL)
				{
					m_pAnswer->SetAnswer(true, nCnt);

					// 実行完了音再生
					CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_TUTORIAL_OK);
				}
			}
		}

		break;
	case CTutorial::TUTORIAL_GIMMICK:

		// 自動的にチュートリアル達成とする
		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			if (m_pAnswer != NULL)
			{
				m_pAnswer->SetAnswer(true, nCnt);
			}
		}
		break;
	case CTutorial::TUTORIAL_LETS_GO:

		// 自動的にチュートリアル達成とする
		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			if (m_pAnswer != NULL)
			{
				m_pAnswer->SetAnswer(true, nCnt);
			}
		}
		break;
	case CTutorial::TUTORIAL_MAX:
		break;
	default:
		assert(false);
		break;
	}

	if (m_pAnswer != NULL)
	{
		if (m_pAnswer->GetAnswer(0) == true &&
			m_pAnswer->GetAnswer(1) == true &&
			m_pAnswer->GetAnswer(2) == true &&
			m_pAnswer->GetAnswer(3) == true)
		{
			m_bPlay = false;

			int mTutorialNumber = (int)m_Tutorial;
			mTutorialNumber++;
			m_Tutorial = (TUTORIAL)mTutorialNumber;

			if (m_pAnswer != NULL)
			{
				m_pAnswer->Uninit();
				m_pAnswer = NULL;
			}
		}
	}
}

//======================================
// ネコの位置をリセットする
//======================================
void CTutorial::CatPosReset(void)
{
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		if (m_apPlayer[nCnt]->GetType() == CPlayer::TYPE_CAT)
		{
			m_apPlayer[nCnt]->SetPos(D3DXVECTOR3(-1000.0f, 0.0f, 0.0f));
		}
	}
}

//======================================
// ネズミの位置をリセットする
//======================================
void CTutorial::RatPosReset(void)
{
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		if (m_apPlayer[nCnt]->GetType() == CPlayer::TYPE_RAT)
		{
			m_apPlayer[nCnt]->SetPos(D3DXVECTOR3(250.0f * nCnt + 500.0f, 0.0f, 0.0f));
		}
	}
}

//======================================
// ネズミの位置をリセットする
//======================================
void CTutorial::RatPosTable(void)
{
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		if (m_apPlayer[nCnt]->GetType() == CPlayer::TYPE_RAT)
		{
			m_apPlayer[nCnt]->SetPos(D3DXVECTOR3(800.0f, 200.0f, -800.0f + nCnt * 500.0f));
		}
	}
}

//======================================
// 情報の設定処理
//======================================
void CTutorial::SetData(const MODE mode)
{
	// 情報の設定処理
	CScene::SetData(mode);

	// スタート状態にする
	m_GameState = STATE_START;

	// 情報の初期化
	m_nFinishCount = 0;				// 終了カウント

	for (int nCnt = 0; nCnt < SKIP_MAX; nCnt++)
	{
		if (m_apSkip[nCnt] == NULL)
		{
			m_apSkip[nCnt] = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_2DUI, CObject::PRIORITY_UI);

			if (nCnt == 0)
			{
				m_apSkip[nCnt]->SetPos(GAUGE_POS);			// 位置
				m_apSkip[nCnt]->SetPosOld(GAUGE_POS);		// 前回の位置
				m_apSkip[nCnt]->SetRot(NONE_D3DXVECTOR3);		// 向き
				m_apSkip[nCnt]->SetSize(GAUGE_SIZE);			// サイズ
			}
			else
			{
				m_apSkip[nCnt]->SetPos(SKIP_POS);			// 位置
				m_apSkip[nCnt]->SetPosOld(SKIP_POS);		// 前回の位置
				m_apSkip[nCnt]->SetRot(NONE_D3DXVECTOR3);		// 向き
				m_apSkip[nCnt]->SetSize(SKIP_SIZE);			// サイズ
			}
			m_apSkip[nCnt]->SetLength();					// 長さ
			m_apSkip[nCnt]->SetAngle();						// 方向

			// 頂点座標の設定処理
			m_apSkip[nCnt]->SetVertex();
		}
	}
	if (m_apSkip[0] != NULL)
	{
		m_apSkip[0]->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_skip_gauge00.png"));		// テクスチャの割り当て処理
	}
	if (m_apSkip[1] != NULL)
	{
		m_apSkip[1]->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_skip_gauge01.png"));		// テクスチャの割り当て処理
	}
	if (m_apSkip[2] != NULL)
	{
		m_apSkip[2]->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_skip00.png"));		// テクスチャの割り当て処理
	}
}

//======================================
// 遷移処理
//======================================
void CTutorial::Transition(void)
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
// チュートリアルの進行状態の設定処理
//======================================
void CTutorial::SetState(const STATE state)
{
	// チュートリアルの進行状態を設定する
	m_GameState = state;
}

//======================================
// チュートリアルの進行状態の取得処理
//======================================
CTutorial::STATE CTutorial::GetState(void)
{
	// チュートリアルの進行状態を返す
	return m_GameState;
}

//======================================
// プレイヤーの取得処理
//======================================
CPlayer* CTutorial::GetPlayer(const int nID)
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
// ネズミのNULL化処理
//======================================
void CTutorial::DeletePlayer(int nIdx)
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
CEdit* CTutorial::GetEdit(void)
{
	// エディットの情報を返す
	return m_pEdit;
}

//======================================
// エディット状況の取得処理
//======================================
bool CTutorial::IsEdit(void)
{
	// エディット状況を返す
	return m_bEdit;
}

#endif