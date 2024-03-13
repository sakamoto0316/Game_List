//============================================
//
//	�I�u�W�F�N�g���b�V���L���[�u [objmeshCube.cpp]
//	Author:sakamoto kai
//
//============================================
#include "objmeshCube.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "texture.h"

#define WAIGHT_SIZE (11)		//���̒��_��
#define HEIGHT_SIZE (11)		//�c�̒��_��
#define WAIGHT_CENTER (0.5f)	//���̌��_(0.0f�`1.0f)
#define HEIGHT_CENTER (0.5f)	//�c�̌��_(0.0f�`1.0f)
#define FIELD_SIZE (200.0f)		//���ꖇ�̑傫��

//====================================================================
//�R���X�g���N�^
//====================================================================
CObjmeshCube::CObjmeshCube(int nPriority) :CObject(nPriority)
{
	m_pVtxBuff = NULL;
	g_pIdxBuff = NULL;
	m_pos = INITVECTOR3;
	m_rot = INITVECTOR3;
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_Size = D3DXVECTOR3(25.0f, 25.0f, 25.0f);
	m_move = INITVECTOR3;
	m_PlusMove = false;
	m_bLife = false;
	UninitPos = INITVECTOR3;
	m_nLife = -1;
	m_fDel = 0.00000000000f;
}

//====================================================================
//�f�X�g���N�^
//====================================================================
CObjmeshCube::~CObjmeshCube()
{

}

