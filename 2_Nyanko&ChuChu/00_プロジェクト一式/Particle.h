//===================================
//
// �p�[�e�B�N���w�b�_�[[Particle.h]
// Author ��������
//
//===================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "Effect.h"

//-----------------------------------
// �N���X��`(CParticle)
//-----------------------------------
class CParticle
{
public:			// �N�ł��A�N�Z�X�o����

	// �p�[�e�B�N���̎��
	enum TYPE
	{
		TYPE_FIRE = 0,		// ��
		TYPE_DUST,			// ��
		TYPE_ITEMGET,		// �A�C�e���Q�b�g
		TYPE_ENEMYDEATH,	// �G�̎��S
		TYPE_SLIME,			// �X���C����
		TYPE_RESURRECTION,	// ����
		TYPE_HONEY,			// �n�`�~�c��
		TYPE_MAX
	};

	CParticle();							// �R���X�g���N�^
	~CParticle();							// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	// �ÓI�����o�֐�
	static void Create(const D3DXVECTOR3& pos, const CParticle::TYPE type);		// ��������

private:		// ���������A�N�Z�X�ł���

	// �p�[�e�B�N����������
	void InitFire(const D3DXVECTOR3& pos);			// ���n�̐���
	void InitDust(const D3DXVECTOR3& pos);			// ���n���̐���
	void InitItemGet(const D3DXVECTOR3& pos);		// �A�C�e���Q�b�g�̐���
	void InitEnemyDeath(const D3DXVECTOR3& pos);	// �G�̎��S�̐���
	void InitSlime(const D3DXVECTOR3& pos);			// �X���C�����̃p�[�e�B�N������
	void InitResurrection(const D3DXVECTOR3& pos);	// �����̃p�[�e�B�N������
	void InitHoney(const D3DXVECTOR3& pos);			// �n�`�~�c���̃p�[�e�B�N������

};

#endif