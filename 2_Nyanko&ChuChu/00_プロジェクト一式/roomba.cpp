//===========================================
//
// ルンバのメイン処理[roomba.cpp]
// Author 坂本翔唯
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "roomba.h"
#include "model.h"
#include "useful.h"

#include "player.h"
#include "sound.h"

//==============================
// コンストラクタ
//==============================
CRoomba::CRoomba() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_apSub[nCnt] = NULL;
	}

	m_move = NONE_D3DXVECTOR3;
}

//==============================
// デストラクタ
//==============================
CRoomba::~CRoomba()
{

}

//==============================
// ルンバの初期化処理
//==============================
HRESULT CRoomba::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // 初期化処理に失敗した場合

	  // 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_apSub[nCnt] = NULL;
	}

	//// 掃除音を鳴らす
	//CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_CLEANING);
	
	// 値を返す
	return S_OK;
}

//========================================
// ルンバの終了処理
//========================================
void CRoomba::Uninit(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_apSub[nCnt] != NULL)
		{ // プロペラが NULL じゃない場合

			// プロペラの終了処理
			m_apSub[nCnt]->Uninit();
			m_apSub[nCnt] = NULL;
		}
	}

	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// ルンバの更新処理
//=====================================
void CRoomba::Update(void)
{
	//位置を向きの取得
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	//本体の向きを動かす
	rot.y -= 0.005f;

	//向いている方向に移動する処理
	Move(rot);

	//プロペラの位置と向きの更新
	SubUpdate();

	//位置更新
	pos += m_move;

	//位置と向きの更新
	SetPos(pos);
	SetRot(rot);
}

//=====================================
// 移動処理
//=====================================
void CRoomba::Move(D3DXVECTOR3 rot)
{
	m_move = D3DXVECTOR3(
		sinf(rot.y + (D3DX_PI * 1.0f)) * 2.0f,
		0.0f,
		cosf(rot.y + (D3DX_PI * 1.0f)) * 2.0f);
}

//=====================================
// プロペラの更新処理
//=====================================
void CRoomba::SubUpdate(void)
{
	//位置と向きの取得
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	//プロペラの向きを取得
	D3DXVECTOR3 Subrot[2] = {};
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		Subrot[nCnt] = m_apSub[nCnt]->GetRot();
	}

	//プロペラを回す
	Subrot[0].y += 0.1f;
	Subrot[1].y -= 0.1f;

	//プロペラの位置更新
	m_apSub[0]->SetPos(D3DXVECTOR3(
		pos.x + sinf(rot.y + (D3DX_PI * 0.75f)) * 50.0f,
		pos.y,
		pos.z + cosf(rot.y + (D3DX_PI * 0.75f)) * 50.0f));

	m_apSub[1]->SetPos(D3DXVECTOR3(
		pos.x + sinf(rot.y + (D3DX_PI * -0.75f)) * 50.0f,
		pos.y,
		pos.z + cosf(rot.y + (D3DX_PI * -0.75f)) * 50.0f));

	//プロペラの向きを更新する
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_apSub[nCnt]->SetRot(Subrot[nCnt]);
	}
}

//=====================================
// ルンバの描画処理
//=====================================
void CRoomba::Draw(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_apSub[nCnt] != NULL)
		{ // プロペラが NULL じゃない場合

			// プロペラの描画処理
			m_apSub[nCnt]->Draw();
		}
	}

	// 描画処理
	CObstacle::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CRoomba::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos,rot, type);

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_apSub[nCnt] == NULL)
		{ // プロペラが NULL の場合

			// モデルを生成する
			m_apSub[nCnt] = CModel::Create(TYPE_NONE, PRIORITY_BLOCK);

			if (m_apSub[nCnt] != NULL)
			{ // プロペラが NULL の場合

				switch (nCnt)
				{
				case 0:

					// プロペラの位置設定
					m_apSub[nCnt]->SetPos(D3DXVECTOR3(
						pos.x + sinf(rot.y + (D3DX_PI * 0.75f)) * 50.0f,
						pos.y,
						pos.z + cosf(rot.y + (D3DX_PI * 0.75f)) * 50.0f));

					break;

				case 1:

					// プロペラの位置設定
					m_apSub[nCnt]->SetPos(D3DXVECTOR3(
						pos.x + sinf(rot.y + (D3DX_PI * -0.75f)) * 50.0f,
						pos.y,
						pos.z + cosf(rot.y + (D3DX_PI * -0.75f)) * 50.0f));

					break;

				default:

					// 停止
					assert(false);

					break;
				}

				m_apSub[nCnt]->SetFileData((CXFile::TYPE::TYPE_RED_ROOMBA_SUB));	// モデル情報
			}
			else
			{ // 上記以外

				// 停止
				assert(false);
			}
		}
		else
		{ // 上記以外

			// 停止
			assert(false);
		}
	}
}

//=====================================
// 当たり判定処理
//=====================================
bool CRoomba::Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// 位置、半径、高さを取得する
	D3DXVECTOR3 pos = pPlayer->GetPos();
	D3DXVECTOR3 objPos = GetPos();
	float objRadius = GetFileData().fRadius;
	float objHeight = GetFileData().vtxMax.y;

	if (pPlayer->GetType() == CPlayer::TYPE_RAT)
	{ // ネズミの場合

		if (objPos.y <= pos.y + collSize.y &&
			objPos.y + objHeight >= pos.y)
		{ // 高さの判定

			if (useful::CylinderCollision(&pos, objPos, collSize.x + objRadius))
			{ // 円の中に入る場合

				// 位置を適用する
				pPlayer->SetPos(pos);

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
bool CRoomba::Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// 位置、半径、高さを取得する
	D3DXVECTOR3 objPos = GetPos();
	float objRadius = GetFileData().fRadius;
	float objHeight = GetFileData().vtxMax.y;

	if (objPos.y <= pPlayer->GetPos().y + collSize.y &&
		objPos.y + objHeight >= pPlayer->GetPos().y &&
		useful::CylinderInner(pPlayer->GetPos(), objPos, collSize.x + objRadius) &&
		pPlayer->GetType() == CPlayer::TYPE_RAT)
	{ // ネズミが円の中に入った場合

		// true を返す
		return true;
	}

	// false を返す
	return false;
}