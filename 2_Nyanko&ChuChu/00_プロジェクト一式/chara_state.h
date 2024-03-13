//============================================
//
// �L�����N�^�[�̏�ԃA�C�R���w�b�_�[[chara_state.h]
// Author�F��������
//
//============================================
#ifndef _CHARA_STATE_H_					// ���̃}�N����`������Ă��Ȃ�������
#define _CHARA_STATE_H_					// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "object2D.h"

//--------------------------------------------
// �N���X��`(�L�����N�^�[�̏��)
//--------------------------------------------
class CCharaState : public CObject2D
{
public:				// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum STATE
	{
		STATE_NONE = 0,		// �ʏ���
		STATE_STUN,			// �C����
		STATE_GHOST,		// �S�[�X�g���
		STATE_MAX			// ���̗񋓌^�̑���
	};

	CCharaState();			// �R���X�g���N�^
	~CCharaState();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const int nID);					// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CCharaState* Create(const D3DXVECTOR3& pos, const int nID);		// ��������

private:			// ���������A�N�Z�X�ł���

	// �����o�֐�
	void State(void);	// ��ԏ���

	// �����o�ϐ�
	STATE m_state;		// ���
	int m_nPlayerIdx;	// �v���C���[�̃C���f�b�N�X
	bool m_bDisp;		// �`���
};

#endif