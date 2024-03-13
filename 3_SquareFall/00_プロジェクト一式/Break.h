//============================================
//
//	破壊されたブロックを生成する処理 [Break.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _BREAK_H_
#define _BREAK_H_

#include "main.h"
#include "object.h"

//前方宣言
class CObjectXtex;

//オブジェクトプレイヤークラス
class CBreak : public CObject
{
public:

	CBreak(D3DXVECTOR3 pos, int nPriority = 3);
	~CBreak();

	static CBreak *Create(D3DXVECTOR3 pos);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

	D3DXVECTOR3 m_pos;

};
#endif