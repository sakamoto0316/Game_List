//============================================
//
//	左右のブロックの処理 [SideBlock3D.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _SIDEBLOCK3D_H_
#define _SIDEBLOCK3D_H_

#include "main.h"
#include "objectXtex.h"
#include "Map2D.h"

//前方宣言
class CDebugNumber3D;

//オブジェクトプレイヤークラス
class CSide_Block3D : public CObjectXtex
{
public:

	CSide_Block3D(int nPriority = 3);
	~CSide_Block3D();

	static CSide_Block3D *Create();
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	D3DXVECTOR3 GetMove(void) { return m_move; }
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void ChangeColor(int Level);

	int GetIdx(void) { return m_nIdxTexture; }
	int GetIdxXModel(void) { return -1; }

private:
	static LPD3DXMESH m_pMesh;				//メッシュ(頂点情報)へのポインタ
	static LPD3DXBUFFER m_pBuffMat;			//マテリアルへのポインタ
	static DWORD m_dwNumMat;				//マテリアルの数
	static int m_nIdxXModel;				//Xモデルの番号
	int m_nIdxTexture;						//テクスチャの番号
	bool m_bColorChange;					//色が変わったかどうか
	D3DXCOLOR m_BlockColor;
	D3DXVECTOR3 m_move;						//移動量	
	CDebugNumber3D *m_pCNumber;
	CDebugNumber3D *m_pWNumber;
	CDebugNumber3D *m_pHNumber;
	CDebugNumber3D *m_pBNumber;
};
#endif