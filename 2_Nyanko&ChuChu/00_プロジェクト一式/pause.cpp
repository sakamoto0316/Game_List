//=======================================
//
// �|�[�Y�̃��C������[pause.cpp]
// Author ��������
//
//=======================================
#include "main.h"
#include "manager.h"
#include "object2D.h"
#include "game.h"
#include "pause.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "texture.h"
#include "useful.h"

//---------------------------------------
// �������O���
//---------------------------------------
namespace
{
	const D3DXCOLOR PAUSE_BACK_COL = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.4f);			// �w�i�̐F
	const float PAUSE_ALPHA = 0.02f;				// �����x�̕ω��̐��l
	const float  DECIDE_ALPHA = 0.7f;				// ���肵����̓����x�̕ω�
	const float  NOCHOICE_ALPHA = 0.5f;				// �I��ł��Ȃ��I�����̓����x
	const float  SIZEDEST_MAGNI = 1.2f;				// �ڕW�̃T�C�Y�̔{��
	const float  SIZEDEST_CORRECT_VALUE = 0.7f;		// �ڕW�̃T�C�Y�̕␳�̔{��
	const float  CHOICE_ALPHA_MIN = 0.4f;			// �I�����̓����x�̍ŏ��l
	const int SELECT_REPEAT_COUNT = 15;				// �I���̎��̃��s�[�g�̃J�E���g��

	const char* PAUSE_TEXTURE[CPause::POLYGON_MAX] =	// �e�N�X�`���t�@�C����
	{
		nullptr,									// �w�i�|���S��
		"data\\TEXTURE\\PAUSE_menu.png",			// �|�[�Y���j���[�̃e�N�X�`��
		"data\\TEXTURE\\PAUSE_return.png",			// �R���e�B�j���[�̃e�N�X�`��
		"data\\TEXTURE\\PAUSE_Reset.png",			// ���Z�b�g�̃e�N�X�`��
		"data\\TEXTURE\\PAUSE_title.png",			// �^�C�g���̃e�N�X�`��
		"data\\TEXTURE\\PAUSE_Choicebar.png",		// �E�J�[�\���̃e�N�X�`��
		"data\\TEXTURE\\PAUSE_Choicebar.png",		// ���J�[�\���̃e�N�X�`��
	};

	const CPause::Info PAUSE_INFO[CPause::POLYGON_MAX] = 	// �|�[�Y�̏��
	{
		{ D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f) ,D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f) },			// �w�i�|���S��
		{ D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f) ,D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f) },		// �|�[�Y���j���[
		{ D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 260.0f, 0.0f) ,D3DXVECTOR3(360.0f, 64.0f, 0.0f) },	// �R���e�B�j���[
		{ D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 410.0f, 0.0f) ,D3DXVECTOR3(220.0f, 64.0f, 0.0f) },			// ���g���C
		{ D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 560.0f, 0.0f) ,D3DXVECTOR3(200.0f, 64.0f, 0.0f) },			// �^�C�g��
		{ NONE_D3DXVECTOR3,D3DXVECTOR3(50.0f, 50.0f, 0.0f) },	// �E�J�[�\��
		{ NONE_D3DXVECTOR3,D3DXVECTOR3(50.0f, 50.0f, 0.0f) },	// ���J�[�\��
	};
}

//==========================================
// �R���X�g���N�^
//==========================================
CPause::CPause() : CObject(TYPE_PAUSE, PRIORITY_PAUSE)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < POLYGON_MAX; nCnt++)
	{
		m_apObject[nCnt] = nullptr;		// �|���S���̏��
	}

	m_PauseColor = NONE_D3DXCOLOR;		// �I�𒆂̑I�����̐F
	m_sizeDest = NONE_D3DXVECTOR3;		// �ڕW�̃T�C�Y
	m_PauseMenu = MENU_CONTINUE;;		// �|�[�Y���j���[
	m_nPauseCounter = 0;				// �J�E���^�[
	m_fPauseAlpha = 0.0f;				// �����x��ω�������ϐ�
	m_bPause = false;					// �|�[�Y��
	m_bDisp = true;						// �`���
}

