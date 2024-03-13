//===================================
//
// 扇風機ヘッダー[electricfan.h]
// Author 小原立暉
//
//===================================
#ifndef _ELECTRICFAN_H_
#define _ELECTRICFAN_H_

//***********************************
// インクルードファイル
//***********************************
#include "obstacle.h"

//-----------------------------------
// 前方宣言
//-----------------------------------
class CFanBlade;		// 扇風機のファン

//-----------------------------------
// クラス定義(扇風機)
//-----------------------------------
class CElecFan : public CObstacle
{
public:			// 誰でもアクセスできる

	CElecFan();				// コンストラクタ
	~CElecFan();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// 情報の設定処理

	bool Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;		// 当たり判定処理
	bool Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;			// ヒット処理
	bool HitCircle(CPlayer* pPlayer, const float Radius) override;				// 円のヒット処理
	void Action(void) override;										// ギミック起動処理

private:		// 自分だけアクセスできる

	// メンバ変数
	CFanBlade* m_pFan;		// 扇風機のファン
	bool m_bPower;			// 電源状況
};

#endif