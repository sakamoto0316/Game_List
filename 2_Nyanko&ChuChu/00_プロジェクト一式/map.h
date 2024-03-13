#ifndef _MAP_H_	//このマクロが定義されていなければ
#define _MAP_H_	//二重インクルード防止マクロ

#include "main.h"
#include "ground.h"
#include "wall.h"
#include "ceil.h"

#define WALL_NUM (12)

class CMap :public CObject
{
public:
	CMap();
	~CMap();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CMap* Create(void);

	static CWall* GetWall(void);
private:

	D3DXVECTOR3 m_pos;
	int m_partsNum;

	CGround* m_Ground;
	CCeil* m_pCeil;
	static CWall* m_Wall[WALL_NUM];
};
#endif // !_MAP_H_