//============================================
//
// �h�[�i�c2D�w�b�_�[[donut2D.h]
// Author�F��������
//
//============================================
#ifndef _DONUT2D_H_		//���̃}�N����`������Ă��Ȃ�������
#define _DONUT2D_H_		//2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "object.h"

//--------------------------------------------
// �N���X(�h�[�i�c2D�N���X)
//--------------------------------------------
class CDonut2D : public CObject
{
public:			// �N�ł��A�N�Z�X�ł���

	CDonut2D();						// �R���X�g���N�^
	CDonut2D(CObject::TYPE type, PRIORITY priority = PRIORITY_UI);		// �I�[�o�[���[�h�R���X�g���N�^
	virtual ~CDonut2D();			// �f�X�g���N�^
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

	void SetSize(const float size);			// �T�C�Y�ݒ菈��
	float GetSize(void) const;				// �T�C�Y�擾����

	void SetDistance(const float fDist);	// �����̐ݒ菈��
	float GetDistance(void) const;			// �����̎擾����

	void SetDivi(const int nDivi);			// �������̐ݒ菈��
	int GetDivi(void) const;				// �������̎擾����

	void SetNumVtx(void);					// �����_���̐ݒ菈��
	int GetNumVtx(void) const;				// �����_���̎擾����

	int GetTexIdx(void) const;				// �e�N�X�`���̃C���f�b�N�X�̎擾����

	// �ÓI�����o�֐�
	static CDonut2D* Create(const D3DXVECTOR3& pos, const float fSize, const float fDist, const int nDivi);		// ��������

private:

	// �����o�ϐ�
	D3DXVECTOR3 m_pos;							// �ʒu
	D3DXVECTOR3 m_posOld;						// �O��̈ʒu
	float m_fSize;								// �T�C�Y
	float m_fDistance;							// ����
	int m_nDivi;								// ������
	int m_nNumVtx;								// �����_��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// ���_�o�b�t�@�̃|�C���^
	int m_nTexIdx;								// �e�N�X�`���̃C���f�b�N�X
};

#endif