//===================================
//
// �{�w�b�_�[[book.h]
// Author ��������
//
//===================================
#ifndef _BOOK_H_
#define _BOOK_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "obstacle.h"

//-----------------------------------
// �}�N����`
//-----------------------------------
#define MAX_BOOK	(3)		// �{�̍ő吔

//-----------------------------------
// �O���錾
//-----------------------------------
class CModel;			// ���f��

//-----------------------------------
// �N���X��`(�{)
//-----------------------------------
class CBook : public CObstacle
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum STATE
	{
		STATE_STOP = 0,		// ��~���
		STATE_COLLAPSE,		// �|����
		STATE_MAX			// ���̗񋓌^�̑���
	};

	// �\���̒�`(�{)
	struct SBook
	{
		CModel* pBook;		// ��ɍڂ��Ă���{�̏��
		D3DXVECTOR3 move;	// �ړ���
		float fGravity;		// �d��
		bool bDisp;			// �`���
		bool bMove;			// �ړ���
		bool bSe;			// SE�Đ���
	};

	CBook();				// �R���X�g���N�^
	~CBook();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// ���̐ݒ菈��

	bool Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;	// �����蔻�菈��
	bool Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;		// �q�b�g����
	bool HitCircle(CPlayer* pPlayer, const float Radius) override;			// �~�̃q�b�g����
	void Action(CPlayer* pPlayer) override;			// �A�N�V��������

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void StateManager(void);	// ��ԃ}�l�[�W���[
	bool KillZ(void);			// Z���ɂ���������

	// �����o�ϐ�
	SBook m_aBook[MAX_BOOK];	// �{�̍\����
	D3DXVECTOR3 m_move;			// �ړ���
	STATE m_state;				// ���
	int m_nActionID;			// �A�N�V����ID
	float m_fGravity;			// �d��
	bool m_bDisp;				// �`���
	bool m_bMove;				// �ړ���
	bool m_bSe;					// SE�Đ���
};

#endif