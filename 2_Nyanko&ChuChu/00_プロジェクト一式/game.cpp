//============================================
//
// �Q�[���̃��C������[game.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "input.h"
#include "game.h"
#include "fade.h"
#include "file.h"
#include "renderer.h"
#include "log.h"

#include "pause.h"
#include "debugproc.h"
#include "sound.h"

#include "objectElevation.h"
#include "map.h"
#include "skybox.h"
#include "rat.h"
#include "Cat.h"
#include "game_timer.h"
#include "edit.h"
#include "weapon_selectUI.h"
#include "block.h"
#include "countdown.h"
#include "item.h"
#include "resurrection_fan.h"
#include "player.h"
#include "entry.h"
#include "game_finish.h"

#include "obstacle_manager.h"
#include "chara_infoUI.h"
#include "screen_frame.h"

//--------------------------------------------
// �������O���
//--------------------------------------------
namespace
{
	const int MAX_ITEM_POS = 3;					// �A�C�e���o���ʒu�̍ő吔

	// �v���C���[UI�̈ʒu
	const D3DXVECTOR3 PLAYERUI_POS[MAX_PLAY] =
	{
		D3DXVECTOR3(90.0f, SCREEN_HEIGHT * 0.5f - 80.0f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH - 90.0f, SCREEN_HEIGHT * 0.5f - 80.0f, 0.0f),
		D3DXVECTOR3(90.0f, SCREEN_HEIGHT - 80.0f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH - 90.0f, SCREEN_HEIGHT - 80.0f, 0.0f),
	};

	// �A�C�e���̏o���ʒu
	const D3DXVECTOR3 ITEM_SPAWN_POS[MAX_ITEM_POS] =
	{
		D3DXVECTOR3(-1100.0f, 0.0f, 100.0f),
		D3DXVECTOR3(1000.0f, 0.0f, 450.0f),
		D3DXVECTOR3(1250.0f, 0.0f, -800.0f),
	};

	// �ǂݍ��ރt�@�C���̔ԍ�(�u���b�N)
	const CFile::TYPE FILETYPE_BLOCK[MAP_TYPE] =
	{
		CFile::TYPE_MAP_BLOCK1,
		CFile::TYPE_MAP_BLOCK2,
		CFile::TYPE_MAP_BLOCK3,
	};

	// �ǂݍ��ރt�@�C���̔ԍ�(��Q��)
	const CFile::TYPE FILETYPE_OBSTACLE[MAP_TYPE] =
	{
		CFile::TYPE_MAP_OBSTACLE1,
		CFile::TYPE_MAP_OBSTACLE2,
		CFile::TYPE_MAP_OBSTACLE3,
	};

	// �l�R�̏����ʒu
	const D3DXVECTOR3 FILETYPE_CATPOS[MAP_TYPE] =
	{
		D3DXVECTOR3(1200.0f, 0.0f, 700.0f),
		D3DXVECTOR3(-1200.0f,0.0f,850.0f),
		D3DXVECTOR3(-200.0f,0.0f,-600.0f),
	};

	// �l�Y�~�̏����ʒu
	const D3DXVECTOR3 FILETYPE_RATPOS[MAP_TYPE] =
	{
		D3DXVECTOR3(-500.0f, 0.0f, -300.0f),
		D3DXVECTOR3(1000.0f,0.0f,-650.0f),
		D3DXVECTOR3(1450.0f,0.0f,200.0f),
	};

	const int TRANS_COUNT = 80;				// �J�ڃJ�E���g
	const int START_COUNT = 30;				// �J�n�̃J�E���g
	const int MAX_ITEM = 3;					// �A�C�e���̍ő吔
	const int ATEMSPAWN_CONT = (60 - 25) / MAX_ITEM * 60;	// �A�C�e���o���J�E���g
}

