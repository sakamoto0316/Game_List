//===========================================
//
// ���[�h�̏���[Himo.cpp]
// Author ��{�ėB
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "leash.h"
#include "useful.h"
#include "objectX.h"
#include "input.h"
#include "effect.h"
#include "collision.h"
#include "debugproc.h"
#include "tutorial.h"
#include "sound.h"

#define ACTION_TIME (240)
#define WAIT_TIME (20)

//==============================
// �R���X�g���N�^
//==============================
CLeash::CLeash() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	m_move = NONE_D3DXVECTOR3;
	ActionPosHead = NONE_D3DXVECTOR3;
	ActionPosToes = NONE_D3DXVECTOR3;
	m_vtxMax = NONE_D3DXVECTOR3;			// �ő�l
	m_vtxMin = NONE_D3DXVECTOR3;			// �ŏ��l
	m_State = STATE_FALSE;
	m_bSe = false;							// SE�̍Đ���

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_bSetHead[nCnt] = false;
		m_bSetToes[nCnt] = false;
	}
	m_StateCount = 0;
	SetRatUse(true);
}

//==============================
// �f�X�g���N�^
//==============================
CLeash::~CLeash()
{

}

//==============================
// ���[�h�̏���������
//==============================
HRESULT CLeash::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // �����������Ɏ��s�����ꍇ

	  // ���s��Ԃ�
		return E_FAIL;
	}

	m_move = NONE_D3DXVECTOR3;
	ActionPosHead = NONE_D3DXVECTOR3;
	ActionPosToes = NONE_D3DXVECTOR3;
	m_vtxMax = NONE_D3DXVECTOR3;			// �ő�l
	m_vtxMin = NONE_D3DXVECTOR3;			// �ŏ��l
	m_State = STATE_FALSE;
	m_bSe = false;							// SE�̍Đ���

	// �l��Ԃ�
	return S_OK;
}

//========================================
// ���[�h�̏I������
//========================================
void CLeash::Uninit(void)
{
	// �I������y
	CObstacle::Uninit();
}

//=====================================
// ���[�h�̍X�V����
//=====================================
void CLeash::Update(void)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	//�M�~�b�N�N�����̏���
	if (((m_bSetHead[0] == true || m_bSetHead[1] == true || m_bSetHead[2] == true || m_bSetHead[3] == true) && 
		(m_bSetToes[0] == true || m_bSetToes[1] == true || m_bSetToes[2] == true || m_bSetToes[3] == true)) &&
		m_State == STATE_FALSE)
	{//�N�����Ă��Ȃ����Ƀl�Y�~�����[����������
		Action();

		// �A�N�V�����󋵂� true �ɂ���
		SetAction(true);

		if (CManager::Get()->GetMode() == CScene::MODE_TUTORIAL)
		{
			CTutorial::SetMultiAction(true);
		}
	}

	CManager::Get()->GetDebugProc()->Print("\n");
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		if (m_bSetHead[nCnt] == true)
		{
			CManager::Get()->GetDebugProc()->Print("�I��:");
		}
		else
		{
			CManager::Get()->GetDebugProc()->Print("�I�t:");
		}
	}
	CManager::Get()->GetDebugProc()->Print("\n");
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		if (m_bSetToes[nCnt] == true)
		{
			CManager::Get()->GetDebugProc()->Print("�I��:");
		}
		else
		{
			CManager::Get()->GetDebugProc()->Print("�I�t:");
		}
	}
	CManager::Get()->GetDebugProc()->Print("\n");

	StateManager(&pos);

	//�d��
	m_move.y -= 1.0f;

	//�ʒu�X�V
	pos.y += m_move.y;

	//�n�ʔ���
	if (pos.y < 0.0f)
	{
		pos.y = 0.0f;
	}

	SetActionPos(pos, rot);

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_0) == true)
	{ // A�{�^�����������ꍇ
		m_bSetHead[0] = true;
		m_bSetToes[0] = true;
	}

	SetPos(pos);
}

//=====================================
// ���[�h�̕`�揈��
//=====================================
void CLeash::Draw(void)
{
	// �`�揈��
	CObstacle::Draw();
}

//=====================================
// ���[�N�����̏���
//=====================================
void CLeash::Action(void)
{
	m_State = STATE_JUMPWAIT;
	m_StateCount = WAIT_TIME;
	m_move.y = 30.0f;
	SetAction(true);
}

//=====================================
// �M�~�b�N�N���ʒu�̐ݒ�
//=====================================
void CLeash::SetActionPos(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	ActionPosHead = D3DXVECTOR3(
		pos.x + sinf(rot.y + (D3DX_PI * 1.0f)) * 300.0f,
		pos.y,
		pos.z + cosf(rot.y + (D3DX_PI * 1.0f)) * 300.0f);

	ActionPosToes = D3DXVECTOR3(
		pos.x + sinf(rot.y + (D3DX_PI * 0.0f)) * 350.0f,
		pos.y,
		pos.z + cosf(rot.y + (D3DX_PI * 0.0f)) * 350.0f);
}

