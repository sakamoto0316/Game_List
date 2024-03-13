//===========================================
//
// �X���C���̃��C������[slime.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "slime.h"
#include "useful.h"
#include "Particle.h"

//==============================
// �R���X�g���N�^
//==============================
CSlime::CSlime() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{

}

//==============================
// �f�X�g���N�^
//==============================
CSlime::~CSlime()
{

}

//==============================
// �j�Ђ̏���������
//==============================
HRESULT CSlime::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // �����������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �l��Ԃ�
	return S_OK;
}

//========================================
// �j�Ђ̏I������
//========================================
void CSlime::Uninit(void)
{
	// �I������
	CObstacle::Uninit();
}

//=====================================
// �j�Ђ̍X�V����
//=====================================
void CSlime::Update(void)
{

}

//=====================================
// �j�Ђ̕`�揈��
//=====================================
void CSlime::Draw(void)
{
	// �`�揈��
	CObstacle::Draw();
}

//=====================================
// ���̐ݒ菈��
//=====================================
void CSlime::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// ���̐ݒ菈��
	CObstacle::SetData(pos,rot, type);
}

//=====================================
// �q�b�g����
//=====================================
bool CSlime::Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 max = D3DXVECTOR3(collSize.x, collSize.y, collSize.z);		// �T�C�Y�̍ő�l
	D3DXVECTOR3 min = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);			// �T�C�Y�̍ŏ��l

	if (useful::RectangleCollisionXY(GetPos(), pPlayer->GetPos(), GetFileData().vtxMax, max, GetFileData().vtxMin, min) == true &&
		useful::RectangleCollisionXZ(GetPos(), pPlayer->GetPos(), GetFileData().vtxMax, max, GetFileData().vtxMin, min) == true &&
		useful::RectangleCollisionYZ(GetPos(), pPlayer->GetPos(), GetFileData().vtxMax, max, GetFileData().vtxMin, min) == true)
	{ // �l�p�̓����蔻��̒��ɓ����Ă����ꍇ
		CParticle::Create(pPlayer->GetPos(), CParticle::TYPE_SLIME);
		// true ��Ԃ�
		return true;
	}
	else
	{ // ��L�ȊO

		// false ��Ԃ�
		return false;
	}
}