//=======================================
//
// �A�C�e���̘g�̃��C������[item_frame.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "item_frame.h"
#include "texture.h"
#include "useful.h"

//=======================================
// �}�N����`
//=======================================
#define CAT_TEXTURE			"data\\TEXTURE\\Cat_Frame.png"		// �l�R�̘g�̃e�N�X�`��
#define RAT_TEXTURE			"data\\TEXTURE\\Rat_Frame.png"		// �l�Y�~�̘g�̃e�N�X�`��

//=========================
// �R���X�g���N�^
//=========================
CItemFrame::CItemFrame() : CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_UI)
{

}

//=========================
// �f�X�g���N�^
//=========================
CItemFrame::~CItemFrame()
{

}

//=========================
// ����������
//=========================
HRESULT CItemFrame::Init(void)
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
void CItemFrame::Uninit(void)
{
	// �I��
	CObject2D::Uninit();
}

//=========================
// �X�V����
//=========================
void CItemFrame::Update(void)
{

}

//=========================
// �`�揈��
//=========================
void CItemFrame::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();
}

//=========================
// ���̐ݒ菈��
//=========================
void CItemFrame::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const CPlayer::TYPE type)
{
	// �X�N���[���̐ݒ菈��
	SetPos(pos);				// �ʒu�ݒ�
	SetRot(NONE_D3DXVECTOR3);	// �����ݒ�
	SetSize(size);				// �T�C�Y�ݒ�
	SetLength();				// �����ݒ�
	SetAngle();					// �����ݒ�

	switch (type)
	{
	case CPlayer::TYPE_CAT:		// �l�R

		// �e�N�X�`���̊��蓖�ď���
		BindTexture(CManager::Get()->GetTexture()->Regist(CAT_TEXTURE));

		break;

	case CPlayer::TYPE_RAT:		// �l�Y�~

		// �e�N�X�`���̊��蓖�ď���
		BindTexture(CManager::Get()->GetTexture()->Regist(RAT_TEXTURE));

		break;

	default:					// ��L�ȊO

		// ��~
		assert(false);

		break;
	}

	// ���_���̏�����
	SetVertex();
}

//=========================
// ��������
//=========================
CItemFrame* CItemFrame::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const CPlayer::TYPE type)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CItemFrame* pItemFrame = nullptr;		// �v���C���[�̃C���X�^���X�𐶐�

	if (pItemFrame == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pItemFrame = new CItemFrame;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pItemFrame != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pItemFrame->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pItemFrame->SetData(pos, size, type);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �A�C�e���g�̃|�C���^��Ԃ�
	return pItemFrame;
}