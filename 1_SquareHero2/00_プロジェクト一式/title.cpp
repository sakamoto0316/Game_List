//============================================
//
//	�^�C�g����� [title.cpp]
//	Author:sakamoto kai
//
//============================================
#include "title.h"
#include "manager.h"
#include "fade.h"
#include "input.h"
#include "object2D.h"
#include "texture.h"
#include "particle.h"
#include "sound.h"
#include "objmeshDome.h"
#include "player.h"
#include "boss.h"
#include "CubeBlock.h"

//�ÓI�����o�ϐ��錾
CObject2D *CTitle::m_pTitle = NULL;
CObject2D *CTitle::m_pTitleButton = NULL;
CObject2D *CTitle::m_pTitleLogo[4] = {};
int CTitle::m_nSelect = 1;
int CTitle::m_CreateCount = 0;
D3DXVECTOR2 CTitle::m_Scroll = D3DXVECTOR2(0.0f,0.0f);
D3DXVECTOR2 CTitle::m_Tex = D3DXVECTOR2(0.0f, 0.0f);
CObjmeshDome* CTitle::m_pMeshDome = NULL;
CCubeBlock* CTitle::m_pCubeBlock = NULL;
CPlayer* CTitle::m_pPlayer = NULL;
CBoss* CTitle::m_pBoss = NULL;

//====================================================================
//�R���X�g���N�^
//====================================================================
CTitle::CTitle()
{
	m_nSelect = 1;
	m_CreateCount = 0;
	m_Tex = D3DXVECTOR2(0.0f, 0.0f);
}

//====================================================================
//�f�X�g���N�^
//====================================================================
CTitle::~CTitle()
{

}

//====================================================================
//����������
//====================================================================
HRESULT CTitle::Init(void)
{
	CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_BGM_TITLE);

	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	m_pTitle = CObject2D::Create();
	m_pTitle->SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f));
	m_pTitle->SetWight(1280.0f);
	m_pTitle->SetHeight(720.0f);
	m_pTitle->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_pTitle->SetIdx(pTexture->Regist("data\\TEXTURE\\TitleBG.png"));

	m_pMeshDome = CObjmeshDome::Create();
	m_pMeshDome->SetTexture("data\\TEXTURE\\SkyBG.jpg");
	m_pMeshDome->SetRot(D3DXVECTOR3(D3DX_PI * 0.55f, D3DX_PI * -0.89f, D3DX_PI));

	m_pPlayer = CPlayer::Create();
	m_pPlayer->SetPos(D3DXVECTOR3(-50.0f, 60.0f, -450.0f));
	m_pPlayer->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * -0.9f, 0.0f));

	m_pBoss = CBoss::Create("data\\MODEL\\boss.x");
	m_pBoss->SetPos(D3DXVECTOR3(500.0f, 300.0f, 1000.0f));
	m_pBoss->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.1f, 0.0f));

	m_pCubeBlock = CCubeBlock::Create();
	m_pCubeBlock->SetPos(D3DXVECTOR3(-50.0f, 40.0f, -450.0f));
	m_pCubeBlock->SetRot(D3DXVECTOR3(D3DX_PI * 0.98f, D3DX_PI * -0.9f, 0.0f));
	m_pCubeBlock->SetSize(D3DXVECTOR3(250.0f, 25.0f, 10000.0f));

	m_pTitleButton = CObject2D::Create();
	m_pTitleButton->SetPos(D3DXVECTOR3(640.0f, 670.0f, 0.0f));
	m_pTitleButton->SetWight(600.0f);
	m_pTitleButton->SetHeight(350.0f);
	m_pTitleButton->SetIdx(pTexture->Regist("data\\TEXTURE\\TitleBotton.png"));

	return S_OK;
}

//====================================================================
//�I������
//====================================================================
void CTitle::Uninit(void)
{
	//�S�ẴI�u�W�F�N�g�̔j��
	CObject::ReleaseAll();
}

//====================================================================
//�X�V����
//====================================================================
void CTitle::Update(void)
{
	m_Scroll.x += 0.01f;
	m_Scroll.y += 0.0f;
	m_pMeshDome->SetScroll(m_Scroll);

	//�I������
	Select();

	m_CreateCount++;
}

//====================================================================
//�`�揈��
//====================================================================
void CTitle::Draw(void)
{

}

//====================================================================
//�I������
//====================================================================
void CTitle::Select(void)
{
	if (CManager::GetInstance()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true)
	{
		CManager::GetInstance()->SetUseJoyPad(false);
		CFade::SetFade(CScene::MODE_GAME);
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_ENTER_PUSH);
	}
	else if (CManager::GetInstance()->GetInputJoyPad()->GetTrigger(CInputJoypad::BUTTON_A, 0) == true)
	{
		CManager::GetInstance()->SetUseJoyPad(true);
		CFade::SetFade(CScene::MODE_GAME);
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_ENTER_PUSH);
	}
}

//====================================================================
//�I�����ڂ̃J���[�ύX����
//====================================================================
void CTitle::SetSelectColor(int nCnt)
{
	m_nSelect = nCnt;
}