//============================================
//
// �X�N���[���I�u�W�F�N�g�w�b�_�[[scroll.h]
// Author�F��������
//
//============================================
#ifndef _SCROLLOBJECT_H_//���̃}�N����`������Ă��Ȃ�������
#define _SCROLLOBJECT_H_//2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "object2D.h"

//=========================================
// �}�N����`
//=========================================
#define BG_MAX					(1.0f)		// �w�i�̍ő�l
#define BG_INIT					(0.0f)		// �w�i�̍ŏ��l

//--------------------------------------------
// �N���X(�I�u�W�F�N�g2D�X�N���[���N���X)
//--------------------------------------------
class CScroll : public CObject2D
{
public:			// �N�ł��A�N�Z�X�ł���

	CScroll();						// �R���X�g���N�^
	CScroll(CObject::TYPE type, PRIORITY priority = PRIORITY_ENTITY);	// �I�[�o�[���[�h�R���X�g���N�^
	virtual ~CScroll();				// �f�X�g���N�^
	void Box(void);					// �R���X�g���N�^�̔�

	// �����o�֐�
	virtual HRESULT Init(void);		// ����������
	virtual void Uninit(void);		// �I������
	virtual void Update(void);		// �X�V����
	virtual void Draw(void);		// �`�揈��

	// �Q�b�g�E�Z�b�g�֌W
	void SetTex(const D3DXVECTOR2& tex);			// �e�N�X�`�����W�̐ݒ菈��
	D3DXVECTOR2 GetTex(void) const;					// �e�N�X�`�����W�̎擾����
	void SetSpeed(const D3DXVECTOR2& speed);		// ���x�̐ݒ菈��

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	D3DXVECTOR2 m_tex;		// �e�N�X�`�����W
	D3DXVECTOR2 m_speed;	// ���x
};

#endif