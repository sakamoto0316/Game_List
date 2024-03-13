//===========================================
//
// 蜂蜜のメイン処理[honey.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "collision.h"
#include "input.h"
#include "fraction.h"
#include "renderer.h"
#include "honey.h"
#include "useful.h"
#include "Particle.h"
#include "sound.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define HONEY_SCALE			(D3DXVECTOR3(0.5f, 1.0f, 0.5f))		// 蜂蜜状態の拡大率
#define HONEY_FRAC_COUNT	(15)								// 蜂蜜の破片の数
#define HONEY_ADD_SCALE		(0.005f)							// 蜂蜜の拡大率の加算数
#define WALK_SE				(30)								// 歩くSEのカウント数

//==============================
// コンストラクタ
//==============================
CHoney::CHoney() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	m_State = STATE_HONEYBOTTLE;
	m_bLeakSe = false;		// 蜂蜜広がるSE
	m_nWalkSeCount = 0;	// 歩く音のカウンター
	SetCatUse(true);
	SetRatUse(false);
}

//==============================
// デストラクタ
//==============================
CHoney::~CHoney()
{

}

//==============================
// 破片の初期化処理
//==============================
HRESULT CHoney::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値をクリアする
	m_bLeakSe = false;		// 蜂蜜広がるSE
	m_nWalkSeCount = WALK_SE;		// 歩く音のカウンター

	// 値を返す
	return S_OK;
}

//========================================
// 破片の終了処理
//========================================
void CHoney::Uninit(void)
{
	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// 破片の更新処理
//=====================================
void CHoney::Update(void)
{
	//状態管理
	StateManager();
}

//=====================================
// 破片の描画処理
//=====================================
void CHoney::Draw(void)
{
	// 描画処理
	CObstacle::Draw(1.0f);
}

//=====================================
// 状態管理
//=====================================
void CHoney::StateManager(void)
{
	switch (m_State)
	{
	case CHoney::STATE_HONEYBOTTLE:

		break;

	case CHoney::STATE_HONEY:

		D3DXVECTOR3 Scale = GetScale();

		if (Scale.x <= 1.0f)
		{
			if (m_bLeakSe == false)
			{ // SE鳴らしてなかったら

				// 広がるSE再生
				CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_HONEYLEAK);

				m_bLeakSe = true;		// SE鳴らした状態にする
			}

			Scale.x += HONEY_ADD_SCALE;
			Scale.z += HONEY_ADD_SCALE;

			SetScale(Scale);
		}

		break;
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CHoney::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos,rot, type);
}

//=====================================
// 当たり判定処理
//=====================================
bool CHoney::Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// 座標関係の変数を設定する
	D3DXVECTOR3 pos = pPlayer->GetPos();		// 位置
	D3DXVECTOR3 move = pPlayer->GetMove();		// 移動量
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(collSize.x, collSize.y, collSize.z);	// 最大値
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);		// 最小値
	collision::SCollision coll = { false,false,false,false,false,false };

	if (m_State == STATE_HONEYBOTTLE)
	{ // 蜂蜜ボトル状態の場合

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
bool CHoney::Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// ローカル変数宣言
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(collSize.x, collSize.y, collSize.z);	// サイズの最大値
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);		// サイズの最小値

	if (m_State == STATE_HONEY &&
		useful::RectangleCollisionXY(GetPos(), pPlayer->GetPos(), GetFileData().vtxMax, vtxMax, GetFileData().vtxMin, vtxMin) == true &&
		useful::RectangleCollisionXZ(GetPos(), pPlayer->GetPos(), GetFileData().vtxMax, vtxMax, GetFileData().vtxMin, vtxMin) == true &&
		useful::RectangleCollisionYZ(GetPos(), pPlayer->GetPos(), GetFileData().vtxMax, vtxMax, GetFileData().vtxMin, vtxMin) == true)
	{ // 四角の当たり判定の中に入っていた場合

		CParticle::Create(pPlayer->GetPos(), CParticle::TYPE_HONEY);

		// true を返す
		return true;
	}
	else
	{ // 上記以外

		// false を返す
		return false;
	}
}

//=====================================
// ヒット処理
//=====================================
bool CHoney::HitCircle(CPlayer* pPlayer, const float Radius)
{
	m_nWalkSeCount++;		// 歩く音カウンター加算

	if (pPlayer->GetType() == CPlayer::TYPE_CAT &&
		GetAction() == false &&
		useful::CircleCollisionXZ(pPlayer->GetPos(), GetPos(), Radius, GetFileData().fRadius) == true)
	{ // 円の範囲内にいる場合

		if ((m_nWalkSeCount % WALK_SE) == 0 && m_State == STATE_HONEY)
		{ // 一定時間経ったら

			// 歩くSE再生
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_HONEYWALK);

			m_nWalkSeCount = 0;		// カウンター初期化
		}

		// true を返す
		return true;
	}

	// カウンター初期化
	m_nWalkSeCount = WALK_SE - 1;

	// false を返す
	return false;
}

//=====================================
// ギミック起動処理
//=====================================
void CHoney::Action(void)
{
	if (m_State == STATE_HONEYBOTTLE)
	{ // 蜂蜜ボトル状態の場合

		// 蜂蜜状態にする
		m_State = STATE_HONEY;

		// モデルの情報を設定する
		SetFileData(CXFile::TYPE_HONEY);

		// 割れるSE再生
		CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_HONEYBREAK);

		for (int nCnt = 0; nCnt < HONEY_FRAC_COUNT; nCnt++)
		{
			// 破片の生成処理
			CFraction::Create(GetPos(), CFraction::TYPE::TYPE_PRASTICRVASE);
		}

		// 拡大率を設定する
		SetScale(HONEY_SCALE);

		// アクション状況を true にする
		SetAction(true);
	}
}