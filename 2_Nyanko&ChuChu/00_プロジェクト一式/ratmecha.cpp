//===========================================
//
// ネズミメカのメイン処理[toycar.cpp]
// Author 堀川萩大
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "ratmecha.h"
#include "useful.h"
#include "player_idUI.h"
#include "player.h"
#include "collision.h"
#include "map.h"
#include "block.h"
#include "block_manager.h"
#include "obstacle.h"
#include "obstacle_manager.h"
#include "game.h"
#include "input.h"
#include "sound.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define CAR_SPEED			(-7.5f)			// 車の速度
#define CAR_CURVE_SPEED		(0.08f)			// 車の曲がる速度
#define CAR_DEST_ROT_SHIFT	(0.1f)			// 目的の向きの補正の許容範囲
#define CAR_BRAKE_COUNT		(6)				// ブレーキカウント数
#define ROTDEST_MAGNI_MIN	(8)				// 目的の向きの倍率の最小値
#define ROTDEST_MAGNI_RANGE	(11)			// 目的の向きの倍率の範囲
#define ATTACK_SIZE		(D3DXVECTOR3(95.0f, 150.0f, 95.0f))		// 攻撃の判定の大きさ

//-------------------------------------------
// 静的メンバ変数
//-------------------------------------------
int CRatMecha::m_nBgmAll = 0;				// BGMを鳴らした音の総数

//==============================
// コンストラクタ
//==============================
CRatMecha::CRatMecha() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	m_move = NONE_D3DXVECTOR3;		// 移動量
	m_state = STATE_DRIVE;			// 状態
	m_nBrakeCount = 0;				// ブレーキカウント
	m_fRotDest = 0.0f;				// 目的の向き
	m_fRotMagni = 0.0f;				// 向きの倍率
	m_bRight = true;				// 右向き状況
	m_bMove = false;				// 動いているか
	m_pPlayerID = nullptr;			// IDのポインタ
	m_nIdnumber = -1;				// プレイヤーID番号

	// 使用条件
	SetRatUse(true);
}

//==============================
// デストラクタ
//==============================
CRatMecha::~CRatMecha()
{

}

//==============================
// ネズミメカの初期化処理
//==============================
HRESULT CRatMecha::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // 初期化処理に失敗した場合

	  // 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	m_move = NONE_D3DXVECTOR3;		// 移動量
	m_state = STATE_DRIVE;			// 状態
	m_nBrakeCount = 0;				// ブレーキカウント
	m_fRotDest = 0.0f;				// 目的の向き
	m_fRotMagni = 0.0f;				// 向きの倍率
	m_bRight = true;				// 右向き状況
	m_pPlayerID = nullptr;			// IDのポインタ

	// 使用条件
	SetRatUse(true);
	SetCatUse(false);

									// 値を返す
	return S_OK;
}

//========================================
// ネズミメカの終了処理
//========================================
void CRatMecha::Uninit(void)
{
	if (m_pPlayerID != nullptr)
	{
		m_pPlayerID->Uninit();
		m_pPlayerID = nullptr;
	}

	// 終了処理
	CObstacle::Uninit();

	// BGMを鳴らした総数を減算する
	m_nBgmAll--;

	if (m_nBgmAll <= 0)
	{ // 総数が0未満になった場合

		// 総数を補正する
		m_nBgmAll = 0;

		// ネズミメカの走行音を止める
		CManager::Get()->GetSound()->Stop(CSound::SOUND_LABEL_SE_RATMECHA_RUN);
	}
}

//=====================================
// ネズミメカの更新処理
//=====================================
void CRatMecha::Update(void)
{
	// 前回の位置を設定する
	SetPosOld(GetPos());
	if (m_bMove == true)
	{
		if (m_pPlayerID != nullptr)
		{
			m_pPlayerID->SetData(D3DXVECTOR3(GetPos().x, GetPos().y+120.0f, GetPos().z), m_nIdnumber);


		}
		switch (m_state)
		{
		case STATE_DRIVE:

			// 走行処理
			Drive();

			if (MagicWall() == true ||
				Block() == true)
			{ // 魔法壁または、ブロックの当たり判定が true の場合

			  // カーブ状態にする
				m_state = STATE_CURVE;

				// 向きの計算処理
				RotCalc();
			}

			break;

		case STATE_CURVE:

			// カービング処理
			Curve();

			break;

		case STATE_BRAKE:

			// ブレーキカウントを加算する
			m_nBrakeCount++;

			if (m_nBrakeCount % CAR_BRAKE_COUNT == 0)
			{ // ブレーキカウントが一定数になった場合

			  // ブレーキカウントを初期化する
				m_nBrakeCount = 0;

				// ドライブ状態にする
				m_state = STATE_DRIVE;
			}

			break;

		default:

			// 停止
			assert(false);

			break;
		}

	}
}

