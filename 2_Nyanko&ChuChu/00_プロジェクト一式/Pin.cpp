//===========================================
//
// ��e�̏���[Pin.cpp]
// Author ��{�ėB
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "Pin.h"
#include "useful.h"
#include "objectX.h"
#include "input.h"
#include "effect.h"
#include "fraction.h"
#include "sound.h"

#define ACTION_TIME (120)
#define WAIT_TIME (20)

//==============================
// �R���X�g���N�^
//==============================
CPin::CPin() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	m_State = STATE_FALSE;
	m_move = NONE_D3DXVECTOR3;
	SetRatUse(true);
}

//==============================
// �f�X�g���N�^
//==============================
CPin::~CPin()
{

}

//==============================
// ��e�̏���������
//==============================
HRESULT CPin::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // �����������Ɏ��s�����ꍇ

	  // ���s��Ԃ�
		return E_FAIL;
	}

	// �l��Ԃ�
	return S_OK;
}

//========================================
// ��e�̏I������
//========================================
void CPin::Uninit(void)
{
	// �I������
	CObstacle::Uninit();
}

//=====================================
// ��e�̍X�V����
//=====================================
void CPin::Update(void)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	StateManager(&pos,&rot);

	//�ʒu�X�V
	pos += m_move;

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_0) == true)
	{ // 0�{�^�����������ꍇ
		Action();
	}

	SetPos(pos);
	SetRot(rot);
}

//=====================================
// ��e�̕`�揈��
//=====================================
void CPin::Draw(void)
{
	// �`�揈��
	CObstacle::Draw(1.0f);
}

//=====================================
// ��ԊǗ�
//=====================================
void CPin::StateManager(D3DXVECTOR3 *pos, D3DXVECTOR3 *rot)
{
	switch (m_State)
	{
	case CPin::STATE_FALSE:

		break;

	case CPin::STATE_FALLWAIT:	//�M�~�b�N�N��������ʔ����܂ł̏�������
		rot->z += 0.1f;
		m_move.y -= 0.75f;
		m_move.x = sinf(rot->y + (D3DX_PI * -0.5f)) * 4.0f;
		m_move.z = cosf(rot->y + (D3DX_PI * -0.5f)) * 4.0f;

		if (pos->y < 0)
		{
			pos->y = 0.0f;
			rot->z = 0.0f;
			m_State = STATE_TRUE;
			SetFileData(CXFile::TYPE_RED_PINSET);

			for (int nCnt = 0; nCnt < 20; nCnt++)
			{
				CFraction::Create(GetPos(), CFraction::TYPE_PIN);
			}

			// ��e���U�鉹��炷
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_THUMBTACK);
		}
		break;

	case CPin::STATE_TRUE:	//�M�~�b�N�̌��ʔ��������~�܂ł̏���
		m_move = NONE_D3DXVECTOR3;
		pos->y = 0.0f;
		break;
	}
}

//=====================================
// ���[�N�����̏���
//=====================================
void CPin::Action(void)
{
	if (m_State == STATE_FALSE)
	{
		m_State = STATE_FALLWAIT;
		SetAction(true);
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CPin::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos,rot, type);
}

//=====================================
// �q�b�g����
//=====================================
bool CPin::Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	if (m_State == STATE_TRUE)
	{ // �M�~�b�N������Ԃ̏ꍇ

		if (pPlayer->GetType() == CPlayer::TYPE_CAT)
		{ // �Ώۃv���C���[���l�R�������ꍇ

			// �ő�l�ƍŏ��l��ݒ肷��
			D3DXVECTOR3 vtxMax = D3DXVECTOR3(collSize.x, collSize.y, collSize.z);
			D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);

			if (useful::RectangleCollisionXY(pPlayer->GetPos(), GetPos(), vtxMax, GetFileData().vtxMax, vtxMin, GetFileData().vtxMin) == true &&
				useful::RectangleCollisionXZ(pPlayer->GetPos(), GetPos(), vtxMax, GetFileData().vtxMax, vtxMin, GetFileData().vtxMin) == true &&
				useful::RectangleCollisionYZ(pPlayer->GetPos(), GetPos(), vtxMax, GetFileData().vtxMax, vtxMin, GetFileData().vtxMin) == true)
			{ // �͈͓��ɓ������ꍇ

				// �I������
				Uninit();

				// true ��Ԃ�
				return true;
			}
		}
	}

	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CPin::HitCircle(CPlayer* pPlayer, const float Radius)
{
	if (GetAction() == false &&
		useful::CircleCollisionXZ(pPlayer->GetPos(), GetPos(), Radius, GetFileData().fRadius) == true)
	{//�~�͈͓̔��̏ꍇture��Ԃ�
		return true;
	}

	// false ��Ԃ�
	return false;
}