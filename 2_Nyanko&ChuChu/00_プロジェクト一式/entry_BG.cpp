//=======================================
//
// �G���g���[�̔w�i����[entry_BG.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "renderer.h"
#include "entry_BG.h"

#include "model.h"

//---------------------------------------
// �������O���
//---------------------------------------
namespace
{
	const D3DXVECTOR3 BG_POS[CEntryBG::TYPE_MAX] =		// �w�i�̈ʒu
	{
		D3DXVECTOR3(0.0f, 0.0f, 2650.0f),
		D3DXVECTOR3(900.0f, -200.0f, 200.0f),
		D3DXVECTOR3(700.0f, 0.0f, -150.0f),
		D3DXVECTOR3(0.0f, 0.0f, 1100.0f),
		D3DXVECTOR3(0.0f, 0.0f, 1200.0f),
		D3DXVECTOR3(0.0f, -30.0f, -250.0f),
		D3DXVECTOR3(-900.0f, -30.0f, 450.0f),
		D3DXVECTOR3(700.0f, 270.0f,0.0f),
		D3DXVECTOR3(700.0f, 20.0f,0.0f),
		D3DXVECTOR3(700.0f, 140.0f,0.0f),
	};

	const D3DXVECTOR3 BG_ROT[CEntryBG::TYPE_MAX] =		// �w�i�̈ʒu
	{
		NONE_D3DXVECTOR3,
		NONE_D3DXVECTOR3,
		NONE_D3DXVECTOR3,
		NONE_D3DXVECTOR3,
		NONE_D3DXVECTOR3,
		NONE_D3DXVECTOR3,
		NONE_D3DXVECTOR3,
		D3DXVECTOR3(D3DX_PI * 0.0f,-1.0f,0.0f),
		D3DXVECTOR3(D3DX_PI * 0.0f,-1.0f,0.0f),
		D3DXVECTOR3(D3DX_PI * 0.0f,-1.0f,0.0f),
	};
}

//=========================
// �R���X�g���N�^
//=========================
CEntryBG::CEntryBG() : CObject(CObject::TYPE_ENTRYBG, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_apModel[nCnt] = nullptr;			// ���f���̏��
	}
}

//=========================
// �f�X�g���N�^
//=========================
CEntryBG::~CEntryBG()
{

}

//=========================
// ����������
//=========================
HRESULT CEntryBG::Init(void)
{
	// �S�Ă̒l������������
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apModel[nCnt] == nullptr)
		{ // ���f���̏�� NULL �̏ꍇ

			// ���f���𐶐�����
			m_apModel[nCnt] = CModel::Create(TYPE_NONE, PRIORITY_BLOCK);
		}
	}

	// ������Ԃ�
	return S_OK;
}

//=========================
// �I������
//=========================
void CEntryBG::Uninit(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{ // ���f���̏�� NULL ����Ȃ��ꍇ

			// ���f���̏I������
			m_apModel[nCnt]->Uninit();
			m_apModel[nCnt] = nullptr;
		}
	}

	// �{�̂̏I������
	Release();
}

//=========================
// �X�V����
//=========================
void CEntryBG::Update(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{ // ���f���̏�� NULL ����Ȃ��ꍇ

			// ���f���̍X�V����
			m_apModel[nCnt]->Update();
		}
	}
}

//=========================
// �`�揈��
//=========================
void CEntryBG::Draw(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{ // ���f���̏�� NULL ����Ȃ��ꍇ

			// ���f���̕`�揈��
			m_apModel[nCnt]->Draw();
		}
	}
}

//=========================
// ���̐ݒ菈��
//=========================
void CEntryBG::SetData(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{ // ���f���̏�� NULL �̏ꍇ

			// ����ݒ肷��
			m_apModel[nCnt]->SetPos(BG_POS[nCnt]);								// �ʒu
			m_apModel[nCnt]->SetPosOld(BG_POS[nCnt]);							// �O��̈ʒu
			m_apModel[nCnt]->SetRot(BG_ROT[nCnt]);							// ����
			m_apModel[nCnt]->SetScale(NONE_SCALE);								// �g�嗦
			m_apModel[nCnt]->SetFileData((CXFile::TYPE)(INIT_ENTRANCE + nCnt));	// ���f���̏��
		}
		
	}
}

//=========================
// ��������
//=========================
CEntryBG* CEntryBG::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CEntryBG* pEntry = nullptr;		// �G���g���[�̔w�i�̃C���X�^���X�𐶐�

	if (pEntry == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pEntry = new CEntryBG;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pEntry != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pEntry->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pEntry->SetData();
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �G���g���[�̔w�i�̃|�C���^��Ԃ�
	return pEntry;
}