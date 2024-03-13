//============================================
//
// �A�j���[�V�����w�b�_�[[anim.h]
// Author�F��������
//
//============================================
#ifndef _ANIMOBJECT_H_			//���̃}�N����`������Ă��Ȃ�������
#define _ANIMOBJECT_H_			//2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "object2D.h"

//--------------------------------------------
// �N���X(�I�u�W�F�N�g2D�A�j���[�V�����N���X)
//--------------------------------------------
class CAnim : public CObject2D
{
public:			// �N�ł��A�N�Z�X�ł���

	CAnim();						// �R���X�g���N�^
	CAnim(CObject::TYPE type, PRIORITY priority = PRIORITY_ENTITY);		// �I�[�o�[���[�h�R���X�g���N�^
	virtual ~CAnim();				// �f�X�g���N�^
	void Box(void);					// �R���X�g���N�^�̔�

	// �����o�֐�
	virtual HRESULT Init(void);		// ����������
	virtual void Uninit(void);		// �I������
	virtual void Update(void);		// �X�V����
	virtual void Draw(void);		// �`�揈��

	// �Z�b�g�E�Q�b�g�֌W
	int GetPattern(void) const;								// �p�^�[���̎擾����
	float GetTexPattern(void) const;						// �e�N�X�`���̃p�^�[���̎擾����
	void SetAnim(const int nCount, const int nPattern);		// �A�j���[�V�����̐ݒ菈��

	// �ÓI�����o�֐�
	static CAnim* Create(const CObject::TYPE type, const PRIORITY priority);		// �A�j���[�V�����̐�������

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	int m_nCounter;					// �A�j���[�V�����J�E���^�[
	int m_nReplayCount;				// �Đ��J�E���g
	int m_nPattern;					// �A�j���[�V�����p�^�[��
	int m_nReplayPattern;			// �Đ��p�^�[��
	float m_fTexPattern;			// �e�N�X�`���̃p�^�[��
};

#endif