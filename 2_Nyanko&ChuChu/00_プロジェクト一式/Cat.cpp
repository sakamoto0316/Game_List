//============================================
//
// 猫のメイン処理[Cat.cpp]
// Author：坂本翔唯
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "Cat.h"
#include "manager.h"
#include "game.h"
#include "tutorial.h"
#include "result.h"
#include "renderer.h"
#include "debugproc.h"
#include "input.h"
#include "model.h"
#include "sound.h"
#include "useful.h"
#include "texture.h"
#include "scene.h"

#include "camera.h"
#include "collision.h"
#include "elevation_manager.h"
#include "objectElevation.h"
#include "effect.h"
#include "Particle.h"
#include "motion.h"
#include "shadowCircle.h"
#include "destruction.h"
#include "ripple.h"
#include "obstacle_manager.h"
#include "rat.h"
#include "itemUI.h"
#include "item_mark.h"
#include "fraction.h"
#include "player_idUI.h"

//--------------------------------------------
// 無名名前空間
//--------------------------------------------
namespace
{
	const D3DXVECTOR3 ITEMUI_POS[MAX_PLAY] =			// アイテムUIの位置
	{
		D3DXVECTOR3(70.0f,50.0f,0.0f),
		D3DXVECTOR3(SCREEN_WIDTH - 70.0f,50.0f,0.0f),
		D3DXVECTOR3(70.0f,SCREEN_HEIGHT * 0.5f + 50.0f,0.0f),
		D3DXVECTOR3(SCREEN_WIDTH - 70.0f,SCREEN_HEIGHT * 0.5f + 50.0f,0.0f)
	};
	const D3DXVECTOR3 CAT_SIZE = D3DXVECTOR3(70.0f, 280.0f, 70.0f);		// 当たり判定のサイズ
	const float MOVE_SPEED = 20.0f;			// 移動速度
	const float ATTACK_DISTANCE = 100.0f;	// 攻撃範囲までの距離
	const float GRAVITY = 1.2f;				// 重力
	const float STUN_HEIGHT = 300.0f;		// 気絶演出が出てくる高さ
	const float ID_HEIGHT = 350.0f;			// IDが出てくる高さ
	const int STANDBY_COUNT = 12;			// スタンバイ状態のカウント数
	const int ATTACK_COUNT = 30;				// 攻撃状態のカウント数
}

//--------------------------------------------
// マクロ定義
//--------------------------------------------
#define ATTACK_SIZE		(D3DXVECTOR3(95.0f, 150.0f, 95.0f))		// 攻撃の判定の大きさ

//=========================================
// コンストラクタ
//=========================================
CCat::CCat() : CPlayer(CObject::TYPE_PLAYER, CObject::PRIORITY_PLAYER)
{
	// 全ての値をクリアする
	m_pItemUI = nullptr;			// アイテムUIの情報
	m_AttackPos = NONE_D3DXVECTOR3;	//攻撃の位置
	m_posDest = NONE_D3DXVECTOR3;	// 目的の位置
	m_rotDest = NONE_D3DXVECTOR3;	// 目的の向き
	m_nShadowIdx = INIT_SHADOW;		// 影のインデックス
	m_nItemCount = 0;				// アイテムの所持数
	m_nAtkTime = 0;
	m_bSE = false;					// SE再生してるか
}

//=========================================
// デストラクタ
//=========================================
CCat::~CCat()
{

}

//===========================================
// プレイヤーの初期化処理
//===========================================
HRESULT CCat::Init(void)
{
	if (FAILED(CPlayer::Init()))
	{ // 初期化処理に失敗した場合

	  // 停止
		assert(false);

		// 失敗を返す
		return E_FAIL;
	}

	if (CManager::Get()->GetMode() == CScene::MODE_RESULT && CResult::GetState() == CGame::STATE_RAT_WIN)
	{ // リザルト　ネコの負け
		// ベタ打ち
		SetNumModel(11);
	}
	else
	{
		// ベタ打ち
		SetNumModel(10);

	}

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
		pMotion->Load(CMotion::TYPE_CAT);
	}
	else
	{ // ポインタが NULL じゃない場合

	  // 停止
		assert(false);
	}

	// モーションの設定処理
	pMotion->Set(MOTIONTYPE_NEUTRAL);

	// モーション情報を設定する
	SetMotion(pMotion);

	// 全ての値を初期化する
	m_pItemUI = nullptr;			// アイテムUIの情報
	m_posDest = NONE_D3DXVECTOR3;	// 目的の位置
	m_rotDest = NONE_D3DXVECTOR3;	// 目的の向き
	m_nShadowIdx = INIT_SHADOW;		// 影のインデックス
	m_nItemCount = 0;				// アイテムの所持数
	m_bSE = false;					// SE再生してるか

	// 値を返す
	return S_OK;
}

