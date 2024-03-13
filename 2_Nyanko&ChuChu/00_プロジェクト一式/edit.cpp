//===========================================
//
// �G�f�B�b�g�̃��C������[edit.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "edit.h"
#include "manager.h"
#include "debugproc.h"
#include "input.h"
#include "useful.h"

#include "obstacle_manager.h"
#include "block_manager.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define ADJUST_MOVE		(2.0f)		// ��������Ԃ̈ړ���
#define NORMAL_MOVE		(16.0f)		// �ʏ��Ԃ̈ړ���
#define ROTMOVE			(0.01f)		// �����̈ړ���

//==============================
// �R���X�g���N�^
//==============================
CEdit::CEdit() : CModel(CObject::TYPE_EDIT, CObject::PRIORITY_BG)
{
	// �S�Ă̒l���N���A����
	m_type = TYPE::TYPE_OBSTACLE;				// ���
	m_obstacleType = CObstacle::TYPE_HONEY;		// ��Q���̎��
	m_blockType = CBlock::TYPE_CARDBOARD;		// �u���b�N�̎��
	m_rotType = CBlock::ROTTYPE_FRONT;			// �����̎��
}

//==============================
// �f�X�g���N�^
//==============================
CEdit::~CEdit()
{

}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CEdit::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_type = TYPE::TYPE_OBSTACLE;			// ���
	m_obstacleType = CObstacle::TYPE_HONEY;	// ��Q���̎��
	m_blockType = CBlock::TYPE_CARDBOARD;	// �u���b�N�̎��
	m_rotType = CBlock::ROTTYPE_FRONT;		// �����̎��

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �j�Ђ̏I������
//========================================
void CEdit::Uninit(void)
{
	// �I������
	CModel::Uninit();
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CEdit::Update(void)
{
	// ��ނ��Ƃ̏���
	TypeProcess();

	// ��ނ̐ݒ菈�� 
	Type();

	// �ړ�����
	Move();

	// �c�ړ�����
	HeightMove();

	// �������ړ�����
	Adjust();

	// �c�������ړ�����
	HeightAdjust();

	// ���Z�b�g����
	Reset();

	// ��������
	Delete();

	// �ݒu����
	Set();

	// �f�o�b�O�\��
	CManager::Get()->GetDebugProc()->Print("�ʒu�F%f %f %f\n�����F%f %f %f\n�X�^�C���F%d\n"
		"LSHIFT�L�[�F�������L�[\nW/A/S/D�L�[�F�ړ�\n�E�L�[�F�E��]\n���L�[�F����]\n���L�[�F�����̏�����\n"
		"9�L�[�F����\n0�L�[�F�ݒu\nSPACE�L�[�F��ޕύX\nU/M�L�[�F�c�ړ�"
		, GetPos().x, GetPos().y, GetPos().z, GetRot().x, GetRot().y, GetRot().z, m_type);
}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CEdit::Draw(void)
{
	// �`�揈��
	CModel::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CEdit::SetData(void)
{
	// ���̐ݒ菈��
	SetPos(NONE_D3DXVECTOR3);				// �ʒu
	SetPosOld(NONE_D3DXVECTOR3);			// �O��̈ʒu
	SetRot(NONE_D3DXVECTOR3);				// ����
	SetScale(NONE_SCALE);					// �g�嗦
	SetFileData(CXFile::TYPE_HONEY);		// ���f���̏��ݒ�

	// �S�Ă̒l���N���A����
	m_type = TYPE::TYPE_OBSTACLE;			// ���
	m_obstacleType = CObstacle::TYPE_HONEY;	// ��Q���̎��
	m_blockType = CBlock::TYPE_CARDBOARD;	// �u���b�N�̎��
}

//=======================================
// ��������
//=======================================
CEdit* CEdit::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CEdit* pEdit = nullptr;	// �C���X�^���X�𐶐�

	if (pEdit == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �C���X�^���X�𐶐�
		pEdit = new CEdit;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pEdit != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pEdit->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pEdit->SetData();
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �j�Ђ̃|�C���^��Ԃ�
	return pEdit;
}

//=======================================
// ��ނ��Ƃ̏���
//=======================================
void CEdit::TypeProcess(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LCONTROL) == true)
	{ // ��CTRL�L�[�������Ă���ꍇ

		// ���̐�̏������s��Ȃ�
		return;
	}

	switch (m_type)
	{
	case CEdit::TYPE_OBSTACLE:		// ��Q��

		// ��Q���̏���
		ObstacleProcess();

		break;

	case CEdit::TYPE_BLOCK:			// �u���b�N

		// �u���b�N�̏���
		BlockProcess();

		break;

	default:						// ��L�ȊO

		// ��~
		assert(false);

		break;
	}
}

