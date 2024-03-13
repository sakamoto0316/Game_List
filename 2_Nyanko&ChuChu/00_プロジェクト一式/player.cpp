//===========================================
//
// プレイヤーのメイン処理[player.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "player.h"
#include "game.h"
#include "tutorial.h"
#include "result.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "useful.h"
#include "MultiCamera.h"
#include "sound.h"

#include "motion.h"
#include "player_idUI.h"
#include "stun.h"
#include "rat_ghost.h"
#include "resurrection_fan.h"
#include "collision.h"
#include "recoveringUI.h"
#include "speech_message.h"
#include "death_arrow.h"

#include "Cat.h"
#include "rat.h"

//-------------------------------------------
// 無名名前空間
//-------------------------------------------
namespace
{
	const D3DXVECTOR3 SMASH_MOVE = D3DXVECTOR3(8.0f, 20.0f, 8.0f);		// 吹き飛び状態の移動量
	const D3DXCOLOR SMASH_COLOR = D3DXCOLOR(0.9f, 0.0f, 0.1f, 0.7f);		// 吹き飛び状態の時の色
	const float CAT_CAMERA_HEIGHT = 250.0f;		// 猫のカメラの高さ
	const float CAT_CAMERA_DIS = 50.0f;			// 猫のカメラの視点と注視点の高さの差分(角度)
	const float RAT_CAMERA_HEIGHT = 100.0f;		// 猫のカメラの高さ
	const float RAT_CAMERA_DIS = 60.0f;			// ネズミのカメラの視点と注視点の高さの差分(角度)
	const float DIFF_ROT = 0.2f;					// 角度に足す差分の割合
	const float CAMERA_ROT_MOVE = 0.032f;		// カメラの向きの移動量
	const float ADD_ACTION_RADIUS = 40.0f;		// サーチ時の半径の追加数
	const int NONE_PLAYERIDX = -1;				// プレイヤーの番号の初期値
	const int CAT_SMASH_STUN = 120;				// ネコのスタン時間
	const int RAT_SMASH_STUN = 90;				// ネズミのスタン時間
	const int STUN_WAIT = 120;					// オブジェクト無効の待機時間
	const int DEATH_WAIT = 120;					// 死亡時の待機時間
	const int SMASH_WAIT = 40;					// 吹き飛び状態のカウント数
	const int STUN_FLASH_INTERVAL = 12;			// プレイヤーの点滅間隔
	const int DEATH_FLASH_INTERVAL = 4;			// プレイヤーの点滅間隔
	const WORD SMASH_VIBRATE = 30000;			// 吹き飛んだ時のバイブレーション
	const WORD STUN_VIBRATE = 20000;				// 気絶したときのバイブレーション
}

//==============================
// コンストラクタ
//==============================
CPlayer::CPlayer() : CCharacter(CObject::TYPE_PLAYER, CObject::PRIORITY_PLAYER)
{
	// コンストラクタの箱
	Box();
}

//==============================
// オーバーロードコンストラクタ
//==============================
CPlayer::CPlayer(CObject::TYPE type, PRIORITY priority) : CCharacter(type, priority)
{
	// コンストラクタの箱
	Box();
}

//==============================
// デストラクタ
//==============================
CPlayer::~CPlayer()
{

}

//==============================
// コンストラクタの箱
//==============================
void CPlayer::Box(void)
{
	// 全ての値をクリアする
	m_pMotion = nullptr;				// モーションの情報
	m_pPlayerID = nullptr;				// プレイヤーのID表示
	m_pStun = nullptr;					// 気絶の情報
	m_pRatGhost = nullptr;				// 幽霊ネズミの情報
	m_pRessrectionFan = nullptr;		// 円の範囲の情報
	m_pRecoveringUI = nullptr;			// 回復中のUIの情報
	m_pSpeechMessage = nullptr;			// 伝達メッセージの情報
	m_sizeColl = NONE_D3DXVECTOR3;		// 当たり判定のサイズ
	m_col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);				// 色
	m_type = TYPE_CAT;					// 種類
	m_nPlayerIdx = NONE_PLAYERIDX;		// プレイヤーのインデックス
	m_fSpeed = 0.0f;					// 速度
	m_fSpeedCopy = 0.0f;				// 速度のコピー
	m_fRotDest = 0.0f;					// 目標
	m_fStunHeight = 0.0f;				// 気絶が出る高さ
	m_bAttack = false;					// 攻撃したか
	m_bMove = false;					// 移動しているか
	m_bDisp = true;						// 表示するか
	m_bDispSmash = false;				// 吹き飛び用の表示するか
	m_CameraRot = NONE_D3DXVECTOR3;		// カメラの向き
	m_nResurrectionTime = 0;			// 復活するまでの時間
	m_bTutorial = false;
	m_bKill = false;
	m_bSe = false;						// SE再生したかどうか
	m_bCatSe = false;					// ネコ用SE再生状況
	m_bRatSe = false;					// ネズミ用SE再生状況

	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		m_pDeathArrow[nCnt] = nullptr;
	}

	for (int nCnt = 0; nCnt < LOG_MAX; nCnt++)
	{
		m_apLog[nCnt] = nullptr;
	}
	m_nLogNumber = 0;
}

//==============================
// プレイヤーの初期化処理
//==============================
HRESULT CPlayer::Init(void)
{
	if (FAILED(CCharacter::Init()))
	{ // 初期化処理に失敗した場合

		// 停止
		assert(false);

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	m_pMotion = nullptr;				// モーションの情報
	m_pPlayerID = nullptr;				// プレイヤーのID表示
	m_pStun = nullptr;					// 気絶の情報
	m_pRatGhost = nullptr;				// 幽霊ネズミの情報
	m_pRessrectionFan = nullptr;		// 円の範囲の情報
	m_pRecoveringUI = nullptr;			// 回復中のUIの情報
	m_pSpeechMessage = nullptr;			// 伝達メッセージの情報
	//m_move = NONE_D3DXVECTOR3;			// 移動量
	m_sizeColl = NONE_D3DXVECTOR3;		// 当たり判定のサイズ
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);				// 色
	m_type = TYPE_CAT;					// 種類
	m_nPlayerIdx = NONE_PLAYERIDX;		// プレイヤーのインデックス
	m_fSpeed = 0.0f;					// 速度
	m_fSpeedCopy = 0.0f;				// 速度のコピー
	m_fRotDest = 0.0f;					// 目標
	m_fStunHeight = 0.0f;				// 気絶が出る高さ
	m_bAttack = false;					// 攻撃したか
	m_bMove = false;					// 移動しているか
	m_bDisp = true;						// 表示するか
	m_bDispSmash = false;				// 吹き飛び用の表示するか
	m_bCatSe = false;					// ネコ用SE再生状況
	m_bRatSe = false;					// ネズミ用SE再生状況
	m_nResurrectionTime = 0;			// 復活するまでの時間
	m_nLogPlayer = 0;

	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{// 死亡矢印の情報
		m_pDeathArrow[nCnt] = nullptr;
	}

	// 値を返す
	return S_OK;
}

