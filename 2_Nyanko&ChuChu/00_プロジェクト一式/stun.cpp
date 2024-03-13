//============================================
//
// �C�≉�o�̏���[stun.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "stun.h"
#include "objectbillboard.h"
#include "texture.h"
#include "useful.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define STUN_SIZE				(D3DXVECTOR3(10.0f, 10.0f, 0.0f))	// �C�≉�o�̃T�C�Y
#define STUN_TEXTURE			"data\\TEXTURE\\Stun.png"			// �C�≉�o�̃e�N�X�`��
#define STUN_SHIFT_ROT			((float)((D3DX_PI * 2) / 4))		// �C�≉�o�̂��炷���̌���
#define STUN_SHIFT_WIDTH		(30.0f)								// �C�≉�o�̂��炷��
#define STUN_ADD_ROT			(0.1f)								// �C�≉�o�̌����̉��Z��

//========================
// �R���X�g���N�^
//========================
CStun::CStun() : CObject(CObject::TYPE_STUN, CObject::PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
	m_pos = NONE_D3DXVECTOR3;		// �ʒu
	m_fRot = 0.0f;					// ��]�p�̌���
	for (int nCntUI = 0; nCntUI < MAX_STUN; nCntUI++)
	{
		m_apStun[nCntUI] = nullptr;
	}
}

//========================
// �f�X�g���N�^
//========================
CStun::~CStun()
{

}

//========================
// ����������
//========================
HRESULT CStun::Init(void)
{
	// ���������m�ۂ���
	for (int nCnt = 0; nCnt < MAX_STUN; nCnt++)
	{
		if (m_apStun[nCnt] == nullptr)
		{ // �|�C���^�� NULL �̏ꍇ

			// ���������m�ۂ���
			m_apStun[nCnt] = new CBillboard(CObject::TYPE_NONE, CObject::PRIORITY_ENTITY);
		}
		else
		{ // �|�C���^�� NULL ����Ȃ��ꍇ

			// ��~
			assert(false);

			// ���s��Ԃ�
			return E_FAIL;
		}

		if (m_apStun[nCnt] != nullptr)
		{ // �|�C���^�� NULL ����Ȃ��ꍇ

			// ����������
			if (FAILED(m_apStun[nCnt]->Init()))
			{ // �����������Ɏ��s�����ꍇ

				// ��~
				assert(false);

				// ���s��Ԃ�
				return E_FAIL;
			}

			// �e�N�X�`���̊��蓖�ď���
			m_apStun[nCnt]->BindTexture(CManager::Get()->GetTexture()->Regist(STUN_TEXTURE));
		}
		else
		{ // �|�C���^���@NULL �̏ꍇ

			// ��~
			assert(false);

			// ���s��Ԃ�
			return E_FAIL;
		}
	}

	// �S�Ă̒l������������
	m_pos = NONE_D3DXVECTOR3;		// �ʒu
	m_fRot = 0.0f;					// ��]�p�̌���

	// ������Ԃ�
	return S_OK;
}

//========================
// �I������
//========================
void CStun::Uninit(void)
{
	// �S�Ă̒l������������
	for (int nCnt = 0; nCnt < MAX_STUN; nCnt++)
	{
		if (m_apStun[nCnt] != nullptr)
		{ // �\��UI�� NULL ����Ȃ��ꍇ

			// �I������
			m_apStun[nCnt]->Uninit();
			m_apStun[nCnt] = nullptr;
		}
	}

	// �{�̂̏I������
	Release();
}

//========================
// �X�V����
//========================
void CStun::Update(void)
{
	// ���������Z����
	m_fRot += STUN_ADD_ROT;

	// �����̐��K������
	useful::RotNormalize(&m_fRot);

	// ���[�J���ϐ��錾
	D3DXVECTOR3 posCorrect;		// �␳��̈ʒu
	float fRot;					// ����

	for (int nCnt = 0; nCnt < MAX_STUN; nCnt++)
	{
		if (m_apStun[nCnt] != nullptr)
		{ // �ԍ��̃|�C���^�� NULL ����Ȃ��ꍇ

			// ������ݒ肷��
			fRot = m_fRot + STUN_SHIFT_ROT * (nCnt);

			// �����̐��K������
			useful::RotNormalize(&fRot);

			// �␳�p�̈ʒu��ݒ肷��
			posCorrect.x = sinf(fRot) * STUN_SHIFT_WIDTH;
			posCorrect.y = 0.0f;
			posCorrect.z = cosf(fRot) * STUN_SHIFT_WIDTH;

			// �ʒu��ݒ肷��
			m_apStun[nCnt]->SetPos(m_pos + posCorrect);

			// ���_���̐ݒ菈��
			m_apStun[nCnt]->SetVertex();
		}
	}
}

//========================
// �`�揈��
//========================
void CStun::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_STUN; nCnt++)
	{
		if (m_apStun[nCnt] != nullptr)
		{ // ��� NULL ����Ȃ��ꍇ

			// �`�揈��
			m_apStun[nCnt]->DrawLightOff();
		}
	}
}

//========================
// ���̐ݒ菈��
//========================
void CStun::SetData(const D3DXVECTOR3 pos)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 posCorrect;		// �␳��̈ʒu
	float fRot;					// ����

	// �S�Ă̒l��ݒ肷��
	m_pos = pos;		// �ʒu��ݒ肷��
	m_fRot = 0.0f;		// ��]�p�̌���

	for (int nCnt = 0; nCnt < MAX_STUN; nCnt++)
	{
		// ������ݒ肷��
		fRot = STUN_SHIFT_ROT * (nCnt);

		// �����̐��K������
		useful::RotNormalize(&fRot);

		// �␳�p�̈ʒu��ݒ肷��
		posCorrect.x = sinf(fRot) * STUN_SHIFT_WIDTH;
		posCorrect.y = 0.0f;
		posCorrect.z = cosf(fRot) * STUN_SHIFT_WIDTH;

		if (m_apStun[nCnt] != nullptr)
		{ // �ԍ��̃|�C���^�� NULL ����Ȃ��ꍇ

			// ����ݒ肷��
			m_apStun[nCnt]->SetPos(m_pos + posCorrect);	// �ʒu�ݒ�
			m_apStun[nCnt]->SetSize(STUN_SIZE);			// �T�C�Y�ݒ�

			// ���_���̐ݒ菈��
			m_apStun[nCnt]->SetVertex();
		}
	}
}

//========================
// �ʒu�̐ݒ菈��
//========================
void CStun::SetPos(const D3DXVECTOR3& pos)
{
	// �ʒu��ݒ肷��
	m_pos = pos;
}

//========================
// ��������
//========================
CStun* CStun::Create(const D3DXVECTOR3 pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CStun* pStun = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pStun == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pStun = new CStun;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pStun != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pStun->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pStun->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �C�≉�o�̃|�C���^��Ԃ�
	return pStun;
}