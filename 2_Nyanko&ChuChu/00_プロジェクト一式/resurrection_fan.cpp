//===========================================
//
// 生き返りの円の範囲の処理[resurrection_fan.h]
// Author 佐藤根詩音
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "resurrection_fan.h"
#include "model.h"
#include "texture.h"
#include "player.h"
#include "game.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define RADIUS			(100.0f)	// 半径
#define DEFAULT_COLOR	(D3DXCOLOR(0.2f, 0.5f, 0.5f, 0.2f))		// 初期色
#define REZ_COLOR		(D3DXCOLOR(0.0f, 1.0f, 0.2f, 0.6f))		// 回復の色

//-------------------------------------------
// 静的メンバ変数宣言
//-------------------------------------------

//==============================
// コンストラクタ
//==============================
CRessrectionFan::CRessrectionFan() : CObject3DFan(CObject::TYPE_PLAYER, CObject::PRIORITY_PLAYER)
{
	// 全ての値をクリアする
	m_nRezTime = 0;			// 回復時間
	m_bRez = false;			// 回復してるか

}

//==============================
// デストラクタ
//==============================
CRessrectionFan::~CRessrectionFan()
{

}

//==============================
// 生き返りの円の初期化処理
//==============================
HRESULT CRessrectionFan::Init(void)
{
	if (FAILED(CObject3DFan::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	m_nRezTime = 0;			// 回復時間
	m_bRez = false;			// 回復してるか

	// 値を返す
	return S_OK;
}

//========================================
// 生き返りの円の終了処理
//========================================
void CRessrectionFan::Uninit(void)
{
	// 終了処理
	CObject3DFan::Uninit();
}

//=====================================
// 生き返りの円の更新処理
//=====================================
void CRessrectionFan::Update(void)
{
	// 頂点座標の設定処理
	SetVertex();

	// 頂点の色の設定処理
	SetVtxColor(DEFAULT_COLOR, REZ_COLOR, m_nRezTime);
}

//=====================================
// 生き返りの円の描画処理
//=====================================
void CRessrectionFan::Draw(void)
{
	// 描画処理
	CObject3DFan::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CRessrectionFan::SetData(const D3DXVECTOR3& pos, const D3DXCOLOR& col)
{
	// 設定処理に便利なマクロ定義
	//NONE_D3DXVECTOR3					// 向きを傾けない時とかに使用する
	//NONE_SCALE						// 拡大率を変更しないときとかに使う
	// 情報の設定処理

	//==========================================================================
	// 3Dポリゴン
	//==========================================================================
	SetPos(pos);					// 位置
	SetPosOld(GetPos());			// 前回の位置
	SetRot(NONE_D3DXVECTOR3);		// 向き
	SetSize(NONE_SCALE);			// サイズ
	SetNumAngle(NUM_REZ_ANGLE);		// 角度の総数
	SetRadius(RADIUS);				// 半径
	SetColor(col);					// 色
	BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\cheese.jpg"));		// テクスチャの割り当て処理
}

//=======================================
// 生成処理
//=======================================
CRessrectionFan* CRessrectionFan::Create(const D3DXVECTOR3& pos, const D3DXCOLOR& col)
{
	// ローカルオブジェクトを生成
	CRessrectionFan* pRessrectionFan = nullptr;	// サンプルのインスタンスを生成

	if (pRessrectionFan == nullptr)
	{ // オブジェクトが NULL の場合

		// インスタンスを生成
		pRessrectionFan = new CRessrectionFan;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pRessrectionFan != nullptr)
	{ // オブジェクトが NULL じゃない場合
		
		// 情報の設定処理
		pRessrectionFan->SetData(pos, col);

		// 初期化処理
		if (FAILED(pRessrectionFan->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// サンプルのポインタを返す
	return pRessrectionFan;
}

//=======================================
// 回復時間の設定
//=======================================
void CRessrectionFan::SetResurrectionFan(int nFan)
{
	// 回復時間代入
	m_nRezTime = nFan;
}

//=======================================
// 角度の取得
//=======================================
int CRessrectionFan::GetResurrectionFan(void)
{
	// 回復時間を返す
	return m_nRezTime;
}