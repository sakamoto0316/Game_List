//============================================
//
//	プレイヤーの処理 [playerlevel.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _PLAYERLEVEL_H_
#define _PLAYERLEVEL_H_

#include "object.h"

//前方宣言
class CModel;
class CMotion;

//オブジェクトプレイヤークラス
class CPlayerLevel : public CObject
{
public:
	CPlayerLevel();
	~CPlayerLevel();

	//プレイヤーのモーション
	typedef enum
	{
		ACTION_WAIT1 = 0,
		ACTION_WAIT2,
		ACTION_WAIT3,
		ACTION_WAIT4,
		ACTION_RUNPOZE,
		ACTION_MAX,

	}ACTION_TYPE;

	D3DMATRIX GetMtxWorld(void) { return m_mtxWorld; }
	static CPlayerLevel *Create();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void LoadLevelData(const char *pFilename);
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }

private:
	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_rot;		//向き
	D3DXMATRIX m_mtxWorld;	//ワールドマトリックス

	CModel *m_apModel[64];
	CMotion *m_pMotion;
	char *m_aModelName[64];
	int m_nNumModel;
};

#endif