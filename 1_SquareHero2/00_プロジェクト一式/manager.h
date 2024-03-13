//============================================
//
//	�}�l�[�W�� [manager.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
#include "object.h"

//�O���錾
class CRenderer;
class CDebugProc;
class CInputKeyboard;
class CInputJoypad;
class CInputMouse;
class CCamera;
class CLight;
class CTexture;
class CXModel;
class CLevelUP;
class CFade;
class CSound;
class CTime;
class CRanking;

//�V�[���N���X
class CScene
{
public:
	CScene();
	~CScene();

	enum MODE
	{
		MODE_TITLE = 0,
		MODE_GAME,
		MODE_RESULT
	};

	static CScene *Create(MODE mode);
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static void SetMode(MODE mode);
	static MODE GetMode(void) { return m_mode; }

private:
	static MODE m_mode;
};

//�}�l�[�W���N���X
class CManager
{
public:
	CManager();
	~CManager();

	static CManager *GetInstance();
	static HRESULT Release(void);

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow); 	//�Ԃ�l��HRESULT�Ȃ̂͒��_�o�b�t�@�̐����ȂǂɎ��s�����Ƃ��m�F�̂���
	void Uninit(void);
	void Update(void);
	void Draw(void);

	CRenderer *GetRenderer(void) { return m_pRenderer; }
	CDebugProc *GetDebugProc(void) { return m_pDebugProc; }
	CInputKeyboard *GetInputKeyboard(void) { return m_pInputKeyboard; }
	CInputJoypad* GetInputJoyPad(void) { return m_pInputJoyPad; }
	CInputMouse*GetInputMouse(void) { return m_pInputMouse; }
	CCamera *GetCamera(void) { return m_pCamera; }
	CTexture *GetTexture(void) { return m_pTexture; }
	CXModel *GetXModel(void) { return m_pXModel; }
	CScene *GetScene(void) { return m_pScene; }
	CFade *GetFade(void) { return m_Fade; }
	CSound *GetSound(void) { return m_pSound; }
	CRanking* GetRanking(void) { return m_pRanking; }
	void SetScene(CScene *Scene) { m_pScene = Scene; }
	void SetLevelUP(CLevelUP *LevelUP) { m_LevelUP = LevelUP; }
	void SetEdit(bool bEdit) { m_bEdit = bEdit; }
	bool GetEdit(void) { return m_bEdit; }
	void SetStop(bool Set) { m_bStop = Set; }
	bool GetStop(void) { return m_bStop; }
	void SetPause(bool Set) { m_Pause = Set; }
	bool GetPause(void) { return m_Pause; }
	void SetEndScore(int Set) { m_EndScore = Set; }
	int GetEndScore(void) { return m_EndScore; }
	void SetEndTime(int Set) { m_EndTime = Set; }
	int GetEndTime(void) { return m_EndTime; }
	void SetTutorialStart(bool Set) { m_SetTutorial = Set; }
	bool GetTutorialStart(void) { return m_SetTutorial; }
	void SetScoreResult(bool Set) { m_SetScoreResult = Set; }
	bool GetScoreResult(void) { return m_SetScoreResult; }
	void SetSetTutorialPad(bool Set) { m_SetJoyPad = Set; }
	bool GetSetTutorialPad(void) { return m_SetJoyPad; }
	void SetPauseOK(bool Set) { m_PauseOK = Set; }
	bool GetPauseOK(void) { return m_PauseOK; }
	void SetUseJoyPad(bool Set) { m_bPad = Set; }
	bool GetUseJoyPad(void) { return m_bPad; }
	void SetGameClear(bool Set) { m_bGameClear = Set; }
	bool GetGameClear(void) { return m_bGameClear; }

private:
	static CManager *pManager;

	int m_EndScore;						//�ŏI�I�ȃX�R�A
	int m_EndTime;						//�ŏI�I�ȃ^�C��
	bool m_bGameClear;					//�Q�[���N���A��Ԃ�
	bool m_SetTutorial;					//�G�f�B�b�g���[�h���ǂ���
	bool m_bEdit;						//�G�f�B�b�g���[�h���ǂ���
	bool m_bStop;						//��ʒ�~��Ԃ��ǂ���
	bool m_Pause;						//�|�[�Y��Ԃ��ǂ���
	bool m_SetScoreResult;				//���U���g�ɃX�R�A�������邩�ǂ���
	bool m_SetJoyPad;					//�W���C�p�b�h�ő��삵�Ă��邩�ǂ���
	bool m_PauseOK;						//�|�[�Y�������Ă����v��
	bool m_bPad;						//�W���C�p�b�h���g�p���Ă��邩�ǂ���
	CRenderer *m_pRenderer;				//�����_���[�̃|�C���^
	CDebugProc *m_pDebugProc;			//�f�o�b�O�v���b�N�̃|�C���^
	CInputKeyboard *m_pInputKeyboard;	//�L�[�{�[�h�̃|�C���^
	CInputJoypad* m_pInputJoyPad;		//�W���C�p�b�h�̃|�C���^
	CInputMouse*m_pInputMouse;			//�}�E�X�̃|�C���^
	CCamera *m_pCamera;					//�J�����̃|�C���^
	CLight *m_pLight;					//���C�g�̃|�C���^
	CTexture *m_pTexture;				//�e�N�X�`���̃|�C���^
	CXModel *m_pXModel;					//X���f���̃|�C���^
	CScene *m_pScene;					//�V�[���̃|�C���^
	CLevelUP *m_LevelUP;				//���x���A�b�v�̃|�C���^
	CFade *m_Fade;						//�t�F�[�h�̃|�C���^
	CSound *m_pSound;					//�T�E���h�̃|�C���^
	CRanking* m_pRanking;
};												

#endif