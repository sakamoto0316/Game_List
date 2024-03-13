//============================================================
//
// X�t�@�C������ [xfile.cpp]
// Author�F��������
//
//============================================================
//************************************************************
// �C���N���[�h�t�@�C��
//************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "character.h"
#include "model.h"
#include "texture.h"

//=====================================================================��������CHierarchy�̏���=====================================================================

//========================
// �R���X�g���N�^
//========================
CHierarchy::CHierarchy()
{
	// �S�Ă̒l���N���A����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �O��̈ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ����
	m_scale = NONE_SCALE;								// �g�嗦
	ZeroMemory(&m_mtxWorld, sizeof(D3DXMATRIX));		// ���[���h�}�g���b�N�X
	ZeroMemory(&m_XFileData, sizeof(CXFile::SXFile));	// X�t�@�C���̃f�[�^
	m_apParent = nullptr;								// �e���f���̃|�C���^
}

//========================
// �f�X�g���N�^
//========================
CHierarchy::~CHierarchy()
{

}

//========================
// ����������
//========================
HRESULT CHierarchy::Init(void)
{
	// �S�Ă̒l������������
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ʒu
	m_posOld = m_pos;			// �O��̈ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ����
	m_scale = NONE_SCALE;		// �g�嗦

	// ������Ԃ�
	return S_OK;
}

//========================
// �I������
//========================
void CHierarchy::Uninit(void)
{
	// �e���f���ւ̃|�C���^�� NULL �ɂ���
	m_apParent = nullptr;
}

//========================
// �X�V����
//========================
void CHierarchy::Update(void)
{

}

