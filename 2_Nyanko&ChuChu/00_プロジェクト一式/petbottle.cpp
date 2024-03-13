//===========================================
//
// �y�b�g�{�g���̃��C������[petbottle.cpp]
// Author ���˕�
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "useful.h"
#include "petbottle.h"

#include "objectElevation.h"
#include "elevation_manager.h"
#include "block.h"
#include "block_manager.h"
#include "map.h"
#include "collision.h"
#include "sound.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define STAND_ROT	(D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f))		// ������Ԃ̌���
#define GRAVITY		(0.5f)			// �d��
#define SPEED		(13.0f)			// �]���鑬�x
#define ROT_MOVE	(0.01f)			// �����̈ړ���

//==============================
// �R���X�g���N�^
//==============================
CPetbottle::CPetbottle() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	m_move = NONE_D3DXVECTOR3;			// �ړ���
	m_posPlayer = NONE_D3DXVECTOR3;		// �Ԃ������v���C���[�̈ʒu
	m_vtxMax = NONE_D3DXVECTOR3;		// �ő�l
	m_vtxMin = NONE_D3DXVECTOR3;		// �ŏ��l
	m_state = STATE_STAND;				// ���
	m_fAlpha = 1.0f;					// �����x
	SetRatUse(false);
	SetCatUse(true);
}

//==============================
// �f�X�g���N�^
//==============================
CPetbottle::~CPetbottle()
{

}

//==============================
// �y�b�g�{�g���̏���������
//==============================
HRESULT CPetbottle::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_move = NONE_D3DXVECTOR3;			// �ړ���
	m_posPlayer = NONE_D3DXVECTOR3;		// �Ԃ������v���C���[�̈ʒu
	m_vtxMax = NONE_D3DXVECTOR3;		// �ő�l
	m_vtxMin = NONE_D3DXVECTOR3;		// �ŏ��l
	m_state = STATE_STAND;				// ���
	m_fAlpha = 1.0f;					// �����x

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �y�b�g�{�g���̏I������
//========================================
void CPetbottle::Uninit(void)
{
	// �I������
	CObstacle::Uninit();
}

//=====================================
// �y�b�g�{�g���̍X�V����
//=====================================
void CPetbottle::Update(void)
{
	switch (m_state)
	{
	case CPetbottle::STATE_STAND:		// �������

		// ������ݒ肷��
		SetRot(STAND_ROT);

		break;

	case CPetbottle::STATE_COLLAPSE:	// �|����

		// ��]����
		Cycle();

		// �d�͏���
		Gravity();

		if (Block() == true ||
			MagicWall() == true)
		{ // �u���b�N�������̒[�ɓ��������ꍇ

			// �ޏ��Ԃɂ���
			m_state = STATE_LEAVE;

			// ���̐�̏������s��Ȃ�
			return;
		}

		break;

	case STATE_LEAVE:					// �ޏ���

		// �����x�����Z����
		m_fAlpha -= 0.01f;

		if (m_fAlpha <= 0.0f)
		{ // �����x�� 0.0f �ȉ��̏ꍇ

			// �y�b�g�{�g�����]���鉹���~�߂�
			CManager::Get()->GetSound()->Stop(CSound::SOUND_LABEL_SE_PETBOTTLES_ROLL);

			// �I������
			Uninit();

			// ���̐�̏������s��Ȃ�
			return;
		}

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	// �N���n�ʂƂ̓����蔻��
	Elevation();
}

//=====================================
// �y�b�g�{�g���̕`�揈��
//=====================================
void CPetbottle::Draw(void)
{
	switch (m_state)
	{
	case CPetbottle::STATE_LEAVE:

		// �`�揈��
		CObstacle::Draw(m_fAlpha);

		break;

	default:

		// �`�揈��
		CObstacle::Draw(1.0f);

		break;
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CPetbottle::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos,rot, type);

	// ������ݒ肷��
	SetRot(STAND_ROT);

	// �S�Ă̒l���N���A����
	m_move = NONE_D3DXVECTOR3;			// �ړ���
	m_posPlayer = NONE_D3DXVECTOR3;		// �Ԃ������v���C���[�̈ʒu
	m_vtxMax = NONE_D3DXVECTOR3;		// �ő�l
	m_vtxMin = NONE_D3DXVECTOR3;		// �ŏ��l
	m_state = STATE_STAND;				// ���
	m_fAlpha = 1.0f;					// �����x
}

//=====================================
// �����蔻�菈��
//=====================================
bool CPetbottle::Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// �ʒu���擾����
	D3DXVECTOR3 pos = pPlayer->GetPos();
	D3DXVECTOR3 move = pPlayer->GetMove();

	if (m_state == STATE_STAND)
	{ // ������Ԃ̏ꍇ

		if (pos.y <= GetPos().y + GetFileData().vtxMax.z &&
			pos.y + collSize.y >= GetPos().y + GetFileData().vtxMin.z)
		{ // �y�b�g�{�g���ƏՓ˂����ꍇ

			// �~���̓����蔻�菈��
			useful::CylinderCollision(&pos, GetPos(), GetFileData().vtxMax.x + collSize.x);
		}
	}

	// �ʒu�ƈړ��ʂ�K�p����
	pPlayer->SetPos(pos);
	pPlayer->SetMove(move);

	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CPetbottle::Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// �ő�l�ƍŏ��l��ݒ肷��
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(collSize.x, collSize.y, collSize.z);
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);

	if (m_state == STATE_COLLAPSE &&
		pPlayer->GetType() == CPlayer::TYPE_RAT &&
		useful::RectangleCollisionXY(GetPos(), pPlayer->GetPos(), m_vtxMax, vtxMax, m_vtxMin, vtxMin) == true &&
		useful::RectangleCollisionXZ(GetPos(), pPlayer->GetPos(), m_vtxMax, vtxMax, m_vtxMin, vtxMin) == true &&
		useful::RectangleCollisionYZ(GetPos(), pPlayer->GetPos(), m_vtxMax, vtxMax, m_vtxMin, vtxMin) == true)
	{ // �|���Ԃ��A�����蔻�肪 true �̏ꍇ

		// true ��Ԃ�
		return true;
	}

	// false ��Ԃ�
	return false;
}

