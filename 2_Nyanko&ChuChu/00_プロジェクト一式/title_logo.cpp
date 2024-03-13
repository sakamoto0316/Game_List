//============================================
//
// �^�C�g�����S����[title_logo.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "title_logo.h"
#include "object2D.h"
#include "title.h"
#include "locus2D.h"
#include "texture.h"
#include "useful.h"
#include "sound.h"

#include "title_press.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define RAT_TEXTURE				"data/TEXTURE/title.3.png"			// �^�C�g�����S(�l�Y�~)�̃e�N�X�`��
#define CAT_TEXTURE				"data/TEXTURE/title.1.png"			// �^�C�g�����S(�l�R)�̃e�N�X�`��
#define AND_TEXTURE				"data/TEXTURE/title.2.png"				// �^�C�g�����S(��)�̃e�N�X�`��
#define RAT_POS					(D3DXVECTOR3(-360.0f, 330.0f, 0.0f))	// �l�Y�~�̈ʒu
#define CAT_POS					(D3DXVECTOR3(-240.0f, 270.0f, 0.0f))	// �l�R�̈ʒu
#define AND_POS					(D3DXVECTOR3(530.0f, 300.0f, 0.0f))		// ���̈ʒu
#define RAT_SIZE				(D3DXVECTOR3(360.0f, 60.0f, 0.0f))		// �l�Y�~�̃T�C�Y
#define CAT_SIZE				(D3DXVECTOR3(240.0f, 60.0f, 0.0f))		// �l�R�̃T�C�Y
#define AND_SIZE				(NONE_D3DXVECTOR3)						// ���̃T�C�Y
#define ESCAPE_MOVE_SPEED		(60.0f)			// ������Ԃ̈ړ��ʂ̑��x
#define CAT_APPEAR_RAT_POS		(780.0f)		// �l�R���ړ��������l�Y�~�̈ʒu
#define RAT_ESCAPE_STOP_POS		(930.0f)		// �l�Y�~�̎~�܂�ʒu
#define CAT_ESCAPE_STOP_POS		(250.0f)		// �l�R�̎~�܂�ʒu
#define LOCUS_COUNT				(5)				// �c���̏o��J�E���g��
#define AND_ADD_SIZE			(5.0f)			// �A���h�̃T�C�Y�̒ǉ���
#define AND_APPEAR_COUNT		(10)			// �A���h�o����Ԃ̃J�E���g��
#define AND_DEST_SIZE			(D3DXVECTOR3(AND_ADD_SIZE * AND_APPEAR_COUNT, AND_ADD_SIZE * AND_APPEAR_COUNT, 0.0f))	// �A���h�̖ړI�̃T�C�Y
#define CAT_FRAMEOUT_RAT_POS	(SCREEN_WIDTH)							// �l�R����ʊO�Ɉړ��������l�Y�~�̈ʒu
#define RAT_FRAMEOUT_STOP_POS	(SCREEN_WIDTH + RAT_SIZE.x)				// �l�Y�~�̎~�܂�ʒu
#define CAT_FRAMEOUT_STOP_POS	(SCREEN_WIDTH + CAT_SIZE.x)				// �l�R�̎~�܂�ʒu
#define AND_FRAMEOUT_MOVE		(D3DXVECTOR3(-32.0f, -10.0f, 0.0f))		// ��ʊO�̃A���h�̈ړ���
#define SHAKEOFF_MOVE_SPEED		(-60.0f)								// �����؂��Ԃ̈ړ��ʂ̑��x
#define SHAKEOFF_RAT_POS_Y		(650.0f)								// �����؂��Ԃ̃l�Y�~�̏c�̈ʒu
#define SHAKEOFF_RAT_STOP_POS	(SCREEN_WIDTH * 0.5f)					// �����؂��Ԃ̃l�Y�~�̒�~����ʒu
#define HOLEIN_RAT_SIZE_FRAME	(40)									// �������Ԃ̃l�Y�~�̃T�C�Y�̏k���t���[����
#define HOLEIN_RAT_SUB_POS		(2.8f)									// �������Ԃ̃l�Y�~�̈ʒu�̌��Z��

