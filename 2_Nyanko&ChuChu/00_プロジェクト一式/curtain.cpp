//===========================================
//
// カーテンの処理[curtain.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "curtain.h"
#include "useful.h"
#include "input.h"
#include "collision.h"
#include "game.h"
#include "sound.h"

#include "switch.h"

//-------------------------------------------
// 無名名前空間
//-------------------------------------------
namespace
{
	const D3DXVECTOR3 SWITCH_POS[MAP_TYPE][MAX_SWITCH] =		// スイッチの位置
	{
		{ // 1マップ目
			NONE_D3DXVECTOR3,
			NONE_D3DXVECTOR3,
			NONE_D3DXVECTOR3
		},

		{ // 2マップ目
			D3DXVECTOR3(-1390.0f, 290.0f, -640.0f),
			D3DXVECTOR3(714.0f, 290.0f, -274.0f),
			D3DXVECTOR3(300.0f, 290.0f, 980.0f),
		},

		{ // 3マップ目
			D3DXVECTOR3(750.0f, 256.0f, 980.0f),
			D3DXVECTOR3(-1336.0f, 256.0f, 40.0f),
			D3DXVECTOR3(-1582.0f, 256.0f, -650.0f),
		},
	};
	const D3DXVECTOR3 SWITCH_ROT[MAP_TYPE][MAX_SWITCH] =		// スイッチの向き
	{
		{ // 1マップ目
			NONE_D3DXVECTOR3,
			NONE_D3DXVECTOR3,
			NONE_D3DXVECTOR3
		},

		{ // 2マップ目
			D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f),
			D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f),
			D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f),
		},

		{ // 3マップ目
			D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f),
			D3DXVECTOR3(0.0f, D3DX_PI * 1.0f, 0.0f),
			D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f),
		},
	};
	const float CLOSE_SCALE = 0.03f;				// 閉じた状態の拡大率
	const float SCALE_CORRECT = 0.01f;				// 拡大率の補正率
	const float OPEN_SCALE = 1.0f;					// 開いた状態の拡大率
	const float ADD_SWITCH_RADIUS = 50.0f;			// 追加分のスイッチの半径
}

//==============================
// コンストラクタ
//==============================
CCurtain::CCurtain() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < MAX_SWITCH; nCnt++)
	{
		m_apSwitch[nCnt] = nullptr;		// スイッチの情報
	}
	m_state = STATE_CLOSE;				// 状態
	m_stateOld = m_state;				// 前回の状態
	m_vtxMax = NONE_D3DXVECTOR3;		// 最大値
	m_vtxMin = NONE_D3DXVECTOR3;		// 最小値
	m_fEdge = 0.0f;						// カーテンの端の座標
	SetCatUse(true);					// ネコの使用条件
	SetRatUse(true);					// ネズミの使用条件
}

//==============================
// デストラクタ
//==============================
CCurtain::~CCurtain()
{

}

//==============================
// カーテンの初期化処理
//==============================
HRESULT CCurtain::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // 初期化処理に失敗した場合

	  // 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	for (int nCnt = 0; nCnt < MAX_SWITCH; nCnt++)
	{
		m_apSwitch[nCnt] = nullptr;		// モデルの情報
	}
	m_state = STATE_CLOSE;				// 状態
	m_stateOld = m_state;				// 前回の状態
	m_vtxMax = NONE_D3DXVECTOR3;		// 最大値
	m_vtxMin = NONE_D3DXVECTOR3;		// 最小値
	m_fEdge = 0.0f;						// カーテンの端の座標

	// 値を返す
	return S_OK;
}

//========================================
// カーテンの終了処理
//========================================
void CCurtain::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_SWITCH; nCnt++)
	{
		if (m_apSwitch[nCnt] != nullptr)
		{ // スイッチの情報が NULL じゃない場合

			// スイッチの終了処理
			m_apSwitch[nCnt]->Uninit();
			m_apSwitch[nCnt] = nullptr;
		}
	}

	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// カーテンの更新処理
//=====================================
void CCurtain::Update(void)
{
	// 前回の位置を設定する
	SetPosOld(GetPos());

	// 状態マネージャー
	StateManager();

	for (int nCnt = 0; nCnt < MAX_SWITCH; nCnt++)
	{
		if (m_apSwitch[nCnt] != nullptr)
		{ // スイッチの情報が NULL じゃない場合

			// スイッチの更新処理
			m_apSwitch[nCnt]->Update();
		}
	}

	if (m_apSwitch[0]->GetBoot() == true &&
		m_apSwitch[1]->GetBoot() == true &&
		m_apSwitch[2]->GetBoot() == true)
	{ // 全てスイッチが入っていた場合

		// 開ける
		m_state = STATE_OPEN;
	}
	else
	{ // 上記以外

		// 閉じる
		m_state = STATE_CLOSE;
	}

	if (m_stateOld != m_state)
	{ // 状態が切り替わった場合

		// カーテンの稼働音を鳴らす
		CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_CURTAIN_OPEN);
	}

	// 前回の状態を設定する
	m_stateOld = m_state;

	// 拡大率の設定処理
	ScaleVtxSet();
}

