//============================================
//
//	破壊可能ブロックの処理 [break_blockBillboard.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _BREAKBLOCKBILLBOARD_H_
#define _BREAKBLOCKBILLBOARD_H_

#include "main.h"
#include "objectBillboard.h"
#include "Map2D.h"

#define NUM 0

//前方宣言
class CDebugNumber3D;

//オブジェクトプレイヤークラス
class CBreak_BlockBillboard : public CObjectBillboard
{
public:

	CBreak_BlockBillboard(int nPriority = 3);
	~CBreak_BlockBillboard();

	static CBreak_BlockBillboard *Create();
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	D3DXVECTOR3 GetMove(void) { return m_move; }
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool bX);

	void SetCNumber(int Number) { m_CreateNumber = Number; }
	void SetWNumber(int Number) { m_WightNumber = Number; }
	void SetHNumber(int Number) { m_HeightNumber = Number; }
	void SetUse(int Create, int Wight, int Height, bool Use) { m_bUse[Create][Wight][Height] = Use; }
	void SetTexture(void);
	int GetIdx(void) { return m_nIdxTexture; }

private:
	int m_nIdxTexture;						//テクスチャの番号
	int m_CreateNumber;						//生成の番号
	int m_WightNumber;						//横の番号
	int m_HeightNumber;						//縦の番号
	static bool m_bUse[100][SET_BLOCK_WIGHT][SET_BLOCK_HEIGHT];
	D3DXVECTOR3 m_move;						//移動量	
	CDebugNumber3D *m_pCNumber;
	CDebugNumber3D *m_pWNumber;
	CDebugNumber3D *m_pHNumber;
	CDebugNumber3D *m_pBNumber;
};
#endif