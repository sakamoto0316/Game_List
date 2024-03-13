//===========================================
//
// ペットボトルのメイン処理[petbottle.cpp]
// Author 大野祥平
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "useful.h"
#include "petbottle.h"

#include "objectElevation.h"
#include "elevation_manager.h"
#include "block.h"
#include "block_manager.h"
#include "map.h"
#include "collision.h"
#include "sound.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define STAND_ROT	(D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f))		// 直立状態の向き
#define GRAVITY		(0.5f)			// 重力
#define SPEED		(13.0f)			// 転がる速度
#define ROT_MOVE	(0.01f)			// 向きの移動量

//==============================
// コンストラクタ
//==============================
CPetbottle::CPetbottle() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	m_move = NONE_D3DXVECTOR3;			// 移動量
	m_posPlayer = NONE_D3DXVECTOR3;		// ぶつかったプレイヤーの位置
	m_vtxMax = NONE_D3DXVECTOR3;		// 最大値
	m_vtxMin = NONE_D3DXVECTOR3;		// 最小値
	m_state = STATE_STAND;				// 状態
	m_fAlpha = 1.0f;					// 透明度
	SetRatUse(false);
	SetCatUse(true);
}

//==============================
// デストラクタ
//==============================
CPetbottle::~CPetbottle()
{

}

//==============================
// ペットボトルの初期化処理
//==============================
HRESULT CPetbottle::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	m_move = NONE_D3DXVECTOR3;			// 移動量
	m_posPlayer = NONE_D3DXVECTOR3;		// ぶつかったプレイヤーの位置
	m_vtxMax = NONE_D3DXVECTOR3;		// 最大値
	m_vtxMin = NONE_D3DXVECTOR3;		// 最小値
	m_state = STATE_STAND;				// 状態
	m_fAlpha = 1.0f;					// 透明度

	// 値を返す
	return S_OK;
}

//========================================
// ペットボトルの終了処理
//========================================
void CPetbottle::Uninit(void)
{
	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// ペットボトルの更新処理
//=====================================
void CPetbottle::Update(void)
{
	switch (m_state)
	{
	case CPetbottle::STATE_STAND:		// 直立状態

		// 向きを設定する
		SetRot(STAND_ROT);

		break;

	case CPetbottle::STATE_COLLAPSE:	// 倒れ状態

		// 回転処理
		Cycle();

		// 重力処理
		Gravity();

		if (Block() == true ||
			MagicWall() == true)
		{ // ブロックか部屋の端に当たった場合

			// 退場状態にする
			m_state = STATE_LEAVE;

			// この先の処理を行わない
			return;
		}

		break;

	case STATE_LEAVE:					// 退場状態

		// 透明度を減算する
		m_fAlpha -= 0.01f;

		if (m_fAlpha <= 0.0f)
		{ // 透明度が 0.0f 以下の場合

			// ペットボトルが転がる音を止める
			CManager::Get()->GetSound()->Stop(CSound::SOUND_LABEL_SE_PETBOTTLES_ROLL);

			// 終了処理
			Uninit();

			// この先の処理を行わない
			return;
		}

		break;

	default:

		// 停止
		assert(false);

		break;
	}

	// 起伏地面との当たり判定
	Elevation();
}

//=====================================
// ペットボトルの描画処理
//=====================================
void CPetbottle::Draw(void)
{
	switch (m_state)
	{
	case CPetbottle::STATE_LEAVE:

		// 描画処理
		CObstacle::Draw(m_fAlpha);

		break;

	default:

		// 描画処理
		CObstacle::Draw(1.0f);

		break;
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CPetbottle::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos,rot, type);

	// 向きを設定する
	SetRot(STAND_ROT);

	// 全ての値をクリアする
	m_move = NONE_D3DXVECTOR3;			// 移動量
	m_posPlayer = NONE_D3DXVECTOR3;		// ぶつかったプレイヤーの位置
	m_vtxMax = NONE_D3DXVECTOR3;		// 最大値
	m_vtxMin = NONE_D3DXVECTOR3;		// 最小値
	m_state = STATE_STAND;				// 状態
	m_fAlpha = 1.0f;					// 透明度
}

//=====================================
// 当たり判定処理
//=====================================
bool CPetbottle::Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// 位置を取得する
	D3DXVECTOR3 pos = pPlayer->GetPos();
	D3DXVECTOR3 move = pPlayer->GetMove();

	if (m_state == STATE_STAND)
	{ // 直立状態の場合

		if (pos.y <= GetPos().y + GetFileData().vtxMax.z &&
			pos.y + collSize.y >= GetPos().y + GetFileData().vtxMin.z)
		{ // ペットボトルと衝突した場合

			// 円柱の当たり判定処理
			useful::CylinderCollision(&pos, GetPos(), GetFileData().vtxMax.x + collSize.x);
		}
	}

	// 位置と移動量を適用する
	pPlayer->SetPos(pos);
	pPlayer->SetMove(move);

	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CPetbottle::Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// 最大値と最小値を設定する
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(collSize.x, collSize.y, collSize.z);
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);

	if (m_state == STATE_COLLAPSE &&
		pPlayer->GetType() == CPlayer::TYPE_RAT &&
		useful::RectangleCollisionXY(GetPos(), pPlayer->GetPos(), m_vtxMax, vtxMax, m_vtxMin, vtxMin) == true &&
		useful::RectangleCollisionXZ(GetPos(), pPlayer->GetPos(), m_vtxMax, vtxMax, m_vtxMin, vtxMin) == true &&
		useful::RectangleCollisionYZ(GetPos(), pPlayer->GetPos(), m_vtxMax, vtxMax, m_vtxMin, vtxMin) == true)
	{ // 倒れ状態かつ、当たり判定が true の場合

		// true を返す
		return true;
	}

	// false を返す
	return false;
}

