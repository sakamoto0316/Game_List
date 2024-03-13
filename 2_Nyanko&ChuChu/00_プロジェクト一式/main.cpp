//=========================================
//
// �e�L�X�g�̕`��[main.cpp]
// Author ��������
//
//=========================================
#include "main.h"
#include "manager.h"

// �}�N����`
#define CLASS_NAME					"WindowClass"				// �E�C���h�E�N���X�̖��O
#define WINDOW_NAME					"�ɂ�񂱁�����`����`"	// �E�C���h�E�̖��O(�L���v�V�����ɕ\��)
#define ID_BUTTON_FINISH			(101)						// �I���{�^����ID

// �v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//-----------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------
int g_nCountFPS = 0;

//=========================================
//���C���֐�
//=========================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE /*hInstancePrev*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	// �I�����Ƀ��������[�N�����o
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),										//WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,												//�E�C���h�E�̃X�^�C��
		WindowProc,												//�E�C���h�E�v���V�[�W��
		0,														//0�ɂ���(�ʏ�͎g�p���Ȃ�)
		0,														//0�ɂ���(�ʏ�͎g�p���Ȃ�)
		hInstance,												//�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),							//�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW),								//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),								//�N���C�A���g�̈�̔w�i�F
		NULL,													//���j���[�o�[
		CLASS_NAME,												//�E�C���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION)							//�t�@�C���̃A�C�R��
	};
	HWND hWnd;													//�E�C���h�E�n���h��(���ʎq)
	MSG msg;													//���b�Z�[�W���i�[����ϐ�

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };				//��ʃT�C�Y�̍\����

	//�E�C���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	DWORD dwCurrentTime;										//���ݎ���
	DWORD dwExecLastTime;										//�Ō�ɏ�����������
	DWORD dwFrameCount;											//�t���[���J�E���g
	DWORD dwFPSLastTime;										//�Ō��FPS���v����������

	//�E�C���h�E�𐶐�
	hWnd = CreateWindowEx(0,									//�g���E�C���h�E�X�^�C��
		CLASS_NAME,												//�E�C���h�E�N���X�̖��O
		WINDOW_NAME,											//�E�C���h�E�̖��O
		WS_OVERLAPPEDWINDOW,									//�E�C���h�E�X�^�C��
		CW_USEDEFAULT,											//�E�C���h�E�̍���X���W
		CW_USEDEFAULT,											//�E�C���h�E�̍���Y���W
		(rect.right - rect.left),								//�E�C���h�E�̕�
		(rect.bottom - rect.top),								//�E�C���h�E�̍���
		NULL,													//�e�E�C���h�E�̃n���h��
		NULL,													//���j���[�n���h���܂��͎q�E�C���h�EID
		hInstance,												//�C���X�^���X�n���h��
		NULL);													//�E�C���h�E�쐬�f�[�^

	//����\��ݒ�
	timeBeginPeriod(1);
	dwCurrentTime = 0;											//����������
	dwExecLastTime = timeGetTime();								//���ݎ������擾(�ۑ�)
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//�E�C���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);									//�E�C���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);											//�N���C�A���g�̈���X�V

	//�����_���̎��ݒ�
	srand((unsigned int)time(0));

	// ��������
	CManager::Create();

	if (CManager::Get() != nullptr)
	{ // �}�l�[�W���[�� nullptr ����Ȃ��ꍇ

		// �}�l�[�W���[�̏�����
		CManager::Get()->Init(hInstance, hWnd, FALSE);
	}
	else
	{ // ��L�ȊO

		// ���s��Ԃ�
		return -1;
	}

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windows�̏���

			if (msg.message == WM_QUIT)
			{//WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���

				//�����o��
				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);							//���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
				DispatchMessage(&msg);							//�E�C���h�E�v���V�[�W���փ��b�Z�[�W�𑗏o
			}
		}
		else
		{//DirectX�̏���

			dwCurrentTime = timeGetTime();						//���ݎ������擾

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{ // 0.5�b�o��

				// FPS���v��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				//FPS�𑪒肵��������ۑ�
				dwFPSLastTime = dwCurrentTime;

				// �t���[���J�E���g���N���A
				dwFrameCount = 0;
			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{ // 60����1�b�o��

				// �����J�n�̎���[���ݎ���]��ۑ�
				dwExecLastTime = dwCurrentTime;

				if (CManager::Get() != nullptr)
				{ // �m�ۂɐ������Ă����ꍇ

					// �}�l�[�W���[�̍X�V
					CManager::Get()->Update();

					// �}�l�[�W���[�̕`��
					CManager::Get()->Draw();

					//�t���[���J�E���g�����Z
					dwFrameCount++;
				}
			}
		}
	}

	// �����_���[�̔j��
	if (CManager::Get() != nullptr)
	{ // �}�l�[�W���[�� nullptr ����Ȃ��ꍇ

		// �}�l�[�W���[�̏I������
		CManager::Get()->Uninit();
	}

	//����\��߂�
	timeEndPeriod(1);

	//�E�C���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=========================================
//�E�C���h�E�v���V�[�W��
//=========================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;							//�Ԃ�l���i�[����ϐ���ݒ肷��

	switch (uMsg)
	{
	case WM_DESTROY:					//�E�B���h�E�j���̃��b�Z�[�W

		//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);

		//�����o��
		break;

	case WM_KEYDOWN:											//�L�[�����̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE:											//[ESK�L�[]�������ꂽ

			//�I�����b�Z�[�W��\��
			nID = MessageBox(hWnd, "�I�����܂���?", "�I�����b�Z�[�W", MB_YESNO);

			if (nID == IDYES)
			{//�u�͂��v��I�񂾏ꍇ

				//�E�B���h�E��j������(WM_DESTROY���b�Z�[�W�𑗂�)
				DestroyWindow(hWnd);
			}
			else
			{
				return 0;										//0��Ԃ��Ȃ��ƏI�����Ă��܂�
			}

			//�����o��
			break;
		}
		//�����o��
		break;

	case WM_CLOSE:											//�R�}���h���s�̃��b�Z�[�W

		//�I�����b�Z�[�W��\��
		nID = MessageBox(hWnd, "�I�����܂���?", "�I�����b�Z�[�W", MB_YESNO);

		if (nID == IDYES)
		{//�u�͂��v��I�񂾏ꍇ

			//�E�B���h�E��j������(WM_DESTROY���b�Z�[�W�𑗂�)
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;											//0��Ԃ��Ȃ��ƏI�����Ă��܂�
		}

		//�����o��
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);			//�K��̏�����Ԃ�
}

//=========================================
// FPS�̎擾����
//=========================================
int GetFPS(void)
{
	// FPS��Ԃ�
	return g_nCountFPS;
}