//==========================================
// �f�X�g���N�^
//==========================================
CPause::~CPause()
{

}

//==========================================
// �|�[�Y�̏���������
//==========================================
HRESULT CPause::Init(void)
{
	for (int nCnt = 0; nCnt < POLYGON_MAX; nCnt++)
	{
		if (m_apObject[nCnt] == nullptr)
		{ // �I�u�W�F�N�g�� NULL �̏ꍇ

			// �|���S���̐�������
			m_apObject[nCnt] = m_apObject[nCnt]->Create(CObject2D::TYPE_NONE, CObject::TYPE_NONE, PRIORITY_PAUSE);

			// ����ݒ肷��
			m_apObject[nCnt]->SetPos(PAUSE_INFO[nCnt].pos);			// �ʒu
			m_apObject[nCnt]->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	// ����
			m_apObject[nCnt]->SetSize(PAUSE_INFO[nCnt].size);			// �T�C�Y
			m_apObject[nCnt]->SetLength();								// ����
			m_apObject[nCnt]->SetAngle();								// ����

			// ���_��ݒ肷��
			m_apObject[nCnt]->SetVertex();

			if (nCnt == POLYGON_BACK)
			{ // �w�i�|���S���̏ꍇ

				// ���_�J���[��ݒ肷��
				m_apObject[nCnt]->SetVtxColor(PAUSE_BACK_COL);
			}

			// �e�N�X�`���̊��蓖�ď���
			m_apObject[nCnt]->BindTexture(CManager::Get()->GetTexture()->Regist(PAUSE_TEXTURE[nCnt]));
		}
	}

	// �S�Ă̒l������������
	m_PauseMenu = MENU_CONTINUE;		// ���j���[
	m_PauseColor = NONE_D3DXCOLOR;		// �I�����̐F
	m_sizeDest = D3DXVECTOR3(PAUSE_INFO[m_PauseMenu + POLYGON_CONTINUE].size.x * SIZEDEST_MAGNI, PAUSE_INFO[m_PauseMenu + POLYGON_CONTINUE].size.y * SIZEDEST_MAGNI, 0.0f);			// �ڕW�̃T�C�Y
	m_nPauseCounter = 0;				// �J�E���^�[
	m_fPauseAlpha = PAUSE_ALPHA;		// �����x�̕ω���
	m_bPause = false;					// �|�[�Y��
	m_bDisp = true;						// �`���

	// �J�[�\���̈ړ�����
	CursorMove();

	// ������Ԃ�
	return S_OK;
}

//========================================
// �|�[�Y�̏I������
//========================================
void CPause::Uninit(void)
{
	for (int nCnt = 0; nCnt < POLYGON_MAX; nCnt++)
	{
		// �I������
		m_apObject[nCnt]->Uninit();
	}

	// �j������
	Release();

	// �|�[�Y��NULL������
	CGame::DeletePause();
}

//========================================
// �|�[�Y�̍X�V����
//========================================
void CPause::Update(void)
{
	// �J�E���^�[�����Z����
	m_nPauseCounter++;

	// �|�[�Y�̑I������
	PauseSelect();

	// �J�[�\���̈ړ�����
	CursorMove();

	// �|�[�Y�̌��菈��
	if (PauseDecide() == true)
	{ // �ʂ̃��[�h�ɂȂ����ꍇ

		// ���̐�̏������s��Ȃ�
		return;
	}

	if (CManager::Get()->GetFade()->GetFade() != CFade::FADE_NONE &&
		CManager::Get()->GetFade()->GetFade() != CFade::FADE_IN)
	{ // �t�F�[�h�A�E�g���Ă���ꍇ

		// �����x�̕ω���ݒ肷��
		m_fPauseAlpha = DECIDE_ALPHA;
	}

	// �����x�␳����
	PauseAlphaCorrect();

	// �I�𒆂̑I�����̓����x��ω�������
	m_PauseColor.a -= m_fPauseAlpha;

	// ���_�ݒ菈��
	PauseVertex();
}

