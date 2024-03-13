//============================================
//
//	コンボ処理 [combo.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _COMBO_H_
#define _COMBO_H_

#include "main.h"
#include "player3D.h"

//前方宣言
class CDebugNumber3D;
class CComboUI;

//レベルアップクラス
class CCombo
{
public:
	CCombo();
	~CCombo();

	static CCombo *Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetCombo(int Combo) { m_nComboNumber = Combo; }
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 SetPos(void) { return m_pos; }
	void SetNULL(void);
private:
	D3DXVECTOR3 m_pos;				//位置
	int m_nComboNumber;				//コンボ数
	CDebugNumber3D *m_pNumber1;		//コンボ数UI
	CDebugNumber3D *m_pNumber10;	//コンボ数UI
	CComboUI *m_pComboUI;			//コンボ用UI
};
#endif