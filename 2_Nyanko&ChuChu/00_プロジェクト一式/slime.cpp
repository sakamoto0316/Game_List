//===========================================
//
// スライムのメイン処理[slime.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "slime.h"
#include "useful.h"
#include "Particle.h"

//==============================
// コンストラクタ
//==============================
CSlime::CSlime() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{

}

//==============================
// デストラクタ
//==============================
CSlime::~CSlime()
{

}

//==============================
// 破片の初期化処理
//==============================
HRESULT CSlime::Init(void)
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
void CSlime::Uninit(void)
{
	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// 破片の更新処理
//=====================================
void CSlime::Update(void)
{

}

//=====================================
// 破片の描画処理
//=====================================
void CSlime::Draw(void)
{
	// 描画処理
	CObstacle::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CSlime::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos,rot, type);
}

//=====================================
// ヒット処理
//=====================================
bool CSlime::Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// ローカル変数宣言
	D3DXVECTOR3 max = D3DXVECTOR3(collSize.x, collSize.y, collSize.z);		// サイズの最大値
	D3DXVECTOR3 min = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);			// サイズの最小値

	if (useful::RectangleCollisionXY(GetPos(), pPlayer->GetPos(), GetFileData().vtxMax, max, GetFileData().vtxMin, min) == true &&
		useful::RectangleCollisionXZ(GetPos(), pPlayer->GetPos(), GetFileData().vtxMax, max, GetFileData().vtxMin, min) == true &&
		useful::RectangleCollisionYZ(GetPos(), pPlayer->GetPos(), GetFileData().vtxMax, max, GetFileData().vtxMin, min) == true)
	{ // 四角の当たり判定の中に入っていた場合
		CParticle::Create(pPlayer->GetPos(), CParticle::TYPE_SLIME);
		// true を返す
		return true;
	}
	else
	{ // 上記以外

		// false を返す
		return false;
	}
}