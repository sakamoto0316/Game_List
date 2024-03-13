//============================================
//
// �`���[�g���A���̃��C������[game.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "input.h"
#include "tutorial.h"
#include "fade.h"
#include "file.h"
#include "renderer.h"
#include "log.h"
#include "texture.h"

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

#include "answer.h"
#include "explanation.h"
#include "block_manager.h"

//--------------------------------------------
// �������O���
//--------------------------------------------
namespace
{
	const D3DXVECTOR3 PLAYERUI_POS[MAX_PLAY] =								// �v���C���[UI�̈ʒu
	{
		D3DXVECTOR3(90.0f, SCREEN_HEIGHT * 0.5f - 80.0f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH - 90.0f, SCREEN_HEIGHT * 0.5f - 80.0f, 0.0f),
		D3DXVECTOR3(90.0f, SCREEN_HEIGHT - 80.0f, 0.0f),
		D3DXVECTOR3(SCREEN_WIDTH - 90.0f, SCREEN_HEIGHT - 80.0f, 0.0f),
	};
	const int TRANS_COUNT = 80;				// �J�ڃJ�E���g
}

#define SKIP_POS	(D3DXVECTOR3(1080.0f,50.0f,0.0f))					//�X�L�b�v�̈ʒu
#define SKIP_SIZE	(D3DXVECTOR3(200.0f,50.0f,0.0f))					//�X�L�b�v�̃T�C�Y
#define GAUGE_POS	(D3DXVECTOR3(880.0f,50.0f,0.0f))					//�Q�[�W�̈ʒu
#define GAUGE_SIZE	(D3DXVECTOR3(0.0f,50.0f,0.0f))						//�Q�[�W�̃T�C�Y

//--------------------------------------------
// �ÓI�����o�ϐ��錾
//--------------------------------------------
CPlayer* CTutorial::m_apPlayer[MAX_PLAY] = {};						// �v���C���[�̏��
CTutorial::STATE CTutorial::m_GameState = CTutorial::STATE_START;	// �`���[�g���A���̐i�s���
int CTutorial::m_nFinishCount = 0;									// �I���J�E���g
CTutorial::TUTORIAL CTutorial::m_Tutorial = TUTORIAL_MOVE;			// �`���[�g���A���̍���
bool CTutorial::m_bPlay = false;									// �`���[�g���A���̃v���C�����ۂ�
CAnswer*  CTutorial::m_pAnswer = nullptr;							// �ԓ����A�N�V����
CExplanation*  CTutorial::m_pExplanation = nullptr;					// ����
bool CTutorial::m_MultiAction = false;								// �A�g�N���̏��
CObject2D *CTutorial::m_apSkip[SKIP_MAX] = {};						// �X�L�b�v��UI
float CTutorial::m_fSkipAlpha = D3DX_PI;							// �X�L�b�v�̕s�����x
float CTutorial::m_fGauge = 0.0f;									// �Q�[�W�̐��l
float CTutorial::m_fGaugeMax = SKIP_SIZE.x;							// �Q�[�W�̍ő�l

// �f�o�b�O��
#ifdef _DEBUG
CEdit* CTutorial::m_pEdit = nullptr;								// �G�f�B�b�g�̏��
bool CTutorial::m_bEdit = false;									// �G�f�B�b�g��
#endif

//=========================================
// �R���X�g���N�^
//=========================================
CTutorial::CTutorial() : CScene(TYPE_SCENE, PRIORITY_BG)
{
	// �S�Ă̒l���N���A����
	m_nFinishCount = 0;			// �I���J�E���g
	m_GameState = STATE_START;	// ���
	m_Tutorial = TUTORIAL_MOVE;
	m_bPlay = false;
	m_pAnswer = nullptr;
	m_pExplanation = nullptr;
	m_MultiAction = false;

	for (int nCntPlay = 0; nCntPlay < MAX_PLAY; nCntPlay++)
	{
		m_apPlayer[nCntPlay] = nullptr;		// �l�Y�~�̏��
	}
	for (int nCnt = 0; nCnt < SKIP_MAX; nCnt++)
	{
		m_apSkip[nCnt] = NULL;
	}

	m_fSkipAlpha = D3DX_PI;

	// �f�o�b�O��
#ifdef _DEBUG
	m_pEdit = nullptr;			// �G�f�B�b�g
	m_bEdit = false;			// �G�f�B�b�g��
#endif
}

