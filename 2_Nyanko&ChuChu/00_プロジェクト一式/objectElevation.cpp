//======================================================================================================================
//
//	�N���n�ʏ��� [mesh_elevation.cpp]
//	Author�F��������
//
//======================================================================================================================
//**********************************************************************************************************************
//	�C���N���[�h�t�@�C��
//**********************************************************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "objectElevation.h"
#include "elevation_manager.h"
#include "Effect.h"
#include "input.h"
#include "useful.h"
#include "texture.h"

//----------------------------------------------------------------------------------------------------------------------
// �}�N����`
//----------------------------------------------------------------------------------------------------------------------
#define ELEVATION_TXT			"data/TXT/Elevation.txt"			// �N���n�ʂ̃e�L�X�g
#define TEXTURE_DIVI_X			(0.01f)								// �e�N�X�`���̕�����(X��)
#define TEXTURE_DIVI_Z			(0.01f)								// �e�N�X�`���̕�����(Z��)

//================================
// �R���X�g���N�^
//================================
CElevation::CElevation() : CObject(CObject::TYPE_FIELD, CObject::PRIORITY_BG)
{
	// �S�Ă̒l���N���A����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ����
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �T�C�Y
	m_sizeDivi = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 1������̖ʂ̃T�C�Y
	ZeroMemory(&m_mtxWorld, sizeof(D3DXMATRIX));	// ���[���h�}�g���b�N�X
	m_pVtxBuff = nullptr;							// ���_�o�b�t�@�̃|�C���^
	m_pIdxBuff = nullptr;							// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	m_nVtxX = 0;									// ���̒��_��
	m_nVtxZ = 0;									// ���s�̒��_��
	m_nDiviX = 0;									// ���̕�����
	m_nDiviZ = 0;									// ���s�̕�����
	m_nNumVtx = 0;									// �����_��
	m_nNumIdx = 0;									// ���C���f�b�N�X��
	m_nTexIdx = NONE_TEXIDX;						// �e�N�X�`���̃C���f�b�N�X

	// �S�Ă̒l���N���A����
	m_pPrev = nullptr;		// �O�̃A�E�g�{�[���ւ̃|�C���^
	m_pNext = nullptr;		// ���̃A�E�g�{�[���ւ̃|�C���^

	if (CElevationManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// �}�l�[�W���[�ւ̓o�^����
		CElevationManager::Get()->Regist(this);
	}
}

//================================
// �f�X�g���N�^
//================================
CElevation::~CElevation()
{

}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
void CElevation::SetPrev(CElevation* pPrev)
{
	// �O�̃|�C���^��ݒ肷��
	m_pPrev = pPrev;
}

//============================
// ��̃|�C���^�̐ݒ菈��
//============================
void CElevation::SetNext(CElevation* pNext)
{
	// ���̃|�C���^��ݒ肷��
	m_pNext = pNext;
}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
CElevation* CElevation::GetPrev(void) const
{
	// �O�̃|�C���^��Ԃ�
	return m_pPrev;
}

//============================
// ���̃|�C���^�̐ݒ菈��
//============================
CElevation* CElevation::GetNext(void) const
{
	// ���̃|�C���^��Ԃ�
	return m_pNext;
}

//================================
// ����������
//================================
HRESULT CElevation::Init(void)
{
	// �f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

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

	// ���_���̒��_�ݒ菈��
	SetVertex();

	// �C���f�b�N�X�̐ݒ菈��
	SetIndex();

	// ������Ԃ�
	return S_OK;
}

//================================
// �I������
//================================
void CElevation::Uninit(void)
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

	if (CElevationManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// ���X�g�\���̈�����������
		CElevationManager::Get()->Pull(this);
	}

	// ���X�g�\���֌W�̃|�C���^�� NULL �ɂ���
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//================================
// �X�V����
//================================
void CElevation::Update(void)
{
	// �@���̐ݒ菈��
	SetNormalize();
}

//================================
// �`�揈��
//================================
void CElevation::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;		// �v�Z�p�}�g���b�N�X

	// ���C�e�B���O��OFF�ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

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

	// ���C�e�B���O��ON�ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//================================
// ���̐ݒ菈��
//================================
void CElevation::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const float fSizeX, const float fSizeZ, const int nDiviX, const int nDiviZ)
{
	// �S�Ă̒l������������
	m_pos = pos;						// �ʒu
	m_rot = rot;						// ����
	m_size.x = fSizeX;					// �T�C�Y(X��)
	m_size.z = fSizeZ;					// �T�C�Y(Z��)
	m_nDiviX = nDiviX;					// ���̕�����
	m_nDiviZ = nDiviZ;					// ���s�̕�����
	m_nVtxX = m_nDiviX + 1;				// ���̒��_��
	m_nVtxZ = m_nDiviZ + 1;				// ���s�̒��_��
	m_nNumVtx = m_nVtxX * m_nVtxZ;		// �����_��
	m_nNumIdx = (2 * (m_nVtxX * m_nDiviZ)) + ((m_nVtxZ - 2) * 2);		// ���C���f�b�N�X��
	m_nTexIdx = NONE_TEXIDX;			// �e�N�X�`���̃C���f�b�N�X
	m_sizeDivi = D3DXVECTOR3			// 1������̖ʂ̃T�C�Y
	(
		m_size.x / (float)(m_nDiviX),
		0.0f,
		m_size.z / (float)(m_nDiviZ)
	);
}

