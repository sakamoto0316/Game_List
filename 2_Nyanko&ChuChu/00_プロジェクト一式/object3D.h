//===================================
//
// �I�u�W�F�N�g3D�w�b�_�[[object3D.h]
// Author ��������
//
//===================================
#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include "object.h"

//--------------------------------------------
// �N���X(�I�u�W�F�N�g3D�N���X)
//--------------------------------------------
class CObject3D : public CObject
{
public:			// �N�ł��A�N�Z�X�ł���

	CObject3D();						// �R���X�g���N�^
	CObject3D(CObject::TYPE type, PRIORITY priority = PRIORITY_ENTITY);		// �I�[�o�[���[�h�R���X�g���N�^
	virtual ~CObject3D();				// �f�X�g���N�^
	void Box(void);						// �R���X�g���N�^�̔�

	// �����o�֐�
	virtual HRESULT Init(void);			// ����������
	virtual void Uninit(void);			// �I������
	virtual void Update(void);			// �X�V����
	virtual void Draw(void);			// �`�揈��

	void DrawLightOff(void);	// �`�揈��(���C�e�B���O����)

	void BindTexture(int nIdx);				// �e�N�X�`���̊��蓖�ď���

	// ���_����n
	void SetVertex(void);									// ���_���̐ݒ�
	void SetVertexHardCoding(const D3DXVECTOR3& VtxMax, const D3DXVECTOR3& VtxMin);			// ���_���̐ݒ�(���ߑł�)
	void SetVertexElev(float fHeight);						// �N���̂��钸�_���̐ݒ�
	void SetVtxColor(const D3DXCOLOR& col);					// ���_�J���[�̐ݒ菈��
	void SetVtxTextureWidth(const D3DXVECTOR2& size);		// ���_�e�N�X�`���̐ݒ菈��(�c�̈��Ԋu�̃e�N�X�`���z��)
	void SetVtxTextureHeight(const D3DXVECTOR2& size);		// ���_�e�N�X�`���̐ݒ菈��(���̈��Ԋu�̃e�N�X�`���z��)

	// �Z�b�g�E�Q�b�g�֌W
	void SetPos(const D3DXVECTOR3& pos);	// �ʒu�ݒ菈��
	D3DXVECTOR3 GetPos(void) const;			// �ʒu�擾����

	void SetPosOld(const D3DXVECTOR3& posOld);	// �O��̈ʒu�ݒ菈��
	D3DXVECTOR3 GetPosOld(void) const;			// �O��̈ʒu�擾����

	void SetRot(const D3DXVECTOR3& rot);	// �����ݒ菈��
	D3DXVECTOR3 GetRot(void) const;			// �����擾����

	void SetSize(const D3DXVECTOR3& size);	// �T�C�Y�ݒ菈��
	D3DXVECTOR3 GetSize(void) const;		// �T�C�Y�擾����

	D3DXMATRIX GetMatrix(void) const;		// �}�g���b�N�X�̎擾����

	int GetTexIdx(void) const;				// �e�N�X�`���̃C���f�b�N�X�̎擾����

	// �ÓI�����o�֐�
	static CObject3D* Create(const TYPE type, const PRIORITY priority);		// ��������

	float ElevationCollision(const D3DXVECTOR3 pos);	// �N���̂���|���S���̓����蔻��

private:

	// �����o�ϐ�
	D3DXVECTOR3 m_pos;							// �ʒu
	D3DXVECTOR3 m_posOld;						// �O��̈ʒu
	D3DXVECTOR3 m_rot;							// ����
	D3DXVECTOR3 m_size;							// �T�C�Y
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// ���_�o�b�t�@�̃|�C���^
	D3DXMATRIX m_mtxWorld;						// ���[���h�}�g���b�N�X
	int m_nTexIdx;								// �e�N�X�`���̃C���f�b�N�X
};

#endif