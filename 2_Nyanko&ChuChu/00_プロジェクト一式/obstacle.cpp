//===========================================
//
// ��Q���̃��C������[obstacle.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "obstacle.h"
#include "obstacle_manager.h"
#include "useful.h"
#include "objectbillboard.h"
#include "texture.h"

#include "honey.h"
#include "slime.h"
#include "hairball.h"
#include "petbottle.h"
#include "toycar.h"
#include "roomba.h"
#include "Himo.h"
#include "speaker.h"
#include "mousetrap.h"
#include "leash.h"
#include "Pin.h"
#include "electricfan.h"
#include "cup.h"
#include "garbagecan.h"
#include "tv.h"
#include "dynamite.h"
#include "book.h"
#include "curtain.h"
#include "ratmecha.h"
#include "game.h"
#include "tutorial.h"

//==============================
// �R���X�g���N�^
//==============================
CObstacle::CObstacle() : CModel(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �R���X�g���N�^�̔�
	Box();
}

//==============================
// �I�[�o�[���[�h�R���X�g���N�^
//==============================
CObstacle::CObstacle(CObject::TYPE type, PRIORITY priority) : CModel(type, priority)
{
	// �R���X�g���N�^�̔�
	Box();
}

//==============================
// �f�X�g���N�^
//==============================
CObstacle::~CObstacle()
{

}

//==============================
// �R���X�g���N�^�̔�
//==============================
void CObstacle::Box(void)
{
	// �S�Ă̒l���N���A����
	m_type = TYPE_HONEY;	// ���
	m_pPrev = nullptr;		// �O�̂ւ̃|�C���^
	m_pNext = nullptr;		// ���̂ւ̃|�C���^
	m_pGimmickUI = NULL;
	m_pMultiGimmickUI[0] = NULL;
	m_pMultiGimmickUI[1] = NULL;
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_pGimmickUIFalse[nCnt] = false;
	}
	m_bCatUse = false;
	m_bRatUse = false;
	m_bAction = false;
	m_fAlpha = 1.0f;
	m_bCatDisp = false;
	m_bRatDisp = false;

	if (CObstacleManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// �}�l�[�W���[�ւ̓o�^����
		CObstacleManager::Get()->Regist(this);
	}
}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
void CObstacle::SetPrev(CObstacle* pPrev)
{
	// �O�̃|�C���^��ݒ肷��
	m_pPrev = pPrev;
}

//============================
// ��̃|�C���^�̐ݒ菈��
//============================
void CObstacle::SetNext(CObstacle* pNext)
{
	// ���̃|�C���^��ݒ肷��
	m_pNext = pNext;
}

//============================
// �O�̃|�C���^�̐ݒ菈��
//============================
CObstacle* CObstacle::GetPrev(void) const
{
	// �O�̃|�C���^��Ԃ�
	return m_pPrev;
}

