//===========================================
//
// �X�s�[�J�[�̏���[Himo.cpp]
// Author ��{�ėB
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "speaker.h"
#include "manager.h"
#include "useful.h"
#include "sound.h"

#include "note.h"
#include "collision.h"

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define SPEAKER_RADIUS	(50.0f)		// �����̏o���Ԋu(�t���[��)
#define NOTE_INTERVAL	(20)		// �����̏o���Ԋu(�t���[��)
#define NOTE_LIFE		(90)		// �����̎���
#define NOTE_SPEED		(15.0f)		// �����̑���
#define NOTE_HEIGHT		(100.0f)	// �����̍���
#define NOTE_SHIFT		(100.0f)	// �����̂��炷��
#define STOP_SCALE		(1.0f)		// �ʏ펞�̊g�嗦
#define SHRINK_SCALE	(0.85f)		// �k�ݏ�Ԃ̊g�嗦
#define EXTEND_SCALE	(1.15f)		// �L�я�Ԃ̊g�嗦
#define ADD_SCALE		(0.05f)		// �g�嗦�̉��Z��
#define ADD_HIT_RADIUS	(40.0f)		// �ǉ��̓����蔻��̔��a

//-------------------------------------------
// �ÓI�����o�ϐ��錾
//-------------------------------------------
CNote* CSpeaker::m_apNote[MAX_NOTE] = {};		// �����̏��
int CSpeaker::m_nNumBgmAll = 0;					// BGM�炵������

//==============================
// �R���X�g���N�^
//==============================
CSpeaker::CSpeaker() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < MAX_NOTE; nCnt++)
	{
		m_apNote[nCnt] = NULL;
		m_bmySet[nCnt] = false;
	}
	m_state = STATE_STOP;		// ���
	m_bAction = false;
	m_nNoteCount = 0;
	SetCatUse(true);
	SetRatUse(true);
}

//==============================
// �f�X�g���N�^
//==============================
CSpeaker::~CSpeaker()
{

}

//==============================
// �X�s�[�J�[�̏���������
//==============================
HRESULT CSpeaker::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // �����������Ɏ��s�����ꍇ

	  // ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < MAX_NOTE; nCnt++)
	{
		m_apNote[nCnt] = NULL;
		m_bmySet[nCnt] = false;
	}

	m_state = STATE_STOP;		// ���
	m_bAction = false;
	m_nNoteCount = 0;

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �X�s�[�J�[�̏I������
//========================================
void CSpeaker::Uninit(void)
{
	m_nNumBgmAll = 0;

	for (int nCnt = 0; nCnt < MAX_NOTE; nCnt++)
	{
		if (m_apNote[nCnt] != nullptr)
		{ // ������ NULL �̏ꍇ

			// �����̏I������
			m_apNote[nCnt]->Uninit();
			m_apNote[nCnt] = nullptr;
		}
	}

	// �I������
	CObstacle::Uninit();
}

//=====================================
// �X�s�[�J�[�̍X�V����
//=====================================
void CSpeaker::Update(void)
{
	if (m_bAction == true)
	{
		SetNote();
	}
	else
	{ // ��L�ȊO

		// ��~��Ԃɂ���
		m_state = STATE_STOP;
	}

	for (int nCnt = 0; nCnt < MAX_NOTE; nCnt++)
	{
		if (m_bmySet[nCnt] == true)
		{
			if (m_apNote[nCnt] != NULL)
			{
				m_apNote[nCnt]->Update();
			}
		}
	}

	// ��Ԃɂ�鏈��
	State();
}

//=====================================
// �X�s�[�J�[�̕`�揈��
//=====================================
void CSpeaker::Draw(void)
{
	// �`�揈��
	CObstacle::Draw();

	for (int nCnt = 0; nCnt < MAX_NOTE; nCnt++)
	{
		if (m_apNote[nCnt] != NULL)
		{
			m_apNote[nCnt]->Draw();
		}
	}
}

//=====================================
// �����̐�������
//=====================================
void CSpeaker::SetNote(void)
{
	m_nNoteCount++;

	if (m_nNoteCount % NOTE_INTERVAL == 0)
	{
		for (int nCnt = 0; nCnt < MAX_NOTE; nCnt++)
		{
			if (m_apNote[nCnt] == NULL)
			{
				D3DXVECTOR3 pos = GetPos();
				D3DXVECTOR3 rot = GetRot();

				m_apNote[nCnt] = CNote::Create(D3DXVECTOR3(pos.x - (sinf(rot.y) * NOTE_SHIFT), pos.y + NOTE_HEIGHT, pos.z - (cosf(rot.y) * NOTE_SHIFT)));
				m_apNote[nCnt]->SetMain(this);
				m_apNote[nCnt]->SetIndex(nCnt);
				m_apNote[nCnt]->SetLife(NOTE_LIFE);
				m_apNote[nCnt]->SetMove(D3DXVECTOR3(
					sinf(rot.y + (D3DX_PI * 1.0f)) * NOTE_SPEED,
					0.0f,
					cosf(rot.y + (D3DX_PI * 1.0f)) * NOTE_SPEED));
				m_bmySet[nCnt] = true;
				break;
			}
		}
	}
}

//=====================================
// �A�N�V��������
//=====================================
void CSpeaker::Action(void)
{
	// �A�N�V�����󋵂����ւ���
	m_bAction = !m_bAction;

	if (m_bAction == true)
	{ // BGM�Đ����ĂȂ�������

		m_nNumBgmAll++;					// BGM�炵������
	}
	else if (m_bAction == false)
	{ // �A�N�V�������Ȃ��Ƃ�

		m_nNumBgmAll--;
	}

	if (m_nNumBgmAll <= 0)
	{ // ����Đ����ĂȂ�������

		// �^���~�߂�
		CManager::Get()->GetSound()->Stop(CSound::SOUND_LABEL_BGM_SPEAKER);

		// �Q�[��BGM����
		CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_BGM_GAME);
	}
	else if (m_bAction == true && m_nNumBgmAll == 1)
	{ // ��Đ����Ă���

		// �Q�[��BGM�~�߂�
		CManager::Get()->GetSound()->Stop(CSound::SOUND_LABEL_BGM_GAME);

		// �^������
		CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_BGM_SPEAKER);
	}

	// �k�ݏ�Ԃɂ���
	m_state = STATE_SHRINK;
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CSpeaker::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos, rot, type);

	// �S�Ă̒l��ݒ肷��
	m_state = STATE_STOP;		// ���
}

