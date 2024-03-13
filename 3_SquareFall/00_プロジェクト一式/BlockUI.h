//============================================
//
//	ブロックのUIの処理 [BlockUI.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _BLOCKUI_H_
#define _BLOCKUI_H_

#include "main.h"
#include "objectXtex.h"

//オブジェクトプレイヤークラス
class CBlockUI : public CObjectXtex
{
public:

	CBlockUI(int nPriority = 5);
	~CBlockUI();

	static CBlockUI *Create();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetIdx(void) { return m_nIdxTexture; }
	bool Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3 *pMove, float fHeight, float fWidth, bool bX);
	void Hit(D3DXVECTOR3 pos, int Damage);
	void SetMyCount(int Count) { m_MyCount = Count; }

private:
	static LPD3DXMESH m_pMesh;				//メッシュ(頂点情報)へのポインタ
	static LPD3DXBUFFER m_pBuffMat;			//マテリアルへのポインタ
	static DWORD m_dwNumMat;				//マテリアルの数
	static int m_nIdxXModel;				//Xモデルの番号
	int m_nIdxTexture;						//テクスチャの番号
	int m_MyCount;							//自分の番号
};
#endif