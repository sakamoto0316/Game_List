//===========================================
//
// テレビの処理[cup.cpp]
// Author 堀川萩大
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "tv.h"
#include "model.h"
#include "useful.h"
#include "input.h"
#include "texture.h"
#include "sound.h"
#include "object3D.h"
#include "objectbillboard.h"

#include "player.h"
#include "collision.h"
#include "game.h"

//------------------------------
// 無名名前関数
//------------------------------
namespace
{
	const D3DXVECTOR3 REMOCON_POS[MAP_TYPE] =		// リモコンの位置
	{
		D3DXVECTOR3(-280.0f, 200.0f, -50.0f),
		D3DXVECTOR3(-1490.0f, 196.0f, 404.0f),
		D3DXVECTOR3(1020.0f, 212.0f, -350.0f),
	};
	const D3DXVECTOR3 REMOCON_ROT[MAP_TYPE] =		// リモコンの向き
	{
		D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI * 1.0f, 0.0f),
		D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f),
	};
	const int COOL_TIME = 300;			// クールタイム
	const int CHANGE_TIME = 120;		// 画面変化速度
	const D3DXVECTOR3 VISION_SIZE = D3DXVECTOR3(150.0f, 80.0f, 0.0f);	// ビジョンのサイズ
	const char* NONE_TEXTURE = "data\\TEXTURE\\TV000.png";				// 何でもない画面のテクスチャ
	const char* BOMB_TEXTURE = "data\\TEXTURE\\TV001.png";				// 爆弾の画面のテクスチャ
	const char* COOLTIME_TEXTURE = "data\\TEXTURE\\TV_sandstorm.jpg";	// クールタイム中のテクスチャ
	const float CAT_RADIUS = 140.0f;	// ネコの半径
	const float RAT_RADIUS = 80.0f;		// ネズミの半径
}

//==============================
// コンストラクタ
//==============================
CTv::CTv() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	m_State = STATE_NONE;				// アイテムが取れる状態に
	m_pVision = nullptr;				// ポリゴン情報をnullptr
	m_remocon.pRemocon = nullptr;		// リモコン情報をnullptr
	m_remocon.pGimmickUI = nullptr;		// ギミックUIをnullptr
	m_vtxMax = NONE_D3DXVECTOR3;		// 最大値
	m_vtxMin = NONE_D3DXVECTOR3;		// 最小値
	m_nCoolTime = 0;					// クールタイム
	m_nChangeVision = 0;		// 画面変化処理
	m_bPower = false;				// 電源
	SetRatUse(false);					// ネズミが使用できるか
	SetCatUse(true);					// ネコが使用できるか
}

//==============================
// デストラクタ
//==============================
CTv::~CTv()
{

}

