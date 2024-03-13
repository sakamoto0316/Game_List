//============================================
//
// �}�l�[�W���[�̃w�b�_�[[manager.h]
// Author�F��������
//
//============================================
#ifndef _MANAGER_H_			//���̃}�N����`������Ă��Ȃ�������
#define _MANAGER_H_			//2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "main.h"
#include "scene.h"
#include "camera.h"

#define CAMERA 1

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CRenderer;		// �����_���[
class CInputKeyboard;	// �L�[�{�[�h����
class CInputGamePad;	// �Q�[���p�b�h
class CSound;			// �T�E���h
class CFile;			// �t�@�C��
class CDebugProc;		// �f�o�b�O�\��
class CCamera;			// �J����
class CMultiCamera;		// �J����
class CLight;			// ���C�g
class CTexture;			// �e�N�X�`��
class CFade;			// �t�F�[�h

//--------------------------------------------
// �N���X(�}�l�[�W���[�N���X)
//--------------------------------------------
class CManager
{
public:						// �N�ł��A�N�Z�X�ł���

	// �����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);		// ����������
	void Uninit(void);							// �I������
	void Update(void);							// �X�V����
	void Draw(void);							// �`�揈��

	HRESULT TexLoad(void);						// �e�N�X�`���̓ǂݍ��ݏ���
	void TexUnload(void);						// �e�N�X�`���̔j������

	// �Z�b�g�E�Q�b�g�֌W
	CRenderer* GetRenderer(void);			// �����_���[�̎擾����
	CInputKeyboard* GetInputKeyboard(void);	// �L�[�{�[�h�̎擾����
	CInputGamePad* GetInputGamePad(void);	// �Q�[���p�b�h�̎擾����
	CSound* GetSound(void);					// �T�E���h�̎擾����
	CFile* GetFile(void);					// �t�@�C���̎擾����
	CDebugProc* GetDebugProc(void);			// �f�o�b�O�\���̎擾����
	CCamera* GetCamera(void);				// �J�����\���̎擾����
	CMultiCamera* GetMlutiCamera(int Idx);	// �J�����\���̎擾����
	CLight* GetLight(void);					// ���C�g�̎擾����
	CTexture* GetTexture(void);				// �e�N�X�`���̎擾����
	CFade* GetFade(void);					// �t�F�[�h�̎擾����
	void SetMode(const CScene::MODE mode);	// ���[�h�̐ݒ菈��
	CScene::MODE GetMode(void);				// ���[�h�̎擾����

	void SetMlutiCamera(CMultiCamera *Camera, int Idx) { m_pMultiCamera[Idx] = Camera; }	// �J�����\���̎擾����

	// �ÓI�����o�֐�
	static CManager* Create(void);			// �}�l�[�W���[�̐�������
	static CManager* Get(void);				// �}�l�[�W���[�̎擾����

private:					// ���������A�N�Z�X�ł���

	CManager();				// �R���X�g���N�^
	~CManager();			// �f�X�g���N�^

	// �����o�ϐ�
	CRenderer* m_pRenderer;					// �����_���[�̏��
	CInputKeyboard* m_pInputKeyboard;		// �L�[�{�[�h�̏��
	CInputGamePad* m_pInputGamePad;			// �Q�[���p�b�h�̏��
	CSound* m_pSound;						// �T�E���h�̏��
	CFile* m_pFile;							// �t�@�C���̏��
	CDebugProc* m_pDebugProc;				// �f�o�b�O�\���̏��
	CCamera* m_pCamera;						// �J�����̏��
	CMultiCamera* m_pMultiCamera[4];		// �J�����̏��
	CLight* m_pLight;						// ���C�g�̏��
	CTexture* m_pTexture;					// �e�N�X�`���̏��
	CScene* m_pScene;						// �V�[���̏��
	CFade* m_pFade;							// �t�F�[�h�̏��
	CScene::MODE m_ModeNow;					// ���݂̃��[�h���

#ifdef _DEBUG		// �f�o�b�O���̂�

	bool m_bWire;						// ���C���[�t���[����

#endif

	// �ÓI�����o�ϐ�
	static CManager* m_pManager;			// �}�l�[�W���[�̏��
};

#endif