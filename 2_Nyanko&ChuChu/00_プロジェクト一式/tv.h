//===================================
//
// �e���r�w�b�_�[[cup.h]
// Author �x�씋��
//
//===================================
#ifndef _TV_H_
#define _TV_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "obstacle.h"

class CConsent;
class CObject3D;
class CModel;

//-----------------------------------
// �N���X��`(�R�b�v)
//-----------------------------------
class CTv : public CObstacle
{
public:			// �N�ł��A�N�Z�X�ł���

	CTv();				// �R���X�g���N�^
	~CTv();				// �f�X�g���N�^

	// �񋓌^��`(���)
	enum STATE
	{
		STATE_NONE = 0,	// �A�C�e���擾�\���
		STATE_COOLDOWN,	// �N�[���^�C�����
		STATE_BOMB,		// ���e��ʂ������ꍇ
		STATE_MAX		// ���̗񋓌^�̑���
	};

	// �\���̒�`(�����R��)
	struct SRemocon
	{
		CModel* pRemocon;			// �����R���̃��f�����
		CBillboard* pGimmickUI;		// �M�~�b�NUI
	};

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// ���̐ݒ菈��

	bool Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;		// �����蔻�菈��
	bool HitCircle(CPlayer* pPlayer, const float Radius) override;
	void Action(void) override;		// �A�N�V����
	bool HitRemocon(void);			// �����R���̃q�b�g����
	void PowerAction(void);			// �d������
	void VisionChange(void);		// �e���r��ʐ؂�ւ�
private:		// ���������A�N�Z�X�ł���
	void StateManager(void);		// ��ԊǗ��}�l�[�W���[

	CObject3D *m_pVision;		// �|���S�����
	SRemocon m_remocon;			// �����R��
	D3DXVECTOR3 m_vtxMax;		// �ő�l
	D3DXVECTOR3 m_vtxMin;		// �ŏ��l
	STATE m_State;				// �e���r�̏��
	int m_nCoolTime;			// �N�[���^�C��
	int m_nChangeVision;		// ��ʕω�����
	bool m_bPower;				// �d��
};

#endif