//============================================
//
// プレスエンター処理[title_press.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "title_press.h"
#include "object2D.h"
#include "texture.h"
#include "useful.h"
#include "sound.h"

#include "title.h"

//--------------------------------------------
// マクロ定義
//--------------------------------------------
#define PRESS_TEXTURE		"data\\TEXTURE\\PRESS.png"				// プレスのテクスチャ
#define BUTTON_TEXTURE		"data\\TEXTURE\\ENTER.png"				// ボタンのテクスチャ
#define PRESS_SIZE			(D3DXVECTOR3(200.0f, 50.0f, 0.0f))		// 「PRESS」のサイズ
#define BUTTON_SIZE			(D3DXVECTOR3(200.0f, 50.0f, 0.0f))		// 「ENTER」のサイズ
#define INIT_PRESS_POS		(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - PRESS_SIZE.x, 600.0f, 0.0f))		// 「PRESS」の初期位置
#define INIT_BUTTON_POS		(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + BUTTON_SIZE.x, 600.0f, 0.0f))	// 「ENTER」の初期位置
#define DEEP_DEST_ALPHA		(1.0f)		// 濃色の目的の透明度
#define LIGHT_DEST_ALPHA	(0.3f)		// 薄色の目的の透明度
#define ADD_ALPHA			(0.02f)		// 追加の透明度
#define TRANS_ADD_ALPHA		(0.2f)		// 遷移状態の追加の透明度
#define SMASH_COUNT			(26)		// 吹き飛ばすカウント数
#define SMASH_MOVE			(D3DXVECTOR3(-35.0f, 0.0f, 0.0f))		// 吹き飛ばす移動量

//============================
// コンストラクタ
//============================
CTitlePress::CTitlePress() : CObject(CObject::TYPE_PRESSENTER, PRIORITY_UI)
{
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_aPress[nCnt].move = NONE_D3DXVECTOR3;		// 移動量
		m_aPress[nCnt].fRotMove = 0.0f;				// 向きの移動量
		m_aPress[nCnt].pPress = nullptr;			// プレスの情報
		m_aPress[nCnt].nStateCount = 0;				// 状態カウント
		m_aPress[nCnt].fAlpha = 0.0f;				// 透明度
		m_aPress[nCnt].fAlphaDest = 0.0f;			// 目的の透明度
	}

	m_bSe = false;									// SEの再生状況
}

//============================
// デストラクタ
//============================
CTitlePress::~CTitlePress()
{

}

//============================
// 初期化処理
//============================
HRESULT CTitlePress::Init(void)
{
	// 全ての値を初期化する
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_aPress[nCnt].pPress == nullptr)
		{ // プレスの情報が NULL の場合

			// プレスを生成する
			m_aPress[nCnt].pPress = CObject2D::Create(CObject2D::TYPE_NONE, CObject::TYPE_NONE, PRIORITY_UI);

			if (m_aPress[nCnt].pPress != nullptr)
			{ // 情報が入っている場合

				if (FAILED(m_aPress[nCnt].pPress->Init()))
				{ // 初期化に失敗した場合

					// 停止
					assert(false);

					// 失敗を返す
					return E_FAIL;
				}
			}
		}
		else
		{ // 上記以外

			// 停止
			assert(false);

			// 失敗を返す
			return E_FAIL;
		}

		m_aPress[nCnt].move = NONE_D3DXVECTOR3;		// 移動量
		m_aPress[nCnt].fRotMove = 0.0f;				// 向きの移動量
		m_aPress[nCnt].nStateCount = 0;				// 状態カウント
		m_aPress[nCnt].fAlpha = 0.0f;				// 透明度
		m_aPress[nCnt].fAlphaDest = 0.0f;			// 目的の透明度
	}

	m_bSe = false;									// SEの再生状況

	// 成功を返す
	return S_OK;
}

//============================
// 終了処理
//============================
void CTitlePress::Uninit(void)
{
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_aPress[nCnt].pPress != nullptr)
		{ // タイトルのポリゴンが NULL じゃない場合

			// ポリゴンの終了処理
			m_aPress[nCnt].pPress->Uninit();
			m_aPress[nCnt].pPress = nullptr;
		}
	}

	// 本体の終了処理
	Release();
}

