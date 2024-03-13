//===========================================
//
// �Ԏ����͂̃��A�N�V�����̃��C������[sample.cpp]
// Author ��{�ėB
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "answer.h"
#include "object2D.h"
#include "texture.h"
#include "input.h"
#include "sound.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define ANSWER_POS (D3DXVECTOR3(1100.0f, 150.0f, 0.0f))
#define ANSWER_POS2 (D3DXVECTOR3(1070.0f, 45.0f, 0.0f))
#define ANSWER_SIZE (38.0f)
#define ANSWER_DISTANCE (98.0f)

//-------------------------------------------
// �ÓI�����o�ϐ��錾
//-------------------------------------------

//==============================
// �R���X�g���N�^
//==============================
CAnswer::CAnswer() : CObject/*�e�N���X*/(/*�����Ƀ^�C�v������*/CObject::TYPE_2DUI, /*�����ɗD�揇�ʂ�����*/CObject::PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_apAnswer[nCnt] = NULL;
		m_abPressAnswer[nCnt] = false;
		m_apPlayerID[nCnt] = NULL;
	}
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);;
}

//==============================
// �f�X�g���N�^
//==============================
CAnswer::~CAnswer()
{

}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CAnswer::Init(void)
{
	//if (FAILED(�e�N���X::Init()))
	//{ // �����������Ɏ��s�����ꍇ

	//	// ���s��Ԃ�
	//	return E_FAIL;
	//}

	// �S�Ă̒l������������

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �j�Ђ̏I������
//========================================
void CAnswer::Uninit(void)
{
	//// �I������
	//�e�N���X::Uninit();

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		if (m_apAnswer[nCnt] != NULL)
		{
			m_apAnswer[nCnt]->Uninit();
			m_apAnswer[nCnt] = NULL;
		}
	}

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		if (m_apPlayerID[nCnt] != NULL)
		{
			m_apPlayerID[nCnt]->Uninit();
			m_apPlayerID[nCnt] = NULL;
		}
	}

	Release();
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CAnswer::Update(void)
{
	if (CTutorial::GetPlay() == false)
	{//�����̃v���C���
		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			// �����x��ς���
			if (m_Color.a < 1.0f)
			{
				m_Color.a += 0.015f;
			}
			else
			{
				m_Color.a = 1.0f;
			}

			// �ς��������x�𔽉f����
			if (m_apAnswer[nCnt] != NULL)
			{
				m_apAnswer[nCnt]->SetVtxColor(m_Color);
			}
			if (m_apPlayerID[nCnt] != NULL)
			{
				m_apPlayerID[nCnt]->SetVtxColor(m_Color);
			}

			//���͂Ń`�F�b�N������
			if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true)
			{
				m_abPressAnswer[nCnt] = true;
			}

			if (CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_START, nCnt))
			{
				m_abPressAnswer[nCnt] = true;

				// OK���Đ�
				CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_CHECK);
			}
		}
	}

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		if (m_apAnswer[nCnt] != NULL)
		{
			if (m_abPressAnswer[nCnt] == true)
			{
				m_apAnswer[nCnt]->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_checkbox01.png"));		// �e�N�X�`���̊��蓖�ď���
			}

			m_apAnswer[nCnt]->Update();
		}
	}

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		if (m_apPlayerID[nCnt] != NULL)
		{
			m_apPlayerID[nCnt]->Update();
		}
	}

	if (m_abPressAnswer[0] == true &&
		m_abPressAnswer[1] == true &&
		m_abPressAnswer[2] == true &&
		m_abPressAnswer[3] == true)
	{
		CTutorial::PlayTrue();
	}
}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CAnswer::Draw(void)
{
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		if (m_apPlayerID[nCnt] != NULL)
		{
			if (m_abPressAnswer[nCnt] == true)
			{
				m_apPlayerID[nCnt]->Draw();
			}
		}
	}

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		if (m_apAnswer[nCnt] != NULL)
		{
			m_apAnswer[nCnt]->Draw();
		}
	}

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		if (m_apPlayerID[nCnt] != NULL)
		{
			if (m_abPressAnswer[nCnt] == false)
			{
				m_apPlayerID[nCnt]->Draw();
			}
		}
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CAnswer::SetData(void)
{
	if (CTutorial::GetPlay() == true)
	{
		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			if (m_apAnswer[nCnt] == NULL)
			{
				m_apAnswer[nCnt] = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
				
				switch (nCnt)
				{
				case 0:
					m_apAnswer[nCnt]->SetPos(D3DXVECTOR3(100.0f, 240.0f, 0.0f));		// �ʒu
					m_apAnswer[nCnt]->SetPosOld(D3DXVECTOR3(100.0f, 240.0f, 0.0f));		// �O��̈ʒu
					break;
				case 1:
					m_apAnswer[nCnt]->SetPos(D3DXVECTOR3(1200.0f, 240.0f, 0.0f));		// �ʒu
					m_apAnswer[nCnt]->SetPosOld(D3DXVECTOR3(1180.0f, 240.0f, 0.0f));	// �O��̈ʒu
					break;
				case 2:
					m_apAnswer[nCnt]->SetPos(D3DXVECTOR3(100.0f, 360.0f + 240.0f, 0.0f));		// �ʒu
					m_apAnswer[nCnt]->SetPosOld(D3DXVECTOR3(100.0f, 360.0f + 240.0f, 0.0f));	// �O��̈ʒu
					break;
				case 3:
					m_apAnswer[nCnt]->SetPos(D3DXVECTOR3(1200.0f, 360.0f + 240.0f, 0.0f));		// �ʒu
					m_apAnswer[nCnt]->SetPosOld(D3DXVECTOR3(1180.0f, 360.0f + 240.0f, 0.0f));	// �O��̈ʒu
					break;
				}
				m_apAnswer[nCnt]->SetRot(NONE_D3DXVECTOR3);							// ����
				m_apAnswer[nCnt]->SetSize(D3DXVECTOR3(30.0f, 30.0f, 0.0f));			// �T�C�Y
				m_apAnswer[nCnt]->SetLength();										// ����
				m_apAnswer[nCnt]->SetAngle();										// ����
				m_apAnswer[nCnt]->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_checkbox00.png"));		// �e�N�X�`���̊��蓖�ď���

				// ���_���W�̐ݒ菈��
				m_apAnswer[nCnt]->SetVertex();
			}
		}
	}
	else
	{
		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			if (m_apAnswer[nCnt] == NULL)
			{
				m_apAnswer[nCnt] = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);

				switch (nCnt)
				{
				case 0:
					if (CTutorial::GetTutorial() == CTutorial::TUTORIAL_GIMMICK || CTutorial::GetTutorial() == CTutorial::TUTORIAL_LETS_GO || CTutorial::GetTutorial() == CTutorial::TUTORIAL_MAX)
					{
						m_apAnswer[nCnt]->SetPos(ANSWER_POS2);		// �ʒu
						m_apAnswer[nCnt]->SetPosOld(ANSWER_POS2);	// �O��̈ʒu
					}
					else
					{
						m_apAnswer[nCnt]->SetPos(ANSWER_POS);		// �ʒu
						m_apAnswer[nCnt]->SetPosOld(ANSWER_POS);	// �O��̈ʒu
					}
					break;
				case 1:
					m_apAnswer[nCnt]->SetPos(D3DXVECTOR3(m_apAnswer[0]->GetPos().x + ANSWER_DISTANCE, m_apAnswer[0]->GetPos().y, 0.0f));		// �ʒu
					m_apAnswer[nCnt]->SetPosOld(D3DXVECTOR3(m_apAnswer[0]->GetPos().x + ANSWER_DISTANCE, m_apAnswer[0]->GetPos().y, 0.0f));	// �O��̈ʒu
					break;
				case 2:
					m_apAnswer[nCnt]->SetPos(D3DXVECTOR3(m_apAnswer[0]->GetPos().x, m_apAnswer[0]->GetPos().y + ANSWER_DISTANCE, 0.0f));		// �ʒu
					m_apAnswer[nCnt]->SetPosOld(D3DXVECTOR3(m_apAnswer[0]->GetPos().x, m_apAnswer[0]->GetPos().y + ANSWER_DISTANCE, 0.0f));	// �O��̈ʒu
					break;
				case 3:
					m_apAnswer[nCnt]->SetPos(D3DXVECTOR3(m_apAnswer[0]->GetPos().x + ANSWER_DISTANCE, m_apAnswer[0]->GetPos().y + ANSWER_DISTANCE, 0.0f));		// �ʒu
					m_apAnswer[nCnt]->SetPosOld(D3DXVECTOR3(m_apAnswer[0]->GetPos().x + ANSWER_DISTANCE, m_apAnswer[0]->GetPos().y + ANSWER_DISTANCE, 0.0f));	// �O��̈ʒu
					break;
				}
				m_apAnswer[nCnt]->SetRot(NONE_D3DXVECTOR3);										// ����
				m_apAnswer[nCnt]->SetSize(D3DXVECTOR3(ANSWER_SIZE, ANSWER_SIZE, 0.0f));			// �T�C�Y
				m_apAnswer[nCnt]->SetLength();													// ����
				m_apAnswer[nCnt]->SetAngle();													// ����
				m_apAnswer[nCnt]->SetVtxColor(m_Color);											// �F
				m_apAnswer[nCnt]->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_checkbox00.png"));		// �e�N�X�`���̊��蓖�ď���

																																	// ���_���W�̐ݒ菈��
				m_apAnswer[nCnt]->SetVertex();
			}
		}

		for (int nCnt = 0; nCnt < 4; nCnt++)
		{
			if (m_apPlayerID[nCnt] == NULL)
			{
				m_apPlayerID[nCnt] = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
				m_apPlayerID[nCnt]->SetPos(D3DXVECTOR3(m_apAnswer[nCnt]->GetPos().x, m_apAnswer[nCnt]->GetPos().y, 0.0f));		// �ʒu
				m_apPlayerID[nCnt]->SetPosOld(D3DXVECTOR3(m_apAnswer[nCnt]->GetPos().x, m_apAnswer[nCnt]->GetPos().y, 0.0f));	// �O��̈ʒu
				m_apPlayerID[nCnt]->SetRot(NONE_D3DXVECTOR3);						// ����
				m_apPlayerID[nCnt]->SetSize(D3DXVECTOR3(ANSWER_SIZE * 1.1f, ANSWER_SIZE * 1.1f, 0.0f));		// �T�C�Y
				m_apPlayerID[nCnt]->SetLength();									// ����
				m_apPlayerID[nCnt]->SetAngle();										// ����
				m_apPlayerID[nCnt]->SetVtxColor(m_Color);							// �F

				switch (nCnt)
				{
				case 0:
					m_apPlayerID[nCnt]->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\PlayerID_1P.png"));		// �e�N�X�`���̊��蓖�ď���
					break;
				case 1:
					m_apPlayerID[nCnt]->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\PlayerID_2P.png"));		// �e�N�X�`���̊��蓖�ď���
					break;
				case 2:
					m_apPlayerID[nCnt]->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\PlayerID_3P.png"));		// �e�N�X�`���̊��蓖�ď���
					break;
				case 3:
					m_apPlayerID[nCnt]->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\PlayerID_4P.png"));		// �e�N�X�`���̊��蓖�ď���
					break;
				default:
					break;
				}

				// ���_���W�̐ݒ菈��
				m_apPlayerID[nCnt]->SetVertex();
			}
		}
	}

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_abPressAnswer[nCnt] = false;
	}
}

//=======================================
// ��������
//=======================================
CAnswer* CAnswer::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CAnswer* pSample = nullptr;	// �Ԏ����͂̃��A�N�V�����̃C���X�^���X�𐶐�

	if (pSample == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

	  // �C���X�^���X�𐶐�
		pSample = new CAnswer;
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
		pSample->SetData();
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