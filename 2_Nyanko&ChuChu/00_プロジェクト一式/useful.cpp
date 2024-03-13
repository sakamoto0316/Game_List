//============================================
//
// �֗�����[useful.cpp]
// Author�F��������
//
//============================================
//********************************************
// �}�N����`
//********************************************
#include "useful.h"
#include "manager.h"

//======================
// �����̐��K��
//======================
void useful::RotNormalize(float *pRot)
{
	if (*pRot > D3DX_PI)
	{ // ������3.14f�𒴂��Ă����ꍇ

		// ������␳����
		*pRot -= D3DX_PI * 2;
	}
	else if (*pRot < -D3DX_PI)
	{ // ������-3.14f�𒴂��Ă����ꍇ

		// ������␳����
		*pRot += D3DX_PI * 2;
	}
}

//======================
// �d�͏���
//======================
void useful::Gravity(float *fGravity, float* fPosY, const float fAdd)
{
	// �d�͂����Z����
	*fGravity -= fAdd;

	// �d�͂�������
	*fPosY += *fGravity;
}

//======================
// �z�[�~���O����
//======================
void useful::RotCorrect(const float fDest, float *pRot, const float fCorrect)
{
	// ���[�J���ϐ��錾
	float fRotDiff;			// �����̍���

	// �����̍��������߂�
	fRotDiff = fDest - *pRot;

	// �����̐��K��
	RotNormalize(&fRotDiff);

	// ������␳����
	*pRot += fRotDiff * fCorrect;

	// �����̐��K��
	RotNormalize(pRot);
}

//======================
// �l�̕␳����
//======================
void useful::Correct(const float fDest, float *pValue, const float fCorrect)
{
	// ���[�J���ϐ��錾
	float fDiff;			// �l�̍���

	// �l�̍��������߂�
	fDiff = fDest - *pValue;

	// �l��␳����
	*pValue += fDiff * fCorrect;
}

//======================
// 1.0f��0.0f�𔽓]���鏈��
//======================
void useful::ColReverse(float *pData)
{
	if (*pData >= 1.0f)
	{ // �f�[�^�� 0.0f �ȉ��̏ꍇ

		// �f�[�^�� 1.0f �ɂ���
		*pData = 0.0f;
	}
	else if (*pData <= 0.0f)
	{ // �f�[�^�� 1.0f �ȏ�̏ꍇ

		// �f�[�^�� 0.0f �ɂ���
		*pData = 1.0f;
	}
}

//======================
// �~�̓����蔻��(XY����)
//======================
bool useful::CircleCollisionXY(const D3DXVECTOR3& pos0, const D3DXVECTOR3& pos1, const float fRadius0, const float fRadius1)
{
	// ���[�J���ϐ��錾
	float fLength;

	// �~�͈̔͂��Z�o
	fLength = (pos1.x - pos0.x) * (pos1.x - pos0.x) + (pos1.y - pos0.y) * (pos1.y - pos0.y);

	if (fLength <= (fRadius0 + fRadius1) * (fRadius0 + fRadius1))
	{ // �I�u�W�F�N�g�����������ꍇ

		// true ��Ԃ�
		return true;
	}
	else
	{ // �I�u�W�F�N�g���������Ă��Ȃ��ꍇ

		// false ��Ԃ�
		return false;
	}
}

//======================
// �~�̓����蔻��(XZ����)
//======================
bool useful::CircleCollisionXZ(const D3DXVECTOR3& pos0, const D3DXVECTOR3& pos1, const float fRadius0, const float fRadius1)
{
	// ���[�J���ϐ��錾
	float fLength;

	// �~�͈̔͂��Z�o
	fLength = (pos1.x - pos0.x) * (pos1.x - pos0.x) + (pos1.z - pos0.z) * (pos1.z - pos0.z);

	if (fLength <= (fRadius0 + fRadius1) * (fRadius0 + fRadius1))
	{ // �I�u�W�F�N�g�����������ꍇ

		// true ��Ԃ�
		return true;
	}
	else
	{ // �I�u�W�F�N�g���������Ă��Ȃ��ꍇ

		// false ��Ԃ�
		return false;
	}
}

