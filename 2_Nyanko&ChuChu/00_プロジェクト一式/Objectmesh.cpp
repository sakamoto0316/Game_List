//======================================================================================================================
//
//	���b�V������ [mesh.cpp]
//	Author�F��������
//
//======================================================================================================================
//**********************************************************************************************************************
//	�C���N���[�h�t�@�C��
//**********************************************************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "Objectmesh.h"
#include "mesh_manager.h"
#include "useful.h"
#include "texture.h"

#include "mesh_field.h"
#include "mesh_wall.h"
#include "mesh_cylinder.h"
#include "mesh_dome.h"

//----------------------------------------------------------------------------------------------------------------------
// �}�N����`
//----------------------------------------------------------------------------------------------------------------------
#define MESH_TXT			"data/TXT/Mesh.txt"			// ���b�V���̃e�L�X�g

//================================
// �R���X�g���N�^
//================================
CMesh::CMesh() : CObject(CObject::TYPE_FIELD, CObject::PRIORITY_BG)
{
	// �R���X�g���N�^�̔�
	Box();
}

//================================
// �I�[�o�[���[�h�R���X�g���N�^
//================================
CMesh::CMesh(CObject::TYPE type, CObject::PRIORITY priority) : CObject(type, priority)
{
	// �R���X�g���N�^�̔�
	Box();
}

//================================
// �f�X�g���N�^
//================================
CMesh::~CMesh()
{

}

//================================
// �R���X�g���N�^�̔�
//================================
void CMesh::Box(void)
{
	// �S�Ă̒l���N���A����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ����
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �T�C�Y
	m_sizeDivi = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 1������̖ʂ̃T�C�Y
	ZeroMemory(&m_mtxWorld, sizeof(D3DXMATRIX));	// ���[���h�}�g���b�N�X
	m_pVtxBuff = nullptr;							// ���_�o�b�t�@�̃|�C���^
	m_pIdxBuff = nullptr;							// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	m_type = TYPE_FIELD;							// ���
	m_vtx.x = 0;									// �����̒��_��
	m_vtx.y = 0;									// �c���̒��_��
	m_vtx.z = 0;									// �����̒��_��
	m_divi.x = 0;									// �����̕�����
	m_divi.y = 0;									// �c���̕�����
	m_divi.z = 0;									// �����̕�����
	m_nNumVtx = 0;									// �����_��
	m_nNumIdx = 0;									// ���C���f�b�N�X��
	m_nTexIdx = NONE_TEXIDX;						// �e�N�X�`���̃C���f�b�N�X
	m_bLightOff = false;							// ���C�e�B���O��

	// �S�Ă̒l���N���A����
	m_pPrev = nullptr;		// �O�̃A�E�g�{�[���ւ̃|�C���^
	m_pNext = nullptr;		// ���̃A�E�g�{�[���ւ̃|�C���^

	if (CMeshManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// �}�l�[�W���[�ւ̓o�^����
		CMeshManager::Get()->Regist(this);
	}
}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
void CMesh::SetPrev(CMesh* pPrev)
{
	// �O�̃|�C���^��ݒ肷��
	m_pPrev = pPrev;
}

//============================
// ��̃|�C���^�̐ݒ菈��
//============================
void CMesh::SetNext(CMesh* pNext)
{
	// ���̃|�C���^��ݒ肷��
	m_pNext = pNext;
}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
CMesh* CMesh::GetPrev(void) const
{
	// �O�̃|�C���^��Ԃ�
	return m_pPrev;
}

//============================
// ���̃|�C���^�̐ݒ菈��
//============================
CMesh* CMesh::GetNext(void) const
{
	// ���̃|�C���^��Ԃ�
	return m_pNext;
}

