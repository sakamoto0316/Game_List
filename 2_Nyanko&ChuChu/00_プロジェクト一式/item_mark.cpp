//=======================================
//
// �A�C�e���̃}�[�N�̃��C������[item_mark.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "item_mark.h"
#include "texture.h"
#include "useful.h"

//=======================================
// �}�N����`
//=======================================
#define MOUSETRAP_TEXTURE	"data\\TEXTURE\\Mousetrap.png"		// �l�Y�~�߂�̃e�N�X�`��
#define DYNAMITE_TEXTURE	"data\\TEXTURE\\dynamite.png"		// �_�C�i�}�C�g�̃e�N�X�`��
#define SMALL_MAGNI			(D3DXVECTOR3(0.9f, 1.1f, 0.0f))		// ��������Ԃ̔{��
#define BIG_MAGNI			(D3DXVECTOR3(1.1f, 0.9f, 0.0f))		// �傫����Ԃ̔{��
#define SIZING_CORRECT		(0.05f)								// �g�k�̕␳�{��
#define SIZING_BORDER		(0.1f)								// �T�C�Y�̋��E��

//=========================
// �R���X�g���N�^
//=========================
CItemMark::CItemMark() : CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
	m_sizeDest = NONE_D3DXVECTOR3;		// �ړI�̃T�C�Y
	m_sizeCopy = NONE_D3DXVECTOR3;		// �����̃T�C�Y
	m_state = STATE_SMALL;				// ���
	m_type = CItem::TYPE_MOUSETRAP;		// ���
}

//=========================
// �f�X�g���N�^
//=========================
CItemMark::~CItemMark()
{

}

//=========================
// ����������
//=========================
HRESULT CItemMark::Init(void)
{
	if (FAILED(CObject2D::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_sizeDest = NONE_D3DXVECTOR3;		// �ړI�̃T�C�Y
	m_sizeCopy = NONE_D3DXVECTOR3;		// �����̃T�C�Y
	m_state = STATE_SMALL;				// ���
	m_type = CItem::TYPE_MOUSETRAP;		// ���

	// ������Ԃ�
	return S_OK;
}

//=========================
// �I������
//=========================
void CItemMark::Uninit(void)
{
	// �I��
	CObject2D::Uninit();
}

//=========================
// �X�V����
//=========================
void CItemMark::Update(void)
{
	// �T�C�Y�ݒ菈��
	Sizing();

	// ���_���W�̐ݒ菈��
	SetVertex();
}

//=========================
// �`�揈��
//=========================
void CItemMark::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();
}

//=========================
// ���̐ݒ菈��
//=========================
void CItemMark::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const CItem::TYPE type)
{
	// �X�N���[���̐ݒ菈��
	SetPos(pos);				// �ʒu�ݒ�
	SetRot(NONE_D3DXVECTOR3);	// �����ݒ�
	SetSize(size);				// �T�C�Y�ݒ�
	SetLength();				// �����ݒ�
	SetAngle();					// �����ݒ�

	// �S�Ă̒l��ݒ肷��
	m_sizeDest.x = size.x * SMALL_MAGNI.x;			// �ړI�̃T�C�Y(X��)
	m_sizeDest.y = size.y * SMALL_MAGNI.y;			// �ړI�̃T�C�Y(Y��)
	m_sizeCopy = size;			// �����̃T�C�Y
	m_state = STATE_SMALL;		// ���
	m_type = type;				// ���

	switch (type)
	{
	case CItem::TYPE_MOUSETRAP:

		// �e�N�X�`���̊��蓖�ď���
		BindTexture(CManager::Get()->GetTexture()->Regist(MOUSETRAP_TEXTURE));

		break;

	case CItem::TYPE_DYNAMITE:

		// �e�N�X�`���̊��蓖�ď���
		BindTexture(CManager::Get()->GetTexture()->Regist(DYNAMITE_TEXTURE));

		break;

	default:

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
CItemMark* CItemMark::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const CItem::TYPE type)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CItemMark* pItemMark = nullptr;		// �v���C���[�̃C���X�^���X�𐶐�

	if (pItemMark == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pItemMark = new CItemMark;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pItemMark != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pItemMark->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pItemMark->SetData(pos, size, type);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �A�C�e���}�[�N�̃|�C���^��Ԃ�
	return pItemMark;
}

//=========================
// ��ނ̎擾����
//=========================
CItem::TYPE CItemMark::GetType(void) const
{
	// ��ނ�Ԃ�
	return m_type;
}

//=========================
// �T�C�Y�ݒ菈��
//=========================
void CItemMark::Sizing(void)
{
	// �T�C�Y���擾����
	D3DXVECTOR3 size = GetSize();

	// �T�C�Y�̕␳����
	useful::Correct(m_sizeDest.x, &size.x, SIZING_CORRECT);
	useful::Correct(m_sizeDest.y, &size.y, SIZING_CORRECT);
	useful::Correct(m_sizeDest.z, &size.z, SIZING_CORRECT);

	switch (m_state)
	{
	case CItemMark::STATE_SMALL:

		if (m_sizeDest.x + SIZING_BORDER >= size.x)
		{ // �ړI�̃T�C�Y�Ɉ��ʋ߂Â����ꍇ

			// �g���Ԃɂ���
			m_state = STATE_BIG;

			// �ړI�̃T�C�Y��ݒ肷��
			m_sizeDest.x = m_sizeCopy.x * BIG_MAGNI.x;
			m_sizeDest.y = m_sizeCopy.y * BIG_MAGNI.y;
		}

		break;

	case CItemMark::STATE_BIG:

		if (m_sizeDest.x - SIZING_BORDER <= size.x)
		{ // �ړI�̃T�C�Y�Ɉ��ʋ߂Â����ꍇ

			// �k����Ԃɂ���
			m_state = STATE_SMALL;

			// �ړI�̃T�C�Y��ݒ肷��
			m_sizeDest.x = m_sizeCopy.x * SMALL_MAGNI.x;
			m_sizeDest.y = m_sizeCopy.y * SMALL_MAGNI.y;
		}

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	// �T�C�Y��K�p����
	SetSize(size);
}