//========================================
// プレイヤーの終了処理
//========================================
void CPlayer::Uninit(void)
{
	if (m_pMotion != nullptr)
	{ // モーションが NULL じゃない場合

		// モーションのメモリを開放する
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	if (m_pPlayerID != nullptr)
	{ // プレイヤーのID表示が NULL じゃない場合

		// プレイヤーのID表示の終了処理
		m_pPlayerID->Uninit();
		m_pPlayerID = nullptr;
	}

	if (m_pStun != nullptr)
	{ // 気絶演出が NULL じゃない場合

		// 気絶演出の終了処理
		m_pStun->Uninit();
		m_pStun = nullptr;
	}

	if (m_pRatGhost != nullptr)
	{ // 幽霊ネズミが NULL じゃない場合

		//幽霊ネズミの終了処理
		m_pRatGhost->Uninit();
		m_pRatGhost = nullptr;
	}

	if (m_pRessrectionFan != nullptr)
	{ // 円の範囲が NULL じゃない場合

		//円の範囲の終了処理
		m_pRessrectionFan = nullptr;
	}

	if (m_pRecoveringUI != nullptr)
	{ // 回復中のUIが NULL じゃない場合

		//回復中のUIの終了処理
		m_pRecoveringUI->Uninit();
		m_pRecoveringUI = nullptr;
	}

	if (m_pSpeechMessage != nullptr)
	{ // 伝達メッセージが NULL じゃないとき

		//伝達メッセージの終了処理
		m_pSpeechMessage = nullptr;
	}

	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		if (m_pDeathArrow[nCnt] != nullptr)
		{ // 死亡矢印が NULL じゃないとき

			//死亡矢印の終了処理
			m_pDeathArrow[nCnt]->Uninit();
			m_pDeathArrow[nCnt] = nullptr;
		}
	}

	for (int nCnt = 0; nCnt < LOG_MAX; nCnt++)
	{
		if (m_apLog[nCnt] != NULL)
		{
			m_apLog[nCnt]->Uninit();
			m_apLog[nCnt] = NULL;
		}
	}

	if (CManager::Get()->GetMode() == CScene::MODE_TUTORIAL)
	{
		// プレイヤーを消去する
		CTutorial::DeletePlayer(m_nPlayerIdx);
	}
	else
	{
		// プレイヤーを消去する
		CGame::DeletePlayer(m_nPlayerIdx);
	}

	// 終了処理
	CCharacter::Uninit();
}

//=====================================
// プレイヤーの更新処理
//=====================================
void CPlayer::Update(void)
{
	// 障害物との当たり判定
	collision::ObstacleHit(this, m_sizeColl.x, m_sizeColl.y, m_sizeColl.z);

	// 気絶状態の管理
	StunStateManager();

	// 状態の管理
	StateManager();

	// 起動可能障害物や警告を出す障害物のサーチ
	collision::ObstacleSearch(this, m_sizeColl.x + ADD_ACTION_RADIUS);

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_E) ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_B, m_nPlayerIdx) == true)
	{ // アクションキーを押した場合

		if (m_State != STATE_DEATH &&
			m_StunState != STUNSTATE_SMASH &&
			m_StunState != STUNSTATE_STUN)
		{ // アクションを起こせる場合

			// 障害物のアクション処理
			collision::ObstacleAction(this, m_sizeColl.x + ADD_ACTION_RADIUS);
		}
	}

#if CAMERA != 0
	//カメラ情報の更新
	CameraUpdate();
#endif // CAMERA

#ifdef _DEBUG

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_1))
	{
		SetLog(m_nPlayerIdx, CLog::TYPE::TYPE_DEATH);
	}

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_2))
	{
		SetLog(m_nPlayerIdx, CLog::TYPE::TYPE_STUN);
	}

#endif // _DEBUG

	if (m_pMotion != nullptr)
	{ // モーションが NULL じゃない場合

		// モーションの更新処理
		m_pMotion->Update();
	}

	for (int nCnt = 0; nCnt < LOG_MAX; nCnt++)
	{
		if (m_apLog[nCnt] != NULL)
		{
			m_apLog[nCnt]->Update();
		}
	}

	// 壁の当たり判定
	collision::WallCollision(this, m_sizeColl);

	// デバッグ表示
	CManager::Get()->GetDebugProc()->Print("位置：%f %f %f\n向き：%f %f %f\n", GetPos().x, GetPos().y, GetPos().z, GetRot().x, GetRot().y, GetRot().z);
}

//=====================================
// プレイヤーの描画処理
//=====================================
void CPlayer::Draw(void)
{
	if (m_bDisp == true)
	{ // 表示状態のとき

		if (m_bDispSmash == true)
		{ // 吹き飛ばされてるとき

			// 描画処理(色)
			CCharacter::Draw(m_col);
		}
		else
		{ // それ以外のとき

			// 描画処理
			CCharacter::Draw();
		}
	}

	for (int nCnt = 0; nCnt < LOG_MAX; nCnt++)
	{
		if (m_apLog[nCnt] != NULL)
		{
			m_apLog[nCnt]->Draw();
		}
	}

	if (m_pPlayerID != nullptr)
	{ // プレイヤーのID表示が NULL じゃない場合

		if (m_nPlayerIdx != CObject::GetDrawIdx() && (CManager::Get()->GetMode() == CScene::MODE_GAME || CManager::Get()->GetMode() == CScene::MODE_TUTORIAL))
		{
			m_pPlayerID->Draw();
		}
	}
}

