//===========================================
//
// ラットのメイン処理[rat.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "rat.h"
#include "player.h"
#include "game.h"
#include "tutorial.h"
#include "result.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "useful.h"

#include "motion.h"
#include "player_idUI.h"
#include "stun.h"
#include "collision.h"
#include "elevation_manager.h"
#include "objectElevation.h"
#include "obstacle_manager.h"
#include "obstacle.h"
#include "Particle.h"
#include "rat_ghost.h"
#include "resurrection_fan.h"
#include "object3Dfan.h"
#include "recoveringUI.h"
#include "speech_message.h"
#include "sound.h"

//-------------------------------------------
// 無名名前空間
//-------------------------------------------
namespace
{
	const D3DXVECTOR3 COLLSIZE = D3DXVECTOR3(30.0f, 50.0f, 30.0f);		// 当たり判定でのサイズ
	const float GRAVITY = 1.2f;					// 重力
	const float ADD_MOVE_Y = 25.0f;				// ジャンプ力
	const float ATTACK_DISTANCE = 80.0f;			// 攻撃範囲までの距離
	const float MOVE_SPEED = 15.0f;				// 速度
	const float ARROW_DISTANCE = 100.0f;			// このネズミの矢印の距離
	const float STUN_HEIGHT = 80.0f;				// 気絶演出が出てくる高さ
	const float ID_HEIGHT = 110.0f;				// IDが出てくる高さ
	const int INVINCIBLE_COUNT = 60;				// 無敵カウント
	const WORD DEATH_VIBRATE = 50000;			// 死んだときのバイブレーションの強度
	const int DEATH_VIBRATE_COUNT = 20;			// 死んだときのバイブレーションのカウント数
}

//--------------------------------------------
// 静的メンバ変数宣言
//--------------------------------------------
bool CRat::m_bResurrection = false;		// 復活させてるのか

//==============================
// コンストラクタ
//==============================
CRat::CRat() : CPlayer(CObject::TYPE_PLAYER, CObject::PRIORITY_PLAYER)
{
	// 全ての値をクリアする
	m_nRezCounter = 0;					// 回復するまでのカウンター
	m_bJump = false;					// ジャンプ状況
	m_bSe = false;						// SE再生状況
}

//==============================
// デストラクタ
//==============================
CRat::~CRat()
{

}

//==============================
// ネズミの初期化処理
//==============================
HRESULT CRat::Init(void)
{
	if (FAILED(CPlayer::Init()))
	{ // 初期化処理に失敗した場合

		// 停止
		assert(false);

		// 失敗を返す
		return E_FAIL;
	}

	// ベタ打ち
	SetNumModel(6);

	// データの設定処理
	CCharacter::SetData();

	// モーションのポインタを宣言
	CMotion* pMotion = nullptr;

	if (pMotion == nullptr)
	{ // モーションが NULL だった場合

		// モーションの生成処理
		pMotion = CMotion::Create();
	}
	else
	{ // ポインタが NULL じゃない場合

		// 停止
		assert(false);
	}

	if (pMotion != nullptr)
	{ // ポインタが NULL じゃない場合

		// モーションの情報を取得する
		pMotion->SetModel(GetHierarchy(), GetNumModel());

		// ロード処理
		pMotion->Load(CMotion::TYPE_RAT);
	}
	else
	{ // ポインタが NULL じゃない場合

	  // 停止
		assert(false);
	}

	// モーションの設定処理
	pMotion->Set(MOTIONTYPE_NEUTRAL);

	// モーションの情報を設定する
	SetMotion(pMotion);

	// 全ての値を初期化する
	m_bJump = false;				// ジャンプ状況
	m_bSe = false;						// SE再生状況

	// 値を返す
	return S_OK;
}

//========================================
// ネズミの終了処理
//========================================
void CRat::Uninit(void)
{
	// 終了処理
	CPlayer::Uninit();
}