//=========================================
// �f�X�g���N�^
//=========================================
CTutorial::~CTutorial()
{

}

//=========================================
//����������
//=========================================
HRESULT CTutorial::Init(void)
{
	// �V�[���̏�����
	CScene::Init();

	// �e�L�X�g�ǂݍ��ݏ���
	CElevation::TxtSet();

	// ���b�V���̓ǂݍ��ݏ���
	//CMesh::TxtSet();

	// �}�b�v�̏������[�h����
	CManager::Get()->GetFile()->FalseSuccess();
	CManager::Get()->GetFile()->Load(CFile::TYPE_TUTORIAL_DEFULT);
	//CManager::Get()->GetFile()->Load(CFile::TYPE_TUTORIAL_TABLE);
	//CManager::Get()->GetFile()->Load(CFile::TYPE_TUTORIAL_KILL);
	//CManager::Get()->GetFile()->Load(CFile::TYPE_TUTORIAL_ACTION);

	// �}�b�v�̐ݒ菈��
	CManager::Get()->GetFile()->SetMap();

	//// �J�E���g�_�E���̐�������
	//CCountdown::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(200.0f, 250.0f, 0.0f), 5);

	// ���b�V���̃e�L�X�g�ǂݍ���
	//CMesh::TxtSet();

	// �X�J�C�{�b�N�X�̐�������
	CSkyBox::Create();

	//�}�b�v�̐���
	CMap::Create();

#ifdef _DEBUG	//��Q���e�X�g�p

	//CObstacle *pObstacle = NULL;

	//// �����o�̐�������
	//CObstacle::Create(D3DXVECTOR3(-600.0f, 0.0f, -400.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_ROOMBA);
	//CObstacle::Create(D3DXVECTOR3(600.0f, 0.0f, 400.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_ROOMBA);

	//// �Ђ��̐�������
	//CObstacle::Create(D3DXVECTOR3(-600.0f, 650.0f, 0.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_HIMO);

	//// �X�s�[�J�[�̐�������
	//pObstacle = CObstacle::Create(D3DXVECTOR3(900.0f, 0.0f, 900.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_SPEAKER);
	//pObstacle->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.25f, 0.0f));

	//pObstacle = CObstacle::Create(D3DXVECTOR3(1000.0f, 0.0f, 900.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_SPEAKER);
	//pObstacle->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f));

	//// ���[�h�̐�������
	//pObstacle = CObstacle::Create(D3DXVECTOR3(400.0f, 0.0f, -600.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), CObstacle::TYPE_LEASH);

	//// ��e�̐�������
	//CObstacle::Create(D3DXVECTOR3(-200.0f, 200.0f, -120.0f), NONE_D3DXVECTOR3, CObstacle::TYPE_PIN);

	//// ��@�̐�������
	//CObstacle::Create(D3DXVECTOR3(100.0f, 0.0f, 900.0f), NONE_D3DXVECTOR3, CObstacle::TYPE::TYPE_FAN);

	//CObstacle::Create(D3DXVECTOR3(-1000.0f, 650.0f, 360.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), CObstacle::TYPE_HIMO);

	//// �R�b�v�̐�������
	//CObstacle::Create(D3DXVECTOR3(-200.0f, 200.0f, 100.0f), NONE_D3DXVECTOR3, CObstacle::TYPE::TYPE_CUP);
	//pObstacle = CObstacle::Create(D3DXVECTOR3(400.0f, 200.0f, 100.0f), D3DXVECTOR3(0.0f, D3DX_PI * 1.0f, 0.0f), CObstacle::TYPE::TYPE_CUP);
	//pObstacle->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 1.0f, 0.0f));

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
				m_apPlayer[nCntPlay] = CPlayer::Create(D3DXVECTOR3(-500.0f, 0.0f, 0.0f), nCntPlay, CPlayer::TYPE_CAT);
			}
			else
			{ // ��L�ȊO

			  // �v���C���[�̐���
				m_apPlayer[nCntPlay] = CPlayer::Create(D3DXVECTOR3(250.0f * nCntPlay + 500.0f, 0.0f, 0.0f), nCntPlay, CPlayer::TYPE_RAT);
			}
		}
	}

	// �L�����N�^�[UI�̐�������
	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		CCharaInfoUI::Create(PLAYERUI_POS[nCnt], nCnt, m_apPlayer[nCnt]->GetType());
	}

	// ���̏�����
	m_nFinishCount = 0;				// �I���J�E���g
	m_GameState = STATE_START;		// ���

									// ������Ԃ�
	return S_OK;
}

