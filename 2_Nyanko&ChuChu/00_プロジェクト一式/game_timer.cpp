//============================================
//
// ���ԏ���[time.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "game_timer.h"
#include "manager.h"
#include "game.h"
#include "renderer.h"
#include "texture.h"

#include "number.h"
#include "pause.h"

//--------------------------------------------------
// �ÓI�����o�ϐ��錾
//--------------------------------------------------
CGameTime* CGameTime::m_pGameTimer = nullptr;		// �Q�[���^�C�}�[�̏��

//--------------------------------------------------
// �}�N����`
//--------------------------------------------------
#define TIME_COUNTDOWN		(120)	// �b��
#define ONE_SECOND			(60)	// 1�b�̃t���[����
#define TIME_POS			(D3DXVECTOR3(618.0f, SCREEN_HEIGHT * 0.5f, 0.0f))		// �Q�[���^�C�}�[�̈ʒu
#define TIME_SIZE			(D3DXVECTOR3(25.0f, 40.0f, 0.0f))		// �Q�[���^�C�}�[�̃T�C�Y
#define TIME_CORON_POS		(D3DXVECTOR3(618.0f, SCREEN_HEIGHT * 0.5f, 0.0f))		// �Q�[���^�C�}�[�̃R�����̈ʒu
#define TIME_CORON_SIZE		(D3DXVECTOR3(15.0f, 30.0f, 0.0f))		// �Q�[���^�C�}�[�̃R�����̃T�C�Y
#define TIME_BG_POS			(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f))		// �Q�[���^�C�}�[�̔w�i�̈ʒu
#define TIME_BG_SIZE		(D3DXVECTOR3(90.0f, 40.0f, 0.0f))		// �Q�[���^�C�}�[�̔w�i�̃T�C�Y
#define TIME_SHIFT			(23.0f)									// �Q�[���^�C�}�[�̂��炷��
#define TIME_CORON_SHIFT	(15.0f)									// �Q�[���^�C�}�[�̃R�����̂��炷��
#define NUMBER_TEXTURE		"data\\TEXTURE\\Number.png"				// �����̃e�N�X�`��
#define CORON_TEXTURE		"data\\TEXTURE\\time_koron.png"			// �R�����̃e�N�X�`��
#define BG_TEXTURE		"data\\TEXTURE\\timebg.jpg"					// �Q�[���^�C�}�[�̔w�i�̃e�N�X�`��

//========================
// �R���X�g���N�^
//========================
CGameTime::CGameTime() : CObject(CObject::TYPE_TIME, CObject::PRIORITY_UI)
{
	// �S�Ă̒l������������
	for (int nCnt = 0; nCnt < GAME_TIME_DIGIT; nCnt++)
	{
		m_apNumber[nCnt] = nullptr;		// �����̏��
	}
	m_pColon = nullptr;					// �R����
	m_pBG = nullptr;					// �w�i
	m_nSeconds = TIME_COUNTDOWN;		// �b��
	m_nFrame = 0;						// �t���[����
}

//========================
// �f�X�g���N�^
//========================
CGameTime::~CGameTime()
{

}

//========================
// ����������
//========================
HRESULT CGameTime::Init(void)
{
	// �S�Ă̒l������������
	m_nSeconds = TIME_COUNTDOWN;		// �b��
	m_nFrame = 0;						// �t���[����

	for (int nCnt = 0; nCnt < GAME_TIME_DIGIT; nCnt++)
	{
		if (m_apNumber[nCnt] == nullptr)
		{ // �����̏�� NULL �̏ꍇ

			// �����𐶐�����
			m_apNumber[nCnt] = new CNumber(CObject::TYPE_NONE, CObject::PRIORITY_UI);

			if (m_apNumber[nCnt] != nullptr)
			{ // �����̏�� NULL ����Ȃ��ꍇ

				if (FAILED(m_apNumber[nCnt]->Init()))
				{ // �����������Ɏ��s�����ꍇ

					// ��~
					assert(false);

					// ���s��Ԃ�
					return E_FAIL;
				}
			}
			else
			{ // ��L�ȊO

				// ��~
				assert(false);

				// ���s��Ԃ�
				return E_FAIL;
			}
		}
	}

	if (m_pColon == nullptr)
	{ // �R������ NULL �̏ꍇ

		// �R�����𐶐�����
		m_pColon = CObject2D::Create(CObject2D::TYPE_NONE, TYPE_NONE, PRIORITY_UI);
	}

	if (m_pBG == nullptr)
	{ // �w�i�� NULL �̏ꍇ

		// �w�i�𐶐�����
		m_pBG = CObject2D::Create(CObject2D::TYPE_NONE, TYPE_NONE, PRIORITY_UI);
	}


	// ������Ԃ�
	return S_OK;
}