//=====================================
// 円のヒット処理
//=====================================
bool CPetbottle::HitCircle(CPlayer* pPlayer, const float Radius)
{
	if (GetAction() == false &&
		useful::CircleCollisionXZ(pPlayer->GetPos(), GetPos(), Radius, GetFileData().fRadius) == true)
	{ // ペットボトルに衝突した場合

		// ぶつかったプレイヤーの位置を設定する
		m_posPlayer = pPlayer->GetPos();

		// true を返す
		return true;
	}

	// false を返す
	return false;
}

//=====================================
// ギミック起動処理
//=====================================
void CPetbottle::Action(void)
{
	// 位置と向きと方向を宣言する
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	float fAngle = 0.0f;

	// 倒れ状態にする
	m_state = STATE_COLLAPSE;
	SetFileData(CXFile::TYPE_RED_PETBOTTLE);

	// アクション状況を true にする
	SetAction(true);

	// ペットボトルが倒れる音を鳴らす
	CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_PETBOTTLES_FALL_DOWN);

	// 方向を設定する
	fAngle = atan2f((pos.x - m_posPlayer.x), (pos.z - m_posPlayer.z));

	// 向きを設定する
	rot.x = 0.0f;
	rot.z = 0.0f;

	if (fAngle >= D3DX_PI * -0.25f &&
		fAngle <= D3DX_PI * 0.25f)
	{ // 方向が手前からの場合

		// 向きを設定する
		rot.y = D3DX_PI * 0.5f;
	}
	else if (fAngle >= D3DX_PI * 0.25f &&
		fAngle <= D3DX_PI * 0.75f)
	{ // 方向が左からの場合

		// 向きを設定する
		rot.y = D3DX_PI;
	}
	else if (fAngle >= D3DX_PI * -0.75f &&
		fAngle <= D3DX_PI * -0.25f)
	{ // 方向が右からの場合

		// 向きを設定する
		rot.y = 0.0f;
	}
	else
	{ // 上記以外(方向が奥からの場合)

		// 向きを設定する
		rot.y = D3DX_PI * -0.5f;
	}

	// 向きを適用する
	SetRot(rot);

	// 当たり判定の設定処理
	CollsionSetting();

	// ペットボトルが転がる音を鳴らす
	CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_PETBOTTLES_ROLL);
}

//=====================================
// ブロックとの当たり判定
//=====================================
bool CPetbottle::Block(void)
{
	D3DXVECTOR3 pos = GetPos();			// 位置を取得する
	CBlock* pBlock = CBlockManager::Get()->GetTop();	// ブロックの先頭を取得する

	while (pBlock != nullptr)
	{ // ブロックが NULL じゃない限り回る

		// 六面体の当たり判定
		if (collision::HexahedronCollision
		(
			&pos,
			pBlock->GetPos(),
			GetPosOld(),
			pBlock->GetPosOld(),
			m_vtxMin,
			pBlock->GetVtxMin(),
			m_vtxMax,
			pBlock->GetVtxMax()
		) == true)
		{
			// true を返す
			return true;
		}

		// 次のブロックを取得する
		pBlock = pBlock->GetNext();
	}

	// false を返す
	return false;
}

