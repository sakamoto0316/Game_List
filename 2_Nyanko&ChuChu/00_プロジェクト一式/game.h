//============================================
//
// ゲームヘッダー[game.h]
// Author：小原立暉
//
//============================================
#ifndef _GAME_H_			//このマクロ定義がされていなかったら
#define _GAME_H_			//2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "main.h"
#include "scene.h"

//--------------------------------------------
// マクロ定義
//--------------------------------------------
#define MAP_TYPE		(3)		// マップの種類

//--------------------------------------------
// 前方宣言
//--------------------------------------------
class CPause;			// ポーズ
class CEdit;			// エディット
class CPlayer;			// プレイヤー
class CGameFinish;		// フィニッシュ

//--------------------------------------------
// クラス(ゲームクラス)
//--------------------------------------------
class CGame : public CScene
{
public:						// 誰でもアクセスできる

	// ゲームの進行状態
	enum STATE
	{
		STATE_START = 0,	// 開始状態
		STATE_PLAY,			// プレイ状態
		STATE_RAT_WIN,		// ネズミの勝利状態
		STATE_CAT_WIN,		// ネコの勝利状態
		STATE_MAX			// この列挙型の総数
	};

	CGame();				// コンストラクタ
	~CGame();				// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const MODE mode);		// 情報の設定処理

	// 静的メンバ関数(セット・ゲット)
	static CPause* GetPause(void);					// ポーズの取得処理

	static void SetState(const STATE state);		// ゲームの進行状態の設定処理
	static STATE GetState(void);					// ゲームの進行状態の取得処理

	static CPlayer* GetPlayer(const int nID);		// プレイヤーの取得処理

	static void SetCountDown(const bool Set) { m_bCountDown = Set; }		// ゲームの進行状態の設定処理
	static bool GetCountDown(void) { return m_bCountDown; }					// ゲームの進行状態の取得処理

	static void SetItemSpawn(const bool bItemSpawn) { m_bItemSpawn = bItemSpawn; }	// アイテム出現状態の設定
	static bool GetItemSpawn(void) {return m_bItemSpawn; }					// アイテム出現状態の取得

	static void SetMapNumber(const int Number) { m_nMapNumber = Number; }	// マップ番号の設定
	static int GetMapNumber(void) { return m_nMapNumber; }					// マップ番号の取得

	// NULL化処理
	static void DeletePause(void);		// ポーズのNULL化処理
	static void DeletePlayer(int nIdx);	// プレイヤーのNULL化処理

// デバッグ版
#ifdef _DEBUG
	static CEdit* GetEdit(void);		// エディットの取得処理
	static bool IsEdit(void);			// エディット状況の取得処理
	static bool GetEditbool(void) { return m_bEdit; }			// エディット状況の取得処理
#endif

private:					// 自分だけアクセスできる

	// メンバ関数
	void Pause(void);			// ポーズ処理
	void Transition(void);		// 遷移処理
	void ItemSpawn(void);		// アイテム出現処理

	// 静的メンバ変数(最初から必要な物を配置しておく)
	static CPause* m_pPause;				// ポーズの情報
	static CPlayer* m_apPlayer[MAX_PLAY];	// プレイヤーの情報
	static CGameFinish* m_pFinish;			// フィニッシュの情報
	static STATE m_GameState;				// ゲームの進行状態
	static int m_nFinishCount;				// 終了カウント
	static int m_nItemSpawnCount;			// アイテム出現カウンター
	static int m_nNumItem;					// アイテムの数
	static bool m_bCountDown;				// カウントダウンが使用されているかどうか
	static bool m_bItemSpawn;				// アイテムが出現しているかどうか
	static int m_nMapNumber;				// マップ番号

// デバッグ版
#ifdef _DEBUG
	static CEdit* m_pEdit;				// エディットの情報
	static bool m_bEdit;				// エディット状況
#endif
};

#endif