//=====================================
// カーテンの描画処理
//=====================================
void CCurtain::Draw(void)
{
	// 描画処理
	CObstacle::Draw();

	for (int nCntSwith = 0; nCntSwith < MAX_SWITCH; nCntSwith++)
	{
		if (m_apSwitch[nCntSwith] != nullptr)
		{ // スイッチの情報が NULL じゃない場合

			for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
			{// どのプレイヤーのカメラ番号か回して確かめる
				if (CManager::Get()->GetMode() == CScene::MODE_GAME)
				{// ゲームモードの時
					CPlayer* pPlayer = CGame::GetPlayer(nCnt);
					if (pPlayer->GetType() == CPlayer::TYPE::TYPE_CAT)
					{// ネコプレイヤーを取得
						if (pPlayer->GetPlayerIdx() == GetDrawIdx())
						{// カメラ番号とプレイヤー番号が一致する時
							if (m_apSwitch[nCntSwith]->GetBoot() == true)
							{// テレビの電源がONの時リモコンの表示を薄くする

								// スイッチの描画処理
								m_apSwitch[nCntSwith]->Draw(1.0f);
							}
							else
							{
								// スイッチの描画処理
								m_apSwitch[nCntSwith]->Draw(0.3f);
							}
						}
					}
					else if (pPlayer->GetType() == CPlayer::TYPE::TYPE_RAT)
					{// ネズミプレイヤーを取得
						if (pPlayer->GetPlayerIdx() == GetDrawIdx())
						{// カメラ番号とプレイヤー番号が一致する時
							if (m_apSwitch[nCntSwith]->GetBoot() == false)
							{// テレビの電源がOFFの時リモコンの表示を薄くする

								// スイッチの描画処理
								m_apSwitch[nCntSwith]->Draw(1.0f);
							}
							else
							{
								// スイッチの描画処理
								m_apSwitch[nCntSwith]->Draw(0.3f);
							}
						}
					}
				}
			}

			//// スイッチの描画処理
			//m_apSwitch[nCnt]->Draw();
		}
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CCurtain::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos, rot, type);

	// 拡大率を初期化する
	SetScale(D3DXVECTOR3(1.0f, 1.0f, CLOSE_SCALE));

	if (CManager::Get()->GetMode() == CScene::MODE_GAME)
	{ // ゲームモードの場合

		// マップの番号を取得する
		int nMapNum = CGame::GetMapNumber();

		// 全ての値を設定する
		for (int nCnt = 0; nCnt < MAX_SWITCH; nCnt++)
		{
			if (m_apSwitch[nCnt] == nullptr)
			{ // モデルが NULL じゃない場合

				// スイッチの生成処理
				m_apSwitch[nCnt] = CSwitch::Create(SWITCH_POS[nMapNum][nCnt], SWITCH_ROT[nMapNum][nCnt]);
			}
		}
	}
	m_state = STATE_CLOSE;			// 状態

	// 頂点の設定処理
	VtxSetting();

	// 拡大率による頂点の設定処理
	ScaleVtxSet();
}

