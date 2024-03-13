//=======================================
//
// ����̂ӂ������̃��C������[weapon_balloon.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "weapon_balloon.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

//=======================================
// �}�N����`
//=======================================


//=========================
// �R���X�g���N�^
//=========================
CWeaponBalloon::CWeaponBalloon() : CBillboard(CObject::TYPE_WEAPONBALLOON, CObject::PRIORITY_PLAYER)
{
	// �S�Ă̒l���N���A����
}

//=========================
// �f�X�g���N�^
//=========================
CWeaponBalloon::~CWeaponBalloon()
{

}

//=========================
// ����������
//=========================
HRESULT CWeaponBalloon::Init(void)
{
	if (FAILED(CBillboard::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������

	// ������Ԃ�
	return S_OK;
}

//=========================
// �I������
//=========================
void CWeaponBalloon::Uninit(void)
{
	// �I��
	CBillboard::Uninit();
}

//=========================
// �X�V����
//=========================
void CWeaponBalloon::Update(void)
{
	
}

//=========================
// �`�揈��
//=========================
void CWeaponBalloon::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �`�揈��
	CBillboard::DrawLightOff();

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=========================
// ���̐ݒ菈��
//=========================
void CWeaponBalloon::SetData(const D3DXVECTOR3& pos, const char* pFileName)
{
	// �X�N���[���̐ݒ菈��
	SetPos(pos);			// �ʒu�ݒ�
	SetPosOld(pos);			// �O��̈ʒu�ݒ�
	SetSize(D3DXVECTOR3(140.0f, 140.0f, 0.0f));	// �T�C�Y�ݒ�

	// ���_���̏�����
	SetVertex();

	// �e�N�X�`���̓ǂݍ��ݏ���
	BindTexture(CManager::Get()->GetTexture()->Regist(pFileName));
}

//=========================
// ��������
//=========================
CWeaponBalloon* CWeaponBalloon::Create(const D3DXVECTOR3& pos, const char* pFileName)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CWeaponBalloon* pBalloon = nullptr;		// �ӂ������̃C���X�^���X�𐶐�

	if (pBalloon == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pBalloon = new CWeaponBalloon;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pBalloon != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pBalloon->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pBalloon->SetData(pos, pFileName);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �ӂ������̃|�C���^��Ԃ�
	return pBalloon;
}