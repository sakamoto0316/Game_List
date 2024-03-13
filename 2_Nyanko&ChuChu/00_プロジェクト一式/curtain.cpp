//===========================================
//
// �J�[�e���̏���[curtain.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "curtain.h"
#include "useful.h"
#include "input.h"
#include "collision.h"
#include "game.h"
#include "sound.h"

#include "switch.h"

//-------------------------------------------
// �������O���
//-------------------------------------------
namespace
{
	const D3DXVECTOR3 SWITCH_POS[MAP_TYPE][MAX_SWITCH] =		// �X�C�b�`�̈ʒu
	{
		{ // 1�}�b�v��
			NONE_D3DXVECTOR3,
			NONE_D3DXVECTOR3,
			NONE_D3DXVECTOR3
		},

		{ // 2�}�b�v��
			D3DXVECTOR3(-1390.0f, 290.0f, -640.0f),
			D3DXVECTOR3(714.0f, 290.0f, -274.0f),
			D3DXVECTOR3(300.0f, 290.0f, 980.0f),
		},

		{ // 3�}�b�v��
			D3DXVECTOR3(750.0f, 256.0f, 980.0f),
			D3DXVECTOR3(-1336.0f, 256.0f, 40.0f),
			D3DXVECTOR3(-1582.0f, 256.0f, -650.0f),
		},
	};
	const D3DXVECTOR3 SWITCH_ROT[MAP_TYPE][MAX_SWITCH] =		// �X�C�b�`�̌���
	{
		{ // 1�}�b�v��
			NONE_D3DXVECTOR3,
			NONE_D3DXVECTOR3,
			NONE_D3DXVECTOR3
		},

		{ // 2�}�b�v��
			D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f),
			D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f),
			D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f),
		},

		{ // 3�}�b�v��
			D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f),
			D3DXVECTOR3(0.0f, D3DX_PI * 1.0f, 0.0f),
			D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f),
		},
	};
	const float CLOSE_SCALE = 0.03f;				// ������Ԃ̊g�嗦
	const float SCALE_CORRECT = 0.01f;				// �g�嗦�̕␳��
	const float OPEN_SCALE = 1.0f;					// �J������Ԃ̊g�嗦
	const float ADD_SWITCH_RADIUS = 50.0f;			// �ǉ����̃X�C�b�`�̔��a
}

//==============================
// �R���X�g���N�^
//==============================
CCurtain::CCurtain() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < MAX_SWITCH; nCnt++)
	{
		m_apSwitch[nCnt] = nullptr;		// �X�C�b�`�̏��
	}
	m_state = STATE_CLOSE;				// ���
	m_stateOld = m_state;				// �O��̏��
	m_vtxMax = NONE_D3DXVECTOR3;		// �ő�l
	m_vtxMin = NONE_D3DXVECTOR3;		// �ŏ��l
	m_fEdge = 0.0f;						// �J�[�e���̒[�̍��W
	SetCatUse(true);					// �l�R�̎g�p����
	SetRatUse(true);					// �l�Y�~�̎g�p����
}

//==============================
// �f�X�g���N�^
//==============================
CCurtain::~CCurtain()
{

}

//==============================
// �J�[�e���̏���������
//==============================
HRESULT CCurtain::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // �����������Ɏ��s�����ꍇ

	  // ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	for (int nCnt = 0; nCnt < MAX_SWITCH; nCnt++)
	{
		m_apSwitch[nCnt] = nullptr;		// ���f���̏��
	}
	m_state = STATE_CLOSE;				// ���
	m_stateOld = m_state;				// �O��̏��
	m_vtxMax = NONE_D3DXVECTOR3;		// �ő�l
	m_vtxMin = NONE_D3DXVECTOR3;		// �ŏ��l
	m_fEdge = 0.0f;						// �J�[�e���̒[�̍��W

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �J�[�e���̏I������
//========================================
void CCurtain::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_SWITCH; nCnt++)
	{
		if (m_apSwitch[nCnt] != nullptr)
		{ // �X�C�b�`�̏�� NULL ����Ȃ��ꍇ

			// �X�C�b�`�̏I������
			m_apSwitch[nCnt]->Uninit();
			m_apSwitch[nCnt] = nullptr;
		}
	}

	// �I������
	CObstacle::Uninit();
}

