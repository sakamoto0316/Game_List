//============================================
//
//	弾の処理 [bullet3D.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _BULLET3D_H_
#define _BULLET3D_H_

#include "main.h"
#include "objectBillboard.h"

//弾クラス
class CBullet3D : public CObjectBillboard
{
public:
	typedef enum
	{
		BULLET_NORMAL = 0,
		BULLET_SPREAD_3WAY,
		BULLET_SPREAD_CONTINUE_3WAY,
		BULLET_SPREAD_CROSS,
		BULLET_SPREAD_EXCROSS,
	}BULLET_TYPE;

	CBullet3D(BULLET_TYPE Type, int nPriority = 2);
	~CBullet3D();

	static CBullet3D *Create(BULLET_TYPE Type);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	D3DXVECTOR3 GetMove(void) { return m_move; }
	void SetLife(int Life) { m_nLife = Life; }
	int GetLife(void) { return m_nLife; }
	void SetStop(float Stop) { m_stop = Stop; }
	float GetStop(void) { return m_stop; }
	int GetIdx(void) { return m_nIdxTexture; }
	void SetSpreadCount(int SpreadCount) { m_SpreadCount = SpreadCount; }


private:
	bool CollisionObject(D3DXVECTOR3 pos);	//オブジェクトとの当たり判定
	void Hit(D3DXVECTOR3 pos);							//弾が当たった時の処理

	BULLET_TYPE m_Type;						//弾の種類
	int m_SpreadCount;						//拡散弾を発生させるカウント
	int m_nIdxTexture;						//テクスチャの番号
	D3DXVECTOR3 m_move;						//移動量	
	int m_nLife;							//寿命	
	float m_stop;							//減衰係数	
};
#endif