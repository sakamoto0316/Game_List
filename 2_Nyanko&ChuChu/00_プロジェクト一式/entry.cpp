//============================================
//
// エントリー画面のメイン処理[entry.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "entry.h"
#include "renderer.h"
#include "fade.h"
#include "Objectmesh.h"
#include "debugproc.h"
#include "entry_UI.h"
#include "entry_team.h"
#include "entry_BG.h"
#include "input.h"
#include "player.h"
#include "sound.h"
#include "entry_message.h"
#include "entry_rand.h"

//--------------------------------------------
// マクロ定義
//--------------------------------------------
#define POS_MESSAGEUI			(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 130.0f, 675.0f, 0.0f))		// 操作説明UIの位置
#define SIZE_MESSAGEUI			(D3DXVECTOR3(500.0f, 50.0f, 0.0f))						// 操作説明UIのサイズ

//--------------------------------------------
// 静的メンバ変数
//--------------------------------------------
int CEntry::m_nCatIdx = 0;						// ネコをやるプレイヤー
int CEntry::m_nCatOldIdx = 0;					// 差分用ID
int CEntry::m_EntryId[MAX_PLAY] = {};			// 全体のID
CPlayer* CEntry::m_apPlayer[MAX_PLAY] = {};		// プレイヤーのモデル情報
CEntryUI* CEntry::m_apUI[MAX_PLAY] = {};		// エントリーUIの情報

//=========================================
// コンストラクタ
//=========================================
CEntry::CEntry() : CScene(TYPE_SCENE, PRIORITY_BG)
{
	// 全ての値をクリアする
	m_nCatIdx = 0;					// ネコをやるプレイヤー
	m_nCatOldIdx = 0;				// 差分用ID
	m_nSceneCnt = 0;				// 遷移までのカウント
	m_bEnter = false;				// エンターを押したかどうか
	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		m_apUI[nCnt] = nullptr;		// エントリーUIの情報
		m_apPlayer[nCnt] = nullptr;	// プレイヤーのモデル情報
	}
}

//=========================================
// デストラクタ
//=========================================
CEntry::~CEntry()
{

}

//=========================================
//初期化処理
//=========================================
HRESULT CEntry::Init(void)
{
	// 全ての値を初期化する
	m_nCatIdx = 0;					// ネコをやるプレイヤー
	m_nCatOldIdx = 0;				// 差分用ID
	m_nSceneCnt = 0;				// 遷移までのカウント
	m_bEnter = false;				// エンターを押したかどうか

	//　シーンの初期化
	CScene::Init();

	// 背景の生成処理
	CEntryBG::Create();

	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		if (nCnt == m_nCatIdx)
		{ // ネコをやるプレイヤーのみ

			// エントリーUIの生成処理
			m_apUI[nCnt] = CEntryUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + (300.0f * nCnt) - 450.0f, SCREEN_HEIGHT * 0.45f, 0.0f), nCnt, CPlayer::TYPE_CAT);

			// ネコの生成処理
			m_apPlayer[nCnt] = CPlayer::Create(D3DXVECTOR3(-500.0f + (350.0f*nCnt), 0.0f, -150.0f), nCnt, CPlayer::TYPE_CAT);

		}
		else
		{ // 上記以外

			// エントリーUIの生成処理
			m_apUI[nCnt] = CEntryUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + (300.0f * nCnt) - 450.0f, SCREEN_HEIGHT * 0.45f, 0.0f), nCnt, CPlayer::TYPE_RAT);

			// ラットの生成処理
			m_apPlayer[nCnt] = CPlayer::Create(D3DXVECTOR3(-500.0f + (350.0f*nCnt), 0.0f, -150.0f), nCnt, CPlayer::TYPE_RAT);

		}
		// ID代入
		m_EntryId[nCnt] = nCnt;
	}

	// エントリー画面の操作説明UIの生成
	CEntryMessage::Create(POS_MESSAGEUI, POS_MESSAGEUI, SIZE_MESSAGEUI);

	// エントリー画面のランダム指示UIの生成
	CEntryRandom::Create();

	// 成功を返す
	return S_OK;
}

//=============================================
//終了処理
//=============================================
void CEntry::Uninit(void)
{
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		if (m_apUI[nCnt] != nullptr)
		{ // エントリーUIの情報が NULL じゃない場合

			// エントリーUIの終了処理
			m_apUI[nCnt]->Uninit();
			m_apUI[nCnt] = nullptr;
		}
		m_apPlayer[nCnt] = nullptr;		// ネズミの情報
	}

	CManager::Get()->GetSound()->Stop();

	// 終了処理
	CScene::Uninit();
}

