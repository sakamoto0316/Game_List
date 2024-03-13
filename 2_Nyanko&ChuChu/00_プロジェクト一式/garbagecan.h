//===================================
//
// �S�~���w�b�_�[[garbagecan.h]
// Author ��������
//
//===================================
#ifndef _GARBAGECAN_H_
#define _GARBAGECAN_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "obstacle.h"

class CPlayer;

//-----------------------------------
// �N���X��`(�I��)
//-----------------------------------
class CGarbage : public CObstacle
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum State
	{
		STATE_GARBAGECAN = 0,	// �S�~��
		STATE_FALL,				// �������
		STATE_BANANA_NORMAL,	// �o�i�i�̔�
		STATE_BANANA_SLIDE,		// �o�i�i�̔�
		STATE_MAX				// ���̗񋓌^�̑���
	};

	// �񋓌^��`(���)
	enum SLIDE
	{
		SLIDE_STOP = 0,	// ��~���
		SLIDE_ON,		// ������
		SLIDE_BREAK,	// �Ԃ�����
		SLIDE_MAX		// ���̗񋓌^�̑���
	};

	CGarbage();				// �R���X�g���N�^
	~CGarbage();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// ���̐ݒ菈��

	void SlideOn(D3DXVECTOR3 pos, D3DXVECTOR3 move, CPlayer *pPlayer);
	bool Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;		// �����蔻�菈��
	bool Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;			// �q�b�g����
	bool HitCircle(CPlayer* pPlayer, const float Radius) override;				// �q�b�g�̉~����
	void Action(void) override;										// �M�~�b�N�N������

private:		// ���������A�N�Z�X�ł���
	void Break(void);
	void StateManager(void);
	bool MagicWall(void);

	State m_State;
	SLIDE m_Slide;
	D3DXVECTOR3 m_PlayerPos;
	D3DXVECTOR3 m_SlideMove;
	D3DXVECTOR3 m_move;
	CPlayer *m_pPlayer;
};

#endif