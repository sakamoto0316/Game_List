//============================================
//
//	�}�l�[�W�� [manager.cpp]
//	Author:sakamoto kai
//
//============================================
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "input.h"
#include "camera.h"
#include "light.h"
#include "objectX.h"
#include "texture.h"
#include "XModel.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "Pause.h"
#include "sound.h"
#include "Edit.h"
#include "time.h"

#define SET_MODE (CScene::MODE_TITLE)

//�ÓI�����o�ϐ��錾
CManager *CManager::pManager = nullptr;
CScene::MODE CScene::m_mode = SET_MODE;

//====================================================================
//�R���X�g���N�^
//====================================================================
CManager::CManager()
{
	//�ÓI�����o�ϐ��錾
	m_bEdit = false;
	m_bStop = false;
	m_SetTutorial = false;
	m_Pause = false;
	m_SetScoreResult = false;
	m_SetJoyPad = false;
	m_PauseOK = false;
	m_bPad = false;
	m_EndScore = 157;
	m_bGameClear = false;

	pManager = nullptr;
	m_pRenderer = nullptr;
	m_pDebugProc = nullptr;
	m_pInputKeyboard = nullptr;
	m_pInputJoyPad = nullptr;
	m_pInputMouse = nullptr;
	m_pCamera = nullptr;
	m_pLight = nullptr;
	m_pTexture = nullptr;
	m_pXModel = nullptr;
	m_pScene = nullptr;
	m_LevelUP = nullptr;
	m_Fade = nullptr;
	m_pSound = nullptr;
	m_pRanking = nullptr;
}

//====================================================================
//�f�X�g���N�^
//====================================================================
CManager::~CManager()
{

}

//====================================================================
//����������
//====================================================================
CManager *CManager::GetInstance(void)
{
	if (pManager == nullptr)
	{
		pManager = new CManager;
	}
	return pManager;
}

//====================================================================
//����������
//====================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	if (m_pRenderer == nullptr)
	{
		//�����_���[�̐���
		m_pRenderer = new CRenderer;
	}

	//�����_���[�̏���������
	if (FAILED(m_pRenderer->Init(hInstance, hWnd, TRUE)))
	{//���������������s�����ꍇ
		return E_FAIL;
	}

	if (m_pDebugProc == nullptr)
	{
		//�f�o�b�O�\���̐���
		m_pDebugProc = new CDebugProc;

		if (m_pDebugProc != nullptr)
		{
			m_pDebugProc->Init();
		}
	}

	if (m_pSound == nullptr)
	{
		//�T�E���h�̐���
		m_pSound = new CSound;
	}

	//�T�E���h�̏���������
	if (FAILED(m_pSound->InitSound(hWnd)))
	{//���������������s�����ꍇ
		return E_FAIL;
	}

	if (m_pInputKeyboard == nullptr)
	{
		//�L�[�{�[�h�̐���
		m_pInputKeyboard = new CInputKeyboard;
	}
	//�L�[�{�[�h�̏���������
	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{//���������������s�����ꍇ
		return E_FAIL;
	}

	if (m_pInputJoyPad == nullptr)
	{
		//�W���C�p�b�h�̐���
		m_pInputJoyPad = new CInputJoypad;
	}
	//�W���C�p�b�h�̏���������
	if (FAILED(m_pInputJoyPad->Init(hInstance, hWnd)))
	{//���������������s�����ꍇ
		return E_FAIL;
	}

	if (m_pInputMouse == nullptr)
	{
		//�}�E�X�̐���
		m_pInputMouse = new CInputMouse;
	}
	//�L�[�{�[�h�̏���������
	if (FAILED(m_pInputMouse->Init(hInstance, hWnd)))
	{//���������������s�����ꍇ
		return E_FAIL;
	}

	if (m_pCamera == nullptr)
	{
		//�J�����̐���
		m_pCamera = new CCamera;
	}

	//�J�����̏���������
	if (FAILED(m_pCamera->Init()))
	{//���������������s�����ꍇ
		return E_FAIL;
	}

	if (m_pLight == nullptr)
	{
		//���C�g�̐���
		m_pLight = new CLight;
	}

	//���C�g�̏���������
	if (FAILED(m_pLight->Init()))
	{//���������������s�����ꍇ
		return E_FAIL;
	}

	if (m_pTexture == nullptr)
	{
		//�e�N�X�`���̐���
		m_pTexture = new CTexture;
	}

	//�S�Ẵe�N�X�`���̓ǂݍ���
	if (FAILED(m_pTexture->Load()))
	{//�ǂݍ��݂����s�����ꍇ
		return E_FAIL;
	}

	if (m_pXModel == nullptr)
	{
		//X���f���̐���
		m_pXModel = new CXModel;
	}

	//�S�Ă�X���f���̓ǂݍ���
	if (FAILED(m_pXModel->Load()))
	{//�ǂݍ��݂����s�����ꍇ
		return E_FAIL;
	}

	//�V�[���̐���
	if (m_pScene == nullptr)
	{
		m_pScene = CScene::Create(SET_MODE);
	}

	if (m_Fade == nullptr)
	{
		//�t�F�[�h�̐���
		m_Fade = new CFade;

		if (m_Fade != nullptr)
		{
			m_Fade->Init(SET_MODE);
		}
	}

	m_PauseOK = true;

	return S_OK;
}