//--------------------------------------------
// �ÓI�����o�ϐ��錾
//--------------------------------------------
CPause* CGame::m_pPause = nullptr;							// �|�[�Y�̏��
CPlayer* CGame::m_apPlayer[MAX_PLAY] = {};					// �v���C���[�̏��
CGame::STATE CGame::m_GameState = CGame::STATE_START;		// �Q�[���̐i�s���
int CGame::m_nFinishCount = 0;								// �I���J�E���g
int CGame::m_nItemSpawnCount = 0;							// �A�C�e���o���J�E���^�[
int CGame::m_nNumItem = 0;									// �A�C�e���̐�
CGameFinish* CGame::m_pFinish = nullptr;					// �t�B�j�b�V���̏��
bool CGame::m_bCountDown = false;							// �J�E���g�_�E�����g�p����Ă��邩
bool CGame::m_bItemSpawn = false;							// �A�C�e�����o�����Ă��邩�ǂ���
int CGame::m_nMapNumber = 0;								// �A�C�e�����o�����Ă��邩�ǂ���

// �f�o�b�O��
#ifdef _DEBUG
CEdit* CGame::m_pEdit = nullptr;							// �G�f�B�b�g�̏��
bool CGame::m_bEdit = false;								// �G�f�B�b�g��
#endif

//=========================================
// �R���X�g���N�^
//=========================================
CGame::CGame() : CScene(TYPE_SCENE, PRIORITY_BG)
{
	// �S�Ă̒l���N���A����
	m_pPause = nullptr;			// �|�[�Y
	m_pFinish = nullptr;		// �t�B�j�b�V��
	m_nFinishCount = 0;			// �I���J�E���g
	m_nItemSpawnCount = 0;		// �A�C�e���o���J�E���g
	m_nNumItem = 0;				// �A�C�e���̐�
	m_GameState = STATE_START;	// ���
	m_bCountDown = false;
	m_bItemSpawn = false;		// �A�C�e�����o�����Ă��邩�ǂ���
	m_nMapNumber = 0;

	for (int nCntPlay = 0; nCntPlay < MAX_PLAY; nCntPlay++)
	{
		m_apPlayer[nCntPlay] = nullptr;		// �l�Y�~�̏��
	}

// �f�o�b�O��
#ifdef _DEBUG
	m_pEdit = nullptr;			// �G�f�B�b�g
	m_bEdit = false;			// �G�f�B�b�g��
#endif
}

//=========================================
// �f�X�g���N�^
//=========================================
CGame::~CGame()
{

}

//=========================================
//����������
//=========================================
HRESULT CGame::Init(void)
{
	// �V�[���̏�����
	CScene::Init();

	// ��ʂ̘g�̐���
	CScreenFrame::Create();

	// �e�L�X�g�ǂݍ��ݏ���
	CElevation::TxtSet();

	// ���b�V���̓ǂݍ��ݏ���
	//CMesh::TxtSet();

	// �}�b�v�̔ԍ��������_���ŎZ�o
	m_nMapNumber = rand() % MAP_TYPE;

	// �}�b�v�̏������[�h����
	CManager::Get()->GetFile()->FalseSuccess();

	//CObstacle::Create(D3DXVECTOR3(300.0f, 0.0f, -300.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_TV);
	//CObstacle::Create(D3DXVECTOR3(-800.0f, 0.0f, 200.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_CUP);
	//CObstacle::Create(D3DXVECTOR3(-800.0f, 0.0f, 400.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_CUP);
	//CObstacle::Create(D3DXVECTOR3(-800.0f, 0.0f, 600.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_CUP);
	//CObstacle::Create(D3DXVECTOR3(200.0f, 0.0f, 200.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_PIN);
	//CObstacle::Create(D3DXVECTOR3(200.0f, 0.0f, 300.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_PIN);
	//CObstacle::Create(D3DXVECTOR3(200.0f, 0.0f, 400.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_PIN);
	//CObstacle::Create(D3DXVECTOR3(200.0f, 0.0f, 500.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_PIN);

	CManager::Get()->GetFile()->Load(FILETYPE_OBSTACLE[m_nMapNumber]);
	CManager::Get()->GetFile()->Load(FILETYPE_BLOCK[m_nMapNumber]);
	//CManager::Get()->GetFile()->Load(CFile::TYPE_MAP_BLOCKSAMPLE);
	//CManager::Get()->GetFile()->Load(CFile::TYPE_MAP_OBSTACLESAMPLE);

	// �}�b�v�̐ݒ菈��
	CManager::Get()->GetFile()->SetMap();

	// �J�E���g�_�E���̐�������
	CCountdown::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(200.0f, 250.0f, 0.0f), START_COUNT, false);

	// ���b�V���̃e�L�X�g�ǂݍ���
	//CMesh::TxtSet();

	// �X�J�C�{�b�N�X�̐�������
	CSkyBox::Create();

	//�}�b�v�̐���
	CMap::Create();