//=====================================
// ネズミの更新処理
//=====================================
void CRat::Update(void)
{
	// 前回の位置を設定する
	SetPosOld(GetPos());

	if (CPlayer::GetStunState() != CPlayer::STUNSTATE_STUN &&
		CPlayer::GetState() != CPlayer::STATE_DEATH)
	{ // 気絶状態or死亡状態じゃない場合

		if (GetTutorial() != true)
		{
			// ジャンプ処理
			Jump();

			if (GetStunState() != STUNSTATE_SMASH)
			{ // 吹き飛び状態の場合

				// 移動操作処理
				MoveControl();
			}

			//// 攻撃処理
			//Attack();

			// 生き返りの当たり判定
			ResurrectionCollision();

			//移動処理
			Move();
		}

		// モーションの設定処理
		MotionManager();
	}
	else
	{
		// 移動量を初期化する
		SetMove(NONE_D3DXVECTOR3);
	}

	// 重力処理
	Gravity();

	// 死亡矢印の処理
	DeathArrow();

	// 起伏地面の当たり判定
	Elevation();

	// 角度の正規化
	RotNormalize();

	// プレイヤーの更新処理
	CPlayer::Update();

	// 障害物との衝突判定
	if (collision::ObstacleCollision(this, GetSizeColl().x, GetSizeColl().y, GetSizeColl().z) == true)
	{ // 上に乗った場合

		// ジャンプ状況を false にする
		m_bJump = false;
	}

	// ブロックとの当たり判定
	if (collision::BlockCollision(this, GetSizeColl()) == true)
	{ // 上に乗った場合

		// ジャンプ状況を false にする
		m_bJump = false;
	}

	if (GetMove().y <= -GRAVITY)
	{ // 重力が一定以上あった場合(あとで修繕予定)

		// ジャンプしている
		m_bJump = true;
	}

	if (GetPlayerID() != nullptr)
	{ // プレイヤーのID表示が NULL じゃない場合

		// 位置を設定する
		GetPlayerID()->SetPos(D3DXVECTOR3(GetPos().x, GetPos().y + ID_HEIGHT, GetPos().z));
		GetPlayerID()->Update();
	}

	// デバッグ表示
	CManager::Get()->GetDebugProc()->Print("蘇生カウント：%d\n", CPlayer::GetResurrectionTime());
}

//=====================================
// ネズミの描画処理
//=====================================
void CRat::Draw(void)
{
	// 描画処理
	CPlayer::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CRat::MotionManager(void)
{
	// モーションの種類を取得する
	int nMotionType = GetMotion()->GetType();

	if (CManager::Get()->GetMode() == CScene::MODE_RESULT)
	{ // リザルト

		if (CResult::GetState() == CGame::STATE_RAT_WIN)
		{ // ねずみのかち

			if (nMotionType != MOTIONTYPE_WIN)
			{
				nMotionType = MOTIONTYPE_WIN;

				// モーションの設定処理
				GetMotion()->Set(nMotionType);
			}
		}
		else if (CResult::GetState() == CGame::STATE_CAT_WIN)
		{ // ねこのかち

			if (nMotionType != MOTIONTYPE_DEATH)
			{
				nMotionType = MOTIONTYPE_DEATH;

				// モーションの設定処理
				GetMotion()->Set(nMotionType);
			}
		}
	}
	else
	{ // リザルト以外のとき

		if (GetStunState() == STUNSTATE_SMASH)
		{
			if (nMotionType != MOTIONTYPE_KNOCKBACK)
			{
				nMotionType = MOTIONTYPE_KNOCKBACK;

				// モーションの設定処理
				GetMotion()->Set(nMotionType);
			}
		}
		else if (GetStunState() == STUNSTATE_STUN)
		{
			if (nMotionType != MOTIONTYPE_STUN)
			{
				nMotionType = MOTIONTYPE_STUN;

				// モーションの設定処理
				GetMotion()->Set(nMotionType);
			}
		}
		else if (m_bJump == true)
		{
			if (nMotionType != MOTIONTYPE_JUMP)
			{
				nMotionType = MOTIONTYPE_JUMP;

				// モーションの設定処理
				GetMotion()->Set(nMotionType);

				// ジャンプ再生
				CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_JUMP);
			}
		}
		else if (GetMove().x > 0.05f || GetMove().x < -0.05f ||
			GetMove().z > 0.05f || GetMove().z < -0.05f)
		{
			if (nMotionType != MOTIONTYPE_MOVE)
			{
				nMotionType = MOTIONTYPE_MOVE;

				// モーションの設定処理
				GetMotion()->Set(nMotionType);
			}
		}
		else if (m_bResurrection == true)
		{
			if (nMotionType != MOTIONTYPE_RESURRECTION)
			{
				nMotionType = MOTIONTYPE_RESURRECTION;

				// モーションの設定処理
				GetMotion()->Set(nMotionType);
			}
		}
		else
		{
			if (nMotionType != MOTIONTYPE_NEUTRAL)
			{
				nMotionType = MOTIONTYPE_NEUTRAL;

				// モーションの設定処理
				GetMotion()->Set(nMotionType);
			}
		}
	}
}