//=====================================
// �|�[�Y�̕`�揈��
//=====================================
void CPause::Draw(void)
{
// �f�o�b�O�p
#ifdef _DEBUG

	if (m_bDisp == true)
	{ // �`��󋵂� true �������ꍇ

		for (int nCnt = 0; nCnt < POLYGON_MAX; nCnt++)
		{
			// �`�揈��
			m_apObject[nCnt]->Draw();
		}
	}

#else

	for (int nCnt = 0; nCnt < POLYGON_MAX; nCnt++)
	{
		// �`�揈��
		m_apObject[nCnt]->Draw();
	}

#endif
}

//=====================================
// �T�C�Y�␳����
//=====================================
void CPause::SizeCorrect(int nIdx)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 size = m_apObject[nIdx]->GetSize();		// �T�C�Y���擾����

	// �T�C�Y�̕␳
	useful::Correct(m_sizeDest.x, &size.x, SIZEDEST_CORRECT_VALUE);
	useful::Correct(m_sizeDest.y, &size.y, SIZEDEST_CORRECT_VALUE);

	//�T�C�Y���X�V����
	m_apObject[nIdx]->SetSize(size);
}

//=====================================
// �|�[�Y�󋵂̐ݒ菈��
//=====================================
void CPause::SetPause(const bool bPause)
{
	// �|�[�Y�̏󋵂�ݒ肷��
	m_bPause = bPause;

	if (m_bPause == false)
	{ // �|�[�Y�� false �̏ꍇ

		// �I�����Ă�����̂��R���e�B�j���[�ɂ���
		m_PauseMenu = MENU::MENU_CONTINUE;
	}
}

//=====================================
// �|�[�Y�󋵂̎擾����
//=====================================
bool CPause::GetPause(void)
{
	// �|�[�Y�̏󋵂�Ԃ�
	return m_bPause;
}

//=====================================
// �`��󋵂̐؂�ւ�����
//=====================================
void CPause::ChangeDisp(void)
{
	// �`��󋵂�؂�ւ���
	m_bDisp = m_bDisp ? false : true;
}

//=====================================
// �|�[�Y�̑I������
//=====================================
void CPause::PauseSelect(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_W) == true ||
		CManager::Get()->GetInputKeyboard()->GetRepeat(DIK_W, SELECT_REPEAT_COUNT) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_UP, 0) == true)
	{ // W�L�[���������ꍇ

		// �|�[�Y�̐ݒ�
		m_PauseMenu = (MENU)((m_PauseMenu + (MENU_MAX - 1)) % MENU_MAX);

		// �����x�̕ω���ݒ肷��
		m_fPauseAlpha = PAUSE_ALPHA;

		// �I������炷
		CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_SELECT);
	}

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_S) == true ||
		CManager::Get()->GetInputKeyboard()->GetRepeat(DIK_S, SELECT_REPEAT_COUNT) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_DOWN, 0) == true)
	{ // S�L�[���������ꍇ

		// �|�[�Y�̐ݒ�
		m_PauseMenu = (MENU)((m_PauseMenu + 1) % MENU_MAX);

		// �����x�̕ω���ݒ肷��
		m_fPauseAlpha = PAUSE_ALPHA;

		// �I������炷
		CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_SELECT);
	}

	// �ڕW�̃T�C�Y�̐ݒ菈��
	m_sizeDest = D3DXVECTOR3(PAUSE_INFO[m_PauseMenu + POLYGON_CONTINUE].size.x * SIZEDEST_MAGNI, PAUSE_INFO[m_PauseMenu + POLYGON_CONTINUE].size.y * SIZEDEST_MAGNI, 0.0f);
}

