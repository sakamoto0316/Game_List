//===================================
//
// ペットボトルヘッダー[petbottle.h]
// Author 大野祥平
//
//===================================
#ifndef _PETBOTTLE_H_
#define _PETBOTTLE_H_

//***********************************
// インクルードファイル
//***********************************
#include "obstacle.h"

//-----------------------------------
// クラス定義(ペットボトル)
//-----------------------------------
class CPetbottle : public CObstacle
{
public:			// 誰でもアクセスできる

	// 列挙型定義(状態)
	enum STATE
	{
		STATE_STAND = 0,	// 通常状態
		STATE_COLLAPSE,		// 倒れ状態
		STATE_LEAVE,		// 退場状態
		STATE_MAX			// この列挙型の総数
	};

	CPetbottle();			// コンストラクタ
	~CPetbottle();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// 情報の設定処理

	bool Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;	// 当たり判定処理
	bool Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;		// ヒット処理
	bool HitCircle(CPlayer* pPlayer, const float Radius) override;			// 円のヒット処理
	void Action(void) override;												// ギミック起動処理

private:		// 自分だけアクセスできる

	// メンバ関数
	bool Block(void);				// ブロックとの当たり判定
	void Cycle(void);				// 回転処理
	void Gravity(void);				// 重力処理
	void Elevation(void);			// 起伏地面の当たり判定
	bool MagicWall(void);			// 魔法の壁処理
	void CollsionSetting(void);		// 当たり判定の設定処理

	// メンバ変数
	D3DXVECTOR3 m_move;			// 移動量
	D3DXVECTOR3 m_posPlayer;	// ぶつかったプレイヤーの位置
	D3DXVECTOR3 m_vtxMax;		// 最大値
	D3DXVECTOR3 m_vtxMin;		// 最小値
	STATE m_state;				// 状態
	float m_fAlpha;				// 透明度
};
#endif