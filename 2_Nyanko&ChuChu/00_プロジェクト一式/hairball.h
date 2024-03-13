//===================================
//
// 毬ヘッダー[hairball.h]
// Author 小原立暉
//
//===================================
#ifndef _HAIRBALL_H_
#define _HAIRBALL_H_

//***********************************
// インクルードファイル
//***********************************
#include "obstacle.h"

//-----------------------------------
// クラス定義(毬)
//-----------------------------------
class CHairBall : public CObstacle
{
public:			// 誰でもアクセスできる

	// 列挙型定義(状態)
	enum STATE
	{
		STATE_STOP = 0,		// 停止状態
		STATE_SMASH,		// 吹き飛ばし状態
		STATE_MAX			// この列挙型の総数
	};

	CHairBall();			// コンストラクタ
	~CHairBall();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// 情報の設定処理

	bool Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;		// 当たり判定処理
	bool Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;			// ヒット処理

private:		// 自分だけアクセスできる

	// メンバ関数
	void Move(void);			// 移動処理
	void Gravity(void);			// 重力処理
	void Elevation(void);		// 起伏地面の当たり判定
	void Block(void);			// ブロックの当たり判定
	void MagicWall(void);		// 魔法の壁

	// メンバ変数
	D3DXVECTOR3 m_move;			// 移動量
	STATE m_state;				// 状態
};

#endif