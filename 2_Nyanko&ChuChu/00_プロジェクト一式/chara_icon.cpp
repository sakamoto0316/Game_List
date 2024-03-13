//=======================================
//
// �L�����N�^�[�̉摜�̃��C������[chara_image.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "chara_icon.h"
#include "texture.h"
#include "useful.h"

//=======================================
// �}�N����`
//=======================================
#define ICON_SIZE			(D3DXVECTOR3(50.0f, 50.0f, 0.0f))		// �A�C�R���̃T�C�Y
#define CAT_ICON_TEXTURE	"data\\TEXTURE\\Cat_Icon.png"			// �l�R�̃A�C�R���̃e�N�X�`��
#define RAT_ICON_TEXTURE	"data\\TEXTURE\\Rat_Icon.png"			// �l�Y�~�̃A�C�R���̃e�N�X�`��

//=========================
// �R���X�g���N�^
//=========================
CCharaIcon::CCharaIcon() : CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_UI)
{

}

//=========================
// �f�X�g���N�^
//=========================
CCharaIcon::~CCharaIcon()
{

}

//=========================
// ����������
//=========================
HRESULT CCharaIcon::Init(void)
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
void CCharaIcon::Uninit(void)
{
	// �I��
	CObject2D::Uninit();
}

//=========================
// �X�V����
//=========================
void CCharaIcon::Update(void)
{

}

//=========================
// �`�揈��
//=========================
void CCharaIcon::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();
}

//=========================
// ���̐ݒ菈��
//=========================
void CCharaIcon::SetData(const D3DXVECTOR3& pos, const CPlayer::TYPE type)
{
	// �X�N���[���̐ݒ菈��
	SetPos(pos);				// �ʒu�ݒ�
	SetRot(NONE_D3DXVECTOR3);	// �����ݒ�
	SetSize(ICON_SIZE);			// �T�C�Y�ݒ�
	SetLength();				// �����ݒ�
	SetAngle();					// �����ݒ�

	// ���_���̏�����
	SetVertex();

	switch (type)
	{
	case CPlayer::TYPE_CAT:

		// �e�N�X�`���̓ǂݍ��ݏ���
		BindTexture(CManager::Get()->GetTexture()->Regist(CAT_ICON_TEXTURE));

		break;

	case CPlayer::TYPE_RAT:

		// �e�N�X�`���̓ǂݍ��ݏ���
		BindTexture(CManager::Get()->GetTexture()->Regist(RAT_ICON_TEXTURE));

		break;

	default:

		// ��~
		assert(false);

		break;
	}
}

//=========================
// ��������
//=========================
CCharaIcon* CCharaIcon::Create(const D3DXVECTOR3& pos, const CPlayer::TYPE type)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CCharaIcon* pCharaImage = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pCharaImage == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pCharaImage = new CCharaIcon;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pCharaImage != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pCharaImage->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pCharaImage->SetData(pos, type);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �L�����N�^�[�摜�̃|�C���^��Ԃ�
	return pCharaImage;
}