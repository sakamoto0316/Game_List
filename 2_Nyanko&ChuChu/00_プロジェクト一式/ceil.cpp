//=======================================
//
// 天井処理[ceil.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "ceil.h"
#include "object3D.h"
#include "texture.h"
#include "useful.h"

//---------------------------------------
// 無名名前空間
//---------------------------------------
namespace
{
	const D3DXVECTOR3 CEIL_SHIFT[MAX_CEIL] =		// 天井のずらす幅
	{
		D3DXVECTOR3(0.0f, 0.0f, 1000.0f),
		D3DXVECTOR3(0.0f, 0.0f, -1000.0f),
	};
	const D3DXVECTOR3 CEIL_ROT[MAX_CEIL] =			// 天井の向き
	{
		D3DXVECTOR3(-D3DX_PI * 0.8f, 0.0f, 0.0f),
		D3DXVECTOR3(D3DX_PI * 0.8f, 0.0f, 0.0f),
	};
	const D3DXVECTOR3 CEIL_SIZE = D3DXVECTOR3(1600.0f, 0.0f, 2000.0f);	// 天井のサイズ
	const char* CEIL_TEXTURE = "data\\TEXTURE\\ground001.jpg";			// 天井テクスチャ
}

//=========================
// コンストラクタ
//=========================
CCeil::CCeil() : CObject(CObject::TYPE_MAP, CObject::PRIORITY_BG)
{
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < MAX_CEIL; nCnt++)
	{
		m_apCeil[nCnt] = nullptr;		// 天井のポリゴン
	}
}

//=========================
// デストラクタ
//=========================
CCeil::~CCeil()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CCeil::Init(void)
{
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < MAX_CEIL; nCnt++)
	{
		m_apCeil[nCnt] = nullptr;		// 天井のポリゴン
	}

	// 成功を返す
	return S_OK;
}

//=========================
// 終了処理
//=========================
void CCeil::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_CEIL; nCnt++)
	{
		if (m_apCeil[nCnt] != nullptr)
		{ // 天井が NULL じゃない場合

			// 天井の終了処理
			m_apCeil[nCnt]->Uninit();
			m_apCeil[nCnt] = nullptr;
		}
	}

	// 本体の終了処理
	Release();
}

//=========================
// 更新処理
//=========================
void CCeil::Update(void)
{
	for (int nCnt = 0; nCnt < MAX_CEIL; nCnt++)
	{
		if (m_apCeil[nCnt] != nullptr)
		{ // 天井が NULL じゃない場合

			// 頂点座標の設定処理
			m_apCeil[nCnt]->SetVertex();
		}
	}
}

//=========================
// 描画処理
//=========================
void CCeil::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_CEIL; nCnt++)
	{
		if (m_apCeil[nCnt] != nullptr)
		{ // 天井が NULL じゃない場合

			// 描画処理
			m_apCeil[nCnt]->DrawLightOff();
		}
	}
}

//=========================
// 情報の設定処理
//=========================
void CCeil::SetData(const D3DXVECTOR3& pos)
{
	for (int nCnt = 0; nCnt < MAX_CEIL; nCnt++)
	{
		if (m_apCeil[nCnt] == nullptr)
		{ // 天井が NULL の場合

			// 天井を生成する
			m_apCeil[nCnt] = CObject3D::Create(TYPE_NONE, PRIORITY_BG);

			// スクロールの設定処理
			m_apCeil[nCnt]->SetPos(pos + CEIL_SHIFT[nCnt]);			// 位置設定
			m_apCeil[nCnt]->SetPosOld(pos + CEIL_SHIFT[nCnt]);			// 前回の位置設定
			m_apCeil[nCnt]->SetRot(CEIL_ROT[nCnt]);		// 向き設定
			m_apCeil[nCnt]->SetSize(CEIL_SIZE);		// サイズ設定

			// テクスチャの割り当て処理
			m_apCeil[nCnt]->BindTexture(CManager::Get()->GetTexture()->Regist(CEIL_TEXTURE));

			// 頂点座標の設定処理
			m_apCeil[nCnt]->SetVertex();
		}
	}
}

//=========================
// 生成処理
//=========================
CCeil* CCeil::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CCeil* pCeil = nullptr;	// プレイヤーのインスタンスを生成

	if (pCeil == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pCeil = new CCeil;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pCeil != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pCeil->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pCeil->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 天井のポインタを返す
	return pCeil;
}