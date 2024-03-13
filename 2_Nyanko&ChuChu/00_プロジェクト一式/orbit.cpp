//=================================================================================
//
//	�O�Տ��� [orbit.cpp]
//	Author�F��������
//
//=================================================================================
//*********************************************************************************
//	�C���N���[�h�t�@�C��
//*********************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "orbit.h"
#include "texture.h"

//---------------------------------------------------------------------------------
//	�}�N����`
//---------------------------------------------------------------------------------
#define ORBIT_HEIGHT_VTX		(2)											// �O�Ղ̏c��
#define ORBIT_COL				(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))			// �O�Ղ̐F
#define ORBIT_ALPHA_SUB			(0.02f)										// �����x�̌��Z��

//=================================
// �R���X�g���N�^
//=================================
COrbit::COrbit() : CObject(CObject::TYPE_ORBIT, CObject::PRIORITY_ENTITY)
{
	// �S�Ă̒l���N���A����
	m_pVtxBuff = nullptr;							// ���_�o�b�t�@�ւ̃|�C���^
	m_pTexture = nullptr;							// �e�N�X�`���ւ̃|�C���^
	ZeroMemory(&m_mtxWorld,sizeof(m_mtxWorld));		// ���[���h�}�g���b�N�X
	m_posParent = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �e�̈ʒu
	m_rotParent = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �e�̌���

	for (int nCntVtx = 0; nCntVtx < MAX_ORBIT_VTX; nCntVtx++)
	{
		m_aPosPoint[nCntVtx] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �v�Z��̊e���_���W
		m_aColPoint[nCntVtx] = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		// �v�Z��̊e���_�J���[
	}
}

//=================================
// �f�X�g���N�^
//=================================
COrbit::~COrbit()
{

}

