//============================================
//
// ���ԏ���[time.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "time.h"
#include "manager.h"
#include "game.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

// �}�N����`
#define TIME_TEXTURE		"data\\TEXTURE\\TimeNumber.png"		// ���Ԃ̃e�N�X�`��
#define TIMEDOT_TEXTURE		"data\\TEXTURE\\TimeDot.png"		// ���Ԃ̓_�̃e�N�X�`��
#define TIMEDOT_COUNT		(3)									// ���Ԃ̓_�̔ԍ�

//========================
// �R���X�g���N�^
//========================
CTime::CTime() : CObject(CObject::TYPE_TIME, CObject::PRIORITY_UI)
{
	// �R���X�g���N�^�̔�
	Box();
}

//========================
// �I�[�o�[���[�h�R���X�g���N�^
//========================
CTime::CTime(CObject::TYPE type, PRIORITY priority) : CObject(type, priority)
{
	// �R���X�g���N�^�̔�
	Box();
}

//========================
// �f�X�g���N�^
//========================
CTime::~CTime()
{

}

//========================
// �R���X�g���N�^�̔�
//========================
void CTime::Box(void)
{
	// �S�Ă̒l������������
	for (int nCnt = 0; nCnt < MAX_TIME_DIGIT; nCnt++)
	{
		// �����̏��
		m_apNumber[nCnt] = nullptr;
	}

	m_pDot = nullptr;				// �^�C���̓_
	m_TotalTime = 0;				// ���v����
}

//========================
// ����������
//========================
HRESULT CTime::Init(void)
{
	// ���[�J���ϐ��錾
	int nTexIdx;		// �e�N�X�`���̃C���f�b�N�X

	// �S�Ă̒l������������
	m_TotalTime = 0;				// ���v����

	// �e�N�X�`���̓ǂݍ��ݏ���
	nTexIdx = CManager::Get()->GetTexture()->Regist(TIME_TEXTURE);

	// ���������m�ۂ���
	for (int nCnt = 0; nCnt < MAX_TIME_DIGIT; nCnt++)
	{
		if (m_apNumber[nCnt] == nullptr)
		{ // �|�C���^�� NULL �̏ꍇ

			// ���������m�ۂ���
			m_apNumber[nCnt] = new CNumber(CObject::TYPE_NONE, CObject::PRIORITY_UI);
		}
		else
		{ // �|�C���^�� NULL ����Ȃ��ꍇ

			// ��~
			assert(false);

			// ���s��Ԃ�
			return E_FAIL;
		}

		if (m_apNumber[nCnt] != nullptr)
		{ // �|�C���^�� NULL ����Ȃ��ꍇ

			// ����������
			if (FAILED(m_apNumber[nCnt]->Init()))
			{ // �����������Ɏ��s�����ꍇ

				// ��~
				assert(false);

				// ���s��Ԃ�
				return E_FAIL;
			}

			// �e�N�X�`���̊��蓖�ď���
			m_apNumber[nCnt]->BindTexture(nTexIdx);
		}
		else
		{ // �|�C���^���@NULL �̏ꍇ

			// ��~
			assert(false);

			// ���s��Ԃ�
			return E_FAIL;
		}
	}

	// �^�C���̓_�𐶐�����
	m_pDot = CObject2D::Create(CObject2D::TYPE_NONE, CObject::TYPE_NONE, CObject::PRIORITY_UI);

	if (m_pDot != nullptr &&
		CManager::Get()->GetTexture() != nullptr)
	{ // �^�C���̓_�� NULL ����Ȃ����A�e�N�X�`���� NULL ����Ȃ��ꍇ

		// �e�N�X�`���̊��蓖�ď���
		m_pDot->BindTexture(CManager::Get()->GetTexture()->Regist(TIMEDOT_TEXTURE));
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

//========================
// �I������
//========================
void CTime::Uninit(void)
{
	// �S�Ă̒l������������
	for (int nCnt = 0; nCnt < MAX_TIME_DIGIT; nCnt++)
	{
		if (m_apNumber[nCnt] != nullptr)
		{ // ���Ԃ̃|�C���^�� NULL ����Ȃ��ꍇ

			// �I������
			m_apNumber[nCnt]->Uninit();
			m_apNumber[nCnt] = nullptr;
		}
	}

	if (m_pDot != nullptr)
	{ // �_�̏�� NULL ����Ȃ��ꍇ

		// �^�C���̓_�̏I������
		m_pDot->Uninit();
		m_pDot = nullptr;
	}

	// �����̏I������
	Release();
}

//========================
// �X�V����
//========================
void CTime::Update(void)
{
	// 1�����Ƃ̐��l�ݒ菈��
	SetNumber();
}

//========================
// �`�揈��
//========================
void CTime::Draw(void)
{
	// �S�Ă̒l������������
	for (int nCnt = 0; nCnt < MAX_TIME_DIGIT; nCnt++)
	{
		if (m_apNumber[nCnt] != nullptr)
		{ // �ԍ��̃|�C���^�� NULL ����Ȃ��ꍇ

			// �`�揈��
			m_apNumber[nCnt]->Draw();
		}
	}

	if (m_pDot != nullptr)
	{ // �^�C���̓_�� NULL ����Ȃ��ꍇ

		// �`�揈��
		m_pDot->Draw();
	}
}

//========================
// ���̐ݒ菈��
//========================
void CTime::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& size, const D3DXVECTOR3& dotSize, const float fShift)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 Numberpos;		// �ԍ��̈ʒu

	for (int nCnt = 0; nCnt < MAX_TIME_DIGIT; nCnt++)
	{
		if (nCnt == TIMEDOT_COUNT)
		{ // �_��ł����ރJ�E���g�̏ꍇ

			// �_�̈ʒu��ݒ肷��
			Numberpos.x = pos.x + (nCnt * fShift) - size.x - (dotSize.x * 0.5f);
			Numberpos.y = pos.y + size.y - dotSize.y;
			Numberpos.z = 0.0f;

			// ����ݒ肷��
			m_pDot->SetPos(Numberpos);		// �ʒu
			m_pDot->SetRot(rot);			// ����
			m_pDot->SetSize(dotSize);		// �T�C�Y
			m_pDot->SetAngle();				// ����
			m_pDot->SetLength();			// ����

			// ���_���̐ݒ菈��
			m_pDot->SetVertex();
		}

		// �ԍ��̈ʒu��ݒ肷��
		Numberpos.x = pos.x + (nCnt * fShift);
		Numberpos.y = pos.y;
		Numberpos.z = 0.0f;

		if (m_apNumber[nCnt] != nullptr)
		{ // �ԍ��̃|�C���^�� NULL ����Ȃ��ꍇ

			// �ݒ菈��
			m_apNumber[nCnt]->SetPos(Numberpos);		// �ʒu�ݒ�
			m_apNumber[nCnt]->SetRot(rot);				// �����ݒ�
			m_apNumber[nCnt]->SetSize(size);			// �T�C�Y�ݒ�
			m_apNumber[nCnt]->SetLength();				// �����ݒ�
			m_apNumber[nCnt]->SetAngle();				// �����ݒ�

			m_apNumber[nCnt]->SetType(CNumber::TYPE_TIME);		// �ԍ��̎��
			m_apNumber[nCnt]->SetNumber(0);				// �ԍ���ݒ肷��

			// ���_���̐ݒ菈��
			m_apNumber[nCnt]->SetVertex();

			// �e�N�X�`���̐ݒ菈��(�A�j���[�V�����o�[�W����)
			m_apNumber[nCnt]->SetVtxTextureAnim(NUMBER_TEXTURE_PATTERN, 0);
		}
	}
}

