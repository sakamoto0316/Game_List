//===================================
//
// �^�C�g���̕ǃw�b�_�[[title_wall.h]
// Author ��������
//
//===================================
#ifndef _TITLE_WALL_H_
#define _TITLE_WALL_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �N���X��`(�^�C�g���̕�)
//-----------------------------------
class CTitleWall : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	CTitleWall();			// �R���X�g���N�^
	~CTitleWall();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(void);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CTitleWall* Create(void);	// ��������

private:		// ���������A�N�Z�X�ł���

};

#endif