//=============================================
//�I������
//=============================================
void CTutorial::Uninit(void)
{
	for (int nCntPlay = 0; nCntPlay < MAX_PLAY; nCntPlay++)
	{
		m_apPlayer[nCntPlay] = nullptr;		// �l�Y�~�̏��
	}

	// �I���J�E���g������������
	m_nFinishCount = 0;

	// �Đ����̃T�E���h�̒�~
	CManager::Get()->GetSound()->Stop();

	if (m_pExplanation != NULL)
	{
		m_pExplanation->Uninit();
		m_pExplanation = NULL;
	}

	if (m_pAnswer != NULL)
	{
		m_pAnswer->Uninit();
		m_pAnswer = NULL;
	}

	for (int nCnt = 0; nCnt < SKIP_MAX; nCnt++)
	{
		if (m_apSkip[nCnt] != NULL)
		{
			m_apSkip[nCnt]->Uninit();
			m_apSkip[nCnt] = NULL;
		}
	}

	// �I������
	CScene::Uninit();
}

//======================================
//�X�V����
//======================================
void CTutorial::Update(void)
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

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_F3) == true)
	{ // F3�L�[���������ꍇ
		CBlockManager::Get()->UninitAll();
	}

#endif

	if (m_bPlay == false)
	{
		//���݂��Ȃ��ꍇ����--------------------------------------------------------------------------
		if (m_pExplanation == NULL)
		{
			m_pExplanation = CExplanation::Create(m_Tutorial);

			// �����o���̏o������炷
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_TUTORIAL_BUBBLE);

			for (int nCnt = 0; nCnt < 4; nCnt++)
			{
				CTutorial::GetPlayer(nCnt)->SetTutorial(true);
			}
		}

		if (m_pAnswer == NULL)
		{
			m_pAnswer = CAnswer::Create();
		}

		//�X�V
		if (m_pExplanation != NULL)
		{
			m_pExplanation->Update();
		}

		if (m_pAnswer != NULL)
		{
			m_pAnswer->Update();
		}
	}
	else
	{
		if (m_pAnswer == NULL)
		{
			m_pAnswer = CAnswer::Create();
		}

		if (m_pAnswer != NULL)
		{
			m_pAnswer->Update();
		}

		//�v���C��Ԃւ̈ڍs
		PlayFalse();
	}

	switch (m_GameState)
	{
	case CTutorial::STATE_START:

		break;

	case CTutorial::STATE_PLAY:

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
			//CManager::Get()->GetFile()->Save(CFile::TYPE_TUTORIAL_DEFULT);	// �u���b�N
			//CManager::Get()->GetFile()->Save(CFile::TYPE_TUTORIAL_TABLE);		// �u���b�N
			//CManager::Get()->GetFile()->Save(CFile::TYPE_TUTORIAL_KILL);		// �u���b�N
			//CManager::Get()->GetFile()->Save(CFile::TYPE_TUTORIAL_ACTION);		// �u���b�N
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

	if (CManager::Get()->GetInputKeyboard()->GetPress(DIK_0) == true ||
		CManager::Get()->GetInputGamePad()->GetPress(CInputGamePad::JOYKEY::JOYKEY_START, 0) ||
		CManager::Get()->GetInputGamePad()->GetPress(CInputGamePad::JOYKEY::JOYKEY_START, 1) ||
		CManager::Get()->GetInputGamePad()->GetPress(CInputGamePad::JOYKEY::JOYKEY_START, 2) ||
		CManager::Get()->GetInputGamePad()->GetPress(CInputGamePad::JOYKEY::JOYKEY_START, 3))
	{
		if (m_apSkip[0] != NULL)
		{
			m_fGauge += 1.5f;
			if (m_fGaugeMax <= m_fGauge)
			{
				// �Q�[�����[�h�ɑJ��
				CManager::Get()->GetFade()->SetFade(CScene::MODE_GAME);
			}
		}
	}
	else
	{
		m_fGauge = 0.0f;
	}

	if (m_apSkip[0] != NULL)
	{
		m_apSkip[0]->SetPos(D3DXVECTOR3(880.0f + m_fGauge, 50.0f, 0.0f));
		m_apSkip[0]->SetSize(D3DXVECTOR3(m_fGauge, 50.0f, 0.0f));
		m_apSkip[0]->SetLength();					// ����
		m_apSkip[0]->SetAngle();						// ����
		m_apSkip[0]->SetVertex();
	}

	if (m_apSkip[2] != NULL && m_bPlay == true)
	{
		if (sinf(m_fSkipAlpha) >= 0.5f)
		{
			m_fSkipAlpha += 0.02f;
		}
		else
		{
			m_fSkipAlpha += 0.4f;
		}
		m_apSkip[2]->SetVtxColor(D3DXCOLOR(1.0f, 1.01f, 1.0f, sinf(m_fSkipAlpha)));
	}

	for (int nCnt = 0; nCnt < SKIP_MAX; nCnt++)
	{
		if (m_apSkip[nCnt] != NULL)
		{
			m_apSkip[nCnt]->Update();
		}
	}

	CManager::Get()->GetDebugProc()->Print("��ԁF%d", m_GameState);
}

