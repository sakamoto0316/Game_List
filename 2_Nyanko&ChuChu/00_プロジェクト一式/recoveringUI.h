//===================================
//
// 回復中UIヘッダー[recoveringUI.h]
// Author 佐藤根詩音
//
//===================================
#ifndef _RECOVERINGUI_H_
#define _RECOVERINGUI_H_

//***********************************
// インクルードファイル
//***********************************
#include "objectbillboard.h"

//-----------------------------------
// クラス定義(サンプル)
//-----------------------------------
class CRecoveringUI : public CBillboard
{
public:			// 誰でもアクセスできる

	// UIの透明度状態
	enum ALPHA
	{
		ALPHA_OPACITY = 0,		// 不透明
		ALPHA_TRANSPARENT,		// 透明
		ALPHA_MAX
	};

	CRecoveringUI();			// コンストラクタ
	~CRecoveringUI();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld);		// 情報の設定処理
	
	void SetDisplayUI(bool bRez);	// UIの表示状態の設定
	bool GetDisplayUI(void);		// UIの表示状態の取得

	// 静的メンバ関数
	static CRecoveringUI* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld);		// 生成処理

private:		// 自分だけアクセスできる
	bool m_bDisp;			// 表示するか
	float m_fAlpha;			// 透明度
	ALPHA m_alpha;			// 透明度の状態

};

#endif