//==============================
// テレビの初期化処理
//==============================
HRESULT CTv::Init(void)
{
	// 全ての値をクリアする
	m_State = STATE_NONE;				// アイテムが取れる状態に
	m_pVision = nullptr;				// ポリゴン情報をnullptr
	m_remocon.pRemocon = nullptr;		// リモコン情報をnullptr
	m_remocon.pGimmickUI = nullptr;		// ギミックUIをnullptr
	m_vtxMax = NONE_D3DXVECTOR3;		// 最大値
	m_vtxMin = NONE_D3DXVECTOR3;		// 最小値
	m_nCoolTime = 0;					// クールタイム
	m_nChangeVision = 0;		// 画面変化処理
	m_bPower = false;				// 電源

	if (FAILED(CObstacle::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	if (CManager::Get()->GetMode() == CScene::MODE_GAME)
	{ //ゲームモードの場合

		// マップの番号を取得する
		int nMapNum = CGame::GetMapNumber();

		// リモコンを生成
		m_remocon.pRemocon = CModel::Create(TYPE_NONE, PRIORITY_BLOCK);

		if (m_remocon.pRemocon != nullptr)
		{ // リモコンが NULL じゃない場合

			// 情報の設定処理
			m_remocon.pRemocon->SetPos(REMOCON_POS[nMapNum]);		// 位置
			m_remocon.pRemocon->SetPosOld(REMOCON_POS[nMapNum]);	// 前回の位置
			m_remocon.pRemocon->SetRot(REMOCON_ROT[nMapNum]);		// 向き
			m_remocon.pRemocon->SetScale(NONE_SCALE);				// 拡大率
			m_remocon.pRemocon->SetFileData(CXFile::TYPE_REMOCON);	// モデルの情報
		}
	}

	// 使用条件
	SetRatUse(false);								// ネズミが使用できるか
	SetCatUse(true);								// ネコが使用できるか

	// 値を返す
	return S_OK;
}

//========================================
// テレビの終了処理
//========================================
void CTv::Uninit(void)
{
	if (m_pVision != nullptr)
	{ // テレビ画面が NULL の場合

		// テレビ画面の終了処理
		m_pVision->Uninit();
		m_pVision = nullptr;
	}

	if (m_remocon.pRemocon != nullptr)
	{ // リモコンが NULL の場合

		// リモコンの終了処理
		m_remocon.pRemocon->Uninit();
		m_remocon.pRemocon = nullptr;
	}

	if (m_remocon.pGimmickUI != nullptr)
	{ // ギミックUIが NULL の場合

		// ギミックUIの終了処理
		m_remocon.pGimmickUI->Uninit();
		m_remocon.pGimmickUI = nullptr;
	}

	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// テレビの更新処理
//=====================================
void CTv::Update(void)
{
	// 状態マネージャー
	StateManager();

	// テレビ画面切り替え処理
	VisionChange();

	if (m_pVision != nullptr)
	{ // テレビ画面が NULL じゃない場合

		// テレビ画面の更新処理
		m_pVision->Update();
	}

	if (m_remocon.pRemocon != nullptr)
	{	// リモコンのモデルがnullではないとき

		if (HitRemocon() == true)
		{	// 周りにプレイヤーがいたら

			if (m_remocon.pGimmickUI == nullptr)
			{ // ギミックUIが NULL の場合

				//UIの表示
				m_remocon.pGimmickUI = CBillboard::Create(TYPE_NONE, PRIORITY_UI);
				m_remocon.pGimmickUI->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\UI_GimmickOn.png"));
				m_remocon.pGimmickUI->SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0f));

				m_remocon.pGimmickUI->SetPos(D3DXVECTOR3(
					m_remocon.pRemocon->GetPos().x,
					m_remocon.pRemocon->GetPos().y + 50.0f,
					m_remocon.pRemocon->GetPos().z));
				m_remocon.pGimmickUI->SetPosOld(D3DXVECTOR3(
					m_remocon.pRemocon->GetPos().x,
					m_remocon.pRemocon->GetPos().y + 50.0f,
					m_remocon.pRemocon->GetPos().z));

				m_remocon.pGimmickUI->SetVertex();
			}

			if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_B, 0) == true ||
				CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_B, 1) == true ||
				CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_B, 2) == true ||
				CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_B, 3) == true ||
				CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_E) == true)
			{	// ボタンが押されたとき

				//　テレビの電源操作
				PowerAction();
			}
		}
		else
		{ // 上記以外

			if (m_remocon.pGimmickUI != nullptr)
			{ // ギミックUIが NULL じゃない場合

				// ギミックUIの終了処理
				m_remocon.pGimmickUI->Uninit();
				m_remocon.pGimmickUI = nullptr;
			}
		}

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_0) == true)
		{	// ボタンが押されたとき

			//　テレビの電源操作
			PowerAction();
		}
	}
}

//=====================================
// テレビの描画処理
//=====================================
void CTv::Draw(void)
{
	// 描画処理
	if (m_bPower == true)
	{// テレビの電源がOFFの時薄くする
		CObstacle::Draw(1.0f);
	}
	else
	{
		CObstacle::Draw(0.3f);
	}

	if (m_remocon.pRemocon != nullptr)
	{ // リモコンが NULL じゃない場合

		for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
		{// どのプレイヤーのカメラ番号か回して確かめる
			if (CManager::Get()->GetMode() == CScene::MODE_GAME)
			{// ゲームモードの時
				CPlayer* pPlayer = CGame::GetPlayer(nCnt);
				if (pPlayer->GetType() == CPlayer::TYPE::TYPE_CAT)
				{// ネコプレイヤーを取得
					if (pPlayer->GetPlayerIdx() == GetDrawIdx())
					{// カメラ番号とプレイヤー番号が一致する時
						if (m_bPower == true)
						{// テレビの電源がONの時リモコンの表示を薄くする

							// 描画処理
							m_remocon.pRemocon->Draw(0.3f);
						}
						else
						{
							// 描画処理
							m_remocon.pRemocon->Draw(1.0f);
						}
					}
				}
				else if (pPlayer->GetType() == CPlayer::TYPE::TYPE_RAT)
				{// ネズミプレイヤーを取得
					if (pPlayer->GetPlayerIdx() == GetDrawIdx())
					{// カメラ番号とプレイヤー番号が一致する時
						if (m_bPower == false)
						{// テレビの電源がOFFの時リモコンの表示を薄くする

							// 描画処理
							m_remocon.pRemocon->Draw(0.3f);
						}
						else
						{
							// 描画処理
							m_remocon.pRemocon->Draw(1.0f);
						}
					}
				}
			}
		}
	}

	if (m_pVision != nullptr)
	{ // ビジョンが NULL じゃない場合

		// 描画処理
		m_pVision->DrawLightOff();
	}

	if (m_remocon.pGimmickUI != nullptr)
	{ // ギミックUIが NULL じゃない場合

		// 描画処理
		m_remocon.pGimmickUI->Draw();
	}
}

