//===========================================
//
// リードの処理[Himo.cpp]
// Author 坂本翔唯
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "leash.h"
#include "useful.h"
#include "objectX.h"
#include "input.h"
#include "effect.h"
#include "collision.h"
#include "debugproc.h"
#include "tutorial.h"
#include "sound.h"

#define ACTION_TIME (240)
#define WAIT_TIME (20)

//==============================
// コンストラクタ
//==============================
CLeash::CLeash() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	m_move = NONE_D3DXVECTOR3;
	ActionPosHead = NONE_D3DXVECTOR3;
	ActionPosToes = NONE_D3DXVECTOR3;
	m_vtxMax = NONE_D3DXVECTOR3;			// 最大値
	m_vtxMin = NONE_D3DXVECTOR3;			// 最小値
	m_State = STATE_FALSE;
	m_bSe = false;							// SEの再生状況

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_bSetHead[nCnt] = false;
		m_bSetToes[nCnt] = false;
	}
	m_StateCount = 0;
	SetRatUse(true);
}

//==============================
// デストラクタ
//==============================
CLeash::~CLeash()
{

}

//==============================
// リードの初期化処理
//==============================
HRESULT CLeash::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // 初期化処理に失敗した場合

	  // 失敗を返す
		return E_FAIL;
	}

	m_move = NONE_D3DXVECTOR3;
	ActionPosHead = NONE_D3DXVECTOR3;
	ActionPosToes = NONE_D3DXVECTOR3;
	m_vtxMax = NONE_D3DXVECTOR3;			// 最大値
	m_vtxMin = NONE_D3DXVECTOR3;			// 最小値
	m_State = STATE_FALSE;
	m_bSe = false;							// SEの再生状況

	// 値を返す
	return S_OK;
}

//========================================
// リードの終了処理
//========================================
void CLeash::Uninit(void)
{
	// 終了処理y
	CObstacle::Uninit();
}

//=====================================
// リードの更新処理
//=====================================
void CLeash::Update(void)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	//ギミック起動時の処理
	if (((m_bSetHead[0] == true || m_bSetHead[1] == true || m_bSetHead[2] == true || m_bSetHead[3] == true) && 
		(m_bSetToes[0] == true || m_bSetToes[1] == true || m_bSetToes[2] == true || m_bSetToes[3] == true)) &&
		m_State == STATE_FALSE)
	{//起動していない時にネズミが両端を持ったら
		Action();

		// アクション状況を true にする
		SetAction(true);

		if (CManager::Get()->GetMode() == CScene::MODE_TUTORIAL)
		{
			CTutorial::SetMultiAction(true);
		}
	}

	CManager::Get()->GetDebugProc()->Print("\n");
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		if (m_bSetHead[nCnt] == true)
		{
			CManager::Get()->GetDebugProc()->Print("オン:");
		}
		else
		{
			CManager::Get()->GetDebugProc()->Print("オフ:");
		}
	}
	CManager::Get()->GetDebugProc()->Print("\n");
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		if (m_bSetToes[nCnt] == true)
		{
			CManager::Get()->GetDebugProc()->Print("オン:");
		}
		else
		{
			CManager::Get()->GetDebugProc()->Print("オフ:");
		}
	}
	CManager::Get()->GetDebugProc()->Print("\n");

	StateManager(&pos);

	//重力
	m_move.y -= 1.0f;

	//位置更新
	pos.y += m_move.y;

	//地面判定
	if (pos.y < 0.0f)
	{
		pos.y = 0.0f;
	}

	SetActionPos(pos, rot);

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_0) == true)
	{ // Aボタンを押した場合
		m_bSetHead[0] = true;
		m_bSetToes[0] = true;
	}

	SetPos(pos);
}

//=====================================
// リードの描画処理
//=====================================
void CLeash::Draw(void)
{
	// 描画処理
	CObstacle::Draw();
}

//=====================================
// 両端起動時の処理
//=====================================
void CLeash::Action(void)
{
	m_State = STATE_JUMPWAIT;
	m_StateCount = WAIT_TIME;
	m_move.y = 30.0f;
	SetAction(true);
}

//=====================================
// ギミック起動位置の設定
//=====================================
void CLeash::SetActionPos(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	ActionPosHead = D3DXVECTOR3(
		pos.x + sinf(rot.y + (D3DX_PI * 1.0f)) * 300.0f,
		pos.y,
		pos.z + cosf(rot.y + (D3DX_PI * 1.0f)) * 300.0f);

	ActionPosToes = D3DXVECTOR3(
		pos.x + sinf(rot.y + (D3DX_PI * 0.0f)) * 350.0f,
		pos.y,
		pos.z + cosf(rot.y + (D3DX_PI * 0.0f)) * 350.0f);
}

