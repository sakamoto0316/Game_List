//============================================
//
// 障害物マネージャーヘッダー[obstacle_manager.h]
// Author：小原立暉
//
//============================================
#ifndef _OBSTACLE_MANAGER_H_		// このマクロ定義がされていなかったら
#define _OBSTACLE_MANAGER_H_		// 2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "main.h"

//--------------------------------------------
// 前方宣言
//--------------------------------------------
class CObstacle;		// 障害物

//--------------------------------------------
// クラス(障害物マネージャークラス)
//--------------------------------------------
class CObstacleManager
{
public:				// 誰でもアクセスできる

	CObstacleManager();			// コンストラクタ
	~CObstacleManager();		// デストラクタ

	// メンバ関数
	void Regist(CObstacle* pThis);		// 登録処理
	void Uninit(void);					// 終了処理
	
	CObstacle* GetTop(void);				// 先頭の取得処理
	void Pull(CObstacle* pThis);			// リスト構造の引き抜き処理

	// 静的メンバ関数
	static CObstacleManager* Create(void);	// 生成処理
	static CObstacleManager* Get(void);		// 取得処理

private:			// 自分だけアクセスできる

	// メンバ変数
	CObstacle* m_pTop;	// 先頭のオブジェクト
	int m_nNumAll;			// オブジェクトの総数

	// 静的メンバ変数
	static CObstacleManager* m_pManager;		// マネージャーの変数
};

#endif