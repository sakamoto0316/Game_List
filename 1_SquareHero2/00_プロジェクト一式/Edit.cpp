//============================================
//
//	�G�f�B�b�g [Edit.cpp]
//	Author:sakamoto kai
//
//============================================
#include "Edit.h"
#include "object.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "input.h"
#include "objmeshCube.h"
#include "CubeBlock.h"
#include "debugproc.h"

//�}�N����`


//�ÓI�����o�ϐ��錾

//====================================================================
//�R���X�g���N�^
//====================================================================
CEdit::CEdit()
{
	if (m_pEditBlock == nullptr)
	{
		m_pEditBlock = CObjmeshCube::Create();
		m_pEditBlock->SetSize(D3DXVECTOR3(100.0f, 10.0f, 100.0f));
	}

	MoveWidth = 100.0f;
}

//====================================================================
//�f�X�g���N�^
//====================================================================
CEdit::~CEdit()
{

}

//====================================================================
//��������
//====================================================================
CEdit* CEdit::Create()
{
	CEdit* pMap = NULL;

	if (pMap == NULL)
	{
		//�I�u�W�F�N�g2D�̐���
		pMap = new CEdit();
	}

	return pMap;
}

//====================================================================
//�I������
//====================================================================
void CEdit::Uninit(void)
{

}

//====================================================================
//�X�V����
//====================================================================
void CEdit::Update(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	if (pInputKeyboard->GetTrigger(DIK_W) == true)
	{
		m_pEditBlock->SetPos(D3DXVECTOR3(m_pEditBlock->GetPos().x, m_pEditBlock->GetPos().y, m_pEditBlock->GetPos().z + MoveWidth));
	}

	if (pInputKeyboard->GetTrigger(DIK_S) == true)
	{
		m_pEditBlock->SetPos(D3DXVECTOR3(m_pEditBlock->GetPos().x, m_pEditBlock->GetPos().y, m_pEditBlock->GetPos().z - MoveWidth));
	}

	if (pInputKeyboard->GetTrigger(DIK_A) == true)
	{
		m_pEditBlock->SetPos(D3DXVECTOR3(m_pEditBlock->GetPos().x - MoveWidth, m_pEditBlock->GetPos().y, m_pEditBlock->GetPos().z));
	}

	if (pInputKeyboard->GetTrigger(DIK_D) == true)
	{
		m_pEditBlock->SetPos(D3DXVECTOR3(m_pEditBlock->GetPos().x + MoveWidth, m_pEditBlock->GetPos().y, m_pEditBlock->GetPos().z));
	}

	if (pInputKeyboard->GetTrigger(DIK_LSHIFT) == true)
	{
		m_pEditBlock->SetPos(D3DXVECTOR3(m_pEditBlock->GetPos().x, m_pEditBlock->GetPos().y + MoveWidth, m_pEditBlock->GetPos().z));
	}

	if (pInputKeyboard->GetTrigger(DIK_LCONTROL) == true)
	{
		m_pEditBlock->SetPos(D3DXVECTOR3(m_pEditBlock->GetPos().x, m_pEditBlock->GetPos().y - MoveWidth, m_pEditBlock->GetPos().z));
	}

	if (pInputKeyboard->GetTrigger(DIK_E) == true)
	{
		m_pEditBlock->SetSize(D3DXVECTOR3(m_pEditBlock->GetSize().x + MoveWidth, m_pEditBlock->GetSize().y, m_pEditBlock->GetSize().z));
	}

	if (pInputKeyboard->GetTrigger(DIK_C) == true)
	{
		m_pEditBlock->SetSize(D3DXVECTOR3(m_pEditBlock->GetSize().x - MoveWidth, m_pEditBlock->GetSize().y, m_pEditBlock->GetSize().z));
	}

	if (pInputKeyboard->GetTrigger(DIK_Q) == true)
	{
		m_pEditBlock->SetSize(D3DXVECTOR3(m_pEditBlock->GetSize().x, m_pEditBlock->GetSize().y, m_pEditBlock->GetSize().z + MoveWidth));
	}

	if (pInputKeyboard->GetTrigger(DIK_Z) == true)
	{
		m_pEditBlock->SetSize(D3DXVECTOR3(m_pEditBlock->GetSize().x, m_pEditBlock->GetSize().y, m_pEditBlock->GetSize().z - MoveWidth));
	}

	if (pInputKeyboard->GetTrigger(DIK_UP) == true)
	{
		m_pEditBlock->SetSize(D3DXVECTOR3(m_pEditBlock->GetSize().x, m_pEditBlock->GetSize().y + MoveWidth, m_pEditBlock->GetSize().z));
	}

	if (pInputKeyboard->GetTrigger(DIK_DOWN) == true)
	{
		m_pEditBlock->SetSize(D3DXVECTOR3(m_pEditBlock->GetSize().x, m_pEditBlock->GetSize().y - MoveWidth, m_pEditBlock->GetSize().z));
	}

	if (pInputKeyboard->GetTrigger(DIK_RIGHT) == true)
	{
		MoveWidth += 10.0f;
	}

	if (pInputKeyboard->GetTrigger(DIK_LEFT) == true)
	{
		MoveWidth -= 10.0f;
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		CCubeBlock* pBlock = CCubeBlock::Create();
		pBlock->SetPos(m_pEditBlock->GetPos());
		pBlock->SetSize(m_pEditBlock->GetSize());
	}

	if (pInputKeyboard->GetTrigger(DIK_BACKSPACE) == true)
	{
		CollisionBlock();
	}

	if (pInputKeyboard->GetTrigger(DIK_F9) == true)
	{
		SaveData();
	}

	//�f�o�b�O�\���̎擾
	CDebugProc* pDebugProc = CManager::GetInstance()->GetDebugProc();
	pDebugProc->Print("%f:%f:%f\n", m_pEditBlock->GetPos().x, m_pEditBlock->GetPos().y, m_pEditBlock->GetPos().z);
	pDebugProc->Print("%f:%f:%f\n", m_pEditBlock->GetSize().x, m_pEditBlock->GetSize().y, m_pEditBlock->GetSize().z);
	pDebugProc->Print("%f\n", MoveWidth);
}