//=====================================
// 吹き飛び状態
//=====================================
void CPlayer::Smash(const float fAngle)
{
	// ローカル変数宣言
	D3DXVECTOR3 pos = GetPos();		// 位置を取得する
	D3DXVECTOR3 move = GetMove();	// 移動量を取得する

	if (m_State == STATE_NONE &&
		m_StunState == STUNSTATE_NONE)
	{ // ダメージ受ける状態だった場合

		// バイブレーションを設定する
		CManager::Get()->GetInputGamePad()->GetRightVibration(GetPlayerIdx(), SMASH_VIBRATE, SMASH_WAIT);
		CManager::Get()->GetInputGamePad()->GetLeftVibration(GetPlayerIdx(), SMASH_VIBRATE, SMASH_WAIT);

		// 移動量を算出する
		move.x = sinf(fAngle) * SMASH_MOVE.x;
		move.y = SMASH_MOVE.y;
		move.z = cosf(fAngle) * SMASH_MOVE.z;

		m_fRotDest = fAngle;

		// 位置加算
		pos += move;

		// 移動量設定
		SetMove(move);

		// 位置設定
		SetPos(pos);

		if (m_type == TYPE_RAT)
		{
			// チュッ再生
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_CHU);
			m_bRatSe = true;
		}
		else if (m_type == TYPE_CAT)
		{
			// にゃ～ん再生
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_CATDAMAGE);
			m_bCatSe = true;


		}

		// 吹き飛び状態にする
		m_StunState = STUNSTATE_SMASH;

		// 気絶状態カウントを設定する
		m_StunStateCount = SMASH_WAIT;
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CPlayer::SetData(const D3DXVECTOR3& pos, const int nID, const TYPE type)
{
	// 情報の設定処理
	SetPos(pos);					// 位置
	SetPosOld(pos);					// 前回の位置
	SetRot(NONE_D3DXVECTOR3);		// 向き
	SetScale(NONE_SCALE);			// 拡大率

	// 全ての値をクリアする
	m_pStun = nullptr;					// 気絶の情報
	//m_move = NONE_D3DXVECTOR3;			// 移動量
	m_sizeColl = NONE_D3DXVECTOR3;		// 当たり判定のサイズ
	m_type = type;						// 種類
	m_nPlayerIdx = nID;					// プレイヤーのインデックス
	m_fSpeed = 0.0f;					// 速度
	m_fSpeedCopy = 0.0f;				// 速度のコピー
	m_bAttack = false;					// 攻撃したか
	m_bMove = false;					// 移動しているか

	if (m_pPlayerID == nullptr)
	{ // プレイヤーのID表示が NULL の場合

		// プレイヤーのID表示の生成処理
		m_pPlayerID = CPlayerID::Create(pos, nID);
	}
}

//=======================================
// 生成処理
//=======================================
CPlayer* CPlayer::Create(const D3DXVECTOR3& pos, const int nID, const TYPE type)
{
	// プレイヤーのポインタ
	CPlayer* pPlayer = nullptr;

	if (pPlayer == nullptr)
	{ // オブジェクトが NULL の場合

		switch (type)
		{
		case TYPE::TYPE_CAT:		// ネコ

			// ネコを生成
			pPlayer = new CCat;

			break;

		case TYPE::TYPE_RAT:		// ネズミ

			// ネズミを生成
			pPlayer = new CRat;

			break;

		default:					// 上記以外

			// 停止
			assert(false);

			break;
		}
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pPlayer != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pPlayer->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pPlayer->SetData(pos, nID, type);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// プレイヤーのポインタを返す
	return pPlayer;
}

//=======================================
// 移動操作処理
//=======================================
void CPlayer::MoveControl(void)
{
	if (CManager::Get()->GetMode() == CScene::MODE_GAME || CManager::Get()->GetMode() == CScene::MODE_TUTORIAL)
	{
		// ローカル変数宣言
		//D3DXVECTOR3 rot = GetRot();

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_D) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLXPress(m_nPlayerIdx) > 0)
		{ // 右を押した場合

			if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true ||
				CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nPlayerIdx) > 0)
			{ // 上を押した場合

				// 向きを設定する
				//rot.y = m_CameraRot.y + D3DX_PI * -0.75f;
				m_fRotDest = m_CameraRot.y + D3DX_PI * -0.75f;
			}
			else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true ||
				CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nPlayerIdx) < 0)
			{ // 下を押した場合

				// 向きを設定する
				//rot.y = m_CameraRot.y + D3DX_PI * -0.25f;
				m_fRotDest = m_CameraRot.y + D3DX_PI * -0.25f;
			}
			else
			{ // 上記以外

				// 向きを設定する
				//rot.y = m_CameraRot.y + D3DX_PI * -0.5f;
				m_fRotDest = m_CameraRot.y + D3DX_PI * -0.5f;

			}
			m_bMove = true;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_A) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLXPress(m_nPlayerIdx) < 0)
		{ // 左を押した場合

			if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true ||
				CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nPlayerIdx) > 0)
			{ // 上を押した場合

				// 向きを設定する
				//rot.y = m_CameraRot.y + D3DX_PI * 0.75f;
				m_fRotDest = m_CameraRot.y + D3DX_PI * 0.75f;

			}
			else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true ||
				CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nPlayerIdx) < 0)
			{ // 下を押した場合

				// 向きを設定する
				//rot.y = m_CameraRot.y + D3DX_PI * 0.25f;
				m_fRotDest = m_CameraRot.y + D3DX_PI * 0.25f;
			}
			else
			{ // 上記以外

				// 向きを設定する
				//rot.y = m_CameraRot.y + D3DX_PI * 0.5f;
				m_fRotDest = m_CameraRot.y + D3DX_PI * 0.5f;
			}
			m_bMove = true;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nPlayerIdx) > 0)
		{ // 上を押した場合

			// 向きを設定する
			//rot.y = m_CameraRot.y + D3DX_PI * 1.0f;
			m_fRotDest = m_CameraRot.y + D3DX_PI * 1.0f;
			m_bMove = true;
		}
		else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nPlayerIdx) < 0)
		{ // 下を押した場合

			// 向きを設定する
			//rot.y = m_CameraRot.y + D3DX_PI * 0.0f;
			m_fRotDest = m_CameraRot.y + D3DX_PI * 0.0f;
			m_bMove = true;
		}
		else
		{ // 上記以外
			m_bMove = false;
			// 速度を設定する
			m_fSpeed = 0.0f;
		}
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nPlayerIdx) > 0)
	{ // 上を押した場合

		// 向きを設定する
		//rot.y = m_CameraRot.y + D3DX_PI * 1.0f;
		m_fRotDest = m_CameraRot.y + D3DX_PI * 1.0f;
		m_bMove = true;
	}
	else if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickLYPress(m_nPlayerIdx) < 0)
	{ // 下を押した場合

		// 向きを設定する
		//rot.y = m_CameraRot.y + D3DX_PI * 0.0f;
		m_fRotDest = m_CameraRot.y + D3DX_PI * 0.0f;
		m_bMove = true;
	}
	else
	{ // 上記以外

		// 移動状況を false にする
		m_bMove = false;

		// 速度を設定する
		m_fSpeed = 0.0f;
	}
}

