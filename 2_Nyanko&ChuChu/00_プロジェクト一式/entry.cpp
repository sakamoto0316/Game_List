//============================================
//
// �G���g���[��ʂ̃��C������[entry.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "entry.h"
#include "renderer.h"
#include "fade.h"
#include "Objectmesh.h"
#include "debugproc.h"
#include "entry_UI.h"
#include "entry_team.h"
#include "entry_BG.h"
#include "input.h"
#include "player.h"
#include "sound.h"
#include "entry_message.h"
#include "entry_rand.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define POS_MESSAGEUI			(D3DXVECTOR3(SCREEN_WIDTH * 0.5f - 130.0f, 675.0f, 0.0f))		// �������UI�̈ʒu
#define SIZE_MESSAGEUI			(D3DXVECTOR3(500.0f, 50.0f, 0.0f))						// �������UI�̃T�C�Y

//--------------------------------------------
// �ÓI�����o�ϐ�
//--------------------------------------------
int CEntry::m_nCatIdx = 0;						// �l�R�����v���C���[
int CEntry::m_nCatOldIdx = 0;					// �����pID
int CEntry::m_EntryId[MAX_PLAY] = {};			// �S�̂�ID
CPlayer* CEntry::m_apPlayer[MAX_PLAY] = {};		// �v���C���[�̃��f�����
CEntryUI* CEntry::m_apUI[MAX_PLAY] = {};		// �G���g���[UI�̏��

//=========================================
// �R���X�g���N�^
//=========================================
CEntry::CEntry() : CScene(TYPE_SCENE, PRIORITY_BG)
{
	// �S�Ă̒l���N���A����
	m_nCatIdx = 0;					// �l�R�����v���C���[
	m_nCatOldIdx = 0;				// �����pID
	m_nSceneCnt = 0;				// �J�ڂ܂ł̃J�E���g
	m_bEnter = false;				// �G���^�[�����������ǂ���
	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		m_apUI[nCnt] = nullptr;		// �G���g���[UI�̏��
		m_apPlayer[nCnt] = nullptr;	// �v���C���[�̃��f�����
	}
}

//=========================================
// �f�X�g���N�^
//=========================================
CEntry::~CEntry()
{

}

//=========================================
//����������
//=========================================
HRESULT CEntry::Init(void)
{
	// �S�Ă̒l������������
	m_nCatIdx = 0;					// �l�R�����v���C���[
	m_nCatOldIdx = 0;				// �����pID
	m_nSceneCnt = 0;				// �J�ڂ܂ł̃J�E���g
	m_bEnter = false;				// �G���^�[�����������ǂ���

	//�@�V�[���̏�����
	CScene::Init();

	// �w�i�̐�������
	CEntryBG::Create();

	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		if (nCnt == m_nCatIdx)
		{ // �l�R�����v���C���[�̂�

			// �G���g���[UI�̐�������
			m_apUI[nCnt] = CEntryUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + (300.0f * nCnt) - 450.0f, SCREEN_HEIGHT * 0.45f, 0.0f), nCnt, CPlayer::TYPE_CAT);

			// �l�R�̐�������
			m_apPlayer[nCnt] = CPlayer::Create(D3DXVECTOR3(-500.0f + (350.0f*nCnt), 0.0f, -150.0f), nCnt, CPlayer::TYPE_CAT);

		}
		else
		{ // ��L�ȊO

			// �G���g���[UI�̐�������
			m_apUI[nCnt] = CEntryUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + (300.0f * nCnt) - 450.0f, SCREEN_HEIGHT * 0.45f, 0.0f), nCnt, CPlayer::TYPE_RAT);

			// ���b�g�̐�������
			m_apPlayer[nCnt] = CPlayer::Create(D3DXVECTOR3(-500.0f + (350.0f*nCnt), 0.0f, -150.0f), nCnt, CPlayer::TYPE_RAT);

		}
		// ID���
		m_EntryId[nCnt] = nCnt;
	}

	// �G���g���[��ʂ̑������UI�̐���
	CEntryMessage::Create(POS_MESSAGEUI, POS_MESSAGEUI, SIZE_MESSAGEUI);

	// �G���g���[��ʂ̃����_���w��UI�̐���
	CEntryRandom::Create();

	// ������Ԃ�
	return S_OK;
}

//=============================================
//�I������
//=============================================
void CEntry::Uninit(void)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		if (m_apUI[nCnt] != nullptr)
		{ // �G���g���[UI�̏�� NULL ����Ȃ��ꍇ

			// �G���g���[UI�̏I������
			m_apUI[nCnt]->Uninit();
			m_apUI[nCnt] = nullptr;
		}
		m_apPlayer[nCnt] = nullptr;		// �l�Y�~�̏��
	}

	CManager::Get()->GetSound()->Stop();

	// �I������
	CScene::Uninit();
}

