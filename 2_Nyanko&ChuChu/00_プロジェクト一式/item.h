//===================================
//
// アイテムヘッダー[item.h]
// Author 小原立暉
//
//===================================
#ifndef _ITEM_H_
#define _ITEM_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"

//-----------------------------------
// クラス定義(アイテム)
//-----------------------------------
class CItem : public CModel
{
public:			// 誰でもアクセスできる

	// 列挙型定義(種類)
	enum TYPE
	{
		TYPE_MOUSETRAP = 0,		// ネズミ捕り
		TYPE_DYNAMITE,			// ダイナマイト
		TYPE_MAX				// この列挙型の総数
	};

	// 列挙型定義(状態)
	enum STATE
	{
		STATE_NONE = 0,		// 何もしない
		STATE_STANDBY,		// 待機
		STATE_MAX			// この列挙型の総数
	};

	CItem();			// コンストラクタ
	~CItem();			// デストラクタ

	// リスト構造関係
	void SetPrev(CItem* pPrev);		// 前のポインタの設定処理
	void SetNext(CItem* pNext);		// 後のポインタの設定処理
	CItem* GetPrev(void) const;		// 前のポインタの設定処理
	CItem* GetNext(void) const;		// 次のポインタの設定処理

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const TYPE type);			// 情報の設定処理

	// セット・ゲット関係
	void SetType(const TYPE type);		// 種類の設定処理
	void SetState(const STATE state);	// 状態の設定処理

	TYPE GetType(void) const;			// 種類の取得処理
	STATE GetState(void) const;			// 種類の取得処理

	// 静的メンバ関数
	static CItem* Create(const D3DXVECTOR3& pos, const TYPE type);	// 生成処理

private:		// 自分だけアクセスできる

	// メンバ関数
	void Cycle(void);		// 回転処理
	void Scaling(void);		// 拡縮処理

	// メンバ変数
	TYPE m_type;			// 種類
	STATE m_state;			// 状態
	float m_fScaleDest;		// 目的の拡大率

	// リスト構造関係
	CItem* m_pPrev;	// 前へのポインタ
	CItem* m_pNext;	// 次へのポインタ
};

#endif