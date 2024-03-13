//============================================
//
//	チュートリアル時のUI設定 [TutorialUI.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"
#include "manager.h"

//前方宣言
class CObject2D;

//シーンクラス
class CTutorialUI
{
public:
	CTutorialUI(int TutorialNumber);
	~CTutorialUI();

	static CTutorialUI *Create(int TutorialNumber);

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	void DeleteUI(void);
	void DeleteTutorial(void);
	virtual void Update(void);
	virtual void Draw(void);

	CObject2D *GetPlayerBG(void) { return m_pPlayerBG; }

private:
	bool m_bColor;
	float m_SetColor;
	float m_SetColorHlaf;
	int m_TurorialNumber;
	int m_PushNumber;
	CObject2D *m_pScreenBG;
	CObject2D *m_pPlayerBG;
	CObject2D *m_pChatBG;
	CObject2D *m_pChat;
	CObject2D *m_pTurorialText;
	CObject2D *m_pArrorw;
};
#endif