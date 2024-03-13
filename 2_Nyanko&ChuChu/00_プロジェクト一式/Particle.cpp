//=======================================
//
//�p�[�e�B�N���̃��C������[Particle.cpp]
//Author ��������
//
//=======================================
#include "Particle.h"

//---------------------------------------
// �R���X�g���N�^
//---------------------------------------
CParticle::CParticle()
{

}

//---------------------------------------
// �f�X�g���N�^
//---------------------------------------
CParticle::~CParticle()
{

}

//===============================
//�p�[�e�B�N���̏���������
//===============================
HRESULT CParticle::Init(void)
{
	// ������Ԃ�
	return S_OK;
}

//===============================
//�p�[�e�B�N���̏I������
//===============================
void CParticle::Uninit(void)
{

}

//===============================
//�p�[�e�B�N���̍X�V����
//===============================
void CParticle::Update(void)
{
	
}

//===============================
//�p�[�e�B�N���̕`�揈��
//===============================
void CParticle::Draw(void)
{
	
}

//===============================
// ��������
//===============================
void CParticle::Create(const D3DXVECTOR3& pos, const CParticle::TYPE type)
{
	// ���[�J���|�C���^�錾
	CParticle* pParticle = nullptr;		// �p�[�e�B�N��2D�̃|�C���^

	if (pParticle == nullptr)
	{ // �p�[�e�B�N���� NULL �̏ꍇ

		// ���������m�ۂ���
		pParticle = new CParticle;
	}

	if (pParticle != nullptr)
	{ // ��� NULL ����Ȃ��ꍇ

		switch (type)
		{
		case TYPE_FIRE:			// ���n

			// �����̏���������
			pParticle->InitFire(pos);

			break;

		case TYPE_DUST:			// ���n

			// ���̏���������
			pParticle->InitDust(pos);

			break;

		case TYPE_ITEMGET:		// �A�C�e���擾

			// �A�C�e���Q�b�g�̏���������
			pParticle->InitItemGet(pos);

			break;

		case TYPE_ENEMYDEATH:	// �G�̎��S

			// �G�̎��S�̏���������
			pParticle->InitEnemyDeath(pos);

			break;

		case TYPE_SLIME:	// �S����

			// �S�����̏���������
			pParticle->InitSlime(pos);

			break;

		case TYPE_RESURRECTION: //����

			//�����̏���������
			pParticle->InitResurrection(pos);

			break;

		case TYPE_HONEY: // �n�`�~�c

			// �n�`�~�c�̏���������
			pParticle->InitHoney(pos);

			break;

		default:			// ��L�ȊO

			// ��~
			assert(false);

			break;
		}
	}
	else
	{ // ��L�ȊO

		// ��~
		assert(false);
	}

	if (pParticle != nullptr)
	{ // �p�[�e�B�N���� NULL ����Ȃ��ꍇ

		// ���������J������
		delete pParticle;
		pParticle = nullptr;
	}
}

//===============================
// �����p�[�e�B�N������
//===============================
void CParticle::InitFire(const D3DXVECTOR3& pos)
{
	//[�����p�ϐ�]
	D3DXVECTOR3 ShiftPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ���
	int nLife = 0;											// �̗�
	float fAngle = 0.0f;									// ����
	float fSpeed = 0.0f;									// ���x
	float fRadius = 0.0f;									// ���a

	for (int nCntPar = 0; nCntPar < 20; nCntPar++)
	{
		// �ʒu�̐ݒ�
		ShiftPos.x = pos.x + (float)((rand() % 101 - 50) / 10.0f);
		ShiftPos.y = pos.y + (float)((rand() % 101 - 50) / 10.0f);
		ShiftPos.z = 0.0f;

		//�p�x��ݒ肷��
		fAngle = (float)(rand() % 629 - 314) / 100.0f;

		//�ړ��ʂ�ݒ肷��
		fSpeed = (float)(rand() % 300) / 100.0f + 4.0f;

		//�ړ��ʂ�ݒ肷��
		move.x = sinf(fAngle) * fSpeed;
		move.y = cosf(fAngle) * fSpeed;

		//���a��ݒ肷��
		fRadius = (float)(rand() % 1000) / 100.0f + 30.0f;

		// �����̐ݒ�
		nLife = rand() % 30 + 7;

		// �G�t�F�N�g�̐ݒ菈��
		CEffect::Create
		(
			ShiftPos,			// �ʒu
			move,				// �ړ���
			nLife,				// ����
			fRadius,			// ���a
			CEffect::TYPE_FIRE,	// ���
			D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),
			true
		);
	}
}

