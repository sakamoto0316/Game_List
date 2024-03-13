//===========================================
//
// �G���g���[��ʂ̃����_���w������[entry_rand.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "entry_rand.h"
#include "manager.h"
#include "texture.h"

//-------------------------------------------
// �������O���
//-------------------------------------------
namespace
{
	const D3DXVECTOR3 RAND_POS = D3DXVECTOR3(1150.0f, 680.0f, 0.0f);	// �ʒu
	const D3DXVECTOR3 RAND_SIZE = D3DXVECTOR3(120.0f, 30.0f, 0.0f);		// �T�C�Y
	const char* RAND_TEXTURE = "data\\TEXTURE\\entry_random.png";		// �e�N�X�`���̖��O
}

//==============================
// �R���X�g���N�^
//==============================
CEntryRandom::CEntryRandom() : CObject2D(CObject::TYPE_ENTRYRANDOM, CObject::PRIORITY_UI)
{

}

//==============================
// �f�X�g���N�^
//==============================
CEntryRandom::~CEntryRandom()
{

}

//==============================
// �G���g���[��ʂ̑�������̏���������
//==============================
HRESULT CEntryRandom::Init(void)
{
	if (FAILED(CObject2D::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �G���g���[��ʂ̑�������̏I������
//========================================
void CEntryRandom::Uninit(void)
{
	// �I������
	CObject2D::Uninit();
}

//=====================================
// �G���g���[��ʂ̑�������̍X�V����
//=====================================
void CEntryRandom::Update(void)
{

}

//=====================================
// �G���g���[��ʂ̑�������̕`�揈��
//=====================================
void CEntryRandom::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CEntryRandom::SetData(void)
{
	// ���̐ݒ菈��
	SetPos(RAND_POS);			// �ʒu
	SetPosOld(RAND_POS);		// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);	// ����
	SetSize(RAND_SIZE);			// �T�C�Y
	SetLength();				// ����
	SetAngle();					// ����
	BindTexture(CManager::Get()->GetTexture()->Regist(RAND_TEXTURE));		// �e�N�X�`���̊��蓖�ď���

	// ���_���W�̐ݒ菈��
	SetVertex();
}

//=======================================
// ��������
//=======================================
CEntryRandom* CEntryRandom::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CEntryRandom* pEntryRandom = nullptr;		// UI�̃C���X�^���X�𐶐�

	if (pEntryRandom == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �C���X�^���X�𐶐�
		pEntryRandom = new CEntryRandom;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pEntryRandom != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pEntryRandom->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pEntryRandom->SetData();
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// UI�̃|�C���^��Ԃ�
	return pEntryRandom;
}