//============================================
//
//	経験値の処理 [LevelPoint3D.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _LEVELPOINT_H_
#define _LEVELPOINT_H_

#include "main.h"
#include "objectX.h"

//前方宣言
class CItem;
class CEnemy;
class CLifeGaugeBillboard;

//オブジェクトプレイヤークラス
class CLevelPoint : public CObjectX
{
public:
	typedef enum
	{
		MOVE_WAIT = 0,
		MOVE_PLAYER,
		MOVE_MAX,
	}MOVE_STATE;

	CLevelPoint(int nPriority = 3);
	~CLevelPoint();
	int GetIdxXModel(void) { return m_nIdxXModel; }
	int GetIdxTexture(int nCnt) { return m_nIdxTexture[nCnt]; }

	static CLevelPoint *Create();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	D3DXVECTOR3 GetMove(void) { return m_move; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }

private:
	static int m_nIdxXModel;				//Xモデルの番号
	static int m_nIdxTexture[64];			//Xモデルテクスチャの番号
	D3DXVECTOR3 m_move;						//移動量
	float m_SpeedUp;						//移動量
	MOVE_STATE m_MoveState;					//移動状態
	int m_MoveCount;						//移動状態変更のためのカウント
};
#endif