//=======================================
// �ړ�����
//=======================================
void CEdit::Move(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LSHIFT) == true ||
		CManager::Get()->GetInputKeyboard()->GetPress(DIK_LCONTROL) == true)
	{ // ��SHIFT�܂��́A��CTRL�L�[�������Ă����ꍇ

		// ���̐�̏������s��Ȃ�
		return;
	}

	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();		// �ʒu���擾����

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_W) == true)
	{ // W�L�[�������Ă����ꍇ

		// �ʒu�����Z����
		pos.z += NORMAL_MOVE;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_S) == true)
	{ // S�L�[�������Ă����ꍇ

		// �ʒu�����Z����
		pos.z -= NORMAL_MOVE;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_D) == true)
	{ // D�L�[�������Ă����ꍇ

		// �ʒu�����Z����
		pos.x += NORMAL_MOVE;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_A) == true)
	{ // A�L�[�������Ă����ꍇ

		// �ʒu�����Z����
		pos.x -= NORMAL_MOVE;
	}

	// �ʒu��ݒ肷��
	SetPos(pos);
}

//=======================================
// ����������
//=======================================
void CEdit::Adjust(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LCONTROL) == true)
	{ // ��CTRL�L�[�������Ă���ꍇ

		// ���̐�̏������s��Ȃ�
		return;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LSHIFT) == true)
	{ // ��SHIFT�L�[�������Ă����ꍇ

		// ���[�J���ϐ��錾
		D3DXVECTOR3 pos = GetPos();		// �ʒu���擾����

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_W) == true)
		{ // W�L�[���������ꍇ

			// �ʒu�����Z����
			pos.z += ADJUST_MOVE;
		}

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_S) == true)
		{ // S�L�[���������ꍇ

			// �ʒu�����Z����
			pos.z -= ADJUST_MOVE;
		}

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_D) == true)
		{ // D�L�[���������ꍇ

			// �ʒu�����Z����
			pos.x += ADJUST_MOVE;
		}

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_A) == true)
		{ // A�L�[���������ꍇ

			// �ʒu�����Z����
			pos.x -= ADJUST_MOVE;
		}

		// �ʒu��ݒ肷��
		SetPos(pos);
	}
}

//=======================================
// �c�ړ�����
//=======================================
void CEdit::HeightMove(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LSHIFT) == true ||
		CManager::Get()->GetInputKeyboard()->GetPress(DIK_LCONTROL) == true)
	{ // ��SHIFT�܂��́A��CTRL�L�[�������Ă����ꍇ

		// ���̐�̏������s��Ȃ�
		return;
	}

	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();		// �ʒu���擾����

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_U) == true)
	{ // U�L�[�������Ă����ꍇ

		// �ʒu�����Z����
		pos.y += NORMAL_MOVE;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_M) == true)
	{ // M�L�[�������Ă����ꍇ

		// �ʒu�����Z����
		pos.y -= NORMAL_MOVE;
	}

	// �ʒu��ݒ肷��
	SetPos(pos);
}

//=======================================
// �c����������
//=======================================
void CEdit::HeightAdjust(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LCONTROL) == true)
	{ // ��CTRL�L�[�������Ă���ꍇ

		// ���̐�̏������s��Ȃ�
		return;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LSHIFT) == true)
	{ // ��SHIFT�L�[�������Ă����ꍇ

		// ���[�J���ϐ��錾
		D3DXVECTOR3 pos = GetPos();		// �ʒu���擾����

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_U) == true)
		{ // W�L�[���������ꍇ

			// �ʒu�����Z����
			pos.y += ADJUST_MOVE;
		}

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_M) == true)
		{ // S�L�[���������ꍇ

			// �ʒu�����Z����
			pos.y -= ADJUST_MOVE;
		}

		// �ʒu��ݒ肷��
		SetPos(pos);
	}
}

//=======================================
// �����̈ړ�����
//=======================================
void CEdit::RotMove(void)
{
	// �������擾����
	D3DXVECTOR3 rot = GetRot();

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_RIGHT) == true)
	{ // �E�L�[�������Ă���ꍇ

		// ���������Z����
		rot.y -= ROTMOVE;
	}

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LEFT) == true)
	{ // ���L�[�������Ă���ꍇ

		// ���������Z����
		rot.y += ROTMOVE;
	}

	// �����̐��K��
	useful::RotNormalize(&rot.y);

	// ������ݒ肷��
	SetRot(rot);
}

