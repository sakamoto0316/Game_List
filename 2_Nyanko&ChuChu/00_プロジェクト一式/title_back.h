//===================================
//
// タイトルの背景ヘッダー[title_back.h]
// Author 小原立暉
//
//===================================
#ifndef _TITLE_BACK_H_
#define _TITLE_BACK_H_

//***********************************
// インクルードファイル
//***********************************
#include "object3D.h"

//-----------------------------------
// クラス定義(タイトルの背景)
//-----------------------------------
class CTitleBack :public CObject3D
{
public:

	CTitleBack();		// コンストラクタ
	~CTitleBack();		// デストラクタ

	// メンバ関数
	HRESULT Init(void);	// 初期化処理
	void Uninit(void);	// 終了処理
	void Update(void);	// 更新処理
	void Draw(void);	// 描画処理

	void SetData(void);	// 情報の設定処理

	// 静的メンバ関数
	static CTitleBack* Create(void);	// 生成処理

private:
};

#endif