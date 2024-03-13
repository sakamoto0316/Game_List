//============================================
//
// チュートリアルヘッダー[game.h]
// Author：小原立暉
//
//============================================
#ifndef _TUTORIAL_H_			//このマクロ定義がされていなかったら
#define _TUTORIAL_H_			//2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "main.h"
#include "scene.h"

#define SKIP_MAX (3)

//--------------------------------------------
// 前方宣言
//--------------------------------------------
class CPause;			// ポーズ
class CEdit;			// エディット
class CPlayer;			// プレイヤー
class CGameFinish;		// フィニッシュ
class CAnswer;			// 返答リアクション
class CExplanation;		// 説明
class CObject2D;		// 説明

//--------------------------------------------
// クラス(チュートリアルクラス)
//--------------------------------------------
class CTutorial : public CScene
{
public:						// 誰でもアクセスできる

	// チュートリアルの進行状態
	enum STATE
	{
		STATE_START = 0,	// 開始状態
		STATE_PLAY,			// プレイ状態
		STATE_RAT_WIN,		// ネズミの勝利状態
		STATE_CAT_WIN,		// ネコの勝利状態
		STATE_MAX			// この列挙型の総数
	};

	// チュートリアルの進行状態
	enum TUTORIAL
	{
		TUTORIAL_MOVE = 0,		// 移動
		TUTORIAL_ATTACK_JAMP,	// アタック＆ジャンプ
		TUTORIAL_TABLESWING,	// 机を揺らす
		TUTORIAL_CAT_KILL,		// ネコのキル
		TUTORIAL_RAT_RESCUE,	// ネズミの救助
		TUTORIAL_ACTION,		// アクション
		TUTORIAL_ITEM_MULTI,	// アイテム＆マルチアクション
		TUTORIAL_GIMMICK,		// ギミック説明
		TUTORIAL_LETS_GO,		// 勝利条件と画面遷移
		TUTORIAL_MAX			// この列挙型の総数
	};

	CTutorial();				// コンストラクタ
	~CTutorial();				// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const MODE mode);		// 情報の設定処理

										// 静的メンバ関数(セット・ゲット)

	static void SetState(const STATE state);		// チュートリアルの進行状態の設定処理
	static STATE GetState(void);					// チュートリアルの進行状態の取得処理

	static void SetPlay(const bool bPlay) { m_bPlay = bPlay; }		// プレイ中かどうかの進行状態の設定処理
	static bool GetPlay(void) { return m_bPlay; }					// プレイ中かどうかの進行状態の取得処理

	static void SetMultiAction(const bool bPlay) { m_MultiAction = bPlay; }		// プレイ中かどうかの進行状態の設定処理

	static CPlayer* GetPlayer(const int nID);		// プレイヤーの取得処理

	static TUTORIAL GetTutorial(void) { return m_Tutorial; }

	// NULL化処理
	static void DeletePlayer(int nIdx);	// プレイヤーのNULL化処理

	static void PlayTrue(void);
	static void PlayFalse(void);

										// デバッグ版
#ifdef _DEBUG
	static CEdit* GetEdit(void);		// エディットの取得処理
	static bool IsEdit(void);			// エディット状況の取得処理
#endif

private:					// 自分だけアクセスできる

	// メンバ関数
	static void CatPosReset(void);			// ネコの位置をリセットする
	static void RatPosReset(void);			// ネズミの位置をリセットする
	static void RatPosTable(void);			// ネズミをテーブルの上に配置する
	void Transition(void);		// 遷移処理

	// 静的メンバ変数(最初から必要な物を配置しておく)
	static CPlayer* m_apPlayer[MAX_PLAY];	// プレイヤーの情報
	static STATE m_GameState;				// チュートリアルの進行状態
	static int m_nFinishCount;				// 終了カウント
	static TUTORIAL m_Tutorial;				// チュートリアルの項目
	static bool m_bPlay;					// プレイ中かどうか
	static CAnswer* m_pAnswer;				// 返答リアクションの情報
	static CExplanation* m_pExplanation;	// 説明の情報
	static bool m_MultiAction;				// 連携起動の状態
	static CObject2D* m_apSkip[SKIP_MAX];	// スキップ用のUI
	static float m_fSkipAlpha;				// スキップの不透明度
	static float m_fGauge;					// ゲージの数値
	static float m_fGaugeMax;				// ゲージの最大値

	// デバッグ版
#ifdef _DEBUG
	static CEdit* m_pEdit;				// エディットの情報
	static bool m_bEdit;				// エディット状況
#endif
};

#endif