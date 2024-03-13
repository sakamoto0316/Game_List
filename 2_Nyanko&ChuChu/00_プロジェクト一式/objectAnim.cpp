//============================================
//
// �A�j���[�V�����̃��C������[anim.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "objectAnim.h"
#include "renderer.h"
#include "manager.h"

//===========================================
// �R���X�g���N�^
//===========================================
CAnim::CAnim() : CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_BG)
{
	// �R���X�g���N�^�̔�
	Box();
}

//===========================================
// �I�[�o�[���[�h�R���X�g���N�^
//===========================================
CAnim::CAnim(CObject::TYPE type, PRIORITY priority) : CObject2D(type, priority)
{
	// �R���X�g���N�^�̔�
	Box();
}

//===========================================
// �f�X�g���N�^
//===========================================
CAnim::~CAnim()
{

}

//===========================================
// �R���X�g���N�^�̔�
//===========================================
void CAnim::Box(void)
{
	// �S�Ă̒l���N���A����
	m_nCounter = 0;				// �A�j���[�V�����J�E���^�[
	m_nPattern = 0;				// �A�j���[�V�����p�^�[��
	m_nReplayCount = 0;			// �Đ��J�E���g
	m_nReplayPattern = 0;		// �Đ��p�^�[��
	m_fTexPattern = 0.0f;		// �Đ��p�^�[��
}

//===========================================
// ����������
//===========================================
HRESULT CAnim::Init(void)
{
	if (FAILED(CObject2D::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_nCounter = 0;				// �A�j���[�V�����J�E���^�[
	m_nPattern = 0;				// �A�j���[�V�����p�^�[��
	m_nReplayCount = 0;				// �Đ��J�E���g
	m_nReplayPattern = 0;			// �Đ��p�^�[��
	m_fTexPattern = 0.0f;			// �e�N�X�`���̍Đ��p�^�[��

	// ������Ԃ�
	return S_OK;
}

//===========================================
// �I������
//===========================================
void CAnim::Uninit(void)
{
	// �I��
	CObject2D::Uninit();
}

//===========================================
// �X�V����
//===========================================
void CAnim::Update(void)
{
	// �J�E���g�����Z����
	m_nReplayCount++;

	if (m_nReplayCount % m_nCounter == 0)
	{ // �J�E���g���K��l�ɒB�����ꍇ

		// �Đ��J�E���g��0�ɂ���
		m_nReplayCount = 0;

		// �p�^�[�������ړ�����
		m_nReplayPattern = (m_nReplayPattern + 1) % m_nPattern;
	}

	// ���_���̐ݒ菈��
	SetVertexRot();

	// �e�N�X�`���̐ݒ菈��(�A�j���[�V�����o�[�W����)
	SetVtxTextureAnim(m_fTexPattern, m_nReplayPattern);
}

//===========================================
// �`�揈��
//===========================================
void CAnim::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();
}

//===========================================
// �p�^�[���̎擾����
//===========================================
int CAnim::GetPattern(void) const
{
	// ���݂̃p�^�[����Ԃ�
	return m_nReplayPattern;
}

//===========================================
// �e�N�X�`���̃p�^�[���̎擾����
//===========================================
float CAnim::GetTexPattern(void) const
{
	// �e�N�X�`���̃p�^�[����Ԃ�
	return m_fTexPattern;
}

//===========================================
// �A�j���[�V�����̐ݒ菈��
//===========================================
void CAnim::SetAnim(const int nCount, const int nPattern)
{
	// ����ݒ肷��
	m_nCounter = nCount;			// �A�j���[�V�����J�E���^�[
	m_nPattern = nPattern;			// �A�j���[�V�����p�^�[��
	m_fTexPattern = 1.0f / nPattern;	// �e�N�X�`���̍Đ��p�^�[��
}

//===========================================
// �A�j���[�V�����̐�������
//===========================================
CAnim* CAnim::Create(const CObject::TYPE type, const PRIORITY priority)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CAnim* pAnim = nullptr;	// �I�u�W�F�N�g2D�̃C���X�^���X�𐶐�

	if (pAnim == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pAnim = new CAnim(type, priority);
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pAnim != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pAnim->Init()))
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

	// �A�j���[�V�����̃|�C���^��Ԃ�
	return pAnim;
}