//=====================================
// �~�̃q�b�g����
//=====================================
bool CPetbottle::HitCircle(CPlayer* pPlayer, const float Radius)
{
	if (GetAction() == false &&
		useful::CircleCollisionXZ(pPlayer->GetPos(), GetPos(), Radius, GetFileData().fRadius) == true)
	{ // �y�b�g�{�g���ɏՓ˂����ꍇ

		// �Ԃ������v���C���[�̈ʒu��ݒ肷��
		m_posPlayer = pPlayer->GetPos();

		// true ��Ԃ�
		return true;
	}

	// false ��Ԃ�
	return false;
}

//=====================================
// �M�~�b�N�N������
//=====================================
void CPetbottle::Action(void)
{
	// �ʒu�ƌ����ƕ�����錾����
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	float fAngle = 0.0f;

	// �|���Ԃɂ���
	m_state = STATE_COLLAPSE;
	SetFileData(CXFile::TYPE_RED_PETBOTTLE);

	// �A�N�V�����󋵂� true �ɂ���
	SetAction(true);

	// �y�b�g�{�g�����|��鉹��炷
	CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_PETBOTTLES_FALL_DOWN);

	// ������ݒ肷��
	fAngle = atan2f((pos.x - m_posPlayer.x), (pos.z - m_posPlayer.z));

	// ������ݒ肷��
	rot.x = 0.0f;
	rot.z = 0.0f;

	if (fAngle >= D3DX_PI * -0.25f &&
		fAngle <= D3DX_PI * 0.25f)
	{ // ��������O����̏ꍇ

		// ������ݒ肷��
		rot.y = D3DX_PI * 0.5f;
	}
	else if (fAngle >= D3DX_PI * 0.25f &&
		fAngle <= D3DX_PI * 0.75f)
	{ // ������������̏ꍇ

		// ������ݒ肷��
		rot.y = D3DX_PI;
	}
	else if (fAngle >= D3DX_PI * -0.75f &&
		fAngle <= D3DX_PI * -0.25f)
	{ // �������E����̏ꍇ

		// ������ݒ肷��
		rot.y = 0.0f;
	}
	else
	{ // ��L�ȊO(������������̏ꍇ)

		// ������ݒ肷��
		rot.y = D3DX_PI * -0.5f;
	}

	// ������K�p����
	SetRot(rot);

	// �����蔻��̐ݒ菈��
	CollsionSetting();

	// �y�b�g�{�g�����]���鉹��炷
	CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_PETBOTTLES_ROLL);
}

//=====================================
// �u���b�N�Ƃ̓����蔻��
//=====================================
bool CPetbottle::Block(void)
{
	D3DXVECTOR3 pos = GetPos();			// �ʒu���擾����
	CBlock* pBlock = CBlockManager::Get()->GetTop();	// �u���b�N�̐擪���擾����

	while (pBlock != nullptr)
	{ // �u���b�N�� NULL ����Ȃ�������

		// �Z�ʑ̂̓����蔻��
		if (collision::HexahedronCollision
		(
			&pos,
			pBlock->GetPos(),
			GetPosOld(),
			pBlock->GetPosOld(),
			m_vtxMin,
			pBlock->GetVtxMin(),
			m_vtxMax,
			pBlock->GetVtxMax()
		) == true)
		{
			// true ��Ԃ�
			return true;
		}

		// ���̃u���b�N���擾����
		pBlock = pBlock->GetNext();
	}

	// false ��Ԃ�
	return false;
}

