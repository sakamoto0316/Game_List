//=======================================
//
// �G���g���[�̘g�̃��C������[entry_frame.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "entry_frame.h"
#include "texture.h"

//=======================================
// �}�N����`
//=======================================
#define FRAME_SIZE		(D3DXVECTOR3(155.0f, 310.0f, 0.0f))		// �g�̃T�C�Y
#define FRAME_TEXTURE	"data\\TEXTURE\\EntryFrame.png"			// �g�̃e�N�X�`��

//=========================
// �R���X�g���N�^
//=========================
CEntryFrame::CEntryFrame() : CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_UI)
{

}

//=========================
// �f�X�g���N�^
//=========================
CEntryFrame::~CEntryFrame()
{

}

//=========================
// ����������
//=========================
HRESULT CEntryFrame::Init(void)
{
	if (FAILED(CObject2D::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//=========================
// �I������
//=========================
void CEntryFrame::Uninit(void)
{
	// �I��
	CObject2D::Uninit();
}

//=========================
// �X�V����
//=========================
void CEntryFrame::Update(void)
{

}

//=========================
// �`�揈��
//=========================
void CEntryFrame::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();
}

//=========================
// ���̐ݒ菈��
//=========================
void CEntryFrame::SetData(const D3DXVECTOR3& pos)
{
	// �X�N���[���̐ݒ菈��
	SetPos(pos);				// �ʒu�ݒ�
	SetRot(NONE_D3DXVECTOR3);	// �����ݒ�
	SetSize(FRAME_SIZE);		// �T�C�Y�ݒ�
	SetLength();				// �����ݒ�
	SetAngle();					// �����ݒ�

	// �e�N�X�`���̓ǂݍ��ݏ���
	BindTexture(CManager::Get()->GetTexture()->Regist(FRAME_TEXTURE));

	// ���_���̏�����
	SetVertex();
}

//=========================
// ��������
//=========================
CEntryFrame* CEntryFrame::Create(const D3DXVECTOR3& pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CEntryFrame* pEntryFrame = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pEntryFrame == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pEntryFrame = new CEntryFrame;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pEntryFrame != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pEntryFrame->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pEntryFrame->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �G���g���[�̘g�̃|�C���^��Ԃ�
	return pEntryFrame;
}