#ifdef _DEBUG	//��Q���e�X�g�p

	//CObstacle *pObstacle = NULL;

	//// �����o�̐�������
	//CObstacle::Create(D3DXVECTOR3(-280.0f, 200.0f, -200.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CObstacle::TYPE::TYPE_GARBAGECAN);
	//CObstacle::Create(D3DXVECTOR3(600.0f, 0.0f, 400.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_ROOMBA);

	//// �Ђ��̐�������
	//CObstacle::Create(D3DXVECTOR3(-600.0f, 650.0f, 0.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_HIMO);

	//// �X�s�[�J�[�̐�������
	//CObstacle::Create(D3DXVECTOR3(900.0f, 0.0f, 900.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.25f, 0.0f), CObstacle::TYPE::TYPE_SPEAKER);

	//pObstacle = CObstacle::Create(D3DXVECTOR3(1000.0f, 0.0f, 900.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_SPEAKER);
	//pObstacle->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f));

	//// ���[�h�̐�������
	//pObstacle = CObstacle::Create(D3DXVECTOR3(400.0f, 0.0f, -600.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_LEASH);
	//pObstacle->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));

	//// ��e�̐�������
	//CObstacle::Create(D3DXVECTOR3(-200.0f, 200.0f, -120.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_PIN);

	//// ��@�̐�������
	//CObstacle::Create(D3DXVECTOR3(0.0f, 200.0f, 900.0f), NONE_D3DXVECTOR3, CObstacle::TYPE::TYPE_FAN);

	//// �R�b�v�̐�������
	//CObstacle::Create(D3DXVECTOR3(-200.0f, 200.0f, 100.0f), NONE_D3DXVECTOR3, CObstacle::TYPE::TYPE_CUP);
	//pObstacle = CObstacle::Create(D3DXVECTOR3(400.0f, 200.0f, 100.0f), D3DXVECTOR3(0.0f, D3DX_PI * 1.0f, 0.0f), CObstacle::TYPE::TYPE_CUP);
	//pObstacle->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 1.0f, 0.0f));

	////�S�~���̐���
	//CObstacle::Create(D3DXVECTOR3(-100.0f, 200.0f, -500.0f), NONE_D3DXVECTOR3, CObstacle::TYPE::TYPE_GARBAGECAN);

	//CObstacle::Create(D3DXVECTOR3(-400.0f, 0.0f, 400.0f), NONE_D3DXVECTOR3, CObstacle::TYPE::TYPE_PETBOTTLE);
	//
	//CObstacle::Create(D3DXVECTOR3(-400.0f, 0.0f, 400.0f), NONE_D3DXVECTOR3, CObstacle::TYPE::TYPE_TOYCAR);

	//CObstacle::Create(D3DXVECTOR3(-200.0f, 0.0f, 100.0f), NONE_D3DXVECTOR3, CObstacle::TYPE::TYPE_REDKATEN);

	//// �Ђ��̐�������
	//CObstacle::Create(D3DXVECTOR3(-600.0f, 650.0f, 0.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_HIMO);

