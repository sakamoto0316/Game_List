//=======================================
//
// �L�����N�^�[��ID�̃��C������[chara_ID.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "chara_ID.h"
#include "texture.h"
#include "useful.h"

//=======================================
// �}�N����`
//=======================================
#define ID_PATTERN		((float)(1.0f / 4.0f))					// ID��1�ʂ��Ƃ̃T�C�Y
#define ID_SIZE			(D3DXVECTOR3(40.0f, 25.0f, 0.0f))		// ID�̃T�C�Y
#define ID_TEXTURE		"data\\TEXTURE\\PlayerID.png"			// ID�̃e�N�X�`��

//=========================
// �R���X�g���N�^
//=========================
CCharaID::CCharaID() : CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_UI)
{

}

//=========================
// �f�X�g���N�^
//=========================
CCharaID::~CCharaID()
{

}

//=========================
// ����������
//=========================
HRESULT CCharaID::Init(void)
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
void CCharaID::Uninit(void)
{
	// �I��
	CObject2D::Uninit();
}

//=========================
// �X�V����
//=========================
void CCharaID::Update(void)
{

}

//=========================
// �`�揈��
//=========================
void CCharaID::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();
}

//=========================
// ���̐ݒ菈��
//=========================
void CCharaID::SetData(const D3DXVECTOR3& pos, const int nID)
{
	// �X�N���[���̐ݒ菈��
	SetPos(pos);				// �ʒu�ݒ�
	SetRot(NONE_D3DXVECTOR3);	// �����ݒ�
	SetSize(ID_SIZE);			// �T�C�Y�ݒ�
	SetLength();				// �����ݒ�
	SetAngle();					// �����ݒ�

	// ���_���̏�����
	SetVertex();

	// �e�N�X�`���̓ǂݍ��ݏ���
	BindTexture(CManager::Get()->GetTexture()->Regist(ID_TEXTURE));

	// �e�N�X�`�����W�̐ݒ菈��
	SetVtxTextureAnim(ID_PATTERN, nID);
}

//=========================
// ��������
//=========================
CCharaID* CCharaID::Create(const D3DXVECTOR3& pos, const int nID)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CCharaID* pCharaImage = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pCharaImage == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pCharaImage = new CCharaID;
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
		pCharaImage->SetData(pos, nID);
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