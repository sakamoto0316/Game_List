//===================================
//
// 天井ヘッダー[ceil.h]
// Author 小原立暉
//
//===================================
#ifndef _CEIL_H_
#define _CEIL_H_

//***********************************
// インクルードファイル
//***********************************
#include "object.h"

//-----------------------------------
// マクロ定義
//-----------------------------------
#define MAX_CEIL	(2)		// 天井ポリゴンの総数

//-----------------------------------
// 前方宣言
//-----------------------------------
class CObject3D;

//-----------------------------------
// クラス定義(CCeil)
//-----------------------------------
class CCeil : public CObject
{
public:

	CCeil();				// コンストラクタ
	~CCeil();				// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos);				// 情報の設定処理

	// 静的メンバ関数
	static CCeil* Create(const D3DXVECTOR3& pos);		// 生成処理

private:

	// メンバ変数
	CObject3D* m_apCeil[MAX_CEIL];		// 屋根のポリゴン
};

#endif