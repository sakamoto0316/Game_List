//===================================
//
// �j�Ѓw�b�_�[[fraction.h]
// Author ��������
//
//===================================
#ifndef _FRACTION_H_
#define _FRACTION_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �N���X��`(�j��)
//-----------------------------------
class CFraction : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum STATE
	{
		STATE_NONE = 0,		// �ʏ���
		STATE_DELETE,		// �������
		STATE_MAX			// ���̗񋓌^�̑���
	};

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_FLOWERVASE = 0,	// �ԕr
		TYPE_PRASTICRVASE,		// �v���X�`�b�N�P�[�X
		TYPE_PIN,				// ��e
		TYPE_CAT_ATTACK,		// �L�̍U��

		TYPE_MAX				// ���̗񋓌^�̑���
	};

	CFraction();			// �R���X�g���N�^
	~CFraction();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const TYPE type);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CFraction* Create(const D3DXVECTOR3& pos, const TYPE type);	// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void MoveSet(void);		// �ړ��ʂ̐ݒ菈��
	void Move(void);		// �ړ�����
	void RotMove(void);		// �����̈ړ�����
	void Elevation(void);	// �N���n�ʂƂ̓����蔻��

	// �����o�ϐ�
	D3DXVECTOR3 m_move;			// �ړ���
	D3DXVECTOR3 m_rotMove;		// �����̈ړ���
	STATE m_state;				// ���
	int m_nStateCount;			// ��ԃJ�E���g
	float m_fAlpha;				// �����x
};

#endif