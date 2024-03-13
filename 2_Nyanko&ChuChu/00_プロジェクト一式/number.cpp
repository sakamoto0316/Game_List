//============================================
//
// ���l����[number.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "renderer.h"
#include "number.h"

//============================
// �R���X�g���N�^
//============================
CNumber::CNumber() : CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_BG)
{
	// �R���X�g���N�^�̔�
	Box();
}

//============================
// �I�[�o�[���[�h�R���X�g���N�^
//============================
CNumber::CNumber(CObject::TYPE type, CObject::PRIORITY priority) : CObject2D(type, priority)
{
	// �R���X�g���N�^�̔�
	Box();
}

//============================
// �f�X�g���N�^
//============================
CNumber::~CNumber()
{

}

//============================
// �R���X�g���N�^�̔�
//============================
void CNumber::Box(void)
{
	// �S�Ă̒l���N���A����
	m_nNumber = 0;			// ���l
	m_type = TYPE_DECIMAL;	// ���
}

//============================
// ����������
//============================
HRESULT CNumber::Init(void)
{
	if (FAILED(CObject2D::Init()))
	{ // �������Ɏ��s�����ꍇ

	  // ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_nNumber = 0;			// �ԍ�
	m_type = TYPE_DECIMAL;	// ���

	// �X�N���[���̐ݒ菈��
	SetPos(D3DXVECTOR3(400.0f, 300.0f, 0.0f));		// �ʒu�ݒ�
	SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));			// �����ݒ�
	SetSize(D3DXVECTOR3(20.0f, 40.0f, 0.0f));		// �T�C�Y�ݒ�
	SetLength();				// �����ݒ�
	SetAngle();					// �����ݒ�

	// ���_���̏�����
	SetVertex();

	// �e�N�X�`�����̐ݒ菈��
	SetVtxTextureAnim(NUMBER_TEXTURE_PATTERN, m_nNumber);

	// ������Ԃ�
	return S_OK;
}

//============================
// �I������
//============================
void CNumber::Uninit(void)
{
	// �I��
	CObject2D::Uninit();
}

//============================
// �X�V����
//============================
void CNumber::Update(void)
{
	// ���_���̐ݒ菈��
	SetVertex();

	// �e�N�X�`�����̐ݒ菈��
	SetVtxTextureAnim(NUMBER_TEXTURE_PATTERN, m_nNumber);
}

//============================
// �`�揈��
//============================
void CNumber::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();
}

//============================
//��������
//============================
CNumber* CNumber::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CNumber* pNumber = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pNumber == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pNumber = new CNumber;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pNumber != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pNumber->Init()))
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

	// �I�u�W�F�N�g2D�̃|�C���^��Ԃ�
	return pNumber;
}

//============================
// ��ނ̐ݒ菈��
//============================
void CNumber::SetType(const TYPE type)
{
	// ��ނ�������
	m_type = type;
}

//============================
// ��ނ̎擾����
//============================
CNumber::TYPE CNumber::GetType(void) const
{
	// ��ނ�Ԃ�
	return m_type;
}

//============================
// �ԍ��̐ݒ菈��
//============================
void CNumber::SetNumber(const int nNum)
{
	// ���l��������
	m_nNumber = nNum;
}

//============================
// �ԍ��̎擾����
//============================
int CNumber::GetNumber(void) const
{
	// ���l��Ԃ�
	return m_nNumber;
}