//=====================================
// ジャンプ状況の設定処理
//=====================================
void CRat::SetEnableJump(const bool bJump)
{
	// ジャンプ状況を設定する
	m_bJump = bJump;
}

//=====================================
// 情報の設定処理
//=====================================
void CRat::SetData(const D3DXVECTOR3& pos, const int nID, const TYPE type)
{
	// 情報の設定処理
	CPlayer::SetData(pos, nID, type);

	if (GetPlayerID() != nullptr)
	{ // プレイヤーのIDが NULL じゃない場合

		// 位置を設定する
		GetPlayerID()->SetPos(D3DXVECTOR3(pos.x, pos.y + ID_HEIGHT, pos.z));
	}

	// 気絶が出る高さの設定
	SetStunHeight(STUN_HEIGHT);

	// 当たり判定のサイズの設定
	SetSizeColl(COLLSIZE);

	// 移動量を設定する
	SetSpeed(MOVE_SPEED);
	SetSpeedCopy(GetSpeed());

	// 情報を設定する
	m_bJump = false;				// ジャンプしたか

	for (int nCntData = 0; nCntData < GetNumModel(); nCntData++)
	{
		// 初期化処理
		GetHierarchy(nCntData)->SetPos(pos);										// 位置
		GetHierarchy(nCntData)->SetPosOld(pos);										// 前回の位置
		GetHierarchy(nCntData)->SetRot(NONE_D3DXVECTOR3);							// 向き
		GetHierarchy(nCntData)->SetScale(NONE_SCALE);								// 拡大率
		GetHierarchy(nCntData)->SetFileData(CXFile::TYPE(INIT_RAT + nCntData));		// データの設定処理
	}

	// モーションの設定処理
	GetMotion()->Set(MOTIONTYPE_NEUTRAL);

	// 強制モーション処理
	GetMotion()->SetForcibly();

	// モーションの更新処理(やらないと魑魅魍魎が誕生する)
	GetMotion()->Update();
}

//=======================================
// ジャンプ処理
//=======================================
void CRat::Jump(void)
{
	// ローカル変数宣言
	D3DXVECTOR3 move = GetMove();

	if ((CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_SPACE) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, GetPlayerIdx()) == true) &&
		GetStunState() != STUNSTATE_SMASH &&
		m_bJump == false)
	{ // Aボタンを押した場合

		move.y = ADD_MOVE_Y;	// 浮力代入

		m_bJump = true;		// ジャンプしてる状態にする
	}

	// 情報を適用する
	SetMove(move);
}

//=======================================
// 重力処理
//=======================================
void CRat::Gravity(void)
{
	// 移動量を取得する
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 move = GetMove();

	// 重力を加算する
	move.y -= GRAVITY;

	// 位置を移動する
	pos.y += move.y;

	// 移動量を適用する
	SetPos(pos);
	SetMove(move);
}

