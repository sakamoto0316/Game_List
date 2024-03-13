//============================================================
//
// Xファイルヘッダー [xfile.h]
// Author：小原立暉
//
//============================================================
#ifndef _XFILE_H_	// このマクロ定義がされていない場合
#define _XFILE_H_	// 二重インクルード防止のマクロを定義する

//------------------------------------------------------------
// マクロ定義
//------------------------------------------------------------
#define INIT_VTX_MIN	(D3DXVECTOR3( 9999.0f,  9999.0f,  9999.0f))		// モデルの最小の頂点座標の初期値
#define INIT_VTX_MAX	(D3DXVECTOR3(-9999.0f, -9999.0f, -9999.0f))		// モデルの最大の頂点座標の初期値
#define INIT_SIZE		(D3DXVECTOR3(0.0f, 0.0f, 0.0f))					// モデルサイズの初期値
#define INIT_RAT		(CXFile::TYPE_RAT_BODY)							// ネズミモデルの開始位置
#define INIT_CAT		(CXFile::TYPE_CAT_BODY)							// 猫モデルの開始位置
#define INIT_BLOCK		(CXFile::TYPE_CARDBOARD)						// ブロックモデルの開始位置
#define INIT_OBSTACLE	(CXFile::TYPE_HONEYBOTTLE)						// 障害物モデルの開始位置
#define INIT_ENTRANCE	(CXFile::TYPE_ENTRANCE_FLOOR)					// 玄関モデルの開始位置

//------------------------------------------------------------
// クラス定義(Xファイル)
//------------------------------------------------------------
class CXFile
{
public:			// 誰でもアクセスできる

	//************************************************************
	//	列挙型定義 (TYPE)
	//************************************************************
	enum TYPE
	{
		// 通常モデル
		TYPE_RIPPLE = 0,			// 波紋
		TYPE_KARIPLAYER,			// 仮プレイヤー
		TYPE_WOODBLOCK,				// 木箱
		TYPE_WEAPONCAGE,			// 武器小屋
		TYPE_FLOWERFRAC,			// 花瓶の破片
		TYPE_PLASTICFRAC,			// プラスチックケース破片
		TYPE_CAT_ATTACK,			// ネコの攻撃
		TYPE_HONEY,					// 蜂蜜
		TYPE_TOYCARSCREW,			// おもちゃの車(ネジ)
		TYPE_TITLEWALL,				// タイトルの壁
		TYPE_RED_ROOMBA_SUB,		// ルンバのプロペラ{赤のアウトライン}
		TYPE_TARAI,					// たらい
		TYPE_RED_NOTE4,				// 4分音符{赤のアウトライン}
		TYPE_RED_NOTE8,				// 8分音符{赤のアウトライン}
		TYPE_RED_NOTE16,			// 16分音符{赤のアウトライン}
		TYPE_TRAPIRON,				// ネズミ捕りの鉄部分
		TYPE_TRAPITEM,				// ネズミ捕り(アイテム)
		TYPE_RED_LEASHSET,			// 設置状態のリード{赤のアウトライン}
		TYPE_RED_PINSET,			// 設置状態の画鋲{赤のアウトライン}
		TYPE_PINONE,				// 破片用の画鋲
		TYPE_FANBLADE,				// 扇風機(羽根)
		TYPE_CONSENT,				// コンセント
		TYPE_DEATHARROW,			// 死亡矢印
		TYPE_GARBAGE,				// ゴミ
		TYPE_BOOKBLUE,				// 本(青)
		TYPE_BOOKGREEN,				// 本(緑)
		TYPE_BOOKYELLOW,			// 本(黄)
		TYPE_LEVERBODY,				// レバー(本体)
		TYPE_LEVERSTICK,			// レバー(棒)
		TYPE_RED_BOOKRED,			// 本(赤){赤のアウトライン}
		TYPE_RED_BOOKBLUE,			// 本(青){赤のアウトライン}
		TYPE_RED_BOOKGREEN,			// 本(緑){赤のアウトライン}
		TYPE_RED_BOOKYELLOW,		// 本(黄){赤のアウトライン}
		TYPE_RED_TOYCARBODY,		// おもちゃの車(本体){赤のアウトライン}
		TYPE_RED_TOYCARSCREW,		// おもちゃの車(ネジ){赤のアウトライン}
		TYPE_RED_HAIRBALL,			// 毬{赤のアウトライン}
		TYPE_RED_PETBOTTLE,			// ペットボトル{赤のアウトライン}

