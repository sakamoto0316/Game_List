//============================================
//
//	�L���[�u�G�t�F�N�g [CubeEffect.cpp]
//	Author:sakamoto kai
//
//============================================
#include "CubeEffect.h"
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
CCubeEffect::CCubeEffect(int nPriority) :CObjmeshCube(nPriority)
{
	m_pos = INITVECTOR3;
	m_move = INITVECTOR3;
	m_nLife = -1;
	m_bFall = false;
}


//====================================================================
//�f�X�g���N�^
//====================================================================
CCubeEffect::~CCubeEffect()
{

}

//====================================================================
//��������
//====================================================================
CCubeEffect* CCubeEffect::Create(void)
{
	CCubeEffect* pObject3D = NULL;

	if (pObject3D == NULL)
	{
		//�I�u�W�F�N�g3D�̐���
		pObject3D = new CCubeEffect();
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
HRESULT CCubeEffect::Init(void)
{
	CObjmeshCube::Init();

	SetTexture("data\\TEXTURE\\Test.jpg");
	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	SetType(TYPE_CUBEEFFECT);

	return S_OK;
}

//====================================================================
//�I������
//====================================================================
void CCubeEffect::Uninit(void)
{
	CObjmeshCube::Uninit();

	SetDeathFlag(true);
}

//====================================================================
//�X�V����
//====================================================================
void CCubeEffect::Update(void)
{
	if (m_bFall == true)
	{
		m_move.y -= 0.98f;
	}

	m_pos += m_move;

	CObjmeshCube::SetPos(m_pos);
	CObjmeshCube::Update();

	if (m_nLife > 0 && m_nLife != -1)
	{
		m_nLife--;
	}
	else if(m_nLife == 0)
	{
		Uninit();
		return;
	}

	if (m_bFall == true)
	{
		if (m_pos.y < 0.0f)
		{
			Uninit();
			return;
		}
	}
}

//====================================================================
//�`�揈��
//====================================================================
void CCubeEffect::Draw(void)
{
	CObjmeshCube::Draw();
}