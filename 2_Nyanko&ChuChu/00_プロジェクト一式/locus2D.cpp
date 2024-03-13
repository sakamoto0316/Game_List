//=======================================
//
// 2D�c���̃��C������[locus2D.cpp]
// Author ��������
//
//=======================================
#include "locus2D.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//---------------------------------------
// �}�N����`
//---------------------------------------

//=========================
// �R���X�g���N�^
//=========================
CLocus2D::CLocus2D() : CObject2D(CObject::TYPE_LOCUS, CObject::PRIORITY_PLAYER)
{
	// �S�Ă̒l���N���A����
	m_nLife = 0;			// ����
	m_fSub = 0.0f;			// �����x�̌�����
	m_fAlpha = 0.0f;		// �����x
}

//=========================
// �f�X�g���N�^
//=========================
CLocus2D::~CLocus2D()
{

}

//=========================
// ����������
//=========================
HRESULT CLocus2D::Init(void)
{
	if (FAILED(CObject2D::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_nLife = 0;			// ����
	m_fSub = 0.0f;			// �����x�̌�����
	m_fAlpha = 0.0f;		// �����x

	// ������Ԃ�
	return S_OK;
}

//=========================
// �I������
//=========================
void CLocus2D::Uninit(void)
{
	// �I��
	CObject2D::Uninit();
}

//=========================
// �X�V����
//=========================
void CLocus2D::Update(void)
{
	// ���������Z����
	m_nLife--;

	// �����x�����Z����
	m_fAlpha -= m_fSub;

	if (m_fAlpha <= 0.0f)
	{ // �����x�� 0.0f �ȉ��ɂȂ����ꍇ

		// �����x��␳����
		m_fAlpha = 0.0f;
	}

	if (m_nLife <= 0)
	{ // ������ 0 �ȉ��ɂȂ����ꍇ

		// �I������
		Uninit();

		// ���̐�̏������s��Ȃ�
		return;
	}

	// ���_���̏�����
	SetVertexRot();

	// ���_�J���[�̐ݒ菈��
	SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha));
}

//=========================
// �`�揈��
//=========================
void CLocus2D::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();
}
//=========================
// ���̐ݒ菈��
//=========================
void CLocus2D::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& size, const float fAlpha, const int nLife, const int nTexIdx)
{
	// �X�N���[���̐ݒ菈��
	SetPos(pos);			// �ʒu�ݒ�
	SetRot(rot);			// �����ݒ�
	SetSize(size);			// �T�C�Y�ݒ�
	SetLength();			// �����ݒ�
	SetAngle();				// �����ݒ�

	// �S�Ă̒l������������
	m_nLife = nLife;		// ����
	m_fSub = fAlpha / (float)(nLife);	// �����x�̌�����
	m_fAlpha = fAlpha;		// �����x

	// ���_���̏�����
	SetVertexRot();

	// �e�N�X�`�����̐ݒ菈��
	SetVtxTexture();

	// �e�N�X�`���̓ǂݍ��ݏ���
	BindTexture(nTexIdx);
}

//=========================
// ��������
//=========================
CLocus2D* CLocus2D::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& size, const float fAlpha, const int nLife, const int nTexIdx)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CLocus2D* pLocus2D = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pLocus2D == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pLocus2D = new CLocus2D;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pLocus2D != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pLocus2D->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pLocus2D->SetData(pos, rot, size, fAlpha, nLife, nTexIdx);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �I�u�W�F�N�g2D�̃|�C���^��Ԃ�
	return pLocus2D;
}