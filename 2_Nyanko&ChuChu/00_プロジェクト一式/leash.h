//===================================
//
// リードヘッダー[Himo.h]
// Author 坂本翔唯
//
//===================================
#ifndef _LEASH_H_
#define _LEASH_H_

//***********************************
// インクルードファイル
//***********************************
#include "obstacle.h"

//-----------------------------------
// クラス定義(リード)
//-----------------------------------
class CLeash : public CObstacle
{
public:			// 誰でもアクセスできる

	CLeash();				// コンストラクタ
	~CLeash();				// デストラクタ

	// 列挙型定義(状態)
	enum STATE
	{
		STATE_FALSE = 0,	// 停止状態
		STATE_JUMPWAIT,		// 起動まで上に跳ね上がって準備する
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
	void HitMultiCircle(CPlayer* pPlayer, const float Radius, bool bInput) override;
	//void CollisionHead(bool Set) { m_bSetHead = Set; }
	//void CollisionToes(bool Set) { m_bSetToes = Set; }
	void Action(void) override;

	D3DXVECTOR3 GetPosHead(void) { return ActionPosHead; }
	D3DXVECTOR3 GetPosToes(void) { return ActionPosToes; }

private:		// 自分だけアクセスできる

	// メンバ関数
	void StateManager(D3DXVECTOR3 *pos);
	void SetActionPos(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void CollisionSetting(void);			// 当たり判定の設定処理

	// メンバ変数
	D3DXVECTOR3 m_move;			// 移動量
	D3DXVECTOR3 ActionPosHead;	// 先端の位置
	D3DXVECTOR3 ActionPosToes;	// 末端の位置
	D3DXVECTOR3 m_vtxMax;		// 最大値
	D3DXVECTOR3 m_vtxMin;		// 最小値
	STATE m_State;				// 状態
	int m_StateCount;			// 状態管理用のカウント
	bool m_bSetHead[4];			// 先端の準備完了
	bool m_bSetToes[4];			// 末端の準備完了
	bool m_bSe;					// SEの再生状況
};

#endif