//============================
// �R���X�g���N�^
//============================
CTitleLogo::CTitleLogo() : CObject(CObject::TYPE_TITLELOGO, PRIORITY_UI)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_aTitle[nCnt].move = NONE_D3DXVECTOR3;	// �ړ���
		m_aTitle[nCnt].pLogo = nullptr;			// �^�C�g���̃|���S��
		m_aTitle[nCnt].bDisp = false;			// �\����
		m_aTitle[nCnt].bMove = false;			// �ړ���
	}

	m_state = STATE_ESCAPE;		// ���
	m_nStateCount = 0;			// ��ԃJ�E���g
	m_bSe = false;				// SE�Đ���
}

//============================
// �f�X�g���N�^
//============================
CTitleLogo::~CTitleLogo()
{

}

//============================
// ����������
//============================
HRESULT CTitleLogo::Init(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_aTitle[nCnt].pLogo == nullptr)
		{ // �^�C�g���� NULL �̏ꍇ

			// �^�C�g���̃��S�𐶐�����
			m_aTitle[nCnt].pLogo = CObject2D::Create(CObject2D::TYPE_NONE, CObject::TYPE_NONE, CObject::PRIORITY_UI);
		}
		else
		{ // ��L�ȊO

			// ��~
			assert(false);
		}

		// �S�Ă̒l������������
		m_aTitle[nCnt].move = NONE_D3DXVECTOR3;		// �ړ���
		m_aTitle[nCnt].bDisp = false;				// �\����
		m_aTitle[nCnt].bMove = false;				// �ړ���
	}

	m_state = STATE_ESCAPE;		// ���
	m_nStateCount = 0;			// ��ԃJ�E���g
	m_bSe = false;				// SE�Đ���

	// ������Ԃ�
	return S_OK;
}

//============================
// �I������
//============================
void CTitleLogo::Uninit(void)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_aTitle[nCnt].pLogo != nullptr)
		{ // �^�C�g���̃|���S���� NULL ����Ȃ��ꍇ

			// �I������
			m_aTitle[nCnt].pLogo->Uninit();
			m_aTitle[nCnt].pLogo = nullptr;
		}
	}

	// �{�̂̏I������
	Release();
}

//============================
// �X�V����
//============================
void CTitleLogo::Update(void)
{
	switch (CTitle::GetState())
	{
	case CTitle::STATE_TITLE_APPEAR:	// �o�����

		switch (m_state)
		{
		case STATE_ESCAPE:

			// ������Ԃ̏���
			EscapeProcess();

			break;

		case STATE_AND:

			// ���o����Ԃ̏���
			AndProcess();

			break;

		default:

			// ��~
			assert(false);

			break;
		}

		break;

	case CTitle::STATE_WAIT:			// �ҋ@���

		break;

	case CTitle::STATE_TRANS:			// �J�ڏ��

		switch (m_state)
		{
		case STATE_WAIT:

			// ��ʊO��Ԃɂ���
			m_state = STATE_FRAMEOUT;

			// �A���h�̈ړ��ʂ�ݒ肷��
			m_aTitle[TYPE_AND].move = AND_FRAMEOUT_MOVE;

			break;

		case CTitleLogo::STATE_FRAMEOUT:

			// ��ʊO��Ԃ̏���
			FrameOutProcess();

			break;

		case CTitleLogo::STATE_SHAKEOFF:

			// �����؂��Ԃ̏���
			ShakeOffProcess();

			break;

		case CTitleLogo::STATE_HOLEIN:

			// �������Ԃ̏���
			HoleInProcess();

			if (m_bSe == false)
			{ // SE�炵�ĂȂ�������

				// �z�[���C���Đ�
				CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_TITLEHOLE);
				m_bSe = true;
			}

			break;

		case STATE_STOP:

			// ��~���Ă���̂œ��ɏ����͖���

			break;

		default:

			// ��~
			assert(false);

			break;
		}

		break;

	case CTitle::STATE_HOLEIN:			// ���̒��ɓ�����

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		// �����ƒ�����ݒ肷��
		m_aTitle[nCnt].pLogo->SetAngle();
		m_aTitle[nCnt].pLogo->SetLength();

		// ���_���W�̐ݒ菈��
		m_aTitle[nCnt].pLogo->SetVertexRot();
	}
}

