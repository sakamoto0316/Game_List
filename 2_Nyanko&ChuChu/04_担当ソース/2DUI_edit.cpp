//============================================
//
//	2D�G�f�B�b�g [2DUI_edit.cpp]
//	Author:sakamoto kai
//
//============================================
#include "2DUI_edit.h"
#include "object.h"
#include "object2D.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"
#include "Effect.h"
#include "debugproc.h"
#include "texture.h"
#include "useful.h"

//�}�N����`
#define NUM_OBJECT (8)						//�}�b�v�ɏo���I�u�W�F�N�g�̎�ސ�
#define START_OK ("STARTSETUI")				//�X�^�[�g���b�Z�[�W�����邩�ǂ����̊m�F
#define END_SET_OK ("ENDSETUI")				//�G���h���b�Z�[�W�����邩�ǂ����̊m�F
#define UI_SET ("STARTSET")					//�u���b�N�̃Z�b�g���b�Z�[�W
#define DELETE_WIGHT (45.0f)				//�폜�����̉��̍폜�͈�
#define DELETE_HEIGHT (45.0f)				//�폜�����̏c�̍폜�͈�
#define SIDE_PRESSCOUNT (30)				//���ɑf�����ړ�����܂ł̃J�E���g
#define MOVE_POS (10.0f)					//�ړ�����

// �ÓI�����o�ϐ��錾
C2DUIEdit::UIINFO C2DUIEdit::m_aTextureInfo[UI_LABEL_MAX] =
{
	{ "data\\TEXTURE\\Balloon.png","�T���v��00" },
	{ "data\\TEXTURE\\CageMark.png","�T���v��01" },
	{ "data\\TEXTURE\\Dstr003.png","�T���v��02" },
};
CObject2D *C2DUIEdit::m_pEditUI = NULL;			//�u���b�N�ւ̃|�C���^

//====================================================================
//�R���X�g���N�^
//====================================================================
C2DUIEdit::C2DUIEdit()
{
	m_EditPos = NONE_D3DXVECTOR3;
	m_EditRot = NONE_D3DXVECTOR3;
	m_EditSize = D3DXVECTOR3(100.0f,100.0f,0.0f);
	ObjectType = 0;
	m_nSideDistance = 10.0f;
	m_nSideCount = 0;
	m_cTextureName = m_aTextureInfo[ObjectType].pFilename;
}

//====================================================================
//�f�X�g���N�^
//====================================================================
C2DUIEdit::~C2DUIEdit()
{

}

//====================================================================
//��������
//====================================================================
C2DUIEdit *C2DUIEdit::Create()
{
	C2DUIEdit *pMap = NULL;

	if (pMap == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pMap = new C2DUIEdit();
	}

	m_pEditUI = CObject2D::Create(CObject2D::TYPE_NONE, CObject::TYPE_EDITUI, CObject::PRIORITY_UI);
	m_pEditUI->SetPos(D3DXVECTOR3(-200.0f, -200.0f, 0.0f));
	m_pEditUI->SetRot(NONE_D3DXVECTOR3);
	m_pEditUI->SetSize(D3DXVECTOR3(100.0f, 100.0f, 0.0f));
	m_pEditUI->SetAngle();				// ����
	m_pEditUI->SetLength();				// ����

	// �e�N�X�`���̓ǂݍ��ݏ���
	m_pEditUI->BindTexture(CManager::Get()->GetTexture()->Regist(C2DUIEdit::m_aTextureInfo[0].pFilename));

	return pMap;
}

//====================================================================
//�I������
//====================================================================
void C2DUIEdit::Uninit(void)
{

}