#endif // _DEBUG

	{ // �L�����̐�������

		// �l�R�̃C���f�b�N�X���擾����
		int nCat = CEntry::GetCatIdx();

		// �l�Y�~�̐���
		for (int nCntPlay = 0; nCntPlay < MAX_PLAY; nCntPlay++)
		{
			if (nCntPlay == nCat)
			{ // �l�R�S���̃v���C���[�̏ꍇ

				// �v���C���[�̐���
				m_apPlayer[nCntPlay] = CPlayer::Create(FILETYPE_CATPOS[m_nMapNumber], nCntPlay, CPlayer::TYPE_CAT);
			}
			else
			{ // ��L�ȊO

				// �v���C���[�̐���
				m_apPlayer[nCntPlay] = CPlayer::Create(D3DXVECTOR3(FILETYPE_RATPOS[m_nMapNumber].x, FILETYPE_RATPOS[m_nMapNumber].y, 100.0f * nCntPlay + FILETYPE_RATPOS[m_nMapNumber].z), nCntPlay, CPlayer::TYPE_RAT);
			}
		}
	}

	// ��������
	CGameTime::Create();
	m_pFinish = CGameFinish::Create();

	// �L�����N�^�[UI�̐�������
	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		CCharaInfoUI::Create(PLAYERUI_POS[nCnt], nCnt, m_apPlayer[nCnt]->GetType());
	}

	//// ����I��UI�𐶐�
	//CWeaponSelectUI::Create();

	// ���̏�����
	m_nFinishCount = 0;				// �I���J�E���g
	m_GameState = STATE_START;		// ���

	// ������Ԃ�
	return S_OK;
}

//=============================================
//�I������
//=============================================
void CGame::Uninit(void)
{
	// �|�C���^�� NULL �ɂ���
	m_pPause = nullptr;			// �|�[�Y
	m_pFinish = nullptr;		// �t�B�j�b�V��

	for (int nCntPlay = 0; nCntPlay < MAX_PLAY; nCntPlay++)
	{
		m_apPlayer[nCntPlay] = nullptr;		// �l�Y�~�̏��
	}

	// �I���J�E���g������������
	m_nFinishCount = 0;

	// �Đ����̃T�E���h�̒�~
	CManager::Get()->GetSound()->Stop();

	// �I������
	CScene::Uninit();
}

//======================================
//�X�V����
//======================================
void CGame::Update(void)
{

// �f�o�b�O��
#ifdef _DEBUG
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_F7) == true)
	{ // F7�L�[���������ꍇ

		// �G�f�B�b�g�󋵂����ւ���
		m_bEdit = m_bEdit ? false : true;

		if (m_bEdit == true)
		{ // �G�f�B�b�g�󋵂� true �̏ꍇ

			if (m_pEdit == nullptr)
			{ // �G�f�B�b�g�󋵂� NULL �̏ꍇ

				// �G�f�B�b�g�̐�������
				m_pEdit = CEdit::Create();
			}
		}
		else
		{ // ��L�ȊO

			if (m_pEdit != nullptr)
			{ // �G�f�B�b�g�󋵂� NULL ����Ȃ��ꍇ

				// �I������
				m_pEdit->Uninit();
				m_pEdit = nullptr;
			}
			else
			{ // ��L�ȊO

				// ��~
				assert(false);
			}
		}
	}

