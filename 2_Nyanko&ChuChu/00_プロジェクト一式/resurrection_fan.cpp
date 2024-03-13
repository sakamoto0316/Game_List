//===========================================
//
// �����Ԃ�̉~�͈̔͂̏���[resurrection_fan.h]
// Author ����������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "resurrection_fan.h"
#include "model.h"
#include "texture.h"
#include "player.h"
#include "game.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define RADIUS			(100.0f)	// ���a
#define DEFAULT_COLOR	(D3DXCOLOR(0.2f, 0.5f, 0.5f, 0.2f))		// �����F
#define REZ_COLOR		(D3DXCOLOR(0.0f, 1.0f, 0.2f, 0.6f))		// �񕜂̐F

//-------------------------------------------
// �ÓI�����o�ϐ��錾
//-------------------------------------------

//==============================
// �R���X�g���N�^
//==============================
CRessrectionFan::CRessrectionFan() : CObject3DFan(CObject::TYPE_PLAYER, CObject::PRIORITY_PLAYER)
{
	// �S�Ă̒l���N���A����
	m_nRezTime = 0;			// �񕜎���
	m_bRez = false;			// �񕜂��Ă邩

}

//==============================
// �f�X�g���N�^
//==============================
CRessrectionFan::~CRessrectionFan()
{

}

//==============================
// �����Ԃ�̉~�̏���������
//==============================
HRESULT CRessrectionFan::Init(void)
{
	if (FAILED(CObject3DFan::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_nRezTime = 0;			// �񕜎���
	m_bRez = false;			// �񕜂��Ă邩

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �����Ԃ�̉~�̏I������
//========================================
void CRessrectionFan::Uninit(void)
{
	// �I������
	CObject3DFan::Uninit();
}

//=====================================
// �����Ԃ�̉~�̍X�V����
//=====================================
void CRessrectionFan::Update(void)
{
	// ���_���W�̐ݒ菈��
	SetVertex();

	// ���_�̐F�̐ݒ菈��
	SetVtxColor(DEFAULT_COLOR, REZ_COLOR, m_nRezTime);
}

//=====================================
// �����Ԃ�̉~�̕`�揈��
//=====================================
void CRessrectionFan::Draw(void)
{
	// �`�揈��
	CObject3DFan::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CRessrectionFan::SetData(const D3DXVECTOR3& pos, const D3DXCOLOR& col)
{
	// �ݒ菈���ɕ֗��ȃ}�N����`
	//NONE_D3DXVECTOR3					// �������X���Ȃ����Ƃ��Ɏg�p����
	//NONE_SCALE						// �g�嗦��ύX���Ȃ��Ƃ��Ƃ��Ɏg��
	// ���̐ݒ菈��

	//==========================================================================
	// 3D�|���S��
	//==========================================================================
	SetPos(pos);					// �ʒu
	SetPosOld(GetPos());			// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);		// ����
	SetSize(NONE_SCALE);			// �T�C�Y
	SetNumAngle(NUM_REZ_ANGLE);		// �p�x�̑���
	SetRadius(RADIUS);				// ���a
	SetColor(col);					// �F
	BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\cheese.jpg"));		// �e�N�X�`���̊��蓖�ď���
}

//=======================================
// ��������
//=======================================
CRessrectionFan* CRessrectionFan::Create(const D3DXVECTOR3& pos, const D3DXCOLOR& col)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CRessrectionFan* pRessrectionFan = nullptr;	// �T���v���̃C���X�^���X�𐶐�

	if (pRessrectionFan == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �C���X�^���X�𐶐�
		pRessrectionFan = new CRessrectionFan;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pRessrectionFan != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ
		
		// ���̐ݒ菈��
		pRessrectionFan->SetData(pos, col);

		// ����������
		if (FAILED(pRessrectionFan->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �T���v���̃|�C���^��Ԃ�
	return pRessrectionFan;
}

//=======================================
// �񕜎��Ԃ̐ݒ�
//=======================================
void CRessrectionFan::SetResurrectionFan(int nFan)
{
	// �񕜎��ԑ��
	m_nRezTime = nFan;
}

//=======================================
// �p�x�̎擾
//=======================================
int CRessrectionFan::GetResurrectionFan(void)
{
	// �񕜎��Ԃ�Ԃ�
	return m_nRezTime;
}