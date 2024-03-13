//===================================
//
// ネズミメカヘッダー[toycar.h]
// Author 堀川萩大
//
//===================================
#ifndef _RATMECHA_H_
#define _RATMECHA_H_

//***********************************
// インクルードファイル
//***********************************
#include "obstacle.h"

//-----------------------------------
// 前方宣言
//-----------------------------------
class CPlayerID;			// プレイヤーのID

//-----------------------------------
// クラス定義(おもちゃの車)
//-----------------------------------
class CRatMecha : public CObstacle
{
public:			// 誰でもアクセスできる

	// 列挙型定義(状態)
	enum STATE
	{
		STATE_DRIVE = 0,	// ドライブ状態
		STATE_CURVE,		// カーブ状態
		STATE_BRAKE,		// ブレーキ状態
		STATE_MAX			// この列挙型の総数
	};

	CRatMecha();				// コンストラクタ
	~CRatMecha();				// デストラクタ

							// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// 情報の設定処理

	bool Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;		// 当たり判定処理
	bool Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;			// ヒット処理
	void Action(void) override;										// ギミック起動処理
	bool HitCircle(CPlayer* pPlayer, const float Radius) override;				// 円のヒット処理

private:		// 自分だけアクセスできる

	// メンバ関数
	void Drive(void);			// 走行処理
	void Curve(void);			// カービング処理
	void RotCalc(void);			// 向きの計算処理
	bool Block(void);			// ブロックの当たり判定処理
	bool Obstacle(void);		// 障害物の当たり判定処理
	bool MagicWall(void);		// 魔法壁の当たり判定処理

	// メンバ変数
	CPlayerID* m_pPlayerID;		// プレイヤーのIDのポインター
	D3DXVECTOR3 m_move;			// 移動量
	STATE m_state;				// 状態
	int m_nBrakeCount;			// ブレーキカウント
	float m_fRotDest;			// 目的の向き
	float m_fRotMagni;			// 向きの倍率
	bool m_bRight;				// 右向き状況
	bool m_bMove;				// 動いているか
	int m_nIdnumber;			// プレイヤーID番号

	// 静的メンバ変数
	static int m_nBgmAll;		// BGMを鳴らした音の総数
};

#endif