//===========================================
//
// ���포���w�b�_�[[weapon_cage.h]
// Author ��������
//
//===========================================
#ifndef _WEAPON_CAGE_H_
#define _WEAPON_CAGE_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include "model.h"

//-------------------------------------------
// �N���X��`(���포��)
//-------------------------------------------
class CWeaponCage : public CModel
{
public:		// �N�ł��A�N�Z�X�ł���

	CWeaponCage();			// �R���X�g���N�^
	~CWeaponCage();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);		// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CWeaponCage* Create(const D3DXVECTOR3& pos);		// ��������

private:		// ���������A�N�Z�X�ł���

};

#endif