//===================================
//
// �p�[�e�B�N��2D�w�b�_�[[Particle2D.h]
// Author ��������
//
//===================================
#ifndef _PARTICLE2D_H_
#define _PARTICLE2D_H_

#include "effect2D.h"

//-----------------------------------
// �N���X��`(CParticle2D)
//-----------------------------------
class CParticle2D
{
public:			// �N�ł��A�N�Z�X�o����

	CParticle2D();							// �R���X�g���N�^
	~CParticle2D();							// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	// �ÓI�����o�֐�
	static void Create(const D3DXVECTOR3& pos, const CEffect2D::TYPE type);			// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void InitBoost(const D3DXVECTOR3& pos, const CEffect2D::TYPE type);				// �u�[�X�g�̏�����
};

#endif