//===============================
// ���n���̐���
//===============================
void CParticle::InitDust(const D3DXVECTOR3& pos)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 EffectPos;		// �G�t�F�N�g�̈ʒu
	D3DXVECTOR3 EffectMove;		// �G�t�F�N�g�̈ړ���
	int nLife;					// ����
	D3DXVECTOR3 randRot;		// �����_���̌���

	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		// ������ݒ肷��
		randRot.x = (float)((rand() % 629 - 314) * 0.01f);
		EffectPos.x = pos.x + sinf(randRot.x) * 20.0f;

		EffectPos.y = pos.y;

		// ������ݒ肷��
		randRot.z = (float)((rand() % 629 - 314) * 0.01f);
		EffectPos.z = pos.z + cosf(randRot.z) * 20.0f;

		for (int nCntDust = 0; nCntDust < 4; nCntDust++)
		{
			EffectMove.x = sinf(randRot.x) * (rand() % 3 + 10);
			EffectMove.y = (float)(rand() % 3 + 1);
			EffectMove.z = cosf(randRot.z) * (rand() % 3 + 10);

			// ������ݒ肷��
			nLife = rand() % 20 + 10;

			// �G�t�F�N�g�̐�������
			CEffect::Create
			(
				EffectPos,
				EffectMove,
				nLife,
				50.0f,
				CEffect::TYPE_DUST,
				D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f),
				false
			);
		}
	}
}

//===============================
// �A�C�e���Q�b�g�̐���
//===============================
void CParticle::InitItemGet(const D3DXVECTOR3& pos)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 move;		// �G�t�F�N�g�̈ړ���
	D3DXVECTOR3 effectpos;
	int nLife;				// ����
	float fRot;				// ����
	float fRadius;			// ���a

	for (int nCntDust = 0; nCntDust < 15; nCntDust++)
	{

		// ������ݒ肷��
		fRot =  ((D3DX_PI *2)/15.0f)* nCntDust;
		effectpos.x = pos.x + sinf(fRot) *15.0f;
		effectpos.y = pos.y + cosf(fRot) *15.0f;
		effectpos.z = 0.0f;

		// �ړ��ʂ�ݒ肷��
		move.x = sinf(fRot) * 15.0f;
		move.y = cosf(fRot) * 15.0f;
		move.z = cosf(fRot) * 15.0f;

		// ������ݒ肷��
		nLife = 17;

		// ���a��ݒ肷��
		fRadius = 30.0f;
		// �G�t�F�N�g�̐�������
		CEffect::Create
		(
			pos,
			move,
			nLife,
			fRadius,
			CEffect::TYPE_ITEMGET,
			D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f),
			true
		);
	}
}

//===============================
// �G�̎��S�̐���
//===============================
void CParticle::InitEnemyDeath(const D3DXVECTOR3& pos)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 move;		// �G�t�F�N�g�̈ړ���
	int nLife;				// ����
	float fRot;				// ����
	float fRadius;			// ���a

	for (int nCntDust = 0; nCntDust < 10; nCntDust++)
	{
		// ������ݒ肷��
		fRot = (float)((rand() % 629 - 314) * 0.01f);

		// �ړ��ʂ�ݒ肷��
		move.x = sinf(fRot) * (rand() % 20 - 10);
		move.y = cosf(fRot) * (rand() % 20);
		move.z = 0.0f;

		// ������ݒ肷��
		nLife = rand() % 10 + 10;

		// ���a��ݒ肷��
		//fRadius = (float)(rand() % 300 + 15);
		fRadius = 50.0f;
		// �G�t�F�N�g�̐�������
		CEffect::Create
		(
			pos,
			move,
			nLife,
			fRadius,
			CEffect::TYPE_RUPTURE,
			D3DXCOLOR(1.0f, 1.0f, 0.5f, 1.0f),
			false
		);
	}
}