//====================================================================
//�X�V����
//====================================================================
void C2DUIEdit::Update(void)
{
	CObject2D *pEditUI = NULL;

	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::Get()->GetInputKeyboard();

	//�G�f�B�b�g�̈ʒu�𓮂���----------------------------------------------------------
	if (pInputKeyboard->GetTrigger(DIK_W) == true)
	{
		m_EditPos.y -= MOVE_POS;
	}
	if (pInputKeyboard->GetTrigger(DIK_S) == true)
	{
		m_EditPos.y += MOVE_POS;
	}

	if (pInputKeyboard->GetTrigger(DIK_A) == true)
	{
		m_EditPos.x -= MOVE_POS;
	}
	if (pInputKeyboard->GetTrigger(DIK_D) == true)
	{
		m_EditPos.x += MOVE_POS;
	}

	//�������ړ�----------------------------------------------------------------------
	if (pInputKeyboard->GetPress(DIK_W) == true)
	{
		if (m_nSideCount > SIDE_PRESSCOUNT && m_nSideCount % 2 == 0)
		{
			m_EditPos.y -= MOVE_POS * 2.0f;
		}
		m_nSideCount++;
	}
	else if (pInputKeyboard->GetPress(DIK_S) == true)
	{
		if (m_nSideCount > SIDE_PRESSCOUNT && m_nSideCount % 2 == 0)
		{
			m_EditPos.y += MOVE_POS * 2.0f;
		}
		m_nSideCount++;
	}
	else if (pInputKeyboard->GetPress(DIK_A) == true)
	{
		if (m_nSideCount > SIDE_PRESSCOUNT && m_nSideCount % 2 == 0)
		{
			m_EditPos.x -= MOVE_POS * 2.0f;
		}
		m_nSideCount++;
	}
	else if (pInputKeyboard->GetPress(DIK_D) == true)
	{
		if (m_nSideCount > SIDE_PRESSCOUNT && m_nSideCount % 2 == 0)
		{
			m_EditPos.x += MOVE_POS * 2.0f;
		}
		m_nSideCount++;
	}

	if (pInputKeyboard->GetPress(DIK_A) == false &&
		pInputKeyboard->GetPress(DIK_D) == false &&
		pInputKeyboard->GetPress(DIK_W) == false &&
		pInputKeyboard->GetPress(DIK_S) == false)
	{
		m_nSideCount = 0;
	}

	//�I�u�W�F�N�g�؂�ւ�----------------------------------------------------------
	if (pInputKeyboard->GetTrigger(DIK_0) == true)
	{
		ObjectType++;

		if (ObjectType >= UI_LABEL_MAX)
		{
			ObjectType = 0;
		}

		m_cTextureName = m_aTextureInfo[ObjectType].pFilename;

		// �e�N�X�`���̓ǂݍ��ݏ���
		m_pEditUI->BindTexture(CManager::Get()->GetTexture()->Regist(m_cTextureName));
	}

	//�����ƈʒu�̐؂�ւ�----------------------------------------------------------
	if (pInputKeyboard->GetTrigger(DIK_9) == true)
	{
		m_EditRot.y += 1.57f;

		if (m_EditRot.y >= 6.0f)
		{
			m_EditRot.y = 0;
		}
	}

	//�Ƃ��̈ړ��͈͒���----------------------------------------------------------
	if (pInputKeyboard->GetTrigger(DIK_3) == true)
	{
		m_nSideDistance -= 5.0f;
	}
	if (pInputKeyboard->GetTrigger(DIK_4) == true)
	{
		m_nSideDistance += 5.0f;
	}

	//�Ƃ��̈ړ��͈͒���----------------------------------------------------------
	if (pInputKeyboard->GetTrigger(DIK_5) == true)
	{
		m_EditSize.x -= m_nSideDistance;
	}
	if (pInputKeyboard->GetTrigger(DIK_6) == true)
	{
		m_EditSize.x += m_nSideDistance;
	}
	if (pInputKeyboard->GetTrigger(DIK_7) == true)
	{
		m_EditSize.y -= m_nSideDistance;
	}
	if (pInputKeyboard->GetTrigger(DIK_8) == true)
	{
		m_EditSize.y += m_nSideDistance;
	}

	//�ʒu�X�V----------------------------------------------------------
	m_pEditUI->SetPos(m_EditPos);
	m_pEditUI->SetRot(m_EditRot);
	m_pEditUI->SetSize(m_EditSize);
	m_pEditUI->SetAngle();				// ����
	m_pEditUI->SetLength();				// ����

	//�I�u�W�F�N�g�ݒu----------------------------------------------------------
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		pEditUI = CObject2D::Create(CObject2D::TYPE_NONE, CObject::TYPE_2DUI, CObject::PRIORITY_UI);
		pEditUI->SetPos(m_EditPos);
		pEditUI->SetRot(m_EditRot);
		pEditUI->SetSize(m_EditSize);
		pEditUI->SetAngle();				// ����
		pEditUI->SetLength();				// ����
		pEditUI->BindTexture(CManager::Get()->GetTexture()->Regist(m_cTextureName));
	}

	if (pInputKeyboard->GetTrigger(DIK_BACKSPACE) == true)
	{
		DeleteObject(m_EditPos);
	}

	if (pInputKeyboard->GetTrigger(DIK_F9) == true)
	{
		SaveData();
	}

	DebugObject();
}