//============================
// ���̃|�C���^�̐ݒ菈��
//============================
CObstacle* CObstacle::GetNext(void) const
{
	// ���̃|�C���^��Ԃ�
	return m_pNext;
}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CObstacle::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_type = TYPE_HONEY;	// ���

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �j�Ђ̏I������
//========================================
void CObstacle::Uninit(void)
{
	// �I������
	CModel::Uninit();

	if (CObstacleManager::Get() != nullptr)
	{ // �}�l�[�W���[�����݂��Ă����ꍇ

		// ���X�g�\���̈�����������
		CObstacleManager::Get()->Pull(this);
	}

	if (m_pGimmickUI != NULL)
	{
		m_pGimmickUI->Uninit();
		m_pGimmickUI = NULL;
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pMultiGimmickUI[nCnt] != NULL)
		{
			m_pMultiGimmickUI[nCnt]->Uninit();
			m_pMultiGimmickUI[nCnt] = NULL;
		}
	}

	// ���X�g�\���֌W�̃|�C���^�� NULL �ɂ���
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CObstacle::Update(void)
{
	if (m_pGimmickUI != NULL)
	{
		m_pGimmickUI->Update();
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pMultiGimmickUI[nCnt] != NULL)
		{
			m_pMultiGimmickUI[nCnt]->Update();
		}
	}
}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CObstacle::Draw(void)
{
	// �`�揈��
	CModel::Draw();

	if (m_pGimmickUI != NULL)
	{
		m_pGimmickUI->DrawLightOff();
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pMultiGimmickUI[nCnt] != NULL)
		{
			m_pMultiGimmickUI[nCnt]->Draw();
		}
	}
}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CObstacle::Draw(const float fAlpha)
{
	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{// �ǂ̃v���C���[�̃J�����ԍ����񂵂Ċm���߂�
		if (CManager::Get()->GetMode() == CScene::MODE_GAME)
		{// �Q�[�����[�h�̎�
			CPlayer* pPlayer = CGame::GetPlayer(nCnt);
			if (pPlayer->GetType() == CPlayer::TYPE::TYPE_CAT)
			{// �l�R�v���C���[���擾
				if (pPlayer->GetPlayerIdx() == GetDrawIdx())
				{// �J�����ԍ��ƃv���C���[�ԍ�����v���鎞

					if (m_bCatDisp == true)
					{// �ϐ���true�̎������I�ɕ\������

						// �`�揈��
						CModel::Draw(1.0f);
					}
					else
					{// �ϐ���false�̎�
						if (m_bCatUse == false && m_bAction == false)
						{// �l�R���g�p�\�ȏ�Q���̏ꍇ���ʂɕ`��
							// �`�揈��
							CModel::Draw(0.3f);
						}
						else
						{// �l�R���g�p�ł��Ȃ���Q���̏ꍇ�����\��
							// �`�揈��
							CModel::Draw(fAlpha);
						}
					}
				}
			}
			else if (pPlayer->GetType() == CPlayer::TYPE::TYPE_RAT)
			{// �l�Y�~�v���C���[���擾
				if (pPlayer->GetPlayerIdx() == GetDrawIdx())
				{// �J�����ԍ��ƃv���C���[�ԍ�����v���鎞
					if (m_bRatDisp == true)
					{// �ϐ���true�̎������I�ɕ\������

						// �`�揈��
						CModel::Draw(1.0f);
					}
					else
					{// �ϐ���false�̎�
						if (m_bRatUse == false && m_bAction == false)
						{// �l�R���g�p�\�ȏ�Q���̏ꍇ���ʂɕ`��
							// �`�揈��
							CModel::Draw(0.3f);
						}
						else
						{// �l�R���g�p�ł��Ȃ���Q���̏ꍇ�����\��
							// �`�揈��
							CModel::Draw(fAlpha);
						}
					}
				}
			}
		}
		else if (CManager::Get()->GetMode() == CScene::MODE_TUTORIAL)
		{
			CPlayer* pPlayer = CTutorial::GetPlayer(nCnt);
			if (pPlayer->GetType() == CPlayer::TYPE::TYPE_CAT)
			{
				if (pPlayer->GetPlayerIdx() == GetDrawIdx())
				{
					// �`�揈��
					CModel::Draw(fAlpha);
				}
			}
			else if (pPlayer->GetType() == CPlayer::TYPE::TYPE_RAT)
			{
				if (pPlayer->GetPlayerIdx() == GetDrawIdx())
				{
					// �`�揈��
					CModel::Draw(fAlpha);
				}
			}
		}
	}
	//// �`�揈��
	//CModel::Draw(fAlpha);

	if (m_pGimmickUI != NULL)
	{
		m_pGimmickUI->DrawLightOff();
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pMultiGimmickUI[nCnt] != NULL)
		{
			m_pMultiGimmickUI[nCnt]->Draw();
		}
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CObstacle::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// ���̐ݒ菈��
	SetPos(pos);							// �ʒu
	SetPosOld(pos);							// �O��̈ʒu
	SetRot(rot);							// ����
	SetScale(NONE_SCALE);					// �g�嗦
	SetFileData((CXFile::TYPE)(INIT_OBSTACLE + type));	// ���f�����

	// �S�Ă̒l������������
	m_type = type;		// ���
}

