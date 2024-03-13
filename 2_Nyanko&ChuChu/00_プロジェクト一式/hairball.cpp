//===========================================
//
// 毬のメイン処理[hairball.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "hairball.h"
#include "collision.h"
#include "useful.h"
#include "sound.h"

#include "objectElevation.h"
#include "elevation_manager.h"
#include "block.h"
#include "block_manager.h"
#include "map.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define GRAVITY		(0.5f)		// 重力

//==============================
// コンストラクタ
//==============================
CHairBall::CHairBall() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	m_move = NONE_D3DXVECTOR3;		// 移動量
	m_state = STATE_STOP;			// 状態
	SetCatDisp(true);				// 猫側の画面の不透明度を強制的に1.0fにする
}

//==============================
// デストラクタ
//==============================
CHairBall::~CHairBall()
{

}

//==============================
// 破片の初期化処理
//==============================
HRESULT CHairBall::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	m_move = NONE_D3DXVECTOR3;		// 移動量
	m_state = STATE_STOP;			// 状態

	// 値を返す
	return S_OK;
}

//========================================
// 破片の終了処理
//========================================
void CHairBall::Uninit(void)
{
	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// 破片の更新処理
//=====================================
void CHairBall::Update(void)
{
	// 前回の位置を設定する
	SetPosOld(GetPos());

	switch (m_state)
	{
	case STATE_STOP:

		// 特になし

		break;

	case STATE_SMASH:

		// 移動処理
		Move();

		break;

	default:

		// 停止
		assert(false);

		break;
	}

	// 重力処理
	Gravity();

	// 起伏地面との当たり判定
	Elevation();

	// ブロックとの当たり判定
	Block();

	// 魔法の壁処理
	MagicWall();
}

//=====================================
// 破片の描画処理
//=====================================
void CHairBall::Draw(void)
{
	// 描画処理
	CObstacle::Draw(1.0f);
}

//=====================================
// 情報の設定処理
//=====================================
void CHairBall::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos,rot, type);

	// 全ての値を設定する
	m_move = NONE_D3DXVECTOR3;		// 移動量
	m_state = STATE_STOP;			// 状態
}

//=====================================
// 当たり判定処理
//=====================================
bool CHairBall::Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// 位置を取得する
	D3DXVECTOR3 pos = pPlayer->GetPos();

	if (pos.y <= GetPos().y + GetFileData().vtxMax.y &&
		pos.y + collSize.y >= GetPos().y + GetFileData().vtxMin.y)
	{ // 毬と衝突した場合

		// 円柱の当たり判定処理
		useful::CylinderCollision(&pos, GetPos(), GetFileData().fRadius + collSize.x);
	}

	// 位置を適用する
	pPlayer->SetPos(pos);

	// false の場合
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CHairBall::Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// ターゲットの位置と方向を宣言
	D3DXVECTOR3 Targetpos = pPlayer->GetPos();
	float fAngle = 0.0f;

	if (pPlayer->GetType() == CPlayer::TYPE_CAT)
	{ // ネコの場合

		if (Targetpos.y <= GetPos().y + GetFileData().vtxMax.y &&
			Targetpos.y + collSize.y >= GetPos().y + GetFileData().vtxMin.y &&
			useful::CylinderInner(Targetpos, GetPos(), GetFileData().fRadius + collSize.x) == true)
		{ // 毬と衝突した場合

			// まりのSE鳴らす
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_HAIRBALL);

			// 吹き飛ばし状態にする
			m_state = STATE_SMASH;
			SetFileData((CXFile::TYPE)(CXFile::TYPE_RED_HAIRBALL));
			SetAction(true);

			// 方向を設定する
			fAngle = atan2f((GetPos().x - Targetpos.x), (GetPos().z - Targetpos.z));

			// 移動量を設定する
			m_move.x = sinf(fAngle) * 15.0f;
			m_move.y = 15.0f;
			m_move.z = cosf(fAngle) * 15.0f;

			// true を返す
			return false;
		}
		else
		{ // 上記以外

			// false を返す
			return false;
		}
	}
	else
	{ // 上記以外

		if (m_state == STATE_SMASH &&
			Targetpos.y <= GetPos().y + GetFileData().vtxMax.y &&
			Targetpos.y + collSize.y >= GetPos().y + GetFileData().vtxMin.y &&
			useful::CylinderCollision(&Targetpos, GetPos(), GetFileData().fRadius + collSize.x) == true)
		{ // 毬と衝突した場合

			// true を返す
			return true;
		}
		else
		{ // 上記以外

			// false を返す
			return false;
		}
	}
}

//=====================================
// 移動処理
//=====================================
void CHairBall::Move(void)
{
	// 位置を取得する
	D3DXVECTOR3 pos = GetPos();

	// 位置を移動する
	pos.x += m_move.x;
	pos.z += m_move.z;

	// 位置を適用する
	SetPos(pos);
}

