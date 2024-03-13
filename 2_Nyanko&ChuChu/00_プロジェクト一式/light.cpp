//===========================================
//
// ���C�g�̃��C������[light.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "light.h"

#include "input.h"
#include "debugproc.h"

//-------------------------------------------
// �������O���
//-------------------------------------------
namespace
{
	const float LIGHT_PAWOR = 0.8f;
	const D3DXCOLOR LIGHT_DIFFUSE[NUM_LIGHT] =			// ���C�g�̐F
	{
		D3DXCOLOR(LIGHT_PAWOR, LIGHT_PAWOR, LIGHT_PAWOR, 1.0f),
		D3DXCOLOR(LIGHT_PAWOR, LIGHT_PAWOR, LIGHT_PAWOR, 1.0f),
		D3DXCOLOR(LIGHT_PAWOR, LIGHT_PAWOR, LIGHT_PAWOR, 1.0f),
	};
	const D3DXVECTOR3 LIGHT_VECTOR[NUM_LIGHT] =			// ���C�g�̕���
	{
		D3DXVECTOR3(-0.5f, -0.6f, -0.5f),
		D3DXVECTOR3(0.0f, 0.1f, 0.9f),
		D3DXVECTOR3(0.8f, -0.6f, 0.5f),
	};
}

//=========================
// �R���X�g���N�^
//=========================
CLight::CLight()
{
	for (int nCntSet = 0; nCntSet < NUM_LIGHT; nCntSet++)
	{
		// ���C�g�̏����N���A����
		ZeroMemory(&m_light[nCntSet], sizeof(D3DLIGHT9));
	}
}

//=========================
// �f�X�g���N�^
//=========================
CLight::~CLight()
{

}

//=========================
// ���C�g�̏���������
//=========================
HRESULT CLight::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	D3DXVECTOR3 vecDir;				// �ݒ�p�����x�N�g��

	for (int nCntSet = 0; nCntSet < NUM_LIGHT; nCntSet++)
	{
		// ���C�g�̏����N���A����
		ZeroMemory(&m_light[nCntSet], sizeof(D3DLIGHT9));

		// ���C�g�̎�ނ�ݒ�
		m_light[nCntSet].Type = D3DLIGHT_DIRECTIONAL;

		// ���C�g�̊g�U����ݒ�
		m_light[nCntSet].Diffuse = LIGHT_DIFFUSE[nCntSet];

		// ���C�g�̕�����ݒ�
		vecDir = LIGHT_VECTOR[nCntSet];

		// �x�N�g���𐳋K������
		D3DXVec3Normalize(&vecDir, &vecDir);

		m_light[nCntSet].Direction = vecDir;

		// ���C�g��ݒ肷��
		pDevice->SetLight(nCntSet, &m_light[nCntSet]);

		// ���C�g��L���ɂ���
		pDevice->LightEnable(nCntSet, TRUE);
	}

	// ������Ԃ�
	return S_OK;
}

//=========================
// ���C�g�̏I������
//=========================
void CLight::Uninit(void)
{

}

//=========================
// ���C�g�̍X�V����
//=========================
void CLight::Update(void)
{

}