//===================================
//
// �l�Y�~���J�w�b�_�[[toycar.h]
// Author �x�씋��
//
//===================================
#ifndef _RATMECHA_H_
#define _RATMECHA_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "obstacle.h"

//-----------------------------------
// �O���錾
//-----------------------------------
class CPlayerID;			// �v���C���[��ID

//-----------------------------------
// �N���X��`(��������̎�)
//-----------------------------------
class CRatMecha : public CObstacle
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum STATE
	{
		STATE_DRIVE = 0,	// �h���C�u���
		STATE_CURVE,		// �J�[�u���
		STATE_BRAKE,		// �u���[�L���
		STATE_MAX			// ���̗񋓌^�̑���
	};

	CRatMecha();				// �R���X�g���N�^
	~CRatMecha();				// �f�X�g���N�^

							// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// ���̐ݒ菈��

	bool Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;		// �����蔻�菈��
	bool Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;			// �q�b�g����
	void Action(void) override;										// �M�~�b�N�N������
	bool HitCircle(CPlayer* pPlayer, const float Radius) override;				// �~�̃q�b�g����

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void Drive(void);			// ���s����
	void Curve(void);			// �J�[�r���O����
	void RotCalc(void);			// �����̌v�Z����
	bool Block(void);			// �u���b�N�̓����蔻�菈��
	bool Obstacle(void);		// ��Q���̓����蔻�菈��
	bool MagicWall(void);		// ���@�ǂ̓����蔻�菈��

	// �����o�ϐ�
	CPlayerID* m_pPlayerID;		// �v���C���[��ID�̃|�C���^�[
	D3DXVECTOR3 m_move;			// �ړ���
	STATE m_state;				// ���
	int m_nBrakeCount;			// �u���[�L�J�E���g
	float m_fRotDest;			// �ړI�̌���
	float m_fRotMagni;			// �����̔{��
	bool m_bRight;				// �E������
	bool m_bMove;				// �����Ă��邩
	int m_nIdnumber;			// �v���C���[ID�ԍ�

	// �ÓI�����o�ϐ�
	static int m_nBgmAll;		// BGM��炵�����̑���
};

#endif