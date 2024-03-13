//===========================================
//
// �������C������[note.cpp]
// Author ��{�ėB
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "note.h"
#include "useful.h"
#include "speaker.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define NOTE_CYCLE_SPEED	(0.05f)			// ��鑬�x
#define NOTE_UD_HEIGHT		(100.0f)		// �㉺�ړ��̕�

//==============================
// �R���X�g���N�^
//==============================
CNote::CNote() : CModel(CObject::TYPE_NONE, CObject::PRIORITY_BLOCK)
{
	m_move = NONE_D3DXVECTOR3;
	m_nLife = 10;
	m_nRandHeight = 0;
	m_StartPosY = 0.0f;		// �����ʒu�̍���
	m_nIndex = -1;			// �g�p�ԍ�
	m_Main = nullptr;		// �����̎����g�p���Ă���I�u�W�F�N�g
}

//==============================
// �f�X�g���N�^
//==============================
CNote::~CNote()
{

}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CNote::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // �����������Ɏ��s�����ꍇ

	  // ���s��Ԃ�
		return E_FAIL;
	}

	m_move = NONE_D3DXVECTOR3;
	m_nLife = 10;
	m_nRandHeight = 0;
	m_StartPosY = 0.0f;		// �����ʒu�̍���
	m_nIndex = -1;			// �g�p�ԍ�
	m_Main = nullptr;		// �����̎����g�p���Ă���I�u�W�F�N�g

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �j�Ђ̏I������
//========================================
void CNote::Uninit(void)
{
	//�{�̂ɂ��鎩�g�̃|�C���^�폜����
	m_Main->NULLNote(m_nIndex);
	m_Main->MySetIdx(m_nIndex);

	// �I������
	CModel::Uninit();
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CNote::Update(void)
{
	// �ʒu�ƌ��������擾����
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	// �ʒu�����Z����
	m_nLife--;
	rot.y += NOTE_CYCLE_SPEED;
	pos.y = m_StartPosY + sinf(m_nLife * 0.1f) * NOTE_UD_HEIGHT;

	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}

	// �ʒu�X�V
	pos += m_move;

	// �ʒu�ƌ�����ݒ肷��
	SetPos(pos);
	SetRot(rot);
}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CNote::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CNote::SetData(const D3DXVECTOR3& pos)
{
	// ���̐ݒ菈��
	SetPos(pos);								// �ʒu
	SetPosOld(pos);								// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);					// ����
	SetScale(NONE_SCALE);						// �g�嗦

	m_nRandHeight = rand() % 3;
	switch (m_nRandHeight)
	{
	case 0:
		SetFileData(CXFile::TYPE_RED_NOTE4);			// ���f�����
		break;
	case 1:
		SetFileData(CXFile::TYPE_RED_NOTE8);			// ���f�����
		break;
	case 2:
		SetFileData(CXFile::TYPE_RED_NOTE16);			// ���f�����
		break;
	}
	m_StartPosY = pos.y;
}

//=======================================
// ��������
//=======================================
CNote* CNote::Create(const D3DXVECTOR3& pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CNote* pTarai = nullptr;	// �C���X�^���X�𐶐�

	if (pTarai == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

	  // �C���X�^���X�𐶐�
		pTarai = new CNote;
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
		pTarai->SetData(pos);
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