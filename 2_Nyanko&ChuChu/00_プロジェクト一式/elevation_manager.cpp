//============================================
//
// �N���}�l�[�W���[����[elevation_manager.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "elevation_manager.h"
#include "objectElevation.h"

//--------------------------------------------
// �ÓI�����o�ϐ��錾
//--------------------------------------------
CElevationManager* CElevationManager::m_pManager = nullptr;			// �v���C���[�̕ϐ�

//============================
// �R���X�g���N�^
//============================
CElevationManager::CElevationManager()
{
	// �S�Ă̒l���N���A����
	m_pTop = nullptr;		// �擪�̃I�u�W�F�N�g
	m_nNumAll = 0;			// �N���̐�
}

//============================
// �o�^����
//============================
void CElevationManager::Regist(CElevation* pThis)
{
	if (m_pTop == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �擪�̃|�C���^�Ɏ������g����
		m_pTop = pThis;

		// �O�̃I�u�W�F�N�g�ւ̃|�C���^��ݒ肷��
		pThis->SetPrev(nullptr);

		// ���̃I�u�W�F�N�g�ւ̃|�C���^��ݒ肷��
		pThis->SetNext(nullptr);
	}
	else
	{ // ��L�ȊO

		// ���[�J���|�C���^��錾
		CElevation* pObject = m_pTop;			// �擪�̃I�u�W�F�N�g

		while (pObject->GetNext() != nullptr)
		{ // �I�u�W�F�N�g�����������

			// ���̃I�u�W�F�N�g��������
			pObject = pObject->GetNext();
		}

		// ��r�I�u�W�F�N�g�̎��̃I�u�W�F�N�g�Ɏ������g��������
		pObject->SetNext(pThis);

		// ���̃I�u�W�F�N�g�� NULL ������
		pThis->SetNext(nullptr);

		// ���݂̔�r�I�u�W�F�N�g�������̑O�̃I�u�W�F�N�g�ɐݒ肷��
		pThis->SetPrev(pObject);
	}

	// ���������Z����
	m_nNumAll++;
}

//============================
// �I������
//============================
void CElevationManager::Uninit(void)
{
	// ���[�J���ϐ��錾
	CElevation* pObj = nullptr;		// ���݂̃I�u�W�F�N�g�̃|�C���^

	// �I�u�W�F�N�g��������
	pObj = m_pTop;

	while (pObj != nullptr)
	{ // �I�u�W�F�N�g�ƈ�������v���Ă��Ȃ������

		// ������������
		m_pManager->Pull(pObj);

		// ���̃I�u�W�F�N�g��������
		pObj = pObj->GetNext();
	}

	// �}�l�[�W���[�̃��������������
	delete m_pManager;
	m_pManager = nullptr;
}

//============================
// �f�X�g���N�^
//============================
CElevationManager::~CElevationManager()
{

}

//===========================================
// �I�u�W�F�N�g�̎擾����
//===========================================
CElevation* CElevationManager::GetTop(void)
{
	// �I�u�W�F�N�g�̏���n��
	return m_pTop;
}

//===========================================
// ���X�g�\���̈�����������
//===========================================
void CElevationManager::Pull(CElevation* pThis)
{
	// ���[�J���ϐ��錾
	CElevation* pObj = nullptr;		// ���݂̃I�u�W�F�N�g�̃|�C���^

	// �I�u�W�F�N�g��������
	pObj = m_pTop;

	while (pObj != pThis)
	{ // �I�u�W�F�N�g�ƈ�������v���Ă��Ȃ������

		// ���̃I�u�W�F�N�g��������
		pObj = pObj->GetNext();
	}

	if (pObj->GetPrev() != nullptr)
	{ // �O�̃I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ���X�g�\�����玩���𔲂��o��
		pObj->GetPrev()->SetNext(pObj->GetNext());
	}

	if (pObj->GetNext() != nullptr)
	{ // ���̃I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ���X�g�\�����玩���𔲂��o��
		pObj->GetNext()->SetPrev(pObj->GetPrev());
	}

	if (pObj == m_pTop)
	{ // �擪�������ꍇ

		// �擪�̃|�C���^�������n��
		m_pTop = pObj->GetNext();
	}

	// ���������Z����
	m_nNumAll--;
}

//============================
//��������
//============================
CElevationManager* CElevationManager::Create(void)
{
	if (m_pManager == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		m_pManager = new CElevationManager;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// �I�u�W�F�N�g�̃|�C���^��Ԃ�
		return m_pManager;
	}

	if (m_pManager != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// �I�u�W�F�N�g�̃|�C���^��Ԃ�
		return m_pManager;
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g��Ԃ�
		return nullptr;
	}
}

//============================
// �擾����
//============================
CElevationManager* CElevationManager::Get(void)
{
	// �}�l�[�W���[�̃|�C���^��Ԃ�
	return m_pManager;
}