//=================================
//	�O�Ղ̏���������
//=================================
HRESULT COrbit::Init(void)
{
	// �|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();	// �f�o�C�X�ւ̃|�C���^
	VERTEX_3D *pVtx;							// ���_���ւ̃|�C���^

	// �S�Ă̒l���N���A����
	m_pVtxBuff = nullptr;							// ���_�o�b�t�@�ւ̃|�C���^
	m_pTexture = nullptr;						// �e�N�X�`���ւ̃|�C���^
	ZeroMemory(&m_mtxWorld, sizeof(m_mtxWorld));	// ���[���h�}�g���b�N�X
	m_posParent = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �e�̈ʒu
	m_rotParent = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �e�̌���

	for (int nCntVtx = 0; nCntVtx < MAX_ORBIT_VTX; nCntVtx++)
	{
		m_aPosPoint[nCntVtx] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �v�Z��̊e���_���W
		m_aColPoint[nCntVtx] = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		// �v�Z��̊e���_�J���[
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Diabolo.jpg", &m_pTexture);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer
	( // ����
		sizeof(VERTEX_3D) * MAX_ORBIT_VTX,	// �K�v���_��
		D3DUSAGE_WRITEONLY,					// �g�p���@
		FVF_VERTEX_3D,						// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,					// �������̎w��
		&m_pVtxBuff,					// ���_�o�b�t�@�ւ̃|�C���^
		NULL
	);

	//------------------------------------------------------------------------------------------------------------------
	//	���_���̏�����
	//------------------------------------------------------------------------------------------------------------------
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWid = 0; nCntWid < (int)(MAX_ORBIT_VTX * 0.5f); nCntWid++)
	{
		for (int nCntDep = 1; nCntDep >= 0; nCntDep--)
		{
			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// �@���x�N�g���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = ORBIT_COL;

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2
			(
				(float)(nCntWid * 0.05f),
				(float)((nCntDep) % 2)
			);

			pVtx++;				// ���_�f�[�^��i�߂�
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	// ������Ԃ�
	return S_OK;
}

//=================================
//	�O�Ղ̏I������
//=================================
void COrbit::Uninit(void)
{
	if (m_pTexture != nullptr)
	{ // �ϐ� (m_pTexture) ��NULL�ł͂Ȃ��ꍇ

		m_pTexture = nullptr;
	}

	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{ // �ϐ� (g_pVtxBuffOrbit) ��NULL�ł͂Ȃ��ꍇ

		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	// �j������
	Release();
}

//=================================
//	�O�Ղ̍X�V����
//=================================
void COrbit::Update(void)
{
	VERTEX_3D *pVtx;				// ���_���ւ̃|�C���^

	// ���_���W�ƒ��_�J���[�����炷
	for (int nCnt = MAX_ORBIT_VTX - (ORBIT_HEIGHT_VTX + 1); nCnt >= 0; nCnt--)
	{ // ���_�������炷

		// ���_���W�̃f�[�^��2�����炷
		m_aPosPoint[nCnt + ORBIT_HEIGHT_VTX] = m_aPosPoint[nCnt];

		// �����x��������
		m_aColPoint[nCnt].a -= ORBIT_ALPHA_SUB;

		// ���_�J���[�̃f�[�^��2�����炷
		m_aColPoint[nCnt + ORBIT_HEIGHT_VTX] = m_aColPoint[nCnt];
	}

	// �ŏ��̒��_���W�ƒ��_�J���[��������
	for (int nCntNew = 0; nCntNew < MATRIXPLACE_MAX; nCntNew++)
	{ // �}�g���b�N�X�̐��J��Ԃ�

		switch (nCntNew)
		{
		case MATRIXPLACE_BOTTOM:

			// ���_���W��������
			m_aPosPoint[nCntNew].x = m_posParent.x;
			m_aPosPoint[nCntNew].y = m_posParent.y;
			m_aPosPoint[nCntNew].z = m_posParent.z;

			break;

		case MATRIXPLACE_TOP:

			// ���_���W��������
			m_aPosPoint[nCntNew].x = m_posParent.x + sinf(m_rotParent.x) * (100.0f);
			m_aPosPoint[nCntNew].y = m_posParent.y + cosf(m_rotParent.x) * (100.0f);
			m_aPosPoint[nCntNew].z = m_posParent.z;

			break;
		}

		// �F��������
		m_aColPoint[nCntNew] = ORBIT_COL;
	}

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int nNum;

	for (int nCntWid = 0; nCntWid < (int)(MAX_ORBIT_VTX * 0.5f); nCntWid++)
	{
		for (int nCntDep = 1; nCntDep >= 0; nCntDep--)
		{
			nNum = (MATRIXPLACE_MAX * nCntWid) + (1 - nCntDep);

			// ���_���W�̐ݒ�
			pVtx[nNum].pos = m_aPosPoint[nNum];

			// �F�̐ݒ�
			pVtx[nNum].col = m_aColPoint[nNum];
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=================================
//	�O�Ղ̕`�揈��
//=================================
void COrbit::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot;			// �v�Z�p�}�g���b�N�X

	// ���C�e�B���O��OFF�ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// Z�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);					//Z�e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);						//Z�e�X�g�̗L��/�����ݒ�

	// �J�����O��OFF�ɂ���
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0,
		m_pVtxBuff,									//���_�o�b�t�@�ւ̃|�C���^
		0,
		sizeof(VERTEX_3D));							//���_���\���̂̃T�C�Y

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
		0,											//�`�悷��ŏ��̒��_�C���f�b�N�X
		MAX_ORBIT_VTX - 2);							//�`�悷��v���~�e�B�u��

	// �J�����O��ON�ɂ���
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// Z�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);			// Z�e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);				// Z�e�X�g�̗L��/�����ݒ�

	//���C�e�B���O��ON�ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//================================
// �e�N�X�`���̊��蓖�ď���
//================================
void COrbit::BindTexture(int nIdx)
{
	// �e�N�X�`�������蓖�Ă�
	m_pTexture = CManager::Get()->GetTexture()->GetAddress(nIdx);
}

//=================================
// �e�̈ʒu�̐ݒ菈��
//=================================
void COrbit::SetParentData(const D3DXVECTOR3& pos,const D3DXVECTOR3& rot)
{
	// �e�̈ʒu�ƌ�����ݒ肷��
	m_posParent = pos;
	m_rotParent = rot;
}

//=================================
// �S���_�̈ʒu�̐ݒ�
//=================================
void COrbit::PosSet(const D3DXVECTOR3& pos)
{
	// �ʒu��ݒ肷��
	m_posParent = pos;

	for (int nCntVtx = 0; nCntVtx < MAX_ORBIT_VTX; nCntVtx++)
	{
		// �v�Z��̊e���_���W��ݒ肷��
		m_aPosPoint[nCntVtx] = pos;
	}
}

//=================================
// �O�Ղ̐ݒ菈��
//=================================
COrbit* COrbit::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3& rot,const int nTexIdx)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	COrbit* pOrbit = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pOrbit == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pOrbit = new COrbit;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pOrbit != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pOrbit->Init()))
		{ // �������Ɏ��s�����ꍇ

			// �x����
			MessageBox(NULL, "�O�Ղ̏������Ɏ��s�I", "�x���I", MB_ICONWARNING);

			// NULL ��Ԃ�
			return nullptr;
		}

		// �S���_�̈ʒu�̐ݒ菈��
		pOrbit->PosSet(pos);

		// ������ݒ肷��
		pOrbit->m_rotParent = rot;

		// �e�N�X�`���̊��蓖�ď���
		pOrbit->BindTexture(nTexIdx);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}

	// �v���C���[�̃|�C���^��Ԃ�
	return pOrbit;
}