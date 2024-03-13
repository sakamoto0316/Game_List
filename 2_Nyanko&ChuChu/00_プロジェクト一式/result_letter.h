//===================================
//
// ���ʂ̕����̏���[result_letter.h]
// Author ����������
//
//===================================
#ifndef _RESULT_LETTER_H_
#define _RESULT_LETTER_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"
#include "objectX.h"

//-----------------------------------
// �N���X(���U���g��3D�e�L�X�g�N���X)
//-----------------------------------
class CResultLetter : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	CResultLetter();			// �R���X�g���N�^
	~CResultLetter();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const CXFile::TYPE& type);		// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CResultLetter* Create(const D3DXVECTOR3& pos, const CXFile::TYPE& type);		// ��������

private:		// ���������A�N�Z�X�ł���

};

#endif