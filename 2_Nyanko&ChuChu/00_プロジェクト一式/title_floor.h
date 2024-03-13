//===================================
//
// タイトルの床ヘッダー[title_floor.h]
// Author 小原立暉
//
//===================================
#ifndef _TITLE_FLOOR_H_	//このマクロが定義されていなければ
#define _TITLE_FLOOR_H_	//二重インクルード防止マクロ

//***********************************
// インクルードファイル
//***********************************
#include "Object3D.h"

//-----------------------------------
// クラス定義(CTitleFloor)
//-----------------------------------
class CTitleFloor :public CObject3D
{
public:

	CTitleFloor();			// コンストラクタ
	~CTitleFloor();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(void);		// 情報の設定処理

	// 静的メンバ変数
	static CTitleFloor* Create(void);		// 生成処理

private:

};
#endif