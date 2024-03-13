//===========================================
//
// �X�C�b�`�̃��C������[switch.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "switch.h"
#include "model.h"
#include "useful.h"

#include "objectbillboard.h"
#include "texture.h"

// �}�N����`
#define LEVER_SHIFT		(5.0f)		// ���o�[�̂��炷��
#define LEVER_HEIGHT	(18.0f)		// ���o�[�̒ǉ��̍���
#define LEVER_CORRECT	(0.05f)		// ���o�[�̕␳�W��

//==============================
// �R���X�g���N�^
//==============================
CSwitch::CSwitch() : CObject(CObject::TYPE_NONE, CObject::PRIORITY_BLOCK)
{
	// �S�Ă̒l���N���A����
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_apModel[nCnt] = nullptr;		// ���f���̏��
	}
	m_pGimmickUI = nullptr;				// �M�~�b�NUI�̏��
	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		m_aUIFalse[nCnt] = false;		// �S��[False]�̎���UI���폜����
	}
	m_posCopy = NONE_D3DXVECTOR3;		// �ʒu�̃R�s�[
	m_fRotDest = 0.0f;					// �ړI�̌���
	m_fPosYDest = 0.0f;					// �ړI�̈ʒu(Y��)
	m_bBoot = false;					// �N����
}

//==============================
// �f�X�g���N�^
//==============================
CSwitch::~CSwitch()
{

}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CSwitch::Init(void)
{
	// �S�Ă̒l������������
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apModel[nCnt] == nullptr)
		{ // ���f���̏�� NULL �̏ꍇ

			// ���f���̐�������
			m_apModel[nCnt] = CModel::Create(TYPE_NONE, PRIORITY_BLOCK);
		}
	}
	m_pGimmickUI = nullptr;				// �M�~�b�NUI�̏��
	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		m_aUIFalse[nCnt] = false;		// �S��[False]�̎���UI���폜����
	}
	m_posCopy = NONE_D3DXVECTOR3;		// �ʒu�̃R�s�[
	m_fRotDest = 0.0f;					// �ړI�̌���
	m_fPosYDest = 0.0f;					// �ړI�̈ʒu(Y��)
	m_bBoot = false;					// �N����

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �j�Ђ̏I������
//========================================
void CSwitch::Uninit(void)
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

	if (m_pGimmickUI != nullptr)
	{ // �M�~�b�NUI�� NULL ����Ȃ��ꍇ

		// �M�~�b�NUI�̏I������
		m_pGimmickUI->Uninit();
		m_pGimmickUI = nullptr;
	}
	
	// �{�̂̏I������
	Release();
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CSwitch::Update(void)
{
	// ��ԃ}�l�[�W���[
	StateManager();

	if (m_pGimmickUI != nullptr)
	{ // �M�~�b�NUI�� NULL ����Ȃ��ꍇ

		// �X�V����
		m_pGimmickUI->Update();
	}
}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CSwitch::Draw(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{ // ���f���� NULL ����Ȃ��ꍇ

			// ���f���̕`�揈��
			m_apModel[nCnt]->Draw();
		}
	}

	if (m_pGimmickUI != nullptr)
	{ // �M�~�b�NUI�� NULL ����Ȃ��ꍇ

		// �`�揈��
		m_pGimmickUI->DrawLightOff();
	}
}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CSwitch::Draw(const float fAlpha)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{ // ���f���� NULL ����Ȃ��ꍇ

			// ���f���̕`�揈��
			m_apModel[nCnt]->Draw(fAlpha);
		}
	}

	if (m_pGimmickUI != nullptr)
	{ // �M�~�b�NUI�� NULL ����Ȃ��ꍇ

		// �`�揈��
		m_pGimmickUI->DrawLightOff();
	}
}

//=====================================
// �N���󋵂̓���ւ�����
//=====================================
void CSwitch::ChangeBoot(void)
{
	// �N���󋵂����ւ���
	m_bBoot = !m_bBoot;
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CSwitch::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	CXFile::TYPE type;

	// �S�Ă̒l��ݒ肷��
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		// ��ނ�ݒ肷��
		type = (CXFile::TYPE)(CXFile::TYPE_LEVERBODY + nCnt);

		if (m_apModel[nCnt] != nullptr)
		{ // ���f���� NULL ����Ȃ��ꍇ

			switch (nCnt)
			{
			case TYPE_BASE:

				m_apModel[nCnt]->SetPos(pos);				// �ʒu

				break;

			case TYPE_LEVER:

				m_apModel[nCnt]->SetPos(D3DXVECTOR3(pos.x + sinf(rot.y) * LEVER_SHIFT, pos.y + LEVER_HEIGHT, pos.z + cosf(rot.y) * LEVER_SHIFT));				// �ʒu

				break;

			default:

				// ��~
				assert(false);

				break;
			}

			// ���̐ݒ菈��
			m_apModel[nCnt]->SetPosOld(m_apModel[nCnt]->GetPos());			// �O��̈ʒu
			m_apModel[nCnt]->SetRot(rot);				// ����
			m_apModel[nCnt]->SetScale(NONE_SCALE);		// �g�嗦
			m_apModel[nCnt]->SetFileData(type);			// ���f�����
		}
	}
	m_posCopy = pos;						// �ʒu�̃R�s�[
	m_fRotDest = 0.0f;						// �ړI�̌���
	m_fPosYDest = pos.y + LEVER_HEIGHT;		// �ړI�̈ʒu(Y��)
	m_bBoot = false;						// �N����
}

