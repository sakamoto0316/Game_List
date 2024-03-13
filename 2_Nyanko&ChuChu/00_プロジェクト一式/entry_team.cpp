//=======================================
//
// エントリーチーム処理[entry_team.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "entry_team.h"
#include "texture.h"

//=======================================
// マクロ定義
//=======================================
#define TEAM_SIZE		(D3DXVECTOR3(120.0f, 60.0f, 0.0f))		// チームのサイズ
#define TEAM_TEXTURE	"data\\TEXTURE\\MatchChara.png"			// チームのテクスチャ
#define TEAM_PATTERN	(0.5f)									// チームのパターン数

//=========================
// コンストラクタ
//=========================
CEntryTeam::CEntryTeam() : CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_UI)
{
	// 全ての値をクリアする
	m_type = CPlayer::TYPE_CAT;		// チームの種類

	 m_fMove=0.1f;
	 m_nTimeCnt = 0;
}

//=========================
// デストラクタ
//=========================
CEntryTeam::~CEntryTeam()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CEntryTeam::Init(void)
{
	if (FAILED(CObject2D::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	m_type = CPlayer::TYPE_CAT;		// チームの種類

	// 成功を返す
	return S_OK;
}

//=========================
// 終了処理
//=========================
void CEntryTeam::Uninit(void)
{
	// 終了
	CObject2D::Uninit();
}

//=========================
// 更新処理
//=========================
void CEntryTeam::Update(void)
{
	//UIの拡大・移動
	m_nTimeCnt++;
	if (m_nTimeCnt >= 60)
	{
		m_fMove *= -1.0f;
		m_nTimeCnt = 0;
	}

	CObject2D::SetPos(CObject2D::GetPos()+D3DXVECTOR3(0,m_fMove,0));
	CObject2D::SetSize(CObject2D::GetSize() + D3DXVECTOR3(m_fMove*-0.5f, m_fMove*-0.5f, 0));

	// 頂点情報の初期化
	SetVertex();

	// テクスチャ座標の設定処理
	SetVtxTextureAnim(TEAM_PATTERN, m_type);
}

//=========================
// 描画処理
//=========================
void CEntryTeam::Draw(void)
{
	// 描画処理
	CObject2D::Draw();
}

//=========================
// 情報の設定処理
//=========================
void CEntryTeam::SetData(const D3DXVECTOR3& pos, const CPlayer::TYPE type)
{
	// スクロールの設定処理
	
	SetPos(pos);				// 位置設定
	SetRot(NONE_D3DXVECTOR3);	// 向き設定
	SetSize(TEAM_SIZE);			// サイズ設定
	SetLength();				// 長さ設定
	SetAngle();					// 方向設定

	// 全ての値を設定する
	m_type = type;				// チームの種類

	// テクスチャの読み込み処理
	BindTexture(CManager::Get()->GetTexture()->Regist(TEAM_TEXTURE));

	// 頂点情報の初期化
	SetVertex();

	// テクスチャ座標の設定処理
	SetVtxTextureAnim(TEAM_PATTERN, m_type);
}

//=========================
// 生成処理
//=========================
CEntryTeam* CEntryTeam::Create(const D3DXVECTOR3& pos, const CPlayer::TYPE type)
{
	// ローカルオブジェクトを生成
	CEntryTeam* pEntryTeam = nullptr;	// プレイヤーのインスタンスを生成

	if (pEntryTeam == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pEntryTeam = new CEntryTeam;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pEntryTeam != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pEntryTeam->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pEntryTeam->SetData(pos, type);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// エントリーチームのポインタを返す
	return pEntryTeam;
}

//=========================
// 種類の設定処理
//=========================
void CEntryTeam::SetType(const CPlayer::TYPE type)
{
	// 種類を設定する
	m_type = type;
}