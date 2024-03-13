//============================================
//
//	エディット [Edit.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _EDIT_H_
#define _EDIT_H_

#include "main.h"
#include "object.h"

#define SET_BLOCK_WIGHT (20)
#define SET_BLOCK_HEIGHT (25)

//前方宣言
class CEdit_Block3D;

//マップクラス
class CEdit
{
public:
	CEdit();
	~CEdit();

	static CEdit *Create();
	void Uninit(void);
	void Update(void);

protected:

private:
	void SaveData(void);

	static CEdit_Block3D *m_pEditBlock;
	int m_WightNumber;		//横の番号
	int m_HeightNumber;		//縦の番号
};
#endif