//=====================================
// �J�[�e���̍X�V����
//=====================================
void CCurtain::Update(void)
{
	// �O��̈ʒu��ݒ肷��
	SetPosOld(GetPos());

	// ��ԃ}�l�[�W���[
	StateManager();

	for (int nCnt = 0; nCnt < MAX_SWITCH; nCnt++)
	{
		if (m_apSwitch[nCnt] != nullptr)
		{ // �X�C�b�`�̏�� NULL ����Ȃ��ꍇ

			// �X�C�b�`�̍X�V����
			m_apSwitch[nCnt]->Update();
		}
	}

	if (m_apSwitch[0]->GetBoot() == true &&
		m_apSwitch[1]->GetBoot() == true &&
		m_apSwitch[2]->GetBoot() == true)
	{ // �S�ăX�C�b�`�������Ă����ꍇ

		// �J����
		m_state = STATE_OPEN;
	}
	else
	{ // ��L�ȊO

		// ����
		m_state = STATE_CLOSE;
	}

	if (m_stateOld != m_state)
	{ // ��Ԃ��؂�ւ�����ꍇ

		// �J�[�e���̉ғ�����炷
		CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_CURTAIN_OPEN);
	}

	// �O��̏�Ԃ�ݒ肷��
	m_stateOld = m_state;

	// �g�嗦�̐ݒ菈��
	ScaleVtxSet();
}

//=====================================
// �J�[�e���̕`�揈��
//=====================================
void CCurtain::Draw(void)
{
	// �`�揈��
	CObstacle::Draw();

	for (int nCntSwith = 0; nCntSwith < MAX_SWITCH; nCntSwith++)
	{
		if (m_apSwitch[nCntSwith] != nullptr)
		{ // �X�C�b�`�̏�� NULL ����Ȃ��ꍇ

			for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
			{// �ǂ̃v���C���[�̃J�����ԍ����񂵂Ċm���߂�
				if (CManager::Get()->GetMode() == CScene::MODE_GAME)
				{// �Q�[�����[�h�̎�
					CPlayer* pPlayer = CGame::GetPlayer(nCnt);
					if (pPlayer->GetType() == CPlayer::TYPE::TYPE_CAT)
					{// �l�R�v���C���[���擾
						if (pPlayer->GetPlayerIdx() == GetDrawIdx())
						{// �J�����ԍ��ƃv���C���[�ԍ�����v���鎞
							if (m_apSwitch[nCntSwith]->GetBoot() == true)
							{// �e���r�̓d����ON�̎������R���̕\���𔖂�����

								// �X�C�b�`�̕`�揈��
								m_apSwitch[nCntSwith]->Draw(1.0f);
							}
							else
							{
								// �X�C�b�`�̕`�揈��
								m_apSwitch[nCntSwith]->Draw(0.3f);
							}
						}
					}
					else if (pPlayer->GetType() == CPlayer::TYPE::TYPE_RAT)
					{// �l�Y�~�v���C���[���擾
						if (pPlayer->GetPlayerIdx() == GetDrawIdx())
						{// �J�����ԍ��ƃv���C���[�ԍ�����v���鎞
							if (m_apSwitch[nCntSwith]->GetBoot() == false)
							{// �e���r�̓d����OFF�̎������R���̕\���𔖂�����

								// �X�C�b�`�̕`�揈��
								m_apSwitch[nCntSwith]->Draw(1.0f);
							}
							else
							{
								// �X�C�b�`�̕`�揈��
								m_apSwitch[nCntSwith]->Draw(0.3f);
							}
						}
					}
				}
			}

			//// �X�C�b�`�̕`�揈��
			//m_apSwitch[nCnt]->Draw();
		}
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CCurtain::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos, rot, type);

	// �g�嗦������������
	SetScale(D3DXVECTOR3(1.0f, 1.0f, CLOSE_SCALE));

	if (CManager::Get()->GetMode() == CScene::MODE_GAME)
	{ // �Q�[�����[�h�̏ꍇ

		// �}�b�v�̔ԍ����擾����
		int nMapNum = CGame::GetMapNumber();

		// �S�Ă̒l��ݒ肷��
		for (int nCnt = 0; nCnt < MAX_SWITCH; nCnt++)
		{
			if (m_apSwitch[nCnt] == nullptr)
			{ // ���f���� NULL ����Ȃ��ꍇ

				// �X�C�b�`�̐�������
				m_apSwitch[nCnt] = CSwitch::Create(SWITCH_POS[nMapNum][nCnt], SWITCH_ROT[nMapNum][nCnt]);
			}
		}
	}
	m_state = STATE_CLOSE;			// ���

	// ���_�̐ݒ菈��
	VtxSetting();

	// �g�嗦�ɂ�钸�_�̐ݒ菈��
	ScaleVtxSet();
}

