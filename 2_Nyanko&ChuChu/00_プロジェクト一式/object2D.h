//============================================
//
// �I�u�W�F�N�g2D�w�b�_�[[object2D.h]
// Author�F��������
//
//============================================
#ifndef _OBJECT2D_H_//���̃}�N����`������Ă��Ȃ�������
#define _OBJECT2D_H_//2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "object.h"

//--------------------------------------------
// �N���X(�I�u�W�F�N�g2D�N���X)
//--------------------------------------------
class CObject2D : public CObject
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(TYPE)
	enum TYPE
	{
		TYPE_NONE = 0,		// �ʏ��2D�|���S��
		TYPE_ANIM,			// �A�j���[�V����
		TYPE_SCROLL,		// �X�N���[��(�w�i���Ɏg�p)
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	CObject2D();						// �R���X�g���N�^
	CObject2D(CObject::TYPE type, PRIORITY priority = PRIORITY_ENTITY);		// �I�[�o�[���[�h�R���X�g���N�^
	virtual ~CObject2D();				// �f�X�g���N�^
	void Box(void);						// �R���X�g���N�^�̔�

	// �����o�֐�
	virtual HRESULT Init(void);		// ����������
	virtual void Uninit(void);		// �I������
	virtual void Update(void);		// �X�V����
	virtual void Draw(void);		// �`�揈��

	void BindTexture(int nIdx);				// �e�N�X�`���̊��蓖�ď���

	// ���_����n
	void SetVertex(void);										// ���_���̐ݒ�
	void SetVertexRot(void);									// ���_���̐ݒ�(�X���L��o�[�W����)
	void SetVtxWidthGage(void);									// ���_���̐ݒ�(���Q�[�W�\���o�[�W����)
	void SetVtxUnderHeightGage(void);							// ���_���̐ݒ�(�����S�Q�[�W�\���o�[�W����)
	void SetVtxHardCoding(const D3DXVECTOR3& LeftUp, const D3DXVECTOR3& RightUp, const D3DXVECTOR3& LeftDown, const D3DXVECTOR3& RightDown);	// ���_���̐ݒ�(�x�^�ł�)
	void SetVtxColor(const D3DXCOLOR& col);						// ���_�̐F�ݒ菈��
	void SetVtxTexture(void);									// �e�N�X�`���̐ݒ�
	void SetVtxTextureRev(void);								// ���]�e�N�X�`���̐ݒ�
	void SetVtxTextureAnim(float fTexPattern, int nPattern);	// �e�N�X�`���̐ݒ�(�A�j���[�V�����o�[�W����)
	void SetVtxTextureScroll(D3DXVECTOR2& tex);					// �e�N�X�`���̐ݒ�(�X�N���[���o�[�W����)
	void SetVtxTextureWidth(const float tex);					// �e�N�X�`���̐ݒ�(���̃e�N�X�`���C�Ӑݒ�)
	void SetVtxTextureUnderHeight(const float tex);				// �e�N�X�`���̐ݒ�(�����S�̏c�̃e�N�X�`���C�Ӑݒ�)
	void SetVertexAll(void);									// �S�Ă̒��_���̐ݒ�

	// �Z�b�g�E�Q�b�g�֌W
	void SetPos(const D3DXVECTOR3& pos);	// �ʒu�ݒ菈��
	D3DXVECTOR3 GetPos(void) const;			// �ʒu�擾����

	void SetPosOld(const D3DXVECTOR3& posOld);	// �O��̈ʒu�ݒ菈��
	D3DXVECTOR3 GetPosOld(void) const;			// �O��̈ʒu�擾����

	void SetRot(const D3DXVECTOR3& rot);	// �����ݒ菈��
	D3DXVECTOR3 GetRot(void) const;			// �����擾����

	void SetSize(const D3DXVECTOR3& size);	// �T�C�Y�ݒ菈��
	D3DXVECTOR3 GetSize(void) const;		// �T�C�Y�擾����

	void SetLength(void);					// �����ݒ菈��
	float GetLength(void) const;			// �����ݒ菈��

	void SetAngle(void);					// �����ݒ菈��
	float GetAngle(void) const;				// �����ݒ菈��

	int GetTexIdx(void) const;				// �e�N�X�`���̃C���f�b�N�X�̎擾����
	char *GetTexName(void);					// �e�N�X�`���̖��O�̎擾����

	// �ÓI�����o�֐�
	static CObject2D* Create(const TYPE type2D, const CObject::TYPE type, const PRIORITY priority);		// ��������

protected:		// �����Ɣh���N���X�����A�N�Z�X�ł���

private:

	// �����o�ϐ�
	D3DXVECTOR3 m_pos;							// �ʒu
	D3DXVECTOR3 m_posOld;						// �O��̈ʒu
	D3DXVECTOR3 m_rot;							// ����
	D3DXVECTOR3 m_size;							// �T�C�Y
	float m_fAngle;								// ����
	float m_fLength;							// ����
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// ���_�o�b�t�@�̃|�C���^
	int m_nTexIdx;								// �e�N�X�`���̃C���f�b�N�X
};

#endif