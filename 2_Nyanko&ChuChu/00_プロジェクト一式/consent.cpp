//===========================================
//
// �R���Z���g�̃��C������[consent.cpp]
// Author ��{�ėB
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "consent.h"
#include "useful.h"
#include "cup.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define NOTE_CYCLE_SPEED		(0.05f)		// ��鑬�x
#define NOTE_UD_HEIGHT		(100.0f)		// �㉺�ړ��̕�

//==============================
// �R���X�g���N�^
//==============================
CConsent::CConsent() : CModel(CObject::TYPE_NONE, CObject::PRIORITY_BLOCK)
{
	m_pMain = NULL;
	m_move = NONE_D3DXVECTOR3;
	m_nLife = 10;
}

//==============================
// �f�X�g���N�^
//==============================
CConsent::~CConsent()
{

}

//==============================
// �R���Z���g�̏���������
//==============================
HRESULT CConsent::Init(void)
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
// �R���Z���g�̏I������
//========================================
void CConsent::Uninit(void)
{
	//�{�̂ɂ��鎩�g�̃|�C���^�폜����
	m_pMain->NULLConsent();

	// �I������
	CModel::Uninit();
}

//=====================================
// �R���Z���g�̍X�V����
//=====================================
void CConsent::Update(void)
{
	// �ʒu�ƌ��������擾����
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	// �ʒu�X�V
	pos += m_move;

	// �ʒu�ƌ�����ݒ肷��
	SetPos(pos);
	SetRot(rot);
}

//=====================================
// �R���Z���g�̕`�揈��
//=====================================
void CConsent::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=====================================
// �R���Z���g�̕`�揈��
//=====================================
void CConsent::Draw(const float fAlpha)
{
	// �`�揈��
	CModel::Draw(fAlpha);
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CConsent::SetData(const D3DXVECTOR3& pos)
{
	// ���̐ݒ菈��
	SetPos(pos);								// �ʒu
	SetPosOld(pos);								// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);					// ����
	SetScale(NONE_SCALE);						// �g�嗦
	SetFileData(CXFile::TYPE_CONSENT);			// ���f�����
}

//=======================================
// ��������
//=======================================
CConsent* CConsent::Create(const D3DXVECTOR3& pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CConsent* pTarai = nullptr;	// �C���X�^���X�𐶐�

	if (pTarai == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

	  // �C���X�^���X�𐶐�
		pTarai = new CConsent;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

	  // ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pTarai != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

	  // ����������
		if (FAILED(pTarai->Init()))
		{ // �������Ɏ��s�����ꍇ

		  // ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pTarai->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

	  // ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// ���炢�̃M�A�̃|�C���^��Ԃ�
	return pTarai;
}