		// ブロックモデル
		TYPE_CARDBOARD,				// 段ボール
		TYPE_TISSUEBOX,				// ティッシュ箱
		TYPE_PENHOLDER,				// ペン立て
		TYPE_REMOCON,				// リモコン
		TYPE_BEAR,					// ブロック
		TYPE_CLOCK,					// 時計
		TYPE_RUBBISH,				// チリ紙
		TYPE_MILKPACK,				// 牛乳パック
		TYPE_OBAPHONE,				// オバフォン
		TYPE_WII,					// Wii
		TYPE_DS,					// DS
		TYPE_HEADPHONE,				// ヘッドフォン
		TYPE_PEN,					// ペン
		TYPE_ACADAPTER,				// ACアダプター
		TYPE_BUILDINGBLOCK,			// 積み木
		TYPE_GLASSES,				// 眼鏡ケース
		TYPE_PENCIL,				// 鉛筆
		TYPE_PICTUREFRAME,			// 写真立て
		TYPE_SHELF,					// 戸棚
		TYPE_PULLSHELF,				// 引き出し棚
		TYPE_KITCHEN,				// キッチン
		TYPE_REIZOUKO,				// 冷蔵庫
		TYPE_TABLE,					// テーブル
		TYPE_CHAIR,					// 机の椅子
		TYPE_CORKBOARD,				// コルクボード
		TYPE_DESK,					// デスク
		TYPE_DESKBOOK,				// デスク用の本
		TYPE_EXTIMGISHER,			// 消火器
		TYPE_KATEN,					// カーテン
		TYPE_KATENRAIL,				// カーテンのレール
		TYPE_TANSU02,				// たんす
		TYPE_TV_STAND,				// テレビのスタンド
		TYPE_WALL_PLUS50,			// 50*100の壁
		TYPE_WALL_PLUS100,			// 100*100の壁
		TYPE_DOOR001,				// ドア
		TYPE_SMALL_SHELF,			// 小さな棚
		TYPE_BOOKSHELF,				// 横長の本棚
		TYPE_TALBESHELF,			// テーブルの高さの棚
		TYPE_SOFA_SHEET,			// ソファー（座面）
		TYPE_SOFA_BACKTEST,			// ソファー（背もたれ）
		TYPE_CHAIR_SHEET,			// 机の椅子(座面)
		TYPE_CHAIR_BACKREST,		// 机の椅子(背もたれ)
		TYPE_LEVERBODYBLOCK,		// レバー(本体)
		TYPE_WINDOW,				// 窓
		TYPE_WALLCLOCK,				// 壁掛け時計
		TYPE_INTERIOR000,			// 壁のインテリア(棚)
		TYPE_WALLCROSS,				// 横柱

		// 障害物モデル
		TYPE_HONEYBOTTLE,			// 蜂蜜のボトル
		TYPE_SLIME,					// スライム
		TYPE_HAIRBALL,				// 毬
		TYPE_PETBOTTLE,				// ペットボトル
		TYPE_TOYCARBODY,			// おもちゃの車(本体)
		TYPE_RED_ROOMBA_MAIN,		// ルンバの本体{赤のアウトライン}
		TYPE_HIMO,					// ひも
		TYPE_SPEAKER,				// スピーカー
		TYPE_MOUSETRAP,				// ネズミ捕り
		TYPE_LEASH,					// リード
		TYPE_PIN,					// 画鋲
		TYPE_ELECFAN,				// 扇風機(本体)
		TYPE_CUP,					// コップ
		TYPE_GARBAGECAN,			// ゴミ箱
		TYPE_TV,					// テレビ
		TYPE_DYNAMITE,				// 爆弾
		TYPE_BOOKRED,				// 本(赤)
		TYPE_REDKATEN,				// 赤のカーテン
		TYPE_RATMECHA,				// ネズミメカ