//========================
// �I������
//========================
void CGameTime::Uninit(void)
{
	for (int nCnt = 0; nCnt < GAME_TIME_DIGIT; nCnt++)
	{
		if (m_apNumber[nCnt] != nullptr)
		{ // �����̏�� NULL ����Ȃ��ꍇ

			// �����̏I������
			m_apNumber[nCnt]->Uninit();
			m_apNumber[nCnt] = nullptr;
		}
	}

	if (m_pColon != nullptr)
	{ // �R�����̏�� NULL ����Ȃ��ꍇ

		// �R�����̏I������
		m_pColon->Uninit();
		m_pColon = nullptr;
	}

	if (m_pBG != nullptr)
	{ // �w�i�̏�� NULL ����Ȃ��ꍇ

		// �w�i�̏I������
		m_pBG->Uninit();
		m_pBG = nullptr;
	}

	// �{�̂̏I������
	Release();

	// �Q�[���^�C�}�[�� NULL �ɂ���
	m_pGameTimer = nullptr;
}

//========================
// �X�V����
//========================
void CGameTime::Update(void)
{
	if ((CGame::GetPause() != nullptr &&
		CGame::GetPause()->GetPause() == false) &&
		CGame::GetState() != CGame::STATE_START)
	{ // ���̏�ԈȊO�̏ꍇ

		// �v�Z����
		Calculate();
	}
}

//========================
// �`�揈��
//========================
void CGameTime::Draw(void)
{
	if (CGame::GetState() != CGame::STATE_START && CGame::GetCountDown() == false)
	{ // ���̏�ԈȊO�̏ꍇ

		if (m_pBG != nullptr)
		{ // �w�i�̏�� NULL ����Ȃ��ꍇ

			// �`�揈��
			m_pBG->Draw();
		}

		for (int nCnt = 0; nCnt < GAME_TIME_DIGIT; nCnt++)
		{
			if (m_apNumber[nCnt] != nullptr)
			{ // ������ NULL ����Ȃ��ꍇ

				// �`�揈��
				m_apNumber[nCnt]->Draw();
			}
		}

		if (m_pColon != nullptr)
		{ // �R�����̏�� NULL ����Ȃ��ꍇ

			// �`�揈��
			m_pColon->Draw();
		}
	}
}