//============================
// 更新処理
//============================
void CTitlePress::Update(void)
{
	switch (CTitle::GetState())
	{
	case CTitle::STATE_TITLE_APPEAR:	// 出現状態

		break;

	case CTitle::STATE_WAIT:			// 待機状態

		// 透明度処理
		Alpha(ADD_ALPHA);

		break;

	case CTitle::STATE_TRANS:			// 遷移状態

		for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
		{
			// 状態カウントを加算する
			m_aPress[nCnt].nStateCount++;

			if (m_aPress[nCnt].nStateCount % SMASH_COUNT == 0)
			{ // 状態カウントが一定数になった場合

				// 移動量を設定する
				m_aPress[nCnt].move = SMASH_MOVE;

				// 向きの移動量を設定する
				m_aPress[nCnt].fRotMove = (float)((rand() % 11 - 5) * 0.01f);

				if (m_bSe == false)
				{ // SE再生してない

					// ホールイン再生
					CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_TITLECOLLIDE);
					m_bSe = true;
				}
			}
		}

		// 透明度処理
		Alpha(TRANS_ADD_ALPHA);

		break;

	case CTitle::STATE_HOLEIN:			// 穴の中に入っていく処理

		break;

	default:				// 上記以外

		// 停止
		assert(false);

		break;
	}

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		// 吹き飛ばし処理
		Smash(nCnt);

		// 頂点座標の設定処理
		m_aPress[nCnt].pPress->SetVertexRot();

		// 頂点カラーの設定処理
		m_aPress[nCnt].pPress->SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_aPress[nCnt].fAlpha));
	}
}

//============================
// 描画処理
//============================
void CTitlePress::Draw(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_aPress[nCnt].pPress != nullptr)
		{ // タイトルが NULL じゃない場合

			// 描画処理
			m_aPress[nCnt].pPress->Draw();
		}
	}
}

//============================
// 情報の設定処理
//============================
void CTitlePress::SetData(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_aPress[nCnt].pPress != nullptr)
		{ // タイトルが NULL じゃない場合

			// 情報を設定する
			switch (nCnt)
			{
			case CTitlePress::TYPE_PRESS:

				m_aPress[nCnt].pPress->SetPos(INIT_PRESS_POS);		// 位置
				m_aPress[nCnt].pPress->SetSize(PRESS_SIZE);			// サイズ

				// テクスチャの割り当て処理
				m_aPress[nCnt].pPress->BindTexture(CManager::Get()->GetTexture()->Regist(PRESS_TEXTURE));

				break;

			case CTitlePress::TYPE_BUTTON:

				m_aPress[nCnt].pPress->SetPos(INIT_BUTTON_POS);		// 位置
				m_aPress[nCnt].pPress->SetSize(BUTTON_SIZE);		// サイズ

				// テクスチャの割り当て処理
				m_aPress[nCnt].pPress->BindTexture(CManager::Get()->GetTexture()->Regist(BUTTON_TEXTURE));

				break;

			default:

				// 停止
				assert(false);

				break;
			}

			m_aPress[nCnt].pPress->SetRot(NONE_D3DXVECTOR3);	// 向き
			m_aPress[nCnt].pPress->SetAngle();					// 方向
			m_aPress[nCnt].pPress->SetLength();					// 長さ

			// 頂点座標の設定処理
			m_aPress[nCnt].pPress->SetVertex();

			// 頂点カラーの設定処理
			m_aPress[nCnt].pPress->SetVtxColor(NONE_D3DXCOLOR);
		}
		else
		{ // 上記以外

			// 停止
			assert(false);
		}

		m_aPress[nCnt].move = NONE_D3DXVECTOR3;			// 移動量
		m_aPress[nCnt].fRotMove = 0.0f;					// 向きの移動量
		m_aPress[nCnt].nStateCount = 0;					// 状態カウント
		m_aPress[nCnt].fAlpha = 1.0f;					// 透明度
		m_aPress[nCnt].fAlphaDest = LIGHT_DEST_ALPHA;	// 目的の透明度
	}
}

//============================
//生成処理
//============================
CTitlePress* CTitlePress::Create(void)
{
	// プレスエンターのポインタを生成
	CTitlePress* pPress = nullptr;

	if (pPress == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pPress = new CTitlePress;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pPress != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pPress->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pPress->SetData();
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// プレスエンターのポインタを返す
	return pPress;
}

//============================
// 透明度の処理
//============================
void CTitlePress::Alpha(const float fAdd)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (useful::FrameCorrect(m_aPress[nCnt].fAlphaDest, &m_aPress[nCnt].fAlpha, fAdd) == true)
		{ // 目的の透明度に近づいた場合

			// 目的の透明度を設定する
			m_aPress[nCnt].fAlphaDest = (m_aPress[nCnt].fAlphaDest >= DEEP_DEST_ALPHA) ? LIGHT_DEST_ALPHA : DEEP_DEST_ALPHA;
		}
	}
}

//============================
// 吹き飛ばし処理
//============================
void CTitlePress::Smash(const int nType)
{
	// 位置と向きを取得する
	D3DXVECTOR3 pos = m_aPress[nType].pPress->GetPos();
	D3DXVECTOR3 rot = m_aPress[nType].pPress->GetRot();

	// 位置を移動させる
	pos += m_aPress[nType].move;

	// 向きを移動させる
	rot.z += m_aPress[nType].fRotMove;

	// 位置と向きを適用する
	m_aPress[nType].pPress->SetPos(pos);
	m_aPress[nType].pPress->SetRot(rot);
}