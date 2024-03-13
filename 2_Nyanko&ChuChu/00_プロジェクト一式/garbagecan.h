//===================================
//
// ゴミ箱ヘッダー[garbagecan.h]
// Author 小原立暉
//
//===================================
#ifndef _GARBAGECAN_H_
#define _GARBAGECAN_H_

//***********************************
// インクルードファイル
//***********************************
#include "obstacle.h"

class CPlayer;

//-----------------------------------
// クラス定義(蜂蜜)
//-----------------------------------
class CGarbage : public CObstacle
{
public:			// 誰でもアクセスできる

	// 列挙型定義(状態)
	enum State
	{
		STATE_GARBAGECAN = 0,	// ゴミ箱
		STATE_FALL,				// 落下状態
		STATE_BANANA_NORMAL,	// バナナの皮
		STATE_BANANA_SLIDE,		// バナナの皮
		STATE_MAX				// この列挙型の総数
	};

	// 列挙型定義(状態)
	enum SLIDE
	{
		SLIDE_STOP = 0,	// 停止状態
		SLIDE_ON,		// 滑る状態
		SLIDE_BREAK,	// ぶつかり状態
		SLIDE_MAX		// この列挙型の総数
	};

	CGarbage();				// コンストラクタ
	~CGarbage();				// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// 情報の設定処理

	void SlideOn(D3DXVECTOR3 pos, D3DXVECTOR3 move, CPlayer *pPlayer);
	bool Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;		// 当たり判定処理
	bool Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;			// ヒット処理
	bool HitCircle(CPlayer* pPlayer, const float Radius) override;				// ヒットの円処理
	void Action(void) override;										// ギミック起動処理

private:		// 自分だけアクセスできる
	void Break(void);
	void StateManager(void);
	bool MagicWall(void);

	State m_State;
	SLIDE m_Slide;
	D3DXVECTOR3 m_PlayerPos;
	D3DXVECTOR3 m_SlideMove;
	D3DXVECTOR3 m_move;
	CPlayer *m_pPlayer;
};

#endif