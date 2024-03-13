//============================================
//
//	リザルト画面 [result.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "manager.h"

//前方宣言
class CObject2D;
class CRanking;
class CScore;
class CBreak_Block3D;

//シーンクラス
class CResult : public CScene
{
public:
	CResult();
	~CResult();

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static void SetApprear(bool Set) { m_Appear = Set; }
	static bool GetApprear(void) { return m_Appear; }

private:
	void LoadBlock(char *Name, D3DXVECTOR3 pos);

	CBreak_Block3D *m_pBreakBlock3D;
	static CObject2D *m_pResult;
	static CRanking *m_pRanking;
	static CScore *m_NormalScore;
	static CScore *m_MaxConbo;
	static CScore *m_MaxFall;
	static CScore *m_Depth;
	static CScore *m_TotalScore;
	static CObject2D *m_NormalScoreText;
	static CObject2D *m_MaxConboText;
	static CObject2D *m_MaxFallText;
	static CObject2D *m_DepthText;
	static CObject2D *m_TotalScoreText;
	static CObject2D *m_RankText;
	static CObject2D *m_ResultText;
	static CObject2D *m_RankingText;
	static float m_NormalScorePosX;
	static float m_MaxConboPosX;
	static float m_MaxFallPosX;
	static float m_DepthPosX;
	static float m_TotalScorePosX;
	static float m_ResultPosX;
	static float RankingPosX;
	static bool m_Appear;
	static int m_AddScoreCount;
	static int m_AddTotalScore;
};
#endif