//===================================
//
// �����o�w�b�_�[[roomba.h]
// Author ��{�ėB
//
//===================================
#ifndef _ROOMBA_H_
#define _ROOMBA_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "obstacle.h"

class CModel;

//-----------------------------------
// �N���X��`(�����o)
//-----------------------------------
class CRoomba : public CObstacle
{
public:			// �N�ł��A�N�Z�X�ł���

	CRoomba();				// �R���X�g���N�^
	~CRoomba();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// ���̐ݒ菈��

	bool Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;		// �����蔻�菈��
	bool Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;			// �q�b�g����

private:		// ���������A�N�Z�X�ł���

	void SubUpdate(void);	// �v���y���̍X�V�̏���
	void Move(D3DXVECTOR3 rot);		// �ړ�����

	CModel *m_apSub[2];
	D3DXVECTOR3 m_move;

};

#endif