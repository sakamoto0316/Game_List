//=======================================
//
// �G���g���[�`�[������[entry_team.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "entry_team.h"
#include "texture.h"

//=======================================
// �}�N����`
//=======================================
#define TEAM_SIZE		(D3DXVECTOR3(120.0f, 60.0f, 0.0f))		// �`�[���̃T�C�Y
#define TEAM_TEXTURE	"data\\TEXTURE\\MatchChara.png"			// �`�[���̃e�N�X�`��
#define TEAM_PATTERN	(0.5f)									// �`�[���̃p�^�[����

//=========================
// �R���X�g���N�^
//=========================
CEntryTeam::CEntryTeam() : CObject2D(CObject::TYPE_NONE, CObject::PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
	m_type = CPlayer::TYPE_CAT;		// �`�[���̎��

	 m_fMove=0.1f;
	 m_nTimeCnt = 0;
}

//=========================
// �f�X�g���N�^
//=========================
CEntryTeam::~CEntryTeam()
{

}

//=========================
// ����������
//=========================
HRESULT CEntryTeam::Init(void)
{
	if (FAILED(CObject2D::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_type = CPlayer::TYPE_CAT;		// �`�[���̎��

	// ������Ԃ�
	return S_OK;
}

//=========================
// �I������
//=========================
void CEntryTeam::Uninit(void)
{
	// �I��
	CObject2D::Uninit();
}

//=========================
// �X�V����
//=========================
void CEntryTeam::Update(void)
{
	//UI�̊g��E�ړ�
	m_nTimeCnt++;
	if (m_nTimeCnt >= 60)
	{
		m_fMove *= -1.0f;
		m_nTimeCnt = 0;
	}

	CObject2D::SetPos(CObject2D::GetPos()+D3DXVECTOR3(0,m_fMove,0));
	CObject2D::SetSize(CObject2D::GetSize() + D3DXVECTOR3(m_fMove*-0.5f, m_fMove*-0.5f, 0));

	// ���_���̏�����
	SetVertex();

	// �e�N�X�`�����W�̐ݒ菈��
	SetVtxTextureAnim(TEAM_PATTERN, m_type);
}

//=========================
// �`�揈��
//=========================
void CEntryTeam::Draw(void)
{
	// �`�揈��
	CObject2D::Draw();
}

//=========================
// ���̐ݒ菈��
//=========================
void CEntryTeam::SetData(const D3DXVECTOR3& pos, const CPlayer::TYPE type)
{
	// �X�N���[���̐ݒ菈��
	
	SetPos(pos);				// �ʒu�ݒ�
	SetRot(NONE_D3DXVECTOR3);	// �����ݒ�
	SetSize(TEAM_SIZE);			// �T�C�Y�ݒ�
	SetLength();				// �����ݒ�
	SetAngle();					// �����ݒ�

	// �S�Ă̒l��ݒ肷��
	m_type = type;				// �`�[���̎��

	// �e�N�X�`���̓ǂݍ��ݏ���
	BindTexture(CManager::Get()->GetTexture()->Regist(TEAM_TEXTURE));

	// ���_���̏�����
	SetVertex();

	// �e�N�X�`�����W�̐ݒ菈��
	SetVtxTextureAnim(TEAM_PATTERN, m_type);
}

//=========================
// ��������
//=========================
CEntryTeam* CEntryTeam::Create(const D3DXVECTOR3& pos, const CPlayer::TYPE type)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CEntryTeam* pEntryTeam = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pEntryTeam == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pEntryTeam = new CEntryTeam;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pEntryTeam != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pEntryTeam->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pEntryTeam->SetData(pos, type);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �G���g���[�`�[���̃|�C���^��Ԃ�
	return pEntryTeam;
}

//=========================
// ��ނ̐ݒ菈��
//=========================
void CEntryTeam::SetType(const CPlayer::TYPE type)
{
	// ��ނ�ݒ肷��
	m_type = type;
}