//============================================
//
//	�^�C�g����� [title.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "manager.h"

//�}�N����`
#define MAX_SELECT (3)
#define MAX_TITLEUI (3)

//�O���錾
class CObject2D;
class CPlayer3D;
class CBreak_Block3D;
class CBlockUI;
class CTitleUI;
class CFallEffect;
class CObjmeshDome;
class CPlayer;
class CCubeBlock;
class CBoss;

//�V�[���N���X
class CTitle : public CScene
{
public:
	CTitle();
	~CTitle();

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	static void SetSelectColor(int SelectCnt);

private:
	void Select(void);

	static int m_nSelect;
	static int m_CreateCount;
	static D3DXVECTOR2 m_Scroll;
	static D3DXVECTOR2 m_Tex;
	static D3DXCOLOR m_Color;
	static CObject2D *m_pTitle;
	static CObject2D *m_pTitleLogo[4];
	static CObject2D* m_pTitleButton;
	static CObjmeshDome* m_pMeshDome;		//���b�V���h�[��
	static CPlayer* m_pPlayer;				//�v���C���[�̃|�C���^
	static CCubeBlock* m_pCubeBlock;		//�L���[�u�u���b�N
	static CBoss* m_pBoss;					//�{�X

};
#endif