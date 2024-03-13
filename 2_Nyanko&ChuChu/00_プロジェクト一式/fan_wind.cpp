//=======================================
//
// ��@�̕�����[fan_wind.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "fan_wind.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

//=========================
// �R���X�g���N�^
//=========================
CFanWind::CFanWind() : CObject3D(CObject::TYPE_NONE, CObject::PRIORITY_BLOCK)
{

}

//=========================
// �f�X�g���N�^
//=========================
CFanWind::~CFanWind()
{

}

//=========================
// ����������
//=========================
HRESULT CFanWind::Init(void)
{
	if (FAILED(CObject3D::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//=========================
// �I������
//=========================
void CFanWind::Uninit(void)
{
	// �I��
	CObject3D::Uninit();
}

//=========================
// �X�V����
//=========================
void CFanWind::Update(void)
{

}

//=========================
// �`�揈��
//=========================
void CFanWind::Draw(void)
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
void CFanWind::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
	// �X�N���[���̐ݒ菈��
	SetPos(pos);					// �ʒu�ݒ�
	SetPosOld(pos);					// �O��̈ʒu�ݒ�
	SetRot(NONE_D3DXVECTOR3);		// �����ݒ�
	SetSize(size);					// �T�C�Y�ݒ�

	// ���_���W�̐ݒ菈��
	SetVertex();
}

//=========================
// ��������
//=========================
CFanWind* CFanWind::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CFanWind* pWind = nullptr;		// ���̃C���X�^���X�𐶐�

	if (pWind == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pWind = new CFanWind;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pWind != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pWind->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pWind->SetData(pos, size);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// ��@�̕��̃|�C���^��Ԃ�
	return pWind;
}