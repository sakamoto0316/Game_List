//============================================
//
//	�����̏��� [numberBillboard.cpp]
//	Author:sakamoto kai
//
//============================================
#include "numberBillboard.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"

//�}�N����`
#define NUMBER_WIGHT (100.0f)		//����
#define NUMBER_HEIGHT (100.0f)		//�c��

//====================================================================
//�R���X�g���N�^
//====================================================================
CNumberBillboard::CNumberBillboard(int nPriority) : CObjectBillboard(nPriority)
{
	SetWight(NUMBER_WIGHT);
	SetHeight(NUMBER_HEIGHT);
	m_nNumber = 0;
}

//====================================================================
//�f�X�g���N�^
//====================================================================
CNumberBillboard::~CNumberBillboard()
{

}

//====================================================================
//��������
//====================================================================
CNumberBillboard* CNumberBillboard::Create(void)
{
	CNumberBillboard* pNumber = NULL;

	if (pNumber == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pNumber = new CNumberBillboard();
	}

	//�I�u�W�F�N�g�̏���������
	if (FAILED(pNumber->Init()))
	{//���������������s�����ꍇ
		return NULL;
	}

	return pNumber;
}

//====================================================================
//����������
//====================================================================
HRESULT CNumberBillboard::Init(void)
{
	CObjectBillboard::Init();

	CTexture* pTexture = CManager::GetInstance()->GetTexture();;
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\Number01.png");

	SetType(CObject::TYPE_NUMBER);

	SetAnim(D3DXVECTOR2(0.2f, 0.2f));

	return S_OK;
}

//====================================================================
//�I������
//====================================================================
void CNumberBillboard::Uninit(void)
{
	CObjectBillboard::Uninit();
}

//====================================================================
//�X�V����
//====================================================================
void CNumberBillboard::Update(void)
{
	VERTEX_3D* pVtx;	//���_�|�C���^������

	//���_�o�b�t�@�����b�N���A���X���ւ̃|�C���^������
	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//���_���̍X�V
	CObjectBillboard::Update();

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f + (m_nNumber * 0.1f), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f + (m_nNumber * 0.1f), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + (m_nNumber * 0.1f), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + (m_nNumber * 0.1f), 1.0f);

	//���_�o�b�t�@���A�����b�N����
	GetVtxBuff()->Unlock();
}

//====================================================================
//�`�揈��
//====================================================================
void CNumberBillboard::Draw(void)
{
	CObjectBillboard::Draw();
}