//====================================================================
//�I������
//====================================================================
void CManager::Uninit(void)
{
	//BGM�̒�~
	m_pSound->StopSound();

	//�S�ẴI�u�W�F�N�g�̔j��
	CObject::ReleaseAll();

	if (m_Fade != nullptr)
	{
		//�t�F�[�h�̏I������
		m_Fade->Uninit();

		delete m_Fade;
		m_Fade = nullptr;
	}

	if (m_pScene != nullptr)
	{
		//�V�[���̏I������
		m_pScene->Uninit();

		delete m_pScene;
		m_pScene = nullptr;
	}

	if (m_pTexture != nullptr)
	{
		//�e�N�X�`���̏I������
		m_pTexture->Unload();

		delete m_pTexture;
		m_pTexture = nullptr;
	}

	if (m_pXModel != nullptr)
	{
		//X���f���̏I������
		m_pXModel->Unload();

		delete m_pXModel;
		m_pXModel = nullptr;
	}

	if (m_pLight != nullptr)
	{
		//���C�g�̏I������
		m_pLight->Uninit();

		delete m_pLight;
		m_pLight = nullptr;
	}

	if (m_pCamera != nullptr)
	{
		//�J�����̏I������
		m_pCamera->Uninit();

		delete m_pCamera;
		m_pCamera = nullptr;
	}

	if (m_pInputMouse != nullptr)
	{
		//�W���C�p�b�h�̏I������
		m_pInputMouse->Uninit();

		delete m_pInputMouse;
		m_pInputMouse = nullptr;
	}

	if (m_pInputJoyPad != nullptr)
	{
		//�W���C�p�b�h�̏I������
		m_pInputJoyPad->Uninit();

		delete m_pInputJoyPad;
		m_pInputJoyPad = nullptr;
	}

	if (m_pInputKeyboard != nullptr)
	{
		//�L�[�{�[�h�̏I������
		m_pInputKeyboard->Uninit();

		delete m_pInputKeyboard;
		m_pInputKeyboard = nullptr;
	}

	if (m_pDebugProc != nullptr)
	{
		//�f�o�b�O�\���̏I������
		m_pDebugProc->Uninit();

		delete m_pDebugProc;
		m_pDebugProc = nullptr;
	}

	if (m_pRenderer != nullptr)
	{
		//�����_���[�̏I������
		m_pRenderer->Uninit();

		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	if (m_pSound != nullptr)
	{
		//�T�E���h�̏I������
		m_pSound->UninitSound();

		delete m_pSound;
		m_pSound = nullptr;
	}
}

//====================================================================
//�X�V����
//====================================================================
void CManager::Update(void)
{
	//�J�����̍X�V����
	m_pCamera->Update();

	//���C�g�̍X�V����
	m_pLight->Update();

	//�L�[�{�[�h�̍X�V����
	m_pInputKeyboard->Update();

	//�W���C�p�b�h�̍X�V����
	m_pInputJoyPad->Update();

	//�}�E�X�̍X�V����
	m_pInputMouse->Update();

	//�f�o�b�O�\���̍X�V����
	m_pDebugProc->Update();

	//�f�o�b�O�\��
	m_pDebugProc->Print("FPS : %d\n", GetFps());
	m_pDebugProc->Print("�ړ� ([A:��] [D:��])\n");
	m_pDebugProc->Print("�W�����v [W]\n");
	m_pDebugProc->Print("�e���� [SPACE]\n");
	m_pDebugProc->Print("���Z�b�g���� [R]\n");
	m_pDebugProc->Print("�e���˕������� ([Q:��] [E:��])\n");

#ifdef _DEBUG

	if (CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_F2) == true &&
		CScene::GetMode() == CScene::MODE_GAME)
	{
		//�����H �����P�F�����Q;
		m_bEdit = m_bEdit ? false : true;
		CObject::DeleteBlock();
	}
#endif

	if ((CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_P) == true ||
		CManager::GetInstance()->GetInputJoyPad()->GetTrigger(CInputJoypad::BUTTON_START, 0) == true) &&
		CScene::GetMode() == CScene::MODE_GAME &&
		m_PauseOK == true &&
		m_Fade->GetFade() == CFade::FADE_NONE)
	{
		//�����H �����P�F�����Q;
		m_Pause = m_Pause ? false : true;

		if (m_Pause == true)
		{
			CGame::GetPause()->SetAppear(true);
		}
		else
		{
			CGame::GetPause()->SetAppear(false);
		}
	}

	//�V�[���̍X�V����
	m_pScene->Update();

	//�����_���[�̍X�V����
	m_pRenderer->Update();

	//�t�F�[�h�̍X�V����
	m_Fade->Update();
}