//=======================================
// �u���b�N�̌����̈ړ�����
//=======================================
void CEdit::BlockRotMove(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_RIGHT) == true)
	{ // �E�L�[�������Ă���ꍇ

		// �����̎�ނ����Z����
		m_rotType = (CBlock::ROTTYPE)((m_rotType + 1) % CBlock::ROTTYPE_MAX);
	}

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_LEFT) == true)
	{ // ���L�[�������Ă���ꍇ

		// �����̎�ނ����Z����
		m_rotType = (CBlock::ROTTYPE)((m_rotType + (CBlock::ROTTYPE_MAX - 1)) % CBlock::ROTTYPE_MAX);
	}

	switch (m_rotType)
	{
	case CBlock::ROTTYPE_FRONT:

		// ������ݒ肷��
		SetRot(NONE_D3DXVECTOR3);

		break;

	case CBlock::ROTTYPE_RIGHT:

		// ������ݒ肷��
		SetRot(D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));

		break;

	case CBlock::ROTTYPE_BACK:

		// ������ݒ肷��
		SetRot(D3DXVECTOR3(0.0f, D3DX_PI, 0.0f));

		break;

	case CBlock::ROTTYPE_LEFT:

		// ������ݒ肷��
		SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));

		break;

	default:

		// ��~
		assert(false);

		break;
	}
}

//=======================================
// �ݒu����
//=======================================
void CEdit::Set(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LCONTROL) == true)
	{ // ��CTRL�L�[�������Ă���ꍇ

		// ���̐�̏������s��Ȃ�
		return;
	}

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true)
	{ // 0�L�[���������ꍇ

		switch (m_type)
		{
		case CEdit::TYPE_OBSTACLE:		// ��Q��

			// ��Q���̐�������
			CObstacle::Create(GetPos(), GetRot(), m_obstacleType);

			break;

		case CEdit::TYPE_BLOCK:

			// �u���b�N�̐�������
			CBlock::Create(GetPos(), m_rotType, m_blockType);

			break;

		default:						// ���

			// ��~
			assert(false);

			break;
		}
	}
}

//=======================================
// ���Z�b�g����
//=======================================
void CEdit::Reset(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_DOWN) == true)
	{ // ���L�[���������ꍇ

		// �����𐳋K������
		SetRot(NONE_D3DXVECTOR3);
	}
}

//=======================================
// ��Q���̐ݒ菈��
//=======================================
void CEdit::ObstacleProcess(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_1) == true)
	{ // 1�L�[���������ꍇ

		// ��Q���̎�ނ�ݒ肷��
		m_obstacleType = (CObstacle::TYPE)((m_obstacleType + 1) % CObstacle::TYPE_MAX);
	}
	else if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_2) == true)
	{ // 2�L�[���������ꍇ

		// ��Q���̎�ނ�ݒ肷��
		m_obstacleType = (CObstacle::TYPE)((m_obstacleType + (CObstacle::TYPE_MAX - 1)) % CObstacle::TYPE_MAX);
	}

	if (m_obstacleType >= CObstacle::TYPE_MAX)
	{ // �^�C�v�ɂ���ꍇ

		// ��~
		assert(false);
	}
	else
	{ // ��L�ȊO

		// ��Q���̎�ނ�ݒ肷��
		SetFileData((CXFile::TYPE)(INIT_OBSTACLE + m_obstacleType));
	}

	// �����̈ړ�����
	RotMove();

	// �f�o�b�O�\��
	CManager::Get()->GetDebugProc()->Print("1/2�L�[�F��Q���̎�ޕύX\n");
}

//=======================================
// �u���b�N�̏���
//=======================================
void CEdit::BlockProcess(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_1) == true)
	{ // 1�L�[���������ꍇ

		// �u���b�N�̎�ނ�ݒ肷��
		m_blockType = (CBlock::TYPE)((m_blockType + 1) % CBlock::TYPE_MAX);
	}
	else if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_2) == true)
	{ // 2�L�[���������ꍇ

		// �u���b�N�̎�ނ�ݒ肷��
		m_blockType = (CBlock::TYPE)((m_blockType + (CBlock::TYPE_MAX - 1)) % CBlock::TYPE_MAX);
	}

	if (m_blockType >= CBlock::TYPE_MAX)
	{ // �^�C�v�ɂ���ꍇ

		// ��~
		assert(false);
	}
	else
	{ // ��L�ȊO

		// �u���b�N�̎�ނ�ݒ肷��
		SetFileData((CXFile::TYPE)(INIT_BLOCK + m_blockType));
	}

	// �u���b�N�̌����̈ړ�����
	BlockRotMove();

	// �f�o�b�O�\��
	CManager::Get()->GetDebugProc()->Print("1/2�L�[�F�u���b�N�̎�ޕύX\n");
}

