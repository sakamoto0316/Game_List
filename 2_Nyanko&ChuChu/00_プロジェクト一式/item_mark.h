//============================================
//
// アイテムのマークヘッダー[item_mark.h]
// Author：小原立暉
//
//============================================
#ifndef _ITEM_MARK_H_					// このマクロ定義がされていなかったら
#define _ITEM_MARK_H_					// 2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "object2D.h"
#include "item.h"

//--------------------------------------------
// クラス定義(アイテムのマーク)
//--------------------------------------------
class CItemMark : public CObject2D
{
public:				// 誰でもアクセスできる

	// 列挙型定義(状態)
	enum STATE
	{
		STATE_SMALL = 0,	// 小状態
		STATE_BIG,			// 大状態
		STATE_MAX			// この列挙型の総数
	};

	CItemMark();			// コンストラクタ
	~CItemMark();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const CItem::TYPE type);				// 情報の設定処理

	// セット・ゲット関係
	CItem::TYPE GetType(void) const;		// 種類の取得処理

	// 静的メンバ関数
	static CItemMark* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const CItem::TYPE type);	// 生成処理

private:			// 自分だけアクセスできる

	// メンバ変数
	void Sizing(void);		// サイズ設定処理
	
	// メンバ変数
	D3DXVECTOR3 m_sizeDest;	// 目的のサイズ
	D3DXVECTOR3 m_sizeCopy;	// 初期のサイズ
	STATE m_state;			// 状態
	CItem::TYPE m_type;		// 種類
};

#endif