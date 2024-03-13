//===========================================
//
// �l�Y�~�߂�̓S�����̃��C������[mousetrap_iron.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "mousetrap_iron.h"
#include "renderer.h"
#include "useful.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define ROT_MOVE	(0.3f)		// �����̈ړ���

//==============================
// �R���X�g���N�^
//==============================
CTrapIron::CTrapIron() : CModel(CObject::TYPE_NONE, CObject::PRIORITY_BLOCK)
{

}

//==============================
// �f�X�g���N�^
//==============================
CTrapIron::~CTrapIron()
{

}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CTrapIron::Init(void)
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
void CTrapIron::Uninit(void)
{
	// �I������
	CModel::Uninit();
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CTrapIron::Update(void)
{

}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CTrapIron::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CTrapIron::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// ���̐ݒ菈��
	SetPos(pos);								// �ʒu
	SetPosOld(pos);								// �O��̈ʒu
	SetRot(rot);								// ����
	SetScale(NONE_SCALE);						// �g�嗦
	SetFileData(CXFile::TYPE_TRAPIRON);			// ���f�����
}

//=======================================
// ��������
//=======================================
CTrapIron* CTrapIron::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CTrapIron* pIron = nullptr;	// �C���X�^���X�𐶐�

	if (pIron == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �C���X�^���X�𐶐�
		pIron = new CTrapIron;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pIron != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pIron->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pIron->SetData(pos, rot);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �l�Y�~�߂�̓S�����̃|�C���^��Ԃ�
	return pIron;
}

//=======================================
// �ړ�����
//=======================================
bool CTrapIron::Move(void)
{
	// �������擾����
	D3DXVECTOR3 rot = GetRot();

	// ���������Z����
	rot.z += ROT_MOVE;

	if (rot.z >= D3DX_PI)
	{ // ��������萔�̏ꍇ

		// �����̐��K��
		useful::RotNormalize(&rot.z);

		// ������K�p����
		SetRot(rot);

		// true ��Ԃ�
		return true;
	}
	else
	{ // ��L�ȊO

		// �����̐��K��
		useful::RotNormalize(&rot.z);

		// ������K�p����
		SetRot(rot);

		// false ��Ԃ�
		return false;
	}
}