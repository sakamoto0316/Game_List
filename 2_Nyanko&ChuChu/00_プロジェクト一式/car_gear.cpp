//===========================================
//
// ���Ԃ̃��C������[car_gear.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "car_gear.h"
#include "useful.h"
#include "sound.h"
#include "game.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define GEAR_CYCLE_SPEED		(0.1f)		// ��鑬�x

//==============================
// �R���X�g���N�^
//==============================
CCarGear::CCarGear() : CModel(CObject::TYPE_NONE, CObject::PRIORITY_BLOCK)
{
	m_bSe = false;		// SE�Đ���
}

//==============================
// �f�X�g���N�^
//==============================
CCarGear::~CCarGear()
{

}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CCarGear::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	m_bSe = false;		// SE�Đ���

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �j�Ђ̏I������
//========================================
void CCarGear::Uninit(void)
{
	// �I������
	CModel::Uninit();
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CCarGear::Update(void)
{
	// �������擾����
	D3DXVECTOR3 rot = GetRot();

	// ���������Z����
	rot.y += GEAR_CYCLE_SPEED;

	// �����̐��K��
	useful::RotNormalize(&rot.y);

	// ������ݒ肷��
	SetRot(rot);

	if (m_bSe == false && CGame::GetState() == CGame::STATE_PLAY)
	{
		// �˂��Đ�
		CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_NEZI);
		m_bSe = true;
	}
}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CCarGear::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CCarGear::SetData(const D3DXVECTOR3& pos)
{
	// ���̐ݒ菈��
	SetPos(pos);								// �ʒu
	SetPosOld(pos);								// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);					// ����
	SetScale(NONE_SCALE);						// �g�嗦
	SetFileData(CXFile::TYPE_TOYCARSCREW);		// ���f�����
}

//=======================================
// ��������
//=======================================
CCarGear* CCarGear::Create(const D3DXVECTOR3& pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CCarGear* pCarGear = nullptr;	// �C���X�^���X�𐶐�

	if (pCarGear == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �C���X�^���X�𐶐�
		pCarGear = new CCarGear;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pCarGear != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pCarGear->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pCarGear->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �Ԃ̃M�A�̃|�C���^��Ԃ�
	return pCarGear;
}