//============================
// �`�揈��
//============================
void CTitleLogo::Draw(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_aTitle[nCnt].pLogo != nullptr &&
			m_aTitle[nCnt].bDisp == true)
		{ // �^�C�g���� NULL ����Ȃ��ꍇ

			// �`�揈��
			m_aTitle[nCnt].pLogo->Draw();
		}
	}
}

//============================
// ���̐ݒ菈��
//============================
void CTitleLogo::SetData(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_aTitle[nCnt].pLogo != nullptr)
		{ // �^�C�g���� NULL ����Ȃ��ꍇ

			// ����ݒ肷��
			switch (nCnt)
			{
			case TYPE_RAT:		// �l�Y�~

				m_aTitle[nCnt].pLogo->SetPos(RAT_POS);		// �ʒu
				m_aTitle[nCnt].pLogo->SetPosOld(RAT_POS);	// �O��̈ʒu
				m_aTitle[nCnt].pLogo->SetSize(RAT_SIZE);	// �T�C�Y

				// �e�N�X�`���̐ݒ菈��
				m_aTitle[nCnt].pLogo->BindTexture(CManager::Get()->GetTexture()->Regist(RAT_TEXTURE));

				// ����ݒ肷��
				m_aTitle[nCnt].move.x = ESCAPE_MOVE_SPEED;	// �ړ���
				m_aTitle[nCnt].bDisp = true;				// �\����
				m_aTitle[nCnt].bMove = true;				// �ړ���

				break;

			case TYPE_AND:		// �A���h

				m_aTitle[nCnt].pLogo->SetPos(AND_POS);		// �ʒu
				m_aTitle[nCnt].pLogo->SetPosOld(AND_POS);	// �O��̈ʒu
				m_aTitle[nCnt].pLogo->SetSize(AND_SIZE);	// �T�C�Y

				// �e�N�X�`���̐ݒ菈��
				m_aTitle[nCnt].pLogo->BindTexture(CManager::Get()->GetTexture()->Regist(AND_TEXTURE));

				// ����ݒ肷��
				m_aTitle[nCnt].move = NONE_D3DXVECTOR3;		// �ړ���
				m_aTitle[nCnt].bDisp = false;				// �\����
				m_aTitle[nCnt].bMove = false;				// �ړ���

				break;

			case TYPE_CAT:		// �l�R

				m_aTitle[nCnt].pLogo->SetPos(CAT_POS);		// �ʒu
				m_aTitle[nCnt].pLogo->SetPosOld(CAT_POS);	// �O��̈ʒu
				m_aTitle[nCnt].pLogo->SetSize(CAT_SIZE);	// �T�C�Y

				// �e�N�X�`���̐ݒ菈��
				m_aTitle[nCnt].pLogo->BindTexture(CManager::Get()->GetTexture()->Regist(CAT_TEXTURE));

				// ����ݒ肷��
				m_aTitle[nCnt].move.x = ESCAPE_MOVE_SPEED;	// �ړ���
				m_aTitle[nCnt].bDisp = true;				// �\����
				m_aTitle[nCnt].bMove = false;				// �ړ���

				break;
			}

			m_aTitle[nCnt].pLogo->SetRot(NONE_D3DXVECTOR3);	// ����
			m_aTitle[nCnt].pLogo->SetAngle();				// ����
			m_aTitle[nCnt].pLogo->SetLength();				// ����

			// ���_���W�̐ݒ菈��
			m_aTitle[nCnt].pLogo->SetVertexRot();
		}
		else
		{ // ��L�ȊO

			// ��~
			assert(false);
		}
	}

	m_state = STATE_ESCAPE;		// ���
	m_nStateCount = 0;			// ��ԃJ�E���g
}