//========================
// �`�揈��
//========================
void CHierarchy::Draw(void)
{
	// �ϐ���錾
	D3DXMATRIX   mtxScale, mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p

	// �|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();	// �f�o�C�X�ւ̃|�C���^
	D3DXMATERIAL     *pMat;						// �}�e���A���f�[�^�ւ̃|�C���^

	D3DXMATRIX mtxRotModel, mtxTransModel;		// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxParent;						// �e�̃}�g���b�N�X

	// �p�[�c�̃��[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �g�嗦�𔽉f
	D3DXMatrixScaling(&mtxScale, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// �p�[�c�́u�e�̃}�g���b�N�X�v��ݒ�
	if (m_apParent != nullptr)
	{ // �e���f��������ꍇ

		// �e���f���̃C���f�b�N�X���w�肷��
		mtxParent = m_apParent->m_mtxWorld;
	}
	else
	{ // �e���f�����Ȃ��ꍇ

		// �e�̃}�g���b�N�X���擾����
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	// �Z�o�����u�p�[�c�̃��[���h�}�g���b�N�X�v�Ɓu�e�̃}�g���b�N�X�v���|�����킹��
	D3DXMatrixMultiply
	(
		&m_mtxWorld,
		&m_mtxWorld,
		&mtxParent
	);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_XFileData.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_XFileData.dwNumMat; nCntMat++)
	{ // �}�e���A���̐����J��Ԃ�

		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, CManager::Get()->GetTexture()->GetAddress(m_XFileData.m_nTexIdx[nCntMat]));

		if (m_scale != NONE_SCALE)
		{ // �g�嗦���ύX����Ă���ꍇ

			// ���_�@���̎������K����L���ɂ���
			pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
		}

		// ���f���̕`��
		m_XFileData.pMesh->DrawSubset(nCntMat);

		// ���_�@���̎������K���𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
	}

	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//========================
// �`�揈��(�F����)
//========================
void CHierarchy::Draw(D3DXCOLOR col)
{
	// �ϐ���錾
	D3DXMATRIX   mtxScale, mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p

	// �|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();	// �f�o�C�X�ւ̃|�C���^
	D3DXMATERIAL     *pMat;						// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL     colMat;					// �`��p�}�e���A��

	D3DXMATRIX mtxRotModel, mtxTransModel;		// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxParent;						// �e�̃}�g���b�N�X

	// �p�[�c�̃��[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �g�嗦�𔽉f
	D3DXMatrixScaling(&mtxScale, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// �p�[�c�́u�e�̃}�g���b�N�X�v��ݒ�
	if (m_apParent != nullptr)
	{ // �e���f��������ꍇ

		// �e���f���̃C���f�b�N�X���w�肷��
		mtxParent = m_apParent->m_mtxWorld;
	}
	else
	{ // �e���f�����Ȃ��ꍇ

		// �e�̃}�g���b�N�X���擾����
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	// �Z�o�����u�p�[�c�̃��[���h�}�g���b�N�X�v�Ɓu�e�̃}�g���b�N�X�v���|�����킹��
	D3DXMatrixMultiply
	(
		&m_mtxWorld,
		&m_mtxWorld,
		&mtxParent
	);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_XFileData.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_XFileData.dwNumMat; nCntMat++)
	{ // �}�e���A���̐����J��Ԃ�

		// �\���̗̂v�f���N���A
		ZeroMemory(&colMat, sizeof(D3DXMATERIAL));

		// �}�e���A���f�[�^�̃R�s�[�ɑ������
		colMat = pMat[nCntMat];

		// �����x��������
		colMat.MatD3D.Diffuse = col;
		colMat.MatD3D.Ambient = col;
		colMat.MatD3D.Emissive = col;

		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&colMat.MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, CManager::Get()->GetTexture()->GetAddress(m_XFileData.m_nTexIdx[nCntMat]));

		if (m_scale != NONE_SCALE)
		{ // �g�嗦���ύX����Ă���ꍇ

			// ���_�@���̎������K����L���ɂ���
			pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
		}

		// ���f���̕`��
		m_XFileData.pMesh->DrawSubset(nCntMat);

		// ���_�@���̎������K���𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
	}

	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//========================
// ���f���e�̕`�揈��
//========================
void CHierarchy::DrawShadow(void)
{
	// �ϐ���錾
	D3DXMATRIX   mtxScale, mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p

	// �|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();	// �f�o�C�X�ւ̃|�C���^
	D3DXMATERIAL     *pMat;						// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL     colMat;					// �`��p�}�e���A��

	D3DXMATRIX mtxRotModel, mtxTransModel;		// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxParent;						// �e�̃}�g���b�N�X

	// �p�[�c�̃��[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �g�嗦�𔽉f
	D3DXMatrixScaling(&mtxScale, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// �p�[�c�́u�e�̃}�g���b�N�X�v��ݒ�
	if (m_apParent != nullptr)
	{ // �e���f��������ꍇ

		// �e���f���̃C���f�b�N�X���w�肷��
		mtxParent = m_apParent->m_mtxWorld;
	}
	else
	{ // �e���f�����Ȃ��ꍇ

		// �e�̃}�g���b�N�X���擾����
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	// �Z�o�����u�p�[�c�̃��[���h�}�g���b�N�X�v�Ɓu�e�̃}�g���b�N�X�v���|�����킹��
	D3DXMatrixMultiply
	(
		&m_mtxWorld,
		&m_mtxWorld,
		&mtxParent
	);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_XFileData.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_XFileData.dwNumMat; nCntMat++)
	{ // �}�e���A���̐����J��Ԃ�

		// �\���̗̂v�f���N���A
		ZeroMemory(&colMat, sizeof(D3DXMATERIAL));

		// �����x��������
		colMat.MatD3D.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		colMat.MatD3D.Ambient = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		colMat.MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&colMat.MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);

		if (m_scale != NONE_SCALE)
		{ // �g�嗦���ύX����Ă���ꍇ

			// ���_�@���̎������K����L���ɂ���
			pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
		}

		// ���f���̕`��
		m_XFileData.pMesh->DrawSubset(nCntMat);

		// ���_�@���̎������K���𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
	}

	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//========================
// �`�揈��(�����x����)
//========================
void CHierarchy::Draw(float fAlpha)
{
	// �ϐ���錾
	D3DXMATRIX   mtxScale, mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p

	// �|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();	// �f�o�C�X�ւ̃|�C���^
	D3DXMATERIAL     *pMat;						// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL     colMat;					// �`��p�}�e���A��

	D3DXMATRIX mtxRotModel, mtxTransModel;		// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxParent;						// �e�̃}�g���b�N�X

	// �p�[�c�̃��[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �g�嗦�𔽉f
	D3DXMatrixScaling(&mtxScale, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// �p�[�c�́u�e�̃}�g���b�N�X�v��ݒ�
	if (m_apParent != nullptr)
	{ // �e���f��������ꍇ

		// �e���f���̃C���f�b�N�X���w�肷��
		mtxParent = m_apParent->m_mtxWorld;
	}
	else
	{ // �e���f�����Ȃ��ꍇ

		// �e�̃}�g���b�N�X���擾����
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	// �Z�o�����u�p�[�c�̃��[���h�}�g���b�N�X�v�Ɓu�e�̃}�g���b�N�X�v���|�����킹��
	D3DXMatrixMultiply
	(
		&m_mtxWorld,
		&m_mtxWorld,
		&mtxParent
	);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_XFileData.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_XFileData.dwNumMat; nCntMat++)
	{ // �}�e���A���̐����J��Ԃ�

		// �\���̗̂v�f���N���A
		ZeroMemory(&colMat, sizeof(D3DXMATERIAL));

		// �����x��������
		colMat.MatD3D.Diffuse = pMat[nCntMat].MatD3D.Diffuse;
		colMat.MatD3D.Ambient = pMat[nCntMat].MatD3D.Ambient;

		// �}�e���A���̓����x��ݒ肷��
		colMat.MatD3D.Diffuse.a = fAlpha;
		colMat.MatD3D.Ambient.a = fAlpha;

		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&colMat.MatD3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, CManager::Get()->GetTexture()->GetAddress(m_XFileData.m_nTexIdx[nCntMat]));

		if (m_scale != NONE_SCALE)
		{ // �g�嗦���ύX����Ă���ꍇ

		  // ���_�@���̎������K����L���ɂ���
			pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
		}

		// ���f���̕`��
		m_XFileData.pMesh->DrawSubset(nCntMat);

		// ���_�@���̎������K���𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
	}

	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//========================
// X�t�@�C���̃f�[�^�̎擾����
//========================
CXFile::SXFile CHierarchy::GetFileData(void)
{
	// X�t�@�C���̃f�[�^��Ԃ�
	return m_XFileData;
}

//========================
// �ʒu�ݒ菈��
//========================
void CHierarchy::SetPos(const D3DXVECTOR3& pos)
{
	// �ʒu��ݒ肷��
	m_pos = pos;
}

//========================
// �ʒu�擾����
//========================
D3DXVECTOR3 CHierarchy::GetPos(void) const
{
	// �ʒu��Ԃ�
	return m_pos;
}

//========================
// �O��̈ʒu�ݒ菈��
//========================
void CHierarchy::SetPosOld(const D3DXVECTOR3& posOld)
{
	// �O��̈ʒu��ݒ肷��
	m_posOld = posOld;
}

//========================
// �O��̈ʒu�擾����
//========================
D3DXVECTOR3 CHierarchy::GetPosOld(void) const
{
	// �O��̈ʒu��Ԃ�
	return m_posOld;
}

//========================
// �����ݒ菈��
//========================
void CHierarchy::SetRot(const D3DXVECTOR3& rot)
{
	// ������ݒ肷��
	m_rot = rot;
}

//========================
// �����擾����
//========================
D3DXVECTOR3 CHierarchy::GetRot(void) const
{
	// ������ݒ肷��
	return m_rot;
}

//========================
// �T�C�Y�ݒ菈��
//========================
void CHierarchy::SetScale(const D3DXVECTOR3& scale)
{
	// �g�嗦��ݒ肷��
	m_scale = scale;
}

//========================
// �T�C�Y�擾����
//========================
D3DXVECTOR3 CHierarchy::GetScale(void) const
{
	// �g�嗦��Ԃ�
	return m_scale;
}

//========================
// �f�[�^�̐ݒ菈��
//========================
void CHierarchy::SetFileData(const CXFile::TYPE type)
{
	if (type >= 0 && type < CXFile::TYPE_MAX)
	{ // ��ނ��K����̏ꍇ

		// �t�@�C���̃f�[�^��������
		m_XFileData = CXFile::GetXFile(type);
	}
	else
	{ // ��L�ȊO

		// ��~
		assert(false);
	}
}

//========================
// �f�[�^�̐ݒ菈��(�t�@�C���f�[�^�̐ݒ��)
//========================
void CHierarchy::SetFileData(const CXFile::SXFile filaData)
{
	// �t�@�C���̃f�[�^��������
	m_XFileData = filaData;
}

//========================
// �}�g���b�N�X�̎擾����
//========================
D3DXMATRIX CHierarchy::GetMatrix(void) const
{
	// ���[���h�}�g���b�N�X��Ԃ�
	return m_mtxWorld;
}

//========================
// �e�̐ݒ菈��
//========================
void CHierarchy::SetParent(CHierarchy* pModel)
{
	// �e�̃|�C���^��������
	m_apParent = pModel;
}

//========================
// �e�̎擾����
//========================
CHierarchy* CHierarchy::GetParent(void) const
{
	if (m_apParent != nullptr)
	{ // �e���f���̏�񂪂������ꍇ

		// �e���f���̏���Ԃ�
		return m_apParent;
	}
	else
	{ // �e���f���̏�񂪂Ȃ��ꍇ

		// NULL ��Ԃ�
		return nullptr;
	}
}

//========================
// ��������
//========================
CHierarchy* CHierarchy::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CHierarchy* pModel = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pModel == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pModel = new CHierarchy;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pModel != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

	  // ����������
		if (FAILED(pModel->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �I�u�W�F�N�g2D�̃|�C���^��Ԃ�
	return pModel;
}

//=====================================================================��������CCharacter�̏���=====================================================================

//========================
// �R���X�g���N�^
//========================
CCharacter::CCharacter() : CObject(TYPE_NONE, PRIORITY_BG)
{
	// �R���X�g���N�^�̔�
	Box();
}

//========================
// �I�[�o�[���[�h�R���X�g���N�^
//========================
CCharacter::CCharacter(CObject::TYPE type, PRIORITY priority) : CObject(type, priority)
{
	// �R���X�g���N�^�̔�
	Box();
}

//========================
// �f�X�g���N�^
//========================
CCharacter::~CCharacter()
{

}

//========================
// �R���X�g���N�^�̔�
//========================
void CCharacter::Box(void)
{
	// �S�Ă̒l���N���A����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �O��̈ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ����
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ړ���
	m_scale = NONE_SCALE;								// �g�嗦
	ZeroMemory(&m_mtxWorld, sizeof(D3DXMATRIX));		// ���[���h�}�g���b�N�X
	
	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		m_apModel[nCnt] = nullptr;						// ���f���̃|�C���^
	}

	m_nNumModel = 0;									// ���f���̑���
}

//========================
// ����������
//========================
HRESULT CCharacter::Init(void)
{
	// �S�Ă̒l������������
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ʒu
	m_posOld = m_pos;									// �O��̈ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ����
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ړ���
	m_scale = NONE_SCALE;								// �g�嗦

	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		m_apModel[nCnt] = nullptr;						// ���f���̃|�C���^
	}

	m_nNumModel = 0;									// ���f���̑���

	// ������Ԃ�
	return S_OK;
}

//========================
// �I������
//========================
void CCharacter::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{ // ���f���̃|�C���^�� NULL ����Ȃ��ꍇ

			// �I������
			m_apModel[nCnt]->Uninit();

			// ���������J������
			delete m_apModel[nCnt];
			m_apModel[nCnt] = nullptr;
		}
	}

	// �j������
	Release();
}

//========================
// �X�V����
//========================
void CCharacter::Update(void)
{

}

//========================
// �`�揈��
//========================
void CCharacter::Draw(void)
{
	// �ϐ���錾
	D3DXMATRIX   mtxScale, mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxWorld = GetMatrix();			// �}�g���b�N�X���擾����

	// �|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();	// �f�o�C�X�ւ̃|�C���^

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// �g�嗦�𔽉f
	D3DXMatrixScaling(&mtxScale, GetScale().x, GetScale().y, GetScale().z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		// �`�揈��
		m_apModel[nCnt]->Draw();
	}
}

//========================
// �`�揈��(�F����)
//========================
void CCharacter::Draw(D3DXCOLOR col)
{
	// �ϐ���錾
	D3DXMATRIX   mtxScale, mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxWorld = GetMatrix();			// �}�g���b�N�X���擾����

	// �|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();	// �f�o�C�X�ւ̃|�C���^

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// �g�嗦�𔽉f
	D3DXMatrixScaling(&mtxScale, GetScale().x, GetScale().y, GetScale().z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		// �`�揈��
		m_apModel[nCnt]->Draw(col);
	}
}

//========================
// ���f���e�̕`�揈��
//========================
void CCharacter::DrawShadow(void)
{
	// �ϐ���錾
	D3DXMATRIX   mtxScale, mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxWorld = GetMatrix();			// �}�g���b�N�X���擾����

	// �|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();	// �f�o�C�X�ւ̃|�C���^

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// �g�嗦�𔽉f
	D3DXMatrixScaling(&mtxScale, GetScale().x, GetScale().y, GetScale().z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		// �`�揈��
		m_apModel[nCnt]->DrawShadow();
	}
}

//========================
// �`�揈��(�����F)
//========================
void CCharacter::Draw(D3DXCOLOR* col)
{
	// �ϐ���錾
	D3DXMATRIX   mtxScale, mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxWorld = GetMatrix();			// �}�g���b�N�X���擾����

	// �|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();	// �f�o�C�X�ւ̃|�C���^

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// �g�嗦�𔽉f
	D3DXMatrixScaling(&mtxScale, GetScale().x, GetScale().y, GetScale().z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		// �`�揈��
		m_apModel[nCnt]->Draw(*col);
	}
}

//========================
// �`�揈��(�����x����)
//========================
void CCharacter::Draw(float fAlpha)
{
		// �ϐ���錾
	D3DXMATRIX   mtxScale, mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxWorld = GetMatrix();			// �}�g���b�N�X���擾����

	// �|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();	// �f�o�C�X�ւ̃|�C���^

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// �g�嗦�𔽉f
	D3DXMatrixScaling(&mtxScale, GetScale().x, GetScale().y, GetScale().z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScale);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, GetRot().y, GetRot().x, GetRot().z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, GetPos().x, GetPos().y, GetPos().z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		// �`�揈��
		m_apModel[nCnt]->Draw(fAlpha);
	}
}

