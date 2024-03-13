//===========================================
//
// 武器小屋ヘッダー[weapon_cage.h]
// Author 小原立暉
//
//===========================================
#ifndef _WEAPON_CAGE_H_
#define _WEAPON_CAGE_H_

//-------------------------------------------
// インクルードファイル
//-------------------------------------------
#include "model.h"

//-------------------------------------------
// クラス定義(武器小屋)
//-------------------------------------------
class CWeaponCage : public CModel
{
public:		// 誰でもアクセスできる

	CWeaponCage();			// コンストラクタ
	~CWeaponCage();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos);		// 情報の設定処理

	// 静的メンバ関数
	static CWeaponCage* Create(const D3DXVECTOR3& pos);		// 生成処理

private:		// 自分だけアクセスできる

};

#endif