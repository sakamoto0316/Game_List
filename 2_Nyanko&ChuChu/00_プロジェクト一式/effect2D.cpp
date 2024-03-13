//=======================================
//
// 2D�G�t�F�N�g�̃��C������[effect2D.cpp]
// Author ��������
//
//=======================================
#include "effect2D.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

//=======================================
// �}�N����`
//=======================================
#define NORMAL_EFFECT_TEXTURE		"data\\TEXTURE\\effect000.jpg"		// �ʏ�̃G�t�F�N�g�̃e�N�X�`��
#define STAR_EFFECT_TEXTURE			"data\\TEXTURE\\SpeedEffect.tga"	// ���̃G�t�F�N�g�̃e�N�X�`��
#define BOOST_EFFECT_TEXTURE		"data\\TEXTURE\\smoke.tga"			// ���̃G�t�F�N�g�̃e�N�X�`��
#define GLASS_ROT_MOVE				(0.04f)								// �K���X�̌����̈ړ���

//=========================
// �R���X�g���N�^
//=========================
CEffect2D::CEffect2D() : CObject2D(CObject::TYPE_EFFECT, CObject::PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ړ���
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// �F
	m_type = TYPE_NONE;								// ���
	m_nLife = 0;									// ����
	m_fSub = 0.0f;									// �����ɂȂ�Ԋu
	m_fContra = 0.0f;								// ���a�̏k�ފԊu
	m_bAdd = false;									// ���Z������
}

//=========================
// �f�X�g���N�^
//=========================
CEffect2D::~CEffect2D()
{

}

