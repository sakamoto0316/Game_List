//====================================================
//
// �X�J�C�{�b�N�X���� [skybox.cpp]
// Author�F��������
//
//====================================================
//****************************************************
//	�C���N���[�h�t�@�C��
//****************************************************
#include "manager.h"
#include "skybox.h"
#include "texture.h"

//----------------------------------------------------
// �}�N����`
//----------------------------------------------------
#define TEXTURE				"data\\TEXTURE\\NoonSky.jpg"				// �e�N�X�`���̃p�X
#define SKYBOX_POS			(D3DXVECTOR3(20000.0f, -10000.0f, 0.0f))	// �ʒu
#define SKYBOX_ROT			(D3DXVECTOR3(0.0f, 0.0f, 0.0f))				// ����
#define SKYBOX_WIDTH		(40000.0f)									// ����
#define SKYBOX_HEIGHT		(40000.0f)									// �c��
#define SKYBOX_DIVI_CIRCUM	(32)										// �~���̕�����
#define SKYBOX_DIVI_HEIGHT	(32)										// �c�̕�����
#define SKYBOX_ROTATION		(0.001f)									// �񂷑��x

//================================
// �R���X�g���N�^
//================================
CSkyBox::CSkyBox() : CMeshDome(CObject::TYPE_SKYBOX, CObject::PRIORITY_BG)
{
	
}

//================================
// �f�X�g���N�^
//================================
CSkyBox::~CSkyBox()
{

}

//================================
// ����������
//================================
HRESULT CSkyBox::Init(void)
{
	if (FAILED(CMeshDome::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//================================
// �I������
//================================
void CSkyBox::Uninit(void)
{
	// �I������
	CMeshDome::Uninit();
}

//================================
// �X�V����
//================================
void CSkyBox::Update(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 rot = GetRot();		// ����

	// ��������
	rot.y += SKYBOX_ROTATION;

	// �����̐ݒ菈��
	SetRot(rot);
}

//================================
// �`�揈��
//================================
void CSkyBox::Draw(void)
{
	// �`�揈��
	CMeshDome::Draw();
}

//================================
// ��������
//================================
CSkyBox* CSkyBox::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CSkyBox* pSkyBox = nullptr;	// �I�u�W�F�N�g3D�̃C���X�^���X�𐶐�

	if (pSkyBox == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pSkyBox = new CSkyBox;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pSkyBox != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// �h�[���̐ݒ菈��
		pSkyBox->SetDataDome(SKYBOX_POS, SKYBOX_ROT, SKYBOX_WIDTH, SKYBOX_HEIGHT, SKYBOX_DIVI_CIRCUM, SKYBOX_DIVI_HEIGHT);

		// ����������
		if (FAILED(pSkyBox->Init()))
		{ // �����������Ɏ��s�����ꍇ

			// NULL ��Ԃ�
			return nullptr;
		}

		// �e�N�X�`���̊��蓖�ď���
		pSkyBox->BindTexture(CManager::Get()->GetTexture()->Regist(TEXTURE));

		// ���C�e�B���O�󋵂�ݒ肷��
		pSkyBox->SetLighting(true);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}

	// �X�J�C�{�b�N�X�̃|�C���^��Ԃ�
	return pSkyBox;
}