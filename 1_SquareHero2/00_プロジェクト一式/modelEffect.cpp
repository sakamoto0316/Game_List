//============================================
//
//	�G�̏��� [enemy.cpp]
//	Author:sakamoto kai
//
//============================================
#include "modelEffect.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "texture.h"
#include "XModel.h"
#include "player.h"
#include "Particle.h"
#include "objGauge2D.h"
#include "number.h"
#include "input.h"
#include "CubeBlock.h"
#include "CubeDamage.h"
#include "sound.h"
#include "CubeSpin.h"
#include "camera.h"
#include "fade.h"

//�}�N����`
#define COLLISION_SIZE (D3DXVECTOR3(20.0f,20.0f,20.0f))		//�����蔻��
#define MOVE_SPEED (3.0f)		//�ړ����x
//====================================================================
//�R���X�g���N�^
//====================================================================
CModelEffect::CModelEffect(int nPriority) : CObjectX(nPriority)
{
	SetWight(COLLISION_SIZE.x);
	SetHeight(COLLISION_SIZE.y);
	m_nIdxXModel = NULL;
	m_nIdxTexture = -1;
	m_pos = INITVECTOR3;
	m_rot = INITVECTOR3;
	m_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

//====================================================================
//�f�X�g���N�^
//====================================================================
CModelEffect::~CModelEffect()
{

}

//====================================================================
//��������
//====================================================================
CModelEffect* CModelEffect::Create(char* pModelName)
{
	CModelEffect* pBlock = NULL;

	if (pBlock == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pBlock = new CModelEffect();
	}

	//�I�u�W�F�N�g�̏���������
	if (FAILED(pBlock->Init(pModelName)))
	{//���������������s�����ꍇ
		return NULL;
	}

	return pBlock;
}

//====================================================================
//����������
//====================================================================
HRESULT CModelEffect::Init(char* pModelName)
{
	SetType(CObject::TYPE_EFFECT);

	CObjectX::Init(pModelName);

	return S_OK;
}

//====================================================================
//�I������
//====================================================================
void CModelEffect::Uninit(void)
{
	CObjectX::Uninit();
}

//====================================================================
//�X�V����
//====================================================================
void CModelEffect::Update(void)
{
	if (m_color.a > 0.0f)
	{
		SetMatColor(m_color);
		m_color.a -= 0.05f;
	}
	else
	{
		Uninit();
	}

	CObjectX::SetPos(m_pos);
	CObjectX::SetRot(m_rot);
}

//====================================================================
//�`�揈��
//====================================================================
void CModelEffect::Draw(void)
{
	CObjectX::Draw();
}