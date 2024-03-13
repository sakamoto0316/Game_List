//=======================================
//
// �򖗏���[destruction.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "destruction.h"
#include "renderer.h"
#include "texture.h"

//=======================================
// �}�N����`
//=======================================
#define THORN_TEXTURE		"data\\TEXTURE\\Dstr001.png"		// �g�Q�g�Q�򖗂̃e�N�X�`��
#define AIRY_TEXTURE		"data\\TEXTURE\\Dstr002.png"		// �t���t���򖗂̃e�N�X�`��
#define EXPLOSION_TEXTURE	"data\\TEXTURE\\Dstr003.png"		// �����򖗂̃e�N�X�`��

//=========================
// �R���X�g���N�^
//=========================
CDestruction::CDestruction() : CBillboard(CObject::TYPE_DESTRUCTION, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// �F
	m_state = STATE_ADD;						// ���
	m_fAddAlpha = 0.0f;							// ���Z���铧���x
	m_fAlphaDest = 0.0f;						// �ړI�̓����x
}

//=========================
// �f�X�g���N�^
//=========================
CDestruction::~CDestruction()
{

}

//=========================
// ����������
//=========================
HRESULT CDestruction::Init(void)
{
	if (FAILED(CBillboard::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// �F
	m_state = STATE_ADD;						// ���
	m_fAddAlpha = 0.0f;							// ���Z���铧���x
	m_fAlphaDest = 0.0f;						// �ړI�̓����x

	// ������Ԃ�
	return S_OK;
}

//=========================
// �I������
//=========================
void CDestruction::Uninit(void)
{
	// �I��
	CBillboard::Uninit();
}

//=========================
// �X�V����
//=========================
void CDestruction::Update(void)
{
	// �����x�����Z����
	m_col.a += m_fAddAlpha;

	switch (m_state)
	{
	case STATE_ADD:		// ���Z���

		if (m_col.a >= m_fAlphaDest)
		{ // �ړI�̓����x�𒴂����ꍇ

			// �����x��␳����
			m_col.a = m_fAlphaDest;

			// ���Z���铧���x�𔽓]������
			m_fAddAlpha *= -1;

			// ���Z��Ԃɂ���
			m_state = STATE_SUB;
		}

		break;

	case STATE_SUB:		// ���Z���

		if (m_col.a <= 0.0f)
		{ // ��������萔�ȉ��ɂȂ����ꍇ

			// �I������
			Uninit();

			// ���̐�̏������s��Ȃ�
			return;
		}

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	// ���_�J���[�̐ݒ菈��
	SetVtxColor(m_col);
}

//=========================
// �`�揈��
//=========================
void CDestruction::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �`�揈��
	CBillboard::DrawLightOff();

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=========================
// ���̐ݒ菈��
//=========================
void CDestruction::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const D3DXCOLOR& col, const TYPE type, const int nLife)
{
	// �X�N���[���̐ݒ菈��
	SetPos(pos);		// �ʒu�ݒ�
	SetSize(size);		// �T�C�Y�ݒ�

	// �S�Ă̒l��ݒ肷��
	m_col = col;			// �F
	m_state = STATE_ADD;	// ���
	m_fAlphaDest = col.a;	// �ړI�̓����x
	m_col.a = 0.0f;			// �����x
	m_fAddAlpha = (m_fAlphaDest - m_col.a) / (nLife / 2);		// ���Z���铧���x

	// ���_���̏�����
	SetVertex();

	// ���_�J���[�̐ݒ菈��
	SetVtxColor(m_col);

	switch (type)
	{
	case TYPE_THORN:		// �g�Q�g�Q

		// �e�N�X�`���̓ǂݍ��ݏ���
		BindTexture(CManager::Get()->GetTexture()->Regist(THORN_TEXTURE));

		break;

	case TYPE_AIRY:			// �t���t��

		// �e�N�X�`���̓ǂݍ��ݏ���
		BindTexture(CManager::Get()->GetTexture()->Regist(AIRY_TEXTURE));

		break;

	case TYPE_EXPLOSION:	// ����

		// �e�N�X�`���̓ǂݍ��ݏ���
		BindTexture(CManager::Get()->GetTexture()->Regist(EXPLOSION_TEXTURE));

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
CDestruction* CDestruction::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const D3DXCOLOR& col, const TYPE type, const int nLife)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CDestruction* pDest = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pDest == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pDest = new CDestruction;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pDest != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pDest->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pDest->SetData(pos, size, col, type, nLife);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �I�u�W�F�N�g2D�̃|�C���^��Ԃ�
	return pDest;
}