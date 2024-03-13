//=======================================
//
// �^�C�g���̏��̃��C������[title_floor.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "title_floor.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

//=======================================
// �}�N����`
//=======================================
#define FLOOR_TEXTURE	"data\\TEXTURE\\ground001.jpg"			// �������e�N�X�`��
#define FLOOR_SIZE		(D3DXVECTOR3(1000.0f, 0.0f, 1000.0f))	// ���̃T�C�Y

//=========================
// �R���X�g���N�^
//=========================
CTitleFloor::CTitleFloor() : CObject3D(CObject::TYPE_MAP, CObject::PRIORITY_BG)
{

}

//=========================
// �f�X�g���N�^
//=========================
CTitleFloor::~CTitleFloor()
{

}

//=========================
// ����������
//=========================
HRESULT CTitleFloor::Init(void)
{
	if (FAILED(CObject3D::Init()))
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
void CTitleFloor::Uninit(void)
{
	// �I��
	CObject3D::Uninit();
}

//=========================
// �X�V����
//=========================
void CTitleFloor::Update(void)
{
	
}

//=========================
// �`�揈��
//=========================
void CTitleFloor::Draw(void)
{
	// �`�揈��
	CObject3D::Draw();
}

//=========================
// ���̐ݒ菈��
//=========================
void CTitleFloor::SetData(void)
{
	// ���̐ݒ菈��
	SetPos(NONE_D3DXVECTOR3);		// �ʒu
	SetPosOld(NONE_D3DXVECTOR3);	// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);		// ����
	SetSize(FLOOR_SIZE);			// �T�C�Y�ݒ�

	// ���_���̏�����
	SetVertex();

	// �e�N�X�`���̓ǂݍ��ݏ���
	BindTexture(CManager::Get()->GetTexture()->Regist(FLOOR_TEXTURE));
}

//=========================
// ��������
//=========================
CTitleFloor* CTitleFloor::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CTitleFloor* pFloor = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pFloor == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pFloor = new CTitleFloor;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pFloor != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pFloor->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pFloor->SetData();
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// ���̃|�C���^��Ԃ�
	return pFloor;
}