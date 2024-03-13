//============================================================
//
// ���f���w�b�_�[ [model.h]
// Author�F��������
//
//============================================================
#ifndef _MODEL_H_	// ���̃}�N����`������Ă��Ȃ��ꍇ
#define _MODEL_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

//************************************************************
// �C���N���[�h�t�@�C��
//************************************************************
#include "object.h"
#include "objectX.h"

//------------------------------------------------------------
// �}�N����`
//------------------------------------------------------------
#define NONE_SCALE		(D3DXVECTOR3(1.0f, 1.0f, 1.0f))

//------------------------------------------------------------
// �N���X��`(���f��)
//------------------------------------------------------------
class CModel : public CObject
{
public:			// �N�ł��A�N�Z�X�ł���

	CModel();			// �R���X�g���N�^
	CModel(CObject::TYPE type, PRIORITY priority = PRIORITY_ENTITY);		// �I�[�o�[���[�h�R���X�g���N�^
	virtual ~CModel();	// �f�X�g���N�^
	void Box(void);		// �R���X�g���N�^�̔�

	// �����o�֐�
	virtual HRESULT Init(void);		// ����������
	virtual void Uninit(void);		// �I������
	virtual void Update(void);		// �X�V����
	virtual void Draw(void);		// �`�揈��

	void Draw(D3DXCOLOR col);		// �`�揈��(�F����)
	void Draw(D3DXCOLOR* col);		// �`�揈��(�����F)
	void Draw(const float fAlpha);	// �`�揈��(�����x����)
	void DrawShadow(void);			// ���f���e�̕`�揈��
	void DrawBlock(const D3DXMATERIAL* pMat);	// �G�f�B�b�g�̕`�揈��

	// �Z�b�g�E�Q�b�g�֐�
	void SetPos(const D3DXVECTOR3& pos);	// �ʒu�ݒ菈��
	D3DXVECTOR3 GetPos(void) const;			// �ʒu�擾����

	void SetPosOld(const D3DXVECTOR3& posOld);	// �O��̈ʒu�ݒ菈��
	D3DXVECTOR3 GetPosOld(void) const;			// �O��̈ʒu�擾����

	void SetRot(const D3DXVECTOR3& rot);	// �����ݒ菈��
	D3DXVECTOR3 GetRot(void) const;			// �����擾����

	void SetScale(const D3DXVECTOR3& scale);	// �g�嗦�ݒ菈��
	D3DXVECTOR3 GetScale(void) const;			// �g�嗦�擾����

	D3DXMATRIX GetMatrix(void) const;			// �}�g���b�N�X�̎擾����

	void SetFileData(const CXFile::TYPE type);						// �f�[�^�̐ݒ菈��
	void SetFileData(const CXFile::SXFile filaData);				// �f�[�^�̐ݒ菈��(�t�@�C���f�[�^�̐ݒ��)

	CXFile::SXFile GetFileData(void);			// X�t�@�C���̃f�[�^�̎擾����

	D3DXMATERIAL GetMaterial(const int nCnt);	// �}�e���A�����̎擾����

	// �ÓI�����o�֐�
	static CModel* Create(const TYPE type, const PRIORITY priority);	// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	D3DXVECTOR3		m_pos;			// �ʒu
	D3DXVECTOR3		m_posOld;		// �O��̈ʒu
	D3DXVECTOR3		m_rot;			// ����
	D3DXVECTOR3		m_scale;		// �g�嗦
	D3DXMATRIX		m_mtxWorld;		// ���[���h�}�g���b�N�X
	CXFile::SXFile	m_XFileData;	// X�t�@�C���̃f�[�^
};

#endif