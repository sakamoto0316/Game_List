//============================================
//
// �Q�[���t�B�j�b�V������[game_finish.cpp]
// Author�F�x�씋��
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "game.h"
#include "game_finish.h"
#include "object2D.h"
#include "texture.h"
#include "useful.h"
#include "game_timer.h"
#include "countdown.h"
#include "sound.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define FINISH_TEXTURE		"data\\TEXTURE\\FinishLogo.png"						// �uFINISH�v�̃e�N�X�`��
#define FINISH_SIZE			(D3DXVECTOR3(300.0f, 100.0f, 0.0f))					// �uFINISH�v�̃T�C�Y
#define INIT_FINISH_POS		(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 360.0f, 0.0f))	// �uFINISH�v�̏����ʒu
#define NORMAL_SIZE			(1.0f)								// �ʏ�T�C�Y
#define VISIBLE_COLOR		(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// �ʏ�J���[
#define FINISH_COUNT		(60)								// �t�B�j�b�V���J�E���g

//--------------------------------------------
// �ÓI�����o�ϐ�
//--------------------------------------------
CGameTime* CGameFinish::m_pGameTime = nullptr;		// �Q�[���^�C���̏��
CCountdown* CGameFinish::m_pCountdown = nullptr;	// �J�E���g�_�E���̏��

//============================
// �R���X�g���N�^
//============================
CGameFinish::CGameFinish() : CObject(CObject::TYPE_FINISHUI, PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
	m_pFinish = nullptr;		// �t�B�j�b�V���̏��
	m_pGameTime = nullptr;		// �Q�[���^�C���̏��
	m_pCountdown = nullptr;		// �J�E���g�_�E���̏��
	m_fSize = NORMAL_SIZE;		// �T�C�Y
	m_bFinish = false;			// �I��������
	m_bSe = false;				// SE�Đ���
}

//============================
// �f�X�g���N�^
//============================
CGameFinish::~CGameFinish()
{

}

//============================
// ����������
//============================
HRESULT CGameFinish::Init(void)
{
	// �S�Ă̒l������������
	m_fSize = NORMAL_SIZE * 4.0f;
	m_pFinish = nullptr;
	m_bFinish = false;
	m_bSe = false;				// SE�Đ���

	if (m_pFinish == nullptr)
	{ // �t�B�j�b�V���̏�� NULL �̏ꍇ

		// �t�B�j�b�V���𐶐�����
		m_pFinish = CObject2D::Create(CObject2D::TYPE_NONE, CObject::TYPE_NONE, PRIORITY_PAUSE);

		if (m_pFinish != nullptr)
		{ // ��񂪓����Ă���ꍇ

			if (FAILED(m_pFinish->Init()))
			{ // �������Ɏ��s�����ꍇ

				// ��~
				assert(false);

				// ���s��Ԃ�
				return E_FAIL;
			}
		}
	}
	else
	{ // ��L�ȊO

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//============================
// �I������
//============================
void CGameFinish::Uninit(void)
{
	// �S�Ă̒l���N���A����
	m_pGameTime = nullptr;
	m_pCountdown = nullptr;

	if (m_pFinish != nullptr)
	{ // �I���̃|���S���� NULL ����Ȃ��ꍇ

		// �I���̃|���S���̏I������
		m_pFinish->Uninit();
		m_pFinish = nullptr;
	}

	// �{�̂̏I������
	Release();
}

//============================
// �X�V����
//============================
void CGameFinish::Update(void)
{
	//�I���J�E���g����
	{
		m_pGameTime = CGameTime::Get();
		if (m_pGameTime != nullptr)
		{
			if (m_pCountdown == nullptr && m_pGameTime->GetSeconds() == 5)
			{// �c��T�b���J�E���g�_�E���|�C���^�[��null�̎�
				m_pCountdown = CCountdown::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(50.0f, 80.0f, 0.0f), FINISH_COUNT, true);
				CGame::SetCountDown(true);
			}
			if (m_pGameTime->GetSeconds() == 0)
			{// �J�E���g�_�E����0�ɂȂ�����
				if (CGame::GetState() != CGame::STATE_CAT_WIN)
				{// �L�������Ă����Ԃ���Ȃ���
					m_bFinish = true;
				}
			}
			if (m_bFinish == true)
			{// �I����ԂɂȂ�����

				if (m_bSe == false)
				{ // SE���Đ�����ĂȂ��Ƃ�

					// �s�b�s�[�I�Đ�
					CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_FINISH);

					m_bSe = true;
				}

				m_fSize -= 0.2f;
				if (m_fSize < 1.0f)
				{
					m_fSize = 1.0f;
				}

				//�ݒ菈��
				SetData();
			}
		}
	}
}

//============================
// �`�揈��
//============================
void CGameFinish::Draw(void)
{
	if (m_bFinish == false)
	{// �I�����ĂȂ��ꍇ
		return;
	}
	else
	{
		m_pFinish->Draw();

	}
}

//============================
// ���̐ݒ菈��
//============================
void CGameFinish::SetData(void)
{
	if (m_pFinish != nullptr)
	{	//NULL����Ȃ��ꍇ

		// ����ݒ肷��
		m_pFinish->SetPos(INIT_FINISH_POS);			// �ʒu
		m_pFinish->SetSize(FINISH_SIZE * m_fSize);	// �T�C�Y

		// �e�N�X�`���̊��蓖�ď���
		m_pFinish->BindTexture(CManager::Get()->GetTexture()->Regist(FINISH_TEXTURE));

		m_pFinish->SetRot(NONE_D3DXVECTOR3);	// ����
		m_pFinish->SetAngle();					// ����
		m_pFinish->SetLength();					// ����
		
		// ���_���W�̐ݒ菈��
		m_pFinish->SetVertex();

		// ���_�J���[�̐ݒ菈��
		m_pFinish->SetVtxColor(VISIBLE_COLOR);
	}
	else
	{ // ��L�ȊO

		//�@��~
		assert(false);
	}
}

//============================
//��������
//============================
CGameFinish* CGameFinish::Create(void)
{
	// �Q�[���t�B�j�b�V���̃|�C���^�𐶐�
	CGameFinish* pFinish = nullptr;

	if (pFinish == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

	  // �I�u�W�F�N�g�𐶐�
		pFinish = new CGameFinish;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

	  // ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pFinish != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

	  // ����������
		if (FAILED(pFinish->Init()))
		{ // �������Ɏ��s�����ꍇ

		  // ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pFinish->SetData();
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

	  // ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �Q�[���t�B�j�b�V���̃|�C���^��Ԃ�
	return pFinish;
}

//============================
//�I���̐ݒ菈��
//============================
void CGameFinish::SetFinish(bool bFinish)
{
	m_bFinish = bFinish;
}