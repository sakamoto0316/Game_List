//===========================================
//
// �����o�̃��C������[roomba.cpp]
// Author ��{�ėB
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "roomba.h"
#include "model.h"
#include "useful.h"

#include "player.h"
#include "sound.h"

//==============================
// �R���X�g���N�^
//==============================
CRoomba::CRoomba() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_apSub[nCnt] = NULL;
	}

	m_move = NONE_D3DXVECTOR3;
}

//==============================
// �f�X�g���N�^
//==============================
CRoomba::~CRoomba()
{

}

//==============================
// �����o�̏���������
//==============================
HRESULT CRoomba::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // �����������Ɏ��s�����ꍇ

	  // ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_apSub[nCnt] = NULL;
	}

	//// �|������炷
	//CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_CLEANING);
	
	// �l��Ԃ�
	return S_OK;
}

//========================================
// �����o�̏I������
//========================================
void CRoomba::Uninit(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_apSub[nCnt] != NULL)
		{ // �v���y���� NULL ����Ȃ��ꍇ

			// �v���y���̏I������
			m_apSub[nCnt]->Uninit();
			m_apSub[nCnt] = NULL;
		}
	}

	// �I������
	CObstacle::Uninit();
}

//=====================================
// �����o�̍X�V����
//=====================================
void CRoomba::Update(void)
{
	//�ʒu�������̎擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	//�{�̂̌����𓮂���
	rot.y -= 0.005f;

	//�����Ă�������Ɉړ����鏈��
	Move(rot);

	//�v���y���̈ʒu�ƌ����̍X�V
	SubUpdate();

	//�ʒu�X�V
	pos += m_move;

	//�ʒu�ƌ����̍X�V
	SetPos(pos);
	SetRot(rot);
}

//=====================================
// �ړ�����
//=====================================
void CRoomba::Move(D3DXVECTOR3 rot)
{
	m_move = D3DXVECTOR3(
		sinf(rot.y + (D3DX_PI * 1.0f)) * 2.0f,
		0.0f,
		cosf(rot.y + (D3DX_PI * 1.0f)) * 2.0f);
}

//=====================================
// �v���y���̍X�V����
//=====================================
void CRoomba::SubUpdate(void)
{
	//�ʒu�ƌ����̎擾
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	//�v���y���̌������擾
	D3DXVECTOR3 Subrot[2] = {};
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		Subrot[nCnt] = m_apSub[nCnt]->GetRot();
	}

	//�v���y������
	Subrot[0].y += 0.1f;
	Subrot[1].y -= 0.1f;

	//�v���y���̈ʒu�X�V
	m_apSub[0]->SetPos(D3DXVECTOR3(
		pos.x + sinf(rot.y + (D3DX_PI * 0.75f)) * 50.0f,
		pos.y,
		pos.z + cosf(rot.y + (D3DX_PI * 0.75f)) * 50.0f));

	m_apSub[1]->SetPos(D3DXVECTOR3(
		pos.x + sinf(rot.y + (D3DX_PI * -0.75f)) * 50.0f,
		pos.y,
		pos.z + cosf(rot.y + (D3DX_PI * -0.75f)) * 50.0f));

	//�v���y���̌������X�V����
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_apSub[nCnt]->SetRot(Subrot[nCnt]);
	}
}

//=====================================
// �����o�̕`�揈��
//=====================================
void CRoomba::Draw(void)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_apSub[nCnt] != NULL)
		{ // �v���y���� NULL ����Ȃ��ꍇ

			// �v���y���̕`�揈��
			m_apSub[nCnt]->Draw();
		}
	}

	// �`�揈��
	CObstacle::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CRoomba::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos,rot, type);

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_apSub[nCnt] == NULL)
		{ // �v���y���� NULL �̏ꍇ

			// ���f���𐶐�����
			m_apSub[nCnt] = CModel::Create(TYPE_NONE, PRIORITY_BLOCK);

			if (m_apSub[nCnt] != NULL)
			{ // �v���y���� NULL �̏ꍇ

				switch (nCnt)
				{
				case 0:

					// �v���y���̈ʒu�ݒ�
					m_apSub[nCnt]->SetPos(D3DXVECTOR3(
						pos.x + sinf(rot.y + (D3DX_PI * 0.75f)) * 50.0f,
						pos.y,
						pos.z + cosf(rot.y + (D3DX_PI * 0.75f)) * 50.0f));

					break;

				case 1:

					// �v���y���̈ʒu�ݒ�
					m_apSub[nCnt]->SetPos(D3DXVECTOR3(
						pos.x + sinf(rot.y + (D3DX_PI * -0.75f)) * 50.0f,
						pos.y,
						pos.z + cosf(rot.y + (D3DX_PI * -0.75f)) * 50.0f));

					break;

				default:

					// ��~
					assert(false);

					break;
				}

				m_apSub[nCnt]->SetFileData((CXFile::TYPE::TYPE_RED_ROOMBA_SUB));	// ���f�����
			}
			else
			{ // ��L�ȊO

				// ��~
				assert(false);
			}
		}
		else
		{ // ��L�ȊO

			// ��~
			assert(false);
		}
	}
}

//=====================================
// �����蔻�菈��
//=====================================
bool CRoomba::Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// �ʒu�A���a�A�������擾����
	D3DXVECTOR3 pos = pPlayer->GetPos();
	D3DXVECTOR3 objPos = GetPos();
	float objRadius = GetFileData().fRadius;
	float objHeight = GetFileData().vtxMax.y;

	if (pPlayer->GetType() == CPlayer::TYPE_RAT)
	{ // �l�Y�~�̏ꍇ

		if (objPos.y <= pos.y + collSize.y &&
			objPos.y + objHeight >= pos.y)
		{ // �����̔���

			if (useful::CylinderCollision(&pos, objPos, collSize.x + objRadius))
			{ // �~�̒��ɓ���ꍇ

				// �ʒu��K�p����
				pPlayer->SetPos(pos);

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
bool CRoomba::Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// �ʒu�A���a�A�������擾����
	D3DXVECTOR3 objPos = GetPos();
	float objRadius = GetFileData().fRadius;
	float objHeight = GetFileData().vtxMax.y;

	if (objPos.y <= pPlayer->GetPos().y + collSize.y &&
		objPos.y + objHeight >= pPlayer->GetPos().y &&
		useful::CylinderInner(pPlayer->GetPos(), objPos, collSize.x + objRadius) &&
		pPlayer->GetType() == CPlayer::TYPE_RAT)
	{ // �l�Y�~���~�̒��ɓ������ꍇ

		// true ��Ԃ�
		return true;
	}

	// false ��Ԃ�
	return false;
}