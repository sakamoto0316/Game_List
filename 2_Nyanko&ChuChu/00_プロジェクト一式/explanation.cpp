//===========================================
//
// �����̃��C������[explanation.cpp]
// Author ��{�ėB
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "explanation.h"
#include "answer.h"
#include "object2D.h"
#include "manager.h"
#include "texture.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define SET_SIDE		(100.0f)										//��ʊO�ɒu���Ă����e�N�X�`���̏������ʒu
#define CAT_SIDE		(280.0f)										//��ʊO�ɒu���Ă����e�N�X�`���̏������ʒu
#define CAT_SIDE2		(300.0f)										//��ʊO�ɒu���Ă����e�N�X�`���̏������ʒu
#define RAT_SIDE0		(120.0f)										//��ʊO�ɒu���Ă����e�N�X�`���̏������ʒu
#define RAT_SIDE		(350.0f)										//��ʊO�ɒu���Ă����e�N�X�`���̏������ʒu
#define RAT_SIDE2		(145.0f)										//��ʊO�ɒu���Ă����e�N�X�`���̏������ʒu
#define CAT_KING_POS	(D3DXVECTOR3(-SET_SIDE,330.0f,0.0f))			//�l�R��\�̈ʒu
#define CAT_KING_SIZE	(D3DXVECTOR3(200.0f,400.0f,0.0f))				//�l�R��\�̃T�C�Y
#define CAT_BG_POS		(D3DXVECTOR3(-SET_SIDE + CAT_SIDE,170.0f,0.0f)) //�L�w�i�̈ʒu
#define CAT_BG_POS2		(D3DXVECTOR3(-SET_SIDE + CAT_SIDE2,170.0f,0.0f)) //�L�w�i�̈ʒu
#define CAT_BG_SIZE		(D3DXVECTOR3(80.0f,80.0f,0.0f))					//�L�w�i�̃T�C�Y
#define CAT_BG_SIZE2	(D3DXVECTOR3(50.0f,50.0f,0.0f))					//�L�w�i�̃T�C�Y
#define CAT_TEXT_POS	(D3DXVECTOR3(-SET_SIDE,200.0f,0.0f))			//�L�e�L�X�g�̈ʒu
#define CAT_TEXT_SIZE	(D3DXVECTOR3(400.0f,200.0f,0.0f))				//�L�e�L�X�g�̃T�C�Y
																		
#define RAT_KING_POS	(D3DXVECTOR3(1280.0f + SET_SIDE,520,0.0f))		//�l�Y�~��\�̈ʒu
#define RAT_KING_SIZE	(D3DXVECTOR3(125.0f,200.0f,0.0f))				//�l�Y�~��\�̃T�C�Y
#define RAT_BG_POS0		(D3DXVECTOR3(1280.0f + SET_SIDE - RAT_SIDE,50.0f,0.0f))	//�l�Y�~�w�i�̈ʒu
#define RAT_BG_POS		(D3DXVECTOR3(1280.0f + SET_SIDE - RAT_SIDE,550.0f,0.0f))	//�l�Y�~�w�i�̈ʒu
#define RAT_BG_POS2		(D3DXVECTOR3(1280.0f + SET_SIDE - RAT_SIDE2,680.0f,0.0f))	//�l�Y�~�w�i�̈ʒu
#define RAT_BG_SIZE0	(D3DXVECTOR3(120.0f,50.0f,0.0f))					//�l�Y�~�w�i�̃T�C�Y
#define RAT_BG_SIZE		(D3DXVECTOR3(50.0f,60.0f,0.0f))					//�l�Y�~�w�i�̃T�C�Y
#define RAT_BG_SIZE2	(D3DXVECTOR3(160.0f,50.0f,0.0f))					//�l�Y�~�w�i�̃T�C�Y
#define RAT_TEXT_POS	(D3DXVECTOR3(1280.0f + SET_SIDE,500.0f,0.0f))	//�l�Y�~�e�L�X�g�̈ʒu
#define RAT_TEXT_SIZE	(D3DXVECTOR3(400.0f,200.0f,0.0f))				//�l�Y�~�e�L�X�g�̃T�C�Y

