//============================================
//
//	コンボUIの処理 [comboUI.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _COMBOUI_H_
#define _COMBOUI_H_

#include "main.h"
#include "objectBillboard.h"

//レベルアップUIクラス
class CComboUI : public CObjectBillboard
{
public:

	CComboUI(int nPriority = 5);
	~CComboUI();

	static CComboUI *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetIdx(int Idx) { m_nIdxTexture = Idx; }
	int GetIdx(void) { return m_nIdxTexture; }

private:
	int m_nIdxTexture;						//テクスチャの番号
};
#endif