//================================
// ����������
//================================
HRESULT CMesh::Init(void)
{
	// �|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();	// �f�o�C�X�ւ̃|�C���^

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer
	( // ����
		sizeof(VERTEX_3D) * m_nNumVtx,	// �K�v���_��
		D3DUSAGE_WRITEONLY,				// �g�p���@
		FVF_VERTEX_3D,					// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,				// �������̎w��
		&m_pVtxBuff,					// ���_�o�b�t�@�ւ̃|�C���^
		NULL
	)))
	{ // ���_�̐����Ɏ��s�����ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �C���f�b�N�X�o�b�t�@�̐���
	if (FAILED(pDevice->CreateIndexBuffer
	( // ����
		sizeof(WORD) * m_nNumIdx,		// �K�v�C���f�b�N�X��
		D3DUSAGE_WRITEONLY,				// �g�p���@
		D3DFMT_INDEX16,					// �C���f�b�N�X�o�b�t�@�̃t�H�[�}�b�g
		D3DPOOL_MANAGED,				// �������̎w��
		&m_pIdxBuff,					// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
		NULL
	)))
	{ // �C���f�b�N�X�̐����Ɏ��s�����ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	switch (m_type)
	{
	case TYPE_FIELD:	// �t�B�[���h

		// �t�B�[���h�̒��_�ݒ菈��
		SetVertexField();

		// �C���f�b�N�X�̐ݒ菈��
		SetIndex(m_vtx.z, m_vtx.x);

		break;

	case TYPE_WALL:		// ��

		// �ǂ̒��_�ݒ菈��
		SetVertexWall();

		// �C���f�b�N�X�̐ݒ菈��
		SetIndex(m_vtx.y, m_vtx.x);

		break;

	case TYPE_CYLINDER:	// ��

		// ���̒��_�ݒ菈��
		SetVertexCylinder();

		// �C���f�b�N�X�̐ݒ菈��
		SetIndex(m_vtx.y, m_vtx.x);

		break;

	case TYPE_DOME:		// �h�[��

		// �h�[���̒��_�ݒ菈��
		SetVertexDome();

		// �C���f�b�N�X�̐ݒ菈��
		SetIndex(m_vtx.y, m_vtx.x);

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	// ������Ԃ�
	return S_OK;
}

//================================
// �I������
//================================
void CMesh::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{ // �ϐ� (g_pVtxBuffMeshField) ��NULL�ł͂Ȃ��ꍇ

		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	// �C���f�b�N�X�o�b�t�@�̔j��
	if (m_pIdxBuff != nullptr)
	{ // �ϐ� (g_pIdxBuffMeshField) ��NULL�ł͂Ȃ��ꍇ

		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
	}

	// �j������
	Release();

	if (CMeshManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// ���X�g�\���̈�����������
		CMeshManager::Get()->Pull(this);
	}

	// ���X�g�\���֌W�̃|�C���^�� NULL �ɂ���
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//================================
// �X�V����
//================================
void CMesh::Update(void)
{

}

//================================
// �`�揈��
//================================
void CMesh::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	if (m_bLightOff == true)
	{ // ���C�e�B���O�󋵂� true �̏ꍇ

		// ���C�e�B���O��OFF�ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

		// �`�揈���̒��g
		DrawProcess();

		// ���C�e�B���O��ON�ɂ���
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
	else
	{ // ��L�ȊO

		// �`�揈���̒��g
		DrawProcess();
	}
}

//================================
// �`�揈���̒��g
//================================
void CMesh::DrawProcess(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X

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
		m_pVtxBuff,					// ���_�o�b�t�@�ւ̃|�C���^
		0,
		sizeof(VERTEX_3D));			// ���_���\���̂̃T�C�Y

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, CManager::Get()->GetTexture()->GetAddress(m_nTexIdx));

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̎��
		0,													// �`�悷��ŏ��̒��_�C���f�b�N�X
		0,
		m_nNumVtx,											// �p�ӂ������_�̐�
		0,
		m_nNumIdx - 2);										// �`�悷��v���~�e�B�u��
}

//================================
// �t�B�[���h�̏��ݒ菈��
//================================
void CMesh::SetDataField(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& size, const SGrid& Divi)
{
	// �S�Ă̒l������������
	m_pos = pos;						// �ʒu
	m_rot = rot;						// ����
	m_size = size;						// �傫��
	m_divi.x = Divi.x;					// �����̕�����
	m_divi.y = 0;						// �c���̕�����
	m_divi.z = Divi.z;					// �����̕�����
	m_vtx.x = m_divi.x + 1;				// �����̒��_��
	m_vtx.y = 0;						// �c���̒��_��
	m_vtx.z = m_divi.z + 1;				// �����̒��_��
	m_type = TYPE_FIELD;				// ���
	m_nNumVtx = m_vtx.x * m_vtx.z;		// �����_��
	m_nNumIdx = (2 * (m_vtx.x * m_divi.z)) + ((m_vtx.z - 2) * 2);		// ���C���f�b�N�X��
	m_nTexIdx = NONE_TEXIDX;			// �e�N�X�`���̃C���f�b�N�X
	m_sizeDivi = D3DXVECTOR3			// 1������̖ʂ̃T�C�Y
	(
		m_size.x / (float)(m_divi.x),
		0.0f,
		m_size.z / (float)(m_divi.z)
	);
}

