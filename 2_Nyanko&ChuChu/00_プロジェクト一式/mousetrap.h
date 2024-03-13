//===================================
//
// ネズミ捕りヘッダー[mousetrap.h]
// Author 小原立暉
//
//===================================
#ifndef _MOUSETRAP_H_
#define _MOUSETRAP_H_

//***********************************
// インクルードファイル
//***********************************
#include "obstacle.h"

//-----------------------------------
// 前方宣言
//-----------------------------------
class CTrapIron;		// ネズミ捕りの鉄部分
class CDangerMark;		// 危険マーク

//-----------------------------------
// クラス定義(ネズミ捕り)
//-----------------------------------
class CMouseTrap : public CObstacle
{
public:			// 誰でもアクセスできる

	// 列挙型定義(状態)
	enum STATE
	{
		STATE_NONE = 0,		// 通常状態
		STATE_MOVE,			// 移動状態
		STATE_MAX			// この列挙型の総数
	};

	CMouseTrap();			// コンストラクタ
	~CMouseTrap();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// 情報の設定処理

	bool Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;		// ヒット処理

private:		// 自分だけアクセスできる

	// メンバ関数
	void Move(void);			// 移動処理
	void IronPosSet(void);		// 鉄部分の位置の設定処理

	// メンバ変数
	CTrapIron* m_pIron;			// 鉄部分
	CDangerMark* m_pMark;		// 危険マークの情報
	STATE m_state;				// 状態
	float m_fGravity;			// 重力
};

#endif