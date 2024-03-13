//===================================
//
// �I�u�W�F�N�g3D�t�@���w�b�_�[[object3Dfan.h]
// Author ��������
//
//===================================
#ifndef _OBJECT3DFAN_H_
#define _OBJECT3DFAN_H_

#include "object.h"

//--------------------------------------------
// �N���X(�I�u�W�F�N�g3D�N���X)
//--------------------------------------------
class CObject3DFan : public CObject
{
public:			// �N�ł��A�N�Z�X�ł���

	CObject3DFan();			// �R���X�g���N�^
	CObject3DFan(CObject::TYPE type, PRIORITY priority = PRIORITY_PLAYER);			// �I�[�o�[���[�h�R���X�g���N�^
	virtual ~CObject3DFan();		// �f�X�g���N�^
	void Box(void);			// �R���X�g���N�^�̔�

	// �����o�֐�
	virtual HRESULT Init(void);		// ����������
	virtual void Uninit(void);		// �I������
	virtual void Update(void);		// �X�V����
	virtual void Draw(void);		// �`�揈��

	void BindTexture(int nIdx);		// �e�N�X�`���̊��蓖�ď���

	// ���_����n
	void SetVertex(void);						// ���_���̐ݒ�
	void SetVtxColor(const D3DXCOLOR& col);		// ���_�J���[�̐ݒ菈��
	void SetVtxColor(const D3DXCOLOR& normalCol, const D3DXCOLOR& rezCol, int nEndRezVtx);		// ���_�J���[�ׂ̍����ݒ菈��

	// �Z�b�g�E�Q�b�g�֌W
	void SetPos(const D3DXVECTOR3& pos);	// �ʒu�ݒ菈��
	D3DXVECTOR3 GetPos(void) const;			// �ʒu�擾����

	void SetPosOld(const D3DXVECTOR3& posOld);	// �O��̈ʒu�ݒ菈��
	D3DXVECTOR3 GetPosOld(void) const;			// �O��̈ʒu�擾����

	void SetRot(const D3DXVECTOR3& rot);	// �����ݒ菈��
	D3DXVECTOR3 GetRot(void) const;			// �����擾����

	void SetSize(const D3DXVECTOR3& size);	// �T�C�Y�ݒ菈��
	D3DXVECTOR3 GetSize(void) const;		// �T�C�Y�擾����

	void SetNumAngle(const int nNum);		// �p�x�̑����̐ݒ菈��
	int GetNumAngle(void) const;			// �p�x�̑����̎擾����

	void SetRadius(const float fRadius);	// ���a�̐ݒ菈��
	float GetRadius(void) const;			// ���a�̎擾����

	void SetColor(const D3DXCOLOR col);		// �F�̐ݒ菈��
	D3DXCOLOR GetColor(void) const;			// �F�̎擾����

	// �ÓI�����o�֐�
	static CObject3DFan* Create(void);			// ��������

private:

	// �����o�ϐ�
	D3DXVECTOR3 m_pos;							// �ʒu
	D3DXVECTOR3 m_posOld;						// �O��̈ʒu
	D3DXVECTOR3 m_rot;							// ����
	D3DXVECTOR3 m_size;							// �T�C�Y
	D3DXCOLOR m_col;							// �F
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// ���_�o�b�t�@�̃|�C���^
	D3DXMATRIX m_mtxWorld;						// ���[���h�}�g���b�N�X
	int m_nNumAngle;							// �p�x�̐�
	float m_fRadius;							// ���a
	int m_nTexIdx;								// �e�N�X�`���̃C���f�b�N�X
};

#endif