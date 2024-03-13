//============================================
//
//	�L���[�u�u���b�N [CubeBlock.cpp]
//	Author:sakamoto kai
//
//============================================
#include "CubeBlock.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "texture.h"

#define WAIGHT_SIZE (11)		//���̒��_��
#define HEIGHT_SIZE (11)		//�c�̒��_��
#define WAIGHT_CENTER (0.5f)	//���̌��_(0.0f�`1.0f)
#define HEIGHT_CENTER (0.5f)	//�c�̌��_(0.0f�`1.0f)
#define FIELD_SIZE (200.0f)		//���ꖇ�̑傫��

//====================================================================
//�R���X�g���N�^
//====================================================================
CCubeBlock::CCubeBlock(int nPriority) :CObjmeshCube(nPriority)
{

}

//====================================================================
//�f�X�g���N�^
//====================================================================
CCubeBlock::~CCubeBlock()
{

}

//====================================================================
//��������
//====================================================================
CCubeBlock* CCubeBlock::Create(void)
{
	CCubeBlock* pObject3D = NULL;

	if (pObject3D == NULL)
	{
		//�I�u�W�F�N�g3D�̐���
		pObject3D = new CCubeBlock();
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
HRESULT CCubeBlock::Init(void)
{	
	CObjmeshCube::Init();

	SetTexture("data\\TEXTURE\\Test.jpg");
	SetColor(D3DXCOLOR(0.5f, 0.5f, 0.0f, 0.5f));

	SetType(TYPE_CUBEBLOCK);

	return S_OK;
}

//====================================================================
//�I������
//====================================================================
void CCubeBlock::Uninit(void)
{
	CObjmeshCube::Uninit();

	SetDeathFlag(true);
}

//====================================================================
//�X�V����
//====================================================================
void CCubeBlock::Update(void)
{
	CObjmeshCube::Update();
}

//====================================================================
//�`�揈��
//====================================================================
void CCubeBlock::Draw(void)
{
	CObjmeshCube::Draw();
}

//====================================================================
//�u���b�N�̓����蔻��
//====================================================================
bool CCubeBlock::CollisionBlock(D3DXVECTOR3* pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3* pMove, D3DXVECTOR3* pObjMove, D3DXVECTOR3 Size, bool* bJump, COLLISION XYZ)
{
	D3DXVECTOR3 MyPos = GetPos();
	D3DXVECTOR3 MyPosOld = GetPosOld();
	D3DXVECTOR3 MySize = GetSize();
	D3DXVECTOR3 MyMove = GetMove();

	switch (XYZ)
	{
	case CObject::COLLISION_X:	// X��

		//�{����|�̖�
		if (MyPos.x + MySize.x > pPos->x - Size.x &&
			(MyPosOld.x + MySize.x <= pPos->x - Size.x ||
				MyPos.x + MySize.x <= pPosOld.x - Size.x ||
				(MyPos.x + MySize.x >= pPosOld.x - Size.x &&
					MyPosOld.x + MySize.x <= pPosOld.x - Size.x &&
					MyPosOld.x + MySize.x >= pPos->x - Size.x)) &&
			MyPos.z + MySize.z > pPos->z - Size.z &&
			MyPos.z - MySize.z < pPos->z + Size.z &&
			MyPos.y + MySize.y > pPos->y &&
			MyPos.y - MySize.y < pPos->y + Size.y
			)
		{
			if (MyMove.x >= 0.0f)
			{
				pPos->x = pPosOld.x - Size.x + Size.x + MyMove.x;
			}
			else
			{
				pPos->x = MyPos.x + MySize.x + Size.x + MyMove.x;
			}
			pMove->x = 0.0f;
		}

		//�|����{�̖�
		if (MyPos.x - MySize.x < pPos->x + Size.x &&
			(MyPosOld.x - MySize.x >= pPos->x + Size.x ||
				MyPos.x - MySize.x >= pPosOld.x + Size.x ||
				(MyPos.x - MySize.x <= pPosOld.x + Size.x &&
					MyPosOld.x - MySize.x >= pPosOld.x + Size.x &&
					MyPosOld.x - MySize.x <= pPos->x + Size.x)) &&
			MyPos.z + MySize.z > pPos->z - Size.z &&
			MyPos.z - MySize.z < pPos->z + Size.z &&
			MyPos.y + MySize.y > pPos->y &&
			MyPos.y - MySize.y < pPos->y + Size.y
			)
		{
			if (MyMove.x <= 0.0f)
			{
				pPos->x = pPosOld.x + Size.x - Size.x + MyMove.x;
			}
			else
			{
				pPos->x = MyPos.x - MySize.x - Size.x + MyMove.x;
			}
			pMove->x = 0.0f;
		}

		break;
	case CObject::COLLISION_Y:

		//�{����|�̖�
		if (MyPos.y + MySize.y > pPos->y &&
			(MyPosOld.y + MySize.y <= pPos->y ||
				MyPos.y + MySize.y <= pPosOld.y ||
				(MyPos.y + MySize.y >= pPosOld.y &&
					MyPosOld.y + MySize.y <= pPosOld.y &&
					MyPosOld.y + MySize.y >= pPos->y)) &&
			MyPos.z + MySize.z > pPos->z - Size.z &&
			MyPos.z - MySize.z < pPos->z + Size.z &&
			MyPos.x + MySize.x > pPos->x - Size.x &&
			MyPos.x - MySize.x < pPos->x + Size.x
			)
		{
			if (MyMove.y >= 0.0f)
			{
				pPos->y = pPosOld.y + MyMove.y;
			}
			else
			{
				pPos->y = MyPos.y + MySize.y + MyMove.y;
			}
			pMove->y = 0.0f;
			*bJump = false;
			pObjMove->x = MyMove.x;
			pObjMove->y = MyMove.y;
			pObjMove->z = MyMove.z;
		}

		//�|����{�̖�
		if (MyPos.y - MySize.y < pPos->y + Size.y &&
			(MyPosOld.y - MySize.y >= pPos->y + Size.y ||
				MyPos.y - MySize.y >= pPosOld.y + Size.y ||
				(MyPos.y - MySize.y <= pPosOld.y + Size.y &&
					MyPosOld.y - MySize.y >= pPosOld.y + Size.y &&
					MyPosOld.y - MySize.y <= pPos->y + Size.y)) &&
			MyPos.z + MySize.z > pPos->z - Size.z &&
			MyPos.z - MySize.z < pPos->z + Size.z &&
			MyPos.x + MySize.x > pPos->x - Size.x &&
			MyPos.x - MySize.x < pPos->x + Size.x
			)
		{
			pPos->y = MyPos.y - MySize.y - Size.y + MyMove.y;
			pMove->y = MyMove.y;
		}

		break;
	case CObject::COLLISION_Z:

		//�{����|�̖�
		if (MyPos.z + MySize.z > pPos->z - Size.z &&
			(MyPosOld.z + MySize.z <= pPos->z - Size.z ||
				MyPos.z + MySize.z <= pPosOld.z - Size.z ||
				(MyPos.z + MySize.z >= pPosOld.z - Size.z &&
					MyPosOld.z + MySize.z <= pPosOld.z - Size.z &&
					MyPosOld.z + MySize.z >= pPos->z - Size.z)) &&
			MyPos.x + MySize.x > pPos->x - Size.x &&
			MyPos.x - MySize.x < pPos->x + Size.x &&
			MyPos.y + MySize.y > pPos->y &&
			MyPos.y - MySize.y < pPos->y + Size.y
			)
		{
			if (MyMove.z >= 0.0f)
			{
				pPos->z = pPosOld.z - Size.z + Size.z + MyMove.z;
			}
			else
			{
				pPos->z = MyPos.z + MySize.z + Size.z + MyMove.z;
			}
			pMove->z = 0.0f;
		}

		//�|����{�̖�
		if (MyPos.z - MySize.z < pPos->z + Size.z &&
			(MyPosOld.z - MySize.z >= pPos->z + Size.z ||
				MyPos.z - MySize.z >= pPosOld.z + Size.z ||
				(MyPos.z - MySize.z <= pPosOld.z + Size.z &&
					MyPosOld.z - MySize.z >= pPosOld.z + Size.z &&
					MyPosOld.z - MySize.z <= pPos->z + Size.z)) &&
			MyPos.x + MySize.x > pPos->x - Size.x &&
			MyPos.x - MySize.x < pPos->x + Size.x &&
			MyPos.y + MySize.y > pPos->y &&
			MyPos.y - MySize.y < pPos->y + Size.y
			)
		{
			if (MyMove.z <= 0.0f)
			{
				pPos->z = pPosOld.z + Size.z - Size.z + MyMove.z;
			}
			else
			{
				pPos->z = MyPos.z - MySize.z - Size.z + MyMove.z;
			}
			pMove->z = 0.0f;
		}

		break;
	}

	return false;
}

//====================================================================
//�u���b�N�̓����蔻��
//====================================================================
bool CCubeBlock::CollisionBlockUp(D3DXVECTOR3* pPos, D3DXVECTOR3 pPosOld, D3DXVECTOR3* pMove, D3DXVECTOR3* pObjMove, D3DXVECTOR3 Size, bool* bJump, COLLISION XYZ)
{
	D3DXVECTOR3 MyPos = GetPos();
	D3DXVECTOR3 MyPosOld = GetPosOld();
	D3DXVECTOR3 MySize = GetSize();
	D3DXVECTOR3 MyMove = GetMove();

	switch (XYZ)
	{
	case CObject::COLLISION_X:	// X��

		//�{����|�̖�
		if (MyPos.x + MySize.x > pPos->x - Size.x &&
			(MyPosOld.x + MySize.x <= pPos->x - Size.x ||
				MyPos.x + MySize.x <= pPosOld.x - Size.x ||
				(MyPos.x + MySize.x >= pPosOld.x - Size.x &&
					MyPosOld.x + MySize.x <= pPosOld.x - Size.x &&
					MyPosOld.x + MySize.x >= pPos->x - Size.x)) &&
			MyPos.z + MySize.z > pPos->z - Size.z &&
			MyPos.z - MySize.z < pPos->z + Size.z &&
			MyPos.y + MySize.y > pPos->y &&
			MyPos.y - MySize.y < pPos->y + Size.y
			)
		{
			if (MyMove.x >= 0.0f)
			{
				pPos->x = pPosOld.x - Size.x + Size.x + MyMove.x;
			}
			else
			{
				pPos->x = MyPos.x + MySize.x + Size.x + MyMove.x;
			}
			pMove->x = 0.0f;
		}

		//�|����{�̖�
		if (MyPos.x - MySize.x < pPos->x + Size.x &&
			(MyPosOld.x - MySize.x >= pPos->x + Size.x ||
				MyPos.x - MySize.x >= pPosOld.x + Size.x ||
				(MyPos.x - MySize.x <= pPosOld.x + Size.x &&
					MyPosOld.x - MySize.x >= pPosOld.x + Size.x &&
					MyPosOld.x - MySize.x <= pPos->x + Size.x)) &&
			MyPos.z + MySize.z > pPos->z - Size.z &&
			MyPos.z - MySize.z < pPos->z + Size.z &&
			MyPos.y + MySize.y > pPos->y &&
			MyPos.y - MySize.y < pPos->y + Size.y
			)
		{
			if (MyMove.x <= 0.0f)
			{
				pPos->x = pPosOld.x + Size.x - Size.x + MyMove.x;
			}
			else
			{
				pPos->x = MyPos.x - MySize.x - Size.x + MyMove.x;
			}
			pMove->x = 0.0f;
		}

		break;
	case CObject::COLLISION_Y:

		//�{����|�̖�
		if (MyPos.y + MySize.y > pPos->y &&
			(MyPosOld.y + MySize.y <= pPos->y ||
				MyPos.y + MySize.y <= pPosOld.y ||
				(MyPos.y + MySize.y >= pPosOld.y &&
					MyPosOld.y + MySize.y <= pPosOld.y &&
					MyPosOld.y + MySize.y >= pPos->y)) &&
			MyPos.z + MySize.z > pPos->z - Size.z &&
			MyPos.z - MySize.z < pPos->z + Size.z &&
			MyPos.x + MySize.x > pPos->x - Size.x &&
			MyPos.x - MySize.x < pPos->x + Size.x
			)
		{
			if (MyMove.y >= 0.0f)
			{
				pPos->y = pPosOld.y + MyMove.y;
			}
			else
			{
				pPos->y = MyPos.y + MySize.y + MyMove.y;
			}
			pMove->y = 0.0f;
			*bJump = false;
			pObjMove->x = MyMove.x;
			pObjMove->y = MyMove.y;
			pObjMove->z = MyMove.z;
		}

		break;
	case CObject::COLLISION_Z:

		//�{����|�̖�
		if (MyPos.z + MySize.z > pPos->z - Size.z &&
			(MyPosOld.z + MySize.z <= pPos->z - Size.z ||
				MyPos.z + MySize.z <= pPosOld.z - Size.z ||
				(MyPos.z + MySize.z >= pPosOld.z - Size.z &&
					MyPosOld.z + MySize.z <= pPosOld.z - Size.z &&
					MyPosOld.z + MySize.z >= pPos->z - Size.z)) &&
			MyPos.x + MySize.x > pPos->x - Size.x &&
			MyPos.x - MySize.x < pPos->x + Size.x &&
			MyPos.y + MySize.y > pPos->y &&
			MyPos.y - MySize.y < pPos->y + Size.y
			)
		{
			if (MyMove.z >= 0.0f)
			{
				pPos->z = pPosOld.z - Size.z + Size.z + MyMove.z;
			}
			else
			{
				pPos->z = MyPos.z + MySize.z + Size.z + MyMove.z;
			}
			pMove->z = 0.0f;
		}

		//�|����{�̖�
		if (MyPos.z - MySize.z < pPos->z + Size.z &&
			(MyPosOld.z - MySize.z >= pPos->z + Size.z ||
				MyPos.z - MySize.z >= pPosOld.z + Size.z ||
				(MyPos.z - MySize.z <= pPosOld.z + Size.z &&
					MyPosOld.z - MySize.z >= pPosOld.z + Size.z &&
					MyPosOld.z - MySize.z <= pPos->z + Size.z)) &&
			MyPos.x + MySize.x > pPos->x - Size.x &&
			MyPos.x - MySize.x < pPos->x + Size.x &&
			MyPos.y + MySize.y > pPos->y &&
			MyPos.y - MySize.y < pPos->y + Size.y
			)
		{
			if (MyMove.z <= 0.0f)
			{
				pPos->z = pPosOld.z + Size.z - Size.z + MyMove.z;
			}
			else
			{
				pPos->z = MyPos.z - MySize.z - Size.z + MyMove.z;
			}
			pMove->z = 0.0f;
		}

		break;
	}

	return false;
}