//============================
//��������
//============================
CTitleLogo* CTitleLogo::Create(void)
{
	// �^�C�g�����S�̃|�C���^�𐶐�
	CTitleLogo* pTitle = nullptr;

	if (pTitle == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pTitle = new CTitleLogo;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pTitle != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pTitle->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pTitle->SetData();
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �^�C�g�����S�̃|�C���^��Ԃ�
	return pTitle;
}

//============================
// ������Ԃ̏���
//============================
void CTitleLogo::EscapeProcess(void)
{
	// �ړ�����
	Move(TYPE::TYPE_RAT);		// �l�Y�~
	Move(TYPE::TYPE_CAT);		// �l�R

	// �l�Y�~�̈ʒu�̐ݒ菈��
	EscapeRatPosSet();

	// �l�R�̈ʒu�̐ݒ菈��
	EscapeCatPosSet();

	if (m_nStateCount % LOCUS_COUNT == 0)
	{ // ��莞�Ԃ��Ƃ�

		// �c���̔�������
		Locus(TYPE_RAT);
		Locus(TYPE_CAT);
	}

	// �c���̔����J�E���g�����Z����
	m_nStateCount++;
}

//============================
// ���o����Ԃ̏���
//============================
void CTitleLogo::AndProcess(void)
{
	// ��ԃJ�E���g�����Z����
	m_nStateCount++;

	// �T�C�Y���擾����
	D3DXVECTOR3 rot = m_aTitle[TYPE_AND].pLogo->GetRot();
	D3DXVECTOR3 size = m_aTitle[TYPE_AND].pLogo->GetSize();

	// �T�C�Y�����Z����
	size.x = AND_ADD_SIZE * m_nStateCount;
	size.y = AND_ADD_SIZE * m_nStateCount;

	// ���������Z����
	rot.z -= (D3DX_PI * 2) / AND_APPEAR_COUNT;

	// �����̐��K��
	useful::RotNormalize(&rot.z);

	if (size.x >= AND_DEST_SIZE.x ||
		size.y >= AND_DEST_SIZE.y)
	{ // �T�C�Y�����ȏ�ɂȂ����ꍇ

		// �T�C�Y��␳����
		size = AND_DEST_SIZE;

		// �������܂������ɕ␳����
		rot.z = 0.0f;

		// �ҋ@��Ԃɂ���
		m_state = STATE_WAIT;

		// �^�C�g����ҋ@��Ԃɂ���
		CTitle::SetState(CTitle::STATE_WAIT);

		// �ړ��󋵂� true �ɂ���(�����ɓ����^�C�~���O�ɓ��邩������Ȃ����ߑ΍􂵂Ă���)
		m_aTitle[TYPE_RAT].bMove = true;
		m_aTitle[TYPE_CAT].bMove = true;

		// �^�C�g���̃v���X�𐶐�
		CTitlePress::Create();
	}

	// �����ƃT�C�Y��K�p����
	m_aTitle[TYPE_AND].pLogo->SetRot(rot);
	m_aTitle[TYPE_AND].pLogo->SetSize(size);
}

//============================
// ��ʊO��Ԃ̏���
//============================
void CTitleLogo::FrameOutProcess(void)
{
	// �ړ��󋵂� true �ɂ���
	m_aTitle[TYPE_RAT].bMove = true;
	m_aTitle[TYPE_CAT].bMove = true;

	// �ړ�����
	Move(TYPE::TYPE_RAT);		// �l�Y�~
	Move(TYPE::TYPE_CAT);		// �l�R

	// ��ʊO��Ԃ̃l�Y�~�̈ʒu�֌W����
	FrameOutRatPosSet();

	// ��ʊO��Ԃ̃l�R�̈ʒu�֌W����
	FrameOutCatPosSet();

	// ��ʊO��Ԃ̃A���h�̏���
	FrameOutAnd();

	if (m_nStateCount % LOCUS_COUNT == 0)
	{ // ��莞�Ԃ��Ƃ�

		// �c���̔�������
		Locus(TYPE_RAT);
		Locus(TYPE_CAT);
	}

	// �c���̔����J�E���g�����Z����
	m_nStateCount++;
}

//============================
// �����؂��Ԃ̏���
//============================
void CTitleLogo::ShakeOffProcess(void)
{
	// �ړ��󋵂� true �ɂ���
	m_aTitle[TYPE_RAT].bMove = true;

	// �ړ�����
	Move(TYPE::TYPE_RAT);		// �l�Y�~

	// �����؂��Ԃ̃l�Y�~�̈ʒu�֌W����
	ShakeOffRatPosSet();

	if (m_nStateCount % LOCUS_COUNT == 0)
	{ // ��莞�Ԃ��Ƃ�

		// �c���̔�������
		Locus(TYPE_RAT);
	}

	m_bSe = false;		// SE�Đ����Ȃ�

	// �c���̔����J�E���g�����Z����
	m_nStateCount++;
}

//============================
// �������Ԃ̏���
//============================
void CTitleLogo::HoleInProcess(void)
{
	// �l�Y�~�̏����擾����
	D3DXVECTOR3 pos = m_aTitle[TYPE_RAT].pLogo->GetPos();		// �ʒu
	D3DXVECTOR3 size = m_aTitle[TYPE_RAT].pLogo->GetSize();		// �T�C�Y

	// �T�C�Y�����Z����
	size.x -= RAT_SIZE.x / HOLEIN_RAT_SIZE_FRAME;
	size.y -= RAT_SIZE.y / HOLEIN_RAT_SIZE_FRAME;

	// ��Ɉړ�������(���̒��ɓ����Ă������������o)
	pos.y -= HOLEIN_RAT_SUB_POS;

	if (size.x <= 0.0f ||
		size.y <= 0.0f)
	{ // �T�C�Y��0.0f�ȉ��ɂȂ����ꍇ

		// �T�C�Y��␳����
		size = NONE_D3DXVECTOR3;

		// �l�Y�~��`�悵�Ȃ��悤�ɂ���
		m_aTitle[TYPE_RAT].bDisp = false;

		// ��~��Ԃɂ���
		m_state = STATE_STOP;

		// �^�C�g�������̒��ɓ�������Ԃɂ���
		CTitle::SetState(CTitle::STATE_HOLEIN);

		m_bSe = false;		// SE�Đ����Ȃ�
	}

	// �l�Y�~�̏���K�p����
	m_aTitle[TYPE_RAT].pLogo->SetPos(pos);		// �ʒu
	m_aTitle[TYPE_RAT].pLogo->SetSize(size);	// �T�C�Y
}

//============================
// �ړ�����
//============================
void CTitleLogo::Move(const TYPE type)
{
	if (m_aTitle[type].bMove == true)
	{ // �ړ��󋵂� true �̏ꍇ

		// �ʒu���擾����
		D3DXVECTOR3 pos = m_aTitle[type].pLogo->GetPos();

		// �ʒu�����Z����
		pos.x += m_aTitle[type].move.x;

		// �ʒu��K�p����
		m_aTitle[type].pLogo->SetPos(pos);
	}
}

//============================
// �c����������
//============================
void CTitleLogo::Locus(const TYPE type)
{
	if (m_aTitle[type].bMove == true)
	{ // �ړ��󋵂� true �̏ꍇ

		// �c���̐�������
		CLocus2D::Create
		(
			m_aTitle[type].pLogo->GetPos(),		// �ʒu
			NONE_D3DXVECTOR3,					// ����
			m_aTitle[type].pLogo->GetSize(),	// �T�C�Y
			0.2f,								// �����x
			40,									// ����
			m_aTitle[type].pLogo->GetTexIdx()	// �e�N�X�`���̃C���f�b�N�X
		);
	}
}

//============================
// ������Ԃ̃l�Y�~�̈ʒu�֌W����
//============================
void CTitleLogo::EscapeRatPosSet(void)
{
	// �ʒu���擾����
	D3DXVECTOR3 pos = m_aTitle[TYPE_RAT].pLogo->GetPos();

	if (pos.x >= CAT_APPEAR_RAT_POS)
	{ // �l�Y�~�̈ʒu�����ʒu�𒴂����ꍇ

		// �ړ��󋵂� true �ɂ���
		m_aTitle[TYPE_CAT].bMove = true;
	}

	if (pos.x >= RAT_ESCAPE_STOP_POS)
	{ // �l�Y�~�̈ʒu�����̈ʒu�ɒB�����ꍇ

		// �l�Y�~�̈ʒu��␳����
		pos.x = RAT_ESCAPE_STOP_POS;

		// �ړ��󋵂� false �ɂ���
		m_aTitle[TYPE_RAT].bMove = false;
	}

	// �ʒu��K�p����
	m_aTitle[TYPE_RAT].pLogo->SetPos(pos);
}

//============================
// ������Ԃ̃l�R�̈ʒu�֌W����
//============================
void CTitleLogo::EscapeCatPosSet(void)
{
	// �ʒu���擾����
	D3DXVECTOR3 pos = m_aTitle[TYPE_CAT].pLogo->GetPos();

	if (pos.x >= CAT_ESCAPE_STOP_POS)
	{ // �l�R�̈ʒu�����̈ʒu�ɒB�����ꍇ

		// �l�R�̈ʒu��␳����
		pos.x = CAT_ESCAPE_STOP_POS;

		// �ړ��󋵂� false �ɂ���
		m_aTitle[TYPE_CAT].bMove = false;

		// �A���h�̕\���󋵂� true �ɂ���
		m_aTitle[TYPE_AND].bDisp = true;

		// �ҋ@��Ԃɂ���
		m_state = STATE_AND;

		// ��ԃJ�E���g������������
		m_nStateCount = 0;
	}

	// �ʒu��K�p����
	m_aTitle[TYPE_CAT].pLogo->SetPos(pos);
}

//============================
// ��ʊO��Ԃ̃l�Y�~�̈ʒu�֌W����
//============================
void CTitleLogo::FrameOutRatPosSet(void)
{
	// �ʒu���擾����
	D3DXVECTOR3 pos = m_aTitle[TYPE_RAT].pLogo->GetPos();

	if (pos.x >= CAT_FRAMEOUT_RAT_POS)
	{ // �l�Y�~�̈ʒu�����ʒu�𒴂����ꍇ

		// �ړ��󋵂� true �ɂ���
		m_aTitle[TYPE_CAT].bMove = true;
	}

	if (pos.x >= RAT_FRAMEOUT_STOP_POS)
	{ // �l�Y�~�̈ʒu�����̈ʒu�ɒB�����ꍇ

		// �l�Y�~�̈ʒu��␳����
		pos.x = RAT_FRAMEOUT_STOP_POS;

		// �ړ��󋵂� false �ɂ���
		m_aTitle[TYPE_RAT].bMove = false;
	}

	// �ʒu��K�p����
	m_aTitle[TYPE_RAT].pLogo->SetPos(pos);
}

//============================
// ��ʊO��Ԃ̃l�R�̈ʒu�֌W����
//============================
void CTitleLogo::FrameOutCatPosSet(void)
{
	// �ʒu���擾����
	D3DXVECTOR3 pos = m_aTitle[TYPE_CAT].pLogo->GetPos();

	if (pos.x >= CAT_FRAMEOUT_STOP_POS)
	{ // �l�R�̈ʒu�����̈ʒu�ɒB�����ꍇ

		// �l�R�̈ʒu��␳����
		pos.x = CAT_FRAMEOUT_STOP_POS;

		// �ړ��󋵂� false �ɂ���
		m_aTitle[TYPE_CAT].bMove = false;

		// �l�R��\�������Ȃ�����
		m_aTitle[TYPE_CAT].bDisp = false;

		// ��ԃJ�E���g������������
		m_nStateCount = 0;

		// �����؂��Ԃɂ���
		m_state = STATE_SHAKEOFF;

		// ��ʊO���̃l�Y�~�̐ݒ菈��
		FrameOutSetRat();
	}
	else
	{
		if (m_bSe == false)
		{ // SE�炵�ĂȂ�������

			// �z�[���C���Đ�
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_TITLEBLOW);
			m_bSe = true;
		}
	}

	// �ʒu��K�p����
	m_aTitle[TYPE_CAT].pLogo->SetPos(pos);
}