//======================
// �~�̓����蔻��(YZ����)
//======================
bool useful::CircleCollisionYZ(const D3DXVECTOR3& pos0, const D3DXVECTOR3& pos1, const float fRadius0, const float fRadius1)
{
	// ���[�J���ϐ��錾
	float fLength;

	// �~�͈̔͂��Z�o
	fLength = (pos1.y - pos0.y) * (pos1.y - pos0.y) + (pos1.z - pos0.z) * (pos1.z - pos0.z);

	if (fLength <= (fRadius0 + fRadius1) * (fRadius0 + fRadius1))
	{ // �I�u�W�F�N�g�����������ꍇ

		// true ��Ԃ�
		return true;
	}
	else
	{ // �I�u�W�F�N�g���������Ă��Ȃ��ꍇ

		// false ��Ԃ�
		return false;
	}
}

//======================
// �O�ς̍��E���f����
//======================
float useful::LineOuterProductXZ(const D3DXVECTOR3& posLeft, const D3DXVECTOR3& posRight, const D3DXVECTOR3& pos)
{
	// �ϐ���錾
	D3DXVECTOR3 vecLine;	// ���E���x�N�g��
	D3DXVECTOR3 vecToPos;	// ���[�ƈʒu�̃x�N�g��

	// ���E���x�N�g�������߂�
	vecLine = posRight - posLeft;

	// ���[�ƈʒu�̃x�N�g�������߂�
	vecToPos = pos - posLeft;

	// �O�ς̌v�Z���ʂ�Ԃ�
	return (vecLine.z * vecToPos.x) - (vecLine.x * vecToPos.z);
}

//======================
// �O�ς̍��E���f����(XY����)
//======================
float useful::LineOuterProductXY(const D3DXVECTOR3& posUp, const D3DXVECTOR3& posDown, const D3DXVECTOR3& pos)
{
	// �ϐ���錾
	D3DXVECTOR3 vecLine;	// ���E���x�N�g��
	D3DXVECTOR3 vecToPos;	// ���[�ƈʒu�̃x�N�g��

	// ���E���x�N�g�������߂�
	vecLine = posDown - posUp;

	// ���[�ƈʒu�̃x�N�g�������߂�
	vecToPos = pos - posUp;

	// �O�ς̌v�Z���ʂ�Ԃ�
	return (vecLine.x * vecToPos.y) - (vecLine.y * vecToPos.x);
}

//======================
// �O�ς̍��E���f����(YZ����)
//======================
float useful::LineOuterProductYZ(const D3DXVECTOR3& posUp, const D3DXVECTOR3& posDown, const D3DXVECTOR3& pos)
{
	// �ϐ���錾
	D3DXVECTOR3 vecLine;	// ���E���x�N�g��
	D3DXVECTOR3 vecToPos;	// ���[�ƈʒu�̃x�N�g��

	// ���E���x�N�g�������߂�
	vecLine = posDown - posUp;

	// ���[�ƈʒu�̃x�N�g�������߂�
	vecToPos = pos - posUp;

	// �O�ς̌v�Z���ʂ�Ԃ�
	return (vecLine.y * vecToPos.z) - (vecLine.z * vecToPos.y);
}

//======================
// �@���̌v�Z(���K��)
//======================
void useful::NormalizeVector(D3DXVECTOR3& nor, const D3DXVECTOR3& posRight, const D3DXVECTOR3& posLeft,const D3DXVECTOR3& pos)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 vec1;			// �x�N�g��1
	D3DXVECTOR3 vec2;			// �x�N�g��2

	// �x�N�g�����v�Z����
	vec1 = posLeft - pos;
	vec2 = posRight - pos;

	// �@�����Z�o����
	nor = D3DXVECTOR3((vec1.y * vec2.z) - (vec1.z * vec2.y), (vec1.z * vec2.x) - (vec1.x * vec2.z), (vec1.x * vec2.y) - (vec1.y * vec2.x));

	// �@���𐳋K������
	D3DXVec3Normalize(&nor, &nor);
}

