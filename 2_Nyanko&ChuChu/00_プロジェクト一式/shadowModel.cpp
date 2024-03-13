//===========================================
//
// ���f���e�̃��C������[shadowModel.cpp]
// Author ��������
//
//===========================================
#include "main.h"
#include "shadowModel.h"
#include "light.h"
#include "manager.h"
#include "renderer.h"

//====================
// �R���X�g���N�^
//====================
CShadowModel::CShadowModel() : CModel(TYPE_SHADOW, PRIORITY_SHADOW)
{
	// �S�Ă̒l���N���A����
	ZeroMemory(&m_mtxParent, sizeof(D3DXMATRIX));
}

//====================
// �f�X�g���N�^
//====================
CShadowModel::~CShadowModel()
{

}

//====================
// ����������
//====================
HRESULT CShadowModel::Init(void)
{
	// ����������
	if (FAILED(CModel::Init()))
	{ // �������Ɏ��s�����ꍇ

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	ZeroMemory(&m_mtxParent, sizeof(D3DXMATRIX));

	// ������Ԃ�
	return S_OK;
}

//====================
// �I������
//====================
void CShadowModel::Uninit(void)
{
	// �I�u�W�F�N�g�̏I������
	CModel::Uninit();
}

//====================
// �X�V����
//====================
void CShadowModel::Update(void)
{

}

//====================
// �`�揈��
//====================
void CShadowModel::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	// ���[�J���ϐ��錾
	D3DXMATRIX mtxShadow;		// �e�̃}�g���b�N�X
	D3DLIGHT9 light;			// ���C�g�̏��
	D3DXVECTOR4 posLight;		// ���C�g�̈ʒu
	D3DXVECTOR3 pos, normal;	// ���ʏ�̔C�ӂ̓_�A�@���x�N�g��
	D3DXPLANE plane;			// ���ʏ��

	// Z�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);		// Z�e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);			// Z�o�b�t�@�X�V�̗L�� / �����̐ݒ�

	// ���C�g�̈ʒu��ݒ�
	pDevice->GetLight(0, &light);
	posLight = D3DXVECTOR4(-light.Direction.x, -light.Direction.y, -light.Direction.z, 0.0f);

	// ���ʏ��𐶐�
	pos = GetPos();
	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXPlaneFromPointNormal(&plane, &pos, &normal);

	// �e�̃}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxShadow);

	// �e�̃}�g���b�N�X�̍쐬
	D3DXMatrixShadow(&mtxShadow, &posLight, &plane);
	D3DXMatrixMultiply(&mtxShadow, &m_mtxParent, &mtxShadow);

	// �e�̃}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	// �e��p�`�揈��
	CModel::DrawShadow();

	// Z�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);		// Z�e�X�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);			// Z�o�b�t�@�X�V�̗L�� / �����̐ݒ�
}

//====================
// ���̐ݒ菈��
//====================
void CShadowModel::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& scale, const CXFile::TYPE& type, const D3DXMATRIX& mtx)
{
	// ���̐ݒ�
	SetPos(pos);			// �ʒu
	SetPosOld(pos);			// �O��̈ʒu
	SetRot(rot);			// ����
	SetScale(scale);		// �g�嗦
	SetFileData(type);		// ���
	m_mtxParent = mtx;		// �e�̃}�g���b�N�X

	// X�t�@�C���̏����擾����
	CXFile::SXFile file = GetFileData();

	// �ő�l�𔽉f����
	file.vtxMax.x *= scale.x;
	file.vtxMax.y *= scale.y;
	file.vtxMax.z *= scale.z;

	// �ŏ��l�𔽉f����
	file.vtxMin.x *= scale.x;
	file.vtxMin.y *= scale.y;
	file.vtxMin.z *= scale.z;

	// �f�[�^�̐ݒ菈��
	SetFileData(file);
}

//====================
// �e�̈ʒu�ݒ菈��
//====================
void CShadowModel::SetPosRot(int nIdx, const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// ���[�J���ϐ��錾
	CObject* pObj = nullptr;			// �I�u�W�F�N�g�ւ̃|�C���^
	CShadowModel* pShadow = nullptr;	// �e�ւ̃|�C���^

	// �I�u�W�F�N�g�̏����擾����
	pObj = GetTop(PRIORITY_SHADOW);

	for (int nCnt = 0; nCnt < nIdx; nCnt++)
	{
		// ���̃I�u�W�F�N�g��������
		pObj = pObj->GetNext();
	}

	if (pObj != nullptr)
	{ // �|�C���^�� NULL �̏ꍇ

		if (pObj->GetType() == TYPE_SHADOW)
		{ // ��ނ��e�̏ꍇ

			// �e�̏����擾����
			pShadow = dynamic_cast<CShadowModel*>(pObj);

			if (pShadow != nullptr)
			{ // �|�C���^�� NULL ����Ȃ��ꍇ

				// �ʒu�̐ݒ菈��
				pShadow->SetPos(pos);

				// �����̐ݒ菈��
				pShadow->SetRot(rot);
			}
		}
	}
}

//====================
// ��������
//====================
CShadowModel* CShadowModel::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& scale, const CXFile::TYPE& type, const D3DXMATRIX& mtx)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CShadowModel* pShadow = nullptr;	// �e�̃C���X�^���X�𐶐�

	if (pShadow == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pShadow = new CShadowModel;
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
		pShadow->SetData(pos, rot, scale, type, mtx);
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