//============================================
//
//	�L���[�u�_���[�W [CubeDamage.cpp]
//	Author:sakamoto kai
//
//============================================
#include "CubeDamage.h"
#include "CubeBlock.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "texture.h"
#include "object3D.h"
#include "CubeEffect.h"

#define WAIGHT_SIZE (11)		//���̒��_��
#define HEIGHT_SIZE (11)		//�c�̒��_��
#define WAIGHT_CENTER (0.5f)	//���̌��_(0.0f�`1.0f)
#define HEIGHT_CENTER (0.5f)	//�c�̌��_(0.0f�`1.0f)
#define FIELD_SIZE (200.0f)		//���ꖇ�̑傫��

//�ÓI�����o�ϐ��錾
int CCubeDamage::m_nExplosionCount = 0;
int CCubeDamage::m_nExplosionNum = 0;

//====================================================================
//�R���X�g���N�^
//====================================================================
CCubeDamage::CCubeDamage(int nPriority) :CObjmeshCube(nPriority)
{
	m_pos = INITVECTOR3;
	m_fDamage = 0.0f;
	m_CubeType = CUBETYPE_NORMAL;
	m_pShadow = nullptr;
	m_fSpinCount = INITVECTOR3;
	m_fSpinSpeed = D3DXVECTOR3(-100.0f, -100.0f, -100.0f);
	m_fBOOLSpin = INITVECTOR3;
	m_bSpin = false;
	SpinPos = INITVECTOR3;
	m_fSpinDistance = 0.0f;
	m_fSpinDisMove = 0.0f;
	m_nLife = -1;
	m_nExplosionIdx = -1;
	m_Move = INITVECTOR3;
	SpinSinCos = 0;
}

//====================================================================
//�f�X�g���N�^
//====================================================================
CCubeDamage::~CCubeDamage()
{
	
}

//====================================================================
//��������
//====================================================================
CCubeDamage* CCubeDamage::Create(void)
{
	CCubeDamage* pObject3D = NULL;

	if (pObject3D == NULL)
	{
		//�I�u�W�F�N�g3D�̐���
		pObject3D = new CCubeDamage();
	}

	//�I�u�W�F�N�g�̏���������
	if (FAILED(pObject3D->Init()))
	{//���������������s�����ꍇ
		return NULL;
	}

	return pObject3D;
}

//====================================================================
//����������
//====================================================================
HRESULT CCubeDamage::Init(void)
{
	CObjmeshCube::Init();

	SetTexture("data\\TEXTURE\\Test.jpg");

	SetType(TYPE_CUBEDAMEGE);

	m_pShadow = CObject3D::Create();
	m_pShadow->SetPos(INITVECTOR3);
	m_pShadow->SetRot(D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f));
	m_pShadow->SetWight(0.0f);
	m_pShadow->SetHeight(0.0f);
	m_pShadow->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.3f));

	return S_OK;
}

//====================================================================
//�I������
//====================================================================
void CCubeDamage::Uninit(void)
{
	if (m_pShadow != nullptr)
	{
		m_pShadow->SetDeathFlag(true);
	}

	if (m_CubeType == CUBETYPE_EXPLOSION)
	{
		ExplosionSet();
	}

	CObjmeshCube::Uninit();

	SetDeathFlag(true);
}