		//ネズミモデル
		TYPE_RAT_BODY,				// 体
		TYPE_RAT_HEAD,				// 頭
		TYPE_RAT_LHAND,				// 左手
		TYPE_RAT_RHAND,				// 右手
		TYPE_RAT_LLEG,				// 左足
		TYPE_RAT_RLEG,				// 右足

		//猫モデル
		TYPE_CAT_BODY,				//体
		TYPE_CAT_HEAD,				//頭
		TYPE_CAT_LARM,				//左腕
		TYPE_CAT_LHAND,				//左手
		TYPE_CAT_RAEM,				//右腕
		TYPE_CAT_RHAND,				//右手
		TYPE_CAT_LFOOT,				//左腿
		TYPE_CAT_LLEG,				//左足
		TYPE_CAT_RFOOT,				//右腿
		TYPE_CAT_RLEG,				//右足
		TYPE_CAT_FLAG,				//白旗

		// ネズミモデル
		TYPE_RAT_GHOST,				// 幽霊モデル

		// 3Dテキストモデル
		TYPE_WINCAT_TEXT,			// ねこのかちテキスト
		TYPE_WINRAT_TEXT,			// ねずみのかちテキスト

		// 玄関のモデル
		TYPE_ENTRANCE_FLOOR,		// 玄関の床
		TYPE_ENTRANCE_WALL,			// 玄関の壁
		TYPE_SHOEBOX,				// 靴箱
		TYPE_ENTRANCE_DOOR,			// 玄関のドア
		TYPE_ENTRANCE_FRONT,		// 玄関の奥の壁
		TYPE_ENTRANCE_SHOEFLOOR,	// 靴履き場の床
		TYPE_ENTRANCE_SIDEWALL,		// 横の壁
		TYPE_BOOTS,					// ブーツ
		TYPE_SANDAL,				// サンダル
		TYPE_LESTHERSHOES,			// レザーシューズ

		// 当たり判定モデル
		TYPE_COLLISION,				// 当たり判定のエディットモデル

		// エディットモデル
		TYPE_MAX,					// 全モデルの総数
	};

	//************************************************************
	//	構造体定義 (SXFile)
	//************************************************************
	struct SXFile
	{
		LPD3DXMESH	 pMesh;						// メッシュ (頂点情報) へのポインタ
		LPD3DXBUFFER pBuffMat;					// マテリアルへのポインタ
		DWORD		 dwNumMat;					// マテリアルの数
		D3DXVECTOR3	 vtxMin;					// 最小の頂点座標
		D3DXVECTOR3	 vtxMax;					// 最大の頂点座標
		D3DXVECTOR3	 collsize;					// 当たり判定のサイズ
		float		 fRadius;					// 半径
		int			 m_nTexIdx[MAX_MATERIAL];	// テクスチャのインデックス
	};

	CXFile();			// コンストラクタ
	~CXFile();			// デストラクタ

	// メンバ関数
	static HRESULT Init(void);		// Xファイルの初期化処理
	static void Uninit(void);		// Xファイルの終了処理

	// セット・ゲット関数
	static SXFile GetXFile(TYPE type);	// Xファイルの取得処理

private:

	// メンバ関数
	static HRESULT LoadXFile(void);		// xファイルの読み込み
	static void SetCollision(void);		// 当たり判定の作成
	static HRESULT LoadTexture(void);	// テクスチャの読み込み

	// 静的メンバ変数
	static const char *c_apModelData[CXFile::TYPE_MAX];			// モデルの名前
	static SXFile m_apModel[CXFile::TYPE_MAX];					// モデルの情報
};

#endif