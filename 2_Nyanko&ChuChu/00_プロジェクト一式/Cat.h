//============================================
//
// 猫ヘッダー[Cat.h]
// Author：坂本翔唯
//
//============================================
#ifndef _CAT_H_					// このマクロ定義がされていなかったら
#define _CAT_H_					// 2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "player.h"

//--------------------------------------------
// 前方宣言
//--------------------------------------------
class CItemUI;			// アイテムUI

//--------------------------------------------
// クラス(プレイヤークラス)
//--------------------------------------------
class CCat : public CPlayer
{
public:			// 誰でもアクセスできる

	//************************************************************
	//	列挙型定義(モーションの種類)
	//************************************************************
	enum MOTIONTYPE
	{
		MOTIONTYPE_NEUTRAL = 0,		// 待機
		MOTIONTYPE_MOVE,			// 移動
		MOTIONTYPE_ATTACK,			// 攻撃
		MOTIONTYPE_KNOCKBACK,		// 吹っ飛び
		MOTIONTYPE_STUN,			// 気絶
		MOTIONTYPE_WIN,				// 勝利
		MOTIONTYPE_LOSE,			// 敗北
		MOTIONTYPE_MAX				// この列挙型の総数
	};

	enum ATTACKSTATE
	{
		ATTACKSTATE_MOVE = 0,		// 移動
		ATTACKSTATE_STANDBY,		// スタンバイ
		ATTACKSTATE_ATTACK,			// 攻撃中
		ATTACKSTATE_MAX				// この列挙型の総数
	};

	CCat();				// コンストラクタ
	~CCat();				// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void Hit(void);							// ヒット処理
	void MotionManager(void);				// モーションマネージャー
	void GetItem(const CItem::TYPE type);	// アイテムの取得処理

	// セット・ゲット関数
	void SetItemUI(void);					// アイテムUIの設定処理
	CItemUI* GetItemUI(void) const;			// アイテムUIの取得処理
	void DeleteItemUI(void);				// アイテムUIの消去処理
	int GetItemCount(void) const override;	// アイテムの総数の取得処理

	bool GetAttack_Jump(void) { return m_bAttack; }	// アタックジャンプ状態の取得処理
	bool GetItem_MultiAction(void) { return m_bItem; }

	void SetData(const D3DXVECTOR3& pos, const int nID, const TYPE type);		// 情報の設定処理

private:		// 自分だけアクセスできる

	// メンバ関数
	void Gravity(void);				// 重力処理
	void Attack(void);				// 攻撃処理
	void AttackStateManager(void);	// 攻撃状態マネージャー
	void AttackBlock(void);			// ブロックへの攻撃処理
	void Elevation(void);			// 起伏地面の当たり判定
	void ItemSet(void);				// ネコのアイテム設置処理
	void DebugMessage(void);		// デバッグメッセージ処理

	// メンバ変数
	CItemUI* m_pItemUI;				// アイテムUIの情報
	D3DXVECTOR3 m_AttackPos;		// 攻撃の位置
	D3DXVECTOR3 m_posDest;			// 目的の位置
	D3DXVECTOR3 m_rotDest;			// 目的の向き
	int m_nShadowIdx;				// 影のインデックス
	int m_nItemCount;				// アイテムの所持数

	ATTACKSTATE m_AttackState;		// 攻撃の状態
	int m_nAtkStateCount;			// 攻撃の状態のカウント
	int m_nAtkTime;					// 攻撃が出ている時間
	bool m_bAttack;					// 攻撃をしているかどうか
	bool m_bItem;					// アイテムを使用しているか
	bool m_bSE;						// SE再生してるか
};

#endif