//=====================================
// �����蔻�菈��
//=====================================
bool CSpeaker::Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// �ʒu�ƍŏ��l�ƍő�l��ݒ肷��
	D3DXVECTOR3 pos = pPlayer->GetPos();
	D3DXVECTOR3 move = pPlayer->GetMove();
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(collSize.x, collSize.y, collSize.z);
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);
	collision::SCollision coll = { false,false,false,false,false,false };

	// �Z�ʑ̂̓����蔻��
	coll = collision::HexahedronClush
	(
		&pos,					// �v���C���[�̈ʒu
		GetPos(),				// �ʒu
		pPlayer->GetPosOld(),	// �v���C���[�̑O��̈ʒu
		GetPosOld(),			// �O��̈ʒu
		vtxMin,					// �v���C���[�̍ŏ��l
		GetFileData().vtxMin,	// �ŏ��l
		vtxMax,					// �v���C���[�̍ő�l
		GetFileData().vtxMax	// �ő�l
	);

	// �ʒu��K�p����
	pPlayer->SetPos(pos);

	if(coll.bTop == true)
	{ // ��ɏ�����ꍇ

		// �ړ��ʂ�����������
		move.y = 0.0f;

		// �ړ��ʂ�K�p����
		pPlayer->SetMove(move);

		// true ��Ԃ�
		return true;
	}

	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CSpeaker::Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	for (int nCntNote = 0; nCntNote < MAX_NOTE; nCntNote++)
	{
		if (m_apNote[nCntNote] != nullptr)
		{ // ������ NULL ����Ȃ��ꍇ

			if (pPlayer->GetPos().y <= m_apNote[nCntNote]->GetPos().y + m_apNote[nCntNote]->GetFileData().vtxMax.y &&
				pPlayer->GetPos().y + collSize.y >= m_apNote[nCntNote]->GetPos().y + m_apNote[nCntNote]->GetFileData().vtxMin.y &&
				useful::CylinderInner(pPlayer->GetPos(), m_apNote[nCntNote]->GetPos(), m_apNote[nCntNote]->GetFileData().fRadius + collSize.x) == true)
			{ // �����蔻��̒��ɓ������ꍇ

				// true ��Ԃ�
				return true;
			}
		}
	}

	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CSpeaker::HitCircle(CPlayer* pPlayer, const float Radius)
{
	if (GetAction() == false &&
		useful::CircleCollisionXZ(pPlayer->GetPos(), GetPos(), Radius, GetFileData().fRadius + ADD_HIT_RADIUS) == true)
	{ // �~�͈͓̔��ɂ����ꍇ

		// true ��Ԃ�
		return true;
	}

	// false ��Ԃ�
	return false;
}

//=====================================
// ��Ԃɂ�鏈��
//=====================================
void CSpeaker::State(void)
{
	// �g�嗦���擾����
	D3DXVECTOR3 scale = GetScale();

	switch (m_state)
	{
	case CSpeaker::STATE_STOP:		// ��~���

		// �ϓ��Ȑ��l�̕␳
		useful::FrameCorrect(STOP_SCALE, &scale.y, ADD_SCALE);

		break;

	case CSpeaker::STATE_SHRINK:	// �k�ݏ��

		if (useful::FrameCorrect(SHRINK_SCALE,&scale.y, ADD_SCALE) == true)
		{ // �g�嗦����萔�ɂȂ����ꍇ

			// �g�嗦���Œ肷��
			scale.y = SHRINK_SCALE;

			// �L�я�Ԃɂ���
			m_state = STATE_EXTEND;
		}

		break;

	case CSpeaker::STATE_EXTEND:	// �L�я��

		if (useful::FrameCorrect(EXTEND_SCALE,&scale.y, ADD_SCALE) == true)
		{ // �g�嗦����萔�ɂȂ����ꍇ

			// �g�嗦���Œ肷��
			scale.y = EXTEND_SCALE;

			// �k�ݏ�Ԃɂ���
			m_state = STATE_SHRINK;
		}

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	// �g�嗦��K�p����
	SetScale(scale);
}