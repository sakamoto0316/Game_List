//============================================
//
// �}�l�[�W���[�̃��C������[manager.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "result.h"
#include "input.h"
#include "fade.h"
#include "Objectmesh.h"

#include "entry.h"
#include "file.h"
#include "camera.h"
#include "skybox.h"
#include "result_letter.h"
#include "objectElevation.h"
#include "player.h"
#include "confetti.h"
#include "sound.h"
#include "entry_BG.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define MAX_CONFETTI_X		(10)		// ������̍ő吔X
#define MAX_CONFETTI_Y		(20)		// ������̍ő吔Y
#define GRAVITY_CONFETTI	(15 + 7)	// ������̏d��
#define LIFE_CONFETTI		(100)		// ������̎���
#define INTERVAL_CONFETTI	(120.0f)	// ������̏o���Ԋu

//--------------------------------------------
// �ÓI�����o�ϐ��錾
//--------------------------------------------
CPlayer* CResult::m_apPlayer[MAX_PLAY] = {};							// �l�Y�~�̏��
int CResult::m_nGameState = 0;			// �Q�[���̏��

//=========================================
// �R���X�g���N�^
//=========================================
CResult::CResult() : CScene(TYPE_SCENE, PRIORITY_BG)
{

}

//=========================================
// �f�X�g���N�^
//=========================================
CResult::~CResult()
{

}

//=========================================
//����������
//=========================================
HRESULT CResult::Init(void)
{
	// �V�[���̏�����
	CScene::Init();

	// �X�J�C�{�b�N�X�̐�������
	CSkyBox::Create();

	// �w�i�̐�������
	CEntryBG::Create();

	// �e�L�X�g�ǂݍ��ݏ���
	CElevation::TxtSet();

	// �Q�[���̏�Ԃ��擾����
	m_nGameState = CGame::GetState();

	// 3D�e�L�X�g����
	if (m_nGameState == CGame::STATE_CAT_WIN)
	{ // �l�R����������

		CResultLetter::Create(D3DXVECTOR3(0.0f, 370.0f, 0.0f), CXFile::TYPE_WINCAT_TEXT);		// �˂��̂���
	}
	else if (m_nGameState == CGame::STATE_RAT_WIN)
	{ // �l�Y�~����������

		CResultLetter::Create(D3DXVECTOR3(0.0f, 370.0f, 0.0f), CXFile::TYPE_WINRAT_TEXT);		// �˂��݂̂���
	}

	// �������𗬂�
	CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_VICTORY);
	
	int nCatIdx = CEntry::GetCatIdx();// �l�R�̃C���f�b�N�X���擾����
	int nRatCount = 0;		// �l�Y�~�̃J�E���g

	// �l�Y�~�̐���
	for (int nCntRat = 0; nCntRat < MAX_PLAY; nCntRat++)
	{
		if (nCntRat == nCatIdx)
		{ // �l�R�̃C���f�b�N�X�̏ꍇ

			if (m_nGameState == CGame::STATE_CAT_WIN)
			{ // �l�R���������ꍇ

				// �l�R�̐���
				m_apPlayer[nCntRat] = CPlayer::Create(D3DXVECTOR3(-300.0f, 0.0f, -200.0f), nCntRat, CPlayer::TYPE_CAT);
			}
			else
			{ // ��L�ȊO

				// �l�R�̐���
				m_apPlayer[nCntRat] = CPlayer::Create(D3DXVECTOR3(-300.0f, 0.0f, -100.0f), nCntRat, CPlayer::TYPE_CAT);
			}
		}
		else
		{ // ��L�ȊO

			if (m_nGameState == CGame::STATE_RAT_WIN)
			{ // �l�Y�~���������ꍇ

				// �l�Y�~�̐���
				m_apPlayer[nCntRat] = CPlayer::Create(D3DXVECTOR3(150.0f * nRatCount + 100.0f, 0.0f, -280.0f), nCntRat, CPlayer::TYPE_RAT);
			}
			else
			{ // ��L�ȊO

				// �l�Y�~�̐���
				m_apPlayer[nCntRat] = CPlayer::Create(D3DXVECTOR3(150.0f * nRatCount + 100.0f, 0.0f, -100.0f), nCntRat, CPlayer::TYPE_RAT);
			}

			// �l�Y�~�̃J�E���g�����Z����
			nRatCount++;
		}
	}

	// ������̐���
	CreateConfetti();

	// ������Ԃ�
	return S_OK;
}

