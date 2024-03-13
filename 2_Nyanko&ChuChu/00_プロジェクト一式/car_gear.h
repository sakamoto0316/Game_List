//===================================
//
// 歯車ヘッダー[car_gear.h]
// Author 小原立暉
//
//===================================
#ifndef _CAR_GEAR_H_
#define _CAR_GEAR_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"

//-----------------------------------
// クラス定義(歯車)
//-----------------------------------
class CCarGear : public CModel
{
public:			// 誰でもアクセスできる

	CCarGear();			// コンストラクタ
	~CCarGear();		// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos);				// 情報の設定処理

	// 静的メンバ関数
	static CCarGear* Create(const D3DXVECTOR3& pos);	// 生成処理

private:		// 自分だけアクセスできる
	bool m_bSe;		// SE再生状況

};

#endif