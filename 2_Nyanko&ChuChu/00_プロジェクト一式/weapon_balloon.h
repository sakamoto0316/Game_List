//===================================
//
// 武器のふきだしヘッダー[weapon_balloon.h]
// Author 小原立暉
//
//===================================
#ifndef _WEAPON_BALLOON_H_
#define _WEAPON_BALLOON_H_

//***********************************
// インクルードファイル
//***********************************
#include "objectbillboard.h"

//-----------------------------------
// クラス定義(武器のふきだし)
//-----------------------------------
class CWeaponBalloon : public CBillboard
{
public:

	CWeaponBalloon();		// コンストラクタ
	~CWeaponBalloon();		// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const char* pFileName);		// 情報の設定処理

	// 静的メンバ関数
	static CWeaponBalloon* Create(const D3DXVECTOR3& pos, const char* pFileName);		// 生成処理

private:

	// メンバ変数
};

#endif