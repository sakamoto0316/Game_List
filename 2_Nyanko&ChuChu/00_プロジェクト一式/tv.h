//===================================
//
// テレビヘッダー[cup.h]
// Author 堀川萩大
//
//===================================
#ifndef _TV_H_
#define _TV_H_

//***********************************
// インクルードファイル
//***********************************
#include "obstacle.h"

class CConsent;
class CObject3D;
class CModel;

//-----------------------------------
// クラス定義(コップ)
//-----------------------------------
class CTv : public CObstacle
{
public:			// 誰でもアクセスできる

	CTv();				// コンストラクタ
	~CTv();				// デストラクタ

	// 列挙型定義(状態)
	enum STATE
	{
		STATE_NONE = 0,	// アイテム取得可能状態
		STATE_COOLDOWN,	// クールタイム状態
		STATE_BOMB,		// 爆弾画面だった場合
		STATE_MAX		// この列挙型の総数
	};

	// 構造体定義(リモコン)
	struct SRemocon
	{
		CModel* pRemocon;			// リモコンのモデル情報
		CBillboard* pGimmickUI;		// ギミックUI
	};

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// 情報の設定処理

	bool Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;		// 当たり判定処理
	bool HitCircle(CPlayer* pPlayer, const float Radius) override;
	void Action(void) override;		// アクション
	bool HitRemocon(void);			// リモコンのヒット処理
	void PowerAction(void);			// 電源処理
	void VisionChange(void);		// テレビ画面切り替え
private:		// 自分だけアクセスできる
	void StateManager(void);		// 状態管理マネージャー

	CObject3D *m_pVision;		// ポリゴン情報
	SRemocon m_remocon;			// リモコン
	D3DXVECTOR3 m_vtxMax;		// 最大値
	D3DXVECTOR3 m_vtxMin;		// 最小値
	STATE m_State;				// テレビの状態
	int m_nCoolTime;			// クールタイム
	int m_nChangeVision;		// 画面変化処理
	bool m_bPower;				// 電源
};

#endif