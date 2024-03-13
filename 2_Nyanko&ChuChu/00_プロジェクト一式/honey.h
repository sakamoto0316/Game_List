//===================================
//
// 蜂蜜ヘッダー[honey.h]
// Author 小原立暉
//
//===================================
#ifndef _HONEY_H_
#define _HONEY_H_

//***********************************
// インクルードファイル
//***********************************
#include "obstacle.h"

//-----------------------------------
// クラス定義(蜂蜜)
//-----------------------------------
class CHoney : public CObstacle
{
public:			// 誰でもアクセスできる

	// 列挙型定義(状態)
	enum State
	{
		STATE_HONEYBOTTLE = 0,	// ボトル
		STATE_HONEY,			// 液体
		STATE_MAX				// この列挙型の総数
	};

	CHoney();				// コンストラクタ
	~CHoney();				// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// 情報の設定処理

	bool Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;		// 当たり判定処理
	bool Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;			// ヒット処理
	bool HitCircle(CPlayer* pPlayer, const float Radius) override;				// ヒット処理
	void Action(void) override;													// ギミック起動処理

private:		// 自分だけアクセスできる

	// メンバ関数
	void StateManager(void);

	// メンバ変数
	State m_State;
	int m_nWalkSeCount;	// 歩く音のカウンター
	bool m_bLeakSe;		// 蜂蜜広がるSE
};

#endif