#endif

	switch (m_GameState)
	{
	case CGame::STATE_START:

		break;

	case CGame::STATE_PLAY:

		if (m_pPause != nullptr)
		{ // �|�[�Y�� NULL ����Ȃ��Ƃ�

			if (m_pPause->GetPause() == false)
			{ // �|�[�Y��Ԃ���Ȃ��Ƃ�

				// �A�C�e���o��
				ItemSpawn();
			}
		}

		// �|�[�Y����
		Pause();

		break;

	case CGame::STATE_RAT_WIN:

		// �J�ڏ���
		Transition();

		for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
		{
			if (m_apPlayer[nCnt] != nullptr)
			{ // �v���C���[�� NULL ����Ȃ��ꍇ

				// �J�����̍X�V����
				m_apPlayer[nCnt]->CameraUpdate();
			}
		}

		break;

	case CGame::STATE_CAT_WIN:

		// �J�ڏ���
		if (m_pFinish != nullptr)
		{
			m_pFinish->SetFinish(true);
		}
		Transition();

		for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
		{
			if (m_apPlayer[nCnt] != nullptr)
			{ // �v���C���[�� NULL ����Ȃ��ꍇ

				// �J�����̍X�V����
				m_apPlayer[nCnt]->CameraUpdate();
			}
		}

		break;

	default:

		// ��~
		assert(false);

		break;
	}

#ifdef _DEBUG

	if (m_bEdit == true)
	{ // �G�f�B�b�g�󋵂� true �̏ꍇ

		if (m_pEdit != nullptr)
		{ // �G�f�B�b�g�� NULL ����Ȃ��ꍇ

			// �G�f�B�b�g�̍X�V����
			m_pEdit->Update();
		}

		for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
		{
			// ���S���ʏ���
			CObject::DeathDecision(nCnt);
		}

		if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_F9) == true)
		{ // F9�L�[���������ꍇ

			// �����Z�[�u����
			CManager::Get()->GetFile()->Save(FILETYPE_OBSTACLE[m_nMapNumber]);
			CManager::Get()->GetFile()->Save(FILETYPE_BLOCK[m_nMapNumber]);
			//CManager::Get()->GetFile()->Save(CFile::TYPE_MAP_BLOCKSAMPLE);
			//CManager::Get()->GetFile()->Save(CFile::TYPE_MAP_OBSTACLESAMPLE);
		}
	}
	else
	{ // ��L�ȊO

		if (CManager::Get()->GetRenderer() != nullptr)
		{ // �����_���[�� NULL ����Ȃ��ꍇ

			// �����_���[�̍X�V
			CManager::Get()->GetRenderer()->Update();
		}
	}

#else

	if (CManager::Get()->GetRenderer() != nullptr)
	{ // �����_���[�� NULL ����Ȃ��ꍇ

		// �����_���[�̍X�V
		CManager::Get()->GetRenderer()->Update();
	}

#endif
		
	CManager::Get()->GetDebugProc()->Print("��ԁF%d", m_GameState);
}

//======================================
//�`�揈��
//======================================
void CGame::Draw(void)
{

}

//======================================
// ���̐ݒ菈��
//======================================
void CGame::SetData(const MODE mode)
{
	// ���̐ݒ菈��
	CScene::SetData(mode);

	if (m_pPause == nullptr)
	{ // �|�[�Y�ւ̃|�C���^�� NULL �̏ꍇ

		// �|�[�Y�̐�������
		m_pPause = CPause::Create();
	}

	// �X�^�[�g��Ԃɂ���
	m_GameState = STATE_START;

	// ���̏�����
	m_nFinishCount = 0;				// �I���J�E���g
}

//======================================
// �|�[�Y����
//======================================
void CGame::Pause(void)
{
	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_P) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_BACK, 0) == true ||
		CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_START, 0) == true)
	{ // P�L�[���������ꍇ

		if (CManager::Get()->GetFade()->GetFade() == CFade::FADE_NONE)
		{ // �t�F�[�h������Ԃ��A�I���ȊO�̏ꍇ

			if (m_pPause->GetPause() == false)
			{ // �|�[�Y�� false �������ꍇ

				// �|�[�Y�󋵂� true �ɂ���
				m_pPause->SetPause(true);
			}
			else
			{ // �|�[�Y�� true �������ꍇ

				// �|�[�Y�󋵂� false �ɂ���
				m_pPause->SetPause(false);
			}

			// ���艹��炷
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_DECIDE);
		}
	}
}