//=====================================
// 重力処理
//=====================================
void CHairBall::Gravity(void)
{
	// 位置を取得する
	D3DXVECTOR3 pos = GetPos();

	// 重力処理
	useful::Gravity(&m_move.y, &pos.y, GRAVITY);
	
	// 位置を設定する
	SetPos(pos);
}

//=====================================
// 起伏地面の当たり判定
//=====================================
void CHairBall::Elevation(void)
{
	// ローカル変数宣言
	CElevation* pMesh = CElevationManager::Get()->GetTop();		// 起伏の先頭のオブジェクトを取得する
	D3DXVECTOR3 pos = GetPos();				// 位置を取得する
	float fHeight = 0.0f;					// 高さ
	bool bLand = false;						// 着地状況

	while (pMesh != nullptr)
	{ // 地面の情報がある限り回す

		// 当たり判定を取る
		fHeight = pMesh->ElevationCollision(pos);

		if (pos.y + GetFileData().vtxMin.y <= fHeight)
		{ // 当たり判定の位置が高かった場合

			// 高さを設定する
			pos.y = fHeight - GetFileData().vtxMin.y;

			// 移動量を減算する
			m_move.x *= 0.6f;
			m_move.y *= -0.6f;
			m_move.z *= 0.6f;

			if (m_move.y <= 5.0f)
			{ // 移動量が一定以下の場合

				// 重力を補正する
				m_move.y = 0.0f;

				// 着地する
				bLand = true;
			}
		}

		// 次のポインタを取得する
		pMesh = pMesh->GetNext();
	}

	if (bLand == true)
	{ // 着地状況を true にする

		// 停止状態にする
		m_state = STATE_STOP;
		SetFileData((CXFile::TYPE)(CXFile::TYPE_HAIRBALL));
		SetAction(false);
	}
	else
	{ // 上記以外

		// 吹き飛ばし状態にする
		m_state = STATE_SMASH;
	}

	// 位置を更新する
	SetPos(pos);
}

//=====================================
// ブロックの当たり判定
//=====================================
void CHairBall::Block(void)
{
	// ローカル変数宣言
	CBlock* pBlock = CBlockManager::Get()->GetTop();		// ブロックの先頭のオブジェクトを取得する
	D3DXVECTOR3 pos = GetPos();				// 位置を取得する
	collision::SCollision coll = { false,false, false, false, false, false };		// 当たり判定の変数

	while (pBlock != nullptr)
	{ // 地面の情報がある限り回す

		// 当たり判定の変数を加える
		coll = collision::HexahedronClush(&pos, pBlock->GetPos(), GetPosOld(), pBlock->GetPosOld(), GetFileData().vtxMin, pBlock->GetFileData().vtxMin, GetFileData().vtxMax, pBlock->GetFileData().vtxMax);

		if (coll.bFar == true ||
			coll.bNear == true)
		{ // 奥手前に当たった場合

			// 移動量を逆にする
			m_move.z *= -1.0f;
		}

		if(coll.bLeft == true ||
			coll.bRight == true)
		{ // 左右に当たった場合

			// 移動量を逆にする
			m_move.x *= -1.0f;
		}

		if (coll.bTop == true)
		{ // 上に当たった場合

			// 移動量を逆にする
			m_move.y *= -1.0f;
		}

		// 次のポインタを取得する
		pBlock = pBlock->GetNext();
	}

	// 位置を更新する
	SetPos(pos);
}

//=====================================
// 魔法の壁
//=====================================
void CHairBall::MagicWall(void)
{
	// 位置を取得する
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 Max = GetFileData().vtxMax;
	D3DXVECTOR3 Min = GetFileData().vtxMin;

	if (pos.x + Min.x <= -MAP_SIZE.x)
	{ // 位置が左から出そうな場合

		// 位置を設定する
		pos.x = -MAP_SIZE.x - Min.x;

		// 移動量を逆にする
		m_move.x *= -1;
	}

	if (pos.x + Max.x >= MAP_SIZE.x)
	{ // 位置が右から出そうな場合

		// 位置を設定する
		pos.x = MAP_SIZE.x - Max.x;

		// 移動量を逆にする
		m_move.x *= -1;
	}

	if (pos.z + Min.z <= -MAP_SIZE.z)
	{ // 位置が手前から出そうな場合

		// 位置を設定する
		pos.z = -MAP_SIZE.z - Min.z;

		// 移動量を逆にする
		m_move.z *= -1;
	}

	if (pos.z + Max.z >= MAP_SIZE.z)
	{ // 位置が奥から出そうな場合

		// 位置を設定する
		pos.z = MAP_SIZE.z - Max.z;

		// 移動量を逆にする
		m_move.z *= -1;
	}

	// 位置を適用する
	SetPos(pos);
}