//======================================
//�X�V����
//======================================
void CEntry::Update(void)
{
	if (m_bEnter == false)
	{ // ���肵�Ă��Ȃ��ꍇ

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true ||
			CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, 0) == true ||
			CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, 1) == true ||
			CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, 2) == true ||
			CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, 3) == true)
		{ // ENTER�L�[���������ꍇ�܂���A�{�^�����������ꍇ
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_DECIDE);

			m_bEnter = true;

			for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
			{
				m_apPlayer[m_EntryId[nCnt]]->SetMove(D3DXVECTOR3(0.0f, 25.0f, 0.0f));
			}
		}

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_TAB) == true ||
			CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_Y, 0) == true ||
			CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_Y, 1) == true ||
			CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_Y, 2) == true ||
			CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_Y, 3) == true)
		{ // TAB�L�[���������܂��́AY�{�^�����������ꍇ

			// �l�R��ID�������_���ŕς���
			m_nCatIdx = rand() % MAX_PLAY;

			for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
			{
				if (nCnt == m_nCatIdx)
				{ // �l�R�����v���C���[�̂�

					// �l�R�ɐݒ肷��
					m_apUI[nCnt]->GetTeam()->SetType(CPlayer::TYPE_CAT);

				}
				else
				{ // ��L�ȊO

					// �l�Y�~�ɐݒ肷��
					m_apUI[nCnt]->GetTeam()->SetType(CPlayer::TYPE_RAT);

				}

				m_apPlayer[nCnt]->SetMove(D3DXVECTOR3(0.0f, 25.0f, 0.0f));

				if (m_nCatOldIdx != m_nCatIdx)
				{ // ID���בւ�����

					int nKeepID = 0;	// �ۑ��p����

					nKeepID = m_EntryId[m_nCatIdx];
					m_EntryId[m_nCatIdx] = m_EntryId[m_nCatOldIdx];
					m_EntryId[m_nCatOldIdx] = nKeepID;
					m_nCatOldIdx = m_nCatIdx;
				}
			}

			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_DECIDE);

			m_bEnter = true;
		}
	}

	if (m_bEnter == false)
	{ // �G���g���[���I����Ă��Ȃ��ꍇ
		for (int nCntPlayer = 0; nCntPlayer < 4; nCntPlayer++)
		{
			if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_D) == true ||
				CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_RIGHT, nCntPlayer) == true)
			{ // �E�L�[���������ꍇ
				CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_SELECT);

				// �l�R�����v���C���[��ݒ�
				m_nCatIdx = (m_nCatIdx + 1) % MAX_PLAY;

				for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
				{
					if (nCnt == m_nCatIdx)
					{ // �l�R�����v���C���[�̂�

						// �l�R�ɐݒ肷��
						m_apUI[nCnt]->GetTeam()->SetType(CPlayer::TYPE_CAT);

					}
					else
					{ // ��L�ȊO

						// �l�Y�~�ɐݒ肷��
						m_apUI[nCnt]->GetTeam()->SetType(CPlayer::TYPE_RAT);

					}
				}
			}

			if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_A) == true ||
				CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_LEFT, nCntPlayer) == true)
			{ // ���L�[���������ꍇ

				CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_SELECT);

				// �l�R�����v���C���[��ݒ�
				m_nCatIdx = (m_nCatIdx + MAX_PLAY - 1) % MAX_PLAY;

				for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
				{
					if (nCnt == m_nCatIdx)
					{ // �l�R�����v���C���[�̂�

						// �l�R�ɐݒ肷��
						m_apUI[nCnt]->GetTeam()->SetType(CPlayer::TYPE_CAT);

					}
					else
					{ // ��L�ȊO

						// �l�Y�~�ɐݒ肷��
						m_apUI[nCnt]->GetTeam()->SetType(CPlayer::TYPE_RAT);

					}
				}
			}

			if (m_nCatOldIdx != m_nCatIdx)
			{ // ID���בւ�����

				int nKeepID = 0;	// �ۑ��p����

				nKeepID = m_EntryId[m_nCatIdx];
				m_EntryId[m_nCatIdx] = m_EntryId[m_nCatOldIdx];
				m_EntryId[m_nCatOldIdx] = nKeepID;
				m_nCatOldIdx = m_nCatIdx;
			}

			for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
			{ // �ʒu�ݒ�&�ړ��ʃ��Z�b�g

				m_apPlayer[m_EntryId[nCnt]]->SetPos(D3DXVECTOR3(-500.0f + (350.0f * nCnt), 0.0f, -150.0f));	// �ʒu
				m_apPlayer[m_EntryId[nCnt]]->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));							// �ړ���
				m_apPlayer[m_EntryId[nCnt]]->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));								// ����

				// �W�����v�󋵂� false �ɂ���
				m_apPlayer[nCnt]->SetEnableJump(false);
			}
		}
	}
	else
	{

		for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
		{
			if (m_apPlayer[m_EntryId[nCnt]]->GetPos().y < -2.0f)
			{	// ���̍������Ⴍ�Ȃ����ꍇ

				m_apPlayer[m_EntryId[nCnt]]->SetPos(D3DXVECTOR3(-500.0f + (350.0f * nCnt), -2.0f, -150.0f));
				m_apPlayer[m_EntryId[nCnt]]->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

				// �W�����v�󋵂� false �ɂ���
				m_apPlayer[nCnt]->SetEnableJump(false);
			}
			else
			{	// ����ȊO

				// �ۑ��p����
				float KeepMove = m_apPlayer[m_EntryId[nCnt]]->GetMove().y;	// �W�����v��
				float KeepPos = m_apPlayer[m_EntryId[nCnt]]->GetPos().y;	// ���f���̍���(Y)

				m_apPlayer[m_EntryId[nCnt]]->SetPos(D3DXVECTOR3(-500.0f + (350.0f * nCnt), KeepPos, -150.0f));
				m_apPlayer[m_EntryId[nCnt]]->SetMove(D3DXVECTOR3(0.0f, KeepMove, 0.0f));
			}
			m_apPlayer[m_EntryId[nCnt]]->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		}
		m_nSceneCnt++;
		if (m_nSceneCnt > 80)
		{
			// �Q�[�����[�h�ɑJ��
			CManager::Get()->GetFade()->SetFade(CScene::MODE_TUTORIAL);
		}

	}
	// �����_���[�̍X�V
	CManager::Get()->GetRenderer()->Update();
}

//======================================
//�`�揈��
//======================================
void CEntry::Draw(void)
{

}

//======================================
// �l�R�S���̎擾����
//======================================
int CEntry::GetCatIdx(void)
{
	// �l�R�̃C���f�b�N�X��Ԃ�
	return m_nCatIdx;
}