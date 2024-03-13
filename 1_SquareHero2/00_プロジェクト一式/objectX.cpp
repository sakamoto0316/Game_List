//============================================
//
//	�I�u�W�F�N�gX�t�@�C�� [objectX.cpp]
//	Author:sakamoto kai
//
//============================================
#include "objectX.h"
#include "renderer.h"
#include "manager.h"
#include "Xmodel.h"
#include "texture.h"

#define POLYDON_SIZE (200.0f)

//====================================================================
//�R���X�g���N�^
//====================================================================
CObjectX::CObjectX(int nPriority) :CObject(nPriority)
{
	m_pTexture = NULL;
	m_dwNumMat = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_MatColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_bUseColor = false;
	m_Scaling = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	for(int nCnt = 0; nCnt < 64; nCnt++)
	{
		m_IdxTextureNumber[nCnt] = -1;
	}
}

//====================================================================
//�f�X�g���N�^
//====================================================================
CObjectX::~CObjectX()
{

}

//====================================================================
//��������
//====================================================================
CObjectX *CObjectX::Create(char* pModelName)
{
	CObjectX *pObjectX = NULL;

	if (pObjectX == NULL)
	{
		//�I�u�W�F�N�g3D�̐���
		pObjectX = new CObjectX();
	}

	//�I�u�W�F�N�g�̏���������
	if (FAILED(pObjectX->Init(pModelName)))
	{//���������������s�����ꍇ
		return NULL;
	}

	return pObjectX;
}

//====================================================================
//����������
//====================================================================
HRESULT CObjectX::Init()
{
	return S_OK;
}

//====================================================================
//����������
//====================================================================
HRESULT CObjectX::Init(char* pModelName)
{
	//X�t�@�C���̊��蓖��
	CXModel* pXModel = CManager::GetInstance()->GetXModel();
	m_IdxModelNumber = pXModel->Regist(pModelName);
	pXModel->GetXModelInfo(&m_pBuffMat, &m_dwNumMat, &m_pMesh, m_IdxModelNumber);

	return S_OK;
}

//====================================================================
//�I������
//====================================================================
void CObjectX::Uninit(void)
{
	if (m_pTexture != NULL)
	{
		//���������J������
		delete[] m_pTexture;
		m_pTexture = NULL;
	}

	SetDeathFlag(true);
}

//====================================================================
//�X�V����
//====================================================================
void CObjectX::Update(void)
{
	//SetVerTex();
}

//====================================================================
//�`�揈��
//====================================================================
void CObjectX::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//X���f���̎擾
	CXModel::XModel *pXmodel = CManager::GetInstance()->GetXModel()->GetXModel(m_IdxModelNumber);
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	D3DXMatrixScaling(&m_mtxWorld, m_Scaling.x, m_Scaling.y, m_Scaling.z);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	
	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A��������
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^����������
	pMat = (D3DXMATERIAL*)pXmodel->m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)pXmodel->m_dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		if (m_bUseColor == true)
		{
			m_StateMat.MatD3D.Diffuse = m_MatColor;
			pDevice->SetMaterial(&m_StateMat.MatD3D);
		}
		else
		{
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		}

		//�e�N�X�`���̐ݒ�
		//pDevice->SetTexture(0, m_pTexture[nCntMat]);
		if (m_IdxTextureNumber[nCntMat] != -1)
		{
			pDevice->SetTexture(0, pTexture->GetAddress(m_IdxTextureNumber[nCntMat]));
		}
		else
		{
			pDevice->SetTexture(0, NULL);
		}

		//���f��(�p�[�c)�̕`��
		pXmodel->m_pMesh->DrawSubset(nCntMat);
	}
	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//====================================================================
//�`�揈��
//====================================================================
void CObjectX::Draw(float fAlpha)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//X���f���̎擾
	CXModel::XModel* pXmodel = CManager::GetInstance()->GetXModel()->GetXModel(m_IdxModelNumber);
	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL* pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

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

	//���݂̃}�e���A��������
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^����������
	pMat = (D3DXMATERIAL*)pXmodel->m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)pXmodel->m_dwNumMat; nCntMat++)
	{
		m_StateMat.MatD3D.Diffuse.r = pMat[nCntMat].MatD3D.Diffuse.r;
		m_StateMat.MatD3D.Diffuse.g = pMat[nCntMat].MatD3D.Diffuse.g;
		m_StateMat.MatD3D.Diffuse.b = pMat[nCntMat].MatD3D.Diffuse.b;
		m_StateMat.MatD3D.Diffuse.a = fAlpha;
		pDevice->SetMaterial(&m_StateMat.MatD3D);

		//�e�N�X�`���̐ݒ�
		//pDevice->SetTexture(0, m_pTexture[nCntMat]);
		if (m_IdxTextureNumber[nCntMat] != -1)
		{
			pDevice->SetTexture(0, pTexture->GetAddress(m_IdxTextureNumber[nCntMat]));
		}
		else
		{
			pDevice->SetTexture(0, NULL);
		}

		//���f��(�p�[�c)�̕`��
		pXmodel->m_pMesh->DrawSubset(nCntMat);
	}
	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//====================================================================
//���f�����̊��蓖��
//====================================================================
void CObjectX::SetXModelIdx(int Idx)
{
	m_IdxModelNumber = Idx;
}

//====================================================================
//���f�����̊��蓖��
//====================================================================
void CObjectX::SetTextureIdx(int nCnt, int Idx)
{
	m_IdxTextureNumber[nCnt] = Idx;
}

//====================================================================
//���f�����̊��蓖��
//====================================================================
void CObjectX::BindFile(LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD pdwNumMat)
{
	////�f�o�C�X�̎擾
	//LPDIRECT3DDEVICE9 pDevice =CManager::GetInstance()->GetRenderer()->GetDevice();
	//D3DXMATERIAL *pMat;	//�}�e���A���ւ̃|�C���^

	////���̊��蓖��
	//m_pMesh = pMesh;
	//m_pBuffMat = pBuffMat;
	//m_dwNumMat = pdwNumMat;

	////X���f���̎擾
	//CXModel::XModel *pXmodel =CManager::GetInstance()->GetXModel()->GetXModel(GetIdxXModel());

	////�e�N�X�`���̃��������m��
	//if (m_pTexture == NULL)
	//{
	//	//���������m�ۂ���
	//	m_pTexture = new LPDIRECT3DTEXTURE9[pXmodel->m_dwNumMat];
	//}

	////�}�e���A�����ɑ΂���|�C���^������
	//pMat = (D3DXMATERIAL*)pXmodel->m_pBuffMat->GetBufferPointer();

	//for (int nCntMat = 0; nCntMat < (int)pXmodel->m_dwNumMat; nCntMat++)
	//{
	//	if (pMat[nCntMat].pTextureFilename != NULL)
	//	{
	//		//�e�N�X�`���̓ǂݍ���
	//		D3DXCreateTextureFromFile(pDevice,
	//			pMat[nCntMat].pTextureFilename,
	//			&m_pTexture[nCntMat]);
	//	}
	//	else
	//	{
	//		m_pTexture[nCntMat] = NULL;
	//	}
	//}
}

//====================================================================
//���_���W�̐ݒ�
//====================================================================
void CObjectX::SetVerTex(void)
{

}

//====================================================================
//�e�N�X�`�����W�̐ݒ�
//====================================================================
void CObjectX::SetAnim(D3DXVECTOR2 Tex)
{

}

//====================================================================
//���_�J���[�̐ݒ�
//====================================================================
void CObjectX::SetColor(D3DXCOLOR col)
{

}