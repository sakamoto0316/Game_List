//=======================================
//
// �`�B���b�Z�[�W�̃��C������[speech_message.cpp]
// Author ��������
//
//=======================================
#include "manager.h"
#include "speech_message.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

//=======================================
// �}�N����`
//=======================================
#define HELP_TEXTURE		"data\\TEXTURE\\HelpMessage.png"		// �~���v���̃e�N�X�`��
#define MESSAGE_NONE_LIFE	(-1)		// ��������(����)�̒l
#define EXTEND_COUNT		(50)		// �L�я�Ԃ̃J�E���g��
#define SHRINK_COUNT		(15)		// �k�ݏ�Ԃ̃J�E���g��
#define EXTEND_MAGNI		(D3DXVECTOR3(0.8f, 1.2f, 0.0f))			// �L�я�Ԃ̔{��
#define SHRINK_MAGNI		(D3DXVECTOR3(1.2f, 0.8f, 0.0f))			// �k�ݏ�Ԃ̔{��

//=========================
// �R���X�g���N�^
//=========================
CSpeechMessage::CSpeechMessage() : CBillboard(CObject::TYPE_EFFECT, CObject::PRIORITY_EFFECT)
{
	// �S�Ă̒l���N���A����
	m_sizeDest = NONE_D3DXVECTOR3;	// �ړI�̃T�C�Y
	m_sizeCopy = NONE_D3DXVECTOR3;	// �ŏ��̃T�C�Y
	m_state = STATE_EXTEND;			// ���
	m_type = TYPE_HELP;				// ���
	m_nLife = 0;					// ����
	m_nStateCount = 0;				// ��Ԃ̃J�E���g
	m_nPlayerIdx = -1;		//�v���C���[�ԍ�
}

//=========================
// �f�X�g���N�^
//=========================
CSpeechMessage::~CSpeechMessage()
{

}

//=========================
// ����������
//=========================
HRESULT CSpeechMessage::Init(void)
{
	if (FAILED(CBillboard::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_sizeDest = NONE_D3DXVECTOR3;	// �ړI�̃T�C�Y
	m_sizeCopy = NONE_D3DXVECTOR3;	// �ŏ��̃T�C�Y
	m_state = STATE_EXTEND;			// ���
	m_type = TYPE_HELP;				// ���
	m_nLife = 0;					// ����
	m_nStateCount = 0;				// ��Ԃ̃J�E���g
	m_nPlayerIdx = -1;		//�v���C���[�ԍ�

	// ������Ԃ�
	return S_OK;
}

//=========================
// �I������
//=========================
void CSpeechMessage::Uninit(void)
{
	// �I��
	CBillboard::Uninit();
}

//=========================
// �X�V����
//=========================
void CSpeechMessage::Update(void)
{
	D3DXVECTOR3 size = GetSize();

	// ��ԃJ�E���g�����Z����
	m_nStateCount++;

	switch (m_state)
	{
	case CSpeechMessage::STATE_EXTEND:

		// �T�C�Y��ݒ肷��
		useful::FrameCorrect(m_sizeDest.x, &size.x, (m_sizeDest.x - m_sizeCopy.x) / EXTEND_COUNT);
		useful::FrameCorrect(m_sizeDest.y, &size.y, (m_sizeDest.y - m_sizeCopy.y) / EXTEND_COUNT);

		if (m_nStateCount % EXTEND_COUNT == 0)
		{ // ��ԃJ�E���g����萔�ɂȂ����ꍇ

			// ��ԃJ�E���g������������
			m_nStateCount = 0;

			// �k����Ԃɂ���
			m_state = STATE_SHRINK;

			// �ړI�̃T�C�Y��ݒ肷��
			m_sizeDest = D3DXVECTOR3(m_sizeCopy.x * SHRINK_MAGNI.x, m_sizeCopy.y * SHRINK_MAGNI.y, 0.0f);
		}

		break;

	case CSpeechMessage::STATE_SHRINK:

		// �T�C�Y��ݒ肷��
		useful::FrameCorrect(m_sizeDest.x, &size.x, (m_sizeDest.x - m_sizeCopy.x) / SHRINK_COUNT);
		useful::FrameCorrect(m_sizeDest.y, &size.y, (m_sizeDest.y - m_sizeCopy.y) / SHRINK_COUNT);

		if (m_nStateCount % SHRINK_COUNT == 0)
		{ // ��ԃJ�E���g����萔�ɂȂ����ꍇ

			// ��ԃJ�E���g������������
			m_nStateCount = 0;

			// �g���Ԃɂ���
			m_state = STATE_EXTEND;

			// �ړI�̃T�C�Y��ݒ肷��
			m_sizeDest = D3DXVECTOR3(m_sizeCopy.x * EXTEND_MAGNI.x, m_sizeCopy.y * EXTEND_MAGNI.y, 0.0f);
		}

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	// ���������Z����
	m_nLife--;

	if (m_nLife == 0)
	{ // ������0�ɂȂ����ꍇ

		// �I������
		Uninit();

		// ���̐�̏������s��Ȃ�
		return;
	}

	// �T�C�Y�̐ݒ菈��
	SetSize(size);

	// ���_���W�̐ݒ菈��
	SetVertex();
}

//=========================
// �`�揈��
//=========================
void CSpeechMessage::Draw(void)
{
	int nIdx = CObject::GetDrawIdx();
	if (nIdx != m_nPlayerIdx)
	{
		// �`�揈��
		CBillboard::DrawLightOff();
	}
}

//=========================
// ���̐ݒ菈��
//=========================
void CSpeechMessage::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const int nLife, const TYPE type, int nIdx)
{
	// �X�N���[���̐ݒ菈��
	SetPos(pos);			// �ʒu�ݒ�
	SetSize(size);			// �T�C�Y�ݒ�

	// �S�Ă̒l������������
	m_sizeDest = D3DXVECTOR3(size.x * EXTEND_MAGNI.x, size.y * EXTEND_MAGNI.y, 0.0f);	// �ړI�̃T�C�Y
	m_sizeCopy = size;			// �ŏ��̃T�C�Y
	m_state = STATE_EXTEND;		// ���
	m_type = type;				// ���
	m_nLife = nLife;			// ����
	m_nStateCount = 0;			// ��Ԃ̃J�E���g
	m_nPlayerIdx = nIdx;		//�v���C���[�ԍ�
	// ���_���̏�����
	SetVertex();

	switch (m_type)
	{
	case CSpeechMessage::TYPE_HELP:

		// �e�N�X�`���̊��蓖�ď���
		BindTexture(CManager::Get()->GetTexture()->Regist(HELP_TEXTURE));

		break;

	default:

		// ���ɂȂ�

		break;
	}
}

//=========================
// ��������
//=========================
CSpeechMessage* CSpeechMessage::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const int nLife, const TYPE type,int nIdx)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CSpeechMessage* pMessage = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pMessage == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pMessage = new CSpeechMessage;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pMessage != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pMessage->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pMessage->SetData(pos, size, nLife, type,nIdx);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �`�B���b�Z�[�W�̃|�C���^��Ԃ�
	return pMessage;
}