//=======================================
// 移動処理
//=======================================
void CPlayer::Move(void)
{
	if (CManager::Get()->GetMode() == CScene::MODE_GAME || CManager::Get()->GetMode() == CScene::MODE_TUTORIAL)
	{
		// 位置を取得する
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 move = GetMove();

		// 移動量を設定する
		move.x = -sinf(m_fRotDest) * m_fSpeed;
		move.z = -cosf(m_fRotDest) * m_fSpeed;

		// 移動量を加算する
		pos.x += move.x;
		pos.z += move.z;

		// 移動量を適用する
		SetMove(move);

		// 位置を適用する
		SetPos(pos);
	}
}

//=======================================
// それぞれのプレイヤーのカメラの更新
//=======================================
void CPlayer::CameraUpdate(void)
{
#ifdef _DEBUG

	if (CManager::Get()->GetMode() == CScene::MODE::MODE_GAME)
	{
		if (CGame::GetEditbool() == false)
		{
			CMultiCamera *pCamera = CManager::Get()->GetMlutiCamera(m_nPlayerIdx);
			D3DXVECTOR3 Pos = GetPos();

			if (m_type == TYPE::TYPE_CAT)
			{ //猫のカメラの位置
				pCamera->SetPosR(D3DXVECTOR3(
					Pos.x,
					Pos.y + CAT_CAMERA_HEIGHT,
					Pos.z
				));
				pCamera->SetPosV(D3DXVECTOR3(
					Pos.x + sinf(m_CameraRot.y + (D3DX_PI * 1.0f)) * 200.0f,
					Pos.y + CAT_CAMERA_HEIGHT + CAT_CAMERA_DIS,
					Pos.z + cosf(m_CameraRot.y + (D3DX_PI * 1.0f)) * 200.0f));
			}
			else
			{ //ネズミのカメラの位置
				pCamera->SetPosR(D3DXVECTOR3(
					Pos.x,
					Pos.y + RAT_CAMERA_HEIGHT,
					Pos.z
				));
				pCamera->SetPosV(D3DXVECTOR3(
					Pos.x + sinf(m_CameraRot.y + (D3DX_PI * 1.0f)) * 200.0f,
					Pos.y + RAT_CAMERA_HEIGHT + RAT_CAMERA_DIS,
					Pos.z + cosf(m_CameraRot.y + (D3DX_PI * 1.0f)) * 200.0f));
			}

			if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LSHIFT) == true ||
				CManager::Get()->GetInputGamePad()->GetGameStickRXPress(m_nPlayerIdx) < 0)
			{ // 右スティックを右に倒した場合

			  // カメラの向きを減算する
				m_CameraRot.y -= CAMERA_ROT_MOVE;
			}
			if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_RSHIFT) == true ||
				CManager::Get()->GetInputGamePad()->GetGameStickRXPress(m_nPlayerIdx) > 0)
			{ // 右スティックを右に倒した場合

			  // カメラの向きを加算する
				m_CameraRot.y += CAMERA_ROT_MOVE;
			}

			// 向きの正規化
			useful::RotNormalize(&m_CameraRot.y);
		}
	}
	else
	{
		CMultiCamera *pCamera = CManager::Get()->GetMlutiCamera(m_nPlayerIdx);
		D3DXVECTOR3 Pos = GetPos();

		if (m_type == TYPE::TYPE_CAT)
		{ //猫のカメラの位置
			pCamera->SetPosR(D3DXVECTOR3(
				Pos.x,
				Pos.y + CAT_CAMERA_HEIGHT,
				Pos.z
			));
			pCamera->SetPosV(D3DXVECTOR3(
				Pos.x + sinf(m_CameraRot.y + (D3DX_PI * 1.0f)) * 200.0f,
				Pos.y + CAT_CAMERA_HEIGHT + CAT_CAMERA_DIS,
				Pos.z + cosf(m_CameraRot.y + (D3DX_PI * 1.0f)) * 200.0f));
		}
		else
		{ //ネズミのカメラの位置
			pCamera->SetPosR(D3DXVECTOR3(
				Pos.x,
				Pos.y + RAT_CAMERA_HEIGHT,
				Pos.z
			));
			pCamera->SetPosV(D3DXVECTOR3(
				Pos.x + sinf(m_CameraRot.y + (D3DX_PI * 1.0f)) * 200.0f,
				Pos.y + RAT_CAMERA_HEIGHT + RAT_CAMERA_DIS,
				Pos.z + cosf(m_CameraRot.y + (D3DX_PI * 1.0f)) * 200.0f));
		}

		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LSHIFT) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickRXPress(m_nPlayerIdx) < 0)
		{ // 右スティックを右に倒した場合

			// カメラの向きを減算する
			m_CameraRot.y -= CAMERA_ROT_MOVE;
		}
		if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_RSHIFT) == true ||
			CManager::Get()->GetInputGamePad()->GetGameStickRXPress(m_nPlayerIdx) > 0)
		{ // 右スティックを右に倒した場合

			// カメラの向きを加算する
			m_CameraRot.y += CAMERA_ROT_MOVE;
		}

		// 向きの正規化
		useful::RotNormalize(&m_CameraRot.y);
	}
#endif // _DEBUG

	CMultiCamera *pCamera = CManager::Get()->GetMlutiCamera(m_nPlayerIdx);
	D3DXVECTOR3 Pos = GetPos();

	if (m_type == TYPE::TYPE_CAT)
	{ //猫のカメラの位置
		pCamera->SetPosR(D3DXVECTOR3(
			Pos.x,
			Pos.y + CAT_CAMERA_HEIGHT,
			Pos.z
		));
		pCamera->SetPosV(D3DXVECTOR3(
			Pos.x + sinf(m_CameraRot.y + (D3DX_PI * 1.0f)) * 200.0f,
			Pos.y + CAT_CAMERA_HEIGHT + CAT_CAMERA_DIS,
			Pos.z + cosf(m_CameraRot.y + (D3DX_PI * 1.0f)) * 200.0f));
	}
	else
	{ //ネズミのカメラの位置
		pCamera->SetPosR(D3DXVECTOR3(
			Pos.x,
			Pos.y + RAT_CAMERA_HEIGHT,
			Pos.z
		));
		pCamera->SetPosV(D3DXVECTOR3(
			Pos.x + sinf(m_CameraRot.y + (D3DX_PI * 1.0f)) * 200.0f,
			Pos.y + RAT_CAMERA_HEIGHT + RAT_CAMERA_DIS,
			Pos.z + cosf(m_CameraRot.y + (D3DX_PI * 1.0f)) * 200.0f));
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LSHIFT) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickRXPress(m_nPlayerIdx) < 0)
	{ // 右スティックを右に倒した場合

	  // カメラの向きを減算する
		m_CameraRot.y -= CAMERA_ROT_MOVE;
	}
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_RSHIFT) == true ||
		CManager::Get()->GetInputGamePad()->GetGameStickRXPress(m_nPlayerIdx) > 0)
	{ // 右スティックを右に倒した場合

	  // カメラの向きを加算する
		m_CameraRot.y += CAMERA_ROT_MOVE;
	}

	// 向きの正規化
	useful::RotNormalize(&m_CameraRot.y);
}

