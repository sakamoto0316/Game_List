//=======================================
//
// �V�䏈��[ceil.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "ceil.h"
#include "object3D.h"
#include "texture.h"
#include "useful.h"

//---------------------------------------
// �������O���
//---------------------------------------
namespace
{
	const D3DXVECTOR3 CEIL_SHIFT[MAX_CEIL] =		// �V��̂��炷��
	{
		D3DXVECTOR3(0.0f, 0.0f, 1000.0f),
		D3DXVECTOR3(0.0f, 0.0f, -1000.0f),
	};
	const D3DXVECTOR3 CEIL_ROT[MAX_CEIL] =			// �V��̌���
	{
		D3DXVECTOR3(-D3DX_PI * 0.8f, 0.0f, 0.0f),
		D3DXVECTOR3(D3DX_PI * 0.8f, 0.0f, 0.0f),
	};
	const D3DXVECTOR3 CEIL_SIZE = D3DXVECTOR3(1600.0f, 0.0f, 2000.0f);	// �V��̃T�C�Y
	const char* CEIL_TEXTURE = "data\\TEXTURE\\ground001.jpg";			// �V��e�N�X�`��
}

//=========================
// �R���X�g���N�^
//=========================
CCeil::CCeil() : CObject(CObject::TYPE_MAP, CObject::PRIORITY_BG)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < MAX_CEIL; nCnt++)
	{
		m_apCeil[nCnt] = nullptr;		// �V��̃|���S��
	}
}

//=========================
// �f�X�g���N�^
//=========================
CCeil::~CCeil()
{

}

//=========================
// ����������
//=========================
HRESULT CCeil::Init(void)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < MAX_CEIL; nCnt++)
	{
		m_apCeil[nCnt] = nullptr;		// �V��̃|���S��
	}

	// ������Ԃ�
	return S_OK;
}

//=========================
// �I������
//=========================
void CCeil::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_CEIL; nCnt++)
	{
		if (m_apCeil[nCnt] != nullptr)
		{ // �V�䂪 NULL ����Ȃ��ꍇ

			// �V��̏I������
			m_apCeil[nCnt]->Uninit();
			m_apCeil[nCnt] = nullptr;
		}
	}

	// �{�̂̏I������
	Release();
}

//=========================
// �X�V����
//=========================
void CCeil::Update(void)
{
	for (int nCnt = 0; nCnt < MAX_CEIL; nCnt++)
	{
		if (m_apCeil[nCnt] != nullptr)
		{ // �V�䂪 NULL ����Ȃ��ꍇ

			// ���_���W�̐ݒ菈��
			m_apCeil[nCnt]->SetVertex();
		}
	}
}

//=========================
// �`�揈��
//=========================
void CCeil::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_CEIL; nCnt++)
	{
		if (m_apCeil[nCnt] != nullptr)
		{ // �V�䂪 NULL ����Ȃ��ꍇ

			// �`�揈��
			m_apCeil[nCnt]->DrawLightOff();
		}
	}
}

//=========================
// ���̐ݒ菈��
//=========================
void CCeil::SetData(const D3DXVECTOR3& pos)
{
	for (int nCnt = 0; nCnt < MAX_CEIL; nCnt++)
	{
		if (m_apCeil[nCnt] == nullptr)
		{ // �V�䂪 NULL �̏ꍇ

			// �V��𐶐�����
			m_apCeil[nCnt] = CObject3D::Create(TYPE_NONE, PRIORITY_BG);

			// �X�N���[���̐ݒ菈��
			m_apCeil[nCnt]->SetPos(pos + CEIL_SHIFT[nCnt]);			// �ʒu�ݒ�
			m_apCeil[nCnt]->SetPosOld(pos + CEIL_SHIFT[nCnt]);			// �O��̈ʒu�ݒ�
			m_apCeil[nCnt]->SetRot(CEIL_ROT[nCnt]);		// �����ݒ�
			m_apCeil[nCnt]->SetSize(CEIL_SIZE);		// �T�C�Y�ݒ�

			// �e�N�X�`���̊��蓖�ď���
			m_apCeil[nCnt]->BindTexture(CManager::Get()->GetTexture()->Regist(CEIL_TEXTURE));

			// ���_���W�̐ݒ菈��
			m_apCeil[nCnt]->SetVertex();
		}
	}
}

//=========================
// ��������
//=========================
CCeil* CCeil::Create(const D3DXVECTOR3& pos)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CCeil* pCeil = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pCeil == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pCeil = new CCeil;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pCeil != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pCeil->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pCeil->SetData(pos);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �V��̃|�C���^��Ԃ�
	return pCeil;
}