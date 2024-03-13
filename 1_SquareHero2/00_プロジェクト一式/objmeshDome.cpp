//============================================
//
//	�I�u�W�F�N�g���b�V���h�[�� [objmeshDome.cpp]
//	Author:sakamoto kai
//
//============================================
#include "objmeshDome.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "texture.h"

#define WAIGHT_SIZE (17)			//���̒��_��(�Xor�P�Vor�R�R)�������ƃo�O��
#define HEIGHT_SIZE (8)				//�c�̒��_��
#define WAIGHT_CENTER (0.5f)		//���̌��_(0.0f�`1.0f)
#define HEIGHT_CENTER (1.0f)		//�c�̌��_(0.0f�`1.0f)
#define CYLINDER_HEIGHT (750.0f)	//�ǈꖇ�̍���
#define CYLINDER_RADIUS (6000.0f)	//�~�̔��a

//====================================================================
//�R���X�g���N�^
//====================================================================
CObjmeshDome::CObjmeshDome(int nPriority) :CObject(nPriority)
{
	m_pVtxBuff = NULL;
	g_pIdxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

//====================================================================
//�f�X�g���N�^
//====================================================================
CObjmeshDome::~CObjmeshDome()
{

}

//====================================================================
//��������
//====================================================================
CObjmeshDome* CObjmeshDome::Create(void)
{
	CObjmeshDome* pObject3D = NULL;

	if (pObject3D == NULL)
	{
		//�I�u�W�F�N�g3D�̐���
		pObject3D = new CObjmeshDome();
	}

	//�I�u�W�F�N�g�̏���������
	if (FAILED(pObject3D->Init()))
	{//���������������s�����ꍇ
		return NULL;
	}

	return pObject3D;
}

//====================================================================
//����������
//====================================================================
HRESULT CObjmeshDome::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	SetTexture("data\\TEXTURE\\Wood002.png");

	SetType(TYPE_NONE);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * HEIGHT_SIZE * WAIGHT_SIZE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL)))
	{
		return E_FAIL;
	}

	VERTEX_3D* pVtx;	//���_�|�C���^������

	//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0, nData = 0, nCenterW = 0, nCenterH = 0, nHeight = 0; nCnt < HEIGHT_SIZE * WAIGHT_SIZE; nCnt++)
	{
		//���ԍ��̑��
		nCenterW = nCnt % WAIGHT_SIZE;

		if (nCnt % WAIGHT_SIZE == 0 && nCnt != 0)
		{
			nHeight++;
		}

		//���_���W�̐ݒ� 
		pVtx[nCnt].pos.x = m_pos.x + sinf(D3DX_PI * (1.0f / ((WAIGHT_SIZE - 1) / 2)) * (nCnt - nHeight)) * cosf(D3DX_PI * (1.0f / ((HEIGHT_SIZE - 1) * 2)) * ((HEIGHT_SIZE - 1) - nHeight)) * CYLINDER_RADIUS;

		pVtx[nCnt].pos.y = sinf(D3DX_PI * (1.0f / ((HEIGHT_SIZE - 1) * 2)) * ((HEIGHT_SIZE - 1) - nHeight)) * CYLINDER_RADIUS;

		pVtx[nCnt].pos.z = m_pos.z + cosf(D3DX_PI * (1.0f / ((WAIGHT_SIZE - 1) / 2)) * (nCnt - nHeight)) * cosf(D3DX_PI * (1.0f / ((HEIGHT_SIZE - 1) * 2)) * ((HEIGHT_SIZE - 1) - nHeight)) * CYLINDER_RADIUS;

		//�@���x�N�g���̐ݒ�
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

		//���_�J���[�̐ݒ�
		pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		if (nCenterW % 2 == 0)
		{
			pVtx[nCnt].tex.x = 0.0f;
		}
		else
		{
			pVtx[nCnt].tex.x = 1.0f;
		}
		if (nCenterH % 2 == 0)
		{
			pVtx[nCnt].tex.y = 0.0f;
		}
		else
		{
			pVtx[nCnt].tex.y = 1.0f;
		}

		////�e�N�X�`�����W�̐ݒ�
		//pVtx[nCnt].tex.x = 1.0f / (WAIGHT_SIZE - 1) * nCenterW;
		//pVtx[nCnt].tex.y = 1.0f / (HEIGHT_SIZE - 1) * nCenterH;


		if ((nCnt - nCenterH) % (WAIGHT_SIZE - 1) == 0 && nCnt != 0 && nCnt != (WAIGHT_SIZE - 1) * nCenterH + nCenterH)
		{//�c�ԍ��̑��
			nCenterH++;
		}
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * (WAIGHT_SIZE * HEIGHT_SIZE + WAIGHT_SIZE * (HEIGHT_SIZE - 2) + 2 * (HEIGHT_SIZE - 2)),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuff,
		NULL);

	WORD* pIdx;	//�C���f�b�N�X���ւ̃|�C���^

	//�C���f�b�N�X�o�b�t�@�����b�N���A���_�ԍ��f�[�^�ւ̃|�C���^������
	g_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCnt = 0, nOri = 0; nCnt < (WAIGHT_SIZE * HEIGHT_SIZE + WAIGHT_SIZE * (HEIGHT_SIZE - 2) + 2 * (HEIGHT_SIZE - 2)) / 2; nCnt++)
	{
		if ((nCnt - nOri) % WAIGHT_SIZE == 0 && nCnt != 0 && nCnt != WAIGHT_SIZE * nOri + nOri)
		{
			pIdx[nCnt * 2] = nCnt - 1 - nOri;			//����
			pIdx[nCnt * 2 + 1] = nCnt + WAIGHT_SIZE - nOri;		//�

			nOri++;
		}
		else
		{
			pIdx[nCnt * 2] = nCnt + WAIGHT_SIZE - nOri;	//����
			pIdx[nCnt * 2 + 1] = nCnt - nOri;		//�
		}
	}

	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pIdxBuff->Unlock();

	return S_OK;
}

