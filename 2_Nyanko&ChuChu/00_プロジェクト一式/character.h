//============================================================
//
// �L�����N�^�[�w�b�_�[ [character.h]
// Author�F��������
//
//============================================================
#ifndef _CHARACTER_H_	// ���̃}�N����`������Ă��Ȃ��ꍇ
#define _CHARACTER_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

//************************************************************
// �C���N���[�h�t�@�C��
//************************************************************
#include "object.h"
#include "objectX.h"

#define MAX_PARTS		(20)				// �p�[�c�̍ő吔

//------------------------------------------------------------
// �N���X��`(�K�w�\���̃��f��)
//------------------------------------------------------------
class CHierarchy
{
public:			// �N�ł��A�N�Z�X�ł���

	CHierarchy();			// �R���X�g���N�^
	~CHierarchy();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);			// ����������
	void Uninit(void);			// �I������
	void Update(void);			// �X�V����
	void Draw(void);			// �`�揈��
	void Draw(D3DXCOLOR col);	// �`�揈��(�F����)
	void DrawShadow(void);		// ���f���e�̕`�揈��
	void Draw(float fAlpha);	// �`�揈��(�����x����)

	// �Z�b�g�E�Q�b�g�֐�
	void SetPos(const D3DXVECTOR3& pos);	// �ʒu�ݒ菈��
	D3DXVECTOR3 GetPos(void) const;			// �ʒu�擾����

	void SetPosOld(const D3DXVECTOR3& posOld);	// �O��̈ʒu�ݒ菈��
	D3DXVECTOR3 GetPosOld(void) const;			// �O��̈ʒu�擾����

	void SetRot(const D3DXVECTOR3& rot);	// �����ݒ菈��
	D3DXVECTOR3 GetRot(void) const;			// �����擾����

	void SetScale(const D3DXVECTOR3& scale);	// �g�嗦�ݒ菈��
	D3DXVECTOR3 GetScale(void) const;			// �g�嗦�擾����

	void SetFileData(const CXFile::TYPE type);						// �f�[�^�̐ݒ菈��
	void SetFileData(const CXFile::SXFile filaData);				// �f�[�^�̐ݒ菈��(�t�@�C���f�[�^�̐ݒ��)

	D3DXMATRIX GetMatrix(void) const;			// �}�g���b�N�X�̎擾����

	CXFile::SXFile GetFileData(void);			// X�t�@�C���̃f�[�^�̎擾����

	void SetParent(CHierarchy* pModel);			// �e�̐ݒ菈��
	CHierarchy* GetParent(void) const;			// �e�̎擾����

	// �ÓI�����o�֐�
	static CHierarchy* Create(void);			// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	D3DXVECTOR3		m_pos;			// �ʒu
	D3DXVECTOR3		m_posOld;		// �O��̈ʒu
	D3DXVECTOR3		m_rot;			// ����
	D3DXVECTOR3		m_scale;		// �g�嗦
	D3DXMATRIX		m_mtxWorld;		// ���[���h�}�g���b�N�X
	CXFile::SXFile	m_XFileData;	// X�t�@�C���̃f�[�^
	CHierarchy*		m_apParent;		// �e���f���ւ̃|�C���^
};

//------------------------------------------------------------
// �N���X��`(���f��)
//------------------------------------------------------------
class CCharacter : public CObject
{
public:			// �N�ł��A�N�Z�X�ł���

	CCharacter();			// �R���X�g���N�^
	CCharacter(CObject::TYPE type, PRIORITY priority = PRIORITY_ENTITY);		// �I�[�o�[���[�h�R���X�g���N�^
	virtual ~CCharacter();	// �f�X�g���N�^
	void Box(void);			// �R���X�g���N�^�̔�

	// �����o�֐�
	virtual HRESULT Init(void);			// ����������
	virtual void Uninit(void);			// �I������
	virtual void Update(void);			// �X�V����
	virtual void Draw(void);			// �`�揈��

	void Draw(D3DXCOLOR col);	// �`�揈��(�F����)
	void Draw(D3DXCOLOR* col);	// �`�揈��(�����x����)
	void DrawShadow(void);		// ���f���e�̕`�揈��
	void Draw(float fAlpha);	// �`�揈��(�����x����)

	// �Z�b�g�E�Q�b�g�֐�
	void SetPos(const D3DXVECTOR3& pos);	// �ʒu�ݒ菈��
	D3DXVECTOR3 GetPos(void) const;			// �ʒu�擾����

	void SetPosOld(const D3DXVECTOR3& posOld);	// �O��̈ʒu�ݒ菈��
	D3DXVECTOR3 GetPosOld(void) const;			// �O��̈ʒu�擾����

	void SetRot(const D3DXVECTOR3& rot);	// �����ݒ菈��
	D3DXVECTOR3 GetRot(void) const;			// �����擾����

	void SetMove(const D3DXVECTOR3& move);		// �ړ��ʐݒ菈��
	D3DXVECTOR3 GetMove(void) const;			// �ړ��ʎ擾����

	void SetScale(const D3DXVECTOR3& scale);	// �g�嗦�ݒ菈��
	D3DXVECTOR3 GetScale(void) const;			// �g�嗦�擾����

	D3DXMATRIX GetMatrix(void) const;			// �}�g���b�N�X�̎擾����
	D3DXMATRIX* GetMatrixP(void);				// �}�g���b�N�X�̎擾����

	void SetData(void);							// �f�[�^�̐ݒ菈��

	CHierarchy* GetHierarchy(int nIdx);			// �K�w���f���̎擾����
	CHierarchy** GetHierarchy(void);			// �K�w���f���̃_�u���|�C���^�̎擾����

	void SetNumModel(const int nNum);			// ���f���̑����̐ݒ菈��
	int GetNumModel(void) const;				// ���f���̑����̎擾����

	// �ÓI�����o�֐�
	static CCharacter* Create(void);			// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	D3DXVECTOR3		m_pos;				// �ʒu
	D3DXVECTOR3		m_posOld;			// �O��̈ʒu
	D3DXVECTOR3		m_rot;				// ����
	D3DXVECTOR3		m_move;				// �ړ���
	D3DXVECTOR3		m_scale;			// �g�嗦
	D3DXMATRIX		m_mtxWorld;			// ���[���h�}�g���b�N�X
	CHierarchy* m_apModel[MAX_PARTS];	// ���f���̏��
	int m_nNumModel;					// ���f���̑���
};

#endif