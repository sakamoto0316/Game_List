//============================================
//
// タイトル画面ヘッダー[title.h]
// Author：小原立暉
//
//============================================
#ifndef _TITLE_H_			//このマクロ定義がされていなかったら
#define _TITLE_H_			//2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "scene.h"

//前方宣言
class C2DUIEdit;

//--------------------------------------------
// クラス(タイトルクラス)
//--------------------------------------------
class CTitle : public CScene
{
public:				// 誰でもアクセスできる

	// 列挙型定義(状態)
	enum STATE
	{
		STATE_TITLE_APPEAR = 0,		// タイトルの出現状態
		STATE_WAIT,					// 進行待機状態
		STATE_TRANS,				// 遷移状態
		STATE_HOLEIN,				// 穴の中に入っていく状態
		STATE_MAX					// この列挙型の総数
	};

	CTitle();		// コンストラクタ
	~CTitle();		// デストラクタ

	// メンバ関数
	HRESULT Init(void);				// 初期化処理
	void Uninit(void);				// 終了処理
	void Update(void);				// 更新処理
	void Draw(void);				// 描画処理

	// 静的メンバ関数
	static void SetState(const STATE state);		// 状態の設定処理
	static STATE GetState(void);					// 状態の取得処理

private:					// 自分だけアクセスできる

	// メンバ変数
	C2DUIEdit *m_pUIEdit;
	int m_nTransCount;		// 遷移カウント
	bool m_bEdit;

	// 静的メンバ変数
	static STATE m_state;			// 状態
};

#endif