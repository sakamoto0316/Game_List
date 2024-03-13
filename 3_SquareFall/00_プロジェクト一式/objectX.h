//============================================
//
//	オブジェクトXファイル [objectX.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

#include "main.h"
#include "object.h"

//オブジェクトXクラス
class CObjectX : public CObject
{
public:
	CObjectX(int nPriority = 7);
	~CObjectX();

	static CObjectX *Create(void);

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	void BindFile(LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD pdwNumMat);

	void SetVerTex(void);							//頂点座標の設定
	void SetAnim(D3DXVECTOR2 Tex);					//テクスチャ座標の設定
	void SetColor(D3DXCOLOR col);					//頂点カラーの設定

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	void SetPosOld(D3DXVECTOR3 pos) { m_posOld = pos; }
	D3DXVECTOR3 GetPosOld(void) { return m_posOld; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	void SetWight(float Wight) { m_Wight = Wight; }
	float GetWight(void) { return m_Wight; }
	void SetHeight(float Height) { m_Height = Height; }
	float GetHeight(void) { return m_Height; }
	void SetMatColor(D3DXCOLOR SetColor) { m_MatColor = SetColor; m_bUseColor = true; }
	void SetDefColor(void) { m_bUseColor = false; }

	virtual int GetIdxXModel(void) { return -1; }
	virtual int GetIdxTexture(int nCnt) { return -1; }

protected:
	D3DXMATRIX m_mtxWorld;					//ワールドマトリックス

private:
	float m_Wight;							//幅
	float m_Height;							//高さ
	LPDIRECT3DTEXTURE9 *m_pTexture;			//テクスチャへのポインタ
	DWORD m_dwNumMat;						//マテリアルの数
	D3DXVECTOR3 m_pos;						//頂点の位置
	D3DXVECTOR3 m_posOld;					//過去の位置
	D3DXVECTOR3 m_rot;						//向き
	D3DXMATERIAL m_StateMat;				//状態管理時の色
	D3DXCOLOR m_MatColor;					//マテリアルの色
	bool m_bUseColor;						//色を変更しているかどうか
};
#endif