//================================
// �ǂ̏��ݒ菈��
//================================
void CMesh::SetDataWall(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& size, const SGrid& Divi)
{
	// ������ݒ�
	m_pos = pos;						// �ʒu
	m_rot = rot;						// ����
	m_size = size;						// �傫��
	m_divi.x = Divi.x;					// �����̕�����
	m_divi.y = Divi.y;					// �c���̕�����
	m_divi.z = 0;						// �����̕�����
	m_vtx.x = m_divi.x + 1;				// �����̒��_��
	m_vtx.y = m_divi.y + 1;				// �����̒��_��
	m_vtx.z = 0;						// �����̒��_��
	m_type = TYPE_WALL;					// ���
	m_nNumVtx = m_vtx.x * m_vtx.y;		// �����_��
	m_nNumIdx = (2 * (m_vtx.x * m_divi.y)) + ((m_vtx.y - 2) * 2);		// ���C���f�b�N�X��
	m_nTexIdx = NONE_TEXIDX;			// �e�N�X�`���̃C���f�b�N�X
	m_sizeDivi = D3DXVECTOR3			// 1������̖ʂ̃T�C�Y
	(
		m_size.x / (float)(m_divi.x),
		m_size.y / (float)(m_divi.y),
		0.0f
	);
}

//================================
// ���̏��ݒ菈��
//================================
void CMesh::SetDataCylinder(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const float fCircumSize, const float fHeightSize, const int nCircum, const int nHeight)
{
	// ���̐ݒ�
	m_pos = pos;					// �ʒu
	m_rot = rot;					// ����
	m_size.x = fCircumSize;			// �~���̃T�C�Y
	m_size.y = fHeightSize;			// �����̃T�C�Y
	m_size.z = fCircumSize;			// �����̃T�C�Y
	m_divi.x = nCircum;				// �~���̕�����
	m_divi.y = nHeight;				// �����̕�����
	m_divi.z = nCircum;				// �����̕�����
	m_vtx.x = m_divi.x + 1;			// �~���̒��_��
	m_vtx.y = m_divi.y + 1;			// �����̒��_��
	m_vtx.z = m_divi.z + 1;			// �~���̒��_��
	m_type = TYPE_CYLINDER;			// ���
	m_nNumVtx = m_vtx.x * m_vtx.y;	// �����_��
	m_nNumIdx = (2 * (m_vtx.x * m_divi.y)) + ((m_vtx.y - 2) * 2);			// ���C���f�b�N�X��
	m_nTexIdx = NONE_TEXIDX;		// �e�N�X�`���̃C���f�b�N�X
	m_sizeDivi = D3DXVECTOR3		// 1������̖ʂ̃T�C�Y
	(
		m_size.x / (float)(m_divi.x),
		m_size.y / (float)(m_divi.y),
		m_size.z / (float)(m_divi.z)
	);
}

//================================
// �h�[���̏��ݒ菈��
//================================
void CMesh::SetDataDome(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const float fCircumSize, const float fHeightSize, const int nCircum, const int nHeight)
{
	// ���̐ݒ�
	m_pos = pos;			// �ʒu
	m_rot = rot;			// ����
	m_size.x = fCircumSize;			// �~���̃T�C�Y
	m_size.y = fHeightSize;			// �����̃T�C�Y
	m_size.z = fCircumSize;			// �����̃T�C�Y
	m_divi.x = nCircum;				// �~���̕�����
	m_divi.y = nHeight;				// �����̕�����
	m_divi.z = nCircum;				// �����̕�����
	m_vtx.x = m_divi.x + 1;			// �~���̒��_��
	m_vtx.y = m_divi.y + 1;			// �����̒��_��
	m_vtx.z = m_divi.z + 1;			// �~���̒��_��
	m_type = TYPE_DOME;				// ���
	m_nNumVtx = m_vtx.x * m_vtx.y;	// �����_��
	m_nNumIdx = (2 * (m_vtx.x * m_divi.y)) + ((m_vtx.y - 2) * 2);				// ���C���f�b�N�X��
	m_nTexIdx = NONE_TEXIDX;		// �e�N�X�`���̃C���f�b�N�X
	m_sizeDivi = D3DXVECTOR3		// 1������̖ʂ̃T�C�Y
	(
		m_size.x / (float)(m_divi.x),
		m_size.y / (float)(m_divi.y),
		m_size.z / (float)(m_divi.z)
	);
}

//================================
// �e�N�X�`���̊��蓖�ď���
//================================
void CMesh::BindTexture(int nIdx)
{
	// �e�N�X�`�������蓖�Ă�
	m_nTexIdx = nIdx;
}