//========================
// �ʒu�ݒ菈��
//========================
void CCharacter::SetPos(const D3DXVECTOR3& pos)
{
	// �ʒu��ݒ肷��
	m_pos = pos;
}

//========================
// �ʒu�擾����
//========================
D3DXVECTOR3 CCharacter::GetPos(void) const
{
	// �ʒu��Ԃ�
	return m_pos;
}

//========================
// �O��̈ʒu�ݒ菈��
//========================
void CCharacter::SetPosOld(const D3DXVECTOR3& posOld)
{
	// �O��̈ʒu��ݒ肷��
	m_posOld = posOld;
}

//========================
// �O��̈ʒu�擾����
//========================
D3DXVECTOR3 CCharacter::GetPosOld(void) const
{
	// �O��̈ʒu��Ԃ�
	return m_posOld;
}

//========================
// �����ݒ菈��
//========================
void CCharacter::SetRot(const D3DXVECTOR3& rot)
{
	// ������ݒ肷��
	m_rot = rot;
}

//========================
// �����擾����
//========================
D3DXVECTOR3 CCharacter::GetRot(void) const
{
	// ������ݒ肷��
	return m_rot;
}

//========================
// �ړ��ʐݒ菈��
//========================
void CCharacter::SetMove(const D3DXVECTOR3& move)
{
	// �ړ��ʂ�ݒ肷��
	m_move = move;
}

