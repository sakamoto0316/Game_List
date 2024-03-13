//===========================================
//
// ��@�̃t�@���̃��C������[fan_blade.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "fan_blade.h"
#include "useful.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define ROT_MOVE_CORRECT		(0.01f)		// �����̈ړ��ʂ̕␳��

//==============================
// �R���X�g���N�^
//==============================
CFanBlade::CFanBlade() : CModel(CObject::TYPE_NONE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	m_fRotMove = 0.0f;			// �����̈ړ���
	m_fRotMoveDest = 0.0f;		// �ړI�̌����̈ړ���
}

//==============================
// �f�X�g���N�^
//==============================
CFanBlade::~CFanBlade()
{

}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CFanBlade::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l���N���A����
	m_fRotMove = 0.0f;			// �����̈ړ���
	m_fRotMoveDest = 0.0f;		// �ړI�̌����̈ړ���

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �j�Ђ̏I������
//========================================
void CFanBlade::Uninit(void)
{
	// �I������
	CModel::Uninit();
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CFanBlade::Update(void)
{
	// �������擾����
	D3DXVECTOR3 rot = GetRot();

	// �����̕␳����
	useful::RotCorrect(m_fRotMoveDest, &m_fRotMove, ROT_MOVE_CORRECT);

	// ���������Z����
	rot.z += m_fRotMove;

	// ������K�p����
	SetRot(rot);
}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CFanBlade::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CFanBlade::Draw(const float fAlpha)
{
	// �`�揈��
	CModel::Draw(fAlpha);
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CFanBlade::SetData(const D3DXVECTOR3& pos)
{
	// ���̐ݒ菈��
	SetPos(pos);								// �ʒu
	SetPosOld(pos);								// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);					// ����
	SetScale(NONE_SCALE);						// �g�嗦
	SetFileData(CXFile::TYPE_FANBLADE);			// ���f�����
}

//=======================================
// ��������
//=======================================
CFanBlade* CFanBlade::Create(const D3DXVECTOR3& pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CFanBlade* pFanBlade = nullptr;	// �C���X�^���X�𐶐�

	if (pFanBlade == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �C���X�^���X�𐶐�
		pFanBlade = new CFanBlade;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pFanBlade != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pFanBlade->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pFanBlade->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// ��@�̃t�@���̃|�C���^��Ԃ�
	return pFanBlade;
}

//=======================================
// �ړI�̌����̈ړ��ʂ̐ݒ菈��
//=======================================
void CFanBlade::SetRotMoveDest(const float fRotMove)
{
	// �ړI�̌����̈ړ��ʂ�ݒ肷��
	m_fRotMoveDest = fRotMove;
}