//======================
// ���ς̔��菈��
//======================
float useful::InnerProduct(const D3DXVECTOR3& VecMove, const D3DXVECTOR3& VecNor)
{
	// ���[�J���ϐ��錾
	float fDot = 0.0f;			// ����

	// ���ς̒l���Z�o����
	fDot = (VecMove.x * VecNor.x) + (VecMove.y * VecNor.y) + (VecMove.z * VecNor.z);

	// ���ς̒l��Ԃ�
	return fDot;
}

//======================
// �O�ς̓����蔻�菈��(XZ����)
//======================
bool useful::CollisionOuterProductXZ(const D3DXVECTOR3& Targetpos, const D3DXVECTOR3& TargetposOld, const D3DXVECTOR3 posRight, const D3DXVECTOR3 posLeft, D3DXVECTOR3& cross)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 vecMove, vecLine, vecTopos, posCross;	// �O�ς̕ϐ�
	float fRate;										// �����̕ϐ�

	// �e�̋O�Ղ𑪂�
	vecMove.x = (Targetpos.x - TargetposOld.x);
	vecMove.y = (Targetpos.y - TargetposOld.y);
	vecMove.z = (Targetpos.z - TargetposOld.z);

	// �ǂ̋��E���𑪂�
	vecLine.x = (posRight.x - posLeft.x);
	vecLine.y = (posRight.y - posLeft.y);
	vecLine.z = (posRight.z - posLeft.z);

	// �ǂ̎n�_����e�̈ʒu�̋����𑪂�
	vecTopos.x = (Targetpos.x - posLeft.x);
	vecTopos.y = (Targetpos.y - posLeft.y);
	vecTopos.z = (Targetpos.z - posLeft.z);

	// ���������߂�
	fRate = ((vecTopos.z * vecMove.x) - (vecTopos.x * vecMove.z)) / ((vecLine.z * vecMove.x) - (vecLine.x * vecMove.z));

	// ��_�����߂�
	posCross.x = vecLine.x * fRate + posLeft.x;
	posCross.y = vecLine.y * fRate + posLeft.y;
	posCross.z = vecLine.z * fRate + posLeft.z;

	if ((vecLine.z * vecTopos.x) - (vecLine.x * vecTopos.z) >= 0.0f)
	{ // ���E���𒴂����ꍇ

		if (fRate >= 0.0f && fRate <= 1.0f)
		{ // ������0.0f�`1.0f�̊Ԃ�����(���E���𒴂���)�ꍇ

			// ��_��������
			cross = posCross;

			// ���� ��Ԃ�
			return true;
		}
		else
		{ // ��L�ȊO

			// false ��Ԃ�
			return false;
		}
	}
	else
	{ // ��L�ȊO

		// false ��Ԃ�
		return false;
	}
}