//=============================================
//�I������
//=============================================
void CResult::Uninit(void)
{
	// �j������
	Release();
}

//======================================
//�X�V����
//======================================
void CResult::Update(void)
{

#ifdef _DEBUG	// ������e�X�g�p

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_M) == true)
	{ // M�L�[���������Ƃ�

		// ������̐���
		CreateConfetti();
	}

#endif

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A,0) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_START, 0) == true)
	{ // ENTER�L�[���������ꍇ

		// �����L���O�ɑJ�ڂ���
		CManager::Get()->GetFade()->SetFade(CScene::MODE_TITLE);

		// ���̐�̏������s��Ȃ�
		return;
	}

	if (CManager::Get()->GetRenderer() != nullptr)
	{ // �����_���[�� NULL ����Ȃ��ꍇ

		// �X�V����
		CManager::Get()->GetRenderer()->Update();
	}
}

//======================================
//�`�揈��
//======================================
void CResult::Draw(void)
{

}

//======================================
//�Q�[���̏��擾����
//======================================
int CResult::GetState(void)
{
	return m_nGameState;
}

//======================================
//������̐�������
//======================================
void CResult::CreateConfetti(void)
{
	// ���[�J���ϐ�
	D3DXCOLOR color;		// �F
	D3DXVECTOR3 rotMove;	// ����
	D3DXVECTOR3 size;		// �T�C�Y
	float fGravity;			// �d��
	float fPosX = 0.0f;			// �����lX

	// �ʒu�̐ݒ�
	switch (m_nGameState)
	{
	case CGame::STATE_CAT_WIN:		// �˂��̂���

		fPosX = 0.0f;

		break;

	case CGame::STATE_RAT_WIN:		// �˂��݂̂���

		fPosX = 1000.0f;

		break;

	default:

		assert(false);

		break;
	}

	for (int nCntConfettiX = 0; nCntConfettiX < MAX_CONFETTI_X; nCntConfettiX++)
	{ // X��
		for (int nCntConfettiY = 0; nCntConfettiY < MAX_CONFETTI_Y; nCntConfettiY++)
		{ // Y��

			// ����
			rotMove.x = rand() % 10 * 0.01f;
			rotMove.y = rand() % 10 * 0.01f;
			rotMove.z = rand() % 10 * 0.01f;

			// �F
			color.r = rand() % 10 * 0.1f;
			color.g = rand() % 10 * 0.1f;
			color.b = rand() % 10 * 0.1f;

			// �T�C�Y
			size.x = float(rand() % 17 + 10);
			size.y = float(rand() % 17 + 10);
			size.z = float(rand() % 17 + 10);

			// �d��
			fGravity = float(rand() % GRAVITY_CONFETTI);

			// �����ᐶ��
			CConfetti::Create(D3DXVECTOR3(fPosX + (nCntConfettiX * -INTERVAL_CONFETTI),
				300.0f + (nCntConfettiY * INTERVAL_CONFETTI),
				-230.0f),
				D3DXVECTOR3(size.x, size.y, size.z),		// �T�C�Y
				D3DXVECTOR3(rotMove.x, rotMove.y, rotMove.z),	// ����
				fGravity,							// �d��
				D3DXCOLOR(color.r, color.g, color.b, 1.0f),	// �F
				LIFE_CONFETTI + (LIFE_CONFETTI * nCntConfettiY));								// ����
		}
	}
}