//=======================================
// 向きの補正処理
//=======================================
void CPlayer::RotNormalize(void)
{
	// 向きを取得する
	D3DXVECTOR3 rot = GetRot();

	// 向きの補正処理
	useful::RotCorrect(m_fRotDest, &rot.y, DIFF_ROT);

	// 向きを適用する
	SetRot(rot);
}

////=======================================
//// 攻撃処理
////=======================================
//void CPlayer::Attack(void)
//{
//	// ローカル変数宣言
//	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();		// 先頭の障害物を取得する
//	D3DXVECTOR3 pos = GetPos();
//	D3DXVECTOR3 rot = GetRot();
//
//	if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_B,m_nRatIdx) == true/* && m_bAttack == false*/)
//	{ // Bボタンを押した場合
//
//		while (pObstacle != nullptr)
//		{ // ブロックの情報が NULL じゃない場合
//
//			if (useful::RectangleCollisionXY(D3DXVECTOR3(pos.x + sinf(rot.y) * ATTACK_DISTANCE, pos.y, pos.z + cosf(rot.y) * ATTACK_DISTANCE), pObstacle->GetPos(),
//				SIZE, pObstacle->GetFileData().vtxMax,
//				-SIZE, pObstacle->GetFileData().vtxMin) == true)
//			{ // XYの矩形に当たってたら
//
//				if (useful::RectangleCollisionXZ(D3DXVECTOR3(pos.x + sinf(rot.y) * ATTACK_DISTANCE, pos.y, pos.z + cosf(rot.y) * ATTACK_DISTANCE), pObstacle->GetPos(),
//					SIZE, pObstacle->GetFileData().vtxMax,
//					-SIZE, pObstacle->GetFileData().vtxMin) == true)
//				{ // XZの矩形に当たってたら
//
//					// 障害物の終了処理
//					pObstacle->Uninit();
//				}
//			}
//
//			// 次のオブジェクトを代入する
//			pObstacle = pObstacle->GetNext();
//		}
//
//		//m_bAttack = true;		// 攻撃した状態にする
//	}
//}

//=======================================
// 気絶処理
//=======================================
bool CPlayer::Stun(int StunTime)
{
	if (m_StunState == STUNSTATE_NONE &&
		m_State == STATE_NONE)
	{ // 通常状態だった場合

		// バイブレーションを設定する
		CManager::Get()->GetInputGamePad()->GetRightVibration(GetPlayerIdx(), STUN_VIBRATE, StunTime);
		CManager::Get()->GetInputGamePad()->GetLeftVibration(GetPlayerIdx(), STUN_VIBRATE, StunTime);

		// 気絶状態にする
		m_StunState = STUNSTATE_STUN;
		m_StunStateCount = StunTime;

		if (CManager::Get()->GetMode() == CScene::MODE_TUTORIAL)
		{
			for (int nCnt = 0; nCnt < 4; nCnt++)
			{
				CTutorial::GetPlayer(nCnt)->SetLog(m_nPlayerIdx, CLog::TYPE::TYPE_STUN);
			}
		}
		else if (CManager::Get()->GetMode() == CScene::MODE_GAME)
		{
			for (int nCnt = 0; nCnt < 4; nCnt++)
			{
				CGame::GetPlayer(nCnt)->SetLog(m_nPlayerIdx, CLog::TYPE::TYPE_STUN);
			}
		}

		// 気絶演出の設定処理
		SetStun(GetPos());

		// true(気絶できた) を返す
		return true;
	}
	else
	{ // 上記以外

		// false(気絶失敗) を返す
		return false;
	}

	////猫とネズミで気絶の仕様を変える場合は使って
	//if (m_type == TYPE_CAT)
	//{ // 猫の場合
	//}
	//else if (m_type == TYPE_RAT)
	//{ // ネズミの場合
	//}
}

//=======================================
// アイテムの取得処理
//=======================================
void CPlayer::GetItem(const CItem::TYPE type)
{

}

//=======================================
// アイテムの総数の取得処理
//=======================================
int CPlayer::GetItemCount(void) const
{
	// 停止
	assert(false);

	// 0を返す
	return 0;
}

//=======================================
// ジャンプの設定処理
//=======================================
void CPlayer::SetEnableJump(const bool bJump)
{

}

