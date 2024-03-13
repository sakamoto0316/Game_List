//=======================================
//
// ����I��UI�̃��C������[weapon_selectUI.cpp]
// Author ��������
//
//=======================================
#include "main.h"
#include "manager.h"
#include "weapon_selectUI.h"
#include "object2D.h"
#include "texture.h"

#include "weapon_cage.h"
#include "weapon_balloon.h"

//---------------------------------------
// �}�N����`
//---------------------------------------
#define BALLOON_TEXTURE		"data\\TEXTURE\\Balloon.png"		// �ӂ������̃e�N�X�`��

//==========================================
// �R���X�g���N�^
//==========================================
CWeaponSelectUI::CWeaponSelectUI() : CObject(TYPE_WEAPONSELECTUI, PRIORITY_PLAYER)
{
	// �S�Ă̒l���N���A����
	m_pos = NONE_D3DXVECTOR3;	// �ʒu
	m_pCage = nullptr;			// ���포���̏��
	m_pBalloon = nullptr;		// �ӂ������̏��
}

//==========================================
// �f�X�g���N�^
//==========================================
CWeaponSelectUI::~CWeaponSelectUI()
{

}

//==========================================
// �|�[�Y�̏���������
//==========================================
HRESULT CWeaponSelectUI::Init(void)
{
	// �S�Ă̒l������������
	m_pos = NONE_D3DXVECTOR3;	// �ʒu

	if (m_pCage == nullptr)
	{ // ���포���̏�� NULL �̏ꍇ

		// ���포���𐶐�����
		m_pCage = CWeaponCage::Create(m_pos);
	}

	if (m_pBalloon == nullptr)
	{ // �ӂ������̏�� NULL �̏ꍇ

		// �ӂ������𐶐�����
		m_pBalloon = CWeaponBalloon::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z), BALLOON_TEXTURE);
	}

	// ������Ԃ�
	return S_OK;
}

//========================================
// �|�[�Y�̏I������
//========================================
void CWeaponSelectUI::Uninit(void)
{
	if (m_pCage != nullptr)
	{ // ���포���� NULL ����Ȃ��ꍇ

		// ���포���̏I������
		m_pCage->Uninit();
		m_pCage = nullptr;
	}

	if (m_pBalloon != nullptr)
	{ // �ӂ������� NULL ����Ȃ��ꍇ

		// �ӂ������̏I������
		m_pBalloon->Uninit();
		m_pBalloon = nullptr;
	}

	// �{�̂̏I������
	Release();
}

//========================================
// �|�[�Y�̍X�V����
//========================================
void CWeaponSelectUI::Update(void)
{
	
}

//=====================================
// �|�[�Y�̕`�揈��
//=====================================
void CWeaponSelectUI::Draw(void)
{
	if (m_pCage != nullptr)
	{ // ���포���� NULL ����Ȃ��ꍇ

		// �`�揈��
		m_pCage->Draw();
	}

	if (m_pBalloon != nullptr)
	{ // �ӂ������� NULL ����Ȃ��ꍇ

		// �`�揈��
		m_pBalloon->Draw();
	}
}

//=====================================
// ��������
//=====================================
CWeaponSelectUI* CWeaponSelectUI::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CWeaponSelectUI* pWeapon = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pWeapon == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pWeapon = new CWeaponSelectUI;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pWeapon != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pWeapon->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// ����I��UI�̃|�C���^��Ԃ�
	return pWeapon;
}