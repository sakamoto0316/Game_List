//===========================================
//
// ゴミ箱のメイン処理[garbage.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "garbagecan.h"
#include "renderer.h"
#include "useful.h"
#include "sound.h"

#include "player.h"
#include "block.h"
#include "block_manager.h"
#include "obstacle_manager.h"
#include "collision.h"
#include "fraction.h"
#include "map.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define SPEED		(4.0f)		// 速度
#define GRAVITY		(0.4f)		// 重力
#define ROT_MOVE	(0.05f)		// 向きの移動量
#define CAT_SIZE	(D3DXVECTOR3(70.0f, 280.0f, 70.0f))		// 当たり判定のサイズ

//==============================
// コンストラクタ
//==============================
CGarbage::CGarbage() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	m_State = STATE_GARBAGECAN;		// 状態
	m_Slide = SLIDE_STOP;
	m_pPlayer = NULL;
	m_move = NONE_D3DXVECTOR3;
	m_SlideMove = NONE_D3DXVECTOR3;
	m_PlayerPos = NONE_D3DXVECTOR3;

	// ネズミだけ動かせるようにする
	SetCatUse(false);
	SetRatUse(true);
}

//==============================
// デストラクタ
//==============================
CGarbage::~CGarbage()
{

}

//==============================
// 破片の初期化処理
//==============================
HRESULT CGarbage::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 値を返す
	return S_OK;
}

//========================================
// 破片の終了処理
//========================================
void CGarbage::Uninit(void)
{
	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// 破片の更新処理
//=====================================
void CGarbage::Update(void)
{
	//状態管理
	StateManager();

	if (m_Slide == SLIDE_ON)
	{
		D3DXVECTOR3 pos = GetPos();
		SetPosOld(pos);
		D3DXVECTOR3 posold = GetPosOld();

		pos += m_SlideMove;
		m_pPlayer->SetPos(pos + m_PlayerPos);

		if (Collision(m_pPlayer, GetFileData().vtxMax) == true || 
			MagicWall() == true ||
			((m_SlideMove.x <= 1.0f && m_SlideMove.x >= -1.0f) && (m_SlideMove.z <= 1.0f && m_SlideMove.z >= -1.0f)))
		{
			m_Slide = SLIDE_BREAK;
			m_SlideMove = D3DXVECTOR3(-m_SlideMove.x * 0.1f, 30.0f, -m_SlideMove.z * 0.1f);
		}

		SetPos(pos);
	}
	else if(m_Slide == SLIDE_BREAK)
	{
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 rot = GetRot();
		SetPosOld(pos);
		D3DXVECTOR3 posold = GetPosOld();

		m_SlideMove.y -= 1.0f;
		rot.x += 0.1f;
		rot.z += 0.3f;

		pos += m_SlideMove;

		SetPos(pos);
		SetRot(rot);

		if (pos.y < 0.0f)
		{
			Uninit();
		}
	}
}

//=====================================
// 破片の描画処理
//=====================================
void CGarbage::Draw(void)
{
	// 描画処理
	CObstacle::Draw(1.0f);
}

//=====================================
// 状態管理
//=====================================
void CGarbage::StateManager(void)
{
	// 位置と向きを設定する
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	switch (m_State)
	{
	case STATE_GARBAGECAN:		// ゴミ箱

		break;

	case STATE_FALL:			// 落下状態

		// 移動量を減算する
		m_move.y -= GRAVITY;

		// 位置を移動する
		pos += m_move;

		// 向きを移動する
		rot.z += ROT_MOVE;

		// 向きの正規化
		useful::RotNormalize(&rot.z);

		if (pos.y <= 0.0f)
		{ // 地面以下になった場合

			// 位置を補正する
			pos.y = 0.0f;

			// 移動量を初期化する
			m_move = NONE_D3DXVECTOR3;

			// 向きを初期化する
			rot.z = 0.0f;

			// バナナの皮状態にする
			m_State = STATE_BANANA_NORMAL;

			// モデルの情報を設定する
			SetFileData(CXFile::TYPE_GARBAGE);

			// バナナ落ちる音再生
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_BANANADOWN);
		}

		break;

	case STATE_BANANA_NORMAL:	// バナナの皮

		break;

	case STATE_BANANA_SLIDE:	// バナナ滑り

		break;

	default:

		// 停止
		assert(false);

		break;
	}

	// 位置を向きを適用する
	SetPos(pos);
	SetRot(rot);
}

//=====================================
// 魔法の壁
//=====================================
bool CGarbage::MagicWall(void)
{
	// 位置を取得する
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 Max = GetFileData().vtxMax;
	D3DXVECTOR3 Min = GetFileData().vtxMin;

	if (pos.x + Min.x <= -MAP_SIZE.x)
	{ // 位置が左から出そうな場合

		// 位置を設定する
		pos.x = -MAP_SIZE.x - Min.x;

		// true を返す
		return true;
	}

	if (pos.x + Max.x >= MAP_SIZE.x)
	{ // 位置が右から出そうな場合

		// 位置を設定する
		pos.x = MAP_SIZE.x - Max.x;

		// true を返す
		return true;
	}

	if (pos.z + Min.z <= -MAP_SIZE.z)
	{ // 位置が右から出そうな場合

		// 位置を設定する
		pos.z = -MAP_SIZE.z - Min.z;

		// true を返す
		return true;
	}

	if (pos.z + Max.z >= MAP_SIZE.z)
	{ // 位置が右から出そうな場合

		// 位置を設定する
		pos.z = MAP_SIZE.z - Max.z;

		// true を返す
		return true;
	}

	// 位置を適用する
	SetPos(pos);

	// false を返す
	return false;
}

