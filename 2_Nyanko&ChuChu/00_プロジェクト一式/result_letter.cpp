//===========================================
//
// ���ʂ̕����̏���[result_letter.h]
// Author ����������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "result_letter.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------

//-------------------------------------------
// �ÓI�����o�ϐ��錾
//-------------------------------------------

//==============================
// �R���X�g���N�^
//==============================
CResultLetter::CResultLetter() : CModel(CObject::TYPE_3DTEXT, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
}

//==============================
// �f�X�g���N�^
//==============================
CResultLetter::~CResultLetter()
{

}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CResultLetter::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �j�Ђ̏I������
//========================================
void CResultLetter::Uninit(void)
{
	// �I������
	CModel::Uninit();
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CResultLetter::Update(void)
{

}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CResultLetter::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CResultLetter::SetData(const D3DXVECTOR3& pos, const CXFile::TYPE& type)
{
	// �ݒ菈���ɕ֗��ȃ}�N����`
	//NONE_D3DXVECTOR3					// �������X���Ȃ����Ƃ��Ɏg�p����
	//NONE_SCALE						// �g�嗦��ύX���Ȃ��Ƃ��Ƃ��Ɏg��
	// ���̐ݒ菈��

	//==========================================================================
	// ���f��
	//==========================================================================
	SetPos(pos);					// �ʒu
	SetPosOld(GetPos());			// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);		// ����
	SetScale(NONE_SCALE);			// �g�嗦
	SetFileData(type);				// ���f���̏��
}

//=======================================
// ��������
//=======================================
CResultLetter* CResultLetter::Create(const D3DXVECTOR3& pos, const CXFile::TYPE& type)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CResultLetter* pResultLetter = nullptr;	// �T���v���̃C���X�^���X�𐶐�

	if (pResultLetter == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �C���X�^���X�𐶐�
		pResultLetter = new CResultLetter;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pResultLetter != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pResultLetter->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pResultLetter->SetData(pos, type);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �T���v���̃|�C���^��Ԃ�
	return pResultLetter;
}