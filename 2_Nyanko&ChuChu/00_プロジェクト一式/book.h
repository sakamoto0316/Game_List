//===================================
//
// 本ヘッダー[book.h]
// Author 小原立暉
//
//===================================
#ifndef _BOOK_H_
#define _BOOK_H_

//***********************************
// インクルードファイル
//***********************************
#include "obstacle.h"

//-----------------------------------
// マクロ定義
//-----------------------------------
#define MAX_BOOK	(3)		// 本の最大数

//-----------------------------------
// 前方宣言
//-----------------------------------
class CModel;			// モデル

//-----------------------------------
// クラス定義(本)
//-----------------------------------
class CBook : public CObstacle
{
public:			// 誰でもアクセスできる

	// 列挙型定義(状態)
	enum STATE
	{
		STATE_STOP = 0,		// 停止状態
		STATE_COLLAPSE,		// 倒れ状態
		STATE_MAX			// この列挙型の総数
	};

	// 構造体定義(本)
	struct SBook
	{
		CModel* pBook;		// 上に載っている本の情報
		D3DXVECTOR3 move;	// 移動量
		float fGravity;		// 重力
		bool bDisp;			// 描画状況
		bool bMove;			// 移動状況
		bool bSe;			// SE再生状況
	};

	CBook();				// コンストラクタ
	~CBook();				// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// 情報の設定処理

	bool Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;	// 当たり判定処理
	bool Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;		// ヒット処理
	bool HitCircle(CPlayer* pPlayer, const float Radius) override;			// 円のヒット処理
	void Action(CPlayer* pPlayer) override;			// アクション処理

private:		// 自分だけアクセスできる

	// メンバ関数
	void StateManager(void);	// 状態マネージャー
	bool KillZ(void);			// Z軸による消去処理

	// メンバ変数
	SBook m_aBook[MAX_BOOK];	// 本の構造体
	D3DXVECTOR3 m_move;			// 移動量
	STATE m_state;				// 状態
	int m_nActionID;			// アクションID
	float m_fGravity;			// 重力
	bool m_bDisp;				// 描画状況
	bool m_bMove;				// 移動状況
	bool m_bSe;					// SE再生状況
};

#endif