//====================================================================
//�I������
//====================================================================
void CObjmeshDome::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̔j��
	if (g_pIdxBuff != NULL)
	{
		g_pIdxBuff->Release();
		g_pIdxBuff = NULL;
	}

	SetDeathFlag(true);
}

//====================================================================
//�X�V����
//====================================================================
void CObjmeshDome::Update(void)
{

}

//====================================================================
//�`�揈��
//====================================================================
void CObjmeshDome::Draw(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

		//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuff);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	assert(GetIdx() != -1);		//�e�N�X�`���̔ԍ������Y�ꂽ�ꍇ�G���[��f��

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetAddress(GetIdx()));

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		0,
		0,//�p�ӂ������_�̐�
		0,
		(WAIGHT_SIZE * HEIGHT_SIZE + WAIGHT_SIZE * (HEIGHT_SIZE - 2) + 2 * (HEIGHT_SIZE - 2)) - 2);//�`�悷��v���~�e�B�u�̐�
}

//====================================================================
//���_���W�̐ݒ�
//====================================================================
void CObjmeshDome::SetVerPos(D3DXVECTOR3 Pos0, D3DXVECTOR3 Pos1, D3DXVECTOR3 Pos2, D3DXVECTOR3 Pos3)
{
	VERTEX_3D* pVtx;	//���_�|�C���^������

	//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ� 
	pVtx[0].pos = Pos0;
	pVtx[1].pos = Pos1;
	pVtx[2].pos = Pos2;
	pVtx[3].pos = Pos3;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//====================================================================
//�e�N�X�`�����W�̐ݒ�
//====================================================================
void CObjmeshDome::SetScroll(D3DXVECTOR2 Scroll)
{
	VERTEX_3D* pVtx;	//���_�|�C���^������

	//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0, nData = 0, nCenterW = 0, nCenterH = 0, nHeight = 0; nCnt < HEIGHT_SIZE * WAIGHT_SIZE; nCnt++)
	{
		//���ԍ��̑��
		nCenterW = nCnt % WAIGHT_SIZE;

		if (nCnt % WAIGHT_SIZE == 0 && nCnt != 0)
		{
			nHeight++;
		}

		//�e�N�X�`�����W�̐ݒ�
		if (nCenterW % 2 == 0)
		{
			pVtx[nCnt].tex.x = 0.0f + Scroll.x;
		}
		else
		{
			pVtx[nCnt].tex.x = 1.0f + Scroll.x;
		}
		if (nCenterH % 2 == 0)
		{
			pVtx[nCnt].tex.y = 0.0f + Scroll.y;
		}
		else
		{
			pVtx[nCnt].tex.y = 1.0f + Scroll.y;
		}

		if ((nCnt - nCenterH) % (WAIGHT_SIZE - 1) == 0 && nCnt != 0 && nCnt != (WAIGHT_SIZE - 1) * nCenterH + nCenterH)
		{//�c�ԍ��̑��
			nCenterH++;
		}
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//====================================================================
//���_�J���[�̐ݒ�
//====================================================================
void CObjmeshDome::SetColor(D3DXCOLOR col)
{
	m_Color = col;

	VERTEX_3D* pVtx;	//���_�|�C���^������

	//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < HEIGHT_SIZE * WAIGHT_SIZE; nCnt++)
	{
		//���_�J���[�̐ݒ�
		pVtx[nCnt].col = col;
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//====================================================================
//���_�J���[�̐ݒ�
//====================================================================
void CObjmeshDome::SetTexture(const char* name)
{
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	m_nIdxTexture = pTexture->Regist(name);
}