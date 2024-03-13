//============================================
//
//	�|�[�Y���� [Pause.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"

//�}�N����`
#define MAX_PAUSE (3)

//�O���錾
class CObject2D;

//���x���A�b�v�N���X
class CPause
{
public:
	CPause();
	~CPause();

	static CPause *Create();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetAppear(bool Set) { m_Appear = Set; m_PauseSelect = 0; }
	bool SetAppear(void) { return m_Appear; }

private:

	int m_PauseSelect;
	bool m_Appear;
	static CObject2D *m_pPauseUI[MAX_PAUSE];
	static CObject2D *m_pPauseFG[2];
	static D3DXVECTOR3 m_MovePos;
	static D3DXVECTOR3 m_JumpPos;
	static D3DXVECTOR3 m_AttackPos;
};
#endif