//======================================
//�`�揈��
//======================================
void CTutorial::Draw(void)
{
	if (m_pExplanation != NULL)
	{
		m_pExplanation->Draw();
	}

	if (m_pAnswer != NULL)
	{
		m_pAnswer->Draw();
	}

	for (int nCnt = 0; nCnt < SKIP_MAX; nCnt++)
	{
		if (m_apSkip[nCnt] != NULL)
		{
			m_apSkip[nCnt]->Draw();
		}
	}
}

//======================================
// �v���C��Ԃւ̈ڍs
//======================================
void CTutorial::PlayTrue(void)
{	
	if (m_Tutorial != CTutorial::TUTORIAL_LETS_GO)
	{// �`���[�g���A�����Ōザ��Ȃ���
		m_bPlay = true;

		if (m_pExplanation != NULL)
		{
			m_pExplanation->Uninit();
			m_pExplanation = NULL;
		}
		if (m_pAnswer != NULL)
		{
			m_pAnswer->Uninit();
			m_pAnswer = NULL;
		}
	}

	//�`���[�g���A���̐ݒ菈��---------------------------------------------------------------
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		//�v���C��Ԃ�true�ɂ���
		m_bPlay = true;

		if (m_Tutorial == CTutorial::TUTORIAL_TABLESWING || m_Tutorial == CTutorial::TUTORIAL_CAT_KILL)
		{//�l�R�̃L�������̎�

			//�L�̂݃`���[�g���A����Ԃ��������l�Y�~�̃L�������false�ɂ��Ă���
			if (CTutorial::GetPlayer(nCnt)->GetType() == CPlayer::TYPE::TYPE_CAT)
			{
				CTutorial::GetPlayer(nCnt)->SetTutorial(false);
				CTutorial::GetPlayer(nCnt)->SetRatKill(false);
				CTutorial::GetPlayer(nCnt)->SetRatStun(false);
			}
		}
		else if (m_Tutorial == CTutorial::TUTORIAL_RAT_RESCUE)
		{//�l�Y�~�̑h�������̎�

			//�l�Y�~�̂݃`���[�g���A����Ԃ��������l�Y�~�̑h�������false�ɂ��Ă���
			if (CTutorial::GetPlayer(nCnt)->GetType() == CPlayer::TYPE::TYPE_RAT)
			{
				CTutorial::GetPlayer(nCnt)->SetTutorial(false);
				CTutorial::GetPlayer(nCnt)->SetRatRescue(false);
			}
		}
		else if (m_Tutorial == CTutorial::TUTORIAL_ACTION)
		{//�A�N�V�����N�������̎�

			//�A�N�V�����g�p��Ԃ�false�ɂ��Ă���
			CTutorial::GetPlayer(nCnt)->SetTutorial(false);
			CTutorial::GetPlayer(nCnt)->SetUseAction(false);
		}
		else
		{//����ȊO�̎�

			//�`���[�g���A����Ԃ���������
			CTutorial::GetPlayer(nCnt)->SetTutorial(false);
		}
	}

	//�}�b�v�̐؂�ւ�����--------------------------------------------------------------------
	if (m_Tutorial == CTutorial::TUTORIAL_TABLESWING)
	{
		CBlockManager::Get()->UninitAll();
		CManager::Get()->GetFile()->Load(CFile::TYPE_TUTORIAL_TABLE);

		// �}�b�v�̐ݒ菈��
		CManager::Get()->GetFile()->SetMap();

		RatPosTable();
	}
	else if (m_Tutorial == CTutorial::TUTORIAL_CAT_KILL)
	{
		CBlockManager::Get()->UninitAll();
		CManager::Get()->GetFile()->Load(CFile::TYPE_TUTORIAL_KILL);

		// �}�b�v�̐ݒ菈��
		CManager::Get()->GetFile()->SetMap();

		RatPosReset();
	}
	else if (m_Tutorial == CTutorial::TUTORIAL_RAT_RESCUE)
	{
		CBlockManager::Get()->UninitAll();
		CManager::Get()->GetFile()->Load(CFile::TYPE_TUTORIAL_DEFULT);

		// �}�b�v�̐ݒ菈��
		CManager::Get()->GetFile()->SetMap();
	}
	else if (m_Tutorial == CTutorial::TUTORIAL_ACTION)
	{
		CBlockManager::Get()->UninitAll();
		CManager::Get()->GetFile()->Load(CFile::TYPE_TUTORIAL_ACTION);

		// ��e�ƕR�̐�������
		CObstacle::Create(D3DXVECTOR3(0.0f, 200.0f, 360.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), CObstacle::TYPE_PIN);
		CObstacle::Create(D3DXVECTOR3(520.0f, 200.0f, 360.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), CObstacle::TYPE_PIN);
		CObstacle::Create(D3DXVECTOR3(970.0f, 200.0f, 360.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), CObstacle::TYPE_PIN);
		CObstacle::Create(D3DXVECTOR3(-1000.0f, 650.0f, 360.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), CObstacle::TYPE_HIMO);

		CatPosReset();
		RatPosReset();

		// �}�b�v�̐ݒ菈��
		CManager::Get()->GetFile()->SetMap();
	}
	else if (m_Tutorial == CTutorial::TUTORIAL_ITEM_MULTI)
	{
		CBlockManager::Get()->UninitAll();
		CManager::Get()->GetFile()->Load(CFile::TYPE_TUTORIAL_ACTION);

		// ���[�h�̐�������
		CObstacle::Create(D3DXVECTOR3(520.0f, 200.0f, -500.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f), CObstacle::TYPE_LEASH);

		// �l�Y�~�߂�̐���
		CItem::Create(D3DXVECTOR3(-1100.0f, 0.0f, -800.0f), CItem::TYPE::TYPE_MOUSETRAP);
		CItem::Create(D3DXVECTOR3(-900.0f, 0.0f, -600.0f), CItem::TYPE::TYPE_MOUSETRAP);

		// �}�b�v�̐ݒ菈��
		CManager::Get()->GetFile()->SetMap();
	}
	else if (m_Tutorial == CTutorial::TUTORIAL_LETS_GO)
	{
		// �Q�[�����[�h�ɑJ��
		CManager::Get()->GetFade()->SetFade(CScene::MODE_GAME);
	}
}