//====================================================================
//�X�V����
//====================================================================
void CCubeDamage::Update(void)
{
	m_pos = GetPos();
	m_posOld = m_pos;

	if (m_bSpin == true)
	{//��]�ړ����܂߂�ꍇ
		if (m_CubeType != CUBETYPE_EXPLOSION)
		{
			m_fSpinCount += m_fSpinSpeed;
			m_fSpinDistance += m_fSpinDisMove;
		}

		//���x�������Ă��Ȃ��ꍇ�{���������Ȃ��悤�ɂ���
		if (m_fSpinSpeed.x > -100.0f)
		{
			m_fBOOLSpin.x = 1.0f;
		}
		if (m_fSpinSpeed.y > -100.0f)
		{
			m_fBOOLSpin.y = 1.0f;
		}
		if (m_fSpinSpeed.z > -100.0f)
		{
			m_fBOOLSpin.z = 1.0f;
		}

		//�w�肵����ނ̉�]�ړ����s��
		switch (SpinSinCos)
		{
		case 0:
			m_pos.x = SpinPos.x + (sinf(m_fSpinCount.y) * m_fSpinDistance * m_fBOOLSpin.y) + (sinf(m_fSpinCount.x) * m_fSpinDistance * m_fBOOLSpin.x);
			m_pos.y = SpinPos.y + (cosf(m_fSpinCount.x) * m_fSpinDistance * m_fBOOLSpin.x) + (sinf(m_fSpinCount.z) * m_fSpinDistance * m_fBOOLSpin.z);
			m_pos.z = SpinPos.z + (cosf(m_fSpinCount.y) * m_fSpinDistance * m_fBOOLSpin.y) + (cosf(m_fSpinCount.z) * m_fSpinDistance * m_fBOOLSpin.z);
			break;
		case 1:
			m_pos.x = SpinPos.x + (cosf(m_fSpinCount.y) * m_fSpinDistance * m_fBOOLSpin.y) + (cosf(m_fSpinCount.z) * m_fSpinDistance * m_fBOOLSpin.z);
			m_pos.y = SpinPos.y + (sinf(m_fSpinCount.y) * m_fSpinDistance * m_fBOOLSpin.y) + (sinf(m_fSpinCount.x) * m_fSpinDistance * m_fBOOLSpin.x);
			m_pos.z = SpinPos.z + (cosf(m_fSpinCount.x) * m_fSpinDistance * m_fBOOLSpin.x) + (sinf(m_fSpinCount.z) * m_fSpinDistance * m_fBOOLSpin.z);
			break;
		default:
			m_pos.x = SpinPos.x + (cosf(m_fSpinCount.x) * m_fSpinDistance * m_fBOOLSpin.x) + (sinf(m_fSpinCount.z) * m_fSpinDistance * m_fBOOLSpin.z);
			m_pos.y = SpinPos.y + (cosf(m_fSpinCount.y) * m_fSpinDistance * m_fBOOLSpin.y) + (cosf(m_fSpinCount.z) * m_fSpinDistance * m_fBOOLSpin.z);
			m_pos.z = SpinPos.z + (sinf(m_fSpinCount.y) * m_fSpinDistance * m_fBOOLSpin.y) + (sinf(m_fSpinCount.x) * m_fSpinDistance * m_fBOOLSpin.x);
			break;
		}

		SpinPos += m_Move;
	}
	if (m_CubeType != CUBETYPE_EXPLOSION)
	{
		m_pos += m_Move;
	}

	SetPos(m_pos);

	CollisionShadow();

	CObjmeshCube::Update();

	if (m_CubeType == CUBETYPE_EXPLOSION)
	{
		if (m_nExplosionIdx == 0)
		{
			if (m_nExplosionCount > 0)
			{
				m_nExplosionCount--;
			}
			else
			{
				m_nExplosionNum = 0;
				UninitExplosion();
			}
		}
	}
	else
	{
		if (m_nLife != -1 && m_nLife > 0)
		{
			m_nLife--;
		}
		else if (m_nLife == 0)
		{
			Uninit();
		}
	}

	if (CollisionBlock() == true)
	{
		for (int nCntX = -1; nCntX <= 1; nCntX += 2)
		{
			for (int nCntZ = -1; nCntZ <= 1; nCntZ += 2)
			{
				CCubeEffect* pCEffect = CCubeEffect::Create();
				pCEffect->SetPos(D3DXVECTOR3(GetPos().x + (10.0f * nCntX), GetPos().y, GetPos().z + (10.0f * nCntZ)));
				pCEffect->SetMove(D3DXVECTOR3((2.0f * nCntX), 15.0f, (2.0f * nCntZ)));
				pCEffect->SetSize(D3DXVECTOR3(5.0f, 5.0f, 5.0f));
				pCEffect->SetFall(true);
				pCEffect->SetColor(GetColor());
			}
		}

		Uninit();
	}
}

//====================================================================
//�`�揈��
//====================================================================
void CCubeDamage::Draw(void)
{
	CObjmeshCube::Draw();
}

//====================================================================
//��ސݒ菈��
//====================================================================
void CCubeDamage::SetCubeType(CUBETYPE Set)
{
	m_CubeType = Set;

	switch (m_CubeType)
	{
	case CUBETYPE_EXPLOSION:
		SetColor(D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.5f));
		m_nExplosionIdx = m_nExplosionNum;
		m_nExplosionNum++;
		break;
	case CUBETYPE_NORMAL:
		SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f));
		break;
	case CUBETYPE_BREAK:
		SetColor(D3DXCOLOR(0.8f, 0.3f, 0.0f, 0.5f));
		break;
	}
}

//====================================================================
//����
//====================================================================
void CCubeDamage::ExplosionSet(void)
{
	CCubeDamage* pCubeDamage = CCubeDamage::Create();
	pCubeDamage->SetUseSpin(true);
	pCubeDamage->SetSpinPos(m_pos);
	pCubeDamage->SetMove(m_Move);
	pCubeDamage->SetSpinCount(m_fSpinCount);
	pCubeDamage->SetSpinSpeedX(m_fSpinSpeed.x);
	pCubeDamage->SetSpinSpeedY(m_fSpinSpeed.y);
	pCubeDamage->SetSpinSpeedZ(m_fSpinSpeed.z);
	pCubeDamage->SetSpinDistance(m_fSpinDistance);
	pCubeDamage->SetCubeType(CUBETYPE_BREAK);
	pCubeDamage->SetLife(m_nLife);
	pCubeDamage->SetSpinDisMove(m_fSpinDisMove);
	pCubeDamage->SetSize(GetSize());
	pCubeDamage->SetDamage(m_fDamage);
}