//=======================================
// ��������
//=======================================
CObstacle* CObstacle::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CObstacle* pObstacle = nullptr;	// �C���X�^���X�𐶐�

	if (pObstacle == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		switch (type)
		{
		case CObstacle::TYPE_HONEY:

			// �I���𐶐�����
			pObstacle = new CHoney;

			break;

		case CObstacle::TYPE_SLIME:

			// �X���C���𐶐�����
			pObstacle = new CSlime;

			break;

		case CObstacle::TYPE_HAIRBALL:

			// �{�𐶐�����
			pObstacle = new CHairBall;

			break;

		case CObstacle::TYPE::TYPE_PETBOTTLE:

			//�y�b�g�{�g���𐶐�����
			pObstacle = new CPetbottle;

			break;

		case CObstacle::TYPE_TOYCAR:

			// ��������̎Ԃ𐶐�����
			pObstacle = new CToyCar;

			break;

		case CObstacle::TYPE_ROOMBA:

			// �����o�𐶐�����
			pObstacle = new CRoomba;
			
			break;

		case CObstacle::TYPE_HIMO:		//�N���n

			// �Ђ��𐶐�����
			pObstacle = new CHimo;

			break;

		case CObstacle::TYPE_SPEAKER:	//�N���n

			// �X�s�[�J�[�𐶐�����
			pObstacle = new CSpeaker;

			break;

		case CObstacle::TYPE_MOUSETRAP:

			// �l�Y�~�߂�𐶐�����
			pObstacle = new CMouseTrap;

			break;

		case CObstacle::TYPE_LEASH:		//2�l�ŋN���n

			// ���[�h�𐶐�����
			pObstacle = new CLeash;

			break;

		case CObstacle::TYPE_PIN:		//�N���n

			// ��e�𐶐�����
			pObstacle = new CPin;

			break;

		case CObstacle::TYPE_FAN:		// �N���n

			// ��@�𐶐�����
			pObstacle = new CElecFan;

			break;

		case CObstacle::TYPE_CUP:		// �N���n

			// �R�b�v�𐶐�����
			pObstacle = new CCup;

			break;

		case CObstacle::TYPE_GARBAGECAN:		// �N���n

			// �S�~���𐶐�����
			pObstacle = new CGarbage;

			break;

		case CObstacle::TYPE_TV:		// �e���r

			// �e���r�𐶐�����
			pObstacle = new CTv;

			break;

		case CObstacle::TYPE_DYNAMITE:		// ���e

			// �_�C�i�}�C�g�𐶐�����
			pObstacle = new CDynamite;

			break;

		case CObstacle::TYPE_BOOK:

			// �{�𐶐�����
			pObstacle = new CBook;

			break;

		case CObstacle::TYPE_REDKATEN:

			// �J�[�e���𐶐�����
			pObstacle = new CCurtain;

			break;

		case CObstacle::TYPE_RATMECHA:

			// �J�[�e���𐶐�����
			pObstacle = new CRatMecha;

			break;

		default:

			//��~
			assert(false);

			break;
		}
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pObstacle != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pObstacle->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pObstacle->SetData(pos, rot, type);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// ��Q���̃|�C���^��Ԃ�
	return pObstacle;
}

//=====================================
// �����蔻�菈��
//=====================================
bool CObstacle::Collision(CPlayer* /*pPlayer*/, const D3DXVECTOR3& /*collSize*/)
{
	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CObstacle::Hit(CPlayer* /*pPlayer*/, const D3DXVECTOR3& /*collSize*/)
{
	// false ��Ԃ�
	return false;
}

//=====================================
// �M�~�b�N�N��UI�̕\��
//=====================================
void CObstacle::GimmickUI(bool Set, int Player_Idx)
{
	if (Set == true)
	{//UI�\���͈͓̔��ɂ���ꍇ
		if (m_pGimmickUI == NULL)
		{
			if (m_bAction == false)
			{
				//������UI�\����Ԃ�ON�ɂ���
				m_pGimmickUIFalse[Player_Idx] = true;

				//UI�̕\��
				m_pGimmickUI = CBillboard::Create(TYPE_NONE, PRIORITY_UI);
				m_pGimmickUI->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\UI_GimmickOn.png"));
				m_pGimmickUI->SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0f));

				if (m_type == TYPE::TYPE_HIMO)
				{
					m_pGimmickUI->SetPos(D3DXVECTOR3(
						GetPos().x,
						GetPos().y - 400.0f,
						GetPos().z));
					m_pGimmickUI->SetPosOld(D3DXVECTOR3(
						GetPos().x,
						GetPos().y - 400.0f,
						GetPos().z));
					m_pGimmickUI->SetVertex();
				}
				else if (m_type == TYPE::TYPE_TV)
				{
					m_pGimmickUI->SetPos(D3DXVECTOR3(
						GetPos().x,
						GetPos().y + 310.0f,
						GetPos().z));
					m_pGimmickUI->SetPosOld(D3DXVECTOR3(
						GetPos().x,
						GetPos().y + 310.0f,
						GetPos().z));
					m_pGimmickUI->SetVertex();
				}
				else
				{
					m_pGimmickUI->SetPos(D3DXVECTOR3(
						GetPos().x,
						GetPos().y + 50.0f,
						GetPos().z));
					m_pGimmickUI->SetPosOld(D3DXVECTOR3(
						GetPos().x,
						GetPos().y + 50.0f,
						GetPos().z));
					m_pGimmickUI->SetVertex();
				}
			}
		}
	}
	else
	{//UI�\���͈͓̔��ɂ��Ȃ��ꍇ

		//������UI�\����Ԃ�OFF�ɂ���
		m_pGimmickUIFalse[Player_Idx] = false;
	}

	//�S�Ẵv���C���[�̕\����Ԃ�OFF�̂Ƃ��폜����
	if (m_pGimmickUIFalse[0] == false &&
		m_pGimmickUIFalse[1] == false &&
		m_pGimmickUIFalse[2] == false &&
		m_pGimmickUIFalse[3] == false)
	{
		if (m_pGimmickUI != NULL)
		{
			m_pGimmickUI->Uninit();
			m_pGimmickUI = NULL;
		}
	}
}