//=====================================
// ��]����
//=====================================
void CPetbottle::Cycle(void)
{
	// �����擾����
	D3DXVECTOR3 pos = GetPos();		// �ʒu
	D3DXVECTOR3 rot = GetRot();		// ����

	// �ړ��ʂ�ݒ肷��
	m_move.x = sinf(rot.y - (D3DX_PI * 0.5f)) * SPEED;
	m_move.z = cosf(rot.y - (D3DX_PI * 0.5f)) * SPEED;

	// ���������Z����
	rot.z += ROT_MOVE;

	// �ʒu���ړ�����
	pos.x += m_move.x;
	pos.z += m_move.z;

	// ����K�p����
	SetPos(pos);		// �ʒu
	SetRot(rot);		// ����
}

//=====================================
// �d�͏���
//=====================================
void CPetbottle::Gravity(void)
{
	// �ʒu���擾����
	D3DXVECTOR3 pos = GetPos();

	// �d�͏���
	useful::Gravity(&m_move.y, &pos.y, GRAVITY);
	
	// �ʒu��ݒ肷��
	SetPos(pos);
}

//=====================================
// �N���n�ʂ̓����蔻��
//=====================================
void CPetbottle::Elevation(void)
{
	// ���[�J���ϐ��錾
	CElevation* pMesh = CElevationManager::Get()->GetTop();		// �N���̐擪�̃I�u�W�F�N�g���擾����
	D3DXVECTOR3 pos = D3DXVECTOR3(GetPos().x, GetPos().y, GetPos().z);		// �ʒu���擾����
	float fHeight = 0.0f;					// ����

	while (pMesh != nullptr)
	{ // �n�ʂ̏�񂪂�������

		// �����蔻������
		fHeight = pMesh->ElevationCollision(pos);

		if (pos.y + GetFileData().vtxMin.y <= fHeight)
		{ // �����蔻��̈ʒu�����������ꍇ

			// ������ݒ肷��
			pos.y = fHeight - GetFileData().vtxMin.y;

			// �d�͂�����������
			m_move.y = 0.0f;
		}

		// ���̃|�C���^���擾����
		pMesh = pMesh->GetNext();
	}

	// �ʒu���X�V����
	SetPos(pos);
}

//=====================================
// ���@�̕Ǐ���
//=====================================
bool CPetbottle::MagicWall(void)
{
	// �ʒu���擾����
	D3DXVECTOR3 pos = GetPos();

	if (pos.x + m_vtxMin.x <= -MAP_SIZE.x)
	{ // �ʒu��������o�����ȏꍇ

		// true ��Ԃ�
		return true;
	}

	if (pos.x + m_vtxMax.x >= MAP_SIZE.x)
	{ // �ʒu���E����o�����ȏꍇ

		// true ��Ԃ�
		return true;
	}

	if (pos.z + m_vtxMin.z <= -MAP_SIZE.z)
	{ // �ʒu���E����o�����ȏꍇ

		// true ��Ԃ�
		return true;
	}

	if (pos.z + m_vtxMax.z >= MAP_SIZE.z)
	{ // �ʒu���E����o�����ȏꍇ

		// true ��Ԃ�
		return true;
	}

	// false ��Ԃ�
	return false;
}

//=====================================
// �����蔻��̐ݒ菈��
//=====================================
void CPetbottle::CollsionSetting(void)
{
	// �����ƍő�l�ƍŏ��l���擾����
	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 vtxMin = GetFileData().vtxMin;
	D3DXVECTOR3 vtxMax = GetFileData().vtxMax;

	if (rot.y >= D3DX_PI * -0.25f &&
		rot.y <= D3DX_PI * 0.25f)
	{ // ��������O����̏ꍇ

		// �ő�l�ƍŏ��l��ݒ肷��
		m_vtxMax = vtxMax;
		m_vtxMin = vtxMin;
	}
	else if (rot.y >= D3DX_PI * 0.25f &&
		rot.y <= D3DX_PI * 0.75f)
	{ // ������������̏ꍇ

		// �ő�l�ƍŏ��l��ݒ肷��
		m_vtxMax = D3DXVECTOR3(vtxMax.z, vtxMax.y, -vtxMin.x);
		m_vtxMin = D3DXVECTOR3(vtxMin.z, vtxMin.y, -vtxMax.x);
	}
	else if (rot.y >= D3DX_PI * -0.75f &&
		rot.y <= D3DX_PI * -0.25f)
	{ // �������E����̏ꍇ

		// �ő�l�ƍŏ��l��ݒ肷��
		m_vtxMax = D3DXVECTOR3(-vtxMin.z, vtxMax.y, vtxMax.x);
		m_vtxMin = D3DXVECTOR3(-vtxMax.z, vtxMin.y, vtxMin.x);
	}
	else
	{ // ��L�ȊO(������������̏ꍇ)

		// �ő�l�ƍŏ��l��ݒ肷��
		m_vtxMax = D3DXVECTOR3(-vtxMin.x, vtxMax.y, -vtxMin.z);
		m_vtxMin = D3DXVECTOR3(-vtxMax.x, vtxMin.y, -vtxMax.z);
	}
}