//============================================
//
// �X�R�A�w�b�_�[[score.h]
// Author�F��������
//
//============================================
#ifndef _SCORE_H_					// ���̃}�N����`������Ă��Ȃ�������
#define _SCORE_H_					// 2�d�C���N���[�h�h�~�̃}�N�����`����
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "number.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define MAX_SCORE_DIGIT		(8)			// �X�R�A�̌���

//--------------------------------------------
// �N���X��`(�X�R�A)
//--------------------------------------------
class CScore : public CObject
{
public:				// �N�ł��A�N�Z�X�ł���

	CScore();						// �R���X�g���N�^
	CScore(CObject::TYPE type, CObject::PRIORITY priority = PRIORITY_UI);		// �I�[�o�[���[�h�R���X�g���N�^
	virtual ~CScore();				// �f�X�g���N�^
	void Box(void);					// �R���X�g���N�^�̔�

	// �����o�֐�
	virtual HRESULT Init(void);		// ����������
	virtual void Uninit(void);		// �I������
	virtual void Update(void);		// �X�V����
	virtual void Draw(void);		// �`�揈��

	virtual void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& size, const float fShift);		// ���̐ݒ菈��

	void Calculate(void);			// �v�Z����

	// �Z�b�g�E�Q�b�g�֌W
	void SetScore(const int nScore);		// �X�R�A�̐ݒ菈��
	int GetScore(void) const;				// �X�R�A�̎擾����
	void SetScoreDisp(const int nScore);	// �\���X�R�A�̐ݒ菈��
	int GetScoreDisp(void) const;			// �\���X�R�A�̎擾����
	void AddScore(const int nScore);		// �X�R�A�̉��Z����
	CNumber* GetNumber(int nID) const;		// ���l�̎擾����

private:			// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CNumber *m_apNumber[MAX_SCORE_DIGIT];		// �ԍ��̏��
	int m_nScore;			// �X�R�A
	int m_nDispScore;		// �\���p�X�R�A
};

#endif