//=======================================
// 気絶状態の管理
//=======================================
void CPlayer::StunStateManager(void)
{
	switch (m_StunState)
	{
	case STUNSTATE_NONE:	// 無状態

		break;

	case STUNSTATE_SMASH:	// 吹き飛び状態

		// 色の設定
		m_col = SMASH_COLOR;

		if (m_StunStateCount >= 38)
		{ // 一定時間以上だったら

			m_bDispSmash = true;
		}
		else if (m_bDispSmash == true)
		{ // 色付きで表示してたら

			// 色を表示しない状態にする
			m_bDispSmash = false;
		}

		// カウントを減算する
		m_StunStateCount--;

		if (m_StunStateCount <= 0)
		{ // カウントが一定数以下になった場合

			// 気絶状態にする
			m_StunState = STUNSTATE_STUN;
			SetRatStun(true);

			if (m_type == TYPE_CAT && m_bCatSe == false)
			{
				// にゃ～ん再生
				CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_CATDAMAGE);

				m_bCatSe = true;
			}

			// スタン時間の設定
			if (m_type == TYPE::TYPE_CAT)
			{// ネコの場合
				m_StunStateCount = CAT_SMASH_STUN;

				// バイブレーションを設定する
				CManager::Get()->GetInputGamePad()->GetRightVibration(GetPlayerIdx(), STUN_VIBRATE, CAT_SMASH_STUN);
				CManager::Get()->GetInputGamePad()->GetLeftVibration(GetPlayerIdx(), STUN_VIBRATE, CAT_SMASH_STUN);
			}
			else if (m_type == TYPE::TYPE_RAT)
			{// ネズミの場合
				m_StunStateCount = RAT_SMASH_STUN;

				// バイブレーションを設定する
				CManager::Get()->GetInputGamePad()->GetRightVibration(GetPlayerIdx(), STUN_VIBRATE, RAT_SMASH_STUN);
				CManager::Get()->GetInputGamePad()->GetLeftVibration(GetPlayerIdx(), STUN_VIBRATE, RAT_SMASH_STUN);
			}

			if (CManager::Get()->GetMode() == CScene::MODE_TUTORIAL)
			{
				for (int nCnt = 0; nCnt < 4; nCnt++)
				{
					CTutorial::GetPlayer(nCnt)->SetLog(m_nPlayerIdx, CLog::TYPE::TYPE_STUN);
				}
			}
			else if (CManager::Get()->GetMode() == CScene::MODE_GAME)
			{
				for (int nCnt = 0; nCnt < 4; nCnt++)
				{
					CGame::GetPlayer(nCnt)->SetLog(m_nPlayerIdx, CLog::TYPE::TYPE_STUN);
				}
			}

			// 気絶演出の設定処理
			SetStun(GetPos());
		}

		// 移動状況を false にする
		m_bMove = false;

		break;

	case STUNSTATE_STUN:	//気絶状態

		if (m_pStun != NULL)
		{
			m_pStun->SetPos(D3DXVECTOR3(GetPos().x, GetPos().y + m_fStunHeight, GetPos().z));
		}

		if (m_type == TYPE_RAT && m_bRatSe == false)
		{
			// チュッ再生
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_CHU);
			m_bRatSe = true;
		}
		else if (m_type == TYPE_CAT && m_bCatSe == false)
		{
			// にゃ～ん再生
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_CATDAMAGE);

			m_bCatSe = true;
		}

		// カウントを減算する
		m_StunStateCount--;

		if (m_StunStateCount <= 0)
		{ // カウントが一定数以下になった場合

			// 無敵状態にする
			m_StunState = STUNSTATE_WAIT;
			m_StunStateCount = STUN_WAIT;
			m_bSe = false;

			if (m_type == TYPE_RAT)
			{
				m_bRatSe = false;

			}
			else if (m_type == TYPE_CAT)
			{
				m_bCatSe = false;

			}

			if (m_pStun != nullptr)
			{ // 気絶演出が NULL の場合

				// 気絶演出を削除する
				m_pStun->Uninit();
				m_pStun = nullptr;
			}
		}
		else
		{
			if (m_bSe == false)
			{ // SE再生してない
				// ピヨピヨ再生
				CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_PIYOPIYO);
				m_bSe = true;
			}
		}

		// 移動状況を false にする
		m_bMove = false;

		break;

	case STUNSTATE_WAIT:	//障害物のみ無敵状態

		if ((m_StunStateCount % STUN_FLASH_INTERVAL) == 0)
		{ // 一定時間経ったら

			// 表示状態切り替え
			m_bDisp = m_bDisp ? false : true;
		}

		m_StunStateCount--;

		if (m_StunStateCount <= 0)
		{ // カウントが一定数以下になった場合
			m_StunState = STUNSTATE_NONE;
			m_bDisp = true;		// 表示する状態にする
		}

		break;

	default:

		// 停止
		assert(false);

		break;
	}
}

//=======================================
// 状態の管理
//=======================================
void CPlayer::StateManager(void)
{
	switch (m_State)
	{
	case STATE_NONE:

		break;

	case STATE_INVINCIBLE:	//無敵状態

		// カウントを減算する
		m_StateCount--;

		if ((m_StateCount % DEATH_FLASH_INTERVAL) == 0)
		{ // 一定時間経ったら

			// 表示状態切り替え
			m_bDisp = m_bDisp ? false : true;
		}

		if (m_StateCount <= 0)
		{ // カウントが一定数以下になった場合
			
			// 無状態にする
			m_State = STATE_NONE;
			m_bDisp = true;		// 表示する状態にする
		}
		break;

	case STATE_DEATH:	//死亡状態

		D3DXVECTOR3 pos = GetPos();		// 位置取得

		m_bDisp = false;		// 表示しない状態にする

		if (m_pRatGhost != nullptr)
		{ // 幽霊ネズミが NULL じゃないとき

			// 幽霊ネズミの位置設定
			m_pRatGhost->SetPos(pos);
		}

		if (m_pRessrectionFan != nullptr)
		{ // 円の範囲が NULL じゃないとき

			// 円の範囲の位置設定
			m_pRessrectionFan->SetPos(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z));
		}

		if (m_pRecoveringUI != nullptr)
		{ // 回復中UIが NULL じゃないとき

			// 回復中UIの位置設定
			m_pRecoveringUI->SetPos(D3DXVECTOR3(pos.x + 80.0f, pos.y + 100.0f, pos.z));

			// 回復中UIの前回の位置設定
			m_pRecoveringUI->SetPosOld(GetPosOld());

		}

		if (m_pSpeechMessage != nullptr)
		{ // 伝達メッセージが NULL じゃないとき

			// 伝達メッセージの位置設定
			m_pSpeechMessage->SetPos(D3DXVECTOR3(pos.x, pos.y + 120.0f, pos.z));
		}

		break;
	}
}

//=======================================
// ログの生成番号の加算
//=======================================
void CPlayer::SetLog(int PlayerIdx, CLog::TYPE Type)
{
	for (int nCnt = 0; nCnt < LOG_MAX; nCnt++)
	{
		if (m_apLog[nCnt] == NULL)
		{
			m_apLog[nCnt] = CLog::Create(m_nPlayerIdx, PlayerIdx, m_nLogNumber, Type);
			m_apLog[nCnt]->SetLogIdx(nCnt);
			m_apLog[nCnt]->SetMain(this);
			break;
		}
	}

	m_nLogNumber++;
}

//=======================================
// ログの生成番号の減算
//=======================================
void CPlayer::DelLogNumber(int nLogIdex)
{
	m_nLogNumber--;

	if (m_apLog[nLogIdex] != NULL)
	{
		m_apLog[nLogIdex]->Uninit();
		m_apLog[nLogIdex] = NULL;
	}

	for (int nCnt = 0; nCnt < LOG_MAX; nCnt++)
	{
		if (m_apLog[nCnt] != NULL)
		{
			m_apLog[nCnt]->DelCreateNumber();
		}
	}
}

