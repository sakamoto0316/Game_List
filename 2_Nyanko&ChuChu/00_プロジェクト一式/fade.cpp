//=======================================
//
//�t�F�[�h�̃��C������[Fade.cpp]
//Author ��������
//
//=======================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "Fade.h"
#include "debugproc.h"

//�}�N����`
#define FADE_ADD_ALPHA			(0.05f)									// �t�F�[�h�����̒ǉ����郿�l�̐��l
#define FADE_COLOR				(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f))		// �t�F�[�h�̐F

//==========================================
// �R���X�g���N�^
//==========================================
CFade::CFade()
{
	// �S�Ă̒l���N���A����
	m_pVtxBuff = nullptr;				//�t�F�[�h�̒��_�o�b�t�@�ւ̃|�C���^
	m_fade = FADE_NONE;					// �t�F�[�h�̏��
	m_modeNext = CScene::MODE_LOGO;		// ���̉��(���[�h)
	m_color = FADE_COLOR;				// �|���S��(�t�F�[�h)�̐F
}

//==========================================
// �f�X�g���N�^
//==========================================
CFade::~CFade()
{

}

//==========================================
// �t�F�[�h�̏���������
//==========================================
HRESULT CFade::Init(CScene::MODE modeNext)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = CManager::Get()->GetRenderer()->GetDevice();

	// �S�Ă̒l������������
	m_fade = FADE_IN;				// �t�F�[�h���
	m_modeNext = modeNext;			// ���̉��(���[�h)
	m_color = FADE_COLOR;			// �|���S���̐F

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = m_color;
	pVtx[1].col = m_color;
	pVtx[2].col = m_color;
	pVtx[3].col = m_color;

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	// ���[�h�̐ݒ�
	CManager::Get()->SetMode(m_modeNext);

	// ������Ԃ�
	return S_OK;
}

//========================================
// �t�F�[�h�̏I������
//========================================
void CFade::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{			
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//========================================
// �t�F�[�h�̍X�V����
//========================================
void CFade::Update(void)
{
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{ // �t�F�[�h�C�����

			// �|���S���𓧖��ɂ��Ă���
			m_color.a -= FADE_ADD_ALPHA;

			if (m_color.a <= 0.0f)
			{ // �����x��0.0f�𒴂�����

				// �����x��0.0f�ɂ���
				m_color.a = 0.0f;

				// �������Ă��Ȃ���Ԃɂ���
				m_fade = FADE_NONE;
			}
		}
		else if (m_fade == FADE_OUT)
		{ // �t�F�[�h�A�E�g���

			// �|���S����s�����ɂ��Ă���
			m_color.a += FADE_ADD_ALPHA;

			if (m_color.a >= 1.0f)
			{ // �����x��1.0f�𒴂�����

				// �����x��1.0f�ɂ���
				m_color.a = 1.0f;

				// �t�F�[�h�C����Ԃɂ���
				m_fade = FADE_IN;

				// ���[�h�ݒ�(���̉�ʂɈڍs)
				CManager::Get()->SetMode(m_modeNext);
			}
		}

		// ���_�J���[�̐ݒ�
		pVtx[0].col = m_color;
		pVtx[1].col = m_color;
		pVtx[2].col = m_color;
		pVtx[3].col = m_color;
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	// �f�o�b�O�\��
	CManager::Get()->GetDebugProc()->Print("�t�F�[�h�̏�ԁF%d\n�t�F�[�h�̐F�F%f\n", m_fade, m_color.a);
}

//=====================================
// �t�F�[�h�̕`�揈��
//=====================================
void CFade::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0,
		m_pVtxBuff,								// ���_�o�b�t�@�ւ̃|�C���^
		0,
		sizeof(VERTEX_2D));						// ���_���\���̂̃T�C�Y

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, nullptr);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
		0,											// �`�悷��ŏ��̒��_�C���f�b�N�X
		2);											// �`�悷��v���~�e�B�u��
}

//=====================================
// �t�F�[�h�̐ݒ菈��
//=====================================
void CFade::SetFade(CScene::MODE modeNext)
{
	if (CManager::Get()->GetFade()->GetFade() == CFade::FADE_NONE)
	{ // �t�F�[�h��Ԃ� NONE �������ꍇ

		// �t�F�[�h�A�E�g��Ԃɂ���
		m_fade = FADE_OUT;

		// ���̉��(���[�h)��ݒ�
		m_modeNext = modeNext;

		// �����|���S��(����)�ɂ��Ă���
		m_color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	}
}

//=====================================
// �t�F�[�h�̎擾����
//=====================================
CFade::FADE CFade::GetFade(void)
{
	// �t�F�[�h�̕ϐ���Ԃ�
	return m_fade;
}

//=====================================
// �ÓI�����o�ϐ�
//=====================================
CFade* CFade::Create(CScene::MODE modeNext)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CFade* pFade = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pFade == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pFade = new CFade;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pFade != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pFade->Init(modeNext)))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �t�F�[�h�̃|�C���^��Ԃ�
	return pFade;
}