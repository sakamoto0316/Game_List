//============================================
//
// �^�C�g����ʃw�b�_�[[title.h]
// Author�F��������
//
//============================================
#ifndef _TITLE_H_			//���̃}�N����`������Ă��Ȃ�������
#define _TITLE_H_			//2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "scene.h"

//�O���錾
class C2DUIEdit;

//--------------------------------------------
// �N���X(�^�C�g���N���X)
//--------------------------------------------
class CTitle : public CScene
{
public:				// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum STATE
	{
		STATE_TITLE_APPEAR = 0,		// �^�C�g���̏o�����
		STATE_WAIT,					// �i�s�ҋ@���
		STATE_TRANS,				// �J�ڏ��
		STATE_HOLEIN,				// ���̒��ɓ����Ă������
		STATE_MAX					// ���̗񋓌^�̑���
	};

	CTitle();		// �R���X�g���N�^
	~CTitle();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);				// ����������
	void Uninit(void);				// �I������
	void Update(void);				// �X�V����
	void Draw(void);				// �`�揈��

	// �ÓI�����o�֐�
	static void SetState(const STATE state);		// ��Ԃ̐ݒ菈��
	static STATE GetState(void);					// ��Ԃ̎擾����

private:					// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	C2DUIEdit *m_pUIEdit;
	int m_nTransCount;		// �J�ڃJ�E���g
	bool m_bEdit;

	// �ÓI�����o�ϐ�
	static STATE m_state;			// ���
};

#endif