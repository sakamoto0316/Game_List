//===================================
//
// プレイヤーのID表示ヘッダー[player_idUI.h]
// Author 小原立暉
//
//===================================
#ifndef _PLAYER_IDUI_H_
#define _PLAYER_IDUI_H_

//***********************************
// インクルードファイル
//***********************************
#include "objectbillboard.h"

//-----------------------------------
// クラス定義(CPlayerID)
//-----------------------------------
class CPlayerID : public CBillboard
{
public:

	CPlayerID();			// コンストラクタ
	~CPlayerID();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const int nID);				// 情報の設定処理

	// セット・ゲット関係
	void SetEnableDisp(const bool bDisp);		// 描画状況の設定処理
	bool IsDisp(void) const;					// 描画状況の取得処理

	// 静的メンバ関数
	static CPlayerID* Create(const D3DXVECTOR3& pos, const int nID);	// 生成処理

private:

	// メンバ変数
	bool m_bDisp;		// 描画状況
};

#endif