//=========================
// ����������
//=========================
HRESULT CEffect2D::Init(void)
{
	if (FAILED(CObject2D::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ړ���
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// �F
	m_type = TYPE_NONE;								// ���
	m_nLife = 0;									// ����
	m_fSub = 0.0f;									// �����ɂȂ�Ԋu
	m_fContra = 0.0f;								// ���a�̏k�ފԊu
	m_bAdd = false;									// ���Z������

	// ������Ԃ�
	return S_OK;
}

//=========================
// �I������
//=========================
void CEffect2D::Uninit(void)
{
	// �I��
	CObject2D::Uninit();
}

//=========================
// �X�V����
//=========================
void CEffect2D::Update(void)
{
	// ���[�J���ϐ���錾
	D3DXVECTOR3 pos = GetPos();		// �ʒu���擾����
	D3DXVECTOR3 size = GetSize();	// �T�C�Y���擾����

	// ���������炵�Ă���
	m_nLife--;

	// �ړ�����
	pos += m_move;

	// �����x�����Z������
	m_col.a -= m_fSub;

	// �T�C�Y���k�߂�
	size.x -= m_fContra;
	size.y -= m_fContra;

	if (m_col.a <= 0.0f)
	{ // �����x��0.0f�ȉ��̏ꍇ

		// �����x��␳����
		m_col.a = 0.0f;
	}

	if (size.x <= 0.0f)
	{ // �T�C�Y��0.0f�ȉ��̏ꍇ

		// �T�C�Y��␳����
		size.x = 0.0f;
	}

	if (size.y <= 0.0f)
	{ // �T�C�Y��0.0f�ȉ��̏ꍇ

		// �T�C�Y��␳����
		size.y = 0.0f;
	}

	// �ʒu���X�V����
	SetPos(pos);

	// �T�C�Y���X�V����
	SetSize(size);

	// ��ނ��Ƃ̏���
	TypeProcess();

	if (m_nLife <= 0)
	{ // �G�t�F�N�g�̎������s������

		// �j������
		Uninit();

		// ���̐�̏������s��Ȃ�
		return;
	}

	// ���_���W�̐ݒ菈��
	SetVertex();

	// �F�̐ݒ菈��
	SetVtxColor(m_col);
}

//=========================
// �`�揈��
//=========================
void CEffect2D::Draw(void)
{
	if (m_bAdd == true)
	{ // �ʏ��ނ̏ꍇ

		// �f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

		//���u�����f�B���O�����Z�����ɐݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		// �`�揈��
		CObject2D::Draw();

		//���u�����f�B���O�����ɖ߂�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
	else
	{ // ��L�ȊO

		// �`�揈��
		CObject2D::Draw();
	}
}

//=========================
// ���̐ݒ菈��
//=========================
void CEffect2D::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& move, const int nLife, const float fRadius, const TYPE type)
{
	// �X�N���[���̐ݒ菈��
	SetPos(pos);			// �ʒu�ݒ�
	SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));			// �����ݒ�
	SetSize(D3DXVECTOR3(fRadius, fRadius, 0.0f));	// �T�C�Y�ݒ�
	SetLength();			// �����ݒ�
	SetAngle();				// �����ݒ�

	// �S�Ă̒l������������
	m_type = type;			// ���
	m_nLife = nLife;		// ����
	m_move = move;			// �ړ���

	switch (m_type)
	{
	case TYPE_NONE:			// �ʏ�

		// �F��ݒ肷��
		m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ���Z�����󋵂� true �ɂ���
		m_bAdd = true;

		break;

	case TYPE_SHINING:		// �P��

		// �F��ݒ肷��
		m_col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

		// ���Z�����󋵂� false �ɂ���
		m_bAdd = false;

		break;

	case TYPE_INFIRE:		// �����̉�

		// �F��ݒ肷��
		m_col = D3DXCOLOR(1.0f, 0.7f, 0.2f, 1.0f);

		// ���Z�����󋵂� true �ɂ���
		m_bAdd = true;

		break;

	case TYPE_OUTFIRE:		// �O���̉�

		// �F��ݒ肷��
		m_col = D3DXCOLOR(0.8f, 0.0f, 0.0f, 1.0f);

		// ���Z�����󋵂� false �ɂ���
		m_bAdd = false;

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	m_fSub = m_col.a * (1.0f / m_nLife);			// �����ɂȂ�Ԋu
	m_fContra = fRadius * (1.0f / m_nLife);			// ���a�̏k�ފԊu

	// ���_���̏�����
	SetVertex();

	// ���_�J���[�̐ݒ菈��
	SetVtxColor(m_col);

	if (m_type == TYPE_SHINING)
	{ // ��ނ����֌W�̏ꍇ

		// �e�N�X�`���̓ǂݍ��ݏ���
		BindTexture(CManager::Get()->GetTexture()->Regist(STAR_EFFECT_TEXTURE));
	}
	else if (m_type == TYPE_INFIRE ||
		m_type == TYPE_OUTFIRE)
	{ // ��ނ����E�u�[�X�g�̏ꍇ

		// �e�N�X�`���̓ǂݍ��ݏ���
		BindTexture(CManager::Get()->GetTexture()->Regist(BOOST_EFFECT_TEXTURE));
	}
	else
	{ // ��L�ȊO

		// �e�N�X�`���̓ǂݍ��ݏ���
		BindTexture(CManager::Get()->GetTexture()->Regist(NORMAL_EFFECT_TEXTURE));
	}
}

//=========================
// ��ނɂ�鏈��
//=========================
void CEffect2D::TypeProcess(void)
{
	switch (m_type)
	{
	case TYPE_NONE:			// �ʏ�

		break;

	case TYPE_SHINING:		// �P��

		break;

	case TYPE_INFIRE:		// �����̉�

		break;

	case TYPE_OUTFIRE:		// �O���̉�

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
CEffect2D* CEffect2D::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& move, const int nLife, const float fRadius, const TYPE type)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CEffect2D* pEffect = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pEffect == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pEffect = new CEffect2D;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pEffect != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pEffect->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pEffect->SetData(pos, move, nLife, fRadius, type);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �I�u�W�F�N�g2D�̃|�C���^��Ԃ�
	return pEffect;
}