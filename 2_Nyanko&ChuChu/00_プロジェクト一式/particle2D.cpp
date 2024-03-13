//=======================================
//
// �p�[�e�B�N��2D�̃��C������[Particle2D.cpp]
// Author ��������
//
//=======================================
#include "game.h"
#include "particle2D.h"

//---------------------------------------
// �R���X�g���N�^
//---------------------------------------
CParticle2D::CParticle2D()
{

}

//---------------------------------------
// �f�X�g���N�^
//---------------------------------------
CParticle2D::~CParticle2D()
{

}

//===============================
//�p�[�e�B�N���̏���������
//===============================
HRESULT CParticle2D::Init(void)
{
	// ������Ԃ�
	return S_OK;
}

//===============================
//�p�[�e�B�N���̏I������
//===============================
void CParticle2D::Uninit(void)
{

}

//===============================
//�p�[�e�B�N���̍X�V����
//===============================
void CParticle2D::Update(void)
{
	
}

//===============================
//�p�[�e�B�N���̕`�揈��
//===============================
void CParticle2D::Draw(void)
{
	
}

//===============================
// ��������
//===============================
void CParticle2D::Create(const D3DXVECTOR3& pos, const CEffect2D::TYPE type)
{
	// ���[�J���|�C���^�錾
	CParticle2D* pParticle = nullptr;		// �p�[�e�B�N��2D�̃|�C���^

	if (pParticle == nullptr)
	{ // �p�[�e�B�N���� NULL �̏ꍇ

		// ���������m�ۂ���
		pParticle = new CParticle2D;
	}

	if (pParticle != nullptr)
	{ // ��񂪂������ꍇ

		switch (type)
		{
		case CEffect2D::TYPE_NONE:			// ����

			break;

		case CEffect2D::TYPE_SHINING:		// �P���n

			//// �P������
			//InitShining(pos, type);

			break;

		case CEffect2D::TYPE_OVERTOP:		// ���E�˔j

			// �u�[�X�g�̏�����
			pParticle->InitBoost(pos, type);

			break;

		case CEffect2D::TYPE_INFIRE:		// �����̉�

			// �u�[�X�g�̏�����
			pParticle->InitBoost(pos, type);

			break;

		case CEffect2D::TYPE_OUTFIRE:		// �O���̉�

			// �u�[�X�g�̏�����
			pParticle->InitBoost(pos, type);

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
// �u�[�X�g�̏�����
//===============================
void CParticle2D::InitBoost(const D3DXVECTOR3& pos, const CEffect2D::TYPE type)
{
	D3DXVECTOR3 move;			// �ړ���
	float fRot;					// ����
	int nLife;					// ����
	float fRadius;				// ���a

	fRot = (float)((rand() % 31 - 15) * 0.01f);

	// �ړ��ʂ�ݒ肷��
	move.x = (float)(rand() % 11 - 5) * 0.1f;
	move.y = cosf(fRot) * (float)-(rand() % 40 + 20) * 0.1f;
	move.z = 0.0f;

	nLife = 40;

	fRadius = (float)(rand() % 20 + 60);

	// �G�t�F�N�g�̐�������
	CEffect2D::Create(pos, move, nLife, fRadius, CEffect2D::TYPE_OUTFIRE);

	//for (int nCnt = 0; nCnt < 5; nCnt++)
	//{
	fRot = (float)((rand() % 31 - 15) * 0.01f);

	// �ړ��ʂ�ݒ肷��
	move.x = (float)(rand() % 11 - 5) * 0.1f;
	move.y = cosf(fRot) * (float)-(rand() % 40 + 20) * 0.1f;
	move.z = 0.0f;

	nLife = 40;

	fRadius = (float)(rand() % 10 + 40);

	// �G�t�F�N�g�̐�������
	CEffect2D::Create(pos, move, nLife, fRadius, CEffect2D::TYPE_INFIRE);
	//}
}