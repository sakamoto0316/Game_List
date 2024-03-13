//===========================================
//
// ���炢���C������[tarai.cpp]
// Author ��{�ėB
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "tarai.h"
#include "useful.h"
#include "texture.h"

#include "object3D.h"
#include "Himo.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define GEAR_CYCLE_SPEED		(0.1f)		// ��鑬�x

//==============================
// �R���X�g���N�^
//==============================
CTarai::CTarai() : CModel(CObject::TYPE_NONE, CObject::PRIORITY_BLOCK)
{
	m_pHimo = nullptr;			// �R�̃|�C���^(�����͂��Ȃ�)
	m_move = NONE_D3DXVECTOR3;
	m_nIndex = -1;
	m_pShadow = NULL;
}

//==============================
// �f�X�g���N�^
//==============================
CTarai::~CTarai()
{

}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CTarai::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // �����������Ɏ��s�����ꍇ

	  // ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_pHimo = nullptr;			// �R�̃|�C���^(�����͂��Ȃ�)

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �j�Ђ̏I������
//========================================
void CTarai::Uninit(void)
{
	if (m_pHimo != nullptr)
	{ // �R�̃|�C���^�� NULL ����Ȃ��ꍇ

		// �R�� NULL �ɂ���
		m_pHimo = nullptr;
	}

	// �I������
	CModel::Uninit();

	if (m_pShadow != NULL)
	{
		// �`�揈��
		m_pShadow->Uninit();
		m_pShadow = NULL;
	}
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CTarai::Update(void)
{
	// �ʒu���擾����
	D3DXVECTOR3 pos = GetPos();

	// �ʒu�����Z����
	m_move.y -= 0.8f;

	if (pos.y < 0.0f)
	{
		m_pHimo->NULLTarai(m_nIndex);
		Uninit();
		return;
	}

	// �ʒu�X�V
	pos.y += m_move.y;

	// �ʒu��ݒ肷��
	SetPos(pos);

	if (m_pShadow != NULL)
	{
		// �X�V����
		m_pShadow->Update();
	}
}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CTarai::Draw(void)
{
	// �`�揈��
	CModel::Draw();

	if (m_pShadow != NULL)
	{
		// �f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

		//���u�����f�B���O�����Z�����ɐݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		// �`�揈��
		m_pShadow->Draw();

		//���u�����f�B���O�����ɖ߂�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CTarai::SetData(const D3DXVECTOR3& pos, CHimo* pHimo)
{
	// ���̐ݒ菈��
	SetPos(pos);								// �ʒu
	SetPosOld(pos);								// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);					// ����
	SetScale(NONE_SCALE);						// �g�嗦
	SetFileData(CXFile::TYPE_TARAI);			// ���f�����

	if (m_pShadow == NULL)
	{
		m_pShadow = CObject3D::Create(CObject::TYPE_NONE, PRIORITY_BG);
		m_pShadow->SetPos(D3DXVECTOR3(pos.x, 0.0f, pos.z));			// �ʒu
		m_pShadow->SetPosOld(D3DXVECTOR3(pos.x, 0.0f, pos.z));		// �O��̈ʒu
		m_pShadow->SetRot(D3DXVECTOR3(D3DX_PI * 0.0f, 0.0f, 0.0f));	// ����
		m_pShadow->SetSize(D3DXVECTOR3(150.0f, 0.0f, 150.0f));		// �T�C�Y
		m_pShadow->SetVtxColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));	// �F
		m_pShadow->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\shadow.jpg"));		// �e�N�X�`���̊��蓖�ď���

		// ���_���W�̐ݒ菈��
		m_pShadow->SetVertex();
	}

	if (m_pHimo == nullptr)
	{ // �R�� NULL �̏ꍇ

		// �R�̃|�C���^������
		m_pHimo = pHimo;
	}
}

//=======================================
// ��������
//=======================================
CTarai* CTarai::Create(const D3DXVECTOR3& pos, CHimo* pHimo)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CTarai* pTarai = nullptr;	// �C���X�^���X�𐶐�

	if (pTarai == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

	  // �C���X�^���X�𐶐�
		pTarai = new CTarai;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

	  // ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pTarai != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

	  // ����������
		if (FAILED(pTarai->Init()))
		{ // �������Ɏ��s�����ꍇ

		  // ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pTarai->SetData(pos, pHimo);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

	  // ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// ���炢�̃M�A�̃|�C���^��Ԃ�
	return pTarai;
}