//======================
// �O�ς̓����蔻�菈��(XY����)
//======================
bool useful::CollisionOuterProductXY(const D3DXVECTOR3& Targetpos, const D3DXVECTOR3& TargetposOld, const D3DXVECTOR3 posRight, const D3DXVECTOR3 posLeft, D3DXVECTOR3& cross)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 vecMove, vecLine, vecTopos, posCross;	// �O�ς̕ϐ�
	float fRate;										// �����̕ϐ�

	// �e�̋O�Ղ𑪂�
	vecMove.x = (Targetpos.x - TargetposOld.x);
	vecMove.y = (Targetpos.y - TargetposOld.y);
	vecMove.z = (Targetpos.z - TargetposOld.z);

	// �ǂ̋��E���𑪂�
	vecLine.x = (posRight.x - posLeft.x);
	vecLine.y = (posRight.y - posLeft.y);
	vecLine.z = (posRight.z - posLeft.z);

	// �ǂ̎n�_����e�̈ʒu�̋����𑪂�
	vecTopos.x = (Targetpos.x - posLeft.x);
	vecTopos.y = (Targetpos.y - posLeft.y);
	vecTopos.z = (Targetpos.z - posLeft.z);

	// ���������߂�
	fRate = ((vecTopos.x * vecMove.y) - (vecTopos.y * vecMove.x)) / ((vecLine.x * vecMove.y) - (vecLine.y * vecMove.x));

	// ��_�����߂�
	posCross.x = vecLine.x * fRate - posLeft.x;
	posCross.y = vecLine.y * fRate - posLeft.y;
	posCross.z = vecLine.z * fRate - posLeft.z;

	if ((vecLine.x * vecTopos.y) - (vecLine.y * vecTopos.x) < 0.0f)
	{ // ���E���𒴂����ꍇ

		if (fRate >= 0.0f && fRate <= 1.0f)
		{ // ������0.0f�`1.0f�̊Ԃ�����(���E���𒴂���)�ꍇ

			// ��_��������
			cross = posCross;

			// ���� ��Ԃ�
			return true;
		}
		else
		{ // ��L�ȊO

			// false ��Ԃ�
			return false;
		}
	}
	else
	{ // ��L�ȊO

		// false ��Ԃ�
		return false;
	}
}

//======================
// ��`�̓����蔻��
//======================
bool useful::RectangleCollisionXY(const D3DXVECTOR3& pos0, const D3DXVECTOR3& pos1, const D3DXVECTOR3& VtxMax0, const D3DXVECTOR3& VtxMax1, const D3DXVECTOR3& VtxMin0, const D3DXVECTOR3& VtxMin1)
{
	if (pos0.x + VtxMax0.x >= pos1.x + VtxMin1.x&&
		pos0.x + VtxMin0.x <= pos1.x + VtxMax1.x&&
		pos0.y + VtxMax0.y >= pos1.y + VtxMin1.y&&
		pos0.y + VtxMin0.y <= pos1.y + VtxMax1.y)
	{ // �����蔻��ɓ������Ă����ꍇ

		// true ��Ԃ�
		return true;
	}
	else
	{ // �����蔻��ɓ������Ă��Ȃ��ꍇ

		// false ��Ԃ�
		return false;
	}
}

//======================
// XZ���W�̋�`�̓����蔻��
//======================
bool useful::RectangleCollisionXZ(const D3DXVECTOR3& pos0, const D3DXVECTOR3& pos1, const D3DXVECTOR3& VtxMax0, const D3DXVECTOR3& VtxMax1, const D3DXVECTOR3& VtxMin0, const D3DXVECTOR3& VtxMin1)
{
	if (pos0.x + VtxMax0.x >= pos1.x + VtxMin1.x &&
		pos0.x + VtxMin0.x <= pos1.x + VtxMax1.x &&
		pos0.z + VtxMax0.z >= pos1.z + VtxMin1.z &&
		pos0.z + VtxMin0.z <= pos1.z + VtxMax1.z)
	{ // �����蔻��ɓ������Ă����ꍇ

		// true ��Ԃ�
		return true;
	}
	else
	{ // �����蔻��ɓ������Ă��Ȃ��ꍇ

		// false ��Ԃ�
		return false;
	}
}

//======================
// YZ���W�̋�`�̓����蔻��
//======================
bool useful::RectangleCollisionYZ(const D3DXVECTOR3& pos0, const D3DXVECTOR3& pos1, const D3DXVECTOR3& VtxMax0, const D3DXVECTOR3& VtxMax1, const D3DXVECTOR3& VtxMin0, const D3DXVECTOR3& VtxMin1)
{
	if (pos0.y + VtxMax0.y >= pos1.y + VtxMin1.y &&
		pos0.y + VtxMin0.y <= pos1.y + VtxMax1.y &&
		pos0.z + VtxMax0.z >= pos1.z + VtxMin1.z &&
		pos0.z + VtxMin0.z <= pos1.z + VtxMax1.z)
	{ // �����蔻��ɓ������Ă����ꍇ

		// true ��Ԃ�
		return true;
	}
	else
	{ // �����蔻��ɓ������Ă��Ȃ��ꍇ

		// false ��Ԃ�
		return false;
	}
}