//=====================================
// �����蔻�菈��
//=====================================
bool CCurtain::Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	D3DXVECTOR3 pos = pPlayer->GetPos();
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);	// �ŏ��l
	D3DXVECTOR3 vtxMax = collSize;										// �ő�l

	// �Z�ʑ̂̓����蔻��
	collision::HexahedronCollision
	(
		&pos,
		GetPos(),
		pPlayer->GetPosOld(),
		GetPosOld(),
		vtxMin,
		m_vtxMin,
		vtxMax,
		m_vtxMax
	);

	// �ʒu��K�p����
	pPlayer->SetPos(pos);

	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CCurtain::HitCircle(CPlayer* pPlayer, const float Radius)
{
	for (int nCnt = 0; nCnt < MAX_SWITCH; nCnt++)
	{
		if (m_apSwitch[nCnt] != nullptr)
		{ // �X�C�b�`�̏�� NULL �̏ꍇ

			if (useful::CircleCollisionXZ
			(
				pPlayer->GetPos(),
				m_apSwitch[nCnt]->GetModel(CSwitch::TYPE_BASE)->GetPos(),
				Radius,
				m_apSwitch[nCnt]->GetModel(CSwitch::TYPE_BASE)->GetFileData().fRadius + ADD_SWITCH_RADIUS
			) == true)
			{ // �~�̓����蔻����ɓ������ꍇ

				switch (pPlayer->GetType())
				{
				case CPlayer::TYPE_CAT:		// �l�R

					if (m_apSwitch[nCnt]->GetBoot() == true)
					{ // �N���󋵂� false �̏ꍇ

						// �M�~�b�NUI�̐ݒ菈��
						m_apSwitch[nCnt]->SetGimmickUI(true, pPlayer->GetPlayerIdx());
					}
					else
					{ // ��L�ȊO

						// �M�~�b�NUI�̐ݒ菈��
						m_apSwitch[nCnt]->SetGimmickUI(false, pPlayer->GetPlayerIdx());
					}

					break;

				case CPlayer::TYPE_RAT:		// �l�Y�~

					if (m_apSwitch[nCnt]->GetBoot() == false)
					{ // �N���󋵂� true �̏ꍇ

						// �M�~�b�NUI�̐ݒ菈��
						m_apSwitch[nCnt]->SetGimmickUI(true, pPlayer->GetPlayerIdx());
					}
					else
					{ // ��L�ȊO

						// �M�~�b�NUI�̐ݒ菈��
						m_apSwitch[nCnt]->SetGimmickUI(false, pPlayer->GetPlayerIdx());
					}

					break;

				default:

					// ��~
					assert(false);

					break;
				}
			}
			else
			{ // ��L�ȊO

				// �M�~�b�NUI�̐ݒ菈��
				m_apSwitch[nCnt]->SetGimmickUI(false, pPlayer->GetPlayerIdx());
			}
		}
	}

	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g����
//=====================================
void CCurtain::HitMultiCircle(CPlayer* pPlayer, const float Radius, bool bInput)
{
	for (int nCnt = 0; nCnt < MAX_SWITCH; nCnt++)
	{
		if (m_apSwitch[nCnt] != nullptr)
		{ // �X�C�b�`�̏�� NULL �̏ꍇ

			if (useful::CircleCollisionXZ
			(
				pPlayer->GetPos(),
				m_apSwitch[nCnt]->GetModel(CSwitch::TYPE_BASE)->GetPos(),
				Radius,
				m_apSwitch[nCnt]->GetModel(CSwitch::TYPE_BASE)->GetFileData().fRadius + ADD_SWITCH_RADIUS
			) == true)
			{ // �~�̓����蔻����ɓ������ꍇ

				if (bInput == true)
				{ // ���͏󋵂� true �̏ꍇ

					switch (pPlayer->GetType())
					{
					case CPlayer::TYPE_CAT:		// �l�R

						if (m_apSwitch[nCnt]->GetBoot() == true)
						{ // �N���󋵂� false �̏ꍇ

							// �N���󋵂̓���ւ�����
							m_apSwitch[nCnt]->ChangeBoot();
						}

						break;

					case CPlayer::TYPE_RAT:		// �l�Y�~

						if (m_apSwitch[nCnt]->GetBoot() == false)
						{ // �N���󋵂� true �̏ꍇ

							// �N���󋵂̓���ւ�����
							m_apSwitch[nCnt]->ChangeBoot();
						}

						break;

					default:

						// ��~
						assert(false);

						break;
					}
				}
			}
		}
	}
}

//=====================================
// ���_�̐ݒ菈��
//=====================================
void CCurtain::VtxSetting(void)
{
	// �����ƍő�l�E�ŏ��l��ݒ肷��
	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 vtxMax = GetFileData().vtxMax;
	D3DXVECTOR3 vtxMin = GetFileData().vtxMin;

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

//=====================================
// �g�嗦�ɂ�钸�_�̐ݒ菈��
//=====================================
void CCurtain::ScaleVtxSet(void)
{
	// �������擾����
	D3DXVECTOR3 rot = GetRot();

	// �J�[�e���̒[�̍��W��ݒ肷��
	m_fEdge = GetFileData().vtxMin.z * GetScale().z;

	if (rot.y >= D3DX_PI * -0.25f &&
		rot.y <= D3DX_PI * 0.25f)
	{ // ��������O����̏ꍇ

		// ���_��ݒ肷��
		m_vtxMin.z = m_fEdge;
	}
	else if (rot.y >= D3DX_PI * 0.25f &&
		rot.y <= D3DX_PI * 0.75f)
	{ // ������������̏ꍇ

		// ���_��ݒ肷��
		m_vtxMin.x = m_fEdge;
	}
	else if (rot.y >= D3DX_PI * -0.75f &&
		rot.y <= D3DX_PI * -0.25f)
	{ // �������E����̏ꍇ

		// ���_��ݒ肷��
		m_vtxMax.x = -m_fEdge;
	}
	else
	{ // ��L�ȊO(������������̏ꍇ)

		// ���_��ݒ肷��
		m_vtxMax.z = -m_fEdge;
	}
}

//=====================================
// ��ԃ}�l�[�W���[
//=====================================
void CCurtain::StateManager(void)
{
	// �g�嗦���擾����
	D3DXVECTOR3 scale = GetScale();

	switch (m_state)
	{
	case CCurtain::STATE_CLOSE:		// ������

		// �ϓ��ȕ␳����
		useful::FrameCorrect(CLOSE_SCALE, &scale.z, SCALE_CORRECT);

		break;

	case CCurtain::STATE_OPEN:		// �J�������

		// �ϓ��ȕ␳����
		useful::FrameCorrect(OPEN_SCALE, &scale.z, SCALE_CORRECT);

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	// �g�嗦��K�p����
	SetScale(scale);
}