//============================
// ��ʊO���̃l�Y�~�̐ݒ菈��
//============================
void CTitleLogo::FrameOutSetRat(void)
{
	// �ʒu���擾����
	D3DXVECTOR3 pos = m_aTitle[TYPE_RAT].pLogo->GetPos();

	// �l�Y�~�̈ړ��ʂ�ݒ肷��
	m_aTitle[TYPE_RAT].move.x = SHAKEOFF_MOVE_SPEED;

	// �ʒu��ݒ肷��
	pos.y = SHAKEOFF_RAT_POS_Y;

	// �ʒu��K�p����
	m_aTitle[TYPE_RAT].pLogo->SetPos(pos);
}

//============================
// ��ʊO��Ԃ̃A���h�̏���
//============================
void CTitleLogo::FrameOutAnd(void)
{
	// �ʒu�ƃT�C�Y���擾����
	D3DXVECTOR3 pos = m_aTitle[TYPE_AND].pLogo->GetPos();
	D3DXVECTOR3 rot = m_aTitle[TYPE_AND].pLogo->GetRot();

	// �ʒu�����Z����
	pos += m_aTitle[TYPE_AND].move;

	// �d�͂�������
	m_aTitle[TYPE_AND].move.y += 0.3f;

	// ���������Z����
	rot.z += 0.02f;

	// �����̐��K��
	useful::RotNormalize(&rot.z);

	if (m_state == STATE_SHAKEOFF)
	{ // �T�C�Y�����ȏ�ɂȂ����ꍇ

		// �������܂������ɕ␳����
		rot.z = 0.0f;

		// �A���h�̕`������Ȃ��悤�ɂ���
		m_aTitle[TYPE_AND].bDisp = false;

		//m_bSe = false;
	}

	// �ʒu�ƃT�C�Y��K�p����
	m_aTitle[TYPE_AND].pLogo->SetPos(pos);
	m_aTitle[TYPE_AND].pLogo->SetRot(rot);
}

//============================
// �����؂��Ԃ̃l�Y�~�̈ʒu�֌W����
//============================
void CTitleLogo::ShakeOffRatPosSet(void)
{
	// �ʒu���擾����
	D3DXVECTOR3 pos = m_aTitle[TYPE_RAT].pLogo->GetPos();

	if (pos.x <= SHAKEOFF_RAT_STOP_POS)
	{ // �l�Y�~�̈ʒu�����̈ʒu�ɒB�����ꍇ

		// �l�Y�~�̈ʒu��␳����
		pos.x = SHAKEOFF_RAT_STOP_POS;

		// �ړ��󋵂� false �ɂ���
		m_aTitle[TYPE_RAT].bMove = false;

		// �������Ԃɂ���
		m_state = STATE_HOLEIN;
	}

	// �ʒu��K�p����
	m_aTitle[TYPE_RAT].pLogo->SetPos(pos);
}