//================================
// �e�N�X�`���̊��蓖�ď���
//================================
void CElevation::BindTexture(int nIdx)
{
	// �e�N�X�`�������蓖�Ă�
	m_nTexIdx = nIdx;
}

//================================
// �ʒu�̎擾����
//================================
D3DXVECTOR3 CElevation::GetPos(void) const
{
	// �ʒu��Ԃ�
	return m_pos;
}

//================================
// �T�C�Y�̎擾����
//================================
D3DXVECTOR3 CElevation::GetSize(void) const
{
	// �T�C�Y��Ԃ�
	return m_size;
}

//================================
// X���̒��_���̎擾����
//================================
int CElevation::GetVtxX(void) const
{
	// X���̒��_����Ԃ�
	return m_nVtxX;
}

//================================
// Z���̒��_���̎擾����
//================================
int CElevation::GetVtxZ(void) const
{
	// Z���̒��_����Ԃ�
	return m_nVtxZ;
}

//================================
// �S���_���̎擾����
//================================
int CElevation::GetVtxNum(void) const
{
	// �S���_����Ԃ�
	return m_nNumVtx;
}

//================================
// ���_�̐ݒ菈��
//================================
void CElevation::SetVtxHeight(const int nNum, const float fHeight)
{
	// ���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�̍��������Z����
	pVtx[nNum].pos.y = fHeight;

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================
// ���_�̉��Z����
//================================
void CElevation::AddVertex(const int nNum, const float fAdd)
{
	// ���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�̍��������Z����
	pVtx[nNum].pos.y += fAdd;

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================
// ���_�̐ݒ菈��
//================================
void CElevation::SetVertex(void)
{
	// ���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntDep = 0; nCntDep < m_nVtxZ; nCntDep++)
	{
		for (int nCntWid = 0; nCntWid < m_nVtxX; nCntWid++)
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
			pVtx[0].tex = D3DXVECTOR2(nCntWid * TEXTURE_DIVI_X, nCntDep * TEXTURE_DIVI_Z);

			pVtx++;				// ���_�f�[�^��i�߂�
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================
// �@���̐ݒ菈��
//================================
void CElevation::SetNormalize(void)
{
	// ���[�J���ϐ��錾
	VERTEX_3D *pVtx;							// ���_���ւ̃|�C���^
	D3DXVECTOR3 nor[6] = {};					// �ۑ��p�@��
	D3DXVECTOR3 vec[2] = {};					// �ۑ��p�x�N�g��
	D3DXVECTOR3 SumNor = {};					// ���v�@��
	int nNum = 0;								// ���݂̔ԍ�

	//------------------------------------------------------------------------------------------------------------------
	//	���_���̏�����
	//------------------------------------------------------------------------------------------------------------------
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntDep = 0; nCntDep < m_nVtxZ; nCntDep++)
	{
		for (int nCntWid = 0; nCntWid < m_nVtxX; nCntWid++)
		{
			// ���݂̒��_�̔ԍ���ݒ肷��
			nNum = (m_nVtxX * nCntDep) + nCntWid;

			if (nNum == 0)
			{ // �ŏ�(�����p)�̏ꍇ

				vec[0] = pVtx[nNum].pos - pVtx[nNum + m_nVtxX].pos;
				vec[1] = pVtx[nNum + m_nVtxX + 1].pos - pVtx[nNum + m_nVtxX].pos;

				D3DXVec3Cross(&nor[0], &vec[0], &vec[1]);

				D3DXVec3Normalize(&nor[0], &nor[0]);

				vec[0] = pVtx[nNum + m_nVtxX + 1].pos - pVtx[nNum + 1].pos;
				vec[1] = pVtx[nNum].pos - pVtx[nNum + 1].pos;

				D3DXVec3Cross(&nor[1], &vec[0], &vec[1]);

				D3DXVec3Normalize(&nor[1], &nor[1]);

				SumNor = (nor[0] + nor[1]) / 2;

				D3DXVec3Normalize(&SumNor, &SumNor);

				// �@�����W�̐ݒ�
				pVtx[nNum].nor = SumNor;
			}
			else if (nCntDep == 0 && nCntWid != m_nDiviX)
			{ // ����(�p�ȊO)�̏ꍇ

				vec[0] = pVtx[nNum + m_nVtxX].pos - pVtx[nNum].pos;
				vec[1] = pVtx[nNum - 1].pos - pVtx[nNum].pos;

				D3DXVec3Cross(&nor[0], &vec[0], &vec[1]);

				D3DXVec3Normalize(&nor[0], &nor[0]);

				vec[0] = pVtx[nNum].pos - pVtx[nNum + m_nVtxX].pos;
				vec[1] = pVtx[nNum + m_nVtxX + 1].pos - pVtx[nNum + m_nVtxX].pos;

				D3DXVec3Cross(&nor[1], &vec[0], &vec[1]);

				D3DXVec3Normalize(&nor[1], &nor[1]);

				vec[0] = pVtx[nNum + m_nVtxX + 1].pos - pVtx[nNum + 1].pos;
				vec[1] = pVtx[nNum].pos - pVtx[nNum + 1].pos;

				D3DXVec3Cross(&nor[2], &vec[0], &vec[1]);

				D3DXVec3Normalize(&nor[2], &nor[2]);

				SumNor = (nor[0] + nor[1] + nor[2]) / 3;

				D3DXVec3Normalize(&SumNor, &SumNor);

				// �@�����W�̐ݒ�
				pVtx[nNum].nor = SumNor;
			}
			else if (nCntDep == 0 && nCntWid == m_nDiviX)
			{ // �E���p�̏ꍇ

				vec[0] = pVtx[nNum + m_nVtxX].pos - pVtx[nNum].pos;
				vec[1] = pVtx[nNum - 1].pos - pVtx[nNum].pos;

				D3DXVec3Cross(&nor[0], &vec[0], &vec[1]);

				D3DXVec3Normalize(&nor[0], &nor[0]);

				// �@�����W�̐ݒ�
				pVtx[nNum].nor = nor[0];
			}
			else if (nCntWid == 0 && nCntDep != m_nDiviZ)
			{ // ����(�p�ȊO)�̏ꍇ

				vec[0] = pVtx[nNum].pos - pVtx[nNum + m_nVtxX].pos;
				vec[1] = pVtx[nNum + m_nVtxX + 1].pos - pVtx[nNum + m_nVtxX].pos;

				D3DXVec3Cross(&nor[0], &vec[0], &vec[1]);

				D3DXVec3Normalize(&nor[0], &nor[0]);

				vec[0] = pVtx[nNum - m_nVtxX].pos - pVtx[nNum].pos;
				vec[1] = pVtx[nNum + 1].pos - pVtx[nNum].pos;

				D3DXVec3Cross(&nor[1], &vec[0], &vec[1]);

				D3DXVec3Normalize(&nor[1], &nor[1]);

				vec[0] = pVtx[nNum + m_nVtxX + 1].pos - pVtx[nNum + 1].pos;
				vec[1] = pVtx[nNum].pos - pVtx[nNum + 1].pos;

				D3DXVec3Cross(&nor[2], &vec[0], &vec[1]);

				D3DXVec3Normalize(&nor[2], &nor[2]);

				SumNor = (nor[0] + nor[1] + nor[2]) / 3;

				D3DXVec3Normalize(&SumNor, &SumNor);

				// �@�����W�̐ݒ�
				pVtx[nNum].nor = SumNor;
			}
			else if (nCntWid == m_nDiviX && nCntDep != m_nDiviZ)
			{ // �E��(�p�ȊO)�̏ꍇ

				vec[0] = pVtx[nNum + m_nVtxX].pos - pVtx[nNum].pos;
				vec[1] = pVtx[nNum - 1].pos - pVtx[nNum].pos;

				D3DXVec3Cross(&nor[0], &vec[0], &vec[1]);

				D3DXVec3Normalize(&nor[0], &nor[0]);

				vec[0] = pVtx[nNum - m_nVtxX - 1].pos - pVtx[nNum - 1].pos;
				vec[1] = pVtx[nNum].pos - pVtx[nNum - 1].pos;

				D3DXVec3Cross(&nor[1], &vec[0], &vec[1]);

				D3DXVec3Normalize(&nor[1], &nor[1]);

				vec[0] = pVtx[nNum].pos - pVtx[nNum - m_nVtxX].pos;
				vec[1] = pVtx[nNum - m_nVtxX - 1].pos - pVtx[nNum - m_nVtxX].pos;

				D3DXVec3Cross(&nor[2], &vec[0], &vec[1]);

				D3DXVec3Normalize(&nor[2], &nor[2]);

				SumNor = (nor[0] + nor[1] + nor[2]) / 3;

				D3DXVec3Normalize(&SumNor, &SumNor);

				// �@�����W�̐ݒ�
				pVtx[nNum].nor = SumNor;
			}
			else if (nCntDep == m_nDiviZ && nCntWid == 0)
			{ // ����O���̏ꍇ

				vec[0] = pVtx[nNum - m_nVtxX].pos - pVtx[nNum].pos;
				vec[1] = pVtx[nNum + 1].pos - pVtx[nNum].pos;

				D3DXVec3Cross(&nor[0], &vec[0], &vec[1]);

				D3DXVec3Normalize(&nor[0], &nor[0]);

				// �@�����W�̐ݒ�
				pVtx[nNum].nor = nor[0];
			}
			else if (nCntDep == m_nDiviZ && nCntWid != m_nDiviX)
			{ // ��O��(�p�ȊO)�̏ꍇ

				vec[0] = pVtx[nNum - m_nVtxX - 1].pos - pVtx[nNum - 1].pos;
				vec[1] = pVtx[nNum].pos - pVtx[nNum - 1].pos;

				D3DXVec3Cross(&nor[0], &vec[0], &vec[1]);

				D3DXVec3Normalize(&nor[0], &nor[0]);

				vec[0] = pVtx[nNum].pos - pVtx[nNum - m_nVtxX].pos;
				vec[1] = pVtx[nNum - m_nVtxX - 1].pos - pVtx[nNum - m_nVtxX].pos;

				D3DXVec3Cross(&nor[1], &vec[0], &vec[1]);

				D3DXVec3Normalize(&nor[1], &nor[1]);

				vec[0] = pVtx[nNum - m_nVtxX].pos - pVtx[nNum].pos;
				vec[1] = pVtx[nNum + 1].pos - pVtx[nNum].pos;

				D3DXVec3Cross(&nor[2], &vec[0], &vec[1]);

				D3DXVec3Normalize(&nor[2], &nor[2]);

				SumNor = (nor[0] + nor[1] + nor[2]) / 3;

				D3DXVec3Normalize(&SumNor, &SumNor);

				// �@�����W�̐ݒ�
				pVtx[nNum].nor = SumNor;
			}
			else if (nNum == (m_nNumVtx - 1))
			{ // �Ō�̏ꍇ

				vec[0] = pVtx[nNum - m_nVtxX - 1].pos - pVtx[nNum - 1].pos;
				vec[1] = pVtx[nNum].pos - pVtx[nNum - 1].pos;

				D3DXVec3Cross(&nor[0], &vec[0], &vec[1]);

				D3DXVec3Normalize(&nor[0], &nor[0]);

				vec[0] = pVtx[nNum].pos - pVtx[nNum - m_nVtxX].pos;
				vec[1] = pVtx[nNum - m_nVtxX - 1].pos - pVtx[nNum - m_nVtxX].pos;

				D3DXVec3Cross(&nor[1], &vec[0], &vec[1]);

				D3DXVec3Normalize(&nor[1], &nor[1]);

				SumNor = (nor[0] + nor[1]) / 2;

				D3DXVec3Normalize(&SumNor, &SumNor);

				// �@�����W�̐ݒ�
				pVtx[nNum].nor = SumNor;
			}
			else
			{ // ��L�ȊO(�^��)�̏ꍇ

				vec[0] = pVtx[nNum + m_nVtxX].pos - pVtx[nNum].pos;
				vec[1] = pVtx[nNum - 1].pos - pVtx[nNum].pos;

				D3DXVec3Cross(&nor[0], &vec[0], &vec[1]);

				D3DXVec3Normalize(&nor[0], &nor[0]);

				vec[0] = pVtx[nNum - m_nVtxX - 1].pos - pVtx[nNum - 1].pos;
				vec[1] = pVtx[nNum].pos - pVtx[nNum - 1].pos;

				D3DXVec3Cross(&nor[1], &vec[0], &vec[1]);

				D3DXVec3Normalize(&nor[1], &nor[1]);

				vec[0] = pVtx[nNum].pos - pVtx[nNum - m_nVtxX].pos;
				vec[1] = pVtx[nNum - m_nVtxX - 1].pos - pVtx[nNum - m_nVtxX].pos;

				D3DXVec3Cross(&nor[2], &vec[0], &vec[1]);

				D3DXVec3Normalize(&nor[2], &nor[2]);

				vec[0] = pVtx[nNum - m_nVtxX].pos - pVtx[nNum].pos;
				vec[1] = pVtx[nNum + 1].pos - pVtx[nNum].pos;

				D3DXVec3Cross(&nor[3], &vec[0], &vec[1]);

				D3DXVec3Normalize(&nor[3], &nor[3]);

				vec[0] = pVtx[nNum + m_nVtxX + 1].pos - pVtx[nNum + 1].pos;
				vec[1] = pVtx[nNum].pos - pVtx[nNum + 1].pos;

				D3DXVec3Cross(&nor[4], &vec[0], &vec[1]);

				D3DXVec3Normalize(&nor[4], &nor[4]);

				vec[0] = pVtx[nNum].pos - pVtx[nNum + m_nVtxX].pos;
				vec[1] = pVtx[nNum + m_nVtxX + 1].pos - pVtx[nNum + m_nVtxX].pos;

				D3DXVec3Cross(&nor[5], &vec[0], &vec[1]);

				D3DXVec3Normalize(&nor[5], &nor[5]);

				SumNor = (nor[0] + nor[1] + nor[2] + nor[3] + nor[4] + nor[5]) / 6;

				D3DXVec3Normalize(&SumNor, &SumNor);

				// �@�����W�̐ݒ�
				pVtx[nNum].nor = SumNor;
			}
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================
// �C���f�b�N�X�̐ݒ菈��
//================================
void CElevation::SetIndex(void)
{
	// ���[�J���ϐ��錾
	WORD      *pIdx;							// �C���f�b�N�X���ւ̃|�C���^
	int nIdx = 0;								// �C���f�b�N�X��

	//------------------------------------------------------------------------------------------------------------------
	//	�C���f�b�N�X���̏�����
	//------------------------------------------------------------------------------------------------------------------
	// �C���f�b�N�X�o�b�t�@�����b�N���A���_�ԍ��f�[�^�ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntDep = 1; nCntDep < m_nVtxZ; nCntDep++)
	{
		if (nCntDep != 1)
		{ // �ŏ��ȊO

			// �C���f�b�N�X����ݒ肷��
			pIdx[0] = (WORD)(m_nVtxX * nCntDep);

			// �C���f�b�N�X�f�[�^�����Z����
			pIdx++;
			nIdx++;
		}

		for (int nCntWid = 0; nCntWid < m_nVtxX; nCntWid++)
		{ // 1�w���Ƃɐݒ肷��

			// �C���f�b�N�X����ݒ肷��
			pIdx[0] = (WORD)((m_nVtxX * nCntDep) + nCntWid);
			pIdx[1] = (WORD)((m_nVtxX * nCntDep) - (m_nVtxX - nCntWid));

			// �C���f�b�N�X�f�[�^��2�i�߂�
			pIdx += 2;
			nIdx += 2;

			if (nCntWid == (m_nVtxX - 1) && nCntDep != (m_nVtxZ - 1))
			{ // �܂�Ԃ��ɓ������ꍇ

				// �C���f�b�N�X����ݒ肷��
				pIdx[0] = (WORD)((m_nVtxX * nCntDep) - (m_nVtxX - nCntWid));

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
// �N���̓����蔻��
//================================
float CElevation::ElevationCollision(const D3DXVECTOR3& pos)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 nor, vec1, vec2;	// �ʒu
	float fHeight = pos.y;			// �Ώۂ̍���
	int nNum = 0;					// ���݂̔ԍ�

	// ���_�̔ԍ�
	int nVtxLeftUp;		// ����
	int nVtxLeftDown;	// ����
	int nVtxRightUp;	// �E��
	int nVtxRightDown;	// �E��
	D3DXVECTOR3 vtxLeftUp;		// ����̈ʒu
	D3DXVECTOR3 vtxLeftDown;	// �����̈ʒu
	D3DXVECTOR3 vtxRightUp;		// �E��̈ʒu
	D3DXVECTOR3 vtxRightDown;	// �E���̈ʒu

	if (pos.x <= m_pos.x + m_size.x &&
		pos.x >= m_pos.x - m_size.x &&
		pos.z <= m_pos.z + m_size.z &&
		pos.z >= m_pos.z - m_size.z)
	{ // �n�ʂ͈̔͂ɂ���ꍇ

		VERTEX_3D * pVtx;				//���_���ւ̃|�C���^

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntDep = 0; nCntDep < m_nVtxZ - 1; nCntDep++)
		{
			for (int nCntWid = 0; nCntWid < m_nVtxX - 1; nCntWid++)
			{
				// ���݂̒��_�̔ԍ���ݒ肷��
				nNum = (m_nVtxX * nCntDep) + nCntWid;

				// ���_�̔ԍ���ݒ肷��
				nVtxLeftUp = nNum;					// ����
				nVtxLeftDown = nNum + m_nVtxX;		// ����
				nVtxRightUp = nNum + 1;				// �E��
				nVtxRightDown = nNum + m_nVtxX + 1;	// �E��

				// ���_�̈ʒu��ݒ肷��
				vtxLeftUp = m_pos + pVtx[nVtxLeftUp].pos;
				vtxLeftDown = m_pos + pVtx[nVtxLeftDown].pos;
				vtxRightUp = m_pos + pVtx[nVtxRightUp].pos;
				vtxRightDown = m_pos + pVtx[nVtxRightDown].pos;

				if (vtxLeftUp.z >= pos.z &&
					vtxLeftUp.x <= pos.x &&
					vtxRightDown.z <= pos.z &&
					vtxRightDown.x >= pos.x)
				{ // �l�p�`�̒��ɂ����ꍇ

					if (useful::LineOuterProductXZ(vtxLeftDown, vtxLeftUp, pos) >= 0 &&
						useful::LineOuterProductXZ(vtxLeftUp, vtxRightDown, pos) >= 0 &&
						useful::LineOuterProductXZ(vtxRightDown, vtxLeftDown, pos) >= 0)
					{ // �^�񒆂̋��E����荶���ɋ����ꍇ

						// �@���̌v�Z(���K��)
						//NormalizeVector(nor, pVtx[nVtxRightDown].pos, pVtx[nVtxLeftUp].pos, pVtx[nVtxLeftDown].pos);

						vec1 = vtxLeftUp - vtxLeftDown;
						vec2 = vtxRightDown - vtxLeftDown;

						D3DXVec3Cross(&nor, &vec1, &vec2);

						D3DXVec3Normalize(&nor, &nor);

						if (nor.y != 0.0f)
						{ // �@����Y��0.0f�ȊO�̏ꍇ

							// ������ݒ肷��
							fHeight = (((pos.x - vtxLeftDown.x) * nor.x + (-vtxLeftDown.y) * nor.y + (pos.z - vtxLeftDown.z) * nor.z) * -1.0f) / nor.y;

							// ������Ԃ�
							return fHeight;
						}
					}
					else if (useful::LineOuterProductXZ(vtxLeftUp, vtxRightUp, pos) >= 0 &&
						useful::LineOuterProductXZ(vtxRightDown, vtxLeftUp, pos) >= 0 &&
						useful::LineOuterProductXZ(vtxRightUp, vtxRightDown, pos) >= 0)
					{ // �^�񒆂̋��E�����E���ɋ����ꍇ

						// �@���̌v�Z(���K��)
						//NormalizeVector(nor, pVtx[nVtxLeftUp].pos, pVtx[nVtxRightDown].pos, pVtx[nVtxRightUp].pos);

						vec1 = vtxRightDown - vtxRightUp;
						vec2 = vtxLeftUp - vtxRightUp;

						D3DXVec3Cross(&nor, &vec1, &vec2);

						D3DXVec3Normalize(&nor, &nor);

						if (nor.y != 0.0f)
						{ // �@����Y��0.0f�ȊO�̏ꍇ

							// ������ݒ肷��
							fHeight = (((pos.x - vtxRightUp.x) * nor.x + (-vtxRightUp.y) * nor.y + (pos.z - vtxRightUp.z) * nor.z) * -1.0f) / nor.y;

							// ������Ԃ�
							return fHeight;
						}
					}
				}
			}
		}

		//���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();

		// ������Ԃ�
		return fHeight;
	}
	else
	{ // �n�ʂ͈͓̔��ɂ��Ȃ��ꍇ

		// ������Ԃ�
		return pos.y;
	}
}

//================================
// �N���̓����蔻��(�͈͔���t��)
//================================
float CElevation::ElevationCollision(const D3DXVECTOR3& pos, bool& bRange)
{
		// ���[�J���ϐ��錾
	D3DXVECTOR3 nor, vec1, vec2;	// �ʒu
	float fHeight = pos.y;			// �Ώۂ̍���
	int nNum = 0;					// ���݂̔ԍ�

	// ���_�̔ԍ�
	int nVtxLeftUp;		// ����
	int nVtxLeftDown;	// ����
	int nVtxRightUp;	// �E��
	int nVtxRightDown;	// �E��
	D3DXVECTOR3 vtxLeftUp;		// ����̈ʒu
	D3DXVECTOR3 vtxLeftDown;	// �����̈ʒu
	D3DXVECTOR3 vtxRightUp;		// �E��̈ʒu
	D3DXVECTOR3 vtxRightDown;	// �E���̈ʒu

	if (pos.x <= m_pos.x + (m_size.x * 0.5f) &&
		pos.x >= m_pos.x - (m_size.x * 0.5f) &&
		pos.z <= m_pos.z + (m_size.z * 0.5f) &&
		pos.z >= m_pos.z - (m_size.z * 0.5f))
	{ // �n�ʂ͈̔͂ɂ���ꍇ

		VERTEX_3D * pVtx;				//���_���ւ̃|�C���^

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntDep = 0; nCntDep < m_nVtxZ - 1; nCntDep++)
		{
			for (int nCntWid = 0; nCntWid < m_nVtxX - 1; nCntWid++)
			{
				// ���݂̒��_�̔ԍ���ݒ肷��
				nNum = (m_nVtxX * nCntDep) + nCntWid;

				// ���_�̔ԍ���ݒ肷��
				nVtxLeftUp = nNum;					// ����
				nVtxLeftDown = nNum + m_nVtxX;		// ����
				nVtxRightUp = nNum + 1;				// �E��
				nVtxRightDown = nNum + m_nVtxX + 1;	// �E��

				// ���_�̈ʒu��ݒ肷��
				vtxLeftUp = m_pos + pVtx[nVtxLeftUp].pos;
				vtxLeftDown = m_pos + pVtx[nVtxLeftDown].pos;
				vtxRightUp = m_pos + pVtx[nVtxRightUp].pos;
				vtxRightDown = m_pos + pVtx[nVtxRightDown].pos;

				if (vtxLeftUp.z >= pos.z &&
					vtxLeftUp.x <= pos.x &&
					vtxRightDown.z <= pos.z &&
					vtxRightDown.x >= pos.x)
				{ // �l�p�`�̒��ɂ����ꍇ

					if (useful::LineOuterProductXZ(vtxLeftDown, vtxLeftUp, pos) >= 0 &&
						useful::LineOuterProductXZ(vtxLeftUp, vtxRightDown, pos) >= 0 &&
						useful::LineOuterProductXZ(vtxRightDown, vtxLeftDown, pos) >= 0)
					{ // �^�񒆂̋��E����荶���ɋ����ꍇ

						// �@���̌v�Z(���K��)
						//NormalizeVector(nor, pVtx[nVtxRightDown].pos, pVtx[nVtxLeftUp].pos, pVtx[nVtxLeftDown].pos);

						vec1 = vtxLeftUp - vtxLeftDown;
						vec2 = vtxRightDown - vtxLeftDown;

						D3DXVec3Cross(&nor, &vec1, &vec2);

						D3DXVec3Normalize(&nor, &nor);

						if (nor.y != 0.0f)
						{ // �@����Y��0.0f�ȊO�̏ꍇ

							// ������ݒ肷��
							fHeight = (((pos.x - vtxLeftDown.x) * nor.x + (-vtxLeftDown.y) * nor.y + (pos.z - vtxLeftDown.z) * nor.z) * -1.0f) / nor.y;

							// �͈͓��ɂ���
							bRange = true;

							// ������Ԃ�
							return fHeight;
						}
					}
					else if (useful::LineOuterProductXZ(vtxLeftUp, vtxRightUp, pos) >= 0 &&
						useful::LineOuterProductXZ(vtxRightDown, vtxLeftUp, pos) >= 0 &&
						useful::LineOuterProductXZ(vtxRightUp, vtxRightDown, pos) >= 0)
					{ // �^�񒆂̋��E�����E���ɋ����ꍇ

						// �@���̌v�Z(���K��)
						//NormalizeVector(nor, pVtx[nVtxLeftUp].pos, pVtx[nVtxRightDown].pos, pVtx[nVtxRightUp].pos);

						vec1 = vtxRightDown - vtxRightUp;
						vec2 = vtxLeftUp - vtxRightUp;

						D3DXVec3Cross(&nor, &vec1, &vec2);

						D3DXVec3Normalize(&nor, &nor);

						if (nor.y != 0.0f)
						{ // �@����Y��0.0f�ȊO�̏ꍇ

							// ������ݒ肷��
							fHeight = (((pos.x - vtxRightUp.x) * nor.x + (-vtxRightUp.y) * nor.y + (pos.z - vtxRightUp.z) * nor.z) * -1.0f) / nor.y;

							// �͈͓��ɂ���
							bRange = true;

							// ������Ԃ�
							return fHeight;
						}
					}
				}
			}
		}

		//���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();

		// �͈͓��ɂ���
		bRange = true;

		// ������Ԃ�
		return fHeight;
	}
	else
	{ // �n�ʂ͈͓̔��ɂ��Ȃ��ꍇ

		// ������Ԃ�
		return pos.y;
	}
}

//================================
// �߂��̒��_��T������
//================================
int CElevation::NearVertexSearch(const D3DXVECTOR3& pos)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 distance;		// ����
	int nNum = 0;				// ���_�̔ԍ�
	int nNearNum = 0;			// ��ԋ߂��ԍ�
	float fSum = 0.0f;			// ���v�l
	float fNearSum = 0.0f;		// ��ԋ߂����_�̍��v�l

	VERTEX_3D * pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntDep = 0; nCntDep < m_nVtxZ; nCntDep++)
	{
		for (int nCntWid = 0; nCntWid < m_nVtxX; nCntWid++)
		{
			// ���݂̒��_�̔ԍ���ݒ肷��
			nNum = (m_nVtxX * nCntDep) + nCntWid;

			// �����𑪂�
			distance.x = fabsf(pos.x - (m_pos.x + pVtx[nNum].pos.x));
			distance.z = fabsf(pos.z - (m_pos.z + pVtx[nNum].pos.z));

			// ���v�l�����
			fSum = distance.x + distance.z;

			if (nNum == 0)
			{ // ��ԋ߂��ԍ��������ꍇ

				// ���̋�����ݒ肷��
				fNearSum = fSum;

				// ���̔ԍ���ݒ肷��
				nNearNum = nNum;
			}
			else if(fNearSum >= fSum)
			{ // ���݂̋����̕����Z���ꍇ

				// ���̋�����ݒ肷��
				fNearSum = fSum;

				// ���̔ԍ���ݒ肷��
				nNearNum = nNum;
			}
		}
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	// �ԍ���Ԃ�
	return nNearNum;
}

//================================
// ��������
//================================
CElevation* CElevation::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const float fSizeX, const float fSizeZ, const int nDiviX, const int nDiviZ, char* texturename)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CElevation* pMesh = nullptr;	// �I�u�W�F�N�g3D�̃C���X�^���X�𐶐�

	if (pMesh == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pMesh = new CElevation;
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
		pMesh->SetData(pos, rot, fSizeX, fSizeZ, nDiviX, nDiviZ);

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
void CElevation::TxtSet(void)
{
	// �ϐ���錾
	CElevation* pElevation = nullptr;	// �N���̃|�C���^
	int nEnd;			// �e�L�X�g�ǂݍ��ݏI���̊m�F�p
	D3DXVECTOR3 pos = NONE_D3DXVECTOR3;		// �ʒu
	D3DXVECTOR3 rot = NONE_D3DXVECTOR3;		// ����
	float fSizeX = 0.0f;					// ���̃T�C�Y
	float fSizeZ = 0.0f;					// ���s�̃T�C�Y
	int nDiviX = 0;							// ���̕�����
	int nDiviZ = 0;							// ���s�̕�����
	int nVtxX = 0;							// ���_��(X��)
	int nVtxZ = 0;							// ���_��(Z��)

	// �ϐ��z���錾
	char aString[MAX_STRING];		// �e�L�X�g�̕�����̑���p
	char aTextureName[MAX_STRING];	// �e�N�X�`���̃p�X��

	// �|�C���^��錾
	FILE  *pFile;					// �t�@�C���|�C���^
	VERTEX_3D * pVtx;				// ���_���ւ̃|�C���^

	// �t�@�C����ǂݍ��݌`���ŊJ��
	pFile = fopen(ELEVATION_TXT, "r");

	if (pFile != nullptr)
	{ // �t�@�C�����J�����ꍇ

		do
		{ // �ǂݍ��񂾕����� EOF �ł͂Ȃ��ꍇ���[�v

			// �t�@�C�����當�����ǂݍ���
			nEnd = fscanf(pFile, "%s", &aString[0]);	// �e�L�X�g��ǂݍ��݂������� EOF ��Ԃ�

			if (strcmp(&aString[0], "SET_ELEVATION") == 0)
			{ // �ǂݍ��񂾕����� SET_ELEVATION �̏ꍇ

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
						fscanf(pFile, "%f%f", &fSizeX, &fSizeZ);				// �傫����ǂݍ���
					}
					else if (strcmp(&aString[0], "WIDTH") == 0)
					{ // �ǂݍ��񂾕����� WIDTH �̏ꍇ
						fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%d", &nDiviX);					// �����̕�������ǂݍ���
					}
					else if (strcmp(&aString[0], "DEPTH") == 0)
					{ // �ǂݍ��񂾕����� DEPTH �̏ꍇ
						fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%d", &nDiviZ);					// �����̕�������ǂݍ���
					}
					else if (strcmp(&aString[0], "TEXTURE") == 0)
					{ // �ǂݍ��񂾕����� TEXTURE �̏ꍇ
						fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%s", &aTextureName[0]);			// �p�X��ǂݍ���

						// ��������
						pElevation = Create(pos, rot, fSizeX, fSizeZ, nDiviX, nDiviZ, aTextureName);

						// ���_��(X��)��ݒ肷��
						nVtxX = pElevation->m_nVtxX;

						// ���_��(Z��)��ݒ肷��
						nVtxZ = pElevation->m_nVtxZ;
					}
					else if (strcmp(&aString[0], "ELEV") == 0)
					{ // �ǂݍ��񂾕����� ELEV �̏ꍇ

						fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)

						//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
						pElevation->m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

						for (int nCnt = 0; nCnt < nVtxX * nVtxZ; nCnt++)
						{
							// ���W��ǂݍ���
							fscanf(pFile, "%f %f %f", &pVtx[nCnt].pos.x, &pVtx[nCnt].pos.y, &pVtx[nCnt].pos.z);
						}

						//���_�o�b�t�@���A�����b�N����
						pElevation->m_pVtxBuff->Unlock();
					}
				} while (strcmp(&aString[0], "END_SET_ELEVATION") != 0);	// �ǂݍ��񂾕����� END_SET_ELEVATION �ł͂Ȃ��ꍇ���[�v
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