//=====================================
// 回転処理
//=====================================
void CPetbottle::Cycle(void)
{
	// 情報を取得する
	D3DXVECTOR3 pos = GetPos();		// 位置
	D3DXVECTOR3 rot = GetRot();		// 向き

	// 移動量を設定する
	m_move.x = sinf(rot.y - (D3DX_PI * 0.5f)) * SPEED;
	m_move.z = cosf(rot.y - (D3DX_PI * 0.5f)) * SPEED;

	// 向きを加算する
	rot.z += ROT_MOVE;

	// 位置を移動する
	pos.x += m_move.x;
	pos.z += m_move.z;

	// 情報を適用する
	SetPos(pos);		// 位置
	SetRot(rot);		// 向き
}

//=====================================
// 重力処理
//=====================================
void CPetbottle::Gravity(void)
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
void CPetbottle::Elevation(void)
{
	// ローカル変数宣言
	CElevation* pMesh = CElevationManager::Get()->GetTop();		// 起伏の先頭のオブジェクトを取得する
	D3DXVECTOR3 pos = D3DXVECTOR3(GetPos().x, GetPos().y, GetPos().z);		// 位置を取得する
	float fHeight = 0.0f;					// 高さ

	while (pMesh != nullptr)
	{ // 地面の情報がある限り回す

		// 当たり判定を取る
		fHeight = pMesh->ElevationCollision(pos);

		if (pos.y + GetFileData().vtxMin.y <= fHeight)
		{ // 当たり判定の位置が高かった場合

			// 高さを設定する
			pos.y = fHeight - GetFileData().vtxMin.y;

			// 重力を初期化する
			m_move.y = 0.0f;
		}

		// 次のポインタを取得する
		pMesh = pMesh->GetNext();
	}

	// 位置を更新する
	SetPos(pos);
}

//=====================================
// 魔法の壁処理
//=====================================
bool CPetbottle::MagicWall(void)
{
	// 位置を取得する
	D3DXVECTOR3 pos = GetPos();

	if (pos.x + m_vtxMin.x <= -MAP_SIZE.x)
	{ // 位置が左から出そうな場合

		// true を返す
		return true;
	}

	if (pos.x + m_vtxMax.x >= MAP_SIZE.x)
	{ // 位置が右から出そうな場合

		// true を返す
		return true;
	}

	if (pos.z + m_vtxMin.z <= -MAP_SIZE.z)
	{ // 位置が右から出そうな場合

		// true を返す
		return true;
	}

	if (pos.z + m_vtxMax.z >= MAP_SIZE.z)
	{ // 位置が右から出そうな場合

		// true を返す
		return true;
	}

	// false を返す
	return false;
}

//=====================================
// 当たり判定の設定処理
//=====================================
void CPetbottle::CollsionSetting(void)
{
	// 向きと最大値と最小値を取得する
	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 vtxMin = GetFileData().vtxMin;
	D3DXVECTOR3 vtxMax = GetFileData().vtxMax;

	if (rot.y >= D3DX_PI * -0.25f &&
		rot.y <= D3DX_PI * 0.25f)
	{ // 方向が手前からの場合

		// 最大値と最小値を設定する
		m_vtxMax = vtxMax;
		m_vtxMin = vtxMin;
	}
	else if (rot.y >= D3DX_PI * 0.25f &&
		rot.y <= D3DX_PI * 0.75f)
	{ // 方向が左からの場合

		// 最大値と最小値を設定する
		m_vtxMax = D3DXVECTOR3(vtxMax.z, vtxMax.y, -vtxMin.x);
		m_vtxMin = D3DXVECTOR3(vtxMin.z, vtxMin.y, -vtxMax.x);
	}
	else if (rot.y >= D3DX_PI * -0.75f &&
		rot.y <= D3DX_PI * -0.25f)
	{ // 方向が右からの場合

		// 最大値と最小値を設定する
		m_vtxMax = D3DXVECTOR3(-vtxMin.z, vtxMax.y, vtxMax.x);
		m_vtxMin = D3DXVECTOR3(-vtxMax.z, vtxMin.y, vtxMin.x);
	}
	else
	{ // 上記以外(方向が奥からの場合)

		// 最大値と最小値を設定する
		m_vtxMax = D3DXVECTOR3(-vtxMin.x, vtxMax.y, -vtxMin.z);
		m_vtxMin = D3DXVECTOR3(-vtxMax.x, vtxMin.y, -vtxMax.z);
	}
}