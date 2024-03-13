//=======================================
//
// プレイヤーのID表示のメイン処理[player_idUI.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "player_idUI.h"
#include "useful.h"

//=======================================
// マクロ定義
//=======================================
#define PLAYER_ID_PATTERN	((float)(1.0f / 4.0f))					// プレイヤーのIDの1面ごとのサイズ
#define PLAYER_ID_SIZE		(D3DXVECTOR3(40.0f, 25.0f, 0.0f))		// プレイヤーのID表示のサイズ
#define PLAYER_ID_TEXTURE	"data\\TEXTURE\\PlayerID.png"			// プレイヤーのID表示のテクスチャ

//=========================
// コンストラクタ
//=========================
CPlayerID::CPlayerID() : CBillboard(CObject::TYPE_NONE, CObject::PRIORITY_PLAYER)
{
	// 全ての値をクリアする
	m_bDisp = true;		// 描画状況
}

//=========================
// デストラクタ
//=========================
CPlayerID::~CPlayerID()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CPlayerID::Init(void)
{
	if (FAILED(CBillboard::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	m_bDisp = true;		// 描画状況

	// 成功を返す
	return S_OK;
}

//=========================
// 終了処理
//=========================
void CPlayerID::Uninit(void)
{
	// 終了
	CBillboard::Uninit();
}

//=========================
// 更新処理
//=========================
void CPlayerID::Update(void)
{
	// 頂点情報の初期化
	SetVertex();
}

//=========================
// 描画処理
//=========================
void CPlayerID::Draw(void)
{
	if (m_bDisp == true)
	{ // 描画状況が true の場合

		// 描画処理
		CBillboard::DrawLightOff();
	}
}

//=========================
// 情報の設定処理
//=========================
void CPlayerID::SetData(const D3DXVECTOR3& pos, const int nID)
{
	// スクロールの設定処理
	SetPos(pos);				// 位置設定
	SetPosOld(pos);				// 前回の位置設定
	SetSize(PLAYER_ID_SIZE);	// サイズ設定

	// 全ての値を設定する
	m_bDisp = true;		// 描画状況

	// 頂点情報の初期化
	SetVertex();

	// テクスチャ座標の設定処理
	SetVtxAnim(PLAYER_ID_PATTERN, nID);

	// テクスチャの読み込み処理
	BindTexture(CManager::Get()->GetTexture()->Regist(PLAYER_ID_TEXTURE));
}

//=========================
// 生成処理
//=========================
CPlayerID* CPlayerID::Create(const D3DXVECTOR3& pos, const int nID)
{
	// ローカルオブジェクトを生成
	CPlayerID* pPlayerID = nullptr;	// プレイヤーのID表示のインスタンスを生成

	if (pPlayerID == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pPlayerID = new CPlayerID;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pPlayerID != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pPlayerID->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pPlayerID->SetData(pos, nID);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// プレイヤーのID表示のポインタを返す
	return pPlayerID;
}

//=========================
// 描画状況の設定処理
//=========================
void CPlayerID::SetEnableDisp(const bool bDisp)
{
	// 描画状況を設定する
	m_bDisp = bDisp;
}

//=========================
// 描画状況の取得処理
//=========================
bool CPlayerID::IsDisp(void) const
{
	// 描画状況を返す
	return m_bDisp;
}