//============================================
//
//	敵の処理 [Enemy3D.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _ENEMY3D_H_
#define _ENEMY3D_H_

#include "main.h"
#include "objectX.h"

//前方宣言
class CItem;
class CEnemy;
class CLifeGaugeBillboard;
class CEenmyBullet3D;

//オブジェクトプレイヤークラス
class CEnemy3D : public CObjectX
{
public:
	typedef enum
	{
		ENEMY_NORMAL = 0,
		ENEMY_WALLD,
		ENEMY_WALLU,
		ENEMY_GROUND,
		ENEMY_MAX,
	}ENEMY_TYPE;

	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_DAMAGE,
		STATE_WAIT,
		STATE_MAX,
	}STATE_TYPE;

	CEnemy3D(ENEMY_TYPE Type, int nPriority = 3);
	~CEnemy3D();
	int GetIdxXModel(void) { return m_nIdxXModel[m_Type]; }
	int GetIdxTexture(int nCnt) { return m_nIdxTexture[m_Type][nCnt]; }

	static CEnemy3D *Create(ENEMY_TYPE Type);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	D3DXVECTOR3 MoveNormal(D3DXVECTOR3 pos);
	D3DXVECTOR3 MoveWallD(D3DXVECTOR3 pos);
	void MoveWallU(D3DXVECTOR3 pos);
	D3DXVECTOR3 MoveGround(D3DXVECTOR3 pos);
	void Draw(void);
	void Hit(D3DXVECTOR3 pos, int Damage);											//ダメージヒット処理
	void Death(D3DXVECTOR3 pos, float nRadius, int BreakCount);						//死亡処理
	void StateManager(void);														//状態管理
	bool CollisionBlock(D3DXVECTOR3 *pos, bool bX);									//ブロックとの当たり判定
	void CollisionObjectCircle(D3DXVECTOR3 pos, float nRadiusOut, int BreakCount);	//円の当たり判定
	void SetNULL(void);

	D3DXVECTOR3 GetMove(void) { return m_move; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	void SetEnemyType(ENEMY_TYPE Type) { m_Type = Type; }
	int GetLife(void) { return m_nLife; }

private:
	static int m_nIdxXModel[ENEMY_MAX];			//Xモデルの番号
	static int m_nIdxTexture[ENEMY_MAX][64];	//Xモデルテクスチャの番号
	D3DXVECTOR3 m_move;							//移動量	
	int m_nLife;								//体力	
	CLifeGaugeBillboard *m_pLifeGauge;			//体力用のゲージ表示
	STATE_TYPE m_State;							//状態
	ENEMY_TYPE m_Type;							//敵の種類
	int m_StateCount;							//状態の長さを管理するカウント
	int m_BulletCount;							//敵が弾を撃つためのカウント
	int m_JumpCount;							//敵がジャンプするためのカウント
	bool m_bJump;								//敵がジャンプしたかどうか
	int m_nDeathStopCount;						//敵が死亡する前のヒットストップ
	bool m_bDeathCountFlog;						//敵が死亡するときのフラグ
	bool m_bDeath;								//敵が死亡したかどうか
	CEnemy3D *pEnemy;							//敵のポインタ
};
#endif