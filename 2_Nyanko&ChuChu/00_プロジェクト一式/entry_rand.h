//===================================
//
// エントリー画面のランダム指示ヘッダー[entry_rand.h]
// Author 小原立暉
//
//===================================
#ifndef _ENTRY_RANDOM_H_
#define _ENTRY_RANDOM_H_

//***********************************
// インクルードファイル
//***********************************
#include "object2D.h"

//-----------------------------------
// クラス(エントリー画面のランダム指示)
//-----------------------------------
class CEntryRandom : public CObject2D
{
public:			// 誰でもアクセスできる

	CEntryRandom();			// コンストラクタ
	~CEntryRandom();		// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(void);		// 情報の設定処理

	// 静的メンバ関数
	static CEntryRandom* Create(void);		// 生成処理

private:		// 自分だけアクセスできる


};

#endif