//===================================
//
// �s���w�b�_�[[Pin.h]
// Author ��{�ėB
//
//===================================
#ifndef _PIN_H_
#define _PIN_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "obstacle.h"

//-----------------------------------
// �N���X��`(���[�h)
//-----------------------------------
class CPin : public CObstacle
{
public:			// �N�ł��A�N�Z�X�ł���

	CPin();				// �R���X�g���N�^
	~CPin();			// �f�X�g���N�^

	// �񋓌^��`(���)
	enum STATE
	{
		STATE_FALSE = 0,	// ��~���
		STATE_FALLWAIT,		// �N���܂ŗ������ɏ�������
		STATE_TRUE,			// �N�����
		STATE_MAX			// ���̗񋓌^�̑���
	};

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// ���̐ݒ菈��

	bool Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;		// �q�b�g����
	bool HitCircle(CPlayer* pPlayer, const float Radius) override;
	void Action(void) override;

private:		// ���������A�N�Z�X�ł���
	void StateManager(D3DXVECTOR3 *pos, D3DXVECTOR3 *rot);

	D3DXVECTOR3 m_move;			//�ړ���
	STATE m_State;				//���
};

#endif