//====================================================================
//��������
//====================================================================
CObjmeshCube* CObjmeshCube::Create(void)
{
	CObjmeshCube* pObject3D = NULL;

	if (pObject3D == NULL)
	{
		//�I�u�W�F�N�g3D�̐���
		pObject3D = new CObjmeshCube();
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
HRESULT CObjmeshCube::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	SetTexture("data\\TEXTURE\\Wood002.png");

	SetType(TYPE_BLOCK);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 24,
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

		//���_���W�̐ݒ� 
	pVtx[0].pos.x	= -m_Size.x;
	pVtx[1].pos.x	= m_Size.x;
	pVtx[2].pos.x	= -m_Size.x;
	pVtx[3].pos.x	= m_Size.x;
	pVtx[4].pos.x	= m_Size.x;
	pVtx[5].pos.x	= m_Size.x;
	pVtx[6].pos.x	= m_Size.x;
	pVtx[7].pos.x	= -m_Size.x;
	pVtx[8].pos.x	= -m_Size.x;
	pVtx[9].pos.x	= -m_Size.x;
	pVtx[10].pos.x	= -m_Size.x;
	pVtx[11].pos.x	= m_Size.x;
	pVtx[12].pos.x	= m_Size.x;
	pVtx[13].pos.x	= m_Size.x;
	pVtx[14].pos.x	= m_Size.x;
	pVtx[15].pos.x	= -m_Size.x;
	pVtx[16].pos.x	= -m_Size.x;
	pVtx[17].pos.x	= -m_Size.x;
	pVtx[18].pos.x	= -m_Size.x;
	pVtx[19].pos.x	= m_Size.x;
	pVtx[20].pos.x	= m_Size.x;
	pVtx[21].pos.x	= m_Size.x;
	pVtx[22].pos.x	= -m_Size.x;
	pVtx[23].pos.x	= -m_Size.x;

	pVtx[0].pos.y	= m_Size.y;
	pVtx[1].pos.y	= m_Size.y;
	pVtx[2].pos.y	= m_Size.y;
	pVtx[3].pos.y	= m_Size.y;
	pVtx[4].pos.y	= m_Size.y;
	pVtx[5].pos.y	= m_Size.y;
	pVtx[6].pos.y	= m_Size.y;
	pVtx[7].pos.y	= m_Size.y;
	pVtx[8].pos.y	= m_Size.y;
	pVtx[9].pos.y	= m_Size.y;
	pVtx[10].pos.y	= m_Size.y;
	pVtx[11].pos.y	= m_Size.y;
	pVtx[12].pos.y	= -m_Size.y;
	pVtx[13].pos.y	= -m_Size.y;
	pVtx[14].pos.y	= -m_Size.y;
	pVtx[15].pos.y	= -m_Size.y;
	pVtx[16].pos.y	= -m_Size.y;
	pVtx[17].pos.y	= -m_Size.y;
	pVtx[18].pos.y	= -m_Size.y;
	pVtx[19].pos.y	= -m_Size.y;
	pVtx[20].pos.y	= -m_Size.y;
	pVtx[21].pos.y	= -m_Size.y;
	pVtx[22].pos.y	= -m_Size.y;
	pVtx[23].pos.y	= -m_Size.y;

	pVtx[0].pos.z	= m_Size.z;
	pVtx[1].pos.z	= m_Size.z;
	pVtx[2].pos.z	= -m_Size.z;
	pVtx[3].pos.z	= -m_Size.z;
	pVtx[4].pos.z	= -m_Size.z;
	pVtx[5].pos.z	= m_Size.z;
	pVtx[6].pos.z	= m_Size.z;
	pVtx[7].pos.z	= m_Size.z;
	pVtx[8].pos.z	= m_Size.z;
	pVtx[9].pos.z	= -m_Size.z;
	pVtx[10].pos.z	= -m_Size.z;
	pVtx[11].pos.z	= -m_Size.z;
	pVtx[12].pos.z	= -m_Size.z;
	pVtx[13].pos.z	= m_Size.z;
	pVtx[14].pos.z	= m_Size.z;
	pVtx[15].pos.z	= m_Size.z;
	pVtx[16].pos.z	= m_Size.z;
	pVtx[17].pos.z	= -m_Size.z;
	pVtx[18].pos.z	= -m_Size.z;
	pVtx[19].pos.z	= -m_Size.z;
	pVtx[20].pos.z	= -m_Size.z;
	pVtx[21].pos.z	= m_Size.z;
	pVtx[22].pos.z	= -m_Size.z;
	pVtx[23].pos.z	= m_Size.z;

		//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	pVtx[5].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[8].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	pVtx[9].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	pVtx[10].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[11].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[12].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	pVtx[13].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	pVtx[14].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[15].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[16].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	pVtx[17].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	pVtx[18].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[19].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[20].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	pVtx[21].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	pVtx[22].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	pVtx[23].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

	for (int nCnt = 0; nCnt < 24; nCnt++)
	{
		//���_�J���[�̐ݒ�
		pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[10].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[11].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[12].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[13].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[14].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[15].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[16].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[17].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[18].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[19].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[20].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[21].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[22].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[23].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * (28),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuff,
		NULL);

	WORD* pIdx;	//�C���f�b�N�X���ւ̃|�C���^

	//�C���f�b�N�X�o�b�t�@�����b�N���A���_�ԍ��f�[�^�ւ̃|�C���^������
	g_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	pIdx[0]  = 2;
	pIdx[1]  = 0;
	pIdx[2]  = 3;
	pIdx[3]  = 1;
	pIdx[4]  = 1;
	pIdx[5]  = 12;
	pIdx[6]  = 12;
	pIdx[7]  = 4;
	pIdx[8]  = 13;
	pIdx[9]  = 5;
	pIdx[10] = 14;
	pIdx[11] = 6;
	pIdx[12] = 15;
	pIdx[13] = 7;
	pIdx[14] = 16;
	pIdx[15] = 8;
	pIdx[16] = 17;
	pIdx[17] = 9;
	pIdx[18] = 18;
	pIdx[19] = 10;
	pIdx[20] = 19;
	pIdx[21] = 11;
	pIdx[22] = 11;
	pIdx[23] = 22;
	pIdx[24] = 22;
	pIdx[25] = 20;
	pIdx[26] = 23;
	pIdx[27] = 21;

	//�C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pIdxBuff->Unlock();

	return S_OK;
}

//====================================================================
//�I������
//====================================================================
void CObjmeshCube::Uninit(void)
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
void CObjmeshCube::Update(void)
{
	m_posOld = m_pos;

	m_pos += m_move;

	if (m_Color.a > 0.0f)
	{
		if (m_fDel > 0.001f)
		{
			m_Color.a -= m_fDel;
			SetColor(m_Color);
		}
	}
	else
	{
		Uninit();
		return;
	}

	if (m_nLife != -1 && m_nLife > 0)
	{
		m_nLife--;
	}
	else if(m_nLife == 0)
	{
		Uninit();
		return;
	}

	if (m_bLife == true)
	{
		if (m_PlusMove == true)
		{
			if (m_pos.x > UninitPos.x ||
				m_pos.y > UninitPos.y || 
				m_pos.z > UninitPos.z)
			{
				Uninit();
			}
		}
		else
		{
			if (m_pos.x < UninitPos.x ||
				m_pos.y < UninitPos.y ||
				m_pos.z < UninitPos.z)
			{
				Uninit();
			}
		}
	}
}

//====================================================================
//�`�揈��
//====================================================================
void CObjmeshCube::Draw(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//���C�e�B���O���I�t�ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

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
		(28) - 2);//�`�悷��v���~�e�B�u�̐�

	//���C�e�B���O���I���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//====================================================================
//���_���W�̐ݒ�
//====================================================================
void CObjmeshCube::SetVerPos(D3DXVECTOR3 Pos0, D3DXVECTOR3 Pos1, D3DXVECTOR3 Pos2, D3DXVECTOR3 Pos3)
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
//���_���W�̐ݒ�
//====================================================================
void CObjmeshCube::SetVerSize(void)
{
	VERTEX_3D* pVtx;	//���_�|�C���^������

	//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ� 
	pVtx[0].pos.x = -m_Size.x;
	pVtx[1].pos.x = m_Size.x;
	pVtx[2].pos.x = -m_Size.x;
	pVtx[3].pos.x = m_Size.x;
	pVtx[4].pos.x = m_Size.x;
	pVtx[5].pos.x = m_Size.x;
	pVtx[6].pos.x = m_Size.x;
	pVtx[7].pos.x = -m_Size.x;
	pVtx[8].pos.x = -m_Size.x;
	pVtx[9].pos.x = -m_Size.x;
	pVtx[10].pos.x = -m_Size.x;
	pVtx[11].pos.x = m_Size.x;
	pVtx[12].pos.x = m_Size.x;
	pVtx[13].pos.x = m_Size.x;
	pVtx[14].pos.x = m_Size.x;
	pVtx[15].pos.x = -m_Size.x;
	pVtx[16].pos.x = -m_Size.x;
	pVtx[17].pos.x = -m_Size.x;
	pVtx[18].pos.x = -m_Size.x;
	pVtx[19].pos.x = m_Size.x;
	pVtx[20].pos.x = m_Size.x;
	pVtx[21].pos.x = m_Size.x;
	pVtx[22].pos.x = -m_Size.x;
	pVtx[23].pos.x = -m_Size.x;

	pVtx[0].pos.y = m_Size.y;
	pVtx[1].pos.y = m_Size.y;
	pVtx[2].pos.y = m_Size.y;
	pVtx[3].pos.y = m_Size.y;
	pVtx[4].pos.y = m_Size.y;
	pVtx[5].pos.y = m_Size.y;
	pVtx[6].pos.y = m_Size.y;
	pVtx[7].pos.y = m_Size.y;
	pVtx[8].pos.y = m_Size.y;
	pVtx[9].pos.y = m_Size.y;
	pVtx[10].pos.y = m_Size.y;
	pVtx[11].pos.y = m_Size.y;
	pVtx[12].pos.y = -m_Size.y;
	pVtx[13].pos.y = -m_Size.y;
	pVtx[14].pos.y = -m_Size.y;
	pVtx[15].pos.y = -m_Size.y;
	pVtx[16].pos.y = -m_Size.y;
	pVtx[17].pos.y = -m_Size.y;
	pVtx[18].pos.y = -m_Size.y;
	pVtx[19].pos.y = -m_Size.y;
	pVtx[20].pos.y = -m_Size.y;
	pVtx[21].pos.y = -m_Size.y;
	pVtx[22].pos.y = -m_Size.y;
	pVtx[23].pos.y = -m_Size.y;

	pVtx[0].pos.z = m_Size.z;
	pVtx[1].pos.z = m_Size.z;
	pVtx[2].pos.z = -m_Size.z;
	pVtx[3].pos.z = -m_Size.z;
	pVtx[4].pos.z = -m_Size.z;
	pVtx[5].pos.z = m_Size.z;
	pVtx[6].pos.z = m_Size.z;
	pVtx[7].pos.z = m_Size.z;
	pVtx[8].pos.z = m_Size.z;
	pVtx[9].pos.z = -m_Size.z;
	pVtx[10].pos.z = -m_Size.z;
	pVtx[11].pos.z = -m_Size.z;
	pVtx[12].pos.z = -m_Size.z;
	pVtx[13].pos.z = m_Size.z;
	pVtx[14].pos.z = m_Size.z;
	pVtx[15].pos.z = m_Size.z;
	pVtx[16].pos.z = m_Size.z;
	pVtx[17].pos.z = -m_Size.z;
	pVtx[18].pos.z = -m_Size.z;
	pVtx[19].pos.z = -m_Size.z;
	pVtx[20].pos.z = -m_Size.z;
	pVtx[21].pos.z = m_Size.z;
	pVtx[22].pos.z = -m_Size.z;
	pVtx[23].pos.z = m_Size.z;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//====================================================================
//�e�N�X�`�����W�̐ݒ�
//====================================================================
void CObjmeshCube::SetAnim(D3DXVECTOR2 Tex)
{
	VERTEX_3D* pVtx;	//���_�|�C���^������

					//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(Tex.x, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, Tex.y);
	pVtx[3].tex = D3DXVECTOR2(Tex.x, Tex.y);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//====================================================================
//���_�J���[�̐ݒ�
//====================================================================
void CObjmeshCube::SetColor(D3DXCOLOR col)
{
	m_Color = col;

	VERTEX_3D* pVtx;	//���_�|�C���^������

					//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < 24; nCnt++)
	{
		//���_�J���[�̐ݒ�
		pVtx[nCnt].col = m_Color;
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//====================================================================
//���_�J���[�̐ݒ�
//====================================================================
void CObjmeshCube::SetColorType(int Type)
{
	VERTEX_3D* pVtx;	//���_�|�C���^������

	//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	switch (Type)
	{
	case 0:
		pVtx[0].col  = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pVtx[1].col  = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pVtx[2].col  = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pVtx[3].col  = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pVtx[4].col  = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[5].col  = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[6].col  = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[7].col  = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[8].col  = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[9].col  = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[12].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pVtx[13].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pVtx[14].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pVtx[15].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pVtx[16].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pVtx[17].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pVtx[18].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pVtx[19].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pVtx[20].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pVtx[21].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pVtx[22].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pVtx[23].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

		break;
	default:
		break;
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//====================================================================
//���_�J���[�̐ݒ�
//====================================================================
void CObjmeshCube::SetTexture(const char* name)
{
	CTexture* pTexture = CManager::GetInstance()->GetTexture();
	m_nIdxTexture = pTexture->Regist(name);
}