//================================
// �ʒu�̐ݒ菈��
//================================
void CMesh::SetPos(const D3DXVECTOR3& pos)
{
	// �ʒu��ݒ肷��
	m_pos = pos;
}

//================================
// �ʒu�̎擾����
//================================
D3DXVECTOR3 CMesh::GetPos(void) const
{
	// �ʒu��Ԃ�
	return m_pos;
}

//================================
// �����̐ݒ菈��
//================================
void CMesh::SetRot(const D3DXVECTOR3& rot)
{
	// ������ݒ肷��
	m_rot = rot;
}

//================================
// �����̎擾����
//================================
D3DXVECTOR3 CMesh::GetRot(void) const
{
	// ������Ԃ�
	return m_rot;
}

//================================
// �g�嗦�̐ݒ菈��
//================================
void CMesh::SetSize(const D3DXVECTOR3& size)
{
	// �T�C�Y��ݒ肷��
	m_size = size;
}

//================================
// �g�嗦�̎擾����
//================================
D3DXVECTOR3 CMesh::GetSize(void) const
{
	// �T�C�Y��Ԃ�
	return m_size;
}

//================================
// ���C�e�B���O�̐ݒ菈��
//================================
void CMesh::SetLighting(const bool bLighting)
{
	// ���C�e�B���O�󋵂�ݒ肷��
	m_bLightOff = bLighting;
}

