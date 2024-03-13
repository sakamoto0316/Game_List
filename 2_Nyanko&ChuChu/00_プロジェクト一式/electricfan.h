//===================================
//
// ��@�w�b�_�[[electricfan.h]
// Author ��������
//
//===================================
#ifndef _ELECTRICFAN_H_
#define _ELECTRICFAN_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "obstacle.h"

//-----------------------------------
// �O���錾
//-----------------------------------
class CFanBlade;		// ��@�̃t�@��

//-----------------------------------
// �N���X��`(��@)
//-----------------------------------
class CElecFan : public CObstacle
{
public:			// �N�ł��A�N�Z�X�ł���

	CElecFan();				// �R���X�g���N�^
	~CElecFan();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// ���̐ݒ菈��

	bool Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;		// �����蔻�菈��
	bool Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;			// �q�b�g����
	bool HitCircle(CPlayer* pPlayer, const float Radius) override;				// �~�̃q�b�g����
	void Action(void) override;										// �M�~�b�N�N������

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CFanBlade* m_pFan;		// ��@�̃t�@��
	bool m_bPower;			// �d����
};

#endif