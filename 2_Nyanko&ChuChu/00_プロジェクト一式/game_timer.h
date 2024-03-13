//============================================
//
// ゲームの時間ヘッダー[game_time.h]
// Author：小原立暉
//
//============================================
#ifndef _GAME_TIME_H_					// このマクロ定義がされていなかったら
#define _GAME_TIME_H_					// 2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "object.h"

//--------------------------------------------
// マクロ定義
//--------------------------------------------
#define GAME_TIME_DIGIT		(3)		// ゲームタイマーの桁数

//--------------------------------------------
// 前方宣言
//--------------------------------------------
class CNumber;			// 数字
class CObject2D;		// 2Dポリゴン

//--------------------------------------------
// クラス定義(ゲームタイム)
//--------------------------------------------
class CGameTime : public CObject
{
public:				// 誰でもアクセスできる

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(void);		// 情報の設定処理
	int GetSeconds(void);	// 残り秒数の取得処理

	// 静的メンバ変数
	static CGameTime* Get(void);			// 取得処理
	static CGameTime* Create(void);			// 生成処理

private:			// 自分だけアクセスできる

	CGameTime();			// コンストラクタ
	~CGameTime();			// デストラクタ

	// メンバ関数
	void Calculate(void);		// 計算処理

	// メンバ変数
	CNumber* m_apNumber[GAME_TIME_DIGIT];	// 番号の情報
	CObject2D* m_pColon;					// コロン
	CObject2D* m_pBG;						// 背景
	int m_nSeconds;							// 秒数
	int m_nFrame;							// フレーム数

	// 静的メンバ変数
	static CGameTime* m_pGameTimer;		// ゲームタイマーの情報
};

#endif