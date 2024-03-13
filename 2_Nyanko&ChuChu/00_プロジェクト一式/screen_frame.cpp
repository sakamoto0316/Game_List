//============================================
//
// ��ʂ̘g����[screen_frame.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "screen_frame.h"
#include "object2D.h"
#include "texture.h"

//--------------------------------------------
// �������O���
//--------------------------------------------
namespace
{
	const D3DXVECTOR3 FRAME_POS = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);		// �ʒu
	const D3DXVECTOR3 FRAME_SIZE[CScreenFrame::TYPE_MAX] =			// �T�C�Y
	{
		D3DXVECTOR3(5.0f, SCREEN_HEIGHT * 0.5f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 5.0f, 0.0f),
	};
}

//============================
// �R���X�g���N�^
//============================
CScreenFrame::CScreenFrame() : CObject(TYPE_SCREENFRAME, PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_apFrame[nCnt] = nullptr;		// �g
	}
}

//============================
// �f�X�g���N�^
//============================
CScreenFrame::~CScreenFrame()
{

}

//============================
// ����������
//============================
HRESULT CScreenFrame::Init(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_apFrame[nCnt] = nullptr;		// �g
	}

	// ������Ԃ�
	return S_OK;
}

//============================
// �I������
//============================
void CScreenFrame::Uninit(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if(m_apFrame[nCnt] != nullptr)
		{ // �g�� NULL ����Ȃ��ꍇ

			// �g�̏I������
			m_apFrame[nCnt]->Uninit();
			m_apFrame[nCnt] = nullptr;
		}
	}

	// �{�̂̏I������
	Release();
}

//============================
// �X�V����
//============================
void CScreenFrame::Update(void)
{

}

//============================
// �`�揈��
//============================
void CScreenFrame::Draw(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apFrame[nCnt] != nullptr)
		{ // �g�� NULL ����Ȃ��ꍇ

			// �g�̕`�揈��
			m_apFrame[nCnt]->Draw();
		}
	}
}

//============================
// ���̐ݒ菈��
//============================
void CScreenFrame::SetData(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apFrame[nCnt] == nullptr)
		{ // �g�� NULL �̏ꍇ

			// �g�𐶐�����
			m_apFrame[nCnt] = CObject2D::Create(CObject2D::TYPE_NONE, TYPE_NONE, PRIORITY_UI);

			// �X�N���[���̐ݒ菈��
			m_apFrame[nCnt]->SetPos(FRAME_POS);				// �ʒu�ݒ�
			m_apFrame[nCnt]->SetRot(NONE_D3DXVECTOR3);		// �����ݒ�
			m_apFrame[nCnt]->SetSize(FRAME_SIZE[nCnt]);		// �T�C�Y�ݒ�
			m_apFrame[nCnt]->SetLength();					// �����ݒ�
			m_apFrame[nCnt]->SetAngle();					// �����ݒ�

			// ���_���̏�����
			m_apFrame[nCnt]->SetVertex();

			// ���_�J���[�̐ݒ菈��
			m_apFrame[nCnt]->SetVtxColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
		}
	}
}

//============================
//��������
//============================
CScreenFrame* CScreenFrame::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CScreenFrame* pScreen = nullptr;	// ��ʂ̘g�̃C���X�^���X�𐶐�

	if (pScreen == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pScreen = new CScreenFrame;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pScreen != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pScreen->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pScreen->SetData();
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// ��ʂ̘g�̃|�C���^��Ԃ�
	return pScreen;
}