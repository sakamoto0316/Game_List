//===================================
//
// ピンヘッダー[Pin.h]
// Author 坂本翔唯
//
//===================================
#ifndef _PIN_H_
#define _PIN_H_

//***********************************
// インクルードファイル
//***********************************
#include "obstacle.h"

//-----------------------------------
// クラス定義(リード)
//-----------------------------------
class CPin : public CObstacle
{
public:			// 誰でもアクセスできる

	CPin();				// コンストラクタ
	~CPin();			// デストラクタ

	// 列挙型定義(状態)
	enum STATE
	{
		STATE_FALSE = 0,	// 停止状態
		STATE_FALLWAIT,		// 起動まで落下中に準備する
		STATE_TRUE,			// 起動状態
		STATE_MAX			// この列挙型の総数
	};

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// 情報の設定処理

	bool Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;		// ヒット処理
	bool HitCircle(CPlayer* pPlayer, const float Radius) override;
	void Action(void) override;

private:		// 自分だけアクセスできる
	void StateManager(D3DXVECTOR3 *pos, D3DXVECTOR3 *rot);

	D3DXVECTOR3 m_move;			//移動量
	STATE m_State;				//状態
};

#endif