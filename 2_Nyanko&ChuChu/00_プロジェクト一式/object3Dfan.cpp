//============================================
//
// �I�u�W�F�N�g3D�t�@���̃��C������[object3Dfan.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "object3Dfan.h"
#include "renderer.h"
#include "manager.h"
#include "useful.h"

//=========================================
// �R���X�g���N�^
//=========================================
CObject3DFan::CObject3DFan() : CObject(CObject::TYPE_3DPOLYGON, CObject::PRIORITY_BG)
{
	// �R���X�g���N�^�̔�
	Box();
}

//=========================================
// �I�[�o�[���[�h�R���X�g���N�^
//=========================================
CObject3DFan::CObject3DFan(CObject::TYPE type, PRIORITY priority) : CObject(type, priority)
{
	// �R���X�g���N�^�̔�
	Box();
}

//=========================================
// �f�X�g���N�^
//=========================================
CObject3DFan::~CObject3DFan()
{

}

//==============================
// �R���X�g���N�^�̔�
//==============================
void CObject3DFan::Box(void)
{
	// �S�Ă̒l���N���A����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �O��̈ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ����
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �T�C�Y
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// �F
	m_pVtxBuff = nullptr;							// ���_�o�b�t�@�̃|�C���^
	ZeroMemory(&m_mtxWorld, sizeof(m_mtxWorld));	// ���[���h�}�g���b�N�X
	m_nNumAngle = 0;								// �p�x�̐�
	m_fRadius = 0.0f;								// ���a
	m_nTexIdx = NONE_TEXIDX;						// �e�N�X�`���̃C���f�b�N�X
}

//===========================================
// �I�u�W�F�N�g3D�̏���������
//===========================================
HRESULT CObject3DFan::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumAngle * 3,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL)))
	{ // �o�b�t�@�̐����Ɏ��s�����ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// ���[�J���ϐ��錾
	float fAngle = D3DX_PI / m_nNumAngle;	// �p�x
	VERTEX_3D * pVtx;						//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < m_nNumAngle; nCnt++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �p�x���Z�o����
		fAngle = ((float)((D3DX_PI * 2) / m_nNumAngle) * nCnt) - (D3DX_PI * 2);

		// �����̐��K��
		useful::RotNormalize(&fAngle);

		pVtx[1].pos = D3DXVECTOR3(sinf(fAngle) * m_fRadius, 0.0f, cosf(fAngle) * m_fRadius);

		// �p�x���Z�o����
		fAngle = ((float)((D3DX_PI * 2) / m_nNumAngle) * (nCnt + 1)) - (D3DX_PI * 2);

		// �����̐��K��
		useful::RotNormalize(&fAngle);

		pVtx[2].pos = D3DXVECTOR3(sinf(fAngle) * m_fRadius, 0.0f, cosf(fAngle) * m_fRadius);

		// �@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);
		pVtx[1].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);
		pVtx[2].col = D3DXCOLOR(m_col.r, m_col.g, m_col.b, m_col.a);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);

		// ���_�f�[�^��3���i�߂�
		pVtx += 3;
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

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
// �I�u�W�F�N�g3D�̏I������
//===========================================
void CObject3DFan::Uninit(void)
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
// �I�u�W�F�N�g3D�̍X�V����
//===========================================
void CObject3DFan::Update(void)
{
	// ���_�̐ݒ菈��
	SetVertex();
}

//===========================================
// �I�u�W�F�N�g3D�̕`�揈��
//===========================================
void CObject3DFan::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;			// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;						// �r���[�}�g���b�N�X�擾�p

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ���C�e�B���O��OFF�ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0,
		m_pVtxBuff,									// ���_�o�b�t�@�ւ̃|�C���^
		0,
		sizeof(VERTEX_3D));							// ���_���\���̂̃T�C�Y

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLELIST,		// �v���~�e�B�u�̎��
		0,											// �`�悷��ŏ��̒��_�C���f�b�N�X
		m_nNumAngle);								// �`�悷��v���~�e�B�u��

	// ���C�e�B���O��ON�ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//===========================================
