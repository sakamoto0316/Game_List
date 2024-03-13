//===================================
//
// �r���{�[�h�w�b�_�[[billboard.h]
// Author ��������
//
//===================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "object3D.h"

//--------------------------------------------
// �N���X(�r���{�[�h�N���X)
//--------------------------------------------
class CBillboard : public CObject
{
public:			// �N�ł��A�N�Z�X�ł���

	CBillboard();						// �R���X�g���N�^
	CBillboard(CObject::TYPE type, PRIORITY priority = PRIORITY_ENTITY);		// �I�[�o�[���[�h�R���X�g���N�^
	virtual ~CBillboard();				// �f�X�g���N�^
	void Box(void);						// �R���X�g���N�^�̔�

	// �����o�֐�
	virtual HRESULT Init(void);			// ����������
	virtual void Uninit(void);			// �I������
	virtual void Update(void);			// �X�V����
	virtual void Draw(void);			// �`�揈��

	void DrawLightOff(void);			// �`�揈��(���C�e�B���O����)
	void DrawShift(const D3DXVECTOR3 shift);				// �`�揈��(�ʒu���炵)

	void BindTexture(int nIdx);			// �e�N�X�`���̊��蓖�ď���

	// ���_���֌W
	void SetVertex(void);										// ���_���̐ݒ�
	void SetVtxPosUnder(void);									// ���_���̐ݒ�(�����_)
	void SetVtxAnim(const float fTex, const int nPattern);		// �A�j���[�V�����̐ݒ�
	void SetVtxAnimRev(const float fTex, const int nPattern);	// �A�j���[�V�����̐ݒ�(���])
	void SetVtxColor(D3DXCOLOR col);							// ���_�J���[�̐ݒ�

	// �Z�b�g�E�Q�b�g�֌W
	void SetPos(const D3DXVECTOR3& pos);	// �ʒu�ݒ菈��
	D3DXVECTOR3 GetPos(void) const;			// �ʒu�擾����

	void SetPosOld(const D3DXVECTOR3& posOld);	// �O��̈ʒu�ݒ菈��
	D3DXVECTOR3 GetPosOld(void) const;			// �O��̈ʒu�擾����

	void SetSize(const D3DXVECTOR3& size);	// �T�C�Y�ݒ菈��
	D3DXVECTOR3 GetSize(void) const;		// �T�C�Y�擾����

	int GetTexIdx(void) const;				// �e�N�X�`���̃C���f�b�N�X�̎擾����

	// �ÓI�����o�֐�
	static CBillboard* Create(const TYPE type, const PRIORITY priority);	// ��������

private:

	// �����o�ϐ�
	D3DXVECTOR3 m_pos;							// �ʒu
	D3DXVECTOR3 m_posOld;						// �O��̈ʒu
	D3DXVECTOR3 m_size;							// �T�C�Y
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// ���_�o�b�t�@�̃|�C���^
	D3DXMATRIX m_mtxWorld;						// ���[���h�}�g���b�N�X
	int m_nTexIdx;								// �e�N�X�`���̃C���f�b�N�X
};

//--------------------------------------------
// �N���X(�r���{�[�h�N���X)
//--------------------------------------------
class CBillboardAnim : public CBillboard
{
public:			// �N�ł��A�N�Z�X�ł���

	CBillboardAnim();						// �R���X�g���N�^
	CBillboardAnim(CObject::TYPE type, PRIORITY priority = PRIORITY_ENTITY);		// �I�[�o�[���[�h�R���X�g���N�^
	virtual ~CBillboardAnim();				// �f�X�g���N�^
	void Box(void);							// �R���X�g���N�^�̔�

	// �����o�֐�
	virtual HRESULT Init(void);			// ����������
	virtual void Uninit(void);			// �I������
	virtual void Update(void);			// �X�V����
	virtual void Draw(void);			// �`�揈��

	void DrawLightOff(void);	// �`�揈��(���C�e�B���O����)

	// �Z�b�g�E�Q�b�g�֌W
	int GetPattern(void) const;								// �p�^�[���̎擾����
	float GetTexPattern(void) const;						// �e�N�X�`���̃p�^�[���̎擾����
	void SetAnim(const int nCount, const int nPattern);		// �A�j���[�V�����̐ݒ菈��

	// �ÓI�����o�֐�
	static CBillboardAnim* Create(void);	// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	int m_nCounter;					// �A�j���[�V�����J�E���^�[
	int m_nReplayCount;				// �Đ��J�E���g
	int m_nPattern;					// �A�j���[�V�����p�^�[��
	int m_nReplayPattern;			// �Đ��p�^�[��
	float m_fTexPattern;			// �e�N�X�`���̃p�^�[��
};

#endif