//======================
// �~���̓����蔻��
//======================
bool useful::CylinderCollision(D3DXVECTOR3* TargetPos, const D3DXVECTOR3& ObjectPos, const float fObjectRadius)
{
	// ���[�J���ϐ��錾
	float fLength = 0.0f;			// ����
	float fAngle = 0.0f;			// ����

	// ���������
	fAngle = atan2f((TargetPos->x - ObjectPos.x), (TargetPos->z - ObjectPos.z));

	// ���a�𑪂�
	fLength = sqrtf((TargetPos->x - ObjectPos.x) * (TargetPos->x - ObjectPos.x) + (TargetPos->z - ObjectPos.z) * (TargetPos->z - ObjectPos.z));

	if (fLength <= fObjectRadius)
	{ // �ΏۂƂ̋������I�u�W�F�N�g�̔��a�ȉ��̏ꍇ

		// �ʒu��ݒ肷��
		TargetPos->x = ObjectPos.x + sinf(fAngle) * fObjectRadius;
		TargetPos->z = ObjectPos.z + cosf(fAngle) * fObjectRadius;

		// true ��Ԃ�
		return true;
	}
	else
	{ // ��L�ȊO

		// false ��Ԃ�
		return false;
	}
}

//======================
// �~���̓������菈��
//======================
bool useful::CylinderInner(const D3DXVECTOR3& TargetPos, const D3DXVECTOR3& ObjectPos, const float fObjectRadius)
{
	// ���[�J���ϐ��錾
	float fLength = 0.0f;			// ����

	// ���a�𑪂�
	fLength = sqrtf((TargetPos.x - ObjectPos.x) * (TargetPos.x - ObjectPos.x) + (TargetPos.z - ObjectPos.z) * (TargetPos.z - ObjectPos.z));

	if (fLength <= fObjectRadius)
	{ // �ΏۂƂ̋������I�u�W�F�N�g�̔��a�ȉ��̏ꍇ

		// true ��Ԃ�
		return true;
	}
	else
	{ // ��L�ȊO

		// false ��Ԃ�
		return false;
	}
}

//======================
// 10�i���ւ̕ϊ�����
//======================
void useful::DecimalCalculation(const int nDigit, const int nValue, int* aAnswer)
{
	for (int nCnt = 0; nCnt < nDigit; nCnt++)
	{
		// �l���v�Z
		aAnswer[nCnt] = (nValue % (int)(pow(10, (nDigit - (nCnt)))) / (int)(pow(10, (nDigit - (nCnt + 1)))));
	}
}

//======================
// �ϓ��Ȑ��l�̕␳
//======================
bool useful::FrameCorrect(const float fDest, float *fTarget, const float fCorrect)
{
	if (*fTarget > fDest)
	{ // �T�C�Y���ڕW���߂������ꍇ

		// �T�C�Y�����Z����
		*fTarget -= fCorrect;

		if (*fTarget <= fDest)
		{ // �ڕW�̃T�C�Y�ȉ��ɂȂ����ꍇ

			// �T�C�Y��␳����
			*fTarget = fDest;

			// true ��Ԃ�
			return true;
		}
		else
		{ // ��L�ȊO

			// false ��Ԃ�
			return false;
		}
	}

	if (*fTarget < fDest)
	{ // �T�C�Y���ڕW�����������ꍇ

		// �T�C�Y�����Z����
		*fTarget += fCorrect;

		if (*fTarget >= fDest)
		{ // �ڕW�̃T�C�Y�ȏ�ɂȂ����ꍇ

			// �T�C�Y��␳����
			*fTarget = fDest;

			// true ��Ԃ�
			return true;
		}
		else
		{ // ��L�ȊO

			// false ��Ԃ�
			return false;
		}
	}

	// false ��Ԃ�
	return false;
}