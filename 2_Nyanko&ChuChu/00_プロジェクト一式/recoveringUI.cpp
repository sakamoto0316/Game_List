//===========================================
//
// �񕜒�UI���C������[recoveringUI.cpp]
// Author ����������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "recoveringUI.h"
#include "model.h"
#include "texture.h"
#include "player.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define SIZE_UI		(D3DXVECTOR3(50.0f, 50.0f, 0.0f))		// UI�̑傫��
#define SUB_ALPHA	(0.025f)			// �����x���Z���鐔

//-------------------------------------------
// �ÓI�����o�ϐ��錾
//-------------------------------------------

//==============================
// �R���X�g���N�^
//==============================
CRecoveringUI::CRecoveringUI() : CBillboard(CObject::TYPE_RECOVERINGUI, CObject::PRIORITY_PLAYER)
{
	// �S�Ă̒l���N���A����
	m_bDisp = false;			// UI��\�����邩
	m_fAlpha = 1.0f;			// �����x
	m_alpha = ALPHA_OPACITY;	// �����x�̏��
}

//==============================
// �f�X�g���N�^
//==============================
CRecoveringUI::~CRecoveringUI()
{

}

//==============================
// �񕜒�UI�̏���������
//==============================
HRESULT CRecoveringUI::Init(void)
{
	if (FAILED(CBillboard::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_bDisp = false;			// UI��\�����邩
	m_fAlpha = 1.0f;			// �����x
	m_alpha = ALPHA_OPACITY;	// �����x�̏��

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �񕜒�UI�̏I������
//========================================
void CRecoveringUI::Uninit(void)
{
	// �I������
	CBillboard::Uninit();
}

//=====================================
// �񕜒�UI�̍X�V����
//=====================================
void CRecoveringUI::Update(void)
{
	if (m_bDisp == true)
	{ // UI��\�������Ԃ̎�

		// �����x�ύX
		switch (m_alpha)
		{
		case CRecoveringUI::ALPHA_OPACITY:		// �s����

				// �����ɂ��Ă���
				m_fAlpha -= SUB_ALPHA;

				if (m_fAlpha <= 0.0f)
				{ // �����ɂȂ�����

					// ������Ԃɂ���
					m_alpha = ALPHA_TRANSPARENT;
				}

			break;

		case CRecoveringUI::ALPHA_TRANSPARENT:	// ����

			// �s�����ɂ��Ă���
			m_fAlpha += SUB_ALPHA;

			if (m_fAlpha >= 1.0f)
			{ // �s�����ɂȂ�����

				// �s������Ԃɂ���
				m_alpha = ALPHA_OPACITY;
			}

			break;

		default:

			// ��~����
			assert(false);

			break;
		}
	}
	else if (m_bDisp == false && m_alpha != ALPHA_OPACITY)
	{ // �\�������Ԃ���Ȃ��Ƃ�

		m_fAlpha = 1.0f;
		m_alpha = ALPHA_OPACITY;

	}

	// �F�ݒ�
	SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha));
}

//=====================================
// �񕜒�UI�̕`�揈��
//=====================================
void CRecoveringUI::Draw(void)
{
	if (m_bDisp == true)
	{ // UI��\�������Ԃ̂Ƃ�

		// �`�揈��
		CBillboard::DrawLightOff();
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CRecoveringUI::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld)
{
	// �ݒ菈���ɕ֗��ȃ}�N����`
	//NONE_D3DXVECTOR3					// �������X���Ȃ����Ƃ��Ɏg�p����
	// ���̐ݒ菈��

	//==========================================================================
	// �r���{�[�h
	//==========================================================================
	SetPos(pos);			// �ʒu
	SetPosOld(posOld);		// �O��̈ʒu
	SetSize(SIZE_UI);	// �T�C�Y
	BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\rez_keep.png"));		// �e�N�X�`���̊��蓖�ď���

	// ���_���W�̐ݒ菈��
	SetVertex();
}

//=======================================
// ��������
//=======================================
CRecoveringUI* CRecoveringUI::Create(const D3DXVECTOR3& pos, const  D3DXVECTOR3& posOld)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CRecoveringUI* pRecoveringUI = nullptr;	// �T���v���̃C���X�^���X�𐶐�

	if (pRecoveringUI == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �C���X�^���X�𐶐�
		pRecoveringUI = new CRecoveringUI;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pRecoveringUI != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pRecoveringUI->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pRecoveringUI->SetData(pos, posOld);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �T���v���̃|�C���^��Ԃ�
	return pRecoveringUI;
}

//=======================================
// UI�̕\����Ԃ̐ݒ�
//=======================================
void CRecoveringUI::SetDisplayUI(bool bRez)
{
	// UI�̕\����Ԃ�ݒ�
	m_bDisp = bRez;
}

//=======================================
// UI�̕\����Ԃ̎擾
//=======================================
bool CRecoveringUI::GetDisplayUI(void)
{
	// UI�̕\����Ԃ�Ԃ�
	return m_bDisp;
}