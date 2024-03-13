//===================================
//
// �J�[�e���w�b�_�[[curtain.h]
// Author ��������
//
//===================================
#ifndef _CURTAIN_H_
#define _CURTAIN_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "obstacle.h"

//-----------------------------------
// �}�N����`
//-----------------------------------
#define MAX_SWITCH		(3)		// �X�C�b�`�̍ő吔

//-----------------------------------
// �O���錾
//-----------------------------------
class CSwitch;			// �X�C�b�`

//-----------------------------------
// �N���X��`(�J�[�e��)
//-----------------------------------
class CCurtain : public CObstacle
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum STATE
	{
		STATE_CLOSE = 0,	// ������
		STATE_OPEN,			// �J���Ă���
		STATE_MAX			// ���̗񋓌^�̑���
	};

	CCurtain();				// �R���X�g���N�^
	~CCurtain();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// ���̐ݒ菈��

	bool Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;					// �����蔻�菈��
	bool HitCircle(CPlayer* pPlayer, const float Radius);									// �q�b�g����
	void HitMultiCircle(CPlayer* pPlayer, const float Radius, bool bInput) override;		// �q�b�g����

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void VtxSetting(void);		// ���_�̐ݒ菈��
	void ScaleVtxSet(void);		// �g�嗦�ɂ�钸�_�̐ݒ菈��
	void StateManager(void);	// ��ԃ}�l�[�W���[

	// �����o�ϐ�
	CSwitch* m_apSwitch[MAX_SWITCH];	// �X�C�b�`�̏��
	STATE m_state;						// ���݂̏��
	STATE m_stateOld;					// �O��̏��
	D3DXVECTOR3 m_vtxMax;				// �ő�l
	D3DXVECTOR3 m_vtxMin;				// �ŏ��l
	float m_fEdge;						// �J�[�e���̒[�̍��W
};

#endif