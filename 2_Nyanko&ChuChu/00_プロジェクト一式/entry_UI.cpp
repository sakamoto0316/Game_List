//=======================================
//
// �G���g���[UI����[entry_UI.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "entry_UI.h"
#include "input.h"
#include "texture.h"

#include "entry_frame.h"
#include "entry_team.h"
#include "entry_ID.h"

//=======================================
// �}�N����`
//=======================================
#define TEAM_SHIFT			(240.0f)		// �`�[���̂��炷����
#define ID_SHIFT			(230.0f)		// ID�̂��炷����
#define NONE_ID				(-1)			// �C���f�b�N�X�̏�����

//=========================
// �R���X�g���N�^
//=========================
CEntryUI::CEntryUI() : CObject(CObject::TYPE_ENTRYUI, CObject::PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
	m_pFrame = nullptr;			// �g�̏��
	m_pTeam = nullptr;			// �`�[���̏��
	m_pID = nullptr;			// �v���C���[ID�̏��
	m_nID = NONE_ID;			// �C���f�b�N�X
}

//=========================
// �f�X�g���N�^
//=========================
CEntryUI::~CEntryUI()
{

}

//=========================
// ����������
//=========================
HRESULT CEntryUI::Init(void)
{
	// �S�Ă̒l���N���A����
	m_pFrame = nullptr;			// �g�̏��
	m_pTeam = nullptr;			// �`�[���̏��
	m_pID = nullptr;			// �v���C���[ID�̏��
	m_nID = NONE_ID;			// �C���f�b�N�X

	// ������Ԃ�
	return S_OK;
}

//=========================
// �I������
//=========================
void CEntryUI::Uninit(void)
{
	if (m_pFrame != nullptr)
	{ // �g�̏�� NULL ����Ȃ��ꍇ

		// �g�̏I������
		m_pFrame->Uninit();
		m_pFrame = nullptr;
	}

	if (m_pTeam != nullptr)
	{ // �`�[���̏�� NULL ����Ȃ��ꍇ

		// �`�[���̏I������
		m_pTeam->Uninit();
		m_pTeam = nullptr;
	}

	if (m_pID != nullptr)
	{ // ID�̏�� NULL ����Ȃ��ꍇ

		// ID�̏I������
		m_pID->Uninit();
		m_pID = nullptr;
	}

	// �{�̂̏I������
	Release();
}

//=========================
// �X�V����
//=========================
void CEntryUI::Update(void)
{
	if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_LEFT, m_nID) == true)
	{ // D�L�[���������ꍇ

	}

	if (m_pFrame != nullptr)
	{ // �g�̏�� NULL ����Ȃ��ꍇ

		// �g�̍X�V����
		m_pFrame->Update();
	}

	if (m_pTeam != nullptr)
	{ // �`�[���̏�� NULL ����Ȃ��ꍇ

		// �`�[���̍X�V����
		m_pTeam->Update();
	}

	if (m_pID != nullptr)
	{ // ID�̏�� NULL ����Ȃ��ꍇ

		// ID�̍X�V����
		m_pID->Update();
	}
}

//=========================
// �`�揈��
//=========================
void CEntryUI::Draw(void)
{
	if (m_pFrame != nullptr)
	{ // �g�̏�� NULL ����Ȃ��ꍇ

		// �g�̕`�揈��
		m_pFrame->Draw();
	}

	if (m_pTeam != nullptr)
	{ // �`�[���̏�� NULL ����Ȃ��ꍇ

		// �`�[���̕`�揈��
		m_pTeam->Draw();
	}

	if (m_pID != nullptr)
	{ // ID�̏�� NULL ����Ȃ��ꍇ

		// ID�̕`�揈��
		m_pID->Draw();
	}
}

//=========================
// ���̐ݒ菈��
//=========================
void CEntryUI::SetData(const D3DXVECTOR3& pos, const int nID, const CPlayer::TYPE type)
{
	if (m_pFrame == nullptr)
	{ // �g�̏�� NULL �̏ꍇ

		// �g�𐶐�����
		m_pFrame = CEntryFrame::Create(pos);
	}
	else
	{ // ��L�ȊO

		// ��~
		assert(false);
	}

	if (m_pTeam == nullptr)
	{ // �`�[���̏�� NULL �̏ꍇ

		// �`�[���𐶐�����
		m_pTeam = CEntryTeam::Create(D3DXVECTOR3(pos.x, pos.y - TEAM_SHIFT, 0.0f), type);
	}
	else
	{ // ��L�ȊO

		// ��~
		assert(false);
	}

	if (m_pID == nullptr)
	{ // �`�[���̏�� NULL �̏ꍇ

		// �`�[���𐶐�����
		m_pID = CEntryID::Create(D3DXVECTOR3(pos.x, pos.y + ID_SHIFT, 0.0f), nID);
	}
	else
	{ // ��L�ȊO

		// ��~
		assert(false);
	}
}

//=========================
// ��������
//=========================
CEntryUI* CEntryUI::Create(const D3DXVECTOR3& pos, const int nID, const CPlayer::TYPE type)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CEntryUI* pEntry = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pEntry == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pEntry = new CEntryUI;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pEntry != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pEntry->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pEntry->SetData(pos, nID, type);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �G���g���[UI�̃|�C���^��Ԃ�
	return pEntry;
}

//=========================
// �`�[���̎擾����
//=========================
CEntryTeam* CEntryUI::GetTeam(void)
{
	// �`�[���̃|�C���^��Ԃ�
	return m_pTeam;
}