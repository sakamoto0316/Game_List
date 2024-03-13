//===========================================
//
// �ۉe�̃��C������[shadowCircle.cpp]
// Author ��������
//
//===========================================
#include "main.h"
#include "shadowCircle.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "collision.h"

//-------------------------------------------
// �ÓI�����o�ϐ��錾
//-------------------------------------------
int CShadowCircle::m_nNumAll = 0;				// �e�̑���

//-------------------------------------------
// �}�N����`
//-------------------------------------------
#define SHADOW_TEXTURE		"data\\TEXTURE\\shadow.jpg"		// �e�̃e�N�X�`��

//====================
// �R���X�g���N�^
//====================
CShadowCircle::CShadowCircle() : CObject3D(TYPE_SHADOW, PRIORITY_SHADOW)
{
	// �S�Ă̒l���N���A����
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// �F
	m_nID = INIT_SHADOW;						// �e�̃C���f�b�N�X
}

//====================
// �f�X�g���N�^
//====================
CShadowCircle::~CShadowCircle()
{

}

//====================
// ����������
//====================
HRESULT CShadowCircle::Init(void)
{
	// ����������
	if (FAILED(CObject3D::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// �F
	m_nID = INIT_SHADOW;						// �e�̃C���f�b�N�X

	// ������Ԃ�
	return S_OK;
}

//====================
// �I������
//====================
void CShadowCircle::Uninit(void)
{
	// �I�u�W�F�N�g�̏I������
	CObject3D::Uninit();

	// �e�̑��������Z����
	m_nNumAll--;
}

//====================
// �X�V����
//====================
void CShadowCircle::Update(void)
{

}

//====================
// �`�揈��
//====================
void CShadowCircle::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	// Z�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);		// Z�e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);			// Z�o�b�t�@�X�V�̗L�� / �����̐ݒ�

	//���Z����
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �`�揈��
	CObject3D::Draw();

	//�ʏ�̍����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// Z�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);		// Z�e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);			// Z�o�b�t�@�X�V�̗L�� / �����̐ݒ�
}

//====================
// ���̐ݒ菈��
//====================
void CShadowCircle::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, float fRadius)
{
	// ���̏�����
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f);		// �F
	m_nID = m_nNumAll;								// �ԍ�

	// �e�̑��������Z����
	m_nNumAll++;

	// ���̐ݒ�
	SetPos(D3DXVECTOR3(pos.x, 0.0f, pos.z));			// �ʒu
	SetPosOld(pos);			// �O��̈ʒu
	SetRot(rot);			// ����
	SetSize(D3DXVECTOR3(fRadius, 0.0f, fRadius));		// �T�C�Y

	// �ݒ菈��
	AlphaSet();

	// ���_���̐ݒ菈��
	SetVertex();

	// ���_�J���[�̐ݒ菈��
	SetVtxColor(m_col);

	// �e�N�X�`���̓ǂݍ��ݏ���
	BindTexture(CManager::Get()->GetTexture()->Regist(SHADOW_TEXTURE));
}

//====================
// �e�̈ʒu�ݒ菈��
//====================
void CShadowCircle::SetPosRot(int nIdx, const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// ���[�J���ϐ��錾
	CShadowCircle* pShadow = GetShadow(nIdx);	// �e�ւ̃|�C���^

	if (pShadow != nullptr)
	{ // �|�C���^�� NULL ����Ȃ��ꍇ

		// �ʒu�̐ݒ菈��
		pShadow->SetPos(pos);

		// �����̐ݒ菈��
		pShadow->SetRot(D3DXVECTOR3(0.0f, rot.y, 0.0f));
	}
}

//====================
// �e�̈ʒu�ݒ菈��(Y������)
//====================
void CShadowCircle::SetPosRotXZ(int nIdx, const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// ���[�J���ϐ��錾
	CShadowCircle* pShadow = GetShadow(nIdx);	// �e�ւ̃|�C���^

	if (pShadow != nullptr)
	{ // �|�C���^�� NULL ����Ȃ��ꍇ

		// �e�̈ʒu�̐ݒ菈��
		collision::ShadowCollision(pos, nIdx);

		// �����̐ݒ菈��
		pShadow->SetRot(D3DXVECTOR3(0.0f, rot.y, 0.0f));
	}
}

//====================
// �����x�̐ݒ菈��
//====================
void CShadowCircle::AlphaSet(void)
{

}

//====================
// ID�̎擾����
//====================
int CShadowCircle::GetNumID(void) const
{
	// �e�̔ԍ���Ԃ�
	return m_nID;
}

//====================
// �ۉe�̎擾����
//====================
CShadowCircle* CShadowCircle::GetShadow(int nIdx)
{
	// ���[�J���ϐ��錾
	CObject* pObj = nullptr;			// �I�u�W�F�N�g�̃|�C���^
	CShadowCircle* pShadow = nullptr;	// �e�̃|�C���^

	if (nIdx != INIT_SHADOW)
	{ // �e�̃C���f�b�N�X������ꍇ

		// �I�u�W�F�N�g�̏����擾����
		pObj = GetTop(PRIORITY_SHADOW);

		while (pObj != nullptr)
		{ // �I�u�W�F�N�g�̃|�C���^�� NULL ����Ȃ������

			if (pObj->GetType() == TYPE_SHADOW)
			{ // ��ނ��e�̏ꍇ

				// �e�̏����擾����
				pShadow = dynamic_cast<CShadowCircle*>(pObj);

				if (pShadow != nullptr)
				{ // �e�̃|�C���^�� NULL ����Ȃ��ꍇ

					if (pShadow->GetNumID() == nIdx)
					{ // �e�̔ԍ��������ƈ�v�����ꍇ

						// �e�̃|�C���^��Ԃ�
						return pShadow;
					}
					else
					{ // ��L�ȊO

						// ���̃I�u�W�F�N�g��ݒ肷��
						pObj = pObj->GetNext();
					}
				}
				else
				{ // �e�̃|�C���^�� NULL �̏ꍇ

					// ���̃I�u�W�F�N�g��ݒ肷��
					pObj = pObj->GetNext();
				}
			}
			else
			{ // ��L�ȊO

				// ���̃I�u�W�F�N�g��ݒ肷��
				pObj = pObj->GetNext();
			}
		}

		// NULL ��Ԃ�
		return nullptr;
	}
	else
	{ // ��L�ȊO

		// NULL ��Ԃ�
		return nullptr;
	}
}

//====================
// ��������
//====================
CShadowCircle* CShadowCircle::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, float fRadius)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CShadowCircle* pShadow = nullptr;	// �e�̃C���X�^���X�𐶐�

	if (pShadow == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pShadow = new CShadowCircle;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pShadow != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pShadow->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}

		// ���̐ݒ菈��
		pShadow->SetData(pos, rot, fRadius);
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �e�̃|�C���^��Ԃ�
	return pShadow;
}