//=======================================
// ��ނ̕ύX����
//=======================================
void CEdit::Type(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LCONTROL) == true)
	{ // ��CTRL�L�[�������Ă���ꍇ

		// ���̐�̏������s��Ȃ�
		return;
	}

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_SPACE) == true)
	{ // SPACE�L�[���������ꍇ

		// ��ނ�ύX����
		m_type = (CEdit::TYPE)((m_type + 1) % CEdit::TYPE_MAX);
	}
}

//=======================================
// ��������
//=======================================
void CEdit::Delete(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_LCONTROL) == true)
	{ // ��CTRL�L�[�������Ă���ꍇ

		// ���̐�̏������s��Ȃ�
		return;
	}

	switch (m_type)
	{
	case CEdit::TYPE_OBSTACLE:		// ��Q��

		// ��Q���̏�������
		DeleteObstacle();

		break;

	case CEdit::TYPE_BLOCK:			// �u���b�N

		// �u���b�N�̏�������
		DeleteBlock();

		break;

	default:						// ���

		// ��~
		assert(false);

		break;
	}
}

//=======================================
// ��Q���̏�������
//=======================================
void CEdit::DeleteObstacle(void)
{
	// ���[�J���ϐ��錾
	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();		// �擪�̏�Q�����擾����
	CObstacle* pObstacleNext = nullptr;								// ���̏�Q��

	while (pObstacle != nullptr)
	{ // ��Q���� NULL ����Ȃ��ꍇ

		// ���̏�Q����ݒ肷��
		pObstacleNext = pObstacle->GetNext();

		if (useful::RectangleCollisionXY(GetPos(), pObstacle->GetPos(), GetFileData().vtxMax, pObstacle->GetFileData().vtxMax, GetFileData().vtxMin, pObstacle->GetFileData().vtxMin) == true &&
			useful::RectangleCollisionXZ(GetPos(), pObstacle->GetPos(), GetFileData().vtxMax, pObstacle->GetFileData().vtxMax, GetFileData().vtxMin, pObstacle->GetFileData().vtxMin) == true &&
			useful::RectangleCollisionYZ(GetPos(), pObstacle->GetPos(), GetFileData().vtxMax, pObstacle->GetFileData().vtxMax, GetFileData().vtxMin, pObstacle->GetFileData().vtxMin) == true &&
			CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_BACKSPACE) == true)
		{ // �I�u�W�F�N�g�̒��ɓ����Ă���ꍇ

			// �I������
			pObstacle->Uninit();
		}

		// ���̏�Q���̃|�C���^��������
		pObstacle = pObstacleNext;
	}
}

//=======================================
// �u���b�N�̏�������
//=======================================
void CEdit::DeleteBlock(void)
{
	// ���[�J���ϐ��錾
	CBlock* pBlock = CBlockManager::Get()->GetTop();		// �擪�̃u���b�N���擾����
	CBlock* pBlockNext = nullptr;							// ���̃u���b�N

	while (pBlock != nullptr)
	{ // �u���b�N�� NULL ����Ȃ��ꍇ

		// ���̃u���b�N��ݒ肷��
		pBlockNext = pBlock->GetNext();

		if (useful::RectangleCollisionXY(GetPos(), pBlock->GetPos(), GetFileData().vtxMax, pBlock->GetFileData().vtxMax, GetFileData().vtxMin, pBlock->GetFileData().vtxMin) == true &&
			useful::RectangleCollisionXZ(GetPos(), pBlock->GetPos(), GetFileData().vtxMax, pBlock->GetFileData().vtxMax, GetFileData().vtxMin, pBlock->GetFileData().vtxMin) == true &&
			useful::RectangleCollisionYZ(GetPos(), pBlock->GetPos(), GetFileData().vtxMax, pBlock->GetFileData().vtxMax, GetFileData().vtxMin, pBlock->GetFileData().vtxMin) == true &&
			CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_BACKSPACE) == true)
		{ // �I�u�W�F�N�g�̒��ɓ����Ă���ꍇ

			// �I������
			pBlock->Uninit();
		}

		// ���̃u���b�N�̃|�C���^��������
		pBlock = pBlockNext;
	}
}