//===========================================
// プレイヤーの終了処理
//===========================================
void CCat::Uninit(void)
{
	if (m_pItemUI != nullptr)
	{ // アイテムUIの情報が NULL じゃない場合
		
		// アイテムUIの終了処理
		m_pItemUI->Uninit();
		m_pItemUI = nullptr;
	}

	// 終了処理
	CPlayer::Uninit();
}

//===========================================
// 更新処理
//===========================================
void CCat::Update(void)
{
	// 前回の位置の設定処理
	SetPosOld(GetPos());

	if (CPlayer::GetStunState() != CPlayer::STUNSTATE_STUN &&
		CPlayer::GetState() != CPlayer::STATE_DEATH &&
		m_AttackState == ATTACKSTATE_MOVE)
	{// 移動状態の時

		if (GetTutorial() != true)
		{
			if (GetStunState() != STUNSTATE_SMASH)
			{ // 吹き飛び状態以外の場合

				// 移動操作処理
				MoveControl();

				// アイテムの設置処理
				ItemSet();
			}

			// 攻撃入力の処理
			Attack();

			// 移動処理
			Move();
		}
		// モーション状態の管理
		MotionManager();
	}
	else
	{
		// 移動量を初期化する
		SetMove(NONE_D3DXVECTOR3);
	}

	// 重力処理
	Gravity();

	// 攻撃状態の管理
	AttackStateManager();

	 // 影の位置向きの設定処理
	CShadowCircle::SetPosRot(m_nShadowIdx, GetPos(), GetRot());

	// アイテムとの当たり判定処理
	collision::ItemCollision(*this, m_nItemCount);

	// 起伏地面の当たり判定
	Elevation();

	// 角度の正規化
	RotNormalize();

	// 更新処理
	CPlayer::Update();

	// 障害物との衝突判定
	collision::ObstacleCollision(this, GetSizeColl().x, GetSizeColl().y, GetSizeColl().z);

	// ブロックとの当たり判定
	collision::BlockCollision(this, GetSizeColl());

	if (GetPlayerID() != nullptr)
	{ // プレイヤーのID表示が NULL じゃない場合

		// 位置を設定する
		GetPlayerID()->SetPos(D3DXVECTOR3(GetPos().x, GetPos().y + ID_HEIGHT, GetPos().z));
		GetPlayerID()->Update();
	}

	// デバッグ表示
	DebugMessage();
}

//===========================================
// プレイヤーの描画処理
//===========================================
void CCat::Draw(void)
{
	// 描画処理
	CPlayer::Draw();
}

//===========================================
// 重力処理
//===========================================
void CCat::Gravity(void)
{
	// 位置と移動量を取得する
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 move = GetMove();

	// 重力加算
	move.y -= GRAVITY;

	// 位置を移動する
	pos.y += move.y;

	// 情報を適用する
	SetPos(pos);		// 位置
	SetMove(move);		// 移動量
}

//===========================================
// 攻撃処理
//===========================================
void CCat::Attack(void)
{
	// ゲームモードの時だけ攻撃
	if (CManager::Get()->GetMode() == CScene::MODE_GAME || CManager::Get()->GetMode() == CScene::MODE_TUTORIAL)
	{
		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true ||
			CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, GetPlayerIdx()) == true)
		{ // ENTERキー(Aボタン)を押していた場合

			// 状態を攻撃準備にする
			m_AttackState = ATTACKSTATE_STANDBY;
			m_nAtkStateCount = STANDBY_COUNT;
		
			// ネコの攻撃音を流す
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_CATATTACK);
		}
	}
}

