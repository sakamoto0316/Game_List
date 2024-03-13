//============================================
//
// ���ԃw�b�_�[[time.h]
// Author�F��������
//
//============================================
#ifndef _TIME_H_					// ���̃}�N����`������Ă��Ȃ�������
#define _TIME_H_					// 2�d�C���N���[�h�h�~�̃}�N�����`����
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "number.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CObject2D;				// 2D�|���S��

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define MAX_TIME_DIGIT		(6)			// �^�C���̌���
#define MAX_TIME			(999999)	// ���Ԃ̍ő吔

//--------------------------------------------
// �N���X��`(�^�C��)
//--------------------------------------------
class CTime : public CObject
{
public:				// �N�ł��A�N�Z�X�ł���

	CTime();				// �R���X�g���N�^
	CTime(CObject::TYPE type, PRIORITY priority = PRIORITY_UI);		// �I�[�o�[���[�h�R���X�g���N�^
	virtual ~CTime();		// �f�X�g���N�^
	void Box(void);			// �R���X�g���N�^�̔�

	// �����o�֐�
	virtual HRESULT Init(void);		// ����������
	virtual void Uninit(void);		// �I������
	virtual void Update(void);		// �X�V����
	virtual void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& size, const D3DXVECTOR3& dotSize, const float fShift);				// ���̐ݒ菈��

	void SetNumber(void);	// 1�����Ƃ̐��l�ݒ菈��
	void SetTexture(void);	// 1�����Ƃ̃e�N�X�`���̐ݒ菈��

	// �Z�b�g�E�Q�b�g�֌W
	void SetTotalTime(const DWORD time);	// �o�ߎ��Ԃ̐ݒ菈��
	DWORD GetTotalTime(void) const;			// �o�ߎ��Ԃ̎擾����

	CNumber* GetNumber(const int nID);		// �ԍ����̎擾����

	CObject2D* GetDot(void);				// �_�̎擾����

	// �ÓI�����o�ϐ�
	static CTime* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& size, const D3DXVECTOR3& dotSize, const float fShift);		// ��������

private:			// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CNumber* m_apNumber[MAX_TIME_DIGIT];	// �ԍ��̏��
	CObject2D* m_pDot;						// �^�C���̓_
	DWORD m_TotalTime;						// ���v����
};

#endif