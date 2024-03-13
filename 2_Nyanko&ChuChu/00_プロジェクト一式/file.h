//============================================
//
// ファイルヘッダー[file.h]
// Author：小原立暉
//
//============================================
#ifndef _FILE_H_			//このマクロ定義がされていなかったら
#define _FILE_H_			//2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "main.h"
#include "obstacle.h"
#include "block.h"

//--------------------------------------------
// マクロ定義
//--------------------------------------------
#define MAX_FILE_DATA		(512)		// ファイルのデータの最大数

//--------------------------------------------
// クラス(ファイル読み込みクラス)
//--------------------------------------------
class CFile
{
public:			// 誰でもアクセスできる

	// 列挙型定義(種類)
	enum TYPE
	{
		TYPE_OBSTACLE = 0,	// 障害物
		TYPE_MAP_OBSTACLE1,	// マップの障害物1
		TYPE_MAP_OBSTACLE2,	// マップの障害物2
		TYPE_MAP_OBSTACLE3,	// マップの障害物3
		TYPE_MAP_OBSTACLESAMPLE,	// マップの障害物サンプル
		TYPE_MAP_BLOCK1,	// マップのブロック1
		TYPE_MAP_BLOCK2,	// マップのブロック2
		TYPE_MAP_BLOCK3,	// マップのブロック3
		TYPE_MAP_BLOCKSAMPLE,	// マップのブロックサンプル
		TYPE_BLOCK,			// ブロック
		TYPE_TUTORIAL_DEFULT,	// チュートリアルのデフォルトブロック
		TYPE_TUTORIAL_TABLE,	//チュートリアルのテーブル用ブロック
		TYPE_TUTORIAL_KILL,		// チュートリアルのキル用ブロック
		TYPE_TUTORIAL_ACTION,	// チュートリアルのアクション用ブロック
		TYPE_MAX			// この列挙型の総数
	};

	// 障害物の情報
	struct SObstacleInfo
	{
		D3DXVECTOR3 pos[MAX_FILE_DATA];			// 位置
		D3DXVECTOR3 rot[MAX_FILE_DATA];			// 向き
		CObstacle::TYPE type[MAX_FILE_DATA];	// 種類
		int nNum;								// 総数
		bool bSuccess;							// 成功状況
	};

	// ブロックの情報
	struct SBlockInfo
	{
		D3DXVECTOR3 pos[MAX_FILE_DATA];			// 位置
		CBlock::ROTTYPE rotType[MAX_FILE_DATA];	// 向きの種類
		CBlock::TYPE type[MAX_FILE_DATA];		// 種類
		int nNum;								// 総数
		bool bSuccess;							// 成功状況
	};

	CFile();					// コンストラクタ
	~CFile();					// デストラクタ

	// メンバ関数
	HRESULT Init(void);			// 初期化処理
	void Uninit(void);			// 終了処理

	HRESULT Save(const TYPE type);	// セーブ処理
	HRESULT Load(const TYPE type);	// ロード処理

	void FalseSuccess(void);		// 成功状況のリセット
	void SetMap(void);				// マップの設定処理

private:		// 自分のみアクセスできる

	// メンバ関数(セーブ関係)
	HRESULT SaveObstacle(const char *cFileName);		// 障害物のセーブ処理
	HRESULT SaveBlock(const char *cFileName);			// ブロックのセーブ処理

	// メンバ関数(ロード関係)
	HRESULT LoadObstacle(const char *cFileName);		// 障害物のロード処理
	HRESULT LoadBlock(const char *cFileName);		// ブロックのロード処理

	// メンバ変数
	SObstacleInfo m_ObstacleInfo;	// 障害物の情報
	SBlockInfo m_BlockInfo;			// ブロックの情報

	// 静的メンバ変数
	static const char* c_apBooleanDisp[2];			// bool型の表示
};

#endif