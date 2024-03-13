//===================================
//
// ゲームフィニッシュヘッダー[game_finish.h]
// Author 堀川萩大
//
//===================================
#ifndef _GAME_FINISH_H_
#define _GAME_FINISH_H_

//***********************************
// インクルードファイル
//***********************************
#include "object.h"

//-----------------------------------
// 前方宣言
//-----------------------------------
class CObject2D;		// 2Dポリゴン
class CGameTime;		// ゲームタイム
class CCountdown;		// カウントダウン

//-----------------------------------
// クラス定義(GAMEFINISH)
//-----------------------------------
class CGameFinish : public CObject
{
public:			// 誰でもアクセスできる

	CGameFinish();			// コンストラクタ
	~CGameFinish();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	// 設定取得処理関数
	void SetData(void);				// 情報の設定処理
	void SetFinish(bool bFinish);	// 終了の設定処理

	// 静的メンバ関数
	static CGameFinish* Create(void);	// 生成処理

private:		// 自分だけアクセスできる

	float m_fSize;				// 拡大率
	CObject2D* m_pFinish;		// ポリゴンの情報
	bool m_bFinish;				// 終了したか
	bool m_bSe;					// SE再生状況
	// 静的メンバ変数
	static CGameTime* m_pGameTime;		// ゲームタイムの情報
	static CCountdown* m_pCountdown;	// カウントダウンの情報
};

#endif