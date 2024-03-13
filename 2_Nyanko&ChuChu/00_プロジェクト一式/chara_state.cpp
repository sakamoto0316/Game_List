//=======================================
//
// キャラクターの状態のメイン処理[chara_state.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "chara_state.h"
#include "texture.h"
#include "useful.h"

#include "game.h"
#include "player.h"

//=======================================
// マクロ定義
//=======================================
#define STUN_SIZE				(D3DXVECTOR3(90.0f, 45.0f, 0.0f))	// 気絶アイコンのサイズ
#define GHOST_SIZE				(D3DXVECTOR3(80.0f, 20.0f, 0.0f))	// 死亡アイコンのサイズ
#define STUNICON_TEXTURE		"data\\TEXTURE\\StunIcon.png"		// 気絶アイコンのテクスチャ
#define GHOSTICON_TEXTURE		"data\\TEXTURE\\GhostIcon.png"		// 死亡アイコンのテクスチャ
#define NONE_PLAYERIDX			(-1)								// プレイヤーのインデックスの初期値

//=========================
// コンストラクタ
//=========================
CCharaState::CCharaState() : CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_UI)
{
	// 全ての値をクリアする
	m_state = STATE_STUN;			// 状態
	m_nPlayerIdx = NONE_PLAYERIDX;	// プレイヤーのインデックス
	m_bDisp = false;				// 描画状況
}

//=========================
// デストラクタ
//=========================
CCharaState::~CCharaState()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CCharaState::Init(void)
{
	if (FAILED(CObject2D::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	m_state = STATE_STUN;			// 状態
	m_nPlayerIdx = NONE_PLAYERIDX;	// プレイヤーのインデックス
	m_bDisp = false;				// 描画状況

	// 成功を返す
	return S_OK;
}

//=========================
// 終了処理
//=========================
void CCharaState::Uninit(void)
{
	// 終了
	CObject2D::Uninit();
}

//=========================
// 更新処理
//=========================
void CCharaState::Update(void)
{
	// 状態処理
	State();
}

//=========================
// 描画処理
//=========================
void CCharaState::Draw(void)
{
	if (m_bDisp == true)
	{ // 描画状況が true の場合

		// 描画処理
		CObject2D::Draw();
	}
}

//=========================
// 情報の設定処理
//=========================
void CCharaState::SetData(const D3DXVECTOR3& pos, const int nID)
{
	// スクロールの設定処理
	SetPos(pos);				// 位置設定
	SetRot(NONE_D3DXVECTOR3);	// 向き設定
	SetSize(STUN_SIZE);			// サイズ設定
	SetLength();				// 長さ設定
	SetAngle();					// 方向設定

	// テクスチャの割り当て処理
	BindTexture(CManager::Get()->GetTexture()->Regist(STUNICON_TEXTURE));

	// 頂点情報の初期化
	SetVertex();

	// 全ての値を設定する
	m_state = STATE_NONE;	// 状態
	m_nPlayerIdx = nID;		// プレイヤーのインデックス
	m_bDisp = false;		// 描画状況
}

//=========================
// 生成処理
//=========================
CCharaState* CCharaState::Create(const D3DXVECTOR3& pos, const int nID)
{
	// ローカルオブジェクトを生成
	CCharaState* pCharaImage = nullptr;	// プレイヤーのインスタンスを生成

	if (pCharaImage == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pCharaImage = new CCharaState;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pCharaImage != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pCharaImage->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pCharaImage->SetData(pos, nID);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// キャラクター画像のポインタを返す
	return pCharaImage;
}

//=========================
// 状態処理
//=========================
void CCharaState::State(void)
{
	// ネズミのポインタを宣言する
	CPlayer* pPlayer = nullptr;

	// ネズミのポインタを取得する
	pPlayer = CGame::GetPlayer(m_nPlayerIdx);

	if (pPlayer != nullptr)
	{ // プレイヤーが NULL じゃない場合

		if (pPlayer->GetStunState() == CPlayer::STUNSTATE_STUN)
		{ // 気絶状態の場合

			if (m_state != STATE_STUN)
			{ // 気絶状態以外の場合

				// 描画状況を true にする
				m_bDisp = true;

				// 気絶状態にする
				m_state = STATE_STUN;

				// テクスチャの割り当て処理
				BindTexture(CManager::Get()->GetTexture()->Regist(STUNICON_TEXTURE));

				// サイズを設定する
				SetSize(STUN_SIZE);

				// 頂点情報の設定処理
				SetVertex();
			}
		}
		else if (pPlayer->GetState() == CPlayer::STATE_DEATH)
		{ // 死亡状態の場合

			if (m_state != STATE_GHOST)
			{ // ゴースト状態以外の場合

				// 描画状況を true にする
				m_bDisp = true;

				// ゴースト状態にする
				m_state = STATE_GHOST;

				// テクスチャの割り当て処理
				BindTexture(CManager::Get()->GetTexture()->Regist(GHOSTICON_TEXTURE));

				// サイズを設定する
				SetSize(GHOST_SIZE);

				// 頂点情報の設定処理
				SetVertex();
			}
		}
		else
		{ // 上記以外

			// 描画状況を false にする
			m_bDisp = false;

			// 無状態にする
			m_state = STATE_NONE;
		}
	}
}