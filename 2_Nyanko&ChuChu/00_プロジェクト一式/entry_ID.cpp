//=======================================
//
// �G���g���[��ID�̃��C������[entry_ID.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "entry_ID.h"
#include "texture.h"

//=======================================
// �}�N����`
//=======================================
#define ID_SIZE		(D3DXVECTOR3(120.0f, 60.0f, 0.0f))		// ID�̃T�C�Y
#define ID_TEXTURE	"data\\TEXTURE\\PlayerID.png"			// ID�̃e�N�X�`��
#define ID_PATTERN		(0.25f)								// ID�̃e�N�X�`���̃p�^�[����

//=========================
// �R���X�g���N�^
//=========================
CEntryID::CEntryID() : CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_UI)
{

}

//=========================
// �f�X�g���N�^
//=========================
CEntryID::~CEntryID()
{

}

//=========================
// ����������
//=========================
HRESULT CEntryID::Init(void)
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
void CEntryID::Uninit(void)
{
	// �I��
	CObject2D::Uninit();
}

//=========================
// �X�V����
//=========================
void CEntryID::Update(void)
{

}

//=========================
// �`�揈��
//=========================
void CEntryID::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();
}

//=========================
// ���̐ݒ菈��
//=========================
void CEntryID::SetData(const D3DXVECTOR3& pos, const int nID)
{
	// �X�N���[���̐ݒ菈��
	SetPos(pos);				// �ʒu�ݒ�
	SetRot(NONE_D3DXVECTOR3);	// �����ݒ�
	SetSize(ID_SIZE);		// �T�C�Y�ݒ�
	SetLength();				// �����ݒ�
	SetAngle();					// �����ݒ�

	// �e�N�X�`���̓ǂݍ��ݏ���
	BindTexture(CManager::Get()->GetTexture()->Regist(ID_TEXTURE));

	// ���_���̏�����
	SetVertex();

	// �e�N�X�`�����W�̐ݒ菈��
	SetVtxTextureAnim(ID_PATTERN, nID);
}

//=========================
// ��������
//=========================
CEntryID* CEntryID::Create(const D3DXVECTOR3& pos, const int nID)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CEntryID* pEntryId = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pEntryId == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pEntryId = new CEntryID;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pEntryId != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pEntryId->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pEntryId->SetData(pos, nID);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �G���g���[�̘g�̃|�C���^��Ԃ�
	return pEntryId;
}