//=====================================
// 当たり判定処理
//=====================================
bool CCurtain::Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	D3DXVECTOR3 pos = pPlayer->GetPos();
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);	// 最小値
	D3DXVECTOR3 vtxMax = collSize;										// 最大値

	// 六面体の当たり判定
	collision::HexahedronCollision
	(
		&pos,
		GetPos(),
		pPlayer->GetPosOld(),
		GetPosOld(),
		vtxMin,
		m_vtxMin,
		vtxMax,
		m_vtxMax
	);

	// 位置を適用する
	pPlayer->SetPos(pos);

	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CCurtain::HitCircle(CPlayer* pPlayer, const float Radius)
{
	for (int nCnt = 0; nCnt < MAX_SWITCH; nCnt++)
	{
		if (m_apSwitch[nCnt] != nullptr)
		{ // スイッチの情報が NULL の場合

			if (useful::CircleCollisionXZ
			(
				pPlayer->GetPos(),
				m_apSwitch[nCnt]->GetModel(CSwitch::TYPE_BASE)->GetPos(),
				Radius,
				m_apSwitch[nCnt]->GetModel(CSwitch::TYPE_BASE)->GetFileData().fRadius + ADD_SWITCH_RADIUS
			) == true)
			{ // 円の当たり判定内に入った場合

				switch (pPlayer->GetType())
				{
				case CPlayer::TYPE_CAT:		// ネコ

					if (m_apSwitch[nCnt]->GetBoot() == true)
					{ // 起動状況が false の場合

						// ギミックUIの設定処理
						m_apSwitch[nCnt]->SetGimmickUI(true, pPlayer->GetPlayerIdx());
					}
					else
					{ // 上記以外

						// ギミックUIの設定処理
						m_apSwitch[nCnt]->SetGimmickUI(false, pPlayer->GetPlayerIdx());
					}

					break;

				case CPlayer::TYPE_RAT:		// ネズミ

					if (m_apSwitch[nCnt]->GetBoot() == false)
					{ // 起動状況が true の場合

						// ギミックUIの設定処理
						m_apSwitch[nCnt]->SetGimmickUI(true, pPlayer->GetPlayerIdx());
					}
					else
					{ // 上記以外

						// ギミックUIの設定処理
						m_apSwitch[nCnt]->SetGimmickUI(false, pPlayer->GetPlayerIdx());
					}

					break;

				default:

					// 停止
					assert(false);

					break;
				}
			}
			else
			{ // 上記以外

				// ギミックUIの設定処理
				m_apSwitch[nCnt]->SetGimmickUI(false, pPlayer->GetPlayerIdx());
			}
		}
	}

	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
void CCurtain::HitMultiCircle(CPlayer* pPlayer, const float Radius, bool bInput)
{
	for (int nCnt = 0; nCnt < MAX_SWITCH; nCnt++)
	{
		if (m_apSwitch[nCnt] != nullptr)
		{ // スイッチの情報が NULL の場合

			if (useful::CircleCollisionXZ
			(
				pPlayer->GetPos(),
				m_apSwitch[nCnt]->GetModel(CSwitch::TYPE_BASE)->GetPos(),
				Radius,
				m_apSwitch[nCnt]->GetModel(CSwitch::TYPE_BASE)->GetFileData().fRadius + ADD_SWITCH_RADIUS
			) == true)
			{ // 円の当たり判定内に入った場合

				if (bInput == true)
				{ // 入力状況が true の場合

					switch (pPlayer->GetType())
					{
					case CPlayer::TYPE_CAT:		// ネコ

						if (m_apSwitch[nCnt]->GetBoot() == true)
						{ // 起動状況が false の場合

							// 起動状況の入れ替え処理
							m_apSwitch[nCnt]->ChangeBoot();
						}

						break;

					case CPlayer::TYPE_RAT:		// ネズミ

						if (m_apSwitch[nCnt]->GetBoot() == false)
						{ // 起動状況が true の場合

							// 起動状況の入れ替え処理
							m_apSwitch[nCnt]->ChangeBoot();
						}

						break;

					default:

						// 停止
						assert(false);

						break;
					}
				}
			}
		}
	}
}

//=====================================
// 頂点の設定処理
//=====================================
void CCurtain::VtxSetting(void)
{
	// 向きと最大値・最小値を設定する
	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 vtxMax = GetFileData().vtxMax;
	D3DXVECTOR3 vtxMin = GetFileData().vtxMin;

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

//=====================================
// 拡大率による頂点の設定処理
//=====================================
void CCurtain::ScaleVtxSet(void)
{
	// 向きを取得する
	D3DXVECTOR3 rot = GetRot();

	// カーテンの端の座標を設定する
	m_fEdge = GetFileData().vtxMin.z * GetScale().z;

	if (rot.y >= D3DX_PI * -0.25f &&
		rot.y <= D3DX_PI * 0.25f)
	{ // 方向が手前からの場合

		// 頂点を設定する
		m_vtxMin.z = m_fEdge;
	}
	else if (rot.y >= D3DX_PI * 0.25f &&
		rot.y <= D3DX_PI * 0.75f)
	{ // 方向が左からの場合

		// 頂点を設定する
		m_vtxMin.x = m_fEdge;
	}
	else if (rot.y >= D3DX_PI * -0.75f &&
		rot.y <= D3DX_PI * -0.25f)
	{ // 方向が右からの場合

		// 頂点を設定する
		m_vtxMax.x = -m_fEdge;
	}
	else
	{ // 上記以外(方向が奥からの場合)

		// 頂点を設定する
		m_vtxMax.z = -m_fEdge;
	}
}

//=====================================
// 状態マネージャー
//=====================================
void CCurtain::StateManager(void)
{
	// 拡大率を取得する
	D3DXVECTOR3 scale = GetScale();

	switch (m_state)
	{
	case CCurtain::STATE_CLOSE:		// 閉じる状態

		// 均等な補正処理
		useful::FrameCorrect(CLOSE_SCALE, &scale.z, SCALE_CORRECT);

		break;

	case CCurtain::STATE_OPEN:		// 開いた状態

		// 均等な補正処理
		useful::FrameCorrect(OPEN_SCALE, &scale.z, SCALE_CORRECT);

		break;

	default:

		// 停止
		assert(false);

		break;
	}

	// 拡大率を適用する
	SetScale(scale);
}