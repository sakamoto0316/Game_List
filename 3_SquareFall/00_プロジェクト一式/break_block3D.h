//============================================
//
//	破壊可能ブロックの処理 [break_block3D.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _BREAKBLOCK3D_H_
#define _BREAKBLOCK3D_H_

#include "main.h"
#include "objectXtex.h"
#include "Map2D.h"

#define NUM 0

//前方宣言
class CDebugNumber3D;

//オブジェクトプレイヤークラス
class CBreak_Block3D : public CObjectXtex
{
public:

	CBreak_Block3D(int nPriority = 3);
	~CBreak_Block3D();

	static CBreak_Block3D *Create();
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	D3DXVECTOR3 GetMove(void) { return m_move; }
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Wave(void);											//振動処理
	void Hit(D3DXVECTOR3 pos, int Damage);						//ダメージヒット処理
	bool Break(void);
	void BreakCountSet(int Count);
	static void CreateMapBlocks(int CreateNumber, D3DXVECTOR3 pos);
	bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool bX);
	void ChangeColor(int Level);
	void CleanBlockUse(void);

	int GetCNumber(void) { return m_CreateNumber; }
	void SetCNumber(int Number) { m_CreateNumber = Number; }
	int GetWNumber(void) { return m_WightNumber; }
	void SetWNumber(int Number) { m_WightNumber = Number; }
	int GetHNumber(void) { return m_HeightNumber; }
	void SetHNumber(int Number) { m_HeightNumber = Number; }
	void SetUse(int Create, int Wight, int Height, bool Use) { m_bUse[Create][Wight][Height] = Use; }
	static void TrueUse(int Create, int Wight, int Height) { m_bUse[Create][Wight][Height] = true; }
	static bool GetCheckUse(int Create, int Wight, int Height) { return m_bUse[Create][Wight][Height]; }
	bool GetUse(void) { return m_bUse[m_CreateNumber][m_WightNumber][m_HeightNumber]; }
	static void UseBreak(int Create, int Wight, int Height);
	void SetTexture(void);
	int GetIdx(void) { return m_nIdxTexture; }
	void bUseSet(void);
	int GetIdxXModel(void) { return -1; }

private:
	static LPD3DXMESH m_pMesh;				//メッシュ(頂点情報)へのポインタ
	static LPD3DXBUFFER m_pBuffMat;			//マテリアルへのポインタ
	static DWORD m_dwNumMat;				//マテリアルの数
	static int m_nIdxXModel;				//Xモデルの番号
	int m_nIdxTexture;						//テクスチャの番号
	int m_CreateNumber;						//生成の番号
	int m_WightNumber;						//横の番号
	int m_HeightNumber;						//縦の番号
	static bool m_bUse[100][SET_BLOCK_WIGHT + 2][SET_BLOCK_HEIGHT];
	bool m_bBreak;
	int m_nWaveCount;
	float m_nWavePower;
	bool m_bWave;
	int m_nBreakCount;
	bool m_bColorChange;					//色が変わったかどうか
	D3DXCOLOR m_BlockColor;
	D3DXVECTOR3 m_move;						//移動量	
	CDebugNumber3D *m_pCNumber;
	CDebugNumber3D *m_pWNumber;
	CDebugNumber3D *m_pHNumber;
	CDebugNumber3D *m_pBNumber;
};
#endif