//====================================================================
//�`�揈��
//====================================================================
void CManager::Draw(void)
{
	//�����_���[�̕`�揈��
	m_pRenderer->Draw();
}

//====================================================================
//��������
//====================================================================
CScene *CScene::Create(MODE mode)
{
	CScene *pScene = nullptr;

	if (pScene == nullptr)
	{
		//�V�[���̐���
		switch (mode)
		{
		case MODE_TITLE:
			pScene = new CTitle();
			break;
		case MODE_GAME:
			pScene = new CGame();
			break;
		case MODE_RESULT:
			pScene = new CResult();
			break;
		}
	}

	CManager::GetInstance()->GetInstance()->GetCamera()->ResetCamera();

	CManager::GetInstance()->GetInstance()->SetEdit(false);

	m_mode = mode;

	if (m_mode == MODE_GAME)
	{

	}

	//�I�u�W�F�N�g�̏���������
	if (FAILED(pScene->Init()))
	{//���������������s�����ꍇ
		return nullptr;
	}

	return pScene;
}

//====================================================================
//�R���X�g���N�^
//====================================================================
CScene::CScene()
{

}

//====================================================================
//�f�X�g���N�^
//====================================================================
CScene::~CScene()
{
}

//====================================================================
//����������
//====================================================================
HRESULT CScene::Init(void)
{
	CScene *m_pScene = CManager::GetInstance()->GetScene();

	m_pScene->Init();

	return S_OK;
}

//====================================================================
//�I������
//====================================================================
void CScene::Uninit(void)
{
	CScene *m_pScene = CManager::GetInstance()->GetScene();

	m_pScene->Uninit();
}

//====================================================================
//�X�V����
//====================================================================
void CScene::Update(void)
{
	CScene *m_pScene = CManager::GetInstance()->GetScene();

	m_pScene->Update();
}

//====================================================================
//�`�揈��
//====================================================================
void CScene::Draw(void)
{
	CScene *m_pScene = CManager::GetInstance()->GetScene();

	m_pScene->Draw();
}

//====================================================================
//���[�h�ݒ菈��
//====================================================================
void CScene::SetMode(MODE mode)
{
	CScene *pScene = CManager::GetInstance()->GetScene();
	CManager::GetInstance()->GetSound()->StopSound();

	if (pScene != nullptr)
	{
		//�V�[���̏I������
		pScene->Uninit();

		delete pScene;
		pScene = nullptr;
	}

	//���[�h�̐���
	pScene = Create(mode);

	CManager::GetInstance()->GetInstance()->SetScene(pScene);
}