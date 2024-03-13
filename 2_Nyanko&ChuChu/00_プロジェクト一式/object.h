//============================================
//
// オブジェクトヘッダー[object.h]
// Author：小原立暉
//
//============================================
#ifndef _OBJECT_H_		//このマクロ定義がされていなかったら
#define _OBJECT_H_		//2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "main.h"

//--------------------------------------------
// クラス(オブジェクトクラス)
//--------------------------------------------
class CObject
{
public:			// 誰でもアクセスできる

	// 種類
	enum TYPE
	{
		TYPE_NONE = 0,			// 無し
		TYPE_SCENE,				// シーン
		TYPE_TITLELOGO,			// タイトル
		TYPE_PRESSENTER,		// プレスエンター
		TYPE_EDITUI,			// エディットUI
		TYPE_2DUI,				// 2DUI
		TYPE_TIME,				// タイム
		TYPE_STUN,				// 気絶
		TYPE_SKYBOX,			// スカイボックス
		TYPE_SHADOW,			// 影
		TYPE_SCORE,				// スコア
		TYPE_RIPPLE,			// 波紋
		TYPE_RANKINGWORD,		// ランキングの文字
		TYPE_RANKINGTABLE,		// 取ったスコア
		TYPE_RANKINGPRECE,		// 順位
		TYPE_PAUSE,				// ポーズ
		TYPE_ORBIT,				// 軌跡
		TYPE_FIELD,				// 地面
		TYPE_3DPOLYGON,			// 3Dポリゴン
		TYPE_NEWRECORD,			// 新記録
		TYPE_MESH,				// メッシュ
		TYPE_LOGOMARK,			// ロゴマーク
		TYPE_LOCUS,				// 残像
		TYPE_FRACTION,			// 破片
		TYPE_EFFECT,			// エフェクト
		TYPE_DESTRUCTION,		// 撃波
		TYPE_COLLPOLY,			// 当たり判定ポリゴン
		TYPE_CHARA,				// キャラクター
		TYPE_PLAYER,			// プレイヤー
		TYPE_OBSTACLE,			// 障害物
		TYPE_EDIT,				// エディット
		TYPE_WEAPONSELECTUI,	// 武器選択画面UI
		TYPE_WEAPONCAGE,		// 武器小屋
		TYPE_WEAPONBALLOON,		// 武器のふきだし
		TYPE_BLOCK,				// ブロック
		TYPE_MAP,				// マップ
		TYPE_SLASH,				// 斬撃演出
		TYPE_PLAYERID,			// プレイヤーのID
		TYPE_COUNTDOWN,			// カウントダウン
		TYPE_TITLEWALL,			// タイトルの壁
		TYPE_ENTRYUI,			// エントリーUI
		TYPE_ENTRYRANDOM,		// エントリーのランダム指示
		TYPE_3DTEXT,			// 3Dテキスト
		TYPE_DANGERMARK,		// 危険マーク
		TYPE_ITEM,				// アイテム
		TYPE_CHARAINFO,			// キャラクターの情報UI
		TYPE_WATER,				// 水
		TYPE_FINISHUI,			// 終了カウントダウンのUI
		TYPE_CONFETTI,			// 紙吹雪
		TYPE_RECOVERINGUI,		// 回復中のUI
		TYPE_ITEMUI,			// アイテムUI
		TYPE_DEATHARROW,		// 死亡矢印
		TYPE_ENTRYMESSAGEUI,	// エントリーの説明UI
		TYPE_ENTRYBG,			// エントリー画面の背景
		TYPE_SCREENFRAME,		// 画面の枠
		TYPE_MAX				// この列挙型の総数
	};

	// 優先順位
	enum PRIORITY
	{
		PRIORITY_BG = 0,			// 背景関係
		PRIORITY_BLOCK,				// ブロック・障害物系
		PRIORITY_EFFECT,			// エフェクト系
		PRIORITY_SHADOW,			// 影関係
		PRIORITY_ENTITY,			// 敵・アイテム関係
		PRIORITY_PLAYER,			// プレイヤー関係
		PRIORITY_UI,				// UI関係
		PRIORITY_PAUSE,				// ポーズ(絶対前に出す画面)
		PRIORITY_MAX				// この列挙型の総数
	};

	CObject();													// コンストラクタ
	CObject(TYPE type, PRIORITY priority = PRIORITY_ENTITY);	// オーバーロードコンストラクタ
	virtual ~CObject();											// デストラクタ

	// メンバ関数
	virtual HRESULT Init(void) = 0;	// 初期化処理
	virtual void Uninit(void) = 0;	// 終了処理
	virtual void Update(void) = 0;	// 更新処理
	virtual void Draw(void) = 0;	// 描画処理

	// セット・ゲット関係
	static CObject* GetTop(PRIORITY priority);		// オブジェクトの取得処理

	CObject* GetNext(void);				// 次のポインタの取得処理

	void SetType(const TYPE type);		// 種類の設定処理
	TYPE GetType(void) const;			// 種類の取得処理

	static int GetDrawIdx(void) { return m_DrawIdx; }

	// 静的メンバ関数
	static void ReleaseAll(void);		// 全ての破棄処理
	static void UpdateAll(void);		// 全ての更新処理
	static void DrawAll(void);			// 全ての描画処理

	static void AnyAllClear(const TYPE type);		// 汎用的な全消去処理
	static void AnyAllClear(const PRIORITY priority, const TYPE type);		// 汎用的な全消去処理
	static void DeathDecision(const int nCnt);		// 死亡判別処理

	static void UpdateNormal(void);		// 通常更新処理
	static void UpdateCountdown(void);	// カウントダウン中の更新処理
	static void UpdateGame(void);		// ゲームの更新処理

	static void DrawNormal(void);		// 通常描画処理
	static void DrawGame(void);			// ゲームの描画処理

protected:		// 自分と派生クラスだけがアクセスできる

	// メンバ関数
	void Release(void);					// 破棄処理

private:		// 自分だけアクセスできる

	// メンバ関数
	void Death(void);					// 死亡処理

	// メンバ変数
	CObject* m_pPrev;					// 前のオブジェクトへのポインタ
	CObject* m_pNext;					// 次のオブジェクトへのポインタ
	TYPE m_type;						// 種類
	PRIORITY m_priority;				// オブジェクトの優先順位
	bool m_bDeath;						// 死亡フラグ
	static int m_DrawIdx;				// 描画番号
	
	// 静的メンバ変数
	static CObject* m_apTop[PRIORITY_MAX];				// 先頭のオブジェクトへのポインタ
	static CObject* m_apCur[PRIORITY_MAX];				// 最後尾オブジェクトへのポインタ
	static int m_nNumAll;								// オブジェクトの総数
};

#endif