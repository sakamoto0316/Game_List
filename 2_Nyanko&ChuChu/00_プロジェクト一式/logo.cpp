//============================================
//
// �}�l�[�W���[�̃��C������[manager.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "renderer.h"
#include "logo.h"
#include "logo_mark.h"
#include "input.h"
#include "fade.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define LOGO_TRANSITION_COUNT		(120)		// ���S��ʂ̑J�ڂ���J�E���g

//=========================================
// �R���X�g���N�^
//=========================================
CLogo::CLogo() : CScene(TYPE_SCENE, PRIORITY_BG)
{
	// �S�Ă̏����N���A����
	m_nTransCount = 0;			// �J�ڃJ�E���g
}

//=========================================
// �f�X�g���N�^
//=========================================
CLogo::~CLogo()
{

}

//=========================================
//����������
//=========================================
HRESULT CLogo::Init(void)
{
	// �V�[���̏���������
	CScene::Init();

	// �S�Ă̏�������������
	m_nTransCount = 0;			// �J�ڃJ�E���g

	// ���S�}�[�N�̐�������
	CLogoMark::Create();

	// ������Ԃ�
	return S_OK;
}

//=============================================
//�I������
//=============================================
void CLogo::Uninit(void)
{
	// �j������
	Release();
}

//======================================
//�X�V����
//======================================
void CLogo::Update(void)
{
	// �J�ڃJ�E���g�����Z����
	m_nTransCount++;

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_START, 0) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, 0) == true ||
		m_nTransCount >= LOGO_TRANSITION_COUNT)
	{ // ENTER�L�[���������ꍇ

		// �^�C�g���ɑJ�ڂ���
		CManager::Get()->GetFade()->SetFade(CScene::MODE_TITLE);

		// ���̐�̏������s��Ȃ�
		return;
	}

	if (CManager::Get()->GetRenderer() != nullptr)
	{ // �����_���[�� NULL ����Ȃ��ꍇ

		// �X�V����
		CManager::Get()->GetRenderer()->Update();
	}
}

//======================================
//�`�揈��
//======================================
void CLogo::Draw(void)
{

}