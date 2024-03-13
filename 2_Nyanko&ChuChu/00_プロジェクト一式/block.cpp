//===========================================
//
// �n�`�u���b�N�̃��C������[block.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "block.h"
#include "block_manager.h"
#include "manager.h"
#include "renderer.h"
#include "useful.h"
#include "debugproc.h"

// �}�N����`
#define BLOCK_HEIGHT_MAX		(400.0f)		// �u���b�N�̍����̍ő�l
#define BLOCK_HEIGHT_CORRECT	(99999.0f)		// �u���b�N�̕␳��̍���
#define SWAY_ANGLE				(0.020f * D3DX_PI)			// �h���p�x
#define SWAY_ADD				(0.2f)			// �h��鑁��
#define SWAY_TIME				(30)			// �h�炷����

//==============================
// �R���X�g���N�^
//==============================
CBlock::CBlock() : CModel(CObject::TYPE_BLOCK, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	m_collision = COLLISION_SQUARE;	// �����蔻��̎��
	m_rotType = ROTTYPE_FRONT;		// �����̎��
	m_type = TYPE_CARDBOARD;		// ���
	m_state = STATE_NONE;			// ���
	m_vtxMax = NONE_D3DXVECTOR3;	// �ő�l
	m_vtxMin = NONE_D3DXVECTOR3;	// �ŏ��l
	m_pPrev = nullptr;				// �O�̂ւ̃|�C���^
	m_pNext = nullptr;				// ���̂ւ̃|�C���^
	//m_bOnRat = false;				// �l�Y�~������Ă��邩
	//m_nPlayerIdx = -1;				// �v���C���[�ԍ�
	m_nAngleSwitch = 0;				// �p�x��+-�؂�ւ�
	m_nSwayCount = 0;				// �h�炷�b��

	if (CBlockManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// �}�l�[�W���[�ւ̓o�^����
		CBlockManager::Get()->Regist(this);
	}
}

//==============================
// �f�X�g���N�^
//==============================
CBlock::~CBlock()
{

}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
void CBlock::SetPrev(CBlock* pPrev)
{
	// �O�̃|�C���^��ݒ肷��
	m_pPrev = pPrev;
}

//============================
// ��̃|�C���^�̐ݒ菈��
//============================
void CBlock::SetNext(CBlock* pNext)
{
	// ���̃|�C���^��ݒ肷��
	m_pNext = pNext;
}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
CBlock* CBlock::GetPrev(void) const
{
	// �O�̃|�C���^��Ԃ�
	return m_pPrev;
}

//============================
// ���̃|�C���^�̐ݒ菈��
//============================
CBlock* CBlock::GetNext(void) const
{
	// ���̃|�C���^��Ԃ�
	return m_pNext;
}