//======================================
// �J�ڏ���
//======================================
void CGame::Transition(void)
{
	// �I���J�E���g�����Z����
	m_nFinishCount++;

	if (m_nFinishCount % TRANS_COUNT == 0)
	{ // �I���J�E���g����萔�𒴂����ꍇ

		// ���U���g�ɑJ�ڂ���
		CManager::Get()->GetFade()->SetFade(CScene::MODE_RESULT);
	}
}

//======================================
// �A�C�e���o������
//======================================
void CGame::ItemSpawn(void)
{
	if (m_bItemSpawn == false)
	{ // �A�C�e�����o������ĂȂ�������

		m_nItemSpawnCount++;		// �A�C�e���o���J�E���g���Z
	}
	else if (m_bItemSpawn == true)
	{ // �A�C�e�����o�����Ă���

		m_nItemSpawnCount = 1;		// �J�E���^�[������

		CManager::Get()->GetDebugProc()->Print("\n-----------------------------------------------�A�C�e���o����-----------------------------------------------\n", m_GameState);
	}

	if ((m_nItemSpawnCount % ATEMSPAWN_CONT) == 0 && m_nNumItem < MAX_ITEM)
	{ // ��莞�Ԍo����

		int nItemPos;			// �A�C�e���̏o���ʒu�I��

		nItemPos = rand() % MAX_ITEM_POS;		// �A�C�e���̏o���ʒu�̐ݒ�

		// �l�Y�~�߂�̐���
		CItem::Create(ITEM_SPAWN_POS[nItemPos], CItem::TYPE::TYPE_MOUSETRAP);

		m_nNumItem++;				// �A�C�e���̐����Z

		m_nItemSpawnCount = 0;		// �J�E���^�[������
		m_bItemSpawn = true;		// �A�C�e�����o�����Ă����Ԃɂ���
	}
}


//======================================
// �|�[�Y�̎擾����
//======================================
CPause* CGame::GetPause(void)
{
	// �|�[�Y�̏���Ԃ�
	return m_pPause;
}

//======================================
// �Q�[���̐i�s��Ԃ̐ݒ菈��
//======================================
void CGame::SetState(const STATE state)
{
	// �Q�[���̐i�s��Ԃ�ݒ肷��
	m_GameState = state;
}

//======================================
// �Q�[���̐i�s��Ԃ̎擾����
//======================================
CGame::STATE CGame::GetState(void)
{
	// �Q�[���̐i�s��Ԃ�Ԃ�
	return m_GameState;
}

//======================================
// �v���C���[�̎擾����
//======================================
CPlayer* CGame::GetPlayer(const int nID)
{
	if (nID < MAX_PLAY)
	{ // �C���f�b�N�X����薢���̏ꍇ

		// �v���C���[�̏����擾����
		return m_apPlayer[nID];
	}
	else
	{ // ��L�ȊO

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}
}

//======================================
// �|�[�Y��NULL������
//======================================
void CGame::DeletePause(void)
{
	// �|�[�Y�̃|�C���^�� NULL �ɂ���
	m_pPause = nullptr;
}

//======================================
// �l�Y�~��NULL������
//======================================
void CGame::DeletePlayer(int nIdx)
{
	if (nIdx < MAX_PLAY)
	{ // �ԍ����ő吔�����̏ꍇ

		// �v���C���[�̃|�C���^�� NULL �ɂ���
		m_apPlayer[nIdx] = nullptr;
	}
	else
	{ // ��L�ȊO

		// ��~
		assert(false);
	}
}

// �f�o�b�O��
#ifdef _DEBUG
//======================================
// �G�f�B�b�g�̎擾����
//======================================
CEdit* CGame::GetEdit(void)
{
	// �G�f�B�b�g�̏���Ԃ�
	return m_pEdit;
}

//======================================
// �G�f�B�b�g�󋵂̎擾����
//======================================
bool CGame::IsEdit(void)
{
	// �G�f�B�b�g�󋵂�Ԃ�
	return m_bEdit;
}

#endif