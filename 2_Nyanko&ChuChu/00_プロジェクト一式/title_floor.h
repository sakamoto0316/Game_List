//===================================
//
// �^�C�g���̏��w�b�_�[[title_floor.h]
// Author ��������
//
//===================================
#ifndef _TITLE_FLOOR_H_	//���̃}�N������`����Ă��Ȃ����
#define _TITLE_FLOOR_H_	//��d�C���N���[�h�h�~�}�N��

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "Object3D.h"

//-----------------------------------
// �N���X��`(CTitleFloor)
//-----------------------------------
class CTitleFloor :public CObject3D
{
public:

	CTitleFloor();			// �R���X�g���N�^
	~CTitleFloor();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(void);		// ���̐ݒ菈��

	// �ÓI�����o�ϐ�
	static CTitleFloor* Create(void);		// ��������

private:

};
#endif