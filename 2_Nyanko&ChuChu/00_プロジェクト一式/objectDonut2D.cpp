//============================================
//
// �h�[�i�c2D�̃��C������[donut2D.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "objectDonut2D.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "useful.h"

//=========================================
// �R���X�g���N�^
//=========================================
CDonut2D::CDonut2D() : CObject(CObject::TYPE_NONE, CObject::PRIORITY_BG)
{
	// �R���X�g���N�^�̔�
	Box();
}

//=========================================
// �I�[�o�[���[�h�R���X�g���N�^
//=========================================
CDonut2D::CDonut2D(CObject::TYPE type, PRIORITY priority) : CObject(type, priority)
{
	// �R���X�g���N�^�̔�
	Box();
}

//=========================================
// �f�X�g���N�^
//=========================================
CDonut2D::~CDonut2D()
{

}

//=========================================
// �R���X�g���N�^�̔�
//=========================================
void CDonut2D::Box(void)
{
	// �S�Ă̒l���N���A����
	m_pVtxBuff = nullptr;						// ���_�o�b�t�@�ւ̃|�C���^
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu
	m_posOld = m_pos;							// �O��̈ʒu
	m_fSize = 0.0f;								// �T�C�Y
	m_fDistance = 0.0f;							// ����
	m_nDivi = 0;								// ������
	m_nNumVtx = 0;								// �����_��
	m_nTexIdx = NONE_TEXIDX;					// �e�N�X�`���̃C���f�b�N�X
}

//===========================================
// �I�u�W�F�N�g2D�̏���������
//===========================================
HRESULT CDonut2D::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * m_nNumVtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL)))
	{ // �o�b�t�@�̐����Ɏ��s�����ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// ���_���̐ݒ菈��
	SetVertexAll();

	if (m_pVtxBuff == nullptr)
	{ // ���_�o�b�t�@�̃|�C���^��NULL�̏ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �l��Ԃ�
	return S_OK;
}

//===========================================
// �I�u�W�F�N�g2D�̏I������
//===========================================
void CDonut2D::Uninit(void)
{
	if (m_pVtxBuff != nullptr)
	{ // ���_�o�b�t�@�̔j��

		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	// �j������
	Release();
}

//===========================================
// �I�u�W�F�N�g2D�̍X�V����
//===========================================
void CDonut2D::Update(void)
{

}

//===========================================
// �I�u�W�F�N�g2D�̕`�揈��
//===========================================
void CDonut2D::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0,
		m_pVtxBuff,								// ���_�o�b�t�@�ւ̃|�C���^
		0,
		sizeof(VERTEX_2D));						// ���_���\���̂̃T�C�Y

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, CManager::Get()->GetTexture()->GetAddress(m_nTexIdx));

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
		0,										// �`�悷��ŏ��̒��_�C���f�b�N�X
		m_nNumVtx - 2);							// �`�悷��v���~�e�B�u��
}

//===========================================
// �e�N�X�`���̊��蓖�ď���
//===========================================
void CDonut2D::BindTexture(const int nIdx)
{
	// �e�N�X�`�������蓖�Ă�
	m_nTexIdx = nIdx;
}

//===========================================
// �ʒu�ݒ菈��
//===========================================
void CDonut2D::SetPos(const D3DXVECTOR3& pos)
{
	// �ʒu��ݒ肷��
	m_pos = pos;
}

//===========================================
// �ʒu�擾����
//===========================================
D3DXVECTOR3 CDonut2D::GetPos(void) const
{
	// �ʒu��Ԃ�
	return m_pos;
}

//===========================================
// �O��̈ʒu�ݒ菈��
//===========================================
void CDonut2D::SetPosOld(const D3DXVECTOR3& posOld)
{
	// �O��̈ʒu��ݒ肷��
	m_posOld = posOld;
}

//===========================================
// �O��̈ʒu�擾����
//===========================================
D3DXVECTOR3 CDonut2D::GetPosOld(void) const
{
	// �O��̈ʒu��Ԃ�
	return m_posOld;
}

//===========================================
// �T�C�Y�ݒ菈��
//===========================================
void CDonut2D::SetSize(const float size)
{
	// �T�C�Y��ݒ肷��
	m_fSize = size;
}

//===========================================
// �T�C�Y�擾����
//===========================================
float CDonut2D::GetSize(void) const
{
	// �T�C�Y��Ԃ�
	return m_fSize;
}

//===========================================
// �����̐ݒ菈��
//===========================================
void CDonut2D::SetDistance(const float fDist)
{
	// ������ݒ肷��
	m_fDistance = fDist;
}

//===========================================
// �����̎擾����
//===========================================
float CDonut2D::GetDistance(void) const
{
	// ������Ԃ�
	return m_fDistance;
}

