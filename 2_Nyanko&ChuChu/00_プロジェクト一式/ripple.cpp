//=======================================
//
// �g��̃��C������[ripple.cpp]
// Author�F��������
//
//=======================================
#include "ripple.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

//---------------------------------------
// �}�N����`
//---------------------------------------
#define RIPPLE_INIT_SCALE			(D3DXVECTOR3(5.0f, 5.0f, 5.0f))			// �g��̏����g�嗦
#define RIPPLE_INIT_ALPHA			(1.0f)									// �g��̏��������x
#define RIPPLE_SUB_ALPHA			(0.05f)									// �g��̓����x�̌�����
#define RIPPLE_ADD_SCALE			(0.6f)									// �g��̊g�嗦�̉��Z��

//==========================================
// �R���X�g���N�^
//==========================================
CRipple::CRipple() : CModel(CObject::TYPE_RIPPLE, CObject::PRIORITY_PLAYER)
{
	// �S�Ă̒l���N���A����
	m_fAlpha = 0.0f;			// �����x
}

//==========================================
// �f�X�g���N�^
//==========================================
CRipple::~CRipple()
{

}

//==========================================
// �g��̏���������
//==========================================
HRESULT CRipple::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_fAlpha = 0.0f;			// �����x

	// ������Ԃ�
	return S_OK;
}

//========================================
// �g��̏I������
//========================================
void CRipple::Uninit(void)
{
	// �I������
	CModel::Uninit();
}

//========================================
// �g��̍X�V����
//========================================
void CRipple::Update(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 scale = GetScale();			// �g�嗦���擾����

	// �����x������������
	m_fAlpha -= RIPPLE_SUB_ALPHA;

	// �g�嗦��ω�������
	scale.x += RIPPLE_ADD_SCALE;
	scale.z += RIPPLE_ADD_SCALE;

	// �����X�V����
	SetScale(scale);			// �g�嗦��ݒ肷��

	if (m_fAlpha <= 0.0f)
	{ // �����x�� 0.0f �ȉ��̏ꍇ

	  // �I������
		Uninit();

		// ���̐�̏������s��Ȃ�
		return;
	}
}

//===========================================
// �g��̕`�揈��
//===========================================
void CRipple::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	// �A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);					//�A���t�@�e�X�g�̗L��/�����ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);				//�A���t�@�e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAREF, ALPHA_TEST_NUMBER);				//�A���t�@�e�X�g�̎Q�ƒl�ݒ�

	// �`�揈��(�F���f�^)
	CModel::Draw(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha));

	// �A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);			// �A���t�@�e�X�g�̗L��/�����ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);		// �A���t�@�e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);						// �A���t�@�e�X�g�̎Q�ƒl�ݒ�
}

//===========================================
// ���̐ݒ菈��
//===========================================
void CRipple::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// �X�N���[���̐ݒ菈��
	SetPos(pos);								// �ʒu�ݒ�
	SetPosOld(pos);								// �O��̈ʒu�ݒ�
	SetRot(rot);								// �����ݒ�
	SetScale(RIPPLE_INIT_SCALE);				// �g�嗦
	SetFileData(CXFile::TYPE_RIPPLE);			// �T�C�Y�ݒ�

	// �S�Ă̒l������������
	m_fAlpha = RIPPLE_INIT_ALPHA;				// �����x
}

//===========================================
// ��������
//===========================================
CRipple* CRipple::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CRipple* pRipple = nullptr;	// �t�B�[���h�̃C���X�^���X�𐶐�

	if (pRipple == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pRipple = new CRipple;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pRipple != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pRipple->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �x����
			MessageBox(NULL, "�g��̏������Ɏ��s�I", "�x���I", MB_ICONWARNING);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pRipple->SetData(pos, rot);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}

	// �g��̃|�C���^��Ԃ�
	return pRipple;
}