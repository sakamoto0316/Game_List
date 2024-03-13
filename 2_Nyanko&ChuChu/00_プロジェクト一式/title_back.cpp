//=======================================
//
// �^�C�g���̔w�i�̃��C������[title_back.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "title_back.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

//=======================================
// �}�N����`
//=======================================
#define BACK_POS		(D3DXVECTOR3(0.0f, 300.0f, 600.0f))		// �w�i�̈ʒu
#define BACK_SIZE		(D3DXVECTOR3(1000.0f, 1000.0f, 0.0f))	// �w�i�̃T�C�Y
#define BACK_TEXTURE	"data\\TEXTURE\\wall001.png"			// �������e�N�X�`��

//=========================
// �R���X�g���N�^
//=========================
CTitleBack::CTitleBack() : CObject3D(CObject::TYPE_MAP, CObject::PRIORITY_BG)
{

}

//=========================
// �f�X�g���N�^
//=========================
CTitleBack::~CTitleBack()
{

}

//=========================
// ����������
//=========================
HRESULT CTitleBack::Init(void)
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
void CTitleBack::Uninit(void)
{
	// �I��
	CObject3D::Uninit();
}

//=========================
// �X�V����
//=========================
void CTitleBack::Update(void)
{
	
}

//=========================
// �`�揈��
//=========================
void CTitleBack::Draw(void)
{
	// �`�揈��
	CObject3D::DrawLightOff();
}

//=========================
// ���̐ݒ菈��
//=========================
void CTitleBack::SetData(void)
{
	// ���̐ݒ菈��
	SetPos(BACK_POS);			// �ʒu
	SetPosOld(BACK_POS);		// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);	// ����
	SetSize(BACK_SIZE);			// �T�C�Y�ݒ�

	// ���_���̏�����
	SetVertex();

	// �e�N�X�`���̓ǂݍ��ݏ���
	BindTexture(CManager::Get()->GetTexture()->Regist(BACK_TEXTURE));
}

//=========================
// ��������
//=========================
CTitleBack* CTitleBack::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CTitleBack* pBack = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pBack == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pBack = new CTitleBack;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pBack != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pBack->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pBack->SetData();
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �w�i�̃|�C���^��Ԃ�
	return pBack;
}