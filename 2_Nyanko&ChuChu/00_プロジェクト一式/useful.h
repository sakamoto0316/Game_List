//============================================
//
// �֗��w�b�_�[[useful.h]
// Author�F��������
//
//============================================
#ifndef _USEFUL_H_				//���̃}�N����`������Ă��Ȃ�������
#define _USEFUL_H_				//2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "main.h"

//--------------------------------------------
// ���O���
//--------------------------------------------
namespace useful
{
	void RotNormalize(float *pRot);													// �����̐��K��
	void Gravity(float *fGravity, float* fPosY, const float fAdd);					// �d�͏���
	void RotCorrect(const float fDest, float *pRot, const float fCorrect);			// �����̕␳����(�z�[�~���O����)
	void Correct(const float fDest, float *pValue, const float fCorrect);			// �l�̕␳����
	void ColReverse(float *pData);													// 1.0f��0.0f�𔽓]���鏈��
	bool CircleCollisionXY(const D3DXVECTOR3& pos0, const D3DXVECTOR3& pos1, const float fRadius0, const float fRadius1);		// �~�̓����蔻��(XY����)
	bool CircleCollisionXZ(const D3DXVECTOR3& pos0, const D3DXVECTOR3& pos1, const float fRadius0, const float fRadius1);		// �~�̓����蔻��(XZ����)
	bool CircleCollisionYZ(const D3DXVECTOR3& pos0, const D3DXVECTOR3& pos1, const float fRadius0, const float fRadius1);		// �~�̓����蔻��(YZ����)
	float LineOuterProductXZ(const D3DXVECTOR3& posLeft, const D3DXVECTOR3& posRight, const D3DXVECTOR3& pos);					// �O�ς̍��E���f����(XZ����)
	float LineOuterProductXY(const D3DXVECTOR3& posUp, const D3DXVECTOR3& posDown, const D3DXVECTOR3& pos);						// �O�ς̍��E���f����(XY����)
	float LineOuterProductYZ(const D3DXVECTOR3& posUp, const D3DXVECTOR3& posDown, const D3DXVECTOR3& pos);						// �O�ς̍��E���f����(YZ����)
	void NormalizeVector(D3DXVECTOR3& nor, const D3DXVECTOR3& posRight, const D3DXVECTOR3& posLeft, const D3DXVECTOR3& pos);	// �@���̌v�Z(���K��)
	float InnerProduct(const D3DXVECTOR3& VecMove, const D3DXVECTOR3& VecNor);		// ���ς̔��菈��
	bool CollisionOuterProductXZ(const D3DXVECTOR3& Targetpos, const D3DXVECTOR3& TargetposOld, const D3DXVECTOR3 posRight, const D3DXVECTOR3 posLeft, D3DXVECTOR3& cross);		// �O�ς̓����蔻�菈��(XZ����)
	bool CollisionOuterProductXY(const D3DXVECTOR3& Targetpos, const D3DXVECTOR3& TargetposOld, const D3DXVECTOR3 posRight, const D3DXVECTOR3 posLeft, D3DXVECTOR3& cross);		// �O�ς̓����蔻�菈��(XY����)
	bool RectangleCollisionXY(const D3DXVECTOR3& pos0, const D3DXVECTOR3& pos1, const D3DXVECTOR3& VtxMax0, const D3DXVECTOR3& VtxMax1, const D3DXVECTOR3& VtxMin0, const D3DXVECTOR3& VtxMin1);		// XY���W�̋�`�̓����蔻��
	bool RectangleCollisionXZ(const D3DXVECTOR3& pos0, const D3DXVECTOR3& pos1, const D3DXVECTOR3& VtxMax0, const D3DXVECTOR3& VtxMax1, const D3DXVECTOR3& VtxMin0, const D3DXVECTOR3& VtxMin1);		// XZ���W�̋�`�̓����蔻��
	bool RectangleCollisionYZ(const D3DXVECTOR3& pos0, const D3DXVECTOR3& pos1, const D3DXVECTOR3& VtxMax0, const D3DXVECTOR3& VtxMax1, const D3DXVECTOR3& VtxMin0, const D3DXVECTOR3& VtxMin1);		// YZ���W�̋�`�̓����蔻��
	bool CylinderCollision(D3DXVECTOR3* TargetPos, const D3DXVECTOR3& ObjectPos, const float fObjectRadius);					// �~���̓����蔻��
	bool CylinderInner(const D3DXVECTOR3& TargetPos, const D3DXVECTOR3& ObjectPos, const float fObjectRadius);					// �~���̓������菈��
	void DecimalCalculation(const int nDigit, const int nValue, int* aAnswer);		// 10�i���ւ̕ϊ�����
	bool FrameCorrect(const float fDest, float *fTarget, const float fCorrect);		// �ϓ��Ȑ��l�̕␳
}

#endif