//=====================================
// 破壊時処理
//=====================================
void CGarbage::SlideOn(D3DXVECTOR3 pos, D3DXVECTOR3 move, CPlayer *pPlayer)
{
	m_Slide = SLIDE_ON;
	m_State = STATE_BANANA_SLIDE;
	m_PlayerPos = pos - GetPos();
	m_SlideMove = move;
	m_pPlayer = pPlayer;

	// バナナ滑る音再生
	CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_BANANATURUTURU);
}

//=====================================
// 破壊時処理
//=====================================
void CGarbage::Break(void)
{
	if (m_State == STATE_GARBAGECAN)
	{ // ゴミ箱状態の場合

		m_State = STATE_FALL;

		// 移動量を設定する
		m_move.x = sinf(GetRot().y + (D3DX_PI * -0.5f)) * SPEED;
		m_move.y = 0.0f;
		m_move.z = cosf(GetRot().y + (D3DX_PI * -0.5f)) * SPEED;
	}

	// アクション状況を true にする
	SetAction(true);
}

//=====================================
// 情報の設定処理
//=====================================
void CGarbage::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos,rot, type);
}

//=====================================
// 当たり判定処理
//=====================================
bool CGarbage::Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// 位置と最大値と最小値を設定する
	D3DXVECTOR3 pos = pPlayer->GetPos();
	D3DXVECTOR3 move = pPlayer->GetMove();
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(collSize.x, collSize.y, collSize.z);
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);
	collision::SCollision coll = { false,false,false,false,false,false };

	if (m_State == STATE_GARBAGECAN)
	{ //ゴミ箱状態の場合

		// 六面体の当たり判定
		coll = collision::HexahedronClush(&pos, GetPos(), pPlayer->GetPosOld(), GetPosOld(), vtxMin, GetFileData().vtxMin, vtxMax, GetFileData().vtxMax);

		// 位置を適用する
		pPlayer->SetPos(pos);

		if(coll.bTop == true)
		{ // 上に乗った場合

			// 移動量を初期化する
			move.y = 0.0f;

			// 移動量を設定する
			pPlayer->SetMove(move);

			// true を返す
			return true;
		}
	}
	else if(m_Slide == SLIDE_ON)
	{
		// 先頭のブロックの情報を取得する
		CBlock* pBlock = CBlockManager::Get()->GetTop();

		while (pBlock != nullptr)
		{ // ブロックが NULL の場合

			if (collision::HexahedronCollision(&pos, pBlock->GetPos(), pPlayer->GetPosOld(), pBlock->GetPosOld(), vtxMin, pBlock->GetFileData().vtxMin, vtxMax, pBlock->GetFileData().vtxMax) == true)
			{ // 六面体の当たり判定が true の場合

				// 位置を適用する
				pPlayer->SetPos(pos);

				// true を返す
				return true;
			}

			// 次のブロックの情報を取得する
			pBlock = pBlock->GetNext();
		}

		// 先頭の障害物の情報を取得する
		CObstacle* pObstacle = CObstacleManager::Get()->GetTop();

		while (pObstacle != nullptr)
		{ // 障害物が NULL の場合

			if (pObstacle->GetType() != CObstacle::TYPE::TYPE_GARBAGECAN &&
				pObstacle->Collision(pPlayer, CAT_SIZE) == true)
			{ // 六面体の当たり判定が true の場合

				// 位置を適用する
				pPlayer->SetPos(pos);

				// true を返す
				return true;
			}

			// 次の障害物の情報を取得する
			pObstacle = pObstacle->GetNext();
		}
	}

	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CGarbage::Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// ローカル変数宣言
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(collSize.x, collSize.y, collSize.z);		// サイズの最大値
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);		// サイズの最小値

	if (m_State == STATE_BANANA_NORMAL &&
		pPlayer->GetType() == CPlayer::TYPE_CAT &&
		useful::RectangleCollisionXY(GetPos(), pPlayer->GetPos(), GetFileData().vtxMax, vtxMax, GetFileData().vtxMin, vtxMin) == true &&
		useful::RectangleCollisionXZ(GetPos(), pPlayer->GetPos(), GetFileData().vtxMax, vtxMax, GetFileData().vtxMin, vtxMin) == true &&
		useful::RectangleCollisionYZ(GetPos(), pPlayer->GetPos(), GetFileData().vtxMax, vtxMax, GetFileData().vtxMin, vtxMin) == true)
	{ // ネコがバナナの皮に引っかかった場合

		// true を返す
		return true;
	}

	// false を返す
	return false;
}

//=====================================
// ヒットの円処理
//=====================================
bool CGarbage::HitCircle(CPlayer* pPlayer, const float Radius)
{
	if (GetAction() == false &&
		useful::CircleCollisionXZ(pPlayer->GetPos(), GetPos(), Radius, GetFileData().fRadius) == true)
	{ // 範囲内に入っている場合

		// true を返す
		return true;
	}

	// false を返す
	return false;
}

//=====================================
// ギミック起動処理
//=====================================
void CGarbage::Action(void)
{
	//破壊時処理
	Break();
}