//========================
// 1�����Ƃ̐��l�ݒ菈��
//========================
void CTime::SetNumber(void)
{
	// ���[�J���ϐ��錾
	int aNum[MAX_TIME_DIGIT];		// ����

	// 10�i���ւ̕ϊ�����
	useful::DecimalCalculation(MAX_TIME_DIGIT, m_TotalTime, &aNum[0]);

	for (int nCnt = 0; nCnt < MAX_TIME_DIGIT; nCnt++)
	{
		// �l��ݒ肷��
		m_apNumber[nCnt]->SetNumber(aNum[nCnt]);
	}
}

//========================
// 1�����Ƃ̃e�N�X�`���̐ݒ菈��
//========================
void CTime::SetTexture(void)
{
	for (int nCnt = 0; nCnt < MAX_TIME_DIGIT; nCnt++)
	{
		// �e�N�X�`�����W�̐ݒ菈��
		m_apNumber[nCnt]->SetVtxTextureAnim(NUMBER_TEXTURE_PATTERN, m_apNumber[nCnt]->GetNumber());
	}
}

//========================
// �o�ߎ��Ԃ̐ݒ菈��
//========================
void CTime::SetTotalTime(const DWORD time)
{
	// �o�ߎ��Ԃ�ݒ肷��
	m_TotalTime = time;
}

//========================
// �o�ߎ��Ԃ̎擾����
//========================
DWORD CTime::GetTotalTime(void) const
{
	// �o�ߎ��Ԃ�Ԃ�
	return m_TotalTime;
}

//========================
// �ԍ����̎擾����
//========================
CNumber* CTime::GetNumber(const int nID)
{
	// �ԍ��̏���Ԃ�
	return m_apNumber[nID];
}

//========================
// �_�̎擾����
//========================
CObject2D* CTime::GetDot(void)
{
	// �_�̏����擾����
	return m_pDot;
}

//========================
// ��������
//========================
CTime* CTime::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& size, const D3DXVECTOR3& dotSize, const float fShift)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CTime* pTime = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pTime == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pTime = new CTime;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pTime != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pTime->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pTime->SetData(pos, rot, size, dotSize, fShift);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �I�u�W�F�N�g2D�̃|�C���^��Ԃ�
	return pTime;
}