//=====================================
// ネズミメカの描画処理
//=====================================
void CRatMecha::Draw(void)
{
	// 描画処理
	CObstacle::Draw(1.0f);

	if (m_bMove == true)
	{
		m_pPlayerID->Draw();
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CRatMecha::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos, rot, type);

	// 全ての値を設定する
	m_move = D3DXVECTOR3(sinf(rot.y) * CAR_SPEED, 0.0f, cosf(rot.y) * CAR_SPEED);	// 移動量
	m_state = STATE_DRIVE;			// 状態
	m_nBrakeCount = 0;				// ブレーキカウント
	m_fRotDest = 0.0f;				// 目的の向き
	m_fRotMagni = (float)((rand() % ROTDEST_MAGNI_RANGE + ROTDEST_MAGNI_MIN) * 0.1f);		// 向きの倍率
	m_bRight = true;				// 右向き状況

	if (m_pPlayerID == nullptr)
	{ // プレイヤーのID表示が NULL の場合

	  // プレイヤーのID表示の生成処理
		m_pPlayerID = CPlayerID::Create(pos, 1);
	}
}

//=====================================
// 当たり判定処理
//=====================================
bool CRatMecha::Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CRatMecha::Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
 	if (m_bMove == true)
	{ // ネズミメカが動いていたら

		if (pPlayer->GetType() == CPlayer::TYPE_CAT)
		{
			if (pPlayer->GetAttack_Jump() == true)
			{ // ネコが攻撃していたら

				//	ネコの攻撃判定を出す
				if (useful::RectangleCollisionXZ(
					D3DXVECTOR3(pPlayer->GetPos().x + sinf(pPlayer->GetRot().y) * -100.0f, pPlayer->GetPos().y, pPlayer->GetPos().z + cosf(pPlayer->GetRot().y) * -100.0f),
					GetPos(),
					ATTACK_SIZE, 
					D3DXVECTOR3(10.0f, 50.0f, 10.0f),
					D3DXVECTOR3(-ATTACK_SIZE.x, -ATTACK_SIZE.y, -ATTACK_SIZE.z),
					D3DXVECTOR3(-10.0f, -50.0f, -10.0f)) == true)
				{ // XZの矩形に当たってたら

					// ネズミメカの破壊音を鳴らす
					CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_RATMECHA_BREAK);

					// true を返す
					return true;
				}
			}
		}
	}
	// false を返す
	return false;
}

//=====================================
// 走行処理
//=====================================
void CRatMecha::Drive(void)
{
	// 情報を取得する
	D3DXVECTOR3 pos = GetPos();		// 位置
	D3DXVECTOR3 rot = GetRot();		// 向き

	// 位置を移動する
	pos += m_move;

	// 位置を適用する
	SetPos(pos);
}

//=====================================
// カービング処理
//=====================================
void CRatMecha::Curve(void)
{
	// 向きを取得する
	D3DXVECTOR3 rot = GetRot();

	if (m_bRight == true)
	{ // 右向きの場合

	  // 向きを加算する
		rot.y += CAR_CURVE_SPEED;
	}
	else
	{ // 上記以外

	  // 向きを減算する
		rot.y -= CAR_CURVE_SPEED;
	}

	// 向きの正規化
	useful::RotNormalize(&rot.y);

	if (fabsf(m_fRotDest - rot.y) <= CAR_DEST_ROT_SHIFT)
	{ // 向きが一定まで行った場合

	  // 向きを補正する
		rot.y = m_fRotDest;

		// ブレーキ状態にする
		m_state = STATE_BRAKE;

		// 移動量を設定する
		m_move.x = sinf(rot.y) * CAR_SPEED;
		m_move.z = cosf(rot.y) * CAR_SPEED;
	}

	// 向きを適用する
	SetRot(rot);
}

//=====================================
// 向きの計算処理
//=====================================
void CRatMecha::RotCalc(void)
{
	// 情報を取得する
	D3DXVECTOR3 pos = GetPos();		// 位置
	D3DXVECTOR3 rot = GetRot();		// 向き
	float fRotDiff;					// 向きの差分

	// 目的の向きを設定する
	m_fRotDest = rot.y + (D3DX_PI * m_fRotMagni);

	// 向きの正規化
	useful::RotNormalize(&m_fRotDest);

	// 向きの差分を求める
	fRotDiff = m_fRotDest - rot.y;

	// 向きを正規化する
	useful::RotNormalize(&fRotDiff);

	if (fRotDiff >= 0.0f)
	{ // 向きの差分がプラスの値の場合

		// 右向きにする
		m_bRight = true;
	}
	else
	{ // 上記以外

		// 左向きにする
		m_bRight = false;
	}
}

