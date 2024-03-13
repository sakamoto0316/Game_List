//===========================================
//
// �R�b�v�̏���[cup.cpp]
// Author ��{�ėB
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "cup.h"
#include "useful.h"
#include "objectX.h"
#include "consent.h"
#include "object3D.h"
#include "input.h"
#include "texture.h"
#include "effect.h"
#include "sound.h"

//==============================
// �R���X�g���N�^
//==============================
CCup::CCup() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	m_move = NONE_D3DXVECTOR3;
	m_State = STATE_FALSE;
	m_pWater = NULL;
	m_pConsent = NULL;
	m_WaterSize = NONE_D3DXVECTOR3;
	m_ThunderCounter = 0;
	m_bSe = false;				// SE�Đ���
	SetRatUse(true);
}

//==============================
// �f�X�g���N�^
//==============================
CCup::~CCup()
{

}

//==============================
// �R�b�v�̏���������
//==============================
HRESULT CCup::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // �����������Ɏ��s�����ꍇ

	  // ���s��Ԃ�
		return E_FAIL;
	}

	m_bSe = false;				// SE�Đ���

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �R�b�v�̏I������
//========================================
void CCup::Uninit(void)
{
	if (m_pConsent != NULL)
	{ // �R���Z���g�� NULL �̏ꍇ

		// �R���Z���g�̏I������
		m_pConsent->Uninit();
	}

	if (m_pWater != NULL)
	{ // ���� NULL �̏ꍇ

		// ���̏I������
		m_pWater->Uninit();
	}

	// �I������
	CObstacle::Uninit();
}

//=====================================
// �R�b�v�̍X�V����
//=====================================
void CCup::Update(void)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	StateManager(&pos, &rot);

	//�ʒu�X�V
	pos += m_move;

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_0) == true)
	{ // 0�{�^�����������ꍇ
		Action();
	}

	SetPos(pos);
	SetRot(rot);

	if (m_pWater != NULL)
	{ // ���� NULL ����Ȃ��ꍇ

		// ���̍X�V����
		m_pWater->Update();
	}
}

//=====================================
// �R�b�v�̕`�揈��
//=====================================
void CCup::Draw(void)
{
	// �`�揈��
	CObstacle::Draw(1.0f);

	if (m_pConsent != NULL)
	{
		if (m_State == STATE_TRUE)
		{
			m_pConsent->Draw(1.0f);
		}
		else
		{
			m_pConsent->Draw(0.3f);
		}
	}

	if (m_pWater != NULL)
	{
		m_pWater->Draw();
	}
}

//=====================================
// ��ԊǗ�
//=====================================
void CCup::StateManager(D3DXVECTOR3 *pos, D3DXVECTOR3 *rot)
{
	switch (m_State)
	{
	case CCup::STATE_FALSE:

		break;

	case CCup::STATE_FALLWAIT:	//�M�~�b�N�N��������ʔ����܂ł̏�������
		rot->z += 0.07f;
		m_move.y -= 0.75f;
		m_move.x = sinf(rot->y + (D3DX_PI * -0.5f)) * 4.0f;
		m_move.z = cosf(rot->y + (D3DX_PI * -0.5f)) * 4.0f;

		if (pos->y < 15.0f)
		{
			pos->y = 15.0f;
			m_State = STATE_TRUE;

			// �R�b�v�����������𗬂�
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_THE_CUP_FALLS);

			// �r���r�����𗬂�
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_WATERBIRIBIRI);

			m_pWater = CObject3D::Create(CObject3D::TYPE_NONE, PRIORITY_BLOCK);
			m_pWater->SetPos(GetPos());
			m_pWater->SetRot(D3DXVECTOR3(D3DX_PI * 0.5f, rot->y, 0.0f));
			m_pWater->SetSize(m_WaterSize);
			m_pWater->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\water.png"));
		}
		break;

	case CCup::STATE_TRUE:	//�M�~�b�N�̌��ʔ��������~�܂ł̏���
		m_move = NONE_D3DXVECTOR3;
		pos->y = 15.0f;
		m_ThunderCounter++;

		D3DXVECTOR3 WaterPos = m_pWater->GetPos();

		if (m_WaterSize.x < 150.0f)
		{
			WaterPos.x += sinf(rot->y + (D3DX_PI * -0.5f)) * 0.5f;
			WaterPos.z += cosf(rot->y + (D3DX_PI * -0.5f)) * 0.5f;
			m_WaterSize.x += 0.5f;
			m_WaterSize.y += 0.5f;
		}

		if (m_ThunderCounter % 2 == 0)
		{
			int nRandX = rand() % (int)(m_WaterSize.x * 2.0f);
			int nRandZ = rand() % (int)(m_WaterSize.y * 2.0f);
			int nHalf = (int)m_WaterSize.x;
			CEffect *pEffect = CEffect::Create(D3DXVECTOR3(WaterPos.x + (nRandX - nHalf), WaterPos.y, WaterPos.z + (nRandZ - nHalf)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10, 30.0f, CEffect::TYPE::TYPE_THUNDER, NONE_D3DXCOLOR, true);
		}

		m_pWater->SetPos(WaterPos);
		m_pWater->SetSize(m_WaterSize);
		break;
	}
}

//=====================================
// �R�b�v��������Ƃ��̏���
//=====================================
void CCup::Action(void)
{
	if (m_State == STATE_FALSE)
	{
		m_State = STATE_FALLWAIT;
		SetAction(true);
	}
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CCup::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos, rot, type);

	if (m_pConsent == NULL)
	{
		m_pConsent = CConsent::Create(D3DXVECTOR3(
			pos.x + sinf(rot.y + (D3DX_PI * -0.5f)) * 200.0f,
			0.0f,
			pos.z + cosf(rot.y + (D3DX_PI * -0.5f)) * 200.0f));
		m_pConsent->SetRot(D3DXVECTOR3(0.0f, rot.y + D3DX_PI * 1.0f, 0.0f));
		m_pConsent->SetMain(this);
	}
}

//=====================================
// �q�b�g����
//=====================================
bool CCup::Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	if (m_pWater != nullptr)
	{ // ���� NULL ����Ȃ��ꍇ

		// ���̈ʒu�Ɣ��a���擾����
		D3DXVECTOR3 posWater = m_pWater->GetPos();
		float radiusWater = m_pWater->GetSize().x;

		if (posWater.y >= pPlayer->GetPos().y &&
			posWater.y <= pPlayer->GetPos().y + collSize.y &&
			pPlayer->GetState() != CPlayer::STATE_INVINCIBLE &&
			useful::CylinderInner(pPlayer->GetPos(), posWater, radiusWater) == true)
		{ // �����蔻��̒��ɓ������ꍇ

			// true ��Ԃ�
			return true;
		}
	}

	// false ��Ԃ�
	return false;
}

//=====================================
// �q�b�g����
//=====================================
bool CCup::HitCircle(CPlayer* pPlayer, const float Radius)
{
	if (GetAction() == false &&
		useful::CircleCollisionXZ(pPlayer->GetPos(), GetPos(), Radius, GetFileData().fRadius) == true)
	{//�~�͈͓̔��̏ꍇture��Ԃ�
		return true;
	}

	// false ��Ԃ�
	return false;
}