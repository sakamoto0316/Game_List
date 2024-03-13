//===================================
//
// タイトルの壁ヘッダー[title_wall.h]
// Author 小原立暉
//
//===================================
#ifndef _TITLE_WALL_H_
#define _TITLE_WALL_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"

//-----------------------------------
// クラス定義(タイトルの壁)
//-----------------------------------
class CTitleWall : public CModel
{
public:			// 誰でもアクセスできる

	CTitleWall();			// コンストラクタ
	~CTitleWall();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(void);				// 情報の設定処理

	// 静的メンバ関数
	static CTitleWall* Create(void);	// 生成処理

private:		// 自分だけアクセスできる

};

#endif