//=======================================
// 状態の設定処理
//=======================================
void CPlayer::SetState(STATE State)
{
	m_State = State;

	if (CManager::Get()->GetMode() == CScene::MODE_TUTORIAL)
	{
		if (State == STATE_DEATH)
		{
			for (int nCnt = 0; nCnt < 4; nCnt++)
			{
				CTutorial::GetPlayer(nCnt)->SetLog(m_nPlayerIdx, CLog::TYPE::TYPE_DEATH);
			}
		}
		else if (State == STATE_INVINCIBLE)
		{
			for (int nCnt = 0; nCnt < 4; nCnt++)
			{
				CTutorial::GetPlayer(nCnt)->SetLog(m_nPlayerIdx, CLog::TYPE::TYPE_REVIVAL);
			}
		}
	}
	else if (CManager::Get()->GetMode() == CScene::MODE_GAME)
	{
		if (State == STATE_DEATH)
		{
			for (int nCnt = 0; nCnt < 4; nCnt++)
			{
				CGame::GetPlayer(nCnt)->SetLog(m_nPlayerIdx, CLog::TYPE::TYPE_DEATH);
			}
		}
		else if (State == STATE_INVINCIBLE)
		{
			for (int nCnt = 0; nCnt < 4; nCnt++)
			{
				CGame::GetPlayer(nCnt)->SetLog(m_nPlayerIdx, CLog::TYPE::TYPE_REVIVAL);
			}
		}

	}
}

//=======================================
// モーションの設定処理
//=======================================
void CPlayer::SetMotion(CMotion* pMotion)
{
	// モーションの情報を設定する
	m_pMotion = pMotion;
}

//=======================================
// モーションの取得処理
//=======================================
CMotion* CPlayer::GetMotion(void) const
{
	// モーションの情報を返す
	return m_pMotion;
}

//=======================================
// プレイヤーのIDの取得処理
//=======================================
CPlayerID* CPlayer::GetPlayerID(void) const
{
	// プレイヤーのIDの情報を返す
	return m_pPlayerID;
}

//=======================================
// 気絶演出の設定処理
//=======================================
void CPlayer::SetStun(const D3DXVECTOR3& pos)
{
	if (m_pStun == nullptr)
	{ // 気絶演出が NULL の場合

		// 気絶演出を生成する
		m_pStun = CStun::Create(D3DXVECTOR3(pos.x, pos.y + m_fStunHeight, pos.z));
	}
}

//=======================================
// 気絶演出の取得処理
//=======================================
CStun* CPlayer::GetStun(void) const
{
	// 気絶の情報を返す
	return m_pStun;
}

//=======================================
// 気絶演出の消去処理
//=======================================
void CPlayer::DeleteStun(void)
{
	if (m_pStun != nullptr)
	{ // 気絶の情報が NULL じゃない場合

		// 気絶の終了処理
		m_pStun->Uninit();
		m_pStun = nullptr;
	}
}

//=======================================
// 幽霊ネズミの設定処理
//=======================================
void CPlayer::SetRatGhost(const D3DXVECTOR3& pos)
{
	if (m_pRatGhost == nullptr)
	{ // 幽霊ネズミが NULL のとき

		// ネズミの幽霊の生成
		m_pRatGhost = CRatGhost::Create(pos);
	}
}

//=======================================
// 幽霊ネズミの情報取得処理
//=======================================
CRatGhost* CPlayer::GetRatGhost(void)
{
	// 幽霊ネズミの情報を返す
	return m_pRatGhost;
}

//=======================================
// 幽霊ネズミの情報消去処理
//=======================================
void CPlayer::DeleteRatGhost(void)
{
	if (m_pRatGhost != nullptr)
	{ // 幽霊ネズミが NULL じゃない場合

		//幽霊ネズミの終了処理
		m_pRatGhost->Uninit();
		m_pRatGhost = nullptr;
	}
}

//=======================================
// 円の範囲の設定処理
//=======================================
void CPlayer::SetRessrectionFan(const D3DXVECTOR3& pos, const D3DXCOLOR& col)
{
	if (m_pRessrectionFan == nullptr)
	{ // 円の範囲が NULL のとき

		// 生き返りの円の範囲生成
		m_pRessrectionFan = CRessrectionFan::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, pos.z), col);
	}
}

//=======================================
// 円の範囲の情報取得処理
//=======================================
CRessrectionFan* CPlayer::GetRessrectionFan(void)
{
	// 円の範囲の情報を返す
	return m_pRessrectionFan;
}

//=======================================
// 円の範囲の情報消去処理
//=======================================
void CPlayer::DeleteRessrectionFan(void)
{
	if (m_pRessrectionFan != nullptr)
	{ // 円の範囲が NULL じゃない場合

		//円の範囲の終了処理
		m_pRessrectionFan->Uninit();
		m_pRessrectionFan = nullptr;
	}
}

//=======================================
// 回復中UIの設定処理
//=======================================
void CPlayer::SetRecoveringUI(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld)
{
	if (m_pRecoveringUI == nullptr)
	{ // 回復中UIが NULL のとき

		// 回復中UIの範囲生成
		m_pRecoveringUI = CRecoveringUI::Create(D3DXVECTOR3(pos.x + 80.0f, pos.y + 100.0f, pos.z), posOld);
	}
}

//=======================================
// 回復中UIの情報取得処理
//=======================================
CRecoveringUI* CPlayer::GetRecoveringUI(void)
{
	// 回復中UIの情報を返す
	return m_pRecoveringUI;
}

//=======================================
// 回復中UIの情報消去処理
//=======================================
void CPlayer::DeleteRecoveringUI(void)
{
	if (m_pRecoveringUI != nullptr)
	{ // 回復中UIが NULL じゃない場合

		//回復中UIの終了処理
		m_pRecoveringUI->Uninit();
		m_pRecoveringUI = nullptr;
	}
}

//=======================================
// 伝達メッセージの設定処理
//=======================================
void CPlayer::SetSpeechMessage(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const int nLife, const int type)
{
	if (m_pSpeechMessage == nullptr)
	{ // 伝達メッセージが NULLのとき

		m_pSpeechMessage = CSpeechMessage::Create(pos, size, nLife, (CSpeechMessage::TYPE)type,(int)m_nPlayerIdx);
	}
}

//=======================================
// 伝達メッセージの取得処理
//=======================================
CSpeechMessage* CPlayer::GetSpeechMessage(void)
{
	// 伝達メッセージを返す
	return m_pSpeechMessage;
}

