//============================================
//
// ���b�V��2D�̃��C������[objectmesh2D.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "renderer.h"
#include "objectmesh2D.h"
#include "texture.h"

//=========================================
// �R���X�g���N�^
//=========================================
CMesh2D::CMesh2D() : CObject(CObject::TYPE_NONE, CObject::PRIORITY_BG)
{
	// �R���X�g���N�^�̔�
	Box();
}

//=========================================
// �I�[�o�[���[�h�R���X�g���N�^
//=========================================
CMesh2D::CMesh2D(CObject::TYPE type, PRIORITY priority) : CObject(type, priority)
{
	// �R���X�g���N�^�̔�
	Box();
}

//=========================================
// �f�X�g���N�^
//=========================================
CMesh2D::~CMesh2D()
{

}

//=========================================
// �R���X�g���N�^�̔�
//=========================================
void CMesh2D::Box(void)
{
	// �S�Ă̒l���N���A����
	m_pVtxBuff = nullptr;			// ���_�o�b�t�@�ւ̃|�C���^
	m_pos = NONE_D3DXVECTOR3;		// �ʒu
	m_posOld = m_pos;				// �O��̈ʒu
	m_size = NONE_D3DXVECTOR3;		// �T�C�Y
	m_nDivi = 0;					// ������
	m_nNumVtx = 0;					// �����_��
	m_nTexIdx = NONE_TEXIDX;		// �e�N�X�`���̃C���f�b�N�X
}

//===========================================
// �I�u�W�F�N�g2D�̏���������
//===========================================
HRESULT CMesh2D::Init(void)
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
void CMesh2D::Uninit(void)
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
void CMesh2D::Update(void)
{

}

//===========================================
// �I�u�W�F�N�g2D�̕`�揈��
//===========================================
void CMesh2D::Draw(void)
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
void CMesh2D::BindTexture(const int nIdx)
{
	// �e�N�X�`�������蓖�Ă�
	m_nTexIdx = nIdx;
}

//===========================================
// �ʒu�ݒ菈��
//===========================================
void CMesh2D::SetPos(const D3DXVECTOR3& pos)
{
	// �ʒu��ݒ肷��
	m_pos = pos;
}

//===========================================
// �ʒu�擾����
//===========================================
D3DXVECTOR3 CMesh2D::GetPos(void) const
{
	// �ʒu��Ԃ�
	return m_pos;
}

//===========================================
// �O��̈ʒu�ݒ菈��
//===========================================
void CMesh2D::SetPosOld(const D3DXVECTOR3& posOld)
{
	// �O��̈ʒu��ݒ肷��
	m_posOld = posOld;
}

//===========================================
// �O��̈ʒu�擾����
//===========================================
D3DXVECTOR3 CMesh2D::GetPosOld(void) const
{
	// �O��̈ʒu��Ԃ�
	return m_posOld;
}

//===========================================
// �T�C�Y�ݒ菈��
//===========================================
void CMesh2D::SetSize(const D3DXVECTOR3& size)
{
	// �T�C�Y��ݒ肷��
	m_size = size;
}

//===========================================
// �T�C�Y�擾����
//===========================================
D3DXVECTOR3 CMesh2D::GetSize(void) const
{
	// �T�C�Y��Ԃ�
	return m_size;
}

//===========================================
// �������̐ݒ菈��
//===========================================
void CMesh2D::SetDivi(const int nDivi)
{
	// ��������ݒ肷��
	m_nDivi = nDivi;
}

//===========================================
// �������̎擾����
//===========================================
int CMesh2D::GetDivi(void) const
{
	// ��������Ԃ�
	return m_nDivi;
}

//===========================================
// �����_���̐ݒ菈��
//===========================================
void CMesh2D::SetNumVtx(void)
{
	// �����_����ݒ肷��
	m_nNumVtx = (m_nDivi + 1) * 2;
}

//===========================================
// �����_���̎擾����
//===========================================
int CMesh2D::GetNumVtx(void) const
{
	// �����_����Ԃ�
	return m_nNumVtx;
}

//===========================================
// �e�N�X�`���̃C���f�b�N�X�̎擾����
//===========================================
int CMesh2D::GetTexIdx(void) const
{
	// �e�N�X�`���̃C���f�b�N�X��Ԃ�
	return m_nTexIdx;
}

//===========================================
// ���_���̐ݒ�
//===========================================
void CMesh2D::SetVertex(void)
{
	VERTEX_2D * pVtx;											// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWidth = 0; nCntWidth < m_nDivi + 1; nCntWidth++)
	{
		for (int nCntHeight = 0; nCntHeight < 2; nCntHeight++)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3
			(
				m_pos.x + (nCntWidth * (m_size.x / (m_nDivi / 2))) - m_size.x,	// X���W
				m_pos.y - (nCntHeight * (m_size.y * 2.0f)) + m_size.y,		// Y���W
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
void CMesh2D::SetVtxColor(const D3DXCOLOR& col)
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
void CMesh2D::SetVtxColor(const int nVtx, const D3DXCOLOR& col1, const D3DXCOLOR& col2)
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
void CMesh2D::SetVtxTexture(void)
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
			tex.x = (1.0f / m_nDivi) * nCntWidth;
			tex.y = (float)nCntHeight;

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
void CMesh2D::SetVertexAll(void)
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
CMesh2D* CMesh2D::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const int nDivi)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CMesh2D* pMesh = nullptr;	// �I�u�W�F�N�g2D�̃C���X�^���X�𐶐�

	if (pMesh == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pMesh = new CMesh2D;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pMesh != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ���̐ݒ菈��
		pMesh->m_pos = pos;								// �ʒu
		pMesh->m_size = size;							// �T�C�Y
		pMesh->m_nDivi = nDivi;							// ������
		pMesh->m_nNumVtx = 2 * pMesh->m_nDivi + 2;		// �����_��

		// ����������
		if (FAILED(pMesh->Init()))
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
	return pMesh;
}