//===========================================
// 攻撃状態の管理
//===========================================
void CCat::AttackStateManager(void)
{
	// ローカル変数宣言
	CPlayer* pPlayer = nullptr;
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	switch (m_AttackState)
	{
	case ATTACKSTATE_MOVE:

		//CEffect::Create(m_AttackPos, NONE_D3DXVECTOR3, 1, 400.0f, CEffect::TYPE::TYPE_NONE, D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.8f), true);

		// SE再生しない状態にする
		SetSE(false);
		m_bSE = false;

		break;

	case ATTACKSTATE_STANDBY:

		//CEffect::Create(m_AttackPos, NONE_D3DXVECTOR3, 1, 400.0f, CEffect::TYPE::TYPE_NONE, D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f), true);

		if (m_nAtkStateCount <= 0)
		{//状態カウントが0になった時

			m_bAttack = true;		// 攻撃した状態にする
			m_AttackState = ATTACKSTATE_ATTACK;
			m_nAtkStateCount = ATTACK_COUNT;
			m_nAtkTime = 5;

			for (int nCnt = 0; nCnt < 10; nCnt++)
			{
				// 破片の生成
				CFraction::Create(D3DXVECTOR3(pos.x + sinf(rot.y) * -ATTACK_DISTANCE, pos.y, pos.z + cosf(rot.y) * -ATTACK_DISTANCE), CFraction::TYPE_CAT_ATTACK);
			}
		}
		break;

	case ATTACKSTATE_ATTACK:

		//CEffect::Create(m_AttackPos, NONE_D3DXVECTOR3, 1, 400.0f, CEffect::TYPE::TYPE_NONE, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), true);

		// ブロックへの攻撃処理
		AttackBlock();

		if (useful::CircleCollisionXZ(m_AttackPos, m_AttackPos,10.0f,10.0f) == true && m_nAtkTime > 0)
		{
			for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
			{
				if (CManager::Get()->GetMode() == CScene::MODE_GAME)
				{
					// プレイヤーの情報を取得する
					pPlayer = CGame::GetPlayer(nCnt);
				}
				if (CManager::Get()->GetMode() == CScene::MODE_TUTORIAL)
				{
					// プレイヤーの情報を取得する
					pPlayer = CTutorial::GetPlayer(nCnt);
				}

				if (pPlayer != nullptr &&
					pPlayer->GetType() == CPlayer::TYPE_RAT && pPlayer->GetState() != CPlayer::STUNSTATE_SMASH && pPlayer->GetState() != CPlayer::STUNSTATE_WAIT)
				{ // プレイヤーがネズミの場合

					if (useful::RectangleCollisionXZ(D3DXVECTOR3(pos.x + sinf(rot.y) * -ATTACK_DISTANCE, pos.y, pos.z + cosf(rot.y) * -ATTACK_DISTANCE),
						pPlayer->GetPos(),
						ATTACK_SIZE, D3DXVECTOR3(30.0f, 50.0f, 30.0f),
						D3DXVECTOR3(-ATTACK_SIZE.x, -ATTACK_SIZE.y, -ATTACK_SIZE.z), D3DXVECTOR3(-30.0f, -50.0f, -30.0f)) == true)
					{ // XZの矩形に当たってたら

						// プレイヤーのヒット処理
						pPlayer->Hit();
						SetRatKill(true);
					}
				}
			}
		}

		if (m_nAtkStateCount <= 0)
		{//状態カウントが0になった時
			m_AttackState = ATTACKSTATE_MOVE;
			m_bAttack = false;		// 攻撃してない状態にする
		}
		break;
	}

	if (m_nAtkStateCount > 0)
	{
		m_nAtkStateCount--;
	}
	if (m_nAtkTime > 0)
	{
		m_nAtkTime--;
	}
}