//=======================================
// 攻撃処理
//=======================================
void CRat::Attack(void)
{
	// ローカル変数宣言
	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();		// 先頭の障害物を取得する
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_B, GetPlayerIdx()) == true)
	{ // Bボタンを押した場合

		while (pObstacle != nullptr)
		{ // ブロックの情報が NULL じゃない場合

			if (useful::RectangleCollisionXY(D3DXVECTOR3(pos.x + sinf(rot.y) * ATTACK_DISTANCE, pos.y, pos.z + cosf(rot.y) * ATTACK_DISTANCE), pObstacle->GetPos(),
				COLLSIZE, pObstacle->GetFileData().vtxMax,
				-COLLSIZE, pObstacle->GetFileData().vtxMin) == true)
			{ // XYの矩形に当たってたら

				if (useful::RectangleCollisionXZ(D3DXVECTOR3(pos.x + sinf(rot.y) * ATTACK_DISTANCE, pos.y, pos.z + cosf(rot.y) * ATTACK_DISTANCE), pObstacle->GetPos(),
					COLLSIZE, pObstacle->GetFileData().vtxMax,
					-COLLSIZE, pObstacle->GetFileData().vtxMin) == true)
				{ // XZの矩形に当たってたら

					// 障害物の終了処理
					pObstacle->Uninit();
				}
			}

			// 次のオブジェクトを代入する
			pObstacle = pObstacle->GetNext();
		}
	}
}

//=======================================
// ヒット処理
//=======================================
void CRat::Hit(void)
{
	// ローカル変数宣言
	CPlayer *pPlayer;						// ネズミの情報
	D3DXVECTOR3 pos = GetPos();				// 位置を取得する
	STATE state = GetState();				// 状態を取得する
	int nCntDeath = 0;						// 死亡した数

	if (state == STATE_NONE)
	{ // ダメージ受ける状態だった場合

		// バイブレーションを設定する
		CManager::Get()->GetInputGamePad()->GetRightVibration(GetPlayerIdx(), DEATH_VIBRATE, DEATH_VIBRATE_COUNT);
		CManager::Get()->GetInputGamePad()->GetLeftVibration(GetPlayerIdx(), DEATH_VIBRATE, DEATH_VIBRATE_COUNT);

		CParticle::Create(pos, CParticle::TYPE_ENEMYDEATH); //パーティクル

		SetState(STATE_DEATH);				// 死亡状態にする

		// 生き返りの円の範囲生成
		CPlayer::SetRessrectionFan(pos, D3DXCOLOR(1.0f, 0.0f, 0.1f, 0.5f));

		// ネズミの幽霊の生成
		CPlayer::SetRatGhost(pos);

		// 回復中UIの生成
		CPlayer::SetRecoveringUI(pos, GetPosOld());

		// 伝達メッセージの表示
		CPlayer::SetSpeechMessage(D3DXVECTOR3(pos.x, pos.y + 120.0f, pos.z), D3DXVECTOR3(50.0f, 50.0f, 0.0f), -1, CSpeechMessage::TYPE_HELP);

		for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
		{
			if (CManager::Get()->GetMode() == CScene::MODE_TUTORIAL)
			{
				// プレイヤーの情報を取得する
				pPlayer = CTutorial::GetPlayer(nCnt);
			}
			else
			{
				// プレイヤーの情報を取得する
				pPlayer = CGame::GetPlayer(nCnt);
			}

			if (pPlayer != nullptr &&
				pPlayer->GetType() == TYPE_RAT && 
				pPlayer->GetState() == STATE_DEATH)
			{ // 死亡してるネズミの時

				nCntDeath++;
			}
		}

		if (nCntDeath >= (MAX_PLAY - 1))
		{ // ネズミ全匹死んだら

			// ネコが勝利した状態にする
			CGame::SetState(CGame::STATE_CAT_WIN);
		}

		// 攻撃のヒット音を鳴らす
		CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_CATATTACK_HIT);
	}
}

