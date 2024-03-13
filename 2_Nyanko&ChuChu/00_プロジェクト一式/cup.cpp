//===========================================
//
// コップの処理[cup.cpp]
// Author 坂本翔唯
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "cup.h"
#include "useful.h"
#include "objectX.h"
#include "consent.h"
#include "object3D.h"
#include "input.h"
#include "texture.h"
#include "effect.h"
#include "sound.h"

//==============================
// コンストラクタ
//==============================
CCup::CCup() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	m_move = NONE_D3DXVECTOR3;
	m_State = STATE_FALSE;
	m_pWater = NULL;
	m_pConsent = NULL;
	m_WaterSize = NONE_D3DXVECTOR3;
	m_ThunderCounter = 0;
	m_bSe = false;				// SE再生状況
	SetRatUse(true);
}

//==============================
// デストラクタ
//==============================
CCup::~CCup()
{

}

//==============================
// コップの初期化処理
//==============================
HRESULT CCup::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // 初期化処理に失敗した場合

	  // 失敗を返す
		return E_FAIL;
	}

	m_bSe = false;				// SE再生状況

	// 値を返す
	return S_OK;
}

//========================================
// コップの終了処理
//========================================
void CCup::Uninit(void)
{
	if (m_pConsent != NULL)
	{ // コンセントが NULL の場合

		// コンセントの終了処理
		m_pConsent->Uninit();
	}

	if (m_pWater != NULL)
	{ // 水が NULL の場合

		// 水の終了処理
		m_pWater->Uninit();
	}

	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// コップの更新処理
//=====================================
void CCup::Update(void)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	StateManager(&pos, &rot);

	//位置更新
	pos += m_move;

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_0) == true)
	{ // 0ボタンを押した場合
		Action();
	}

	SetPos(pos);
	SetRot(rot);

	if (m_pWater != NULL)
	{ // 水が NULL じゃない場合

		// 水の更新処理
		m_pWater->Update();
	}
}

//=====================================
// コップの描画処理
//=====================================
void CCup::Draw(void)
{
	// 描画処理
	CObstacle::Draw(1.0f);

	if (m_pConsent != NULL)
	{
		if (m_State == STATE_TRUE)
		{
			m_pConsent->Draw(1.0f);
		}
		else
		{
			m_pConsent->Draw(0.3f);
		}
	}

	if (m_pWater != NULL)
	{
		m_pWater->Draw();
	}
}

//=====================================
// 状態管理
//=====================================
void CCup::StateManager(D3DXVECTOR3 *pos, D3DXVECTOR3 *rot)
{
	switch (m_State)
	{
	case CCup::STATE_FALSE:

		break;

	case CCup::STATE_FALLWAIT:	//ギミック起動から効果発動までの準備時間
		rot->z += 0.07f;
		m_move.y -= 0.75f;
		m_move.x = sinf(rot->y + (D3DX_PI * -0.5f)) * 4.0f;
		m_move.z = cosf(rot->y + (D3DX_PI * -0.5f)) * 4.0f;

		if (pos->y < 15.0f)
		{
			pos->y = 15.0f;
			m_State = STATE_TRUE;

			// コップが落ちた音を流す
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_THE_CUP_FALLS);

			// ビリビリ音を流す
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_WATERBIRIBIRI);

			m_pWater = CObject3D::Create(CObject3D::TYPE_NONE, PRIORITY_BLOCK);
			m_pWater->SetPos(GetPos());
			m_pWater->SetRot(D3DXVECTOR3(D3DX_PI * 0.5f, rot->y, 0.0f));
			m_pWater->SetSize(m_WaterSize);
			m_pWater->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\water.png"));
		}
		break;

	case CCup::STATE_TRUE:	//ギミックの効果発動から停止までの処理
		m_move = NONE_D3DXVECTOR3;
		pos->y = 15.0f;
		m_ThunderCounter++;

		D3DXVECTOR3 WaterPos = m_pWater->GetPos();

		if (m_WaterSize.x < 150.0f)
		{
			WaterPos.x += sinf(rot->y + (D3DX_PI * -0.5f)) * 0.5f;
			WaterPos.z += cosf(rot->y + (D3DX_PI * -0.5f)) * 0.5f;
			m_WaterSize.x += 0.5f;
			m_WaterSize.y += 0.5f;
		}

		if (m_ThunderCounter % 2 == 0)
		{
			int nRandX = rand() % (int)(m_WaterSize.x * 2.0f);
			int nRandZ = rand() % (int)(m_WaterSize.y * 2.0f);
			int nHalf = (int)m_WaterSize.x;
			CEffect *pEffect = CEffect::Create(D3DXVECTOR3(WaterPos.x + (nRandX - nHalf), WaterPos.y, WaterPos.z + (nRandZ - nHalf)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10, 30.0f, CEffect::TYPE::TYPE_THUNDER, NONE_D3DXCOLOR, true);
		}

		m_pWater->SetPos(WaterPos);
		m_pWater->SetSize(m_WaterSize);
		break;
	}
}

//=====================================
// コップがおちるときの処理
//=====================================
void CCup::Action(void)
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
void CCup::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos, rot, type);

	if (m_pConsent == NULL)
	{
		m_pConsent = CConsent::Create(D3DXVECTOR3(
			pos.x + sinf(rot.y + (D3DX_PI * -0.5f)) * 200.0f,
			0.0f,
			pos.z + cosf(rot.y + (D3DX_PI * -0.5f)) * 200.0f));
		m_pConsent->SetRot(D3DXVECTOR3(0.0f, rot.y + D3DX_PI * 1.0f, 0.0f));
		m_pConsent->SetMain(this);
	}
}

//=====================================
// ヒット処理
//=====================================
bool CCup::Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	if (m_pWater != nullptr)
	{ // 水が NULL じゃない場合

		// 水の位置と半径を取得する
		D3DXVECTOR3 posWater = m_pWater->GetPos();
		float radiusWater = m_pWater->GetSize().x;

		if (posWater.y >= pPlayer->GetPos().y &&
			posWater.y <= pPlayer->GetPos().y + collSize.y &&
			pPlayer->GetState() != CPlayer::STATE_INVINCIBLE &&
			useful::CylinderInner(pPlayer->GetPos(), posWater, radiusWater) == true)
		{ // 当たり判定の中に入った場合

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
bool CCup::HitCircle(CPlayer* pPlayer, const float Radius)
{
	if (GetAction() == false &&
		useful::CircleCollisionXZ(pPlayer->GetPos(), GetPos(), Radius, GetFileData().fRadius) == true)
	{//円の範囲内の場合tureを返す
		return true;
	}

	// false を返す
	return false;
}