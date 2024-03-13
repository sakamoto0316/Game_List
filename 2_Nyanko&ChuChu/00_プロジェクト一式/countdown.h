//===================================
//
// �J�E���g�_�E���w�b�_�[[countdown.h]
// Author ��������
//
//===================================
#ifndef _COUNTDOWN_H_
#define _COUNTDOWN_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "number.h"

//-----------------------------------
// �N���X��`(�J�E���g�_�E��)
//-----------------------------------
class CCountdown : public CNumber
{
public:			// �N�ł��A�N�Z�X�ł���

	CCountdown();			// �R���X�g���N�^
	~CCountdown();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const int nCount, bool bEnd);					// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CCountdown* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const int nCount, bool bEnd);		// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void Calculate(void);		// �v�Z����
	void Cycle(void);			// ��]����
	void Scaling(void);			// �g�又��

	// �����o�ϐ�
	D3DXVECTOR3 m_sizeDest;		// �ړI�̃T�C�Y
	D3DXVECTOR3 m_sizeInit;		// �����T�C�Y
	int m_nFrame;				// �o�߃t���[����
	int m_nSecond;				// �b��
	int m_nProgressCount;		// �o�߂�����J�E���g
	bool m_bEnd;				// �I����
};

#endif