//===================================
//
// ブロックヘッダー[block.h]
// Author 小原立暉
//
//===================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"

//-----------------------------------
// クラス定義(地形用ブロック)
//-----------------------------------
class CBlock : public CModel
{
public:			// 誰でもアクセスできる

	// 状態
	enum STATE
	{
		STATE_NONE = 0,		// 何もしない
		STATE_SWAY,			// 揺れる
		STATE_MAX			// この列挙型の総数
	};

	// 向きの種類
	enum ROTTYPE
	{
		ROTTYPE_FRONT = 0,		// 正面
		ROTTYPE_RIGHT,			// 右
		ROTTYPE_BACK,			// 後ろ
		ROTTYPE_LEFT,			// 左
		ROTTYPE_MAX				// この列挙型の総数
	};

	// 列挙型定義(当たり判定の種類)
	enum COLLISION
	{
		COLLISION_SQUARE = 0,		// 四角
		COLLISION_CIRCLE,			// 円
		COLLISION_MAX				// この列挙型の総数
	};

	// 列挙型定義(種類)
	enum TYPE
	{
		TYPE_CARDBOARD = 0,		// 段ボール
		TYPE_TISSUE,			// ティッシュ箱
		TYPE_PENHOLDER,			// ペン立て
		TYPE_REMOCON,			// リモコン
		TYPE_BEAR,				// テディベア
		TYPE_CLOCK,				// 時計
		TYPE_RUBBISH,			// チリ紙
		TYPE_MILKPACK,			// 牛乳パック
		TYPE_OBAPHONE,			// オバフォン
		TYPE_WII,				// Wii
		TYPE_DS,				// DS
		TYPE_HEADPHONE,			// ヘッドフォン
		TYPE_PEN,				// ペン
		TYPE_ACADAPTER,			// ACアダプター
		TYPE_BUILDINGBLOCK,		// 積み木
		TYPE_GLASSES,			// 眼鏡ケース
		TYPE_PENCIL,			// 鉛筆
		TYPE_PICTUREFRAME,		// 写真立て
		TYPE_SHELF,				// 戸棚
		TYPE_PULLSHELF,			// 引き出し棚
		TYPE_KITCHEN,			// キッチン
		TYPE_REIZOUKO,			// 冷蔵庫
		TYPE_TABLE,				// テーブル
		TYPE_CHAIR,				// 机の椅子
		TYPE_CORKBOARD,			// コルクボード
		TYPE_DESK,				// デスク
		TYPE_DESKBOOK,			// デスク用の本
		TYPE_EXTIMGISHER,		// 消火器
		TYPE_KATEN,				// カーテン
		TYPE_KATENRAIL,			// カーテンのレール
		TYPE_TANSU02,			// たんす
		TYPE_TV_STAND,			// テレビ台
		TYPE_WALL_PLUS50,		// 50*100の壁
		TYPE_WALL_PLUS100,		// 100*100の壁
		TYPE_DOOR001,			// ドア
		TYPE_SMALL_SHELF,		// 小さな棚
		TYPE_BOOKSHELF,			// 横長の本棚
		TYPE_TALBESHELF,		// テーブルの高さの棚
		TYPE_SOFA_SHEET,		// ソファー（座面）
		TYPE_SOFA_BACKTEST,		// ソファー（背もたれ）
		TYPE_CHAIR_SHEET,		// 机の椅子(座面)
		TYPE_CHAIR_BACKREST,	// 机の椅子(背もたれ)
		TYPE_LEVERBODYBLOCK,	// レバー(本体)
		TYPE_WINDOW,			// 窓
		TYPE_WALLCLOCK,			// 壁掛け時計
		TYPE_INTERIOR000,		// 壁のインテリア(棚)
		TYPE_WALLCROSS,			// 横柱
		TYPE_MAX				// この列挙型の総数
	};

	CBlock();			// コンストラクタ
	~CBlock();			// デストラクタ

	// リスト構造関係
	void SetPrev(CBlock* pPrev);		// 前のポインタの設定処理
	void SetNext(CBlock* pNext);		// 後のポインタの設定処理
	CBlock* GetPrev(void) const;		// 前のポインタの設定処理
	CBlock* GetNext(void) const;		// 次のポインタの設定処理

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void UninitAll(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const ROTTYPE rotType, const TYPE type);			// 情報の設定処理

	// セット・ゲット関係
	void SetCollision(const COLLISION collsion);	// 当たり判定の種類の設定処理
	//void SetOnRat(const bool bOnRat, const int nPlayerIdx);		// ネズミの乗っている状況設定
	void SetState(STATE state);						// 状態設定

	COLLISION GetCollision(void) const;				// 当たり判定の種類の取得処理
	ROTTYPE GetRotType(void) const;					// 向きの種類の取得処理
	TYPE GetType(void) const;						// 種類の取得処理
	STATE GetState(void) const;						// 状態の取得処理
	D3DXVECTOR3 GetVtxMax(void) const;				// 最大値の取得処理
	D3DXVECTOR3 GetVtxMin(void) const;				// 最小値の取得処理
	//bool GetOnRat(void) const;						// ネズミの乗っている状況取得

	// 静的メンバ関数
	static CBlock* Create(const D3DXVECTOR3& pos, const ROTTYPE rotType, const TYPE type);	// 生成処理

private:		// 自分だけアクセスできる

	// メンバ関数
	void CollisionSetting(void);		// 向きによる最大値・最小値の設定処理
	void UpdateState(void);				// 状態更新処理
	void Sway(void);					// 揺らす処理

	// メンバ変数
	COLLISION m_collision;	// 当たり判定の種類
	ROTTYPE m_rotType;		// 向きの種類
	TYPE m_type;			// 種類
	STATE m_state;			// 状態
	D3DXVECTOR3 m_vtxMax;	// 最大値
	D3DXVECTOR3 m_vtxMin;	// 最小値
	//bool m_bOnRat;			// ネズミが乗っているか
	//int m_nPlayerIdx;		// プレイヤー番号
	int m_nAngleSwitch;		// 角度の+-切り替え
	int m_nSwayCount;		// 揺らす秒数

	// リスト構造関係
	CBlock* m_pPrev;	// 前へのポインタ
	CBlock* m_pNext;	// 次へのポインタ
};

#endif