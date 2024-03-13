//============================================
//
//	�����̏��� [numberBillboard.cpp]
//	Author:sakamoto kai
//
//============================================
#include "numberFall.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"

//�}�N����`
#define NUMBER_WIGHT (20.0f)		//����
#define NUMBER_HEIGHT (20.0f)		//�c��

//====================================================================
//�R���X�g���N�^
//====================================================================
CNumberFall::CNumberFall(int nPriority) : CNumberBillboard(nPriority)
{
	SetWight(NUMBER_WIGHT);
	SetHeight(NUMBER_HEIGHT);
	m_move.x = 0.0f;
	m_move.y = 5.0f;
	m_move.z = 0.0f;
	m_ColorA = 1.0f;
}

//====================================================================
//�f�X�g���N�^
//====================================================================
CNumberFall::~CNumberFall()
{

}

//====================================================================
//��������
//====================================================================
CNumberFall* CNumberFall::Create(void)
{
	CNumberFall* pNumber = NULL;

	if (pNumber == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pNumber = new CNumberFall();
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
HRESULT CNumberFall::Init(void)
{
	CNumberBillboard::Init();

	return S_OK;
}

//====================================================================
//�I������
//====================================================================
void CNumberFall::Uninit(void)
{
	CNumberBillboard::Uninit();
}

//====================================================================
//�X�V����
//====================================================================
void CNumberFall::Update(void)
{
	D3DXVECTOR3 pos = GetPos();

	m_move.y -= 0.98f;
	m_ColorA -= 0.03f;

	pos += m_move;

	SetPos(pos);
	SetColorA(m_ColorA);

	//���_���̍X�V
	CNumberBillboard::Update();

	if (m_ColorA < 0.0f)
	{
		Uninit();
	}
}

//====================================================================
//�`�揈��
//====================================================================
void CNumberFall::Draw(void)
{
	CNumberBillboard::Draw();
}