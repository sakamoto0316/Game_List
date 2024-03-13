//============================================
//
//	ランキングの処理 [ranking.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"
#include "object.h"

//マクロ定義
#define MAX_RANK (5)		//ランキングの数
#define NUM_TIME (8)		//ランキングの桁数

//前方宣言
class CObject;
class CNumber;

//多重背景クラス
class CRanking : public CObject
{
public:
	CRanking();
	~CRanking();

	static CRanking *Create();
	static void SetTime(int Time, int nCnt) { m_nTime[nCnt] = Time; }
	static void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	static void AddTime(int Time) { m_nTime[0] += Time; }
	void FloatSetTime(int Time);
	void SetStartTime(int Time) { m_StartTime = Time; }
	void SetStopTime(bool Stop) { m_StopTime = Stop; }
	void SetRanking(int nRanKing);
	static void ChangeRanking(bool Set) { m_SetRanking = Set; };
	static void SaveRanking(void);
	static void LoadRanking(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetNULL(void);

private:
	static CNumber *m_apObject[NUM_TIME][MAX_RANK];
	static D3DXVECTOR3 m_pos;
	static int m_nCount;
	static int m_StartTime;
	static int m_nTime[MAX_RANK];
	static int m_nNumber[NUM_TIME][MAX_RANK];
	static bool m_StopTime;
	static bool m_SetRanking;
};

#endif