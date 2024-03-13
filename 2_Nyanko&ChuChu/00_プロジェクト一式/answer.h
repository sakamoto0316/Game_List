//===================================
//
// �Ԏ����͂̃��A�N�V�����w�b�_�[[sample.h]
// Author ��{�ėB
//
//===================================
#ifndef _ANSWER_H_
#define _ANSWER_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"
#include "tutorial.h"

class CObject2D;

//-----------------------------------
// �N���X��`(�Ԏ����͂̃��A�N�V����)
//-----------------------------------
class CAnswer : public CObject/*�e�N���X*/
{
public:			// �N�ł��A�N�Z�X�ł���

	CAnswer();			// �R���X�g���N�^
	~CAnswer();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(void/*����*/);		// ���̐ݒ菈��

	void SetAnswer(bool Set, int Idx) { m_abPressAnswer[Idx] = Set; }
	bool GetAnswer(int Idx) { return m_abPressAnswer[Idx]; }

	// �ÓI�����o�֐�
	static CAnswer* Create(void/*����*/);		// ��������

private:		// ���������A�N�Z�X�ł���
	CObject2D *m_apAnswer[4];
	bool m_abPressAnswer[4];
	CObject2D *m_apPlayerID[4];

	D3DXCOLOR m_Color;
};

#endif