//=======================================
// 伝達メッセージの消去処理
//=======================================
void CPlayer::DeleteSpeechMessage(void)
{
	if (m_pSpeechMessage != nullptr)
	{ // 伝達メッセージが NULL じゃないとき

		// 伝達メッセージの終了処理
		m_pSpeechMessage->Uninit();
		m_pSpeechMessage = nullptr;
	}
}

//=======================================
// 死亡矢印の設定処理
//=======================================
void CPlayer::SetDeathArrow(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& rot, const int nIdx, const int PlayerIdx)
{
	if (m_pDeathArrow[nIdx] == nullptr)
	{ // 死亡矢印が NULL の時

	  // 死亡矢印の生成
		m_pDeathArrow[nIdx] = CDeathArrow::Create(pos, posOld, rot, PlayerIdx);
	}
	else if (m_pDeathArrow[nIdx] != nullptr)
	{ // 死亡矢印が NULL じゃないとき

		m_pDeathArrow[nIdx]->SetPos(pos);			// 位置設定
		m_pDeathArrow[nIdx]->SetPosOld(posOld);		// 前回の位置設定
		m_pDeathArrow[nIdx]->SetRot(rot);			// 向き設定
	}
}

//=======================================
// 死亡矢印の取得処理
//=======================================
CDeathArrow* CPlayer::GetDeathArrow(const int nIdx)
{
	// 死亡矢印の情報を返す
	return m_pDeathArrow[nIdx];
}

//=======================================
// 死亡矢印の消去処理
//=======================================
void CPlayer::DeleteDeathArrow(const int nIdx)
{
	if (m_pDeathArrow[nIdx] != nullptr)
	{ // 死亡矢印が NULL じゃない時

	  // 死亡矢印の終了処理
		m_pDeathArrow[nIdx]->Uninit();
		m_pDeathArrow[nIdx] = nullptr;
	}
}

//=======================================
// 移動量の設定処理
//=======================================
//void CPlayer::SetMove(const D3DXVECTOR3& move)
//{
//	// 移動量を設定する
//	m_move = move;
//}

//=======================================
// 移動量の取得処理
//=======================================
//D3DXVECTOR3 CPlayer::GetMove(void) const
//{
//	// 移動量を返す
//	return m_move;
//}

//=======================================
// 当たり判定サイズの設定処理
//=======================================
void CPlayer::SetSizeColl(const D3DXVECTOR3& size)
{
	// 当たり判定のサイズを設定する
	m_sizeColl = size;
}

//=======================================
// 当たり判定サイズの取得処理
//=======================================
D3DXVECTOR3 CPlayer::GetSizeColl(void) const
{
	// 当たり判定サイズを返す
	return m_sizeColl;
}

//=======================================
// 種類の設定処理
//=======================================
void CPlayer::SetType(const TYPE type)
{
	// 種類を設定する
	m_type = type;
}

//=======================================
// 種類の取得処理
//=======================================
CPlayer::TYPE CPlayer::GetType(void) const
{
	// 種類を返す
	return m_type;
}

//=======================================
// プレイヤーのIDの取得処理
//=======================================
int CPlayer::GetPlayerIdx(void) const
{
	// プレイヤーのインデックスを返す
	return m_nPlayerIdx;
}

//=======================================
// 速度の設定処理
//=======================================
void CPlayer::SetSpeed(const float fSpeed)
{
	// 速度を設定する
	m_fSpeed = fSpeed;
}

//=======================================
// 速度の取得処理
//=======================================
float CPlayer::GetSpeed(void) const
{
	// 速度を返す
	return m_fSpeed;
}

//=======================================
// 速度のコピーの設定処理
//=======================================
void CPlayer::SetSpeedCopy(const float fSpeed)
{
	// 速度のコピーを設定する
	m_fSpeedCopy = fSpeed;
}

//=======================================
// 速度のコピーの取得処理
//=======================================
float CPlayer::GetSpeedCopy(void) const
{
	// 速度のコピーを返す
	return m_fSpeedCopy;
}

//=======================================
// 気絶の出る高さの設定処理
//=======================================
void CPlayer::SetStunHeight(const float fHeight)
{
	// 気絶の出る高さを設定する
	m_fStunHeight = fHeight;
}

//=======================================
// 攻撃判定の設定処理
//=======================================
void CPlayer::SetEnableAttack(const bool bAttack)
{
	// 攻撃判定を設定する
	m_bAttack = bAttack;
}

//=======================================
// 攻撃判定の取得処理
//=======================================
bool CPlayer::IsAttack(void) const
{
	// 攻撃判定を返す
	return m_bAttack;
}

//=======================================
// 移動状況の設定処理
//=======================================
void CPlayer::SetEnableMove(const bool bMove)
{
	// 移動状況を設定する
	m_bMove = bMove;
}

//=======================================
// 移動状況の取得処理
//=======================================
bool CPlayer::IsMove(void) const
{
	// 移動状況を返す
	return m_bMove;
}

//=======================================
// 死んだネズミの復活時間の合計設定
//=======================================
void CPlayer::SetResurrectionTime(const int nRezTime)
{
	// 復活時間の合計設定
	m_nResurrectionTime = nRezTime;
}

//=======================================
// 死んだネズミの復活時間の合計追加
//=======================================
void CPlayer::AddResurrectionTime(const int nRezTime)
{
	// 復活時間の合計加算
	m_nResurrectionTime += nRezTime;
}

//=======================================
// 死んだネズミの復活時間の合計取得
//=======================================
int CPlayer::GetResurrectionTime(void)
{
	// 復活時間の合計を返す
	return m_nResurrectionTime;
}

//=======================================
// 回復中表示の判定
//=======================================
void CPlayer::SetDispRecoveringUI(const bool bRez)
{
	if (m_pRecoveringUI != nullptr)
	{ // 回復中UIが NULLじゃなかったら

		// 回復状態を設定する
		m_pRecoveringUI->SetDisplayUI(bRez);
	}
}

//=======================================
// 回復中表示の取得
//=======================================
bool CPlayer::IsDispRecoveringUI(void)
{
	// 回復状態を返す
	return m_pRecoveringUI->GetDisplayUI();
}

//=======================================
// SEの再生設定
//=======================================
void CPlayer::SetSE(bool bSe)
{
	if (m_StunState != STUNSTATE_STUN)
	{
		m_bSe = bSe;

	}
}

//=======================================
// SEの再生取得
//=======================================
bool CPlayer::GetSE(void)
{ 
	return m_bSe; 
}