//=====================================
// 状態管理
//=====================================
void CTv::StateManager(void)
{
	if (m_pVision != nullptr)
	{ // 画面が NULL じゃない場合

		switch (m_State)
		{
		case STATE_NONE:	// 何でもない画面の時

			break;

		case STATE_BOMB:	// 爆弾の画面の時

			break;

		case STATE_COOLDOWN:	// クールタイム中

			// クールタイムを減算する
			m_nCoolTime--;

			if (m_nCoolTime <= 0)
			{ // クールタイムが 0 以下になった場合

				// 通常状態にする
				m_State = STATE_NONE;
			}

			break;

		default:

			// 停止
			assert(false);

			break;
		}
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CTv::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos, rot, type);

	// 最大値と最小値を取得する
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

//=====================================
// 当たり判定処理
//=====================================
bool CTv::Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// 位置と最小値と最大値を設定する
	D3DXVECTOR3 pos = pPlayer->GetPos();
	D3DXVECTOR3 move = pPlayer->GetMove();
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(collSize.x, collSize.y, collSize.z);
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);
	collision::SCollision coll = { false,false,false,false,false,false };

	// 六面体の当たり判定
	coll = collision::HexahedronClush
	(
		&pos,					// プレイヤーの位置
		GetPos(),				// 位置
		pPlayer->GetPosOld(),	// プレイヤーの前回の位置
		GetPosOld(),			// 前回の位置
		vtxMin,					// プレイヤーの最小値
		m_vtxMin,				// 最小値
		vtxMax,					// プレイヤーの最大値
		m_vtxMax				// 最大値
	);

	// 位置を適用する
	pPlayer->SetPos(pos);

	if(coll.bTop == true)
	{ // 上に乗った場合

		// 移動量を初期化する
		move.y = 0.0f;

		// 移動量を適用する
		pPlayer->SetMove(move);

		// true を返す
		return true;
	}

	// false を返す
	return false;
}

//=====================================
// ヒットサークル処理
//=====================================
bool CTv::HitCircle(CPlayer* pPlayer, const float Radius)
{
	if (m_bPower == true && 
		m_State != STATE_COOLDOWN &&
		m_State != STATE_NONE &&
		pPlayer->GetType() == CPlayer::TYPE_CAT)
	{ // アイテムが取れる状態かつ、ネコの場合

		if (useful::CircleCollisionXZ(pPlayer->GetPos(), GetPos(), Radius, GetFileData().fRadius) == true)
		{ // 円の範囲内の場合

			// true を返す
			return true;
		}
	}

	// false を返す
	return false;
}

//=====================================
// テレビの電源の処理
//=====================================
void CTv::Action(void)
{
	// プレイヤーのポインタを宣言
	CPlayer* pPlayer;

	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		// プレイヤーを取得する
		pPlayer = CGame::GetPlayer(nCnt);

		if (pPlayer != nullptr)
		{ // プレイヤーが NULL じゃない場合

			if (pPlayer->GetType() == CPlayer::TYPE_CAT &&
				pPlayer->GetItemCount() < 2)
			{ // ネコの場合

				// アイテムの取得処理
				pPlayer->GetItem(CItem::TYPE_DYNAMITE);

				if (m_State != STATE_COOLDOWN)
				{ // クールタイム以外の場合

					// サウンドの再生
					CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_TV_SANDSTORM);
				}

				// アイテム取った後の状態にする
				m_State = STATE_COOLDOWN;
				m_nCoolTime = COOL_TIME;

				// テクスチャの割り当て処理
				m_pVision->BindTexture(CManager::Get()->GetTexture()->Regist(COOLTIME_TEXTURE));
			}
		}
	}
}