//================================
// ���_�̐ݒ菈��
//================================
void CMesh::SetVertexField(void)
{
	VERTEX_3D *pVtx;							// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntDep = 0; nCntDep < m_vtx.z; nCntDep++)
	{
		for (int nCntWid = 0; nCntWid < m_vtx.x; nCntWid++)
		{
			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3
			( // ����
				(nCntWid * m_sizeDivi.x) - (m_size.x / 2.0f),	// X���W
				0.0f,											// Y���W
				(m_size.z / 2.0f) - (nCntDep * m_sizeDivi.z)	// Z���W
			);

			// �@���x�N�g���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(nCntWid * (1.0f / (float)(m_divi.x)), nCntDep * (1.0f / (float)(m_divi.z)));

			pVtx++;				// ���_�f�[�^��i�߂�
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================
// �ǂ̐ݒ菈��
//================================
void CMesh::SetVertexWall(void)
{
	VERTEX_3D *pVtx;							// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntDep = 0; nCntDep < m_vtx.y; nCntDep++)
	{
		for (int nCntWid = 0; nCntWid < m_vtx.x; nCntWid++)
		{
			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3
			( // ����
				(nCntWid * m_sizeDivi.x) - (m_size.x / 2.0f),	// X���W
				m_size.y - (nCntDep * m_sizeDivi.y),			// Y���W
				0.0f											// Z���W
			);

			// �@���x�N�g���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(nCntWid * (1.0f / (float)(m_divi.x)), nCntDep * (1.0f / (float)(m_divi.y)));

			pVtx++;				// ���_�f�[�^��i�߂�
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================
// ���̐ݒ菈��
//================================
void CMesh::SetVertexCylinder(void)
{
	VERTEX_3D *pVtx;							// ���_���ւ̃|�C���^
	float fAngle;			// �p�x�Z�o�p�ϐ�

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntHeight = 0; nCntHeight < m_vtx.y; nCntHeight++)
	{
		for (int nCntCircum = 0; nCntCircum < m_vtx.x; nCntCircum++)
		{
			// �p�x���Z�o����
			fAngle = D3DX_PI * (nCntCircum * (float)(1.0f / (m_divi.x / 2)));

			// �p�x�̐��K��
			useful::RotNormalize(&fAngle);

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3
			(
				(-sinf(fAngle) * m_size.x),
				m_size.y - (m_sizeDivi.y * nCntHeight),
				(-cosf(fAngle) * m_size.z)
			);

			//�@���x�N�g���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(((float)(1.0f / m_divi.x) * nCntCircum), ((float)(1.0f / m_divi.y) * nCntHeight));

			pVtx++;			// ���_�f�[�^��i�߂�
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================
// �h�[���̐ݒ菈��
//================================
void CMesh::SetVertexDome(void)
{
	// ���[�J���ϐ��錾
	VERTEX_3D *pVtx;		// ���_���ւ̃|�C���^
	float fAngle;			// ����
	float fHeiAngle;		// �����̕���

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntHeight = 0; nCntHeight < m_vtx.y; nCntHeight++)
	{
		for (int nCntCircum = 0; nCntCircum < m_vtx.x; nCntCircum++)
		{
			// �p�x���Z�o����
			fAngle = D3DX_PI * (nCntCircum * (float)(1.0f / (m_divi.x / 2)));
			fHeiAngle = D3DX_PI - ((D3DX_PI * 0.5f) / m_divi.y) * nCntHeight;

			// �p�x�̐��K��
			useful::RotNormalize(&fAngle);
			useful::RotNormalize(&fHeiAngle);

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3
			(
				(sinf(fAngle) * ((float)(m_size.x / m_divi.y) * nCntHeight)),
				cosf(fHeiAngle) * -m_size.y,
				(cosf(fAngle) * ((float)(m_size.z / m_divi.y) * nCntHeight))
			);

			//�@���x�N�g���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2((float)((1.0f / m_divi.x) * nCntCircum), (float)((1.0f / m_divi.y) * nCntHeight));

			pVtx++;			// ���_�f�[�^��i�߂�
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================
// ���_�J���[�̐ݒ菈��
//================================
void CMesh::SetVtxColor(const D3DXCOLOR& col)
{
		// ���[�J���ϐ��錾
	VERTEX_3D *pVtx;		// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntCol = 0; nCntCol < m_nNumVtx; nCntCol++)
	{
		// ���_�J���[��ݒ肷��
		pVtx[0].col = col;

		pVtx++;			// ���_�f�[�^��i�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================
// �C���f�b�N�X�̐ݒ菈��
//================================
void CMesh::SetIndex(const int nNumVtx1, const int nNumVtx2)
{
	// ���[�J���ϐ��錾
	WORD      *pIdx;							// �C���f�b�N�X���ւ̃|�C���^
	int nIdx = 0;								// �C���f�b�N�X��

	//------------------------------------------------------------------------------------------------------------------
	//	�C���f�b�N�X���̏�����
	//------------------------------------------------------------------------------------------------------------------
	// �C���f�b�N�X�o�b�t�@�����b�N���A���_�ԍ��f�[�^�ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntDep = 1; nCntDep < nNumVtx1; nCntDep++)
	{
		if (nCntDep != 1)
		{ // �ŏ��ȊO

			// �C���f�b�N�X����ݒ肷��
			pIdx[0] = (WORD)(nNumVtx2 * nCntDep);

			// �C���f�b�N�X�f�[�^�����Z����
			pIdx++;
			nIdx++;
		}

		for (int nCntWid = 0; nCntWid < nNumVtx2; nCntWid++)
		{ // 1�w���Ƃɐݒ肷��

			// �C���f�b�N�X����ݒ肷��
			pIdx[0] = (WORD)((nNumVtx2 * nCntDep) + nCntWid);
			pIdx[1] = (WORD)((nNumVtx2 * nCntDep) - (nNumVtx2 - nCntWid));

			// �C���f�b�N�X�f�[�^��2�i�߂�
			pIdx += 2;
			nIdx += 2;

			if (nCntWid == (nNumVtx2 - 1) && nCntDep != (nNumVtx1 - 1))
			{ // �܂�Ԃ��ɓ������ꍇ

				// �C���f�b�N�X����ݒ肷��
				pIdx[0] = (WORD)((nNumVtx2 * nCntDep) - (nNumVtx2 - nCntWid));

				// �C���f�b�N�X�f�[�^�����Z����
				pIdx++;
				nIdx++;
			}
		}
	}

	// �C���f�b�N�X�o�b�t�@���A�����b�N����
	m_pIdxBuff->Unlock();
}

//================================
// ��������
//================================
CMesh* CMesh::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& size, const SGrid& Divi, const TYPE type, char* texturename, const bool bLighting)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CMesh* pMesh = nullptr;	// �I�u�W�F�N�g3D�̃C���X�^���X�𐶐�

	if (pMesh == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		switch (type)
		{
		case TYPE_FIELD:			// �t�B�[���h

			// �I�u�W�F�N�g�𐶐�
			pMesh = new CMeshField;

			break;

		case TYPE::TYPE_WALL:		// �E�H�[��

			// �I�u�W�F�N�g�𐶐�
			pMesh = new CMeshWall;

			break;

		case TYPE::TYPE_CYLINDER:	// �V�����_�[

			// �I�u�W�F�N�g�𐶐�
			pMesh = new CMeshCylinder;

			break;

		case TYPE::TYPE_DOME:		// �h�[��

			// �I�u�W�F�N�g�𐶐�
			pMesh = new CMeshDome;

			break;

		default:

			// ��~
			assert(false);

			break;
		}
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

		switch (type)
		{
		case TYPE_FIELD:	// �t�B�[���h

			// �t�B�[���h�̐ݒ菈��
			pMesh->SetDataField(pos, rot, size, Divi);

			break;

		case TYPE_WALL:		// ��

			// �ǂ̐ݒ菈��
			pMesh->SetDataWall(pos, rot, size, Divi);

			break;

		case TYPE_CYLINDER:	// ��

			// ���̐ݒ菈��
			pMesh->SetDataCylinder(pos, rot, size.x, size.y, Divi.x, Divi.y);

			break;

		case TYPE_DOME:

			// �h�[���̐ݒ菈��
			pMesh->SetDataDome(pos, rot, size.x, size.y, Divi.x, Divi.y);

			break;

		default:

			// ��~
			assert(false);

			break;
		}

		// ����������
		if (FAILED(pMesh->Init()))
		{ // �����������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// �e�N�X�`���̊��蓖�ď���
		pMesh->BindTexture(CManager::Get()->GetTexture()->Regist(texturename));

		// ���C�e�B���O�󋵂�ݒ肷��
		pMesh->m_bLightOff = bLighting;
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �I�u�W�F�N�g3D�̃|�C���^��Ԃ�
	return pMesh;
}

//================================
// �e�L�X�g�ǂݍ��ݏ���
//================================
void CMesh::TxtSet(void)
{
	// �ϐ���錾
	int nEnd;			// �e�L�X�g�ǂݍ��ݏI���̊m�F�p
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
	D3DXVECTOR3 size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �T�C�Y
	SGrid divi = { 0,0,0 };			// ������
	bool bLighting = false;			// ���C�e�B���O��

	// �ϐ��z���錾
	char aString[MAX_STRING];		// �e�L�X�g�̕�����̑���p
	char aTextureName[MAX_STRING];	// �e�N�X�`���̃p�X��

	// �|�C���^��錾
	FILE  *pFile;							// �t�@�C���|�C���^

	// �t�@�C����ǂݍ��݌`���ŊJ��
	pFile = fopen(MESH_TXT, "r");

	if (pFile != nullptr)
	{ // �t�@�C�����J�����ꍇ

		do
		{ // �ǂݍ��񂾕����� EOF �ł͂Ȃ��ꍇ���[�v

			// �t�@�C�����當�����ǂݍ���
			nEnd = fscanf(pFile, "%s", &aString[0]);	// �e�L�X�g��ǂݍ��݂������� EOF ��Ԃ�

			if (strcmp(&aString[0], "SET_MESHFIELD") == 0)
			{ // �ǂݍ��񂾕����� SET_MESHFIELD �̏ꍇ

				do
				{ // �ǂݍ��񂾕����� END_SET_MESHFIELD �ł͂Ȃ��ꍇ���[�v

					// �t�@�C�����當�����ǂݍ���
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "POS") == 0)
					{ // �ǂݍ��񂾕����� TYPE �̏ꍇ
						fscanf(pFile, "%s", &aString[0]);						// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%f%f%f", &pos.x, &pos.y, &pos.z);		// �ʒu��ǂݍ���
					}
					else if (strcmp(&aString[0], "ROT") == 0)
					{ // �ǂݍ��񂾕����� RADIUS �̏ꍇ
						fscanf(pFile, "%s", &aString[0]);						// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%f%f%f", &rot.x, &rot.y, &rot.z);		// ������ǂݍ���
					}
					else if (strcmp(&aString[0], "SIZE") == 0)
					{ // �ǂݍ��񂾕����� SIZE �̏ꍇ
						fscanf(pFile, "%s", &aString[0]);						// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%f%f%f", &size.x, &size.y, &size.z);		// �傫����ǂݍ���
					}
					else if (strcmp(&aString[0], "WIDTH") == 0)
					{ // �ǂݍ��񂾕����� WIDTH �̏ꍇ
						fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%d", &divi.x);					// �����̕�������ǂݍ���
					}
					else if (strcmp(&aString[0], "DEPTH") == 0)
					{ // �ǂݍ��񂾕����� DEPTH �̏ꍇ
						fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%d", &divi.z);					// �����̕�������ǂݍ���
					}
					else if (strcmp(&aString[0], "TEXTURE") == 0)
					{ // �ǂݍ��񂾕����� TEXTURE �̏ꍇ
						fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%s", &aTextureName[0]);			// �p�X��ǂݍ���
					}
					else if (strcmp(&aString[0], "LIGHTING") == 0)
					{ // �ǂݍ��񂾕����� LIGHTING �̏ꍇ
						fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%s", &aString[0]);				// OFF��ǂݍ���

						// ���C�e�B���O�󋵂�ݒ肷��
						bLighting = (strcmp(&aString[0], "TRUE") == 0) ? true : false;
					}

				} while (strcmp(&aString[0], "END_SET_MESHFIELD") != 0);	// �ǂݍ��񂾕����� END_SET_MESHFIELD �ł͂Ȃ��ꍇ���[�v

				// �t�B�[���h�̐�������
				Create(pos, rot, size, divi, TYPE::TYPE_FIELD, aTextureName, bLighting);
			}
			else if (strcmp(&aString[0], "SET_MESHWALL") == 0)
			{ // �ǂݍ��񂾕����� SET_MESHWALL �̏ꍇ

				do
				{ // �ǂݍ��񂾕����� END_SET_MESHWALL �ł͂Ȃ��ꍇ���[�v

					// �t�@�C�����當�����ǂݍ���
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "POS") == 0)
					{ // �ǂݍ��񂾕����� TYPE �̏ꍇ
						fscanf(pFile, "%s", &aString[0]);						// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%f%f%f", &pos.x, &pos.y, &pos.z);		// �ʒu��ǂݍ���
					}
					else if (strcmp(&aString[0], "ROT") == 0)
					{ // �ǂݍ��񂾕����� RADIUS �̏ꍇ
						fscanf(pFile, "%s", &aString[0]);						// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%f%f%f", &rot.x, &rot.y, &rot.z);		// ������ǂݍ���
					}
					else if (strcmp(&aString[0], "SIZE") == 0)
					{ // �ǂݍ��񂾕����� SIZE �̏ꍇ
						fscanf(pFile, "%s", &aString[0]);						// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%f%f%f", &size.x, &size.y, &size.z);		// �傫����ǂݍ���
					}
					else if (strcmp(&aString[0], "WIDTH") == 0)
					{ // �ǂݍ��񂾕����� WIDTH �̏ꍇ
						fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%d", &divi.x);					// �����̕�������ǂݍ���
					}
					else if (strcmp(&aString[0], "HEIGHT") == 0)
					{ // �ǂݍ��񂾕����� HEIGHT �̏ꍇ
						fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%d", &divi.y);					// �c���̕�������ǂݍ���
					}
					else if (strcmp(&aString[0], "TEXTURE") == 0)
					{ // �ǂݍ��񂾕����� TEXTURE �̏ꍇ
						fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%s", &aTextureName[0]);			// �p�X��ǂݍ���
					}
					else if (strcmp(&aString[0], "LIGHTING") == 0)
					{ // �ǂݍ��񂾕����� LIGHTING �̏ꍇ
						fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%s", &aString[0]);				// OFF��ǂݍ���

						// ���C�e�B���O�󋵂�ݒ肷��
						bLighting = (strcmp(&aString[0], "TRUE") == 0) ? true : false;
					}

				} while (strcmp(&aString[0], "END_SET_MESHWALL") != 0);	// �ǂݍ��񂾕����� END_SET_MESHWALL �ł͂Ȃ��ꍇ���[�v

				// �E�H�[���̐�������
				Create(pos, rot, size, divi, TYPE::TYPE_WALL, aTextureName, bLighting);
			}
			else if (strcmp(&aString[0], "SET_MESHCYLINDER") == 0)
			{ // �ǂݍ��񂾕����� SET_MESHCYLINDER �̏ꍇ

				do
				{ // �ǂݍ��񂾕����� END_SET_MESHCYLINDER �ł͂Ȃ��ꍇ���[�v

					// �t�@�C�����當�����ǂݍ���
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "POS") == 0)
					{ // �ǂݍ��񂾕����� POS �̏ꍇ
						fscanf(pFile, "%s", &aString[0]);					// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%f%f%f", &pos.x, &pos.y, &pos.z);	// �ʒu��ǂݍ���
					}
					else if (strcmp(&aString[0], "ROT") == 0)
					{ // �ǂݍ��񂾕����� ROT �̏ꍇ
						fscanf(pFile, "%s", &aString[0]);					// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%f%f%f", &rot.x, &rot.y, &rot.z);	// ������ǂݍ���
					}
					else if (strcmp(&aString[0], "SIZE") == 0)
					{ // �ǂݍ��񂾕����� CIRCUMSIZE �̏ꍇ
						fscanf(pFile, "%s", &aString[0]);					// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%f%f", &size.x, &size.y);			// �~���̃T�C�Y��ǂݍ���

						// Z���̃T�C�Y��ݒ肷��
						size.z = size.x;
					}
					else if (strcmp(&aString[0], "CIRCUM") == 0)
					{ // �ǂݍ��񂾕����� CIRCUM �̏ꍇ
						fscanf(pFile, "%s", &aString[0]);					// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%d", &divi.x);						// �~���̕�������ǂݍ���

						// Z���̕�������ݒ肷��
						divi.z = divi.x;
					}
					else if (strcmp(&aString[0], "HEIGHT") == 0)
					{ // �ǂݍ��񂾕����� HEIGHT �̏ꍇ
						fscanf(pFile, "%s", &aString[0]);					// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%d", &divi.y);						// �����̕�������ǂݍ���
					}
					else if (strcmp(&aString[0], "TEXTURE") == 0)
					{ // �ǂݍ��񂾕����� TEXTURE �̏ꍇ
						fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%s", &aTextureName[0]);			// �p�X��ǂݍ���
					}
					else if (strcmp(&aString[0], "LIGHTING") == 0)
					{ // �ǂݍ��񂾕����� LIGHTING �̏ꍇ
						fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%s", &aString[0]);				// OFF��ǂݍ���

						// ���C�e�B���O�󋵂�ݒ肷��
						bLighting = (strcmp(&aString[0], "TRUE") == 0) ? true : false;
					}

				} while (strcmp(&aString[0], "END_SET_MESHCYLINDER") != 0);	// �ǂݍ��񂾕����� END_SET_MESHCYLINDER �ł͂Ȃ��ꍇ���[�v

				// ���̐�������
				Create(pos, rot, size, divi, TYPE::TYPE_CYLINDER, aTextureName, bLighting);
			}
			else if (strcmp(&aString[0], "SET_MESHDOME") == 0)
			{ // �ǂݍ��񂾕����� SET_MESHDOME �̏ꍇ

				do
				{ // �ǂݍ��񂾕����� END_SET_MESHDOME �ł͂Ȃ��ꍇ���[�v

					// �t�@�C�����當�����ǂݍ���
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "POS") == 0)
					{ // �ǂݍ��񂾕����� POS �̏ꍇ
						fscanf(pFile, "%s", &aString[0]);					// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%f%f%f", &pos.x, &pos.y, &pos.z);	// �ʒu��ǂݍ���
					}
					else if (strcmp(&aString[0], "ROT") == 0)
					{ // �ǂݍ��񂾕����� ROT �̏ꍇ
						fscanf(pFile, "%s", &aString[0]);					// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%f%f%f", &rot.x, &rot.y, &rot.z);	// ������ǂݍ���
					}
					else if (strcmp(&aString[0], "SIZE") == 0)
					{ // �ǂݍ��񂾕����� CIRCUMSIZE �̏ꍇ
						fscanf(pFile, "%s", &aString[0]);					// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%f%f", &size.x, &size.y);			// �~���̃T�C�Y��ǂݍ���

						// Z���̃T�C�Y��ݒ肷��
						size.z = size.x;
					}
					else if (strcmp(&aString[0], "CIRCUM") == 0)
					{ // �ǂݍ��񂾕����� CIRCUM �̏ꍇ
						fscanf(pFile, "%s", &aString[0]);					// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%d", &divi.x);						// �~���̕�������ǂݍ���

						// Z���̕�������ݒ肷��
						divi.z = divi.x;
					}
					else if (strcmp(&aString[0], "HEIGHT") == 0)
					{ // �ǂݍ��񂾕����� HEIGHT �̏ꍇ
						fscanf(pFile, "%s", &aString[0]);					// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%d", &divi.y);						// �����̕�������ǂݍ���
					}
					else if (strcmp(&aString[0], "TEXTURE") == 0)
					{ // �ǂݍ��񂾕����� TEXTURE �̏ꍇ
						fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%s", &aTextureName[0]);			// �p�X��ǂݍ���
					}
					else if (strcmp(&aString[0], "LIGHTING") == 0)
					{ // �ǂݍ��񂾕����� LIGHTING �̏ꍇ
						fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%s", &aString[0]);				// OFF��ǂݍ���

						// ���C�e�B���O�󋵂�ݒ肷��
						bLighting = (strcmp(&aString[0], "TRUE") == 0) ? true : false;
					}

				} while (strcmp(&aString[0], "END_SET_MESHDOME") != 0);	// �ǂݍ��񂾕����� END_SET_MESHDOME �ł͂Ȃ��ꍇ���[�v

				// �h�[���̐�������
				Create(pos, rot, size, divi, TYPE::TYPE_DOME, aTextureName, bLighting);
			}
		} while (nEnd != EOF);														// �ǂݍ��񂾕����� EOF �ł͂Ȃ��ꍇ���[�v

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{ // �t�@�C�����J���Ȃ������ꍇ

		// ��~
		assert(false);
	}
}