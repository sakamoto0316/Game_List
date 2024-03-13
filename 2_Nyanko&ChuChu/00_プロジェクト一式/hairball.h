//===================================
//
// �{�w�b�_�[[hairball.h]
// Author ��������
//
//===================================
#ifndef _HAIRBALL_H_
#define _HAIRBALL_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "obstacle.h"

//-----------------------------------
// �N���X��`(�{)
//-----------------------------------
class CHairBall : public CObstacle
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum STATE
	{
		STATE_STOP = 0,		// ��~���
		STATE_SMASH,		// ������΂����
		STATE_MAX			// ���̗񋓌^�̑���
	};

	CHairBall();			// �R���X�g���N�^
	~CHairBall();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// ���̐ݒ菈��

	bool Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;		// �����蔻�菈��
	bool Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;			// �q�b�g����

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void Move(void);			// �ړ�����
	void Gravity(void);			// �d�͏���
	void Elevation(void);		// �N���n�ʂ̓����蔻��
	void Block(void);			// �u���b�N�̓����蔻��
	void MagicWall(void);		// ���@�̕�

	// �����o�ϐ�
	D3DXVECTOR3 m_move;			// �ړ���
	STATE m_state;				// ���
};

#endif