//=====================================
// 状態管理
//=====================================
void CLeash::StateManager(D3DXVECTOR3 *pos)
{
	switch (m_State)
	{
	case CLeash::STATE_FALSE:

		break;

	case CLeash::STATE_JUMPWAIT:	//ギミック起動から効果発動までの準備時間
		m_StateCount--;
		if (m_StateCount <= 0)
		{
			m_State = STATE_TRUE;
			m_StateCount = ACTION_TIME;
			SetFileData(CXFile::TYPE_RED_LEASHSET);

			
		}
		break;

	case CLeash::STATE_TRUE:	//ギミックの効果発動から停止までの処理
		m_StateCount--;

		if (pos->y < 200.0f)
		{
			pos->y = 200.0f;
			m_move.y = 0.0f;

			if (m_bSe == false)
			{ // SE再生してなかったら
				// リード音再生
				CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_LEASH);

				m_bSe = true;
			}
		}

		if (m_StateCount <= 0)
		{
			m_State = STATE_FALSE;
			for (int nCnt = 0; nCnt < 4; nCnt++)
			{
				m_bSetHead[nCnt] = false;
				m_bSetToes[nCnt] = false;
			}

			// アクション状況を false にする
			SetAction(false);

			SetFileData(CXFile::TYPE_LEASH);
		}
		break;
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CLeash::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos,rot, type);

	// 当たり判定の設定処理
	CollisionSetting();
}

//=====================================
// 当たり判定の設定処理
//=====================================
void CLeash::CollisionSetting(void)
{
	// 位置と向きと最小値と最大値を取得する
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 vtxMin = GetFileData().vtxMin;
	D3DXVECTOR3 vtxMax = GetFileData().vtxMax;

	if (rot.y >= D3DX_PI * -0.25f &&
		rot.y <= D3DX_PI * 0.25f)
	{ // 方向が手前からの場合

		// 最大値と最小値を設定する
		m_vtxMax = D3DXVECTOR3(0.0f, vtxMax.y, vtxMax.z);
		m_vtxMin = D3DXVECTOR3(0.0f, vtxMin.y, vtxMin.z);
	}
	else if (rot.y >= D3DX_PI * 0.25f &&
		rot.y <= D3DX_PI * 0.75f)
	{ // 方向が左からの場合

		// 最大値と最小値を設定する
		m_vtxMax = D3DXVECTOR3(vtxMax.z, vtxMax.y, 0.0f);
		m_vtxMin = D3DXVECTOR3(vtxMin.z, vtxMin.y, 0.0f);
	}
	else if (rot.y >= D3DX_PI * -0.75f &&
		rot.y <= D3DX_PI * -0.25f)
	{ // 方向が右からの場合

		// 最大値と最小値を設定する
		m_vtxMax = D3DXVECTOR3(-vtxMin.z, vtxMax.y, 0.0f);
		m_vtxMin = D3DXVECTOR3(-vtxMax.z, vtxMin.y, 0.0f);
	}
	else
	{ // 上記以外(方向が奥からの場合)

		// 最大値と最小値を設定する
		m_vtxMax = D3DXVECTOR3(0.0f, vtxMax.y, -vtxMin.z);
		m_vtxMin = D3DXVECTOR3(0.0f, vtxMin.y, -vtxMax.z);
	}
}

//=====================================
// ヒット処理
//=====================================
bool CLeash::Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// 最大値と最小値を設定する
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(collSize.x, collSize.y, collSize.z);
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);

	if (pPlayer->GetType() == CPlayer::TYPE_CAT)
	{ // ネコの場合

		if (m_State != STATE_FALSE &&
			useful::RectangleCollisionXY(pPlayer->GetPos(), GetPos(), vtxMax, m_vtxMax, vtxMin, m_vtxMin) == true &&
			useful::RectangleCollisionXZ(pPlayer->GetPos(), GetPos(), vtxMax, m_vtxMax, vtxMin, m_vtxMin) == true &&
			useful::RectangleCollisionYZ(pPlayer->GetPos(), GetPos(), vtxMax, m_vtxMax, vtxMin, m_vtxMin) == true)
		{ // 停止状態以外かつ、当たり判定の中に入った場合

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
bool CLeash::HitCircle(CPlayer* pPlayer, const float Radius)
{
	if (GetAction() == false)
	{ // アクション状況が false の場合

		if (useful::CircleCollisionXZ(pPlayer->GetPos(), ActionPosHead, Radius, GetFileData().fRadius) == true)
		{//円の範囲内の場合tureを返す
			return true;
		}

		if (useful::CircleCollisionXZ(pPlayer->GetPos(), ActionPosToes, Radius, GetFileData().fRadius) == true)
		{//円の範囲内の場合tureを返す
			return true;
		}
	}

	return false;
}

//=====================================
// ヒット処理
//=====================================
void CLeash::HitMultiCircle(CPlayer* pPlayer, const float Radius, bool bInput)
{
	if (GetAction() == false)
	{ // アクション状況が false の場合

		if (useful::CircleCollisionXZ(pPlayer->GetPos(), ActionPosHead, Radius, GetFileData().fRadius) == true)
		{//円の範囲内の場合tureを返す

			if (bInput == true)
			{//起動入力がある時
				m_bSetHead[pPlayer->GetPlayerIdx()] = true;
			}
		}
		else
		{
			m_bSetHead[pPlayer->GetPlayerIdx()] = false;
		}

		if (useful::CircleCollisionXZ(pPlayer->GetPos(), ActionPosToes, Radius, GetFileData().fRadius) == true)
		{//円の範囲内の場合tureを返す

			if (bInput == true)
			{//起動入力がある時
				m_bSetToes[pPlayer->GetPlayerIdx()] = true;
			}
		}
		else
		{
			m_bSetToes[pPlayer->GetPlayerIdx()] = false;
		}
	}
}