//=======================================
// ブロックへの攻撃処理
//=======================================
void CCat::AttackBlock(void)
{
	// ローカル変数宣言
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	// ブロックの攻撃判定
	collision::BlockHit(this,
		D3DXVECTOR3(pos.x + sinf(rot.y) * -ATTACK_DISTANCE, pos.y, pos.z + cosf(rot.y) * -ATTACK_DISTANCE),
		ATTACK_SIZE);

	if (GetSE() == true && m_bSE == false)
	{ // SE再生するとき

		// ブロックSE再生
		CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_BLOCKATTACK);

		m_bSE = true;
	}
}

//=======================================
// 起伏地面の当たり判定
//=======================================
void CCat::Elevation(void)
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
		}

		// 次のポインタを取得する
		pMesh = pMesh->GetNext();
	}

	// 位置と移動量を更新する
	SetPos(pos);
	SetMove(move);
}

//===========================================
// ネコのアイテム設置処理
//===========================================
void CCat::ItemSet(void)
{
	if (m_pItemUI != nullptr)
	{ // アイテムUIの情報が NULL じゃない場合

		if (m_nItemCount > 0 &&
			m_pItemUI->GetItemUI(CItemUI::ORDER_FRONT).pMark != nullptr &&
			(CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_TAB) == true ||
				CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_Y, GetPlayerIdx()) == true))
		{ // アイテムを持っている状態でYボタンが押された場合

			switch (m_pItemUI->GetItemUI(CItemUI::ORDER_FRONT).pMark->GetType())
			{
			case CItem::TYPE_MOUSETRAP:		// ネズミ捕り

				// アイテムを設置する
				CObstacle::Create(GetPos(), GetRot(), CObstacle::TYPE::TYPE_MOUSETRAP);
				m_bItem = true;

				break;

			case CItem::TYPE_DYNAMITE:		// ダイナマイト

				// アイテムを設置する
				CObstacle::Create(GetPos(), GetRot(), CObstacle::TYPE::TYPE_DYNAMITE);
				m_bItem = true;

				break;

			default:

				// 停止
				assert(false);

				break;
			}

			// 情報のソート処理
			m_pItemUI->SortInfo();

			// アイテムのカウント数を減算する
			m_nItemCount--;

			// アイテム設置音を鳴らす
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_SETITEM);
		}
	}
}

//===========================================
// デバッグ表示
//===========================================
void CCat::DebugMessage(void)
{
	CManager::Get()->GetDebugProc()->Print("\n 猫情報--------------------------------------------\n");

	// 猫の攻撃位置情報を表示
	CManager::Get()->GetDebugProc()->Print("位置：%f %f %f\n", GetPos().x, GetPos().y, GetPos().z);

	// 猫の操作方法を表示
	CManager::Get()->GetDebugProc()->Print("移動入力：上:[I] / 左:[J] / 下:[K] / 右:[L] \n");
	CManager::Get()->GetDebugProc()->Print("攻撃 : [ENTER] \n");
}

//=======================================
// ヒット処理
//=======================================
void CCat::Hit(void)
{

}

