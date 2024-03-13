//============================================
//
//	�Q�[����� [game.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "manager.h"

//�O���錾
class CTutorialUI;
class CPlayer;
class CMap2D;
class CEdit;
class CTutorialUI;
class CObject2D;
class CObject3D;
class CObjectBillboard;
class CObjectX;
class CObjmeshField;
class CObjmeshWall;
class CObjmeshCylinder;
class CObjmeshDome;
class CCubeBlock;
class CPause;
class CScore;
class CTime;
class CBoss;

//�V�[���N���X
class CGame : public CScene
{
public:
	CGame();
	~CGame();

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	void ReSetGame(void);
	static CPlayer* GetPlayer(void) { return m_pPlayer; }
	static CBoss*GetBoss(void) { return m_pBoss; }
	static CPause *GetPause(void) { return m_pPause; }
	static CScore *GetScore(void) { return m_pScore; }
	static CEdit *GetEdit(void) { return m_pEdit; }
	static CTime* GetTime(void) { return m_pTime; }
	static CObjmeshDome* GetDomeUp(void) { return m_pMeshDomeUp; }
	static CObjmeshDome* GetDomeDown(void) { return m_pMeshDomeDown; }
	static void SetCubeBlock(CCubeBlock *pBlock) { m_pCubeBlock = pBlock; }
	static CCubeBlock*GetCubeBlock(void) { return m_pCubeBlock; }
	static void DeleteTutorial(void);
	static void EventStart(void);
	static void SetEvent(bool Set) { m_bEvent = Set; }
	static bool GetEvent(void) { return m_bEvent; }
	static bool GetEventEnd(void) { return m_bEventEnd; }
	static D3DXVECTOR3 GetEventPos(void) { return m_EventPos; }
	static float GetBGColorA(void) { return m_BGColorA; }
	static void AddBGColorA(float Add) { m_BGColorA += Add; }
	static void SetStageBlock(void);
	static void SetGameEnd(bool Set) { m_bGameEnd = Set; }
	static void DispUI(bool Set);
private:
	static void DeleteMap(void);
	static void EventUpdate();				//�C�x���g�̍X�V
	static void LoadStageBlock(void);
	bool EnemyCheck(void);					//�G�����邩�ǂ����̔��f

	static int m_nEnemyNum;					//���݂̓G�̐�
	static bool m_bGameEnd;					//�Q�[���I����Ԃ��ǂ���
	static bool m_bEvent;					//�C�x���g��Ԃ��ǂ���
	static bool m_bEventEnd;				//�C�x���g���I��������ǂ���
	static int m_nEventCount;				//�C�x���g����
	static int m_nTutorialWave;				//�`���[�g���A���̒i�K
	static float m_EventHeight;				//�C�x���g�p�|���S���̍���
	static float m_NameColorA;				//�C�x���g�p�̖��O�\���̕s�����x
	static float m_BGColorA;				//�Q�[���w�i�̕s�����x
	static D3DXVECTOR3 m_EventPos;			//�C�x���g�J�n���W
	static D3DXVECTOR3 m_BGRot;				//�w�i�̉�]����
	static CTutorialUI *m_pTutorialUI;		//�`���[�g���A��UI�̃|�C���^
	static CPlayer *m_pPlayer;				//�v���C���[�̃|�C���^
	static CEdit *m_pEdit;					//�G�f�B�b�g���[�h�̃|�C���^
	static CPause *m_pPause;				//�|�[�Y�̃|�C���^
	static CScore *m_pScore;				//�X�R�A�̃|�C���^
	static CTime *m_pTime;
	static CObject2D* m_p2DSample;			//2D�|���S���̃T���v��
	static CObject2D* m_pEventBG[2];		//�C�x���g���̔w�i�\��
	static CObject2D* m_p2DUI_Attack;		//�U����2DUI
	static CObject2D* m_p2DUI_Jump;			//�W�����v��2DUI
	static CObject2D* m_p2DUI_Dodge;		//�����2DUI
	static CObject2D* m_p2DUI_Attention;	//���ڂ�2DUI
	static CObject2D *m_p2DUI_AttentionOK;	//���ڂ�2DUI
	static CObject3D* m_p3DSample;			//3D�|���S���̃T���v��
	static CObject3D* m_p3DEventBG;			//�C�x���g���̔w�i
	static CObject2D *m_p2DBossName;		//�{�X�̖��O�\��
	static CObjectBillboard* m_pBillboardSample; //Billboard�|���S���̃T���v��
	static CObjectX* m_pXModelSample;		//X���f���̃T���v��
	static CObjmeshField* m_pMeshFieldSample;//���b�V���t�B�[���h�̃T���v��
	static CObjmeshWall* m_pMeshWallSample;	//���b�V���E�H�[���̃T���v��
	static CObjmeshCylinder* m_pMeshCylinderSample;//���b�V���V�����_�[�̃T���v��
	static CObjmeshDome* m_pMeshDomeUp;		//���b�V���h�[��
	static CObjmeshDome* m_pMeshDomeDown;	//���b�V���h�[��
	static CCubeBlock* m_pCubeBlock;		//�L���[�u�u���b�N
	static CBoss* m_pBoss;					//�{�X
};
#endif