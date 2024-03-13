//===========================================
//
// おもちゃの車のメイン処理[toycar.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "toycar.h"
#include "useful.h"

#include "car_gear.h"
#include "collision.h"
#include "map.h"
#include "block.h"
#include "block_manager.h"
#include "obstacle.h"
#include "obstacle_manager.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define CAR_GEAR_SHIFT		(D3DXVECTOR3(0.0f, 40.0f, 0.0f))		// 車の歯車のずらす幅
#define CAR_SPEED			(-11.0f)		// 車の速度
#define CAR_CURVE_SPEED		(0.08f)			// 車の曲がる速度
#define CAR_DEST_ROT_SHIFT	(0.1f)			// 目的の向きの補正の許容範囲
#define CAR_BRAKE_COUNT		(40)			// ブレーキカウント数
#define ROTDEST_MAGNI_MIN	(8)				// 目的の向きの倍率の最小値
#define ROTDEST_MAGNI_RANGE	(11)			// 目的の向きの倍率の範囲

//==============================
// コンストラクタ
//==============================
CToyCar::CToyCar() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	m_pGear = nullptr;				// 歯車の情報
	m_move = NONE_D3DXVECTOR3;		// 移動量
	m_state = STATE_DRIVE;			// 状態
	m_nBrakeCount = 0;				// ブレーキカウント
	m_fRotDest = 0.0f;				// 目的の向き
	m_fRotMagni = 0.0f;				// 向きの倍率
	m_bRight = true;				// 右向き状況
}

//==============================
// デストラクタ
//==============================
CToyCar::~CToyCar()
{

}

//==============================
// 破片の初期化処理
//==============================
HRESULT CToyCar::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	m_pGear = nullptr;				// 歯車の値
	m_move = NONE_D3DXVECTOR3;		// 移動量
	m_state = STATE_DRIVE;			// 状態
	m_nBrakeCount = 0;				// ブレーキカウント
	m_fRotDest = 0.0f;				// 目的の向き
	m_fRotMagni = 0.0f;				// 向きの倍率
	m_bRight = true;				// 右向き状況

	// 値を返す
	return S_OK;
}

//========================================
// 破片の終了処理
//========================================
void CToyCar::Uninit(void)
{
	if (m_pGear != nullptr)
	{ // 歯車の情報が NULL じゃない場合

		// 終了処理
		m_pGear->Uninit();
		m_pGear = nullptr;
	}

	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// 破片の更新処理
//=====================================
void CToyCar::Update(void)
{
	// 前回の位置を設定する
	SetPosOld(GetPos());

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
			SetFileData((CXFile::TYPE)(CXFile::TYPE_TOYCARBODY));
			m_pGear->SetFileData((CXFile::TYPE)(CXFile::TYPE_TOYCARSCREW));

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
			SetFileData((CXFile::TYPE)(CXFile::TYPE_RED_TOYCARBODY));
			m_pGear->SetFileData((CXFile::TYPE)(CXFile::TYPE_RED_TOYCARSCREW));
		}

		break;

	default:

		// 停止
		assert(false);

		break;
	}

	if (m_pGear != nullptr)
	{ // 歯車が NULL じゃない場合

		// 位置を決定する
		m_pGear->SetPos(GetPos() + CAR_GEAR_SHIFT);

		// 更新処理
		m_pGear->Update();
	}
}

//=====================================
// 破片の描画処理
//=====================================
void CToyCar::Draw(void)
{
	// 描画処理
	CObstacle::Draw();

	if (m_pGear != nullptr)
	{ // 歯車が NULL じゃない場合

		// 描画処理
		m_pGear->Draw();
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CToyCar::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos, rot, type);

	if (m_pGear == nullptr)
	{ // 歯車の情報が NULL の場合

		// 歯車の生成
		m_pGear = CCarGear::Create(GetPos() + CAR_GEAR_SHIFT);
	}

	// 全ての値を設定する
	m_move = D3DXVECTOR3(sinf(rot.y) * CAR_SPEED, 0.0f, cosf(rot.y) * CAR_SPEED);	// 移動量
	m_state = STATE_DRIVE;			// 状態
	m_nBrakeCount = 0;				// ブレーキカウント
	m_fRotDest = 0.0f;				// 目的の向き
	m_fRotMagni = (float)((rand() % ROTDEST_MAGNI_RANGE + ROTDEST_MAGNI_MIN) * 0.1f);		// 向きの倍率
	m_bRight = true;				// 右向き状況
}

//=====================================
// 当たり判定処理
//=====================================
bool CToyCar::Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// 位置と最小値と最大値を宣言
	D3DXVECTOR3 pos = pPlayer->GetPos();
	D3DXVECTOR3 move = pPlayer->GetMove();
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);;
	D3DXVECTOR3 vtxMax = collSize;
	collision::SCollision coll = { false,false,false,false,false,false };

	if (pPlayer->GetType() == CPlayer::TYPE_RAT)
	{ // ネズミの場合

		// 六面体の当たり判定
		coll = collision::HexahedronClush(&pos, GetPos(), pPlayer->GetPosOld(), GetPosOld(), vtxMin, GetFileData().vtxMin, vtxMax, GetFileData().vtxMax);

		// 位置を適用する
		pPlayer->SetPos(pos);

		if (coll.bTop == true)
		{ // 上に乗った場合

			// 移動量を初期化する
			move.y = 0.0f;

			// 移動量を適用する
			pPlayer->SetMove(move);

			// true を返す
			return true;
		}
	}

	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CToyCar::Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// 最小値と最大値を宣言
	D3DXVECTOR3 pos = pPlayer->GetPos();
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);
	D3DXVECTOR3	vtxMax = collSize;

	if (pPlayer->GetType() == CPlayer::TYPE_RAT &&
		m_state == STATE_DRIVE)
	{ // ネズミかつ、ドライブ状態の場合

		if (collision::HexahedronCollision
		(
			&pos,
			GetPos(),
			pPlayer->GetPosOld(),
			GetPosOld(),
			vtxMin,
			GetFileData().vtxMin,
			vtxMax,
			GetFileData().vtxMax
		) == true)
		{ // 車に当たった場合

			// true を返す
			return true;
		}
	}

	// false を返す
	return false;
}

//=====================================
// 走行処理
//=====================================
void CToyCar::Drive(void)
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
void CToyCar::Curve(void)
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
void CToyCar::RotCalc(void)
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
bool CToyCar::Block(void)
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
bool CToyCar::Obstacle(void)
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
bool CToyCar::MagicWall(void)
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