//=======================================
// 死亡矢印の処理
//=======================================
void CRat::DeathArrow(void)
{
	CPlayer *pPlayer;						// ネズミの情報
	STATE state = GetState();				// 状態を取得する
	D3DXVECTOR3 pos = GetPos();				// 位置取得
	D3DXVECTOR3 posOld = GetPosOld();		// 前回の位置取得
	bool abRez[MAX_PLAY];					// 復活してるか

	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		if (CManager::Get()->GetMode() == CScene::MODE_TUTORIAL)
		{
			// プレイヤーの情報を取得する
			pPlayer = CTutorial::GetPlayer(nCnt);
		}
		else
		{
			// プレイヤーの情報を取得する
			pPlayer = CGame::GetPlayer(nCnt);
		}

		abRez[nCnt] = false;

		if (pPlayer != nullptr &&
			pPlayer->GetType() == TYPE_RAT &&
			GetPlayerIdx() != pPlayer->GetPlayerIdx())
		{ // 操作してるネズミじゃないとき

			if (pPlayer->GetState() == STATE_DEATH && state != STATE_DEATH)
			{ // 他のネズミが死亡状態の時

				D3DXVECTOR3 DestPos = pos - pPlayer->GetPos();		// 目的の位置
				D3DXVECTOR3 DestRot = NONE_D3DXVECTOR3;				// 目的の向き

				// 目的の向きを求める
				DestRot.y = atan2f(-DestPos.z, DestPos.x);

				// 死亡矢印生成
				SetDeathArrow(D3DXVECTOR3(pos.x + sinf(DestRot.y + -D3DX_PI * 0.5f) * ARROW_DISTANCE,
					pos.y - 1.0f,
					pos.z + cosf(DestRot.y + -D3DX_PI * 0.5f) * ARROW_DISTANCE),
					posOld, DestRot, nCnt, GetPlayerIdx());

				// 回復させてる状態にする
				abRez[nCnt] = true;
			}

			if (abRez[nCnt] == false)
			{ // 生き返ったら

				// 死亡矢印消去
				DeleteDeathArrow(nCnt);
			}
		}
	}
}

//=======================================
// 起伏地面の当たり判定
//=======================================
void CRat::Elevation(void)
{
	// ローカル変数宣言
	CElevation* pMesh = CElevationManager::Get()->GetTop();		// 起伏の先頭のオブジェクトを取得する
	D3DXVECTOR3 pos = GetPos();				// 位置を取得する
	D3DXVECTOR3 move = GetMove();			// 移動量を取得する
	float fHeight = 0.0f;					// 高さ

	while (pMesh != nullptr)
	{ // 地面の情報がある限り回す

		// 当たり判定を取る
		fHeight = pMesh->ElevationCollision(pos);

		if (pos.y < fHeight)
		{ // 当たり判定の位置が高かった場合

			// 高さを設定する
			pos.y = fHeight;

			move.y = 0.0f;

			m_bJump = false;		// ジャンプしてない状態にする
		}

		// 次のポインタを取得する
		pMesh = pMesh->GetNext();
	}

	// 位置と移動量を更新する
	SetPos(pos);
	SetMove(move);
}

