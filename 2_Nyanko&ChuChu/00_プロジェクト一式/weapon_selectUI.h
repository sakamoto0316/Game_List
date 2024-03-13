//===========================================
//
// ����̑I��UI�w�b�_�[[weapon_selectUI.h]
// Author ��������
//
//===========================================
#ifndef _WEAPON_SELECT_UI_H_
#define _WEAPON_SELECT_UI_H_

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include "object.h"

//-------------------------------------------
// �O���錾
//-------------------------------------------
class CWeaponCage;		// ���포��
class CWeaponBalloon;	// ����̂ӂ�����

//-------------------------------------------
// �N���X��`(����I��UI)
//-------------------------------------------
class CWeaponSelectUI : public CObject
{
public:		// �N�ł��A�N�Z�X�ł���

	CWeaponSelectUI();			// �R���X�g���N�^
	~CWeaponSelectUI();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);			// ����������
	void Uninit(void);			// �I������
	void Update(void);			// �X�V����
	void Draw(void);			// �`�揈��

	// �ÓI�����o�֐�
	static CWeaponSelectUI* Create(void);	// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	D3DXVECTOR3 m_pos;			// �ʒu
	CWeaponCage* m_pCage;		// ���포���̏��
	CWeaponBalloon* m_pBalloon;	// �ӂ������̏��
};

#endif