//=======================================
// ��������
//=======================================
CSwitch* CSwitch::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CSwitch* pSwitch = nullptr;

	if (pSwitch == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �X�C�b�`�𐶐�
		pSwitch = new CSwitch;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pSwitch != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pSwitch->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pSwitch->SetData(pos, rot);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �X�C�b�`�̃|�C���^��Ԃ�
	return pSwitch;
}

//=======================================
// ��ԃ}�l�[�W���[
//=======================================
void CSwitch::StateManager(void)
{
	// �ʒu�ƌ������擾����
	D3DXVECTOR3 pos = m_apModel[TYPE::TYPE_LEVER]->GetPos();
	D3DXVECTOR3 rot = m_apModel[TYPE::TYPE_LEVER]->GetRot();

	if (m_bBoot == true)
	{ // �N���󋵂� true �̏ꍇ

		// �ړI�̌�����ݒ肷��
		m_fRotDest = D3DX_PI * -0.5f;

		// �ړI�̈ʒu��ݒ肷��
		m_fPosYDest = m_posCopy.y - LEVER_HEIGHT;
	}
	else
	{ // ��L�ȊO

		// �ړI�̌�����ݒ肷��
		m_fRotDest = 0.0f;

		// �ړI�̈ʒu��ݒ肷��
		m_fPosYDest = m_posCopy.y + LEVER_HEIGHT;
	}

	// �����̕␳����
	useful::RotCorrect(m_fRotDest, &rot.x, LEVER_CORRECT);

	// �ʒu�̕␳����
	useful::Correct(m_fPosYDest, &pos.y, LEVER_CORRECT);

	// �����̐��K��
	useful::RotNormalize(&rot.x);

	// �ʒu�ƌ�����K�p����
	m_apModel[TYPE_LEVER]->SetPos(pos);
	m_apModel[TYPE_LEVER]->SetRot(rot);
}

//=======================================
// �M�~�b�NUI�̐ݒ菈��
//=======================================
void CSwitch::SetGimmickUI(bool Set, int Player_Idx)
{
	if (Set == true)
	{//UI�\���͈͓̔��ɂ���ꍇ

		if (m_pGimmickUI == nullptr)
		{ // �M�~�b�NUI�� NULL ����Ȃ��ꍇ

			//������UI�\����Ԃ�ON�ɂ���
			m_aUIFalse[Player_Idx] = true;

			//UI�̕\��
			m_pGimmickUI = CBillboard::Create(TYPE_NONE, PRIORITY_UI);
			m_pGimmickUI->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\UI_GimmickOn.png"));
			m_pGimmickUI->SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0f));

			// ���̐ݒ菈��
			m_pGimmickUI->SetPos(D3DXVECTOR3(				// �ʒu
				m_apModel[TYPE_BASE]->GetPos().x,
				m_apModel[TYPE_BASE]->GetPos().y + 60.0f,
				m_apModel[TYPE_BASE]->GetPos().z));
			m_pGimmickUI->SetPosOld(D3DXVECTOR3(			// �O��̈ʒu
				m_apModel[TYPE_BASE]->GetPos().x,
				m_apModel[TYPE_BASE]->GetPos().y + 60.0f,
				m_apModel[TYPE_BASE]->GetPos().z));

			// ���_���W�̐ݒ菈��
			m_pGimmickUI->SetVertex();
		}
	}
	else
	{//UI�\���͈͓̔��ɂ��Ȃ��ꍇ

		//������UI�\����Ԃ�OFF�ɂ���
		m_aUIFalse[Player_Idx] = false;
	}

	//�S�Ẵv���C���[�̕\����Ԃ�OFF�̂Ƃ��폜����
	if (m_aUIFalse[0] == false &&
		m_aUIFalse[1] == false &&
		m_aUIFalse[2] == false &&
		m_aUIFalse[3] == false)
	{
		if (m_pGimmickUI != NULL)
		{ // �M�~�b�NUI�� NULL �̏ꍇ

			// �M�~�b�NUI�̏I������
			m_pGimmickUI->Uninit();
			m_pGimmickUI = NULL;
		}
	}
}

//=======================================
// ���f���̎擾����
//=======================================
CModel* CSwitch::GetModel(const TYPE type)
{
	// ���f���̏���Ԃ�
	return m_apModel[type];
}

//=======================================
// �N���󋵂̐ݒ菈��
//=======================================
void CSwitch::SetBoot(const bool bBoot)
{
	// �N���󋵂�ݒ肷��
	m_bBoot = bBoot;
}

//=======================================
// �N���󋵂̎擾����
//=======================================
bool CSwitch::GetBoot(void) const
{
	// �N���󋵂�Ԃ�
	return m_bBoot;
}