//============================================
//
//	破壊されたブロックの処理 [breakPiece.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _BREAKPIECE_H_
#define _BREAKPIECE_H_

#include "main.h"
#include "objectXtex.h"

//前方宣言

//オブジェクトプレイヤークラス
class CBreak_Piece : public CObjectXtex
{
public:

	CBreak_Piece(int nPriority = 3);
	~CBreak_Piece();

	static CBreak_Piece *Create();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetIdx(void) { return m_nIdxTexture; }
	int GetIdxXModel(void) { return -1; }

private:

	D3DXCOLOR m_BlockColor;
	float m_ColorA;
	static LPD3DXMESH m_pMesh;				//メッシュ(頂点情報)へのポインタ
	static LPD3DXBUFFER m_pBuffMat;			//マテリアルへのポインタ
	static DWORD m_dwNumMat;				//マテリアルの数
	static int m_nIdxXModel;				//Xモデルの番号
	int m_nIdxTexture;						//テクスチャの番号

	D3DXVECTOR3 m_move;						//移動量	
	D3DXVECTOR3 m_rot;						//移動量	

};
#endif