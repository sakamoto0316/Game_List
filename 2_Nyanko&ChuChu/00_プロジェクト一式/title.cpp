//============================================
//
// �^�C�g����ʂ̃��C������[title.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "object.h"
#include "title.h"
#include "fade.h"
#include "Objectmesh.h"
#include "sound.h"

#include "2DUI_edit.h"
#include "skybox.h"
#include "title_logo.h"
#include "title_wall.h"
#include "title_floor.h"
#include "title_back.h"

// �}�N����`
#define ENTRY_TRANS_TIMER		(180)										// �����L���O��ʂɑJ�ڂ���J�E���g��
#define WALL_POS				(D3DXVECTOR3(0.0f, 300.0f, 600.0f))			// �ǂ̈ʒu
#define WALL_ROT				(D3DXVECTOR3(-D3DX_PI * 0.5f, 0.0f, 0.0f))	// �ǂ̌���
#define WALL_SIZE				(D3DXVECTOR3(800.0f, 0.0f, 600.0f))			// �ǂ̃T�C�Y

//--------------------------------------------
// �ÓI�����o�ϐ��錾
//--------------------------------------------
CTitle::STATE CTitle::m_state = STATE_TITLE_APPEAR;			// ���

//=========================================
// �R���X�g���N�^
//=========================================
CTitle::CTitle() : CScene(TYPE_SCENE, PRIORITY_BG)
{
	// �S�Ă̒l���N���A����
	m_pUIEdit = NULL;
	m_state = STATE_TITLE_APPEAR;			// ���
	m_nTransCount = 0;						// �J�ڃJ�E���g
	m_bEdit = false;
}

//=========================================
// �f�X�g���N�^
//=========================================
CTitle::~CTitle()
{

}

//=========================================
//����������
//=========================================
HRESULT CTitle::Init(void)
{
	//�@�V�[���̏�����
	CScene::Init();

	// �^�C�g�����S�̐�������
	CTitleLogo::Create();

	// �^�C�g���̕ǂ̐�������
	CTitleWall::Create();

	// �^�C�g���̏��̐�������
	CTitleFloor::Create();

	// �^�C�g���̔w�i�̐�������
	CTitleBack::Create();

	//UI�G�f�B�^�[�̐���
	m_pUIEdit = C2DUIEdit::Create();
	m_pUIEdit->LoadData(LOADUI_NAME,NONE_D3DXVECTOR3);

	// �S�Ă̒l������������
	m_state = STATE_TITLE_APPEAR;	// ���
	m_nTransCount = 0;				// �J�ڃJ�E���g

	// ������Ԃ�
	return S_OK;
}

//=============================================
//�I������
//=============================================
void CTitle::Uninit(void)
{
	// �I������
	CScene::Uninit();

	if (m_pUIEdit != NULL)
	{
		//�G�f�B�b�g���[�h�̏I������
		m_pUIEdit->Uninit();

		delete m_pUIEdit;
		m_pUIEdit = NULL;
	}

	// �Đ����̃T�E���h���~
	CManager::Get()->GetSound()->Stop();
}

//======================================
//�X�V����
//======================================
void CTitle::Update(void)
{
	//�G�f�B�b�g���[�h�̃I���I�t
	if (m_bEdit)
	{
		//�G�f�B�b�g���[�h�̍X�V����
		m_pUIEdit->Update();
	}
	else
	{
		switch (m_state)
		{
		case CTitle::STATE_TITLE_APPEAR:


			break;

		case CTitle::STATE_WAIT:

			if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true ||
				CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_START, 0) == true ||
				CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, 0) == true)
			{ // ENTER�L�[���������ꍇ

				// �^�C�g���̃X�^�[�g����炷
				CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_TITLE_START);

				// �J�ڏ�Ԃɐݒ肷��
				m_state = STATE_TRANS;

				// ���̐�̏������s��Ȃ�
				return;
			}

			break;

		case CTitle::STATE_TRANS:

			// �J�ڃJ�E���g�����Z����
			m_nTransCount++;

			break;

		case STATE_HOLEIN:

			// �J�ڃJ�E���g�����Z����
			m_nTransCount++;

			if (m_nTransCount % ENTRY_TRANS_TIMER == 0)
			{ // �J�ڃJ�E���g����莞��

				// �G���g���[�ɑJ�ڂ���
				CManager::Get()->GetFade()->SetFade(CScene::MODE_ENTRY);
			}

			break;

		default:

			// ��~
			assert(false);

			break;
		}
	}

#ifdef _DEBUG

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_F2) == true)
	{
		m_bEdit = m_bEdit ? false : true;
	}

#endif // _DEBUG

	// �����_���[�̍X�V
	CManager::Get()->GetRenderer()->Update();
}

//======================================
//�`�揈��
//======================================
void CTitle::Draw(void)
{

}

//======================================
// ��Ԃ̐ݒ菈��
//======================================
void CTitle::SetState(const STATE state)
{
	// ��Ԃ�ݒ肷��
	m_state = state;
}

//======================================
// ��Ԃ̎擾����
//======================================
CTitle::STATE CTitle::GetState(void)
{
	// ��Ԃ�Ԃ�
	return m_state;
}