//===============================
// �X���C�����̃G�t�F�N�g����
//===============================
void CParticle::InitSlime(const D3DXVECTOR3& pos)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 EffectPos;		// �G�t�F�N�g�̈ʒu
	D3DXVECTOR3 EffectMove;		// �G�t�F�N�g�̈ړ���
	int nLife;					// ����
	D3DXVECTOR3 randRot;		// �����_���̌���

		// ������ݒ肷��
	randRot.x = (float)((rand() % 629 - 314) * 0.01f);
	EffectPos.x = pos.x + sinf(randRot.x) * 20.0f;

	EffectPos.y = pos.y;

	// ������ݒ肷��
	randRot.z = (float)((rand() % 629 - 314) * 0.01f);
	EffectPos.z = pos.z + cosf(randRot.z) * 20.0f;

	EffectMove.x = sinf(randRot.x) * (rand() % 3 + 7);
	EffectMove.y = (float)(rand() % 3 + 1);
	EffectMove.z = cosf(randRot.z) * (rand() % 3 + 7);

	// ������ݒ肷��
	nLife = rand() % 10 + 8;

	// �G�t�F�N�g�̐�������
	CEffect::Create
	(
		EffectPos,
		EffectMove,
		nLife,
		50.0f,
		CEffect::TYPE_DUST,
		D3DXCOLOR(0.4f, 1.0f, 0.4f, 1.0f),
		false
	);
}

//===============================
// �����̃G�t�F�N�g����
//===============================
void CParticle::InitResurrection(const D3DXVECTOR3& pos)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 EffectPos;		// �G�t�F�N�g�̈ʒu
	D3DXVECTOR3 EffectMove;		// �G�t�F�N�g�̈ړ���
	int nLife;					// ����
	D3DXVECTOR3 randRot;		// �����_���̌���

		// ������ݒ肷��
		randRot.x = (float)((rand() % 629 - 314) * 0.01f);
		EffectPos.x = pos.x + sinf(randRot.x) * ((float)(rand() %10) + 10.0f);

		EffectPos.y = pos.y;

		// ������ݒ肷��
		randRot.z = (float)((rand() % 629 - 314) * 0.01f);
		EffectPos.z = pos.z + cosf(randRot.z) *((float)(rand() % 10) + 10.0f);

		for (int nCntDust = 0; nCntDust < 4; nCntDust++)
		{
			EffectMove.x = sinf(randRot.x) * (rand() % 3 + 3);
			EffectMove.y = (float)(rand() % 5 + 10);
			EffectMove.z = cosf(randRot.z) * (rand() % 3 + 10);

			// ������ݒ肷��
			nLife = rand() % 10 + 10;

			// �G�t�F�N�g�̐�������
			CEffect::Create
			(
				EffectPos,
				EffectMove,
				nLife,
				20.0f,
				CEffect::TYPE_RESURRECTION,
				D3DXCOLOR(1.0f, 0.8f, 0.0f, 1.0f),
				false
			);
		}

}

//===============================
// �n�`�~�c���̃G�t�F�N�g����
//===============================
void CParticle::InitHoney(const D3DXVECTOR3& pos)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 EffectPos;		// �G�t�F�N�g�̈ʒu
	D3DXVECTOR3 EffectMove;		// �G�t�F�N�g�̈ړ���
	int nLife;					// ����
	D3DXVECTOR3 randRot;		// �����_���̌���

								// ������ݒ肷��
	randRot.x = (float)((rand() % 629 - 314) * 0.01f);
	EffectPos.x = pos.x + sinf(randRot.x) * 20.0f;

	EffectPos.y = pos.y;

	// ������ݒ肷��
	randRot.z = (float)((rand() % 629 - 314) * 0.01f);
	EffectPos.z = pos.z + cosf(randRot.z) * 20.0f;

	EffectMove.x = sinf(randRot.x) * (rand() % 3 + 7);
	EffectMove.y = (float)(rand() % 3 + 1);
	EffectMove.z = cosf(randRot.z) * (rand() % 3 + 7);

	// ������ݒ肷��
	nLife = rand() % 10 + 8;

	// �G�t�F�N�g�̐�������
	CEffect::Create
	(
		EffectPos,
		EffectMove,
		nLife,
		50.0f,
		CEffect::TYPE_DUST,
		D3DXCOLOR(1.0f, 0.8f, 0.1f, 1.0f),
		false
	);
}