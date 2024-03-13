//============================================
//
// エントリー画面ヘッダー[entry.h]
// Author：小原立暉
//
//============================================
#ifndef _ENTRY_H_			//このマクロ定義がされていなかったら
#define _ENTRY_H_			//2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "main.h"
#include "scene.h"

//--------------------------------------------
// 前方宣言
//--------------------------------------------
class CEntryUI;			// エントリーUI
class CPlayer;

//--------------------------------------------
// クラス(エントリー画面クラス)
//--------------------------------------------
class CEntry : public CScene
{
public:				// 誰でもアクセスできる

	CEntry();		// コンストラクタ
	~CEntry();		// デストラクタ

	// メンバ関数
	HRESULT Init(void);				// 初期化処理
	void Uninit(void);				// 終了処理
	void Update(void);				// 更新処理
	void Draw(void);				// 描画処理

	// セット・ゲット関数
	static int GetCatIdx(void);		// ネコ担当の取得処理

private:					// 自分だけアクセスできる

	// 静的メンバ変数
	static int m_nCatIdx;					// ネコをやるプレイヤー
	static int m_nCatOldIdx;				// 差分用ID
	static int m_EntryId[MAX_PLAY];			// 全体のID
	static CEntryUI* m_apUI[MAX_PLAY];		// エントリーUIの情報
	static CPlayer*  m_apPlayer[MAX_PLAY];	// モデル情報
	bool m_bEnter;							// エンターを押したかどうか
	int m_nSceneCnt;						// 遷移までのカウント
};

#endif