//========================
// �ړ��ʎ擾����
//========================
D3DXVECTOR3 CCharacter::GetMove(void) const
{
	// �ړ��ʂ�ݒ肷��
	return m_move;
}

//========================
// �T�C�Y�ݒ菈��
//========================
void CCharacter::SetScale(const D3DXVECTOR3& scale)
{
	// �g�嗦��ݒ肷��
	m_scale = scale;
}

//========================
// �T�C�Y�擾����
//========================
D3DXVECTOR3 CCharacter::GetScale(void) const
{
	// �g�嗦��Ԃ�
	return m_scale;
}

//========================
// �}�g���b�N�X�̎擾����
//========================
D3DXMATRIX CCharacter::GetMatrix(void) const
{
	// �}�g���b�N�X�̏���Ԃ�
	return m_mtxWorld;
}

//========================
// �}�g���b�N�X�̎擾����
//========================
D3DXMATRIX* CCharacter::GetMatrixP(void)
{
	// �}�g���b�N�X�̏���Ԃ�
	return &m_mtxWorld;
}

//========================
// �f�[�^�̐ݒ菈��
//========================
void CCharacter::SetData(void)
{
	for (int nCnt = 0; nCnt < m_nNumModel; nCnt++)
	{
		// �p�[�c�ւ̃|�C���^
		m_apModel[nCnt] = CHierarchy::Create();
	}
}