//=====================================
// ��ԊǗ�
//=====================================
void CLeash::StateManager(D3DXVECTOR3 *pos)
{
	switch (m_State)
	{
	case CLeash::STATE_FALSE:

		break;

	case CLeash::STATE_JUMPWAIT:	//�M�~�b�N�N��������ʔ����܂ł̏�������
		m_StateCount--;
		if (m_StateCount <= 0)
		{
			m_State = STATE_TRUE;
			m_StateCount = ACTION_TIME;
			SetFileData(CXFile::TYPE_RED_LEASHSET);

			
		}
		break;

	case CLeash::STATE_TRUE:	//�M�~�b�N�̌��ʔ��������~�܂ł̏���
		m_StateCount--;

		if (pos->y < 200.0f)
		{
			pos->y = 200.0f;
			m_move.y = 0.0f;

			if (m_bSe == false)
			{ // SE�Đ����ĂȂ�������
				// ���[�h���Đ�
				CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_LEASH);

				m_bSe = true;
			}
		}

		if (m_StateCount <= 0)
		{
			m_State = STATE_FALSE;
			for (int nCnt = 0; nCnt < 4; nCnt++)
			{
				m_bSetHead[nCnt] = false;
				m_bSetToes[nCnt] = false;
			}

			// �A�N�V�����󋵂� false �ɂ���
			SetAction(false);

			SetFileData(CXFile::TYPE_LEASH);
		}
		break;
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CLeash::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos,rot, type);

	// �����蔻��̐ݒ菈��
	CollisionSetting();
}

//=====================================
// �����蔻��̐ݒ菈��
//=====================================
void CLeash::CollisionSetting(void)
{
	// �ʒu�ƌ����ƍŏ��l�ƍő�l���擾����
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 vtxMin = GetFileData().vtxMin;
	D3DXVECTOR3 vtxMax = GetFileData().vtxMax;

	if (rot.y >= D3DX_PI * -0.25f &&
		rot.y <= D3DX_PI * 0.25f)
	{ // ��������O����̏ꍇ

		// �ő�l�ƍŏ��l��ݒ肷��
		m_vtxMax = D3DXVECTOR3(0.0f, vtxMax.y, vtxMax.z);
		m_vtxMin = D3DXVECTOR3(0.0f, vtxMin.y, vtxMin.z);
	}
	else if (rot.y >= D3DX_PI * 0.25f &&
		rot.y <= D3DX_PI * 0.75f)
	{ // ������������̏ꍇ

		// �ő�l�ƍŏ��l��ݒ肷��
		m_vtxMax = D3DXVECTOR3(vtxMax.z, vtxMax.y, 0.0f);
		m_vtxMin = D3DXVECTOR3(vtxMin.z, vtxMin.y, 0.0f);
	}
	else if (rot.y >= D3DX_PI * -0.75f &&
		rot.y <= D3DX_PI * -0.25f)
	{ // �������E����̏ꍇ

		// �ő�l�ƍŏ��l��ݒ肷��
		m_vtxMax = D3DXVECTOR3(-vtxMin.z, vtxMax.y, 0.0f);
		m_vtxMin = D3DXVECTOR3(-vtxMax.z, vtxMin.y, 0.0f);
	}
	else
	{ // ��L�ȊO(������������̏ꍇ)

		// �ő�l�ƍŏ��l��ݒ肷��
		m_vtxMax = D3DXVECTOR3(0.0f, vtxMax.y, -vtxMin.z);
		m_vtxMin = D3DXVECTOR3(0.0f, vtxMin.y, -vtxMax.z);
	}
}

//=====================================
// �q�b�g����
//=====================================
bool CLeash::Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// �ő�l�ƍŏ��l��ݒ肷��
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(collSize.x, collSize.y, collSize.z);
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);

	if (pPlayer->GetType() == CPlayer::TYPE_CAT)
	{ // �l�R�̏ꍇ

		if (m_State != STATE_FALSE &&
			useful::RectangleCollisionXY(pPlayer->GetPos(), GetPos(), vtxMax, m_vtxMax, vtxMin, m_vtxMin) == true &&
			useful::RectangleCollisionXZ(pPlayer->GetPos(), GetPos(), vtxMax, m_vtxMax, vtxMin, m_vtxMin) == true &&
			useful::RectangleCollisionYZ(pPlayer->GetPos(), GetPos(), vtxMax, m_vtxMax, vtxMin, m_vtxMin) == true)
		{ // ��~��ԈȊO���A�����蔻��̒��ɓ������ꍇ

			// true ��Ԃ�
			return true;
		}
	}

	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CLeash::HitCircle(CPlayer* pPlayer, const float Radius)
{
	if (GetAction() == false)
	{ // �A�N�V�����󋵂� false �̏ꍇ

		if (useful::CircleCollisionXZ(pPlayer->GetPos(), ActionPosHead, Radius, GetFileData().fRadius) == true)
		{//�~�͈͓̔��̏ꍇture��Ԃ�
			return true;
		}

		if (useful::CircleCollisionXZ(pPlayer->GetPos(), ActionPosToes, Radius, GetFileData().fRadius) == true)
		{//�~�͈͓̔��̏ꍇture��Ԃ�
			return true;
		}
	}

	return false;
}

//=====================================
// �q�b�g����
//=====================================
void CLeash::HitMultiCircle(CPlayer* pPlayer, const float Radius, bool bInput)
{
	if (GetAction() == false)
	{ // �A�N�V�����󋵂� false �̏ꍇ

		if (useful::CircleCollisionXZ(pPlayer->GetPos(), ActionPosHead, Radius, GetFileData().fRadius) == true)
		{//�~�͈͓̔��̏ꍇture��Ԃ�

			if (bInput == true)
			{//�N�����͂����鎞
				m_bSetHead[pPlayer->GetPlayerIdx()] = true;
			}
		}
		else
		{
			m_bSetHead[pPlayer->GetPlayerIdx()] = false;
		}

		if (useful::CircleCollisionXZ(pPlayer->GetPos(), ActionPosToes, Radius, GetFileData().fRadius) == true)
		{//�~�͈͓̔��̏ꍇture��Ԃ�

			if (bInput == true)
			{//�N�����͂����鎞
				m_bSetToes[pPlayer->GetPlayerIdx()] = true;
			}
		}
		else
		{
			m_bSetToes[pPlayer->GetPlayerIdx()] = false;
		}
	}
}