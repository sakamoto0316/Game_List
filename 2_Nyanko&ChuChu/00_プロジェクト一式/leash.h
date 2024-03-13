//===================================
//
// ���[�h�w�b�_�[[Himo.h]
// Author ��{�ėB
//
//===================================
#ifndef _LEASH_H_
#define _LEASH_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "obstacle.h"

//-----------------------------------
// �N���X��`(���[�h)
//-----------------------------------
class CLeash : public CObstacle
{
public:			// �N�ł��A�N�Z�X�ł���

	CLeash();				// �R���X�g���N�^
	~CLeash();				// �f�X�g���N�^

	// �񋓌^��`(���)
	enum STATE
	{
		STATE_FALSE = 0,	// ��~���
		STATE_JUMPWAIT,		// �N���܂ŏ�ɒ��ˏオ���ď�������
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
	void HitMultiCircle(CPlayer* pPlayer, const float Radius, bool bInput) override;
	//void CollisionHead(bool Set) { m_bSetHead = Set; }
	//void CollisionToes(bool Set) { m_bSetToes = Set; }
	void Action(void) override;

	D3DXVECTOR3 GetPosHead(void) { return ActionPosHead; }
	D3DXVECTOR3 GetPosToes(void) { return ActionPosToes; }

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void StateManager(D3DXVECTOR3 *pos);
	void SetActionPos(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void CollisionSetting(void);			// �����蔻��̐ݒ菈��

	// �����o�ϐ�
	D3DXVECTOR3 m_move;			// �ړ���
	D3DXVECTOR3 ActionPosHead;	// ��[�̈ʒu
	D3DXVECTOR3 ActionPosToes;	// ���[�̈ʒu
	D3DXVECTOR3 m_vtxMax;		// �ő�l
	D3DXVECTOR3 m_vtxMin;		// �ŏ��l
	STATE m_State;				// ���
	int m_StateCount;			// ��ԊǗ��p�̃J�E���g
	bool m_bSetHead[4];			// ��[�̏�������
	bool m_bSetToes[4];			// ���[�̏�������
	bool m_bSe;					// SE�̍Đ���
};

#endif