//========================
// �K�w���f���̎擾����
//========================
CHierarchy* CCharacter::GetHierarchy(int nIdx)
{
	if (m_apModel[nIdx] != nullptr)
	{ // ���f���̏�񂪂������ꍇ

		// ���f���̏���Ԃ�
		return m_apModel[nIdx];
	}
	else
	{ // ��L�ȊO

		// ��~
		assert(false);

		// nullptr ��Ԃ�
		return nullptr;
	}
}

//========================
// �K�w���f���̃_�u���|�C���^�̎擾����
//========================
CHierarchy** CCharacter::GetHierarchy(void)
{
	// ���f���̃_�u���|�C���^��Ԃ�
	return m_apModel;
}

//========================
// ���f���̑����̐ݒ菈��
//========================
void CCharacter::SetNumModel(const int nNum)
{
	// ���f���̑�����ݒ肷��
	m_nNumModel = nNum;
}

//========================
// ���f���̑����̎擾����
//========================
int CCharacter::GetNumModel(void) const
{
	// ���f���̑�����Ԃ�
	return m_nNumModel;
}

//========================
// ��������
//========================
CCharacter* CCharacter::Create(void)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CCharacter* pModel = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pModel == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pModel = new CCharacter(TYPE_CHARA, PRIORITY_BG);
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

	  // NULL ��Ԃ�
		return nullptr;
	}

	if (pModel != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

	  // ����������
		if (FAILED(pModel->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// ���f���̃|�C���^��Ԃ�
	return pModel;
}