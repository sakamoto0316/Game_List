//============================================
//
// �V�[���̃��C������[scene.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "scene.h"

#include "logo.h"
#include "title.h"
#include "entry.h"
#include "tutorial.h"
#include "game.h"
#include "result.h"
#include "sound.h"

#include "manager.h"
#include "file.h"

//======================================
// �R���X�g���N�^
//======================================
CScene::CScene() : CObject(TYPE_SCENE, PRIORITY_BG)
{
	// �R���X�g���N�^�̔�
	Box();
}

//======================================
// �I�[�o�[���[�h�R���X�g���N�^
//======================================
CScene::CScene(TYPE type, PRIORITY priority) : CObject(type, priority)
{
	// �R���X�g���N�^�̔�
	Box();
}

//======================================
// �f�X�g���N�^
//======================================
CScene::~CScene()
{

}

//======================================
// �R���X�g���N�^�̔�
//======================================
void CScene::Box(void)
{
	// �S�Ă̒l���N���A����
	m_mode = MODE_LOGO;			// ���݂̃��[�h
}

//======================================
// ����������
//======================================
HRESULT CScene::Init(void)
{
	// ������Ԃ�
	return S_OK;
}

//======================================
// �I������
//======================================
void CScene::Uninit(void)
{
	// �j������
	Release();
}

//======================================
// �X�V����
//======================================
void CScene::Update(void)
{

}

//======================================
// �`�揈��
//======================================
void CScene::Draw(void)
{

}

//======================================
// ���̐ݒ菈��
//======================================
void CScene::SetData(const MODE mode)
{
	// ���[�h��ݒ肷��
	m_mode = mode;

	if (CManager::Get()->GetSound() != nullptr)
	{ // �T�E���h�� NULL ����Ȃ��ꍇ

		// BGM�𗬂�
		switch (m_mode)
		{
		case MODE_LOGO:

			break;

		case MODE_TITLE:

			// �^�C�g��BGM�𗬂�
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_BGM_TITLE);

			break;

		case MODE_ENTRY:

			// �G���g���[BGM�𗬂�
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_BGM_ENTRY);

			break;

		case MODE_TUTORIAL:

			// �Q�[��BGM�𗬂�
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_BGM_GAME);

			break;

		case MODE_GAME:

			// �Q�[��BGM�𗬂�
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_BGM_GAME);

			break;

		case MODE_RESULT:

			// ���U���gBGM�𗬂�
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_BGM_RESULT);

			break;

		default:

			// ��~
			assert(false);

			break;
		}
	}
}

//======================================
// ���[�h�̐ݒ菈��
//======================================
void CScene::SetMode(const MODE mode)
{
	// ���[�h��ݒ肷��
	m_mode = mode;
}

//======================================
// ���[�h�̎擾����
//======================================
CScene::MODE CScene::GetMode(void) const
{
	// ���[�h��Ԃ�
	return m_mode;
}

//======================================
// ��������
//======================================
CScene* CScene::Create(const MODE mode)
{
	// ���[�J���|�C���^�錾
	CScene* pScene = nullptr;		// �V�[���ւ̃|�C���^

	if (pScene == nullptr)
	{ // �V�[���� NULL �̏ꍇ

		switch (mode)
		{
		case MODE_LOGO:			// ���S���

			// ���S��ʂ𐶐�����
			pScene = new CLogo;

			break;

		case MODE_TITLE:		// �^�C�g�����

			// �^�C�g����ʂ𐶐�����
			pScene = new CTitle;

			break;

		case MODE_ENTRY:

			// �G���g���[��ʂ𐶐�����
			pScene = new CEntry;

			break;

		case MODE_TUTORIAL:

			// �G���g���[��ʂ𐶐�����
			pScene = new CTutorial;

			break;

		case MODE_GAME:			// �Q�[�����

			// �Q�[����ʂ𐶐�����
			pScene = new CGame;

			break;

		case MODE_RESULT:		// ���U���g���

			// ���U���g��ʂ𐶐�����
			pScene = new CResult;

			break;

		default:

			// ��~
			assert(false);

			break;
		}

		if (pScene != nullptr)
		{ // �V�[���ւ̃|�C���^�� NULL ����Ȃ��ꍇ

			// ����������
			if (FAILED(pScene->Init()))
			{ // ���s�����ꍇ

				// ��~
				assert(false);

				// NULL ��Ԃ�
				return nullptr;
			}

			// ���̐ݒ菈��
			pScene->SetData(mode);
		}
		else
		{ // �V�[���ւ̃|�C���^�� NULL �̏ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}
	}
	else
	{ // �V�[���� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �V�[���ւ̃|�C���^��Ԃ�
	return pScene;
}