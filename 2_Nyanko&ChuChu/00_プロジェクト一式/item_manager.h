//============================================
//
// アイテムマネージャーヘッダー[item_manager.h]
// Author：小原立暉
//
//============================================
#ifndef _ITEM_MANAGER_H_		// このマクロ定義がされていなかったら
#define _ITEM_MANAGER_H_		// 2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "main.h"

//--------------------------------------------
// 前方宣言
//--------------------------------------------
class CItem;		// アイテム

//--------------------------------------------
// クラス(アイテムマネージャークラス)
//--------------------------------------------
class CItemManager
{
public:				// 誰でもアクセスできる

	CItemManager();			// コンストラクタ
	~CItemManager();		// デストラクタ

	// メンバ関数
	void Regist(CItem* pThis);		// 登録処理
	void Uninit(void);					// 終了処理
	
	CItem* GetTop(void);				// 先頭の取得処理
	void Pull(CItem* pThis);			// リスト構造の引き抜き処理

	// 静的メンバ関数
	static CItemManager* Create(void);	// 生成処理
	static CItemManager* Get(void);		// 取得処理

private:			// 自分だけアクセスできる

	// メンバ変数
	CItem* m_pTop;	// 先頭のオブジェクト
	int m_nNumAll;			// オブジェクトの総数

	// 静的メンバ変数
	static CItemManager* m_pManager;		// マネージャーの変数
};

#endif