//=====================================
// 電源処理
//=====================================
void CTv::PowerAction(void)
{
	switch (m_bPower)
	{
	case true:

		// テレビの電源ついてた時消す
		if (m_pVision != nullptr)
		{	// ポリゴンが存在していた時nullにする
			m_pVision->Uninit();
			m_pVision = nullptr;

		}
		//	サウンドの再生
		CManager::Get()->GetSound()->Stop(CSound::SOUND_LABEL_SE_TV_SANDSTORM);

		// 電源OFFにする
		m_bPower = false;
		SetAction(false);

		break;

	case false:

		// テレビの電源消えていた時点ける
		if (m_pVision == nullptr)
		{	// ポリゴンが存在していないとき生成する

			D3DXVECTOR3 pPos = GetPos();
			m_pVision = CObject3D::Create(CObject::TYPE_NONE, PRIORITY_BLOCK);
			m_pVision->SetPos(D3DXVECTOR3(pPos.x - sinf(GetRot().y) * 18.0f, pPos.y + 160.0f, pPos.z - cosf(GetRot().y) * 18.0f));
			m_pVision->SetRot(GetRot());
			m_pVision->SetSize(VISION_SIZE);

			// 頂点座標の設定処理
			m_pVision->SetVertex();

			if (m_State == STATE_NONE)
			{ // 何でもない画面の時

				// 通常テクスチャの割り当て処理
				m_pVision->BindTexture(CManager::Get()->GetTexture()->Regist(NONE_TEXTURE));
			}
			else if (m_State == STATE_BOMB)
			{ // 爆弾の画面の時

				// 爆弾テクスチャの割り当て処理
				m_pVision->BindTexture(CManager::Get()->GetTexture()->Regist(BOMB_TEXTURE));
			}
			else
			{ // クールタイム中

				// 砂嵐テクスチャの割り当て処理
				m_pVision->BindTexture(CManager::Get()->GetTexture()->Regist(COOLTIME_TEXTURE));

				//	サウンドの再生
				CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_TV_SANDSTORM);
			}
		}

		// 電源ONにする
		m_bPower = true;
		SetAction(false);

		break;
	}
}

//=====================================
// リモコンのヒットサークル処理
//=====================================
bool CTv::HitRemocon(void)
{
	// プレイヤーのポインタを宣言
	CPlayer* pPlayer;

	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		// プレイヤーを取得する
		pPlayer = CGame::GetPlayer(nCnt);

		if (pPlayer != nullptr &&
			pPlayer->GetState() != CPlayer::STATE_DEATH &&
			pPlayer->GetStunState() != CPlayer::STUNSTATE::STUNSTATE_STUN &&
			pPlayer->GetStunState() != CPlayer::STUNSTATE::STUNSTATE_WAIT)
		{ // プレイヤーが NULL じゃない場合

			switch (pPlayer->GetType())
			{
			case CPlayer::TYPE_CAT:

				if (m_bPower == false &&
					useful::CircleCollisionXZ(pPlayer->GetPos(), m_remocon.pRemocon->GetPos(), CAT_RADIUS, m_remocon.pRemocon->GetFileData().fRadius) == true)
				{ // 電源OFFかつ、円の範囲内の場合

					// true を返す
					return true;
				}

				break;

			case CPlayer::TYPE_RAT:

				if (m_bPower == true &&
					useful::CircleCollisionXZ(pPlayer->GetPos(), m_remocon.pRemocon->GetPos(), RAT_RADIUS, m_remocon.pRemocon->GetFileData().fRadius) == true)
				{ // 電源ONかつ、円の範囲内の場合

					// true を返す
					return true;
				}

				break;

			default:

				// 停止
				assert(false);

				break;
			}
		}
	}

	// false を返す
	return false;
}

//=====================================
// テレビ画面切り替え処理
//=====================================
void CTv::VisionChange(void)
{
	if (m_bPower == true)
	{ // 電源ON状態の場合

		if (m_State != STATE_COOLDOWN)
		{ // クールダウン状態以外の場合

			m_nChangeVision++;
			if (m_nChangeVision % CHANGE_TIME == 0 && m_nChangeVision > 0)
			{
				switch (m_State)
				{
				case STATE_NONE: // 何でもない状態の場合
					m_pVision->BindTexture(CManager::Get()->GetTexture()->Regist(BOMB_TEXTURE));
					m_State = STATE_BOMB;
					//	サウンドの再生
					CManager::Get()->GetSound()->Stop(CSound::SOUND_LABEL_SE_TV_SANDSTORM);
					break;

				case STATE_BOMB: // 爆弾の画面の場合
					m_pVision->BindTexture(CManager::Get()->GetTexture()->Regist(NONE_TEXTURE));
					m_State = STATE_NONE;
					//	サウンドの再生
					CManager::Get()->GetSound()->Stop(CSound::SOUND_LABEL_SE_TV_SANDSTORM);
					break;
				case STATE_COOLDOWN: // クールタイム中の場合

					break;
				default:

					// 停止
					assert(false);

					break;
				}
			}
		}
		else
		{
			if (m_nChangeVision != 0)
			{
				m_nChangeVision = 0;
			}
		}
	}
	
}