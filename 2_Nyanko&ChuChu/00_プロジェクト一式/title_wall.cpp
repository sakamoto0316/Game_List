//===========================================
//
// �^�C�g���̕ǂ̃��C������[title_wall.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "title_wall.h"

//==============================
// �R���X�g���N�^
//==============================
CTitleWall::CTitleWall() : CModel(CObject::TYPE_TITLEWALL, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
}

//==============================
// �f�X�g���N�^
//==============================
CTitleWall::~CTitleWall()
{

}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CTitleWall::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �j�Ђ̏I������
//========================================
void CTitleWall::Uninit(void)
{
	// �I������
	CModel::Uninit();
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CTitleWall::Update(void)
{

}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CTitleWall::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CTitleWall::SetData(void)
{
	// ���̐ݒ菈��
	SetPos(NONE_D3DXVECTOR3);				// �ʒu
	SetPosOld(NONE_D3DXVECTOR3);			// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);				// ����
	SetScale(NONE_SCALE);					// �g�嗦
	SetFileData(CXFile::TYPE_TITLEWALL);	// ���f�����
}

//=======================================
// ��������
//=======================================
CTitleWall* CTitleWall::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CTitleWall* pTitle = nullptr;	// �C���X�^���X�𐶐�

	if (pTitle == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �C���X�^���X�𐶐�
		pTitle = new CTitleWall;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pTitle != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pTitle->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pTitle->SetData();
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �^�C�g���̕ǂ̃|�C���^��Ԃ�
	return pTitle;
}