//====================================================================
//�폜����
//====================================================================
void C2DUIEdit::DeleteObject(D3DXVECTOR3 pos)
{
	for (int nCntPriority = 0; nCntPriority < CObject::PRIORITY_MAX; nCntPriority++)
	{
		//�I�u�W�F�N�g���擾
		CObject *pObj = CObject::GetTop((CObject::PRIORITY)nCntPriority);

		while (pObj != NULL)
		{
			CObject *pObjNext = pObj->GetNext();

			CObject::TYPE type = pObj->GetType();				//��ނ��擾

			if (type == CObject::TYPE_2DUI)
			{//��ނ��u���b�N�̎�
				CObject2D *pUI = (CObject2D*)pObj;

				if (useful::RectangleCollisionXY(pos, pUI->GetPos(), D3DXVECTOR3(DELETE_WIGHT, DELETE_HEIGHT, 0.0f), pUI->GetSize(), D3DXVECTOR3(-DELETE_WIGHT, -DELETE_HEIGHT, 0.0f), pUI->GetSize() * -1.0f) == true)
				{
					pUI->Uninit();
				}
			}

			pObj = pObjNext;
		}
	}
}

//====================================================================
//�f�o�b�O�\��
//====================================================================
void C2DUIEdit::DebugObject(void)
{
	CManager::Get()->GetDebugProc()->Print("\n%s\n", "�[�[�[�[�[�G�f�B�b�g���[�h�[�[�[�[�[");

	CManager::Get()->GetDebugProc()->Print("\n%s\n", "��������[�[");
	//�������
	CManager::Get()->GetDebugProc()->Print("%s\n", "�ړ��F[W],[A],[S],[D]");
	CManager::Get()->GetDebugProc()->Print("%s\n", "�T�C�Y�ύX�l�̉��~�㏸�F[�R�F�S]");
	CManager::Get()->GetDebugProc()->Print("%s\n", "UI�̉��T�C�Y�̉��~�㏸�F[�T�F�U]");
	CManager::Get()->GetDebugProc()->Print("%s\n", "UI�̏c�T�C�Y�̉��~�㏸�F[�V�F�W]");
	CManager::Get()->GetDebugProc()->Print("%s\n", "�I�u�W�F�N�g��]�F[�X]");

	CManager::Get()->GetDebugProc()->Print("\n%s\n", "�[�[�G�f�B�b�g���[�[");

	//�I�u�W�F�N�g
	CManager::Get()->GetDebugProc()->Print("�e�N�X�`���F[%s]\n", m_aTextureInfo[ObjectType].pCommentname);

	//�ʒu�E�����E�傫��
	CManager::Get()->GetDebugProc()->Print("�ʒu�F[%f:%f]\n", m_EditPos.x, m_EditPos.y);
	CManager::Get()->GetDebugProc()->Print("�T�C�Y�ύX�l�F[%f]\n", m_nSideDistance);
	CManager::Get()->GetDebugProc()->Print("�T�C�Y�F[%f:%f]\n", m_EditSize.x, m_EditSize.y);
	CManager::Get()->GetDebugProc()->Print("�����F[%f]\n", m_EditRot.y);

	//�Ƃ��̈ړ��͈�

	CManager::Get()->GetDebugProc()->Print("\n%s\n", "�[�[�[�[�[�G�f�B�b�g���[�h�[�[�[�[�[");
}

