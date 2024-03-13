//===========================================
//
// エントリー画面の操作説明のメイン処理[entry_message.cpp]
// Author 佐藤根詩音
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "entry_message.h"
#include "texture.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define POS_SWITCH		(45)		// 位置の上下変更する時間
#define RESIZE_SCALE	(0.0004f)	// リザイズのスケール
#define COLOR_ALPHA		(0.0007f)	// 色の透明度

//-------------------------------------------
// 静的メンバ変数宣言
//-------------------------------------------

//==============================
// コンストラクタ
//==============================
CEntryMessage::CEntryMessage() : CObject2D(CObject::TYPE_ENTRYMESSAGEUI, CObject::PRIORITY_UI)
{
	// 全ての値をクリアする
	m_nScaleSwitchCounter = 0;		// スケールの上下変更カウンター
	m_nScaleSwitch = 1;				// スケールの上下変更
}

//==============================
// デストラクタ
//==============================
CEntryMessage::~CEntryMessage()
{

}

//==============================
// エントリー画面の操作説明の初期化処理
//==============================
HRESULT CEntryMessage::Init(void)
{
	if (FAILED(CObject2D::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	m_nScaleSwitchCounter = 0;		// スケールの上下変更カウンター
	m_nScaleSwitch = 1;				// スケールの上下変更

	// 値を返す
	return S_OK;
}

//========================================
// エントリー画面の操作説明の終了処理
//========================================
void CEntryMessage::Uninit(void)
{
	// 終了処理
	CObject2D::Uninit();
}

//=====================================
// エントリー画面の操作説明の更新処理
//=====================================
void CEntryMessage::Update(void)
{
	D3DXVECTOR3 size = GetSize();	// サイズ取得

	// 前回の位置設定
	SetPosOld(GetPos());

	// カウンター加算
	m_nScaleSwitchCounter++;

	if ((m_nScaleSwitchCounter % POS_SWITCH) == 0)
	{ // 一定時間経過したら

		// スケールの増減変更
		m_nScaleSwitch *= -1;

		// カウンター初期化
		m_nScaleSwitchCounter = 0;
	}

	// サイズ加算
	size = D3DXVECTOR3(size.x + (size.x * m_nScaleSwitch * RESIZE_SCALE), size.y + (size.y * m_nScaleSwitch * RESIZE_SCALE), 0.0f);

	//サイズ設定
	SetSize(size);

	// 頂点座標の設定処理
	SetVertex();
}

//=====================================
// エントリー画面の操作説明の描画処理
//=====================================
void CEntryMessage::Draw(void)
{
	// 描画処理
	CObject2D::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CEntryMessage::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& size)
{
	// 設定処理に便利なマクロ定義
	//NONE_D3DXVECTOR3					// 向きを傾けない時とかに使用する
	//NONE_SCALE						// 拡大率を変更しないときとかに使う

	// 情報の設定処理
	SetPos(pos);				// 位置
	SetPosOld(posOld);			// 前回の位置
	SetRot(NONE_D3DXVECTOR3);	// 向き
	SetSize(size);				// サイズ
	SetLength();				// 長さ
	SetAngle();					// 方向
	BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\entry_message00.png"));		// テクスチャの割り当て処理

	// 頂点座標の設定処理
	SetVertex();
}

//=======================================
// 生成処理
//=======================================
CEntryMessage* CEntryMessage::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& size)
{
	// ローカルオブジェクトを生成
	CEntryMessage* pEntryMessage = nullptr;	// サンプルのインスタンスを生成

	if (pEntryMessage == nullptr)
	{ // オブジェクトが NULL の場合

		// インスタンスを生成
		pEntryMessage = new CEntryMessage;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pEntryMessage != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pEntryMessage->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pEntryMessage->SetData(pos, posOld, size);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// サンプルのポインタを返す
	return pEntryMessage;
}