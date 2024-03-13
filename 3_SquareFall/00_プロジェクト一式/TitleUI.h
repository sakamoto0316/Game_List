//============================================
//
//	タイトルのUIの処理 [TitleUI.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _TITLEUI_H_
#define _TITLEUI_H_

#include "main.h"
#include "objectXtex.h"

//オブジェクトプレイヤークラス
class CTitleUI : public CObjectXtex
{
public:

	CTitleUI(int nPriority = 5);
	~CTitleUI();

	static CTitleUI *Create();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetIdx(void) { return m_nIdxTexture; }

private:
	static LPD3DXMESH m_pMesh;				//メッシュ(頂点情報)へのポインタ
	static LPD3DXBUFFER m_pBuffMat;			//マテリアルへのポインタ
	static DWORD m_dwNumMat;				//マテリアルの数
	static int m_nIdxXModel;				//Xモデルの番号
	int m_nIdxTexture;						//テクスチャの番号
	int m_MyCount;							//自分の番号
};
#endif