#define IMAGE_POS	(D3DXVECTOR3(640.0f,360.0f,0.0f))					//�摜�̈ʒu
#define IMAGE_SIZE	(D3DXVECTOR3(590.0f,310.0f,0.0f))					//�摜�̃T�C�Y
#define START_POS	(D3DXVECTOR3(1080.0f,620.0f,0.0f))					//�摜�̈ʒu
#define START_SIZE	(D3DXVECTOR3(150.0f,50.0f,0.0f))					//�摜�̃T�C�Y

#define CAT_KING_STOP	(150.0f)										// �l�R��\�̒�~�ʒu
#define CAT_BG_STOP		(630.0f + CAT_SIDE)								// �L�w�i�̒�~�ʒu
#define CAT_BG_STOP2	(630.0f + CAT_SIDE2)							// �L�w�i�̒�~�ʒu
#define CAT_TEXT_STOP	(630.0f)										// �L�e�L�X�g�̒�~�ʒu
#define RAT_KING_STOP	(1280.0f - 150.0f)								// �l�Y�~��\�̒�~�ʒu
#define RAT_BG_STOP0	(1280.0f - RAT_SIDE0)							// �l�Y�~�w�i�̒�~�ʒu
#define RAT_BG_STOP		(1280.0f - 630.0f - RAT_SIDE)					// �l�Y�~�w�i�̒�~�ʒu
#define RAT_BG_STOP2	(1280.0f - 630.0f - RAT_SIDE2)					// �l�Y�~�w�i�̒�~�ʒu
#define RAT_TEXT_STOP	(1280.0f - 630.0f)								// �l�Y�~�e�L�X�g�̒�~�ʒu
#define SIDE_MOVESPEED	(5.0f)											// ���ړ��̑��x
#define A_PLUS_KING		(0.013f)										// ��\�̃��l�̉��Z
#define A_PLUS_TEXT		(0.015f)										// �e�L�X�g�̃��l�̉��Z
//-------------------------------------------
// �ÓI�����o�ϐ��錾
//-------------------------------------------

//==============================
// �R���X�g���N�^
//==============================
CExplanation::CExplanation() : CObject(CObject::TYPE_2DUI, CObject::PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
	m_pBG = NULL;
	m_pCatKing = NULL;
	m_pCatBG = NULL;
	m_pCatText = NULL;
	m_pRatKing = NULL;
	m_pRatBG = NULL;
	m_pRatText = NULL;
	m_ColorKing = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	m_ColorText = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	for (int nCnt = 0; nCnt < IMAGE_MAX; nCnt++)
	{
		m_apImage[nCnt] = NULL;
	}
	m_fStartAlpha = D3DX_PI;
}

