//===================================
//
// 爆弾ヘッダー[dynamite.h]
// Author 堀川萩大
//
//===================================
#ifndef _DYNAMITE_H_
#define _DYNAMITE_H_

//***********************************
// インクルードファイル
//***********************************
#include "obstacle.h"
#include "object3Dfan.h"

class CObject3D;

class CExplosionFan : public CObject3DFan
{
public:
	CExplosionFan();			// コンストラクタ
	~CExplosionFan();			// デストラクタ

								// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXCOLOR& col);		// 情報の設定処理


	// 静的メンバ関数
	static CExplosionFan* Create(const D3DXVECTOR3& pos, const D3DXCOLOR& col);		// 生成処理

private:		// 自分だけアクセスできる

};

//-----------------------------------
// クラス定義(爆弾)
//-----------------------------------
class CDynamite : public CObstacle
{
public:			// 誰でもアクセスできる

				// 列挙型定義(状態)
	enum STATE
	{
		STATE_NONE = 0,		// 通常状態
		STATE_MINI,			// 縮小状態
		STATE_BIG,			// 拡大状態
		STATE_EXPLOSION,	// 爆発状態
		STATE_MAX			// この列挙型の総数
	};

	CDynamite();			// コンストラクタ
	~CDynamite();			// デストラクタ

							// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);		// 情報の設定処理
	bool Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;				// 当たり判定処理
	bool Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;					// ヒット処理

private:		// 自分だけアクセスできる
	
	// メンバ関数
	void ChageScale(void);	// モデルサイズ変更処理
	void Explosion(void);	// 爆発処理

	// メンバ変数
	CExplosionFan* m_pFan;
	CObject3D* m_pExWind[4];		// ポリゴン情報
	STATE m_state;				// 状態
	int m_nExplosion;			// 爆発タイミング
	int m_nDelTyming;			// 爆発の判定時間
	D3DXCOLOR m_col;
	float m_fRadius;
	D3DXVECTOR3 m_SizeChangeSpeed;
	D3DXVECTOR3 m_WindSize;
	D3DXCOLOR m_ColChangeSpeed;
};



#endif