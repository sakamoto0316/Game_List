//============================================
//
//	ライフゲージ [LifeGauge.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _LIFEGAUGE_H_
#define _LIFEGAUGE_H_

#include "main.h"
#include "Gauge.h"

//オブジェクトプレイヤークラス
class CLifeGauge : public CGauge
{
public:

	CLifeGauge(bool Vertical, bool NumberUI, int nPriority = 3);
	~CLifeGauge();

	static CLifeGauge *Create(bool Vertical,bool NumberUI);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetIdx(void) { return m_nIdxTexture; }

private:
	int m_nIdxTexture;		//テクスチャの番号
};
#endif