//======================================
// ������Ԃւ̈ڍs
//======================================
void CTutorial::PlayFalse(void)
{
	switch (m_Tutorial)
	{
	case CTutorial::TUTORIAL_MOVE:

		// �ړ������Ƃ��Ƀ`���[�g���A���B��
		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			if (m_apPlayer[nCnt]->GetBMove() == true)
			{
				if (m_pAnswer != NULL)
				{
					m_pAnswer->SetAnswer(true, nCnt);

					// ���s�������Đ�
					CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_TUTORIAL_OK);
				}
			}
		}

		break;
	case CTutorial::TUTORIAL_ATTACK_JAMP:

		// �l�R�͍U���A�l�Y�~�̓W�����v������ƃ`���[�g���A���B��
		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			if (m_apPlayer[nCnt]->GetAttack_Jump() == true)
			{
				if (m_pAnswer != NULL)
				{
					m_pAnswer->SetAnswer(true, nCnt);

					// ���s�������Đ�
					CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_TUTORIAL_OK);
				}
			}
		}

		break;

	case CTutorial::TUTORIAL_TABLESWING:

		// �l�R���l�Y�~���L������ƃ`���[�g���A���B��
		for (int nCntPlaeyr = 0; nCntPlaeyr < 4; nCntPlaeyr++)
		{
			if (CTutorial::GetPlayer(nCntPlaeyr)->GetType() == CPlayer::TYPE::TYPE_RAT)
			{
				if (CTutorial::GetPlayer(nCntPlaeyr)->GetRatStun() == true)
				{
					for (int nCnt = 0; nCnt < 4; nCnt++)
					{
						if (m_pAnswer != NULL)
						{
							m_pAnswer->SetAnswer(true, nCnt);

							// ���s�������Đ�
							CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_TUTORIAL_OK);
						}
					}
				}
			}
		}

		break;

	case CTutorial::TUTORIAL_CAT_KILL:

		// �l�R���l�Y�~���L������ƃ`���[�g���A���B��
		for (int nCntPlaeyr = 0; nCntPlaeyr < 4; nCntPlaeyr++)
		{
			if (CTutorial::GetPlayer(nCntPlaeyr)->GetType() == CPlayer::TYPE::TYPE_CAT)
			{
				if (CTutorial::GetPlayer(nCntPlaeyr)->GetRatKill() == true)
				{
					for (int nCnt = 0; nCnt < 4; nCnt++)
					{
						if (m_pAnswer != NULL)
						{
							m_pAnswer->SetAnswer(true, nCnt);

							// ���s�������Đ�
							CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_TUTORIAL_OK);
						}
					}
				}
			}
		}

		break;

	case CTutorial::TUTORIAL_RAT_RESCUE:

		// �l�Y�~�������̃l�Y�~��h������ƃ`���[�g���A���B��
		for (int nCntPlaeyr = 0; nCntPlaeyr < 4; nCntPlaeyr++)
		{
			if (CTutorial::GetPlayer(nCntPlaeyr)->GetType() == CPlayer::TYPE::TYPE_RAT)
			{
				if (CTutorial::GetPlayer(nCntPlaeyr)->GetRatRescue() == true)
				{
					for (int nCnt = 0; nCnt < 4; nCnt++)
					{
						if (m_pAnswer != NULL)
						{
							m_pAnswer->SetAnswer(true, nCnt);

							// ���s�������Đ�
							CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_TUTORIAL_OK);
						}
					}
				}
			}
		}

		break;
	case CTutorial::TUTORIAL_ACTION:

		// ��Q�����N�������Ƃ��ɂ��ꂼ��`���[�g���A���B��
		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			if (CTutorial::GetPlayer(nCnt)->GetUseAction() == true)
			{
				if (m_pAnswer != NULL)
				{
					m_pAnswer->SetAnswer(true, nCnt);

					// �`���[�g���A���B�����ɓ����Ȃ��悤�`���[�g���A����Ԃɂ���
					m_apPlayer[nCnt]->SetTutorial(true);

					// ���s�������Đ�
					CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_TUTORIAL_OK);
				}
			}
		}

		break;
	case CTutorial::TUTORIAL_ITEM_MULTI:

		// �l�R�̓l�Y�~�߂�̐ݒu�A�l�Y�~�̓��[�h�̋N���Ń`���[�g���A���B��
		if (m_MultiAction == true)
		{
			for (int nCnt = 0; nCnt < 4; nCnt++)
			{
				if (m_apPlayer[nCnt]->GetType() == CPlayer::TYPE::TYPE_RAT)
				{
					if (m_pAnswer != NULL)
					{
						m_pAnswer->SetAnswer(true, nCnt);

						// ���s�������Đ�
						CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_TUTORIAL_OK);
					}
				}
			}
		}

		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			if (CTutorial::GetPlayer(nCnt)->GetItem_MultiAction() == true)
			{
				if (m_pAnswer != NULL)
				{
					m_pAnswer->SetAnswer(true, nCnt);

					// ���s�������Đ�
					CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_TUTORIAL_OK);
				}
			}
		}

		break;
	case CTutorial::TUTORIAL_GIMMICK:

		// �����I�Ƀ`���[�g���A���B���Ƃ���
		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			if (m_pAnswer != NULL)
			{
				m_pAnswer->SetAnswer(true, nCnt);
			}
		}
		break;
	case CTutorial::TUTORIAL_LETS_GO:

		// �����I�Ƀ`���[�g���A���B���Ƃ���
		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			if (m_pAnswer != NULL)
			{
				m_pAnswer->SetAnswer(true, nCnt);
			}
		}
		break;
	case CTutorial::TUTORIAL_MAX:
		break;
	default:
		assert(false);
		break;
	}

	if (m_pAnswer != NULL)
	{
		if (m_pAnswer->GetAnswer(0) == true &&
			m_pAnswer->GetAnswer(1) == true &&
			m_pAnswer->GetAnswer(2) == true &&
			m_pAnswer->GetAnswer(3) == true)
		{
			m_bPlay = false;

			int mTutorialNumber = (int)m_Tutorial;
			mTutorialNumber++;
			m_Tutorial = (TUTORIAL)mTutorialNumber;

			if (m_pAnswer != NULL)
			{
				m_pAnswer->Uninit();
				m_pAnswer = NULL;
			}
		}
	}
}