//==============================
// �f�X�g���N�^
//==============================
CExplanation::~CExplanation()
{

}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CExplanation::Init(void)
{
	// �S�Ă̒l������������

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �j�Ђ̏I������
//========================================
void CExplanation::Uninit(void)
{
	if (m_pBG != NULL)
	{
		m_pBG->Uninit();
		m_pBG = NULL;
	}
	if (m_pCatKing != NULL)
	{
		m_pCatKing->Uninit();
		m_pCatKing = NULL;
	}
	if (m_pCatBG != NULL)
	{
		m_pCatBG->Uninit();
		m_pCatBG = NULL;
	}
	if (m_pCatText != NULL)
	{
		m_pCatText->Uninit();
		m_pCatText = NULL;
	}
	if (m_pRatKing != NULL)
	{
		m_pRatKing->Uninit();
		m_pRatKing = NULL;
	}
	if (m_pRatBG != NULL)
	{
		m_pRatBG->Uninit();
		m_pRatBG = NULL;
	}
	if (m_pRatText != NULL)
	{
		m_pRatText->Uninit();
		m_pRatText = NULL;
	}
	for (int nCnt = 0; nCnt < IMAGE_MAX; nCnt++)
	{
		if (m_apImage[nCnt] != NULL)
		{
			m_apImage[nCnt]->Uninit();
			m_apImage[nCnt] = NULL;
		}
	}

	Release();
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CExplanation::Update(void)
{
	m_ColorKing.a += A_PLUS_KING;

	if (m_ColorKing.a > 1.0f)
	{
		m_ColorKing.a = 1.0f;
		m_ColorText.a += A_PLUS_TEXT;
	}
	if (m_ColorText.a > 1.0f)
	{
		m_ColorText.a = 1.0f;
	}

	if (m_pCatKing != NULL)
	{
		m_pCatKing->Update();

		D3DXVECTOR3 pos = m_pCatKing->GetPos();

		pos.x += SIDE_MOVESPEED;

		if (pos.x > CAT_KING_STOP)
		{
			pos.x = CAT_KING_STOP;
		}

		m_pCatKing->SetVtxColor(m_ColorKing);
		m_pCatKing->SetPos(pos);
	}
	if (m_pCatBG != NULL)
	{
		m_pCatBG->Update();

		D3DXVECTOR3 pos = m_pCatBG->GetPos();
		pos.x += SIDE_MOVESPEED;

		if (CTutorial::GetTutorial() == CTutorial::TUTORIAL::TUTORIAL_ACTION)
		{
			if (pos.x > CAT_BG_STOP)
			{
				pos.x = CAT_BG_STOP;
			}
		}
		else if (CTutorial::GetTutorial() == CTutorial::TUTORIAL::TUTORIAL_ITEM_MULTI)
		{
			if (pos.x > CAT_BG_STOP2)
			{
				pos.x = CAT_BG_STOP2;
			}
		}

		m_pCatBG->SetVtxColor(m_ColorText);
		m_pCatBG->SetPos(pos);
	}
	if (m_pCatText != NULL)
	{
		m_pCatText->Update();

		D3DXVECTOR3 pos = m_pCatText->GetPos();
		pos.x += SIDE_MOVESPEED;

		if (pos.x > CAT_TEXT_STOP)
		{
			pos.x = CAT_TEXT_STOP;
		}

		m_pCatText->SetVtxColor(m_ColorText);
		m_pCatText->SetPos(pos);
	}
	if (m_pRatKing != NULL)
	{
		m_pRatKing->Update();

		D3DXVECTOR3 pos = m_pRatKing->GetPos();
		pos.x -= SIDE_MOVESPEED;

		if (pos.x < RAT_KING_STOP)
		{
			pos.x = RAT_KING_STOP;
		}

		m_pRatKing->SetVtxColor(m_ColorKing);
		m_pRatKing->SetPos(pos);
	}
	if (m_pRatBG != NULL)
	{
		m_pRatBG->Update();

		D3DXVECTOR3 pos = m_pRatBG->GetPos();
		pos.x -= SIDE_MOVESPEED;

		if (CTutorial::GetTutorial() == CTutorial::TUTORIAL::TUTORIAL_MOVE)
		{
			if (pos.x < RAT_BG_STOP0)
			{
				pos.x = RAT_BG_STOP0;
			}
		}
		if (CTutorial::GetTutorial() == CTutorial::TUTORIAL::TUTORIAL_ACTION)
		{
			if (pos.x < RAT_BG_STOP)
			{
				pos.x = RAT_BG_STOP;
			}
		}
		else if (CTutorial::GetTutorial() == CTutorial::TUTORIAL::TUTORIAL_ITEM_MULTI)
		{
			if (pos.x < RAT_BG_STOP2)
			{
				pos.x = RAT_BG_STOP2;
			}
		}

		m_pRatBG->SetVtxColor(m_ColorText);
		m_pRatBG->SetPos(pos);
	}
	if (m_pRatText != NULL)
	{
		m_pRatText->Update();

		D3DXVECTOR3 pos = m_pRatText->GetPos();
		pos.x -= SIDE_MOVESPEED;

		if (pos.x < RAT_TEXT_STOP)
		{
			pos.x = RAT_TEXT_STOP;
		}

		m_pRatText->SetVtxColor(m_ColorText);
		m_pRatText->SetPos(pos);
	}

	if (m_apImage[2] != NULL)
	{
		if (sinf(m_fStartAlpha) >= 0.5f)
		{
			m_fStartAlpha += 0.03f;
		}
		else
		{
			m_fStartAlpha += 0.2f;
		}
		m_apImage[2]->SetVtxColor(D3DXCOLOR(1.0f, 1.01f, 1.0f, sinf(m_fStartAlpha)));
	}

	for (int nCnt = 0; nCnt < IMAGE_MAX; nCnt++)
	{
		if (m_apImage[nCnt] != NULL)
		{
			m_apImage[nCnt]->Update();
		}
	}
}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CExplanation::Draw(void)
{
	if (m_pBG != NULL)
	{
		m_pBG->Draw();
	}
	if (m_pCatKing != NULL)
	{
		m_pCatKing->Draw();
	}
	if (m_pCatText != NULL)
	{
		m_pCatText->Draw();
	}
	if (m_pRatKing != NULL)
	{
		m_pRatKing->Draw();
	}
	if (m_pRatText != NULL)
	{
		m_pRatText->Draw();
	}
	if (m_pCatBG != NULL)
	{
		m_pCatBG->Draw();
	}
	if (m_pRatBG != NULL)
	{
		m_pRatBG->Draw();
	}
	for (int nCnt = 0; nCnt < IMAGE_MAX; nCnt++)
	{
		if (m_apImage[nCnt] != NULL)
		{
			m_apImage[nCnt]->Draw();
		}
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CExplanation::SetData(CTutorial::TUTORIAL Tutorial)
{
	//Tutorial = CTutorial::TUTORIAL_ITEM_MULTI;

	if (m_pBG == NULL)
	{
		m_pBG = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
		m_pBG->SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f));	// �ʒu
		m_pBG->SetPosOld(D3DXVECTOR3(640.0f, 360.0f, 0.0f));// �O��̈ʒu
		m_pBG->SetRot(NONE_D3DXVECTOR3);					// ����
		m_pBG->SetSize(D3DXVECTOR3(640.0f, 360.0f, 0.0f));	// �T�C�Y
		m_pBG->SetLength();									// ����
		m_pBG->SetAngle();									// ����
		m_pBG->SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));	// �F

		// ���_���W�̐ݒ菈��
		m_pBG->SetVertex();
	}

	if(Tutorial == CTutorial::TUTORIAL_GIMMICK)
	{
		if (m_apImage[0] == NULL)
		{
			m_apImage[0] = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
			m_apImage[0]->SetPos(IMAGE_POS);			// �ʒu
			m_apImage[0]->SetPosOld(IMAGE_POS);			// �O��̈ʒu
			m_apImage[0]->SetRot(NONE_D3DXVECTOR3);		// ����
			m_apImage[0]->SetSize(IMAGE_SIZE);			// �T�C�Y
			m_apImage[0]->SetLength();					// ����
			m_apImage[0]->SetAngle();					// ����

			// ���_���W�̐ݒ菈��
			m_apImage[0]->SetVertex();
		}
	}
	else if (Tutorial == CTutorial::TUTORIAL_LETS_GO)
	{
		if (m_apImage[0] == NULL)
		{
			m_apImage[0] = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
			m_apImage[0]->SetPos(IMAGE_POS);			// �ʒu
			m_apImage[0]->SetPosOld(IMAGE_POS);			// �O��̈ʒu
			m_apImage[0]->SetRot(NONE_D3DXVECTOR3);		// ����
			m_apImage[0]->SetSize(IMAGE_SIZE);			// �T�C�Y
			m_apImage[0]->SetLength();					// ����
			m_apImage[0]->SetAngle();					// ����

														// ���_���W�̐ݒ菈��
			m_apImage[0]->SetVertex();
		}

		if (m_apImage[1] == NULL)
		{
			m_apImage[1] = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
			m_apImage[1]->SetPos(START_POS);			// �ʒu
			m_apImage[1]->SetPosOld(START_POS);			// �O��̈ʒu
			m_apImage[1]->SetRot(NONE_D3DXVECTOR3);		// ����
			m_apImage[1]->SetSize(START_SIZE);			// �T�C�Y
			m_apImage[1]->SetLength();					// ����
			m_apImage[1]->SetAngle();					// ����

			// ���_���W�̐ݒ菈��
			m_apImage[1]->SetVertex();
		}
		if (m_apImage[2] == NULL)
		{			  
			m_apImage[2] = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
			m_apImage[2]->SetPos(START_POS);			// �ʒu
			m_apImage[2]->SetPosOld(START_POS);			// �O��̈ʒu
			m_apImage[2]->SetRot(NONE_D3DXVECTOR3);		// ����
			m_apImage[2]->SetSize(START_SIZE);			// �T�C�Y
			m_apImage[2]->SetLength();					// ����
			m_apImage[2]->SetAngle();					// ����
					  
			// ���_���W�̐ݒ菈��
			m_apImage[2]->SetVertex();
		}
	}
	else
	{
		if (m_pCatKing == NULL && Tutorial != CTutorial::TUTORIAL_RAT_RESCUE)
		{
			m_pCatKing = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
			m_pCatKing->SetPos(CAT_KING_POS);			// �ʒu
			m_pCatKing->SetPosOld(CAT_KING_POS);		// �O��̈ʒu
			m_pCatKing->SetRot(NONE_D3DXVECTOR3);		// ����
			m_pCatKing->SetSize(CAT_KING_SIZE);			// �T�C�Y
			m_pCatKing->SetLength();					// ����
			m_pCatKing->SetAngle();						// ����
			m_pCatKing->SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	// �F
			m_pCatKing->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_icon_Obanyan.png"));		// �e�N�X�`���̊��蓖�ď���

			// ���_���W�̐ݒ菈��
			m_pCatKing->SetVertex();

		}
		if (m_pCatBG == NULL && Tutorial == CTutorial::TUTORIAL_ACTION)
		{
			m_pCatBG = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
			m_pCatBG->SetPos(CAT_BG_POS);				// �ʒu
			m_pCatBG->SetPosOld(CAT_BG_POS);			// �O��̈ʒu
			m_pCatBG->SetRot(NONE_D3DXVECTOR3);			// ����
			m_pCatBG->SetSize(CAT_BG_SIZE);				// �T�C�Y
			m_pCatBG->SetLength();						// ����
			m_pCatBG->SetAngle();						// ����
			m_pCatBG->SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	// �F

			// ���_���W�̐ݒ菈��
			m_pCatBG->SetVertex();
		}
		else if (m_pCatBG == NULL && Tutorial == CTutorial::TUTORIAL_ITEM_MULTI)
		{
			m_pCatBG = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
			m_pCatBG->SetPos(CAT_BG_POS2);				// �ʒu
			m_pCatBG->SetPosOld(CAT_BG_POS2);			// �O��̈ʒu
			m_pCatBG->SetRot(NONE_D3DXVECTOR3);			// ����
			m_pCatBG->SetSize(CAT_BG_SIZE2);				// �T�C�Y
			m_pCatBG->SetLength();						// ����
			m_pCatBG->SetAngle();						// ����
			m_pCatBG->SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	// �F

																		// ���_���W�̐ݒ菈��
			m_pCatBG->SetVertex();
		}

		if (m_pCatText == NULL && Tutorial != CTutorial::TUTORIAL_RAT_RESCUE)
		{
			m_pCatText = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
			m_pCatText->SetPos(CAT_TEXT_POS);			// �ʒu
			m_pCatText->SetPosOld(CAT_TEXT_POS);		// �O��̈ʒu
			m_pCatText->SetRot(NONE_D3DXVECTOR3);		// ����
			m_pCatText->SetSize(CAT_TEXT_SIZE);			// �T�C�Y
			m_pCatText->SetLength();					// ����
			m_pCatText->SetAngle();						// ����
			m_pCatText->SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	// �F

			// ���_���W�̐ݒ菈��
			m_pCatText->SetVertex();
		}
		if (m_pRatKing == NULL && Tutorial != CTutorial::TUTORIAL_TABLESWING && Tutorial != CTutorial::TUTORIAL_CAT_KILL)
		{
			m_pRatKing = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
			m_pRatKing->SetPos(RAT_KING_POS);			// �ʒu
			m_pRatKing->SetPosOld(RAT_KING_POS);		// �O��̈ʒu
			m_pRatKing->SetRot(NONE_D3DXVECTOR3);		// ����
			m_pRatKing->SetSize(RAT_KING_SIZE);			// �T�C�Y
			m_pRatKing->SetLength();					// ����
			m_pRatKing->SetAngle();						// ����
			m_pRatKing->SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	// �F
			m_pRatKing->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_icon_ChuChuGG.png"));		// �e�N�X�`���̊��蓖�ď���

			// ���_���W�̐ݒ菈��
			m_pRatKing->SetVertex();
		}

		if (m_pRatBG == NULL && Tutorial == CTutorial::TUTORIAL_MOVE)
		{
			m_pRatBG = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
			m_pRatBG->SetPos(RAT_BG_POS0);				// �ʒu
			m_pRatBG->SetPosOld(RAT_BG_POS0);			// �O��̈ʒu
			m_pRatBG->SetRot(NONE_D3DXVECTOR3);			// ����
			m_pRatBG->SetSize(RAT_BG_SIZE0);				// �T�C�Y
			m_pRatBG->SetLength();						// ����
			m_pRatBG->SetAngle();						// ����
			m_pRatBG->SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	// �F

																		// ���_���W�̐ݒ菈��
			m_pRatBG->SetVertex();
		}
		else if (m_pRatBG == NULL && Tutorial == CTutorial::TUTORIAL_ACTION)
		{
			m_pRatBG = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
			m_pRatBG->SetPos(RAT_BG_POS);				// �ʒu
			m_pRatBG->SetPosOld(RAT_BG_POS);			// �O��̈ʒu
			m_pRatBG->SetRot(NONE_D3DXVECTOR3);			// ����
			m_pRatBG->SetSize(RAT_BG_SIZE);				// �T�C�Y
			m_pRatBG->SetLength();						// ����
			m_pRatBG->SetAngle();						// ����
			m_pRatBG->SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	// �F

			// ���_���W�̐ݒ菈��
			m_pRatBG->SetVertex();
		}
		else if (m_pRatBG == NULL && Tutorial == CTutorial::TUTORIAL_ITEM_MULTI)
		{
			m_pRatBG = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
			m_pRatBG->SetPos(RAT_BG_POS2);				// �ʒu
			m_pRatBG->SetPosOld(RAT_BG_POS2);			// �O��̈ʒu
			m_pRatBG->SetRot(NONE_D3DXVECTOR3);			// ����
			m_pRatBG->SetSize(RAT_BG_SIZE2);				// �T�C�Y
			m_pRatBG->SetLength();						// ����
			m_pRatBG->SetAngle();						// ����
			m_pRatBG->SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	// �F

																		// ���_���W�̐ݒ菈��
			m_pRatBG->SetVertex();
		}
		if (m_pRatText == NULL && Tutorial != CTutorial::TUTORIAL_TABLESWING && Tutorial != CTutorial::TUTORIAL_CAT_KILL)
		{
			m_pRatText = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
			m_pRatText->SetPos(RAT_TEXT_POS);			// �ʒu
			m_pRatText->SetPosOld(RAT_TEXT_POS);		// �O��̈ʒu
			m_pRatText->SetRot(NONE_D3DXVECTOR3);		// ����
			m_pRatText->SetSize(RAT_TEXT_SIZE);			// �T�C�Y
			m_pRatText->SetLength();					// ����
			m_pRatText->SetAngle();						// ����
			m_pRatText->SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	// �F

			// ���_���W�̐ݒ菈��
			m_pRatText->SetVertex();
		}
	}

	switch (Tutorial)
	{
	case CTutorial::TUTORIAL_MOVE:
		if (m_pRatBG != NULL)
		{
			m_pRatBG->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_ok.png"));		// �e�N�X�`���̊��蓖�ď���
		}
		if (m_pCatText != NULL)
		{
			m_pCatText->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_textcat00.png"));		// �e�N�X�`���̊��蓖�ď���
		}
		if (m_pRatText != NULL)
		{
			m_pRatText->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_textrat00.png"));		// �e�N�X�`���̊��蓖�ď���
		}

		break;

	case CTutorial::TUTORIAL_ATTACK_JAMP:
		if (m_pCatText != NULL)
		{
			m_pCatText->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_textcat01.png"));		// �e�N�X�`���̊��蓖�ď���
		}
		if (m_pRatText != NULL)
		{
			m_pRatText->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_textrat01.png"));		// �e�N�X�`���̊��蓖�ď���
		}
		break;

	case CTutorial::TUTORIAL_TABLESWING:
		if (m_pCatText != NULL)
		{
			m_pCatText->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_textcat05.png"));		// �e�N�X�`���̊��蓖�ď���
		}
		break;

	case CTutorial::TUTORIAL_CAT_KILL:
		if (m_pCatText != NULL)
		{
			m_pCatText->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_textcat02.png"));		// �e�N�X�`���̊��蓖�ď���
		}
		break;

	case CTutorial::TUTORIAL_RAT_RESCUE:
		if (m_pRatText != NULL)
		{
			m_pRatText->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_textrat02.png"));		// �e�N�X�`���̊��蓖�ď���
		}
		break;

	case CTutorial::TUTORIAL_ACTION:
		if (m_pCatBG != NULL)
		{
			m_pCatBG->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_action_Himo.png"));		// �e�N�X�`���̊��蓖�ď���
		}
		if (m_pRatBG != NULL)
		{
			m_pRatBG->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_action_pin.png"));		// �e�N�X�`���̊��蓖�ď���
		}

		if (m_pCatText != NULL)
		{
			m_pCatText->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_textcat03.png"));		// �e�N�X�`���̊��蓖�ď���
		}
		if (m_pRatText != NULL)
		{
			m_pRatText->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_textrat03.png"));		// �e�N�X�`���̊��蓖�ď���
		}
		break;

	case CTutorial::TUTORIAL_ITEM_MULTI:
		if (m_pCatBG != NULL)
		{
			m_pCatBG->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_action_mousetrap.png"));		// �e�N�X�`���̊��蓖�ď���
		}
		if (m_pRatBG != NULL)
		{
			m_pRatBG->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_action_leash.png"));		// �e�N�X�`���̊��蓖�ď���
		}

		if (m_pCatText != NULL)
		{
			m_pCatText->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_textcat04.png"));		// �e�N�X�`���̊��蓖�ď���
		}
		if (m_pRatText != NULL)
		{
			m_pRatText->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_textrat04.png"));		// �e�N�X�`���̊��蓖�ď���
		}
		break;

	case CTutorial::TUTORIAL_GIMMICK:
		if (m_apImage[0] != NULL)
		{
			m_apImage[0]->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_explanation00.png"));		// �e�N�X�`���̊��蓖�ď���
		}
		break;

	case CTutorial::TUTORIAL_LETS_GO:
		if (m_apImage[0] != NULL)
		{
			m_apImage[0]->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_explanation01.png"));		// �e�N�X�`���̊��蓖�ď���
		}
		if (m_apImage[1] != NULL)
		{
			m_apImage[1]->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_start00.png"));		// �e�N�X�`���̊��蓖�ď���
		}
		if (m_apImage[2] != NULL)
		{
			m_apImage[2]->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_start01.png"));		// �e�N�X�`���̊��蓖�ď���
		}
		break;

	default:

		break;
	}
}

//=======================================
// ��������
//=======================================
CExplanation* CExplanation::Create(CTutorial::TUTORIAL Tutorial)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CExplanation* pSample = nullptr;	// �Ԏ����͂̃��A�N�V�����̃C���X�^���X�𐶐�

	if (pSample == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

	  // �C���X�^���X�𐶐�
		pSample = new CExplanation;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

	  // ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pSample != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

	  // ����������
		if (FAILED(pSample->Init()))
		{ // �������Ɏ��s�����ꍇ

		  // ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pSample->SetData(Tutorial);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

	  // ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �Ԏ����͂̃��A�N�V�����̃|�C���^��Ԃ�
	return pSample;
}