//========================
// ���̐ݒ菈��
//========================
void CGameTime::SetData(void)
{
	// ���[�J���ϐ��錾
	int aTexU[GAME_TIME_DIGIT];		// ���Ԃ̃e�N�X�`�����W

	// �S�Ă̒l������������
	m_nSeconds = TIME_COUNTDOWN;		// �b��
	m_nFrame = 0;						// �t���[����

	//�l�̌v�Z
	aTexU[0] = m_nSeconds / ONE_SECOND;
	aTexU[1] = m_nSeconds % ONE_SECOND / 10;
	aTexU[2] = m_nSeconds % 10;

	for (int nCnt = 0; nCnt < GAME_TIME_DIGIT; nCnt++)
	{
		if (m_apNumber[nCnt] != nullptr)
		{ // �����̏�� NULL ����Ȃ��ꍇ

			if (nCnt == 0)
			{ // 0�ȊO�̏ꍇ

				// �ʒu��ݒ肷��
				m_apNumber[nCnt]->SetPos(D3DXVECTOR3(TIME_POS.x - TIME_SHIFT - TIME_CORON_SHIFT, TIME_POS.y, TIME_POS.z));
			}
			else if (nCnt == 1)
			{ // 1

				// �ʒu��ݒ肷��
				m_apNumber[nCnt]->SetPos(D3DXVECTOR3(TIME_POS.x + TIME_SHIFT + TIME_CORON_SHIFT, TIME_POS.y, TIME_POS.z));
			}
			else
			{ // 2

				// �ʒu��ݒ肷��
				m_apNumber[nCnt]->SetPos(D3DXVECTOR3(TIME_POS.x + (3 * TIME_SHIFT) + TIME_CORON_SHIFT, TIME_POS.y, TIME_POS.z));
			}

			// ����ݒ肷��
			m_apNumber[nCnt]->SetRot(NONE_D3DXVECTOR3);		// ����
			m_apNumber[nCnt]->SetSize(TIME_SIZE);			// �T�C�Y
			m_apNumber[nCnt]->SetAngle();					// ����
			m_apNumber[nCnt]->SetLength();					// ����

			m_apNumber[nCnt]->SetType(CNumber::TYPE_TIME);	// �ԍ��̎��
			m_apNumber[nCnt]->SetNumber(aTexU[nCnt]);		// �ԍ���ݒ肷��

			// �e�N�X�`���̊��蓖�ď���
			m_apNumber[nCnt]->BindTexture(CManager::Get()->GetTexture()->Regist(NUMBER_TEXTURE));

			// ���_���̐ݒ菈��
			m_apNumber[nCnt]->SetVertex();

			// �e�N�X�`���̐ݒ菈��(�A�j���[�V�����o�[�W����)
			m_apNumber[nCnt]->SetVtxTextureAnim(NUMBER_TEXTURE_PATTERN, aTexU[nCnt]);
		}
	}

	if (m_pColon != nullptr)
	{ // �R������ NULL ����Ȃ��ꍇ

		// ���̐ݒ菈��
		m_pColon->SetPos(TIME_CORON_POS);		// �ʒu
		m_pColon->SetRot(NONE_D3DXVECTOR3);		// ����
		m_pColon->SetSize(TIME_CORON_SIZE);		// �T�C�Y
		m_pColon->SetAngle();					// ����
		m_pColon->SetLength();					// ����

		// �e�N�X�`���̊��蓖�ď���
		m_pColon->BindTexture(CManager::Get()->GetTexture()->Regist(CORON_TEXTURE));

		// ���_���W�̐ݒ菈��
		m_pColon->SetVertex();
	}

	if (m_pBG != nullptr)
	{ // �w�i�� NULL ����Ȃ��ꍇ

		// ���̐ݒ菈��
		m_pBG->SetPos(TIME_BG_POS);				// �ʒu
		m_pBG->SetPosOld(TIME_BG_POS);			// �O��̈ʒu
		m_pBG->SetRot(NONE_D3DXVECTOR3);		// ����
		m_pBG->SetSize(TIME_BG_SIZE);			// �T�C�Y
		m_pBG->SetAngle();						// ����
		m_pBG->SetLength();						// ����

		// ���_���W�̐ݒ菈��
		m_pBG->SetVertex();
		m_pBG->BindTexture(CManager::Get()->GetTexture()->Regist(BG_TEXTURE));
		// ���_�J���[�̐ݒ菈��
		m_pBG->SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

//========================
// �擾����
//========================
CGameTime* CGameTime::Get(void)
{
	if (m_pGameTimer != nullptr)
	{ // �Q�[���^�C�}�[�� NULL ����Ȃ������ꍇ

		// �Q�[���^�C����Ԃ�
		return m_pGameTimer;
	}
	else
	{ // ��L�ȊO

		// �������ĕԂ�
		return m_pGameTimer = CGameTime::Create();
	}
}

//========================
// ��������
//========================
CGameTime* CGameTime::Create(void)
{
	if (m_pGameTimer == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		m_pGameTimer = new CGameTime;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (m_pGameTimer != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(m_pGameTimer->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		m_pGameTimer->SetData();
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// ���Ԃ̃|�C���^��Ԃ�
	return m_pGameTimer;
}

//========================
// �v�Z����
//========================
void CGameTime::Calculate(void)
{
	// �e���̐������i�[
	int aTexU[GAME_TIME_DIGIT];

	// ���Ԃ̌o�߂����Z����
	m_nFrame++;

	if ((m_nFrame % ONE_SECOND) == 0)
	{ // 1�b�o������

		// 1�b���炷
		m_nSeconds--;

		if (m_nSeconds <= 0)
		{ // ���Ԃ�0�𒴂����ꍇ

			// ���Ԃ�␳����
			m_nSeconds = 0;

			// �l�Y�~�̏�����ݒ肷��
			CGame::SetState(CGame::STATE_RAT_WIN);
		}

		// �l�̌v�Z
		aTexU[0] = m_nSeconds / ONE_SECOND;
		aTexU[1] = m_nSeconds % ONE_SECOND / 10;
		aTexU[2] = m_nSeconds % 10;

		for (int nCnt = 0; nCnt < GAME_TIME_DIGIT; nCnt++)
		{
			// �����̐ݒ菈��
			m_apNumber[nCnt]->SetNumber(aTexU[nCnt]);

			// �e�N�X�`���̐ݒ菈��(�A�j���[�V�����o�[�W����)
			m_apNumber[nCnt]->SetVtxTextureAnim(NUMBER_TEXTURE_PATTERN, aTexU[nCnt]);
		}
	}
}

//========================
// �c��b���̎擾����
//========================
int CGameTime::GetSeconds(void)
{
	return m_nSeconds;
}