//======================================
//更新処理
//======================================
void CEntry::Update(void)
{
	if (m_bEnter == false)
	{ // 決定していない場合

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true ||
			CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, 0) == true ||
			CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, 1) == true ||
			CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, 2) == true ||
			CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, 3) == true)
		{ // ENTERキーを押した場合またはAボタンを押した場合
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_DECIDE);

			m_bEnter = true;

			for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
			{
				m_apPlayer[m_EntryId[nCnt]]->SetMove(D3DXVECTOR3(0.0f, 25.0f, 0.0f));
			}
		}

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_TAB) == true ||
			CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_Y, 0) == true ||
			CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_Y, 1) == true ||
			CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_Y, 2) == true ||
			CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_Y, 3) == true)
		{ // TABキーを押したまたは、Yボタンを押した場合

			// ネコのIDをランダムで変える
			m_nCatIdx = rand() % MAX_PLAY;

			for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
			{
				if (nCnt == m_nCatIdx)
				{ // ネコをやるプレイヤーのみ

					// ネコに設定する
					m_apUI[nCnt]->GetTeam()->SetType(CPlayer::TYPE_CAT);

				}
				else
				{ // 上記以外

					// ネズミに設定する
					m_apUI[nCnt]->GetTeam()->SetType(CPlayer::TYPE_RAT);

				}

				m_apPlayer[nCnt]->SetMove(D3DXVECTOR3(0.0f, 25.0f, 0.0f));

				if (m_nCatOldIdx != m_nCatIdx)
				{ // ID並べ替え処理

					int nKeepID = 0;	// 保存用引数

					nKeepID = m_EntryId[m_nCatIdx];
					m_EntryId[m_nCatIdx] = m_EntryId[m_nCatOldIdx];
					m_EntryId[m_nCatOldIdx] = nKeepID;
					m_nCatOldIdx = m_nCatIdx;
				}
			}

			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_DECIDE);

			m_bEnter = true;
		}
	}

	if (m_bEnter == false)
	{ // エントリーが終わっていない場合
		for (int nCntPlayer = 0; nCntPlayer < 4; nCntPlayer++)
		{
			if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_D) == true ||
				CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_RIGHT, nCntPlayer) == true)
			{ // 右キーを押した場合
				CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_SELECT);

				// ネコをやるプレイヤーを設定
				m_nCatIdx = (m_nCatIdx + 1) % MAX_PLAY;

				for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
				{
					if (nCnt == m_nCatIdx)
					{ // ネコをやるプレイヤーのみ

						// ネコに設定する
						m_apUI[nCnt]->GetTeam()->SetType(CPlayer::TYPE_CAT);

					}
					else
					{ // 上記以外

						// ネズミに設定する
						m_apUI[nCnt]->GetTeam()->SetType(CPlayer::TYPE_RAT);

					}
				}
			}

			if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_A) == true ||
				CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_LEFT, nCntPlayer) == true)
			{ // 左キーを押した場合

				CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_SELECT);

				// ネコをやるプレイヤーを設定
				m_nCatIdx = (m_nCatIdx + MAX_PLAY - 1) % MAX_PLAY;

				for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
				{
					if (nCnt == m_nCatIdx)
					{ // ネコをやるプレイヤーのみ

						// ネコに設定する
						m_apUI[nCnt]->GetTeam()->SetType(CPlayer::TYPE_CAT);

					}
					else
					{ // 上記以外

						// ネズミに設定する
						m_apUI[nCnt]->GetTeam()->SetType(CPlayer::TYPE_RAT);

					}
				}
			}

			if (m_nCatOldIdx != m_nCatIdx)
			{ // ID並べ替え処理

				int nKeepID = 0;	// 保存用引数

				nKeepID = m_EntryId[m_nCatIdx];
				m_EntryId[m_nCatIdx] = m_EntryId[m_nCatOldIdx];
				m_EntryId[m_nCatOldIdx] = nKeepID;
				m_nCatOldIdx = m_nCatIdx;
			}

			for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
			{ // 位置設定&移動量リセット

				m_apPlayer[m_EntryId[nCnt]]->SetPos(D3DXVECTOR3(-500.0f + (350.0f * nCnt), 0.0f, -150.0f));	// 位置
				m_apPlayer[m_EntryId[nCnt]]->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));							// 移動量
				m_apPlayer[m_EntryId[nCnt]]->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));								// 向き

				// ジャンプ状況を false にする
				m_apPlayer[nCnt]->SetEnableJump(false);
			}
		}
	}
	else
	{

		for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
		{
			if (m_apPlayer[m_EntryId[nCnt]]->GetPos().y < -2.0f)
			{	// 一定の高さより低くなった場合

				m_apPlayer[m_EntryId[nCnt]]->SetPos(D3DXVECTOR3(-500.0f + (350.0f * nCnt), -2.0f, -150.0f));
				m_apPlayer[m_EntryId[nCnt]]->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

				// ジャンプ状況を false にする
				m_apPlayer[nCnt]->SetEnableJump(false);
			}
			else
			{	// それ以外

				// 保存用引数
				float KeepMove = m_apPlayer[m_EntryId[nCnt]]->GetMove().y;	// ジャンプ力
				float KeepPos = m_apPlayer[m_EntryId[nCnt]]->GetPos().y;	// モデルの高さ(Y)

				m_apPlayer[m_EntryId[nCnt]]->SetPos(D3DXVECTOR3(-500.0f + (350.0f * nCnt), KeepPos, -150.0f));
				m_apPlayer[m_EntryId[nCnt]]->SetMove(D3DXVECTOR3(0.0f, KeepMove, 0.0f));
			}
			m_apPlayer[m_EntryId[nCnt]]->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		}
		m_nSceneCnt++;
		if (m_nSceneCnt > 80)
		{
			// ゲームモードに遷移
			CManager::Get()->GetFade()->SetFade(CScene::MODE_TUTORIAL);
		}

	}
	// レンダラーの更新
	CManager::Get()->GetRenderer()->Update();
}

//======================================
//描画処理
//======================================
void CEntry::Draw(void)
{

}

//======================================
// ネコ担当の取得処理
//======================================
int CEntry::GetCatIdx(void)
{
	// ネコのインデックスを返す
	return m_nCatIdx;
}