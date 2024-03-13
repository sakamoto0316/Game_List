//============================================
//
//	最高速度落下時の演出ポリゴンの処理 [FallEffect.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _FALLEFFECT_H_
#define _FALLEFFECT_H_

#include "main.h"
#include "objectBillboard.h"

//レベルアップUIクラス
class CFallEffect : public CObjectBillboard
{
public:

	CFallEffect(int nPriority = 5);
	~CFallEffect();

	static CFallEffect *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetIdx(int Idx) { m_nIdxTexture = Idx; }
	int GetIdx(void) { return m_nIdxTexture; }
	void SetLife(int Life) { m_nLife = Life; }
	int GetLife(void) { return m_nLife; }

private:
	int m_nIdxTexture;			//テクスチャの番号
	float m_MoveUP;				//上方向に進む力
	int m_nLife;				//寿命
};
#endif