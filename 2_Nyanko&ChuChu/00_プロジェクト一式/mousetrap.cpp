//===========================================
//
// �l�Y�~�߂�̃��C������[mousetrap.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "mousetrap.h"
#include "obstacle.h"
#include "mousetrap_iron.h"
#include "danger_mark.h"
#include "useful.h"

#include "manager.h"
#include "input.h"
#include "sound.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define IRON_SHIFT			(10.0f)		// �S�����̂��炷�ʒu
#define DANGER_SHIFT		(200.0f)	// �댯�}�[�N�̂��炷�ʒu
#define JUMP_HEIGHT			(9.0f)		// �W�����v�̍���
#define GRAVITY				(1.0f)		// �d��

//==============================
// �R���X�g���N�^
//==============================
CMouseTrap::CMouseTrap() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	m_pIron = nullptr;			// �S����
	m_pMark = nullptr;			// �댯�}�[�N�̏��
	m_state = STATE_NONE;		// ���
	m_fGravity = 0.0f;			// �d��
	SetCatUse(true);
}

//==============================
// �f�X�g���N�^
//==============================
CMouseTrap::~CMouseTrap()
{

}

//==============================
// �l�Y�~�߂�̏���������
//==============================
HRESULT CMouseTrap::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l���N���A����
	m_pIron = nullptr;			// �S����
	m_pMark = nullptr;			// �댯�}�[�N�̏��
	m_state = STATE_NONE;		// ���
	m_fGravity = 0.0f;			// �d��

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �l�Y�~�߂�̏I������
//========================================
void CMouseTrap::Uninit(void)
{
	if (m_pIron != nullptr)
	{ // �S������ NULL ����Ȃ��ꍇ

		// �S�����̏I������
		m_pIron->Uninit();
		m_pIron = nullptr;
	}

	if (m_pMark != nullptr)
	{ // �}�[�N�� NULL ����Ȃ��ꍇ

		// �}�[�N�̏I������
		m_pMark->Uninit();
		m_pMark = nullptr;
	}

	// �I������
	CObstacle::Uninit();
}