// ���_���̐ݒ�
//===========================================
void CObject3DFan::SetVertex(void)
{
	float fAngle;									// �p�x

	VERTEX_3D * pVtx;											//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < m_nNumAngle; nCnt++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �p�x���Z�o����
		fAngle = ((float)((D3DX_PI * 2) / m_nNumAngle) * nCnt) - (D3DX_PI * 2);

		// �����̐��K��
		useful::RotNormalize(&fAngle);

		pVtx[1].pos = D3DXVECTOR3(sinf(fAngle) * m_fRadius, 0.0f, cosf(fAngle) * m_fRadius);

		// �p�x���Z�o����
		fAngle = ((float)((D3DX_PI * 2) / m_nNumAngle) * (nCnt + 1)) - (D3DX_PI * 2);

		// �����̐��K��
		useful::RotNormalize(&fAngle);

		pVtx[2].pos = D3DXVECTOR3(sinf(fAngle) * m_fRadius, 0.0f, cosf(fAngle) * m_fRadius);

		// ���_�f�[�^��3���i�߂�
		pVtx += 3;
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================================
// ���_�J���[�̐ݒ菈��
//===========================================
void CObject3DFan::SetVtxColor(const D3DXCOLOR& col)
{
	VERTEX_3D * pVtx;											//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < m_nNumAngle; nCnt++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].col = col;
		pVtx[1].col = col;
		pVtx[2].col = col;

		// ���_�f�[�^��3���i�߂�
		pVtx += 3;
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================================
// ���_�J���[�ׂ̍����ݒ菈��
//===========================================
void CObject3DFan::SetVtxColor(const D3DXCOLOR& normalCol, const D3DXCOLOR& rezCol, int nEndResVtx)
{
	VERTEX_3D * pVtx;											//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < m_nNumAngle; nCnt++)
	{
		if (nCnt < nEndResVtx)
		{ // �񕜂��Ă�͈͂̒��_�̂Ƃ�

			// ���_���W�̐ݒ�
			pVtx[0].col = rezCol;
			pVtx[1].col = rezCol;
			pVtx[2].col = rezCol;
		}
		else
		{ // �񕜂��Ă�͈͊O

			// ���_���W�̐ݒ�
			pVtx[0].col = normalCol;
			pVtx[1].col = normalCol;
			pVtx[2].col = normalCol;
		}

		// ���_�f�[�^��3���i�߂�
		pVtx += 3;
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================================
// �e�N�X�`���̊��蓖�ď���
//===========================================
void CObject3DFan::BindTexture(const int nIdx)
{
	// �e�N�X�`�������蓖�Ă�
	m_nTexIdx = nIdx;
}

//===========================================
// �ʒu�ݒ菈��
//===========================================
void CObject3DFan::SetPos(const D3DXVECTOR3& pos)
{
	// �ʒu��ݒ肷��
	m_pos = pos;
}

//===========================================
// �ʒu�擾����
//===========================================
D3DXVECTOR3 CObject3DFan::GetPos(void) const
{
	// �ʒu��Ԃ�
	return m_pos;
}

//===========================================
// �O��̈ʒu�ݒ菈��
//===========================================
void CObject3DFan::SetPosOld(const D3DXVECTOR3& posOld)
{
	// �O��̈ʒu��ݒ肷��
	m_posOld = posOld;
}

//===========================================
// �O��̈ʒu�擾����
//===========================================
D3DXVECTOR3 CObject3DFan::GetPosOld(void) const
{
	// �O��̈ʒu��Ԃ�
	return m_posOld;
}

//===========================================
// �����ݒ菈��
//===========================================
void CObject3DFan::SetRot(const D3DXVECTOR3& rot)
{
	// ������ݒ肷��
	m_rot = rot;
}

//===========================================
// �����擾����
//===========================================
D3DXVECTOR3 CObject3DFan::GetRot(void) const
{
	// ������Ԃ�
	return m_rot;
}

//===========================================
// �T�C�Y�ݒ菈��
//===========================================
void CObject3DFan::SetSize(const D3DXVECTOR3& size)
{
	// �T�C�Y��ݒ肷��
	m_size = size;
}

//===========================================
// �T�C�Y�擾����
//===========================================
D3DXVECTOR3 CObject3DFan::GetSize(void) const
{
	// �T�C�Y��Ԃ�
	return m_size;
}

//===========================================
// �p�x�̑����̐ݒ菈��
//===========================================
void CObject3DFan::SetNumAngle(const int nNum)
{
	// �p�x�̑����̐ݒ肷��
	m_nNumAngle = nNum;
}

//===========================================
// �p�x�̑����̎擾����
//===========================================
int CObject3DFan::GetNumAngle(void) const
{
	// �p�x�̑�����Ԃ�
	return m_nNumAngle;
}

//===========================================
// ���a�̐ݒ菈��
//===========================================
void CObject3DFan::SetRadius(const float fRadius)
{
	// ���a��ݒ肷��
	m_fRadius = fRadius;
}

//===========================================
// ���a�̎擾����
//===========================================
float CObject3DFan::GetRadius(void) const
{
	// ���a��Ԃ�
	return m_fRadius;
}
//===========================================
// �F�̐ݒ菈��
//===========================================
void CObject3DFan::SetColor(const D3DXCOLOR col)
{
	// �F��ݒ肷��
	m_col = col;
}

//===========================================
// �F�̎擾����
//===========================================
D3DXCOLOR CObject3DFan::GetColor(void) const
{
	// �F��Ԃ�
	return m_col;
}

//===========================================
// ��������
//===========================================
CObject3DFan* CObject3DFan::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CObject3DFan* pObject3DFan = nullptr;	// �I�u�W�F�N�g3D�̃C���X�^���X�𐶐�

	if (pObject3DFan == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pObject3DFan = new CObject3DFan;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pObject3DFan != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		pObject3DFan->Init();
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �I�u�W�F�N�g3D�̃|�C���^��Ԃ�
	return pObject3DFan;
}