//===========================================
// �������̐ݒ菈��
//===========================================
void CDonut2D::SetDivi(const int nDivi)
{
	// ��������ݒ肷��
	m_nDivi = nDivi;
}

//===========================================
// �������̎擾����
//===========================================
int CDonut2D::GetDivi(void) const
{
	// ��������Ԃ�
	return m_nDivi;
}

//===========================================
// �����_���̐ݒ菈��
//===========================================
void CDonut2D::SetNumVtx(void)
{
	// �����_����ݒ肷��
	m_nNumVtx = (m_nDivi + 1) * 2;
}

//===========================================
// �����_���̎擾����
//===========================================
int CDonut2D::GetNumVtx(void) const
{
	// �����_����Ԃ�
	return m_nNumVtx;
}

//===========================================
// �e�N�X�`���̃C���f�b�N�X�̎擾����
//===========================================
int CDonut2D::GetTexIdx(void) const
{
	// �e�N�X�`���̃C���f�b�N�X��Ԃ�
	return m_nTexIdx;
}

//===========================================
// ���_���̐ݒ�
//===========================================
void CDonut2D::SetVertex(void)
{
	// ���[�J���ϐ��錾
	float fAngle;		// ����
	float fLength;		// ����

	VERTEX_2D * pVtx;											// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWidth = 0; nCntWidth < m_nDivi + 1; nCntWidth++)
	{
		for (int nCntHeight = 0; nCntHeight < 2; nCntHeight++)
		{
			// �p�x���Z�o����
			fAngle = D3DX_PI * (nCntWidth * (float)(1.0f / ((m_nDivi) / 2)));

			// �����Z�o����
			fLength = m_fDistance + (m_fSize * nCntHeight);

			// �p�x�̐��K��
			useful::RotNormalize(&fAngle);

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3
			(
				m_pos.x + (sinf(fAngle) * fLength),
				m_pos.y - (cosf(fAngle) * fLength),
				0.0f
			);

			// ���_�̃|�C���^��i�߂�
			pVtx++;
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================================
// ���_�̐F�ݒ菈��
//===========================================
void CDonut2D::SetVtxColor(const D3DXCOLOR& col)
{
	VERTEX_2D* pVtx;											//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < m_nNumVtx; nCnt++)
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].col = col;

		// ���_�f�[�^��i�߂�
		pVtx++;
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================================
// ���_�̐F(���͈�)�ݒ菈��
//===========================================
void CDonut2D::SetVtxColor(const int nVtx, const D3DXCOLOR& col1, const D3DXCOLOR& col2)
{
	VERTEX_2D* pVtx;											//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < m_nNumVtx; nCnt++)
	{
		if (nVtx > nCnt)
		{ // ���_������蒴�߂̏ꍇ

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].col = col1;
		}
		else
		{ // ��L�ȊO

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].col = col2;
		}

		// ���_�f�[�^��i�߂�
		pVtx++;
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================================
// �e�N�X�`�����W�̐ݒ菈��
//===========================================
void CDonut2D::SetVtxTexture(void)
{
	// ���[�J���ϐ��錾
	VERTEX_2D * pVtx;				// ���_���ւ̃|�C���^
	D3DXVECTOR2 tex;				// �e�N�X�`�����W

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWidth = 0; nCntWidth < m_nDivi + 1; nCntWidth++)
	{
		for (int nCntHeight = 0; nCntHeight < 2; nCntHeight++)
		{
			tex.x = (float)(nCntHeight);
			tex.y = (float)((1.0f / (float)(m_nDivi)) * nCntWidth);

			//���_���W�̐ݒ�
			pVtx[0].tex = tex;

			// ���_�̃|�C���^��i�߂�
			pVtx++;
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================================
// �S�Ă̒��_���̐ݒ�
//===========================================
void CDonut2D::SetVertexAll(void)
{
	// ���_���W�̐ݒ菈��
	SetVertex();

	VERTEX_2D * pVtx;											//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < m_nNumVtx; nCnt++)
	{
		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ���_�f�[�^��i�߂�
		pVtx++;
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	// �e�N�X�`�����W�̐ݒ菈��
	SetVtxTexture();
}

//===========================================
// ��������
//===========================================
CDonut2D* CDonut2D::Create(const D3DXVECTOR3& pos, const float fSize, const float fDist, const int nDivi)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CDonut2D* pDonut = nullptr;	// �I�u�W�F�N�g2D�̃C���X�^���X�𐶐�

	if (pDonut == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pDonut = new CDonut2D;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pDonut != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ���̐ݒ菈��
		pDonut->m_pos = pos;
		pDonut->m_fSize = fSize;
		pDonut->m_fDistance = fDist;
		pDonut->m_nDivi = nDivi;

		// ����������
		if (FAILED(pDonut->Init()))
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

	// �I�u�W�F�N�g2D�̃|�C���^��Ԃ�
	return pDonut;
}