//=====================================
// �l�Y�~�߂�̍X�V����
//=====================================
void CMouseTrap::Update(void)
{
	if (m_pIron != nullptr)
	{ // �S������ NULL ����Ȃ��ꍇ

		// �S�����̈ʒu�ݒ菈��
		IronPosSet();

		switch (m_state)
		{
		case CMouseTrap::STATE_NONE:

			// ���ɂȂ�

			break;

		case CMouseTrap::STATE_MOVE:

			// �ړ�����
			Move();

			// �ړ�����
			if (m_pIron->Move() == true)
			{ // �l�Y�~�߂�̏�ԑJ�ڂ��I�������ꍇ

				// �l�Y�~�߂�Ɋ|���鉹��炷
				CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_MOUSETRAP_ADDICTED);

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
	}
}

//=====================================
// �l�Y�~�߂�̕`�揈��
//=====================================
void CMouseTrap::Draw(void)
{
	// �`�揈��
	CObstacle::Draw();

	if (m_pIron != nullptr)
	{ // �S������ NULL ����Ȃ��ꍇ

		// �S�����̕`�揈��
		m_pIron->Draw();
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CMouseTrap::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos,rot, type);

	// �S�Ă̒l��ݒ肷��
	if (m_pIron == nullptr)
	{ // �S������ NULL �̏ꍇ

		// �S�����𐶐�
		m_pIron = CTrapIron::Create(D3DXVECTOR3(pos.x, pos.y + IRON_SHIFT, pos.z), rot);
	}

	if (m_pMark == nullptr)
	{ // �}�[�N�� NULL �̏ꍇ

		// �댯�}�[�N�̐���
		m_pMark = CDangerMark::Create(D3DXVECTOR3(pos.x, pos.y + DANGER_SHIFT, pos.z), D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	}
	m_state = STATE_NONE;		// ���
}

//=====================================
// �q�b�g����
//=====================================
bool CMouseTrap::Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	if (m_state == STATE_NONE &&
		pPlayer->GetType() == CPlayer::TYPE_RAT &&
		pPlayer->GetState() == CPlayer::STATE_NONE &&
		pPlayer->GetStunState() == CPlayer::STUNSTATE_NONE)
	{ // �C�₵�Ă��Ȃ��l�Y�~���A�ʏ��Ԃ̏ꍇ

		bool bPosbool = false, bPosOldbool = false, bVecbool = false, bVecboolOld = false;

		bool bInside[4] = {};

		D3DXVECTOR3 vecLine, vecMove, vecToPos, vecToPosOld, posOldToVec, posOldToVecOld;
		D3DXVECTOR3 vec[4];
		D3DXVECTOR3 objpos = GetPos();

		float fAngle[4];
		fAngle[0] = atan2f(GetFileData().vtxMin.x, GetFileData().vtxMax.z);
		fAngle[1] = atan2f(GetFileData().vtxMax.x, GetFileData().vtxMax.z);
		fAngle[2] = atan2f(GetFileData().vtxMax.x, GetFileData().vtxMin.z);
		fAngle[3] = atan2f(GetFileData().vtxMin.x, GetFileData().vtxMin.z);

		float fDistance[4];
		fDistance[0] = sqrtf(powf(GetFileData().vtxMin.x, 2) + powf(GetFileData().vtxMax.z, 2));
		fDistance[1] = sqrtf(powf(GetFileData().vtxMax.x, 2) + powf(GetFileData().vtxMax.z, 2));
		fDistance[2] = sqrtf(powf(GetFileData().vtxMax.x, 2) + powf(GetFileData().vtxMin.z, 2));
		fDistance[3] = sqrtf(powf(GetFileData().vtxMin.x, 2) + powf(GetFileData().vtxMin.z, 2));

		vec[0] = D3DXVECTOR3(objpos.x - sinf(-D3DX_PI + fAngle[0] + GetRot().y)*fDistance[0], 0, objpos.z - cosf(-D3DX_PI + fAngle[0] + GetRot().y)* fDistance[0]);
		vec[1] = D3DXVECTOR3(objpos.x - sinf(-D3DX_PI + fAngle[1] + GetRot().y)*fDistance[1], 0, objpos.z - cosf(-D3DX_PI + fAngle[1] + GetRot().y)* fDistance[1]);
		vec[2] = D3DXVECTOR3(objpos.x - sinf(-D3DX_PI + fAngle[2] + GetRot().y)*fDistance[2], 0, objpos.z - cosf(-D3DX_PI + fAngle[2] + GetRot().y)* fDistance[2]);
		vec[3] = D3DXVECTOR3(objpos.x - sinf(-D3DX_PI + fAngle[3] + GetRot().y)*fDistance[3], 0, objpos.z - cosf(-D3DX_PI + fAngle[3] + GetRot().y)* fDistance[3]);

		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			int nCnt2 = nCnt + 1;

			if (nCnt2 >= 4)
			{
				nCnt2 = 0;
			}

			//�x�N�g����
			vecLine = vec[nCnt2] - vec[nCnt];

			vecMove = pPlayer->GetPos() - GetPosOld();

			vecToPos = pPlayer->GetPos() - vec[nCnt];


			//�e�x�N�g���̎Z�o�ƌ�������
			if (0 <= (vecLine.z*vecToPos.x) - (vecLine.x*vecToPos.z))
			{
				bPosbool = true;
			}
			else if (0 > (vecLine.z*vecToPos.x) - (vecLine.x*vecToPos.z))
			{
				bPosbool = false;
			}

			vecToPosOld = GetPosOld() - vec[nCnt];

			if (0 <= (vecLine.z*vecToPosOld.x) - (vecLine.x*vecToPosOld.z))
			{
				bPosOldbool = true;
			}
			else if (0 > (vecLine.z*vecToPosOld.x) - (vecLine.x*vecToPosOld.z))
			{
				bPosOldbool = false;
			}

			posOldToVec = vec[nCnt2] - GetPosOld();

			if (0 <= (vecMove.z*posOldToVec.x) - (vecMove.x*posOldToVec.z))
			{
				bVecbool = true;
			}
			else if (0 > (vecMove.z*posOldToVec.x) - (vecMove.x*posOldToVec.z))
			{
				bVecbool = false;
			}

			posOldToVecOld = vec[nCnt] - GetPosOld();

			if (0 <= (vecMove.z*posOldToVecOld.x) - (vecMove.x*posOldToVecOld.z))
			{
				bVecboolOld = true;
			}
			else if (0 > (vecMove.z*posOldToVecOld.x) - (vecMove.x*posOldToVecOld.z))
			{
				bVecboolOld = false;
			}

			bInside[nCnt] = bPosbool;
		}
		//�ォ��̔���
		if (bInside[0] == bInside[1] && bInside[1] == bInside[2] && bInside[2] == bInside[3] && objpos.y + GetFileData().vtxMax.y > pPlayer->GetPos().y)
		{
			// �ړ���Ԃɂ���
			m_state = STATE_MOVE;

			// �d�͂�ݒ肷��
			m_fGravity = JUMP_HEIGHT;

			// true ��Ԃ�
			return true;
		}
	}

	// false ��Ԃ�
	return false;
}

//=====================================
// �ړ�����
//=====================================
void CMouseTrap::Move(void)
{
	// �ʒu��ݒ肷��
	D3DXVECTOR3 pos = GetPos();

	// �d�͂����Z����
	pos.y += m_fGravity;

	// �d�͂����Z����
	m_fGravity -= GRAVITY;

	// �ʒu��K�p����
	SetPos(pos);
}

//=====================================
// �S�����̈ʒu�̐ݒ菈��
//=====================================
void CMouseTrap::IronPosSet(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 pos = GetPos();					// �ʒu���擾����
	D3DXVECTOR3 posIron = NONE_D3DXVECTOR3;		// �S�̕���

	// �S�̕����̈ʒu��ݒ肷��
	posIron.x = pos.x;
	posIron.y = pos.y + IRON_SHIFT;
	posIron.z = pos.z;

	// �ʒu��K�p����
	m_pIron->SetPos(posIron);
}