//=====================================
// �M�~�b�N�N��UI�̕\��
//=====================================
void CObstacle::MultiGimmickUI(bool Set, int Player_Idx)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (Set == true)
		{//UI�\���͈͓̔��ɂ���ꍇ
			if (m_pMultiGimmickUI[nCnt] == NULL)
			{
				//������UI�\����Ԃ�ON�ɂ���
				m_pGimmickUIFalse[Player_Idx] = true;

				//UI�̕\��
				m_pMultiGimmickUI[nCnt] = CBillboard::Create(TYPE_NONE, PRIORITY_UI);
				m_pMultiGimmickUI[nCnt]->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\UI_GimmickOn.png"));
				m_pMultiGimmickUI[nCnt]->SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0f));
				if (nCnt == 0)
				{
					m_pMultiGimmickUI[nCnt]->SetPos(D3DXVECTOR3(
						GetPosHead().x,
						GetPosHead().y + 50.0f,
						GetPosHead().z));
					m_pMultiGimmickUI[nCnt]->SetPosOld(D3DXVECTOR3(
						GetPosHead().x,
						GetPosHead().y + 50.0f,
						GetPosHead().z));
				}
				else if (nCnt == 1)
				{
					m_pMultiGimmickUI[nCnt]->SetPos(D3DXVECTOR3(
						GetPosToes().x,
						GetPosToes().y + 50.0f,
						GetPosToes().z));
					m_pMultiGimmickUI[nCnt]->SetPosOld(D3DXVECTOR3(
						GetPosToes().x,
						GetPosToes().y + 50.0f,
						GetPosToes().z));
				}
				m_pMultiGimmickUI[nCnt]->SetVertex();
			}
		}
		else
		{//UI�\���͈͓̔��ɂ��Ȃ��ꍇ

		 //������UI�\����Ԃ�OFF�ɂ���
			m_pGimmickUIFalse[Player_Idx] = false;
		}

		//�S�Ẵv���C���[�̕\����Ԃ�OFF�̂Ƃ��폜����
		if (m_pGimmickUIFalse[0] == false &&
			m_pGimmickUIFalse[1] == false &&
			m_pGimmickUIFalse[2] == false &&
			m_pGimmickUIFalse[3] == false)
		{
			if (m_pMultiGimmickUI[nCnt] != NULL)
			{
				m_pMultiGimmickUI[nCnt]->Uninit();
				m_pMultiGimmickUI[nCnt] = NULL;
			}
		}
	}
}

//=======================================
// ��ނ̐ݒ菈��
//=======================================
void CObstacle::SetType(const TYPE type)
{
	// ��ނ�ݒ肷��
	m_type = type;
}

//=======================================
// ��ނ̎擾����
//=======================================
CObstacle::TYPE CObstacle::GetType(void)
{
	// ��ނ�Ԃ�
	return m_type;
}