//==============================
// ����������
//==============================
HRESULT CBlock::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_collision = COLLISION_SQUARE;	// �����蔻��̎��
	m_rotType = ROTTYPE_FRONT;		// �����̎��
	m_type = TYPE_CARDBOARD;		// ���
	m_state = STATE_NONE;			// ���
	m_vtxMax = NONE_D3DXVECTOR3;	// �ő�l
	m_vtxMin = NONE_D3DXVECTOR3;	// �ŏ��l
	//m_bOnRat = false;				// �l�Y�~������Ă��邩
	//m_nPlayerIdx = -1;				// �v���C���[�ԍ�
	m_nAngleSwitch = 1;				// �p�x��+-�؂�ւ�
	m_nSwayCount = 0;				// �h�炷�b��

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �I������
//========================================
void CBlock::Uninit(void)
{
	// �I������
	CModel::Uninit();

	if (CBlockManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// ���X�g�\���̈�����������
		CBlockManager::Get()->Pull(this);
	}

	// ���X�g�\���֌W�̃|�C���^�� NULL �ɂ���
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//========================================
// �I������
//========================================
void CBlock::UninitAll(void)
{
	// ���[�J���ϐ��錾
	CBlock* pObj = nullptr;		// ���݂̃I�u�W�F�N�g�̃|�C���^

	for (int nCnt = 0; nCnt < CObject::PRIORITY_MAX; nCnt++)
	{
		 pObj->GetTop(((CObject::PRIORITY)nCnt));
	}
	Uninit();
}

//=====================================
// �X�V����
//=====================================
void CBlock::Update(void)
{
	// ��ԍX�V����
	UpdateState();
}

//=====================================
// �`�揈��
//=====================================
void CBlock::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CBlock::SetData(const D3DXVECTOR3& pos, const ROTTYPE rotType, const TYPE type)
{
	// ���̐ݒ菈��
	SetPos(pos);							// �ʒu
	SetPosOld(pos);							// �O��̈ʒu
	SetScale(NONE_SCALE);					// �g�嗦

	// �S�Ă̒l������������
	m_type = type;			// ���
	m_rotType = rotType;	// �����̎��

	switch (m_rotType)
	{
	case CBlock::ROTTYPE_FRONT:		// �O����

		// ������ݒ肷��
		SetRot(NONE_D3DXVECTOR3);

		break;

	case CBlock::ROTTYPE_RIGHT:		// �E����

		// ������ݒ肷��
		SetRot(D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));

		break;

	case CBlock::ROTTYPE_BACK:		// ������

		// ������ݒ肷��
		SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

		break;

	case CBlock::ROTTYPE_LEFT:		// ������

		// ������ݒ肷��
		SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	if (m_type >= TYPE_MAX)
	{ // �^�C�v�ɂ���ꍇ

		// ��~
		assert(false);
	}
	else
	{ // ��L�ȊO

		// �u���b�N�̎�ނ�ݒ肷��
		SetFileData((CXFile::TYPE)(INIT_BLOCK + m_type));
	}

	if (m_type == TYPE_PENHOLDER ||
		m_type == TYPE_RUBBISH ||
		m_type == TYPE_HEADPHONE)
	{ // ���̐��l�̏ꍇ

		// �~�̓����蔻���ݒ肷��
		m_collision = COLLISION_CIRCLE;
	}
	else
	{ // ��L�ȊO

		// �l�p�̓����蔻���ݒ肷��
		m_collision = COLLISION_SQUARE;

		// �����ɂ��ő�l�E�ŏ��l�̐ݒ菈��
		CollisionSetting();
	}
}

//=====================================
// ��������
//=====================================
CBlock* CBlock::Create(const D3DXVECTOR3& pos, const ROTTYPE rotType, const TYPE type)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CBlock* pBlock = nullptr;	// �C���X�^���X�𐶐�

	if (pBlock == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �{�𐶐�����
		pBlock = new CBlock;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pBlock != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pBlock->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pBlock->SetData(pos, rotType, type);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �u���b�N�̃|�C���^��Ԃ�
	return pBlock;
}

//=====================================
// �����蔻��̎�ނ̐ݒ菈��
//=====================================
void CBlock::SetCollision(const COLLISION collsion)
{
	// �����蔻���ݒ肷��
	m_collision = collsion;
}

//=====================================
// �����蔻��̎�ނ̎擾����
//=====================================
CBlock::COLLISION CBlock::GetCollision(void) const
{
	// �����蔻���Ԃ�
	return m_collision;
}

//=====================================
// �����̎�ނ̎擾����
//=====================================
CBlock::ROTTYPE CBlock::GetRotType(void) const
{
	// �����̎�ނ�ݒ肷��
	return m_rotType;
}

//=====================================
// ��ނ̎擾����
//=====================================
CBlock::TYPE CBlock::GetType(void) const
{
	// ��ނ�Ԃ�
	return m_type;
}

//=====================================
// �ő�l�̎擾����
//=====================================
D3DXVECTOR3 CBlock::GetVtxMax(void) const
{
	// �ő�l��Ԃ�
	return m_vtxMax;
}

//=====================================
// �ŏ��l�̎擾����
//=====================================
D3DXVECTOR3 CBlock::GetVtxMin(void) const
{
	// �ŏ��l��Ԃ�
	return m_vtxMin;
}

//=====================================
// �l�Y�~�̏���Ă���󋵐ݒ�
//=====================================
//void CBlock::SetOnRat(const bool bOnRat, const int nPlayerIdx)
//{
//	// �l�Y�~�̏���Ă���󋵐ݒ�
//	m_bOnRat = bOnRat;
//	m_nPlayerIdx = nPlayerIdx;
//}

//=====================================
// �l�Y�~�̏���Ă���󋵎擾
//=====================================
//bool CBlock::GetOnRat(void) const
//{
//	// �l�Y�~�̏���Ă���󋵂�Ԃ�
//	return m_bOnRat;
//}

//=====================================
// ��Ԑݒ�
//=====================================
void CBlock::SetState(STATE state)
{
	// ��Ԑݒ�
	m_state = state;
}

//=====================================
// ��Ԃ̎擾����
//=====================================
CBlock::STATE CBlock::GetState(void) const
{
	// ��Ԃ�Ԃ�
	return m_state;
}

//=====================================
// �����ɂ��ő�l�E�ŏ��l�̐ݒ菈��
//=====================================
void CBlock::CollisionSetting(void)
{
	// �ŏ��l�ƍő�l���擾����
	D3DXVECTOR3 vtxMin = GetFileData().vtxMin;
	D3DXVECTOR3 vtxMax = GetFileData().vtxMax;

	switch (m_rotType)
	{
	case CBlock::ROTTYPE_FRONT:		// ����

		// �ő�l�ƍŏ��l��ݒ肷��
		m_vtxMax = vtxMax;			// �ő�l
		m_vtxMin = vtxMin;			// �ŏ��l

		break;

	case CBlock::ROTTYPE_RIGHT:		// �E

		// �ő�l�ƍŏ��l��ݒ肷��
		m_vtxMax = D3DXVECTOR3(-vtxMin.z, vtxMax.y, vtxMax.x);
		m_vtxMin = D3DXVECTOR3(-vtxMax.z, vtxMin.y, vtxMin.x);

		break;

	case CBlock::ROTTYPE_BACK:		// ���

		// �ő�l�ƍŏ��l��ݒ肷��
		m_vtxMax = D3DXVECTOR3(-vtxMin.x, vtxMax.y, -vtxMin.z);
		m_vtxMin = D3DXVECTOR3(-vtxMax.x, vtxMin.y, -vtxMax.z);

		break;

	case CBlock::ROTTYPE_LEFT:		// ��

		// �ő�l�ƍŏ��l��ݒ肷��
		m_vtxMax = D3DXVECTOR3(vtxMax.z, vtxMax.y, -vtxMin.x);
		m_vtxMin = D3DXVECTOR3(vtxMin.z, vtxMin.y, -vtxMax.x);

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	if (m_vtxMax.y >= BLOCK_HEIGHT_MAX)
	{ // �����������ꍇ

		// �l�Y�~�����Ȃ�����
		m_vtxMax.y = BLOCK_HEIGHT_CORRECT;
	}
}

//=====================================
// ��ԍX�V����
//=====================================
void CBlock::UpdateState(void)
{
	switch (m_state)
	{
	case CBlock::STATE_NONE:		// �������Ȃ�

		break;

	case CBlock::STATE_SWAY:		// �h���

		// �h�炷����
		Sway();

		break;

	default:

		// ��~����
		assert(false);

		break;
	}
}

//=====================================
// �h�炷����
//=====================================
void CBlock::Sway(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 rot = GetRot();		// �����擾
	float fAngle = 0.0f;	// ���Z����p�x

	if (rot.z > SWAY_ANGLE || rot.z < -SWAY_ANGLE)
	{ // �p�x���ڕW�͈̔͊O��������

		m_nAngleSwitch *= -1;		// �p�x�ɉ��Z����+-�ύX
	}

	// ���Z����p�x
	fAngle += (SWAY_ANGLE * SWAY_ADD) * m_nAngleSwitch;

	// �p�x���Z
	rot.z += fAngle;

	if (m_nSwayCount >= SWAY_TIME)
	{ // ��莞�Ԍo������

		if (rot.z <= 0.01 && rot.z >= -0.01f)
		{ // �܂������܂ł̌덷�͈̔͂ɂȂ�����

			m_state = STATE_NONE;		// �������Ȃ���Ԃɂ���
			m_nSwayCount = 0;			// �J�E���^�[������
			rot.z = 0.0f;				// �܂������ɂ���
		}
	}
	else
	{
		m_nSwayCount++;					// �J�E���^�[���Z
	}

	// �����̐ݒ�
	SetRot(rot);
}