//=====================================
// �|�[�Y�̌��菈��
//=====================================
bool CPause::PauseDecide(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, 0) == true)
	{ // ENTER�L�[���������ꍇ

		if (CManager::Get()->GetFade()->GetFade() == CFade::FADE_NONE)
		{ // �t�F�[�h���s���Ă��Ȃ��Ƃ�

			switch (m_PauseMenu)
			{
			case MENU_CONTINUE:		// �R���e�B�j���[���w���Ă����ꍇ

				break;

			case MENU_RESET:			// ���g���C���w���Ă����ꍇ

				// �I������
				Uninit();

				// ���[�h�ݒ�(�Q�[���Ɉڍs)
				CManager::Get()->GetFade()->SetFade(CScene::MODE_GAME);

				break;

			case MENU_TITLE:			// �^�C�g�����w���Ă����ꍇ

				// �I������
				Uninit();

				// ���[�h�ݒ�(�^�C�g���Ɉڍs)
				CManager::Get()->GetFade()->SetFade(CScene::MODE_TITLE);

				break;

			default:

				// ��~
				assert(false);

				break;
			}

			// �|�[�Y����������
			m_bPause = false;
		}

		// ���艹��炷
		CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_DECIDE);

		// true ��Ԃ�
		return true;
	}

	// false ��Ԃ�
	return false;
}

//=====================================
// �|�[�Y�̓����x�␳����
//=====================================
void CPause::PauseAlphaCorrect(void)
{
	if (m_PauseColor.a > 1.0f)
	{ // �A���t�@�l��1.0f���ゾ�����ꍇ

		// �A���t�@�l��1.0f�ɐݒ肷��
		m_PauseColor.a = 1.0f;

		// �A���t�@�l�̕������t�ɕς���
		m_fPauseAlpha *= -1;
	}
	else if (m_PauseColor.a < CHOICE_ALPHA_MIN)
	{ // �A���t�@�l����萔�����������ꍇ

		// �A���t�@�l���ŏ��l�ɐݒ肷��
		m_PauseColor.a = CHOICE_ALPHA_MIN;

		// �A���t�@�l�̕������t�ɕς���
		m_fPauseAlpha *= -1;
	}
}

//=====================================
// �|�[�Y�̒��_�ݒ菈��
//=====================================
void CPause::PauseVertex(void)
{
	for (int nPauseCnt = 0; nPauseCnt < MENU_MAX; nPauseCnt++)
	{
		if (m_PauseMenu == nPauseCnt)
		{ // �I�𒆂̑I�����̏ꍇ

			// �F��ݒ肷��
			m_apObject[nPauseCnt + POLYGON_CONTINUE]->SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_PauseColor.a));

			// �T�C�Y�̕␳����
			SizeCorrect(nPauseCnt + POLYGON_CONTINUE);
		}
		else
		{ // �I�����Ă��Ȃ��I�����̏ꍇ

			// �F��ݒ肷��
			m_apObject[nPauseCnt + POLYGON_CONTINUE]->SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, NOCHOICE_ALPHA));

			// �T�C�Y�̐ݒ菈��
			m_apObject[nPauseCnt + POLYGON_CONTINUE]->SetSize(PAUSE_INFO[nPauseCnt + POLYGON_CONTINUE].size);
		}

		// ���_���W�̐ݒ菈��
		m_apObject[nPauseCnt + POLYGON_CONTINUE]->SetVertex();
	}
}

//=====================================
// ���j���[�̈ړ�����
//=====================================
void CPause::CursorMove(void)
{
	// ���ݑI�𒆂̃��j���[�̈ʒu�ƃT�C�Y���擾����
	D3DXVECTOR3 pos = m_apObject[m_PauseMenu + POLYGON_CONTINUE]->GetPos();

	// �J�[�\���̐ݒ菈��
	m_apObject[POLYGON_RCURSOR]->SetPos(D3DXVECTOR3(pos.x + m_sizeDest.x + PAUSE_INFO[POLYGON_RCURSOR].pos.x, pos.y, 0.0f));
	m_apObject[POLYGON_LCURSOR]->SetPos(D3DXVECTOR3(pos.x - m_sizeDest.x - PAUSE_INFO[POLYGON_LCURSOR].pos.x, pos.y, 0.0f));

	// ���_���W�̐ݒ菈��
	m_apObject[POLYGON_RCURSOR]->SetVertex();
	m_apObject[POLYGON_LCURSOR]->SetVertex();
}

//=====================================
// ��������
//=====================================
CPause* CPause::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CPause* pPause = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pPause == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pPause = new CPause;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pPause != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pPause->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �|�[�Y�̃|�C���^��Ԃ�
	return pPause;
}