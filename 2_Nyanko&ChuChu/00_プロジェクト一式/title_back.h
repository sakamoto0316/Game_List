//===================================
//
// �^�C�g���̔w�i�w�b�_�[[title_back.h]
// Author ��������
//
//===================================
#ifndef _TITLE_BACK_H_
#define _TITLE_BACK_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "object3D.h"

//-----------------------------------
// �N���X��`(�^�C�g���̔w�i)
//-----------------------------------
class CTitleBack :public CObject3D
{
public:

	CTitleBack();		// �R���X�g���N�^
	~CTitleBack();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);	// ����������
	void Uninit(void);	// �I������
	void Update(void);	// �X�V����
	void Draw(void);	// �`�揈��

	void SetData(void);	// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CTitleBack* Create(void);	// ��������

private:
};

#endif