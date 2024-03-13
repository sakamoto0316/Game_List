//===================================
//
// エントリー画面の操作説明ヘッダー[entry_message.h]
// Author 佐藤根詩音
//
//===================================
#ifndef _ENTRY_MESSAGE_H_
#define _ENTRY_MESSAGE_H_

//***********************************
// インクルードファイル
//***********************************
#include "object2D.h"

//-----------------------------------
// クラス(エントリー画面の操作説明クラス)
//-----------------------------------
class CEntryMessage : public CObject2D
{
public:			// 誰でもアクセスできる

	CEntryMessage();			// コンストラクタ
	~CEntryMessage();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& size);		// 情報の設定処理

	// 静的メンバ関数
	static CEntryMessage* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& size);		// 生成処理

private:		// 自分だけアクセスできる

	int m_nScaleSwitchCounter;		// スケールの増減変更カウンター
	int m_nScaleSwitch;				// スケールの増減変更

};

#endif