//====================================================================
//�ۑ�����
//====================================================================
void C2DUIEdit::SaveData(void)
{
	FILE *pFile; //�t�@�C���|�C���^��錾

	//�t�@�C�����J��
	pFile = fopen(LOADUI_NAME, "w");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

	 //�X�e�[�W���Z�[�u����J�n�̍��}
		fprintf(pFile, "%s\n\n", START_OK);

		for (int nCntPriority = 0; nCntPriority < CObject::PRIORITY_MAX; nCntPriority++)
		{
			//�I�u�W�F�N�g���擾
			CObject *pObj = CObject::GetTop((CObject::PRIORITY)nCntPriority);

			while (pObj != NULL)
			{
				CObject *pObjNext = pObj->GetNext();

				CObject::TYPE type = pObj->GetType();				//��ނ��擾

				if (type == CObject::TYPE_2DUI)
				{//��ނ��u���b�N�̎�
					CObject2D *pUI = (CObject2D*)pObj;

					fprintf(pFile, "%s\n", UI_SET);

					//�ʒu�̎擾
					fprintf(pFile, "%f ", pUI->GetPos().x);
					fprintf(pFile, "%f ", pUI->GetPos().y);
					fprintf(pFile, "%f\n", pUI->GetPos().z);

					//�����̎擾
					fprintf(pFile, "%f ", pUI->GetRot().x);
					fprintf(pFile, "%f ", pUI->GetRot().y);
					fprintf(pFile, "%f\n", pUI->GetRot().z);

					//�傫���̎擾
					fprintf(pFile, "%f ", pUI->GetSize().x);
					fprintf(pFile, "%f ", pUI->GetSize().y);
					fprintf(pFile, "%f\n", pUI->GetSize().z);

					fprintf(pFile, "%s\n", pUI->GetTexName());

					fprintf(pFile, "%s\n\n", "ENDSET");
				}

				pObj = pObjNext;
			}
		}

		//�X�e�[�W���Z�[�u�����I���̍��}
		fprintf(pFile, "%s", END_SET_OK);

		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		printf("***�t�@�C�����J���܂���ł���***\n");
	}
}

//====================================================================
//�}�b�v��S�Ė��߂Đ���
//====================================================================
void C2DUIEdit::LoadData(char *Name, D3DXVECTOR3 pos)
{
	FILE *pFile; //�t�@�C���|�C���^��錾

	//�t�@�C�����J��
	pFile = fopen(Name, "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ
		D3DXVECTOR3 SetPos = NONE_D3DXVECTOR3;
		D3DXVECTOR3 SetRot = NONE_D3DXVECTOR3;
		D3DXVECTOR3 SetSize = NONE_D3DXVECTOR3;
		char TexName[256] = {};
		char aStartMessage[32] = {};	//�X�^�[�g���b�Z�[�W
		char aSetMessage[32] = {};		//�Z�b�g���b�Z�[�W

		fscanf(pFile, "%s", &aStartMessage[0]);
		if (strcmp(&aStartMessage[0], START_OK) == 0)
		{
			while (1)
			{
				fscanf(pFile, "%s", &aSetMessage[0]);
				if (strcmp(&aSetMessage[0], END_SET_OK) == 0)
				{
					break;
				}
				else if (strcmp(&aSetMessage[0], UI_SET) == 0)
				{
					fscanf(pFile, "%f", &SetPos.x);
					fscanf(pFile, "%f", &SetPos.y);
					fscanf(pFile, "%f", &SetPos.z);
					fscanf(pFile, "%f", &SetRot.x);
					fscanf(pFile, "%f", &SetRot.y);
					fscanf(pFile, "%f", &SetRot.z);
					fscanf(pFile, "%f", &SetSize.x);
					fscanf(pFile, "%f", &SetSize.y);
					fscanf(pFile, "%f", &SetSize.z);
					fscanf(pFile, "%s", &TexName[0]);
					fscanf(pFile, "%s", &aSetMessage[0]);

					CObject2D *pUI = CObject2D::Create(CObject2D::TYPE_NONE, CObject::TYPE_2DUI, CObject::PRIORITY_UI);
					pUI->SetPos(pos + SetPos);
					pUI->SetRot(SetRot);
					pUI->SetSize(SetSize);
					pUI->SetAngle();				// ����
					pUI->SetLength();				// ����
					pUI->BindTexture(CManager::Get()->GetTexture()->Regist(TexName));
				}
			}
		}
		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		printf("***�t�@�C�����J���܂���ł���***\n");
	}
}