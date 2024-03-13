//============================================
//
//	レベルアップ処理 [LevelUP.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _LEVELUP_H_
#define _LEVELUP_H_

#include "main.h"
#include "player3D.h"

//前方宣言
class CLevelUPUI;

//レベルアップクラス
class CLevelUP
{
public:
	CLevelUP(int nLevelUP, CPlayer3D::SHOT_TYPE type);
	~CLevelUP();

	static CLevelUP *Create(int nLevelUP, CPlayer3D::SHOT_TYPE type);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetNULL(void);
	void SetLevelUP(bool Set) { m_bLevelUp = Set; }
	bool GetLevelUp(void) { return m_bLevelUp; }
private:
	void BulletChange(void);

	bool m_bLevelUp;
	static CLevelUPUI *m_pLevelUPText;			//レベルアップメッセージ
	static CLevelUPUI *m_pLevelUPTutorial;		//レベルアップの説明
	static CLevelUPUI *m_pLevelUPBG;			//レベルアップの背景
	static CLevelUPUI *m_pLevelUPUI[3];			//レベルアップ用UI
	static CLevelUPUI *m_pLevelUPCursor;		//レベルアップ用のカーソル
	static int m_nCursorNumber;					//カーソルの位置番号
	static CPlayer3D::SHOT_TYPE m_BulletType;	//プレイヤーの弾の種類
	int LevelUpCount;							//レベルアップ回数のカウント
	int LevelUpMax;								//レベルアップ選択の最大数
};
#endif