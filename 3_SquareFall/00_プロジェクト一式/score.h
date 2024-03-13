//============================================
//
//	スコアの処理 [score.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"
#include "object.h"

//マクロ定義
#define NUM_SCORE (8)		//スコアの桁数

//前方宣言
class CObject;
class CNumber;

//多重背景クラス
class CScore : public CObject
{
public:
	CScore();
	~CScore();

	static CScore *Create();
	void SetScore(int Score);
	void AddScore(int Add);

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	int GetScore(void) { return m_nScore; }

	void SetWight(float Wight) { m_nWight = Wight; }
	void SetHeight(float Height) { m_Height = Height; }

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetNULL(void);

private:
	CNumber *m_apObject[NUM_SCORE];
	D3DXVECTOR3 m_pos;
	int m_nScore;
	int m_nNumber[NUM_SCORE];
	float m_nWight;
	float m_Height;
};

#endif