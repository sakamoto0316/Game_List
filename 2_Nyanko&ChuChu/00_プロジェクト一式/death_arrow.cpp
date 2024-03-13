//===========================================
//
// ���S���̃��C������[death_arrow.cpp]
// Author ����������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "death_arrow.h"
#include "objectX.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------

//-------------------------------------------
// �ÓI�����o�ϐ��錾
//-------------------------------------------

//==============================
// �R���X�g���N�^
//==============================
CDeathArrow::CDeathArrow() : CModel(CObject::TYPE_DEATHARROW, CObject::PRIORITY_PLAYER)
{
	// �S�Ă̒l���N���A����
	m_pos = NONE_D3DXVECTOR3;		// �ʒu
	m_rot = NONE_D3DXVECTOR3;		// ����
	m_nPlayerIdx = -1;
}

//==============================
// �f�X�g���N�^
//==============================
CDeathArrow::~CDeathArrow()
{

}

//==============================
// ���S���̏���������
//==============================
HRESULT CDeathArrow::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_pos = NONE_D3DXVECTOR3;		// �ʒu
	m_rot = NONE_D3DXVECTOR3;		// ����

	// �l��Ԃ�
	return S_OK;
}

//========================================
// ���S���̏I������
//========================================
void CDeathArrow::Uninit(void)
{
	// �I������
	CModel::Uninit();
}

//=====================================
// ���S���̍X�V����
//=====================================
void CDeathArrow::Update(void)
{

}

//=====================================
// ���S���̕`�揈��
//=====================================
void CDeathArrow::Draw(void)
{
	if (m_nPlayerIdx == CObject::GetDrawIdx())
	{
		// �`�揈��
		CModel::Draw();
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CDeathArrow::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& rot, const int nIdx)
{
	// �ݒ菈���ɕ֗��ȃ}�N����`
	//NONE_D3DXVECTOR3					// �������X���Ȃ����Ƃ��Ɏg�p����
	//NONE_SCALE						// �g�嗦��ύX���Ȃ��Ƃ��Ƃ��Ɏg��

	// ���̐ݒ菈��
	SetPos(pos);					// �ʒu
	SetPosOld(posOld);				// �O��̈ʒu
	SetRot(rot);					// ����
	SetScale(NONE_SCALE);			// �g�嗦
	SetFileData(CXFile::TYPE_DEATHARROW);	// ���f���̏��
	m_nPlayerIdx = nIdx;
}

//=======================================
// ��������
//=======================================
CDeathArrow* CDeathArrow::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& rot, const int nIdx)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CDeathArrow* pDeathArrow = nullptr;	// ���S���̃C���X�^���X�𐶐�

	if (pDeathArrow == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �C���X�^���X�𐶐�
		pDeathArrow = new CDeathArrow;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pDeathArrow != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pDeathArrow->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pDeathArrow->SetData(pos, posOld, rot, nIdx);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �T���v���̃|�C���^��Ԃ�
	return pDeathArrow;
}