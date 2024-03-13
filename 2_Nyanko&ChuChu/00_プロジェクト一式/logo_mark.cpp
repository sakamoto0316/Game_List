//============================================
//
// ���S�}�[�N����[logo_mark.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "logo_mark.h"
#include "object2D.h"
#include "texture.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define LOGO_SCREEN_SIZE		(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f))		// ���S��ʂ̃X�N���[���̃T�C�Y
#define LOGO_MARK_SIZE			(D3DXVECTOR3(200.0f, 200.0f, 0.0f))									// ���S��ʂ̃}�[�N�̃T�C�Y
#define LOGO_MARK_TEXTURE		"data/TEXTURE/Obalab.png"											// ���S�}�[�N�̃e�N�X�`��

//============================
// �R���X�g���N�^
//============================
CLogoMark::CLogoMark() : CObject(CObject::TYPE_LOGOMARK, PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_aLogoMark[nCnt] = nullptr;			// 2D�I�u�W�F�N�g�̏��
	}
}

//============================
// �f�X�g���N�^
//============================
CLogoMark::~CLogoMark()
{

}

//============================
// ����������
//============================
HRESULT CLogoMark::Init(void)
{
	for (int nCntUI = 0; nCntUI < TYPE_MAX; nCntUI++)
	{
		// ��������
		m_aLogoMark[nCntUI] = CObject2D::Create(CObject2D::TYPE_NONE, CObject::TYPE_NONE, CObject::PRIORITY_UI);

		// �X�N���[���̐ݒ菈��
		m_aLogoMark[nCntUI]->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));				// �ʒu�ݒ�
		m_aLogoMark[nCntUI]->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		// �����ݒ�
		m_aLogoMark[nCntUI]->SetLength();								// �����ݒ�
		m_aLogoMark[nCntUI]->SetAngle();								// �����ݒ�

		switch (nCntUI)
		{
		case TYPE_SCREEN:

			// �T�C�Y�ݒ�
			m_aLogoMark[nCntUI]->SetSize(LOGO_SCREEN_SIZE);

			// �F�̐ݒ菈��
			m_aLogoMark[nCntUI]->SetVtxColor(D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f));

			break;

		case TYPE_MARK:

			// �T�C�Y�ݒ�
			m_aLogoMark[nCntUI]->SetSize(LOGO_MARK_SIZE);

			// �e�N�X�`���̊��蓖�ď���
			m_aLogoMark[nCntUI]->BindTexture(CManager::Get()->GetTexture()->Regist(LOGO_MARK_TEXTURE));

			break;

		default:

			// ��~
			assert(false);

			break;
		}

		// ���_���̏�����
		m_aLogoMark[nCntUI]->SetVertex();
	}

	// ������Ԃ�
	return S_OK;
}

//============================
// �I������
//============================
void CLogoMark::Uninit(void)
{
	for (int nCntUI = 0; nCntUI < TYPE_MAX; nCntUI++)
	{
		// �I������
		m_aLogoMark[nCntUI]->Uninit();
		m_aLogoMark[nCntUI] = nullptr;
	}

	// �j������
	Release();
}

//============================
// �X�V����
//============================
void CLogoMark::Update(void)
{

}

//============================
// �`�揈��
//============================
void CLogoMark::Draw(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_aLogoMark[nCnt] != nullptr)
		{ // 2D�I�u�W�F�N�g�̏�� NULL ����Ȃ��ꍇ

			// �`�揈��
			m_aLogoMark[nCnt]->Draw();
		}
	}
}

//============================
//��������
//============================
CLogoMark* CLogoMark::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CLogoMark* pLogoMark = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pLogoMark == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pLogoMark = new CLogoMark;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pLogoMark != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pLogoMark->Init()))
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

	// ���S�}�[�N�̃|�C���^��Ԃ�
	return pLogoMark;
}