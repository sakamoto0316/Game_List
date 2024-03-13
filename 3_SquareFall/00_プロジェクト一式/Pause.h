//============================================
//
//	ポーズ処理 [Pause.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"
#include "player3D.h"

//マクロ定義
#define MAX_PAUSE (4)

//前方宣言
class CObject2D;

//レベルアップクラス
class CPause
{
public:
	CPause();
	~CPause();

	static CPause *Create();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetAppear(bool Set) { m_Appear = Set; m_PauseSelect = 0; }
	bool SetAppear(void) { return m_Appear; }

private:

	int m_PauseSelect;
	bool m_Appear;
	static CObject2D *m_pPauseUI[MAX_PAUSE];
	static CObject2D *m_pPauseFG;
};
#endif