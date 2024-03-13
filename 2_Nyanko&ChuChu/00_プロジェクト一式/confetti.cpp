//=======================================
//
// �����Ꮘ��[confetti.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "confetti.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

//=======================================
// �}�N����`
//=======================================

//=========================
// �R���X�g���N�^
//=========================
CConfetti::CConfetti() : CObject3D(CObject::TYPE_CONFETTI, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	m_rotMove = NONE_D3DXVECTOR3;		// �����̈ړ���
	m_nLife = 0;						// ����
	m_fGravity = 0.0f;					// �d��
}

//=========================
// �f�X�g���N�^
//=========================
CConfetti::~CConfetti()
{

}

//=========================
// ����������
//=========================
HRESULT CConfetti::Init(void)
{
	if (FAILED(CObject3D::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_rotMove = NONE_D3DXVECTOR3;		// �����̈ړ���
	m_nLife = 0;						// ����
	m_fGravity = 0.0f;					// �d��

	// ������Ԃ�
	return S_OK;
}

//=========================
// �I������
//=========================
void CConfetti::Uninit(void)
{
	// �I��
	CObject3D::Uninit();
}

//=========================
// �X�V����
//=========================
void CConfetti::Update(void)
{
	// �������擾����
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	// �ʒu��������
	pos.y -= m_fGravity;

	// ���������Z����
	rot += m_rotMove;

	// �����̐��K��
	useful::RotNormalize(&rot.x);
	useful::RotNormalize(&rot.y);
	useful::RotNormalize(&rot.z);

	// ������ݒ肷��
	SetPos(pos);
	SetRot(rot);

	// ���������Z����
	m_nLife--;

	if (m_nLife <= 0)
	{ // ������0�ȉ��̏ꍇ

		// �I������
		Uninit();

		// ���̐�̏������s��Ȃ�
		return;
	}

	// ���_���W�̐ݒ菈��
	SetVertex();
}

//=========================
// �`�揈��
//=========================
void CConfetti::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	// �J�����O�̐ݒ��OFF�ɂ���
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// �`�揈��
	CObject3D::DrawLightOff();

	// �J�����O�̐ݒ��ON�ɂ���
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//=========================
// ���̐ݒ菈��
//=========================
void CConfetti::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const D3DXVECTOR3& rotMove, const float fGravity, const D3DXCOLOR& col, const int nLife)
{
	// �X�N���[���̐ݒ菈��
	SetPos(pos);					// �ʒu�ݒ�
	SetPosOld(pos);					// �ʒu�ݒ�
	SetRot(NONE_D3DXVECTOR3);		// �����ݒ�
	SetSize(size);					// �T�C�Y�ݒ�

	// �S�Ă̒l��ݒ肷��
	m_rotMove = rotMove;		// �����̈ړ���
	m_nLife = nLife;			// ����
	m_fGravity = fGravity;		// �d��

	// ���_���W�̐ݒ菈��
	SetVertex();

	// ���_�J���[�̐ݒ菈��
	SetVtxColor(col);
}

//=========================
// ��������
//=========================
CConfetti* CConfetti::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const D3DXVECTOR3& rotMove, const float fGravity, const D3DXCOLOR& col, const int nLife)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CConfetti* pConfetti = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pConfetti == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pConfetti = new CConfetti;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pConfetti != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pConfetti->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pConfetti->SetData(pos, size, rotMove, fGravity, col, nLife);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// ������̃|�C���^��Ԃ�
	return pConfetti;
}