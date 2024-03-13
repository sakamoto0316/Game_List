//============================================
//
//	ゲージビルボード [GaugeBillboard.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _GAUGEBILLBOARD_H_
#define _GAUGEBILLBOARD_H_

#include "main.h"
#include "object.h"

//前方宣言
class CNumber;

//オブジェクト2Dクラス
class CGaugeBillboard : public CObject
{
public:
	CGaugeBillboard(int nPriority = 3);
	~CGaugeBillboard();

	static CGaugeBillboard *Create(void);

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

	void SetVerTex(void);							//頂点座標の設定
	void SetAnim(D3DXVECTOR2 Tex);					//テクスチャ座標の設定
	void SetColor(D3DXCOLOR col);					//頂点カラーの設定

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	void SetGaugeMax(int Max) { m_GaugeMax = Max; }
	int GetGaugeMax(void) { return m_GaugeMax; }
 	void SetGauge(int Gauge) { m_Gauge = Gauge; }
	int GetGauge(void) { return m_Gauge; }
	void SetTilt(float Tilt) { m_Tilt = Tilt; }
	float GetTilt(void) { return m_Tilt; }
	void SetWight(float Wight) { m_Wight = Wight; }
	float GetWight(void) { return m_Wight; }
	void SetHeight(float Height) { m_Height = Height; }
	float GetHeight(void) { return m_Height; }
	int GetIdx(void) { return m_nIdxTexture; }

protected:
	void SetVtxBuff(LPDIRECT3DVERTEXBUFFER9 Height) { m_pVtxBuff = Height; }
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) { return m_pVtxBuff; }

private:
	int m_nIdxTexture;						//テクスチャの番号
	int m_GaugeMax;						//最大のゲージ
	int m_Gauge;							//現在のゲージ
	float m_Tilt;							//ゲージの傾き
	float m_Wight;							//幅
	float m_Height;							//高さ
	D3DXVECTOR3 m_pos;						//頂点の位置
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9 m_pTexture;			//テクスチャへのポインタ
	D3DXMATRIX m_mtxWorld;					//ワールドマトリックス

	CNumber *m_pNumberMax;
	CNumber *m_pNumber;
};
#endif