//====================================================================
//�����L���[�u�̋N��
//====================================================================
void CCubeDamage::UninitExplosion(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//�I�u�W�F�N�g���擾
		CObject* pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			CObject* pObjNext = pObj->GetNext();

			CObject::TYPE type = pObj->GetType();			//��ނ��擾

			if (type == TYPE_CUBEDAMEGE)
			{//��ނ��u���b�N�̎�
				CCubeDamage* pBlock = (CCubeDamage*)pObj;

				if (pBlock->GetCubeType() == CUBETYPE_EXPLOSION)
				{
					pBlock->Uninit();
				}
			}

			pObj = pObjNext;
		}
	}
}

//====================================================================
//�u���b�N�̓����蔻��
//====================================================================
bool CCubeDamage::CollisionDamageBlock(D3DXVECTOR3 pPos, D3DXVECTOR3 Size, float *Damage)
{
	D3DXVECTOR3 MyPos = GetPos();
	D3DXVECTOR3 MySize = GetSize();

	//��`�͈͓̔����ǂ����̔���
	if (MyPos.x + MySize.x >= pPos.x - Size.x &&
		MyPos.x - MySize.x <= pPos.x + Size.x &&
		MyPos.z + MySize.z >= pPos.z - Size.z &&
		MyPos.z - MySize.z <= pPos.z + Size.z &&
		MyPos.y + MySize.y >= pPos.y &&
		MyPos.y - MySize.y <= pPos.y + Size.y)
	{
		*Damage = m_fDamage;

		if (m_CubeType == CUBETYPE_BREAK)
		{
			Uninit();
		}

		return true;
	}

	return false;
}

//====================================================================
//�I�u�W�F�N�g�Ƃ̓����蔻�菈��
//====================================================================
bool CCubeDamage::CollisionShadow(void)
{
	float BlockPosY = -10000.0f;
	bool bShadow = false;;

	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//�I�u�W�F�N�g���擾
		CObject* pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			CObject* pObjNext = pObj->GetNext();

			CObject::TYPE type = pObj->GetType();			//��ނ��擾

			if (type == TYPE_CUBEBLOCK)
			{//��ނ��u���b�N�̎�
				CCubeBlock* pBlock = (CCubeBlock*)pObj;

				D3DXVECTOR3 MyPos = GetPos();
				D3DXVECTOR3 MySize = GetSize();
				D3DXVECTOR3 BlockPos = pBlock->GetPos();
				D3DXVECTOR3 BlockSize = pBlock->GetSize();
				D3DXVECTOR3 BlockMove = pBlock->GetMove();

				if (BlockPos.y + BlockSize.y > BlockPosY)
				{
					if (BlockPos.x + BlockSize.x > MyPos.x &&
						BlockPos.x - BlockSize.x < MyPos.x &&
						BlockPos.z + BlockSize.z > MyPos.z &&
						BlockPos.z - BlockSize.z < MyPos.z &&
						BlockPos.y - BlockSize.y < MyPos.y)
					{
						float ColorA = (MyPos.y - BlockPos.y + BlockSize.y) * 0.002f;
						m_pShadow->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f - ColorA));

						m_pShadow->SetPos(D3DXVECTOR3(
							MyPos.x,
							BlockPos.y + BlockSize.y + BlockMove.y,
							MyPos.z));
						m_pShadow->SetWight(MySize.x * 2.0f);
						m_pShadow->SetHeight(MySize.z * 2.0f);

						BlockPosY = BlockPos.y + BlockSize.y;
						bShadow = true;
					}
				}
			}

			pObj = pObjNext;
		}
	}

	if (bShadow == false)
	{
		m_pShadow->SetWight(0.0f);
		m_pShadow->SetHeight(0.0f);
	}

	return false;
}

//====================================================================
//�L���[�u�u���b�N�Ƃ̓����蔻�菈��
//====================================================================
bool CCubeDamage::CollisionBlock(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//�I�u�W�F�N�g���擾
		CObject* pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			CObject* pObjNext = pObj->GetNext();

			CObject::TYPE type = pObj->GetType();			//��ނ��擾

			if (type == TYPE_CUBEBLOCK)
			{//��ނ��u���b�N�̎�

				D3DXVECTOR3 MyPos = m_pos;
				D3DXVECTOR3 MyPosOld = m_posOld;
				D3DXVECTOR3 MySize = GetSize();
				D3DXVECTOR3 pPos = pObj->GetPos();
				D3DXVECTOR3 Size = pObj->GetSize();

				if (MyPos.y < pPos.y &&
					MyPosOld.y >= pPos.y &&
					MyPos.z + MySize.z > pPos.z - Size.z &&
					MyPos.z - MySize.z < pPos.z + Size.z &&
					MyPos.x + MySize.x > pPos.x - Size.x &&
					MyPos.x - MySize.x < pPos.x + Size.x
					)
				{
					return true;
				}
			}

			pObj = pObjNext;
		}
	}

	return false;
}