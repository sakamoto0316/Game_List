//=======================================
//
// �v���C���[��ID�\���̃��C������[player_idUI.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "player_idUI.h"
#include "useful.h"

//=======================================
// �}�N����`
//=======================================
#define PLAYER_ID_PATTERN	((float)(1.0f / 4.0f))					// �v���C���[��ID��1�ʂ��Ƃ̃T�C�Y
#define PLAYER_ID_SIZE		(D3DXVECTOR3(40.0f, 25.0f, 0.0f))		// �v���C���[��ID�\���̃T�C�Y
#define PLAYER_ID_TEXTURE	"data\\TEXTURE\\PlayerID.png"			// �v���C���[��ID�\���̃e�N�X�`��

//=========================
// �R���X�g���N�^
//=========================
CPlayerID::CPlayerID() : CBillboard(CObject::TYPE_NONE, CObject::PRIORITY_PLAYER)
{
	// �S�Ă̒l���N���A����
	m_bDisp = true;		// �`���
}

//=========================
// �f�X�g���N�^
//=========================
CPlayerID::~CPlayerID()
{

}

//=========================
// ����������
//=========================
HRESULT CPlayerID::Init(void)
{
	if (FAILED(CBillboard::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_bDisp = true;		// �`���

	// ������Ԃ�
	return S_OK;
}

//=========================
// �I������
//=========================
void CPlayerID::Uninit(void)
{
	// �I��
	CBillboard::Uninit();
}

//=========================
// �X�V����
//=========================
void CPlayerID::Update(void)
{
	// ���_���̏�����
	SetVertex();
}

//=========================
// �`�揈��
//=========================
void CPlayerID::Draw(void)
{
	if (m_bDisp == true)
	{ // �`��󋵂� true �̏ꍇ

		// �`�揈��
		CBillboard::DrawLightOff();
	}
}

//=========================
// ���̐ݒ菈��
//=========================
void CPlayerID::SetData(const D3DXVECTOR3& pos, const int nID)
{
	// �X�N���[���̐ݒ菈��
	SetPos(pos);				// �ʒu�ݒ�
	SetPosOld(pos);				// �O��̈ʒu�ݒ�
	SetSize(PLAYER_ID_SIZE);	// �T�C�Y�ݒ�

	// �S�Ă̒l��ݒ肷��
	m_bDisp = true;		// �`���

	// ���_���̏�����
	SetVertex();

	// �e�N�X�`�����W�̐ݒ菈��
	SetVtxAnim(PLAYER_ID_PATTERN, nID);

	// �e�N�X�`���̓ǂݍ��ݏ���
	BindTexture(CManager::Get()->GetTexture()->Regist(PLAYER_ID_TEXTURE));
}

//=========================
// ��������
//=========================
CPlayerID* CPlayerID::Create(const D3DXVECTOR3& pos, const int nID)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CPlayerID* pPlayerID = nullptr;	// �v���C���[��ID�\���̃C���X�^���X�𐶐�

	if (pPlayerID == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pPlayerID = new CPlayerID;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pPlayerID != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pPlayerID->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pPlayerID->SetData(pos, nID);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �v���C���[��ID�\���̃|�C���^��Ԃ�
	return pPlayerID;
}

//=========================
// �`��󋵂̐ݒ菈��
//=========================
void CPlayerID::SetEnableDisp(const bool bDisp)
{
	// �`��󋵂�ݒ肷��
	m_bDisp = bDisp;
}

//=========================
// �`��󋵂̎擾����
//=========================
bool CPlayerID::IsDisp(void) const
{
	// �`��󋵂�Ԃ�
	return m_bDisp;
}