//=====================================
// ブロックの当たり判定処理
//=====================================
bool CRatMecha::Block(void)
{
	// ローカル変数宣言
	CBlock* pBlock = CBlockManager::Get()->GetTop();		// ブロックの先頭を取得する
	D3DXVECTOR3 pos = GetPos();								// 位置を取得する
	bool bClush = false;									// 衝突判定

	while (pBlock != nullptr)
	{ // ブロックが NULL じゃない場合回す

		if (collision::HexahedronCollision
		(
			&pos,
			pBlock->GetPos(),
			GetPosOld(),
			pBlock->GetPosOld(),
			GetFileData().vtxMin,
			pBlock->GetVtxMin(),
			GetFileData().vtxMax,
			pBlock->GetVtxMax()
		) == true)
		{ // 六面体の当たり判定に当たった場合

			// 衝突判定を true にする
			bClush = true;
		}

		// 次のブロックを取得する
		pBlock = pBlock->GetNext();
	}

	// 位置を適用する
	SetPos(pos);

	// 衝突判定を返す
	return bClush;
}

//=====================================
// 障害物の当たり判定処理
//=====================================
bool CRatMecha::Obstacle(void)
{
	// ローカル変数宣言
	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();	// 障害物の先頭を取得する
	D3DXVECTOR3 pos = GetPos();									// 位置を取得する
	bool bClush = false;										// 衝突判定

	while (pObstacle != nullptr)
	{ // 障害物が NULL じゃない場合回す

		if (collision::HexahedronCollision
		(
			&pos,
			pObstacle->GetPos(),
			GetPosOld(),
			pObstacle->GetPosOld(),
			GetFileData().vtxMin,
			pObstacle->GetFileData().vtxMin,
			GetFileData().vtxMax,
			pObstacle->GetFileData().vtxMax
		) == true)
		{ // 六面体の当たり判定に当たった場合

			// 衝突判定を true にする
			bClush = true;
		}

		// 次の障害物を取得する
		pObstacle = pObstacle->GetNext();
	}

	// 位置を適用する
	SetPos(pos);

	// 衝突判定を返す
	return bClush;
}

//=====================================
// 魔法壁の当たり判定処理
//=====================================
bool CRatMecha::MagicWall(void)
{
	// ローカル変数宣言
	D3DXVECTOR3 pos = GetPos();					// 位置
	float fRadius = GetFileData().fRadius;		// 半径
	bool bClush = false;						// 衝突状況

	if (pos.x - fRadius <= -MAP_SIZE.x)
	{ // 位置が左から出そうな場合

		// 位置を設定する
		pos.x = -MAP_SIZE.x + fRadius;

		// 衝突状況を true にする
		bClush = true;
	}

	if (pos.x + fRadius >= MAP_SIZE.x)
	{ // 位置が右から出そうな場合

		// 位置を設定する
		pos.x = MAP_SIZE.x - fRadius;

		// 衝突状況を true にする
		bClush = true;
	}

	if (pos.z - fRadius <= -MAP_SIZE.z)
	{ // 位置が手前から出そうな場合

		// 位置を設定する
		pos.z = -MAP_SIZE.z + fRadius;

		// 衝突状況を true にする
		bClush = true;
	}

	if (pos.z + fRadius >= MAP_SIZE.z)
	{ // 位置が奥から出そうな場合

		// 位置を設定する
		pos.z = MAP_SIZE.z - fRadius;

		// 衝突状況を true にする
		bClush = true;
	}

	// 位置を適用する
	SetPos(pos);

	// 衝突状況を返す
	return bClush;
}

//=====================================
// ギミック起動処理
//=====================================
void CRatMecha::Action(void)
{
	// プレイヤーのポインタを宣言
	CPlayer* pPlayer;

	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		// プレイヤーを取得する
		pPlayer = CGame::GetPlayer(nCnt);

		if (pPlayer->GetType() == CPlayer::TYPE_RAT)
		{ // ネズミの場合
			if (useful::CircleCollisionXZ(pPlayer->GetPos(), GetPos(), 70.0f, GetFileData().fRadius) == true)
			{//円の範囲内の場合trueを返す

				if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_B, nCnt) == true ||
					CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_E) == true)
				{ // ボタンが押されたとき

					// 押したプレイヤーのIDを取得して保存する
					m_nIdnumber = nCnt;

					if (m_nBgmAll <= 0)
					{ // 総数が0以下の場合

						// ネズミメカの走行音を鳴らす
						CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_RATMECHA_RUN);
					}

					// 走行音を鳴らした数を加算する
					m_nBgmAll++;
				}
			
			}
		}
	}


	if (m_bMove == false)
	{ // ネズミメカを動かし、止められないようにする
		m_bMove = !m_bMove;
		SetAction(true);
	}
}

//=====================================
// ヒット処理
//=====================================
bool CRatMecha::HitCircle(CPlayer* pPlayer, const float Radius)
{
	if (useful::CircleCollisionXZ(pPlayer->GetPos(), GetPos(), Radius, GetFileData().fRadius) == true)
	{//円の範囲内の場合trueを返す
		return true;
	}

	// false を返す
	return false;
}