//============================================
//
// 2D���b�V���w�b�_�[[objectmesh2D.h]
// Author�F��������
//
//============================================
#ifndef _OBJECTMESH2D_H_		//���̃}�N����`������Ă��Ȃ�������
#define _OBJECTMESH2D_H_		//2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "object.h"

//--------------------------------------------
// �N���X(�I�u�W�F�N�g���b�V��2D�N���X)
//--------------------------------------------
class CMesh2D : public CObject
{
public:			// �N�ł��A�N�Z�X�ł���

	CMesh2D();						// �R���X�g���N�^
	CMesh2D(CObject::TYPE type, PRIORITY priority = PRIORITY_UI);		// �I�[�o�[���[�h�R���X�g���N�^
	virtual ~CMesh2D();				// �f�X�g���N�^
	void Box(void);					// �R���X�g���N�^�̔�

	// �����o�֐�
	virtual HRESULT Init(void);		// ����������
	virtual void Uninit(void);		// �I������
	virtual void Update(void);		// �X�V����
	virtual void Draw(void);		// �`�揈��

	void BindTexture(int nIdx);				// �e�N�X�`���̊��蓖�ď���

	// ���_����n
	void SetVertex(void);										// ���_���̐ݒ�
	void SetVtxColor(const D3DXCOLOR& col);						// ���_�̐F�ݒ菈��
	void SetVtxColor(const int nVtx, const D3DXCOLOR& col1, const D3DXCOLOR& col2);			// ���_�̐F(���͈�)�ݒ菈��
	void SetVtxTexture(void);									// �e�N�X�`�����W�̐ݒ菈��
	void SetVertexAll(void);									// �S�Ă̒��_���̐ݒ�

	// �Z�b�g�E�Q�b�g�֌W
	void SetPos(const D3DXVECTOR3& pos);	// �ʒu�ݒ菈��
	D3DXVECTOR3 GetPos(void) const;			// �ʒu�擾����

	void SetPosOld(const D3DXVECTOR3& posOld);	// �O��̈ʒu�ݒ菈��
	D3DXVECTOR3 GetPosOld(void) const;			// �O��̈ʒu�擾����

	void SetSize(const D3DXVECTOR3& size);		// �T�C�Y�ݒ菈��
	D3DXVECTOR3 GetSize(void) const;			// �T�C�Y�擾����

	void SetDivi(const int nDivi);			// �������̐ݒ菈��
	int GetDivi(void) const;				// �������̎擾����

	void SetNumVtx(void);					// �����_���̐ݒ菈��
	int GetNumVtx(void) const;				// �����_���̎擾����

	int GetTexIdx(void) const;				// �e�N�X�`���̃C���f�b�N�X�̎擾����

	// �ÓI�����o�֐�
	static CMesh2D* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const int nDivi);		// ��������

private:

	// �����o�ϐ�
	D3DXVECTOR3 m_pos;							// �ʒu
	D3DXVECTOR3 m_posOld;						// �O��̈ʒu
	D3DXVECTOR3 m_size;							// �T�C�Y
	int m_nDivi;								// ������
	int m_nNumVtx;								// �����_��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// ���_�o�b�t�@�̃|�C���^
	int m_nTexIdx;								// �e�N�X�`���̃C���f�b�N�X
};

#endif