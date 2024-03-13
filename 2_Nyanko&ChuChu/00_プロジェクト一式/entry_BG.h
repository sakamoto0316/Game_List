//===================================
//
// エントリー背景ヘッダー[entry_BG.h]
// Author 小原立暉
//
//===================================
#ifndef _ENTRY_BG_H_
#define _ENTRY_BG_H_

//***********************************
// インクルードファイル
//***********************************
#include "object.h"

//-----------------------------------
// 前方宣言
//-----------------------------------
class CModel;			// モデル

//-----------------------------------
// クラス定義(CEntryBG)
//-----------------------------------
class CEntryBG : public CObject
{
public:

	// 列挙型定義(種類)
	enum TYPE
	{
		TYPE_FLOOR = 0,		// 床
		TYPE_WALL,			// 壁
		TYPE_SHOEBOX,		// 靴箱
		TYPE_DOOR,			// ドア
		TYPE_FARWALL,		// 奥の壁
		TYPE_SHOEFLOOR,		// 靴履き場の床
		TYPE_SIDEWALL,		// 横の壁
		TYPE_BOOTS,			//ブーツ
		TYPE_SANDAL,		//サンダル
		TYPE_LESTHERSHOES,	//レザーシューズ
		TYPE_MAX			// この列挙型の総数
	};

	CEntryBG();				// コンストラクタ
	~CEntryBG();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(void);					// 情報の設定処理

	// 静的メンバ関数
	static CEntryBG* Create(void);		// 生成処理

private:

	// メンバ変数
	CModel* m_apModel[TYPE_MAX];		// モデルの情報
};

#endif