//=======================================
// 生き返りの当たり判定
//=======================================
void CRat::ResurrectionCollision(void)
{
	CPlayer *pPlayer = nullptr;				// ネズミの情報
	bool bCollXY = false;					// XYの範囲に入ったか
	bool bCollXZ = false;					// XZの範囲に入ったか
	bool abRez[MAX_PLAY];					// 回復してるか
	STATE state = GetState();				// 状態を取得する
	STUNSTATE stunState = GetStunState();	// 気絶状態を取得する

	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		if (CManager::Get()->GetMode() == CScene::MODE_TUTORIAL)
		{
			// プレイヤーの情報を取得する
			pPlayer = CTutorial::GetPlayer(nCnt);
		}
		else
		{
			// プレイヤーの情報を取得する
			pPlayer = CGame::GetPlayer(nCnt);
		}
		abRez[nCnt] = false;

		if (pPlayer != nullptr &&
			pPlayer->GetType() == TYPE_RAT &&
			GetPlayerIdx() != pPlayer->GetPlayerIdx())
		{ // 操作してるネズミじゃないとき

			if (pPlayer->GetState() == STATE_DEATH &&
				state != STATE_DEATH && 
				stunState != STUNSTATE::STUNSTATE_SMASH &&
				stunState != STUNSTATE::STUNSTATE_STUN)
			{ // 他のネズミが死亡状態 && 操作してるネズミが復活させれる状態の時

				// 円の当たり判定(XY平面)取得
				bCollXY = useful::CircleCollisionXY(GetPos(), pPlayer->GetPos(), 30.0f, ATTACK_DISTANCE);

				// 円の当たり判定(XZ平面)取得
				bCollXZ = useful::CircleCollisionXZ(GetPos(), pPlayer->GetPos(), 30.0f, ATTACK_DISTANCE);

				// 他のネズミとの当たり判定
				if (bCollXY == true && bCollXZ == true)
				{ // 円の当たり判定(XY平面)と(XZ平面)の範囲にいる場合

					if (m_bResurrection == false)
					{ // 復活させてない状態だったら

						// 復活させてる状態にする
						m_bResurrection = true;

						if (m_bSe == false)
						{
							// 回復中の音再生
							CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_REVIVAL_SAVE);
							m_bSe = true;
						}
					}

					// 復活パーティクル生成
					CParticle::Create(pPlayer->GetPos(), CParticle::TYPE_RESURRECTION);

					// 回復させてる状態にする
					abRez[nCnt] = true;

					// 現在の生き返りの時間取得
					m_nRezCounter = pPlayer->GetResurrectionTime();
							
					// 生き返りのカウンター加算
					m_nRezCounter++;

					// 回復中UI表示設定
					pPlayer->SetDispRecoveringUI(abRez[nCnt]);

					pPlayer->SetResurrectionTime(m_nRezCounter);

					if (pPlayer->GetResurrectionTime() >= NUM_REZ_ANGLE)
					{ // 一定時間経ったら

						// 無敵状態にする
						pPlayer->SetState(STATE_INVINCIBLE);
						pPlayer->SetStateCount(INVINCIBLE_COUNT);
						SetRatRescue(true);

						// 円の範囲の破棄
						pPlayer->DeleteRessrectionFan();

						// 幽霊ネズミの破棄
						pPlayer->DeleteRatGhost();

						// 回復中UIの破棄
						pPlayer->DeleteRecoveringUI();

						// 伝達メッセージの破棄
						pPlayer->DeleteSpeechMessage();

						// 生き返りのカウンター初期化
						pPlayer->SetResurrectionTime(0);
						m_nRezCounter = 0;

						// 復活させてない状態にする
						m_bResurrection = false;

						// 回復中の音停止
						CManager::Get()->GetSound()->Stop(CSound::SOUND_LABEL_SE_REVIVAL_SAVE);
						m_bSe = false;

						// 回復中の音再生
						CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_REVIVAL);
					}
				}
				else if (m_bResurrection == false && (bCollXY == false || bCollXZ == false))
				{ // 復活させてない状態 && 円の当たり判定(XY平面)か(XZ平面)の範囲にいない場合

					// 回復中UI表示設定
					pPlayer->SetDispRecoveringUI(false);

					// 回復中の音停止
					CManager::Get()->GetSound()->Stop(CSound::SOUND_LABEL_SE_REVIVAL_SAVE);
					m_bSe = false;

					if (pPlayer->GetResurrectionTime() > 0)
					{ // 生き返りのカウンターが加算されてたら

						pPlayer->AddResurrectionTime(-1);		// カウンター減算
					}
					else
					{ // 生き返りのカウンターが0以下だったら

						// 生き返りのカウンター初期化
						pPlayer->SetResurrectionTime(0);
					}
				}

				// 回復する範囲の情報取得
				CRessrectionFan *pResurrectionFan = pPlayer->GetRessrectionFan();

				if (pResurrectionFan != nullptr)
				{ // 回復する範囲が NULLのとき

					// 回復の範囲の時間設定
					pResurrectionFan->SetResurrectionFan(pPlayer->GetResurrectionTime());
				}
			}
		}
	}

	if (abRez[0] == false && abRez[1] == false && abRez[2] == false && abRez[3] == false)
	{ // 全員が誰も助けてないとき

		// 復活させてない状態にする
		m_bResurrection = false;
	}
}