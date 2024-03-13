//===========================================
//
// �Ђ��̏���[Himo.cpp]
// Author ��{�ėB
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "Himo.h"
#include "useful.h"
#include "objectX.h"
#include "tarai.h"
#include "input.h"
#include "sound.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define TARAI_FALL_AREA_X	(3001)		// ���炢�̗����͈�(X)
#define TARAI_FALL_AREA_Z	(2001)		// ���炢�̗����͈�(Z)
#define TARAI_COUNT			(40)		// 1�x�̋N���ł��炢�������鐔

//==============================
// �R���X�g���N�^
//==============================
CHimo::CHimo() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	for(int nCnt = 0; nCnt < MAX_TARAI; nCnt++)
	{
		m_apTarai[nCnt] = NULL;
	}
	m_nTaraiCount = 0;
	m_fDownPosY = 0.0f;
	m_fUpPosY = 0.0f;
	m_bFall = false;
	SetCatUse(true);
}

//==============================
// �f�X�g���N�^
//==============================
CHimo::~CHimo()
{

}

//==============================
// �Ђ��̏���������
//==============================
HRESULT CHimo::Init(void)
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
// �Ђ��̏I������
//========================================
void CHimo::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_TARAI; nCnt++)
	{
		if (m_apTarai[nCnt] != nullptr)
		{ // �^���C�� NULL ����Ȃ��ꍇ

			// �^���C�̏I������
			m_apTarai[nCnt]->Uninit();
			m_apTarai[nCnt] = nullptr;
		}
	}

	// �I������
	CObstacle::Uninit();
}

//=====================================
// �Ђ��̍X�V����
//=====================================
void CHimo::Update(void)
{
	// �^���C�̑��݊m�F����
	TaraiCheck();

	{ // �R�̈ړ�����

		// �ʒu���擾����
		D3DXVECTOR3 pos = GetPos();

		if (GetAction() == true)
		{ // �A�N�V�����󋵂� true �̏ꍇ
			
			if (pos.y > m_fDownPosY)
			{ // �K��̈ʒu�܂ŉ������Ă��Ȃ��ꍇ

				// �ʒu��������
				pos.y -= 2.0f;
			}

			// �^���C�̐�������
			SetTarai();
		}
		else
		{ // ��L�ȊO

			if (pos.y < m_fUpPosY)
			{ // �K��̈ʒu�܂ŏオ���Ă��Ȃ��ꍇ

				// �ʒu���グ��
				pos.y += 2.0f;
			}

			// �����󋵂� false �ɂ���
			m_bFall = false;
		}

		// �ʒu�̐ݒ菈��
		SetPos(pos);
	}

	// �^���C�̃J�E���g���f����
	CountJudge();

	for (int nCnt = 0; nCnt < MAX_TARAI; nCnt++)
	{
		if (m_apTarai[nCnt] != NULL)
		{ // �^���C�� NULL ����Ȃ��ꍇ

			// �^���C�̍X�V����
			m_apTarai[nCnt]->Update();
		}
	}
}

//=====================================
// �Ђ��̕`�揈��
//=====================================
void CHimo::Draw(void)
{
	// �`�揈��
	CObstacle::Draw(1.0f);

	for (int nCnt = 0; nCnt < MAX_TARAI; nCnt++)
	{
		if (m_apTarai[nCnt] != NULL)
		{
			m_apTarai[nCnt]->Draw();
		}
	}
}

//=====================================
// ���炢�̑��݊m�F����
//=====================================
void CHimo::TaraiCheck(void)
{
	for (int nCnt = 0; nCnt < MAX_TARAI; nCnt++)
	{
		if (m_apTarai[nCnt] == nullptr)
		{ // �^���C�� NULL ����Ȃ��ꍇ

			// �����󋵂� false �ɂ���
			m_bFall = false;

			// ���̐�̏������s��Ȃ�
			return;
		}
	}

	// �����󋵂� true �ɂ���
	m_bFall = true;
}

//=====================================
// ���炢�̐�������
//=====================================
void CHimo::SetTarai(void)
{
	// �����_���͈̔͂�錾
	int nRandX;
	int nRandY;

	if (m_bFall == false)
	{ // �����󋵂� false �̏ꍇ

		for (int nCnt = 0; nCnt < MAX_TARAI; nCnt++)
		{
			if (m_apTarai[nCnt] == NULL)
			{ // �^���C�� NULL �̏ꍇ

				// ���W�������_���ŎZ�o
				nRandX = rand() % TARAI_FALL_AREA_X;
				nRandY = rand() % TARAI_FALL_AREA_Z;

				// �^���C�𐶐�
				m_apTarai[nCnt] = CTarai::Create(D3DXVECTOR3((float)nRandX - ((float)TARAI_FALL_AREA_X * 0.5f), 1000.0f, (float)nRandY - ((float)TARAI_FALL_AREA_Z * 0.5f)), this);
				m_apTarai[nCnt]->SetIndex(nCnt);

				// �^���C�̗������J�E���g�������Z����
				m_nTaraiCount++;

				// for���𔲂��o��
				break;
			}
		}
	}
}

//=====================================
// �^���C�̃J�E���g���f����
//=====================================
void CHimo::CountJudge(void)
{
	if (m_nTaraiCount >= TARAI_COUNT)
	{ // �J�E���g�����ȏ�̏ꍇ

		// �^���C�J�E���g��0�ɂ���
		m_nTaraiCount = 0;

		// �A�N�V�����󋵂� false �ɂ���
		SetAction(false);
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CHimo::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos,rot, type);

	// �オ��ʒu�E������ʒu��ݒ肷��
	m_fDownPosY = pos.y - 50.0f;
	m_fUpPosY = pos.y;
}

//=====================================
// �R����������ꂽ���̏���
//=====================================
void CHimo::Action(void)
{
	// �A�N�V�����󋵂� true �ɂ���
	SetAction(true);

	// �Ђ���SE�炷
	CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_HIMO);
}

//=====================================
// �q�b�g����
//=====================================
bool CHimo::Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	for (int nCntTarai = 0; nCntTarai < MAX_TARAI; nCntTarai++)
	{
		if (m_apTarai[nCntTarai] != nullptr)
		{ // �^���C�� NULL ����Ȃ��ꍇ

			if (pPlayer->GetPos().y + collSize.y <= m_apTarai[nCntTarai]->GetPosOld().y + m_apTarai[nCntTarai]->GetFileData().vtxMin.y &&
				pPlayer->GetPos().y + collSize.y >= m_apTarai[nCntTarai]->GetPos().y + m_apTarai[nCntTarai]->GetFileData().vtxMin.y &&
				useful::CylinderInner(pPlayer->GetPos(), m_apTarai[nCntTarai]->GetPos(), m_apTarai[nCntTarai]->GetFileData().fRadius + collSize.x) == true)
			{ // �^���C������ɗ����Ă����ꍇ

				// �^���C�����ɗ����鉹��炷
				CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_TUB);

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
bool CHimo::HitCircle(CPlayer* pPlayer, const float Radius)
{
	if (GetAction() == false &&
		useful::CircleCollisionXZ(pPlayer->GetPos(), GetPos(), Radius, GetFileData().fRadius) == true)
	{ // �~�͈͓̔��̏ꍇ

		// true��Ԃ�
		return true;
	}

	// false ��Ԃ�
	return false;
}