//======================================
// �l�R�̈ʒu�����Z�b�g����
//======================================
void CTutorial::CatPosReset(void)
{
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		if (m_apPlayer[nCnt]->GetType() == CPlayer::TYPE_CAT)
		{
			m_apPlayer[nCnt]->SetPos(D3DXVECTOR3(-1000.0f, 0.0f, 0.0f));
		}
	}
}

//======================================
// �l�Y�~�̈ʒu�����Z�b�g����
//======================================
void CTutorial::RatPosReset(void)
{
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		if (m_apPlayer[nCnt]->GetType() == CPlayer::TYPE_RAT)
		{
			m_apPlayer[nCnt]->SetPos(D3DXVECTOR3(250.0f * nCnt + 500.0f, 0.0f, 0.0f));
		}
	}
}

//======================================
// �l�Y�~�̈ʒu�����Z�b�g����
//======================================
void CTutorial::RatPosTable(void)
{
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		if (m_apPlayer[nCnt]->GetType() == CPlayer::TYPE_RAT)
		{
			m_apPlayer[nCnt]->SetPos(D3DXVECTOR3(800.0f, 200.0f, -800.0f + nCnt * 500.0f));
		}
	}
}

//======================================
// ���̐ݒ菈��
//======================================
void CTutorial::SetData(const MODE mode)
{
	// ���̐ݒ菈��
	CScene::SetData(mode);

	// �X�^�[�g��Ԃɂ���
	m_GameState = STATE_START;

	// ���̏�����
	m_nFinishCount = 0;				// �I���J�E���g

	for (int nCnt = 0; nCnt < SKIP_MAX; nCnt++)
	{
		if (m_apSkip[nCnt] == NULL)
		{
			m_apSkip[nCnt] = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_2DUI, CObject::PRIORITY_UI);

			if (nCnt == 0)
			{
				m_apSkip[nCnt]->SetPos(GAUGE_POS);			// �ʒu
				m_apSkip[nCnt]->SetPosOld(GAUGE_POS);		// �O��̈ʒu
				m_apSkip[nCnt]->SetRot(NONE_D3DXVECTOR3);		// ����
				m_apSkip[nCnt]->SetSize(GAUGE_SIZE);			// �T�C�Y
			}
			else
			{
				m_apSkip[nCnt]->SetPos(SKIP_POS);			// �ʒu
				m_apSkip[nCnt]->SetPosOld(SKIP_POS);		// �O��̈ʒu
				m_apSkip[nCnt]->SetRot(NONE_D3DXVECTOR3);		// ����
				m_apSkip[nCnt]->SetSize(SKIP_SIZE);			// �T�C�Y
			}
			m_apSkip[nCnt]->SetLength();					// ����
			m_apSkip[nCnt]->SetAngle();						// ����

			// ���_���W�̐ݒ菈��
			m_apSkip[nCnt]->SetVertex();
		}
	}
	if (m_apSkip[0] != NULL)
	{
		m_apSkip[0]->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_skip_gauge00.png"));		// �e�N�X�`���̊��蓖�ď���
	}
	if (m_apSkip[1] != NULL)
	{
		m_apSkip[1]->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_skip_gauge01.png"));		// �e�N�X�`���̊��蓖�ď���
	}
	if (m_apSkip[2] != NULL)
	{
		m_apSkip[2]->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_skip00.png"));		// �e�N�X�`���̊��蓖�ď���
	}
}

//======================================
// �J�ڏ���
//======================================
void CTutorial::Transition(void)
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
// �`���[�g���A���̐i�s��Ԃ̐ݒ菈��
//======================================
void CTutorial::SetState(const STATE state)
{
	// �`���[�g���A���̐i�s��Ԃ�ݒ肷��
	m_GameState = state;
}

//======================================
// �`���[�g���A���̐i�s��Ԃ̎擾����
//======================================
CTutorial::STATE CTutorial::GetState(void)
{
	// �`���[�g���A���̐i�s��Ԃ�Ԃ�
	return m_GameState;
}

//======================================
// �v���C���[�̎擾����
//======================================
CPlayer* CTutorial::GetPlayer(const int nID)
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
// �l�Y�~��NULL������
//======================================
void CTutorial::DeletePlayer(int nIdx)
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
CEdit* CTutorial::GetEdit(void)
{
	// �G�f�B�b�g�̏���Ԃ�
	return m_pEdit;
}

//======================================
// �G�f�B�b�g�󋵂̎擾����
//======================================
bool CTutorial::IsEdit(void)
{
	// �G�f�B�b�g�󋵂�Ԃ�
	return m_bEdit;
}

#endif