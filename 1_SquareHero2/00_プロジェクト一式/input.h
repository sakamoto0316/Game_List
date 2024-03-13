//========================================================================================
//
//�@���̓f�o�C�X�̏���[input.h]
//	Author:sakamoto kai
//
//========================================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"
#include "Xinput.h"

#pragma comment(lib,"xinput.lib")	//���͏���

//�}�N����`
#define NUM_KEY_MAX (256)	//�L�[�̍ő吔
#define MAX_PLAYER (4)	//�v���C���[�̐l��

//���͂̃N���X�錾
class CInput
{
public:
	CInput();
	virtual ~CInput();

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit();
	virtual void Update() = 0;

protected:
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 pDevice;
};

//�L�[�{�[�h�̃N���X�錾
class CInputKeyboard :public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRerease(int nKey);

private:
	BYTE m_aKeyState[NUM_KEY_MAX];
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];
	BYTE m_aKeyStateRerease[NUM_KEY_MAX];

};

//�W���C�p�b�h�̃N���X�錾
class CInputJoypad :public CInput
{
public:

	//�񋓌^��`
	typedef enum
	{
		BUTTON_UP = 0,	//�\���L�[�̏�{�^��
		BUTTON_DOWN,
		BUTTON_LEFT,
		BUTTON_RIGHT,
		BUTTON_START,
		BUTTON_BACK,
		BUTTON_L_PUSH,
		BUTTON_R_PUSH,
		BUTTON_L,
		BUTTON_R,
		BUTTON_NAZO1,
		BUTTON_NAZO2,
		BUTTON_A,
		BUTTON_B,
		BUTTON_X,
		BUTTON_Y,
		BUTTON_MAX
	}JOYKEY;

	typedef enum
	{
		LSTICK_UP = 0,
		LSTICK_DOWN,
		LSTICK_RIGHT,
		LSTICK_LEFT,
		LSTICK_MAX,
	}JOYPAD_LSTICK;

	CInputJoypad();
	~CInputJoypad();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(JOYKEY key, int nPlayer);
	bool GetTrigger(JOYKEY key, int nPlayer);
	bool GetRelease(JOYKEY key, int nPlayer);

	D3DXVECTOR3 Get_Stick_Left(int nPlayer);
	D3DXVECTOR3 Get_Stick_Right(int nPlayer);
	//float Get_Trigger_Left(int nPlayer);
	//float Get_Trigger_Right(int nPlayer);

	bool Get_LStick_Trigger(JOYPAD_LSTICK Type, int nPlayer);
	//void Get_Vibrtion(int nPlayer, int nLeftPower, int RightPoewr);
	//void Get_Vibrtion_false(int nPlayer);

private:
	DIJOYSTATE m_aKeyState; //�S���͏��̕ۊ�
	DIJOYSTATE m_aKeyStateTrigger; //�g���K�[���
	DIJOYSTATE m_aKeyStateRerease; //�����[�X���
	DIJOYSTATE m_aKeyStateRepeat; //���s�[�g���
	BYTE m_aOldState[32]; //�O��̓��͏���ۑ�

	JOYPAD_LSTICK m_LStickInput;
	bool m_OutputDOK;
	bool m_OutputUOK;
	bool m_OutputLOK;
	bool m_OutputROK;

	XINPUT_STATE m_JoyKeyState[MAX_PLAYER];
	XINPUT_STATE m_JoyKeyStateTrigger[MAX_PLAYER];
	XINPUT_STATE m_JoyKeyStateRelease[MAX_PLAYER];
	XINPUT_VIBRATION m_vibration[MAX_PLAYER];
};

//�}�E�X�̃N���X�錾
class CInputMouse :public CInput
{
public:

	//�񋓌^��`
	typedef enum
	{
		PUSH_LEFT = 0,
		PUSH_RIGHT,
		PUSH_WHEEL,
		PUSH_SIDE_1,
		PUSH_SIDE_2,
		PUSH_MAX,
	}MOUSE_PUSH;

	CInputMouse();
	~CInputMouse();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(MOUSE_PUSH nKey);
	bool GetTrigger(MOUSE_PUSH nKey);
	bool GetRerease(MOUSE_PUSH nKey);
	D3DXVECTOR3 GetMouseMove(void);

private:
	LPDIRECTINPUTDEVICE8 m_pDevMouse = NULL;	//���̓f�o�C�X�ւ̃|�C���^
	DIMOUSESTATE2 m_MouseState;				//�S���͏��̕ۊ�
	DIMOUSESTATE2 m_MouseStateTrigger;		//�g���K�[���
	DIMOUSESTATE2 m_MouseStateRerease;		//�����[�X���
	DIMOUSESTATE2 m_MouseStateRepeat;			//���s�[�g���
	BYTE m_aOldState[8];						//�O��̓��͏���ۑ�

};

#endif