//====================================================================
//�e�̓����蔻�菈��
//====================================================================
void CEdit::CollisionBlock(void)
{
	if (m_pEditBlock != nullptr)
	{
		for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
		{
			//�I�u�W�F�N�g���擾
			CObject* pObj = CObject::GetTop(nCntPriority);

			while (pObj != NULL)
			{
				CObject* pObjNext = pObj->GetNext();

				CObject::TYPE type = pObj->GetType();			//��ނ��擾

				if (type == CObject::TYPE_CUBEBLOCK)
				{//��ނ��u���b�N�̎�
					CCubeBlock* pBlock = (CCubeBlock*)pObj;

					D3DXVECTOR3 MyPos = m_pEditBlock->GetPos();
					D3DXVECTOR3 MySize = m_pEditBlock->GetSize() * 2.0f;
					D3DXVECTOR3 BlockPos = pBlock->GetPos();
					D3DXVECTOR3 BlockSize = pBlock->GetSize();
					D3DXVECTOR3 BlockMove = pBlock->GetMove();

					if (BlockPos.x + BlockSize.x > MyPos.x &&
						BlockPos.x - BlockSize.x < MyPos.x &&
						BlockPos.z + BlockSize.z > MyPos.z &&
						BlockPos.z - BlockSize.z < MyPos.z &&
						BlockPos.y + BlockSize.y > MyPos.y &&
						BlockPos.y - BlockSize.y < MyPos.y)
					{
						pBlock->Uninit();
					}
				}
				pObj = pObjNext;
			}
		}
	}
}

//====================================================================
//�ۑ�����
//====================================================================
void CEdit::SaveData(void)
{
	FILE* pFile; //�t�@�C���|�C���^��錾

	//�t�@�C�����J��
	pFile = fopen(DATA_NAME, "w");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

	 //�X�e�[�W���Z�[�u����J�n�̍��}
		fprintf(pFile, "%s\n\n", "STARTSETSTAGE");

		for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
		{
			//�I�u�W�F�N�g���擾
			CObject* pObj = CObject::GetTop(nCntPriority);

			while (pObj != NULL)
			{
				CObject* pObjNext = pObj->GetNext();

				CObject::TYPE type = pObj->GetType();				//��ނ��擾

				if (type == CObject::TYPE_CUBEBLOCK)
				{//��ނ��u���b�N�̎�
					CCubeBlock* pBlock = (CCubeBlock*)pObj;

					fprintf(pFile, "%s\n", "STARTSETBLOCK");

					//�X�e�[�W���Z�[�u�����I���̍��}
					fprintf(pFile, "POS %f %f %f\n", pBlock->GetPos().x, pBlock->GetPos().y, pBlock->GetPos().z);
					fprintf(pFile, "SIZE %f %f %f\n", pBlock->GetSize().x, pBlock->GetSize().y, pBlock->GetSize().z);

					fprintf(pFile, "%s\n\n", "ENDSETBLOCK");
				}

				pObj = pObjNext;
			}
		}

		//�X�e�[�W���Z�[�u�����I���̍��}
		fprintf(pFile, "%s", "ENDSETSTAGE");

		fclose(pFile);
	}
	else
	{//�t�@�C�����J���Ȃ������ꍇ
		printf("***�t�@�C�����J���܂���ł���***\n");
	}
}