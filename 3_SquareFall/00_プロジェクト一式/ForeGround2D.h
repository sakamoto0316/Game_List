//============================================
//
//	前景の処理 [ForeGround2D.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _FOREGROUND_H_
#define _FOREGROUND_H_

#include "main.h"
#include "object2D.h"

//オブジェクトプレイヤークラス
class CFG : public CObject2D
{
public:

	CFG(int Cnt,int nType, int nPriority = 5);
	~CFG();

	static CFG *Create(int nCnt, int nType);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetIdx(void) { return m_nIdxTexture; }

private:
	int m_nIdxTexture;					//テクスチャの番号
	int m_nLife;						//この前景が存在する時間
	int m_nType;						//前景の種類
	int m_ColorCount;					//前景の色切り替え時間
	bool m_bColorSet;					//前景の色切り替えフラグ
};
#endif