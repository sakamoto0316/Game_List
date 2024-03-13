//============================================
//
//	ゲーム画面 [game.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "manager.h"

//前方宣言
class CPlayer3D;
class CMap2D;
class CPlayerLevel;
class CBossLevel;
class CBreak_Block3D;
class CEdit;
class CTutorialUI;
class CObject2D;
class CPause;
class CScore;

//シーンクラス
class CGame : public CScene
{
public:
	CGame();
	~CGame();

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	void ReSetGame(void);
	void UpdateTutorial(void);
	void SkipTutorial(void);
	void GameStartEvent(void);
	static CPlayer3D *GetPlayer3D(void) { return m_pPlayer3D; }
	static CMap2D *GetMap2D(void) { return m_pMap2D; }
	static CBossLevel *GetBossLevel(void) { return m_pBossLevel; }
	static CPause *GetPause(void) { return m_pPause; }
	static CScore *GetScore(void) { return m_pScore; }
	static void SetGameEnd(int Time) { m_bGameEnd = true; m_bGameEndTime = Time; }
	static bool GetTutorial(void) { return m_bTutorial; }
	static void SetGSEvent(bool Set) { m_bGSEvent = Set; }
	static bool GetGSEvent(void) { return m_bGSEvent; }
	static void SetGSEventCamera(bool Set) { m_bGSEventCamera = Set; }
	static bool GetGSEventCamera(void) { return m_bGSEventCamera; }
	static void SetEvent(bool Set) { m_bEvent = Set; }
	static bool GetEvent(void) { return m_bEvent; }
	static void SetEventStart(bool Set) { m_bEventStart = Set; }
	static bool GetEventStart(void) { return m_bEventStart; }
	static void DeleteTutorial(void);
	static void SetTutorial(void);
	static void SetTutorialUnderText(char *cName);
	static void SetTutorialStart(bool Set) { m_bTutorial = Set; }

private:
	int m_GSEventCount;						//ゲームスタートイベントの長さ
	static bool m_bGSEvent;					//ゲームスタートイベント中かどうか
	static bool m_bGSEventCamera;			//ゲームスタートイベントが発生したかどうか
	bool m_bGSEventEnd;						//ゲームスタートイベントが発生したかどうか
	static bool m_bEvent;					//イベント中かどうか
	static bool m_bEventStart;				//イベントの部屋かどうか
	static bool m_bGameEnd;					//ゲーム終了状態かどうか
	static bool m_bTutorial;				//チュートリアル状態かどうか
	static int m_nTutorialCount;			//何個目のチュートリアルかのカウント
	static bool m_bUseTutorialUI;			//チュートリアルUIを使っているか
	static int m_bGameEndTime;				//ゲーム終了からフェード開始までの時間
	static CPlayer3D *m_pPlayer3D;			//プレイヤーのポインタ
	static CMap2D *m_pMap2D;				//マップ生成のポインタ
	static CPlayerLevel *m_pPlayerLevel;	//プレイヤーのレベルのポインタ
	static CBossLevel *m_pBossLevel;		//階層構造のボスのポインタ
	static CBreak_Block3D *m_pBlock3D;		//ブロックのポインタ
	static CEdit *m_pEdit;					//エディットモードのポインタ
	static CTutorialUI *m_pTutorialUI;		//チュートリアル画面下のUIのポインタ
	static CObject2D *m_pTutorialBG;		//チュートリアル画面下の背景のポインタ
	static CObject2D *m_pTutorialText;		//チュートリアル画面下のテキストのポインタ
	static CPause *m_pPause;				//ポーズのポインタ
	static CObject2D* m_pScoreText;			//スコア用のテキスト
	static CObject2D* m_pEventText;			//イベント用のテキスト
	static CObject2D *m_pEventTextBG;		//イベント用のテキストの背景
	static CScore *m_pScore;				//スコアのポインタ
	static bool m_bTextColor;				//テキストが濃くなっているか薄くなっているか
	static float m_fTextColor;				//テキストの不透明度
	static float m_fEventTextColor;			//イベントテキストの不透明度
};
#endif