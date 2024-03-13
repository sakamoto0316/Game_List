//===========================================
//
// 画鋲の処理[Pin.cpp]
// Author 坂本翔唯
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "Pin.h"
#include "useful.h"
#include "objectX.h"
#include "input.h"
#include "effect.h"
#include "fraction.h"
#include "sound.h"

#define ACTION_TIME (120)
#define WAIT_TIME (20)

//==============================
// コンストラクタ
//==============================
CPin::CPin() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	m_State = STATE_FALSE;
	m_move = NONE_D3DXVECTOR3;
	SetRatUse(true);
}

//==============================
// デストラクタ
//==============================
CPin::~CPin()
{

}

//==============================
// 画鋲の初期化処理
//==============================
HRESULT CPin::Init(void)
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
// 画鋲の終了処理
//========================================
void CPin::Uninit(void)
{
	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// 画鋲の更新処理
//=====================================
void CPin::Update(void)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	StateManager(&pos,&rot);

	//位置更新
	pos += m_move;

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_0) == true)
	{ // 0ボタンを押した場合
		Action();
	}

	SetPos(pos);
	SetRot(rot);
}

//=====================================
// 画鋲の描画処理
//=====================================
void CPin::Draw(void)
{
	// 描画処理
	CObstacle::Draw(1.0f);
}

//=====================================
// 状態管理
//=====================================
void CPin::StateManager(D3DXVECTOR3 *pos, D3DXVECTOR3 *rot)
{
	switch (m_State)
	{
	case CPin::STATE_FALSE:

		break;

	case CPin::STATE_FALLWAIT:	//ギミック起動から効果発動までの準備時間
		rot->z += 0.1f;
		m_move.y -= 0.75f;
		m_move.x = sinf(rot->y + (D3DX_PI * -0.5f)) * 4.0f;
		m_move.z = cosf(rot->y + (D3DX_PI * -0.5f)) * 4.0f;

		if (pos->y < 0)
		{
			pos->y = 0.0f;
			rot->z = 0.0f;
			m_State = STATE_TRUE;
			SetFileData(CXFile::TYPE_RED_PINSET);

			for (int nCnt = 0; nCnt < 20; nCnt++)
			{
				CFraction::Create(GetPos(), CFraction::TYPE_PIN);
			}

			// 画鋲が散る音を鳴らす
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_THUMBTACK);
		}
		break;

	case CPin::STATE_TRUE:	//ギミックの効果発動から停止までの処理
		m_move = NONE_D3DXVECTOR3;
		pos->y = 0.0f;
		break;
	}
}

//=====================================
// 両端起動時の処理
//=====================================
void CPin::Action(void)
{
	if (m_State == STATE_FALSE)
	{
		m_State = STATE_FALLWAIT;
		SetAction(true);
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CPin::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos,rot, type);
}

//=====================================
// ヒット処理
//=====================================
bool CPin::Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	if (m_State == STATE_TRUE)
	{ // ギミック発動状態の場合

		if (pPlayer->GetType() == CPlayer::TYPE_CAT)
		{ // 対象プレイヤーがネコだった場合

			// 最大値と最小値を設定する
			D3DXVECTOR3 vtxMax = D3DXVECTOR3(collSize.x, collSize.y, collSize.z);
			D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);

			if (useful::RectangleCollisionXY(pPlayer->GetPos(), GetPos(), vtxMax, GetFileData().vtxMax, vtxMin, GetFileData().vtxMin) == true &&
				useful::RectangleCollisionXZ(pPlayer->GetPos(), GetPos(), vtxMax, GetFileData().vtxMax, vtxMin, GetFileData().vtxMin) == true &&
				useful::RectangleCollisionYZ(pPlayer->GetPos(), GetPos(), vtxMax, GetFileData().vtxMax, vtxMin, GetFileData().vtxMin) == true)
			{ // 範囲内に入った場合

				// 終了処理
				Uninit();

				// true を返す
				return true;
			}
		}
	}

	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CPin::HitCircle(CPlayer* pPlayer, const float Radius)
{
	if (GetAction() == false &&
		useful::CircleCollisionXZ(pPlayer->GetPos(), GetPos(), Radius, GetFileData().fRadius) == true)
	{//円の範囲内の場合tureを返す
		return true;
	}

	// false を返す
	return false;
}