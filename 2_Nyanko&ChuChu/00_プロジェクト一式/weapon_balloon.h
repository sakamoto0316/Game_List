//===================================
//
// ����̂ӂ������w�b�_�[[weapon_balloon.h]
// Author ��������
//
//===================================
#ifndef _WEAPON_BALLOON_H_
#define _WEAPON_BALLOON_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "objectbillboard.h"

//-----------------------------------
// �N���X��`(����̂ӂ�����)
//-----------------------------------
class CWeaponBalloon : public CBillboard
{
public:

	CWeaponBalloon();		// �R���X�g���N�^
	~CWeaponBalloon();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const char* pFileName);		// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CWeaponBalloon* Create(const D3DXVECTOR3& pos, const char* pFileName);		// ��������

private:

	// �����o�ϐ�
};

#endif