//=======================================
// 情報の設定処理
//=======================================
void CCat::SetData(const D3DXVECTOR3& pos, const int nID, const TYPE type)
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
	SetSizeColl(CAT_SIZE);

	// 移動量を設定する
	SetSpeed(MOVE_SPEED);
	SetSpeedCopy(GetSpeed());

	// 全ての値を初期化する
	m_posDest = pos;		// 目的の位置
	m_rotDest = GetRot();	// 目的の向きを設定する

	for (int nCntData = 0; nCntData < GetNumModel(); nCntData++)
	{
		// 初期化処理
		GetHierarchy(nCntData)->SetPos(pos);										// 位置
		GetHierarchy(nCntData)->SetPosOld(pos);										// 前回の位置
		GetHierarchy(nCntData)->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));				// 向き
		GetHierarchy(nCntData)->SetScale(NONE_SCALE);								// 拡大率
		GetHierarchy(nCntData)->SetFileData(CXFile::TYPE(INIT_CAT + nCntData));				// データの設定処理
	}

	// ローカル変数宣言
	CShadowCircle* pShadow = nullptr;		// 影へのポインタ

	// 影の設定処理
	pShadow = CShadowCircle::Create(pos, GetRot(), 40.0f);

	if (pShadow != nullptr)
	{ // 影のポインタが NULL以外の場合

		// 影のインデックス設定
		m_nShadowIdx = pShadow->GetNumID();
	}

	// モーションの設定処理
	GetMotion()->Set(MOTIONTYPE_NEUTRAL);

	// 強制モーション処理
	GetMotion()->SetForcibly();

	// モーションの更新処理(やらないと魑魅魍魎が誕生する)
	GetMotion()->Update();

	// ゲームモードの時だけUIを生成
	if (CManager::Get()->GetMode() == CScene::MODE_GAME || CManager::Get()->GetMode() == CScene::MODE_TUTORIAL)
	{
		// アイテムUIの生成処理
		SetItemUI();
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CCat::MotionManager(void)
{
	// モーションの種類を取得する
	int nMotionType = GetMotion()->GetType();

	if (CManager::Get()->GetMode() == CScene::MODE_RESULT)
	{ // リザルト && ねこのかち

		if (CResult::GetState() == CGame::STATE_RAT_WIN)
		{ // ねずみのかち

			if (nMotionType != MOTIONTYPE_LOSE)
			{
				nMotionType = MOTIONTYPE_LOSE;

				// モーションの設定処理
				GetMotion()->Set(nMotionType);
			}
		}
		else if (CResult::GetState() == CGame::STATE_CAT_WIN)
		{ // ねこのかち

			if (nMotionType != MOTIONTYPE_WIN)
			{
				nMotionType = MOTIONTYPE_WIN;

				// モーションの設定処理
				GetMotion()->Set(nMotionType);
			}
		}
	}
	else
	{ // リザルト以外のとき
		if (GetStunState() == STUNSTATE_STUN)
		{
			if (nMotionType != MOTIONTYPE_STUN)
			{
				nMotionType = MOTIONTYPE_STUN;

				// モーションの設定処理
				GetMotion()->Set(nMotionType);
			}
		}
		else if (GetStunState() == STUNSTATE_SMASH)
		{
			if (nMotionType != MOTIONTYPE_KNOCKBACK)
			{
				nMotionType = MOTIONTYPE_KNOCKBACK;

				// モーションの設定処理
				GetMotion()->Set(nMotionType);
			}
		}

		else if (m_AttackState == ATTACKSTATE_STANDBY)
		{
			if (nMotionType != MOTIONTYPE_ATTACK)
			{
				nMotionType = MOTIONTYPE_ATTACK;

				// モーションの設定処理
				GetMotion()->Set(nMotionType);
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
// アイテムの取得処理
//=====================================
void CCat::GetItem(const CItem::TYPE type)
{
	// アイテムの所持カウントを加算する
	m_nItemCount++;

	if (m_nItemCount == 1)
	{ // 1個目の場合

		// アイテムのマークを生成する
		m_pItemUI->SetMark(type, CItemUI::ORDER_FRONT);
	}
	else if (m_nItemCount == 2)
	{ // 2個目の場合

		// アイテムのマークを生成する
		m_pItemUI->SetMark(type, CItemUI::ORDER_BACK);
	}
}

//=====================================
// アイテムUIの設定処理
//=====================================
void CCat::SetItemUI(void)
{
	if (m_pItemUI == nullptr)
	{ // アイテムUIが NULL の場合

		// アイテムUIの生成処理
		m_pItemUI = CItemUI::Create(ITEMUI_POS[GetPlayerIdx()]);
	}
}

//=====================================
// アイテムUIの取得処理
//=====================================
CItemUI* CCat::GetItemUI(void) const
{
	// アイテムUIの情報を返す
	return m_pItemUI;
}

//=====================================
// アイテムUIの消去処理
//=====================================
void CCat::DeleteItemUI(void)
{
	if (m_pItemUI != nullptr)
	{ // アイテムUIが NULL じゃない場合

		// アイテムUIの終了処理
		m_pItemUI->Uninit();
		m_pItemUI = nullptr;
	}
}

//=====================================
// アイテムの総数の取得処理
//=====================================
int CCat::GetItemCount(void) const
{
	// アイテムの総数を返す
	return m_nItemCount;
}