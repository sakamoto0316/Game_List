//============================================
//
// �L�����N�^�[�̏��UI����[chara_infoUI.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "chara_infoUI.h"
#include "texture.h"
#include "useful.h"

#include "chara_icon.h"
#include "chara_ID.h"
#include "chara_state.h"

//========================
// �R���X�g���N�^
//========================
CCharaInfoUI::CCharaInfoUI() : CObject(TYPE_CHARAINFO, PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
	m_pIcon = nullptr;		// �A�C�R���̏��
	m_pID = nullptr;		// ID�̏��
	m_pState = nullptr;		// ��Ԃ̏��
}

//========================
// �f�X�g���N�^
//========================
CCharaInfoUI::~CCharaInfoUI()
{

}

//========================
// ����������
//========================
HRESULT CCharaInfoUI::Init(void)
{
	// �S�Ă̒l������������
	m_pIcon = nullptr;		// �A�C�R���̏��
	m_pID = nullptr;		// ID�̏��
	m_pState = nullptr;		// ��Ԃ̏��

	// ������Ԃ�
	return S_OK;
}

//========================
// �I������
//========================
void CCharaInfoUI::Uninit(void)
{
	if (m_pIcon != nullptr)
	{ // �A�C�R���� NULL ����Ȃ��ꍇ

		// �A�C�R���̏I������
		m_pIcon->Uninit();
		m_pIcon = nullptr;
	}

	if (m_pID != nullptr)
	{ // ID�� NULL ����Ȃ��ꍇ

		// ID�̏I������
		m_pID->Uninit();
		m_pID = nullptr;
	}

	if (m_pState != nullptr)
	{ // ��Ԃ� NULL ����Ȃ��ꍇ

		// ��Ԃ̏I������
		m_pState->Uninit();
		m_pState = nullptr;
	}

	// �{�̂̏I������
	Release();
}

//========================
// �X�V����
//========================
void CCharaInfoUI::Update(void)
{
	if (m_pIcon != nullptr)
	{ // �A�C�R���� NULL ����Ȃ��ꍇ

		// �A�C�R���̍X�V����
		m_pIcon->Update();
	}

	if (m_pID != nullptr)
	{ // ID�� NULL ����Ȃ��ꍇ

		// ID�̍X�V����
		m_pID->Update();
	}

	if (m_pState != nullptr)
	{ // ��Ԃ� NULL ����Ȃ��ꍇ

		// ��Ԃ̍X�V����
		m_pState->Update();
	}
}

//========================
// �`�揈��
//========================
void CCharaInfoUI::Draw(void)
{
	if (m_pIcon != nullptr)
	{ // �A�C�R���� NULL ����Ȃ��ꍇ

		// �A�C�R���̕`�揈��
		m_pIcon->Draw();
	}

	if (m_pID != nullptr)
	{ // ID�� NULL ����Ȃ��ꍇ

		// ID�̕`�揈��
		m_pID->Draw();
	}

	if (m_pState != nullptr)
	{ // ��Ԃ� NULL ����Ȃ��ꍇ

		// ��Ԃ̕`�揈��
		m_pState->Draw();
	}
}

//========================
// ���̐ݒ菈��
//========================
void CCharaInfoUI::SetData(const D3DXVECTOR3& pos, const int nPlayerID, const CPlayer::TYPE type)
{
	if (m_pIcon == nullptr)
	{ // �A�C�R���� NULL �̏ꍇ

		// �A�C�R���𐶐�����
		m_pIcon = CCharaIcon::Create(pos, type);
	}

	if (m_pID == nullptr)
	{ // ID�� NULL �̏ꍇ

		// ID�̈ʒu��ݒ�
		D3DXVECTOR3 posID = D3DXVECTOR3(pos.x + 40.0f, pos.y + 50.0f, pos.z);

		// ID�𐶐�����
		m_pID = CCharaID::Create(posID, nPlayerID);
	}

	if (m_pState == nullptr)
	{ // ID�� NULL �̏ꍇ

		// ID�̈ʒu��ݒ�
		D3DXVECTOR3 posState = D3DXVECTOR3(pos.x, pos.y - 40.0f, pos.z);

		// ID�𐶐�����
		m_pState = CCharaState::Create(posState, nPlayerID);
	}
}

//========================
// ��������
//========================
CCharaInfoUI* CCharaInfoUI::Create(const D3DXVECTOR3& pos, const int nPlayerID, const CPlayer::TYPE type)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CCharaInfoUI* pInfoUI = nullptr;		// �L�����N�^�[���UI�̃C���X�^���X�𐶐�

	if (pInfoUI == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pInfoUI = new CCharaInfoUI;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pInfoUI != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pInfoUI->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pInfoUI->SetData(pos, nPlayerID, type);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �L�����N�^�[�̏��UI�̃|�C���^��Ԃ�
	return pInfoUI;
}