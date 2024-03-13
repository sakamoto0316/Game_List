//===================================
//
// �I���w�b�_�[[honey.h]
// Author ��������
//
//===================================
#ifndef _HONEY_H_
#define _HONEY_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "obstacle.h"

//-----------------------------------
// �N���X��`(�I��)
//-----------------------------------
class CHoney : public CObstacle
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum State
	{
		STATE_HONEYBOTTLE = 0,	// �{�g��
		STATE_HONEY,			// �t��
		STATE_MAX				// ���̗񋓌^�̑���
	};

	CHoney();				// �R���X�g���N�^
	~CHoney();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// ���̐ݒ菈��

	bool Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;		// �����蔻�菈��
	bool Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;			// �q�b�g����
	bool HitCircle(CPlayer* pPlayer, const float Radius) override;				// �q�b�g����
	void Action(void) override;													// �M�~�b�N�N������

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void StateManager(void);

	// �����o�ϐ�
	State m_State;
	int m_nWalkSeCount;	// �������̃J�E���^�[
	bool m_bLeakSe;		// �I���L����SE
};

#endif