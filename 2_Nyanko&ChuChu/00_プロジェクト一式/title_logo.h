//===================================
//
// �^�C�g�����S�w�b�_�[[title_logo.h]
// Author ��������
//
//===================================
#ifndef _TITLE_LOGO_H_
#define _TITLE_LOGO_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "object.h"

//-----------------------------------
// �O���錾
//-----------------------------------
class CObject2D;		// 2D�|���S��

//-----------------------------------
// �N���X��`(�^�C�g�����S)
//-----------------------------------
class CTitleLogo : public CObject
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_RAT = 0,		// �ɂ��
		TYPE_AND,			// ��
		TYPE_CAT,			// ����[����[
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	// �񋓌^��`(���)
	enum STATE
	{
		STATE_ESCAPE = 0,	// �������
		STATE_AND,			// ���o�����
		STATE_WAIT,			// �ҋ@���
		STATE_FRAMEOUT,		// ��ʊO���
		STATE_SHAKEOFF,		// �����؂���
		STATE_HOLEIN,		// ��������
		STATE_STOP,			// ��~���
		STATE_MAX			// ���̗񋓌^�̑���
	};

	// �\���̒�`(�^�C�g�����S)
	struct STitleLogo
	{
		D3DXVECTOR3 move;		// �ړ���
		CObject2D* pLogo;		// �^�C�g���̃|���S��
		bool bDisp;				// �\����
		bool bMove;				// �ړ���
	};

	CTitleLogo();			// �R���X�g���N�^
	~CTitleLogo();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(void);		// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CTitleLogo* Create(void);	// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void EscapeProcess(void);			// ������Ԃ̏���
	void AndProcess(void);				// ���o����Ԃ̏���
	void FrameOutProcess(void);			// ��ʊO��Ԃ̏���
	void ShakeOffProcess(void);			// �����؂��Ԃ̏���
	void HoleInProcess(void);			// �������Ԃ̏���

	void Move(const TYPE type);			// �ړ�����
	void Locus(const TYPE type);		// �c����������

	void EscapeRatPosSet(void);			// ������Ԃ̃l�Y�~�̈ʒu�֌W����
	void EscapeCatPosSet(void);			// ������Ԃ̃l�R�̈ʒu�֌W����

	void FrameOutRatPosSet(void);		// ��ʊO��Ԃ̃l�Y�~�̈ʒu�֌W����
	void FrameOutCatPosSet(void);		// ��ʊO��Ԃ̃l�R�̈ʒu�֌W����
	void FrameOutSetRat(void);			// ��ʊO���̃l�Y�~�̐ݒ菈��
	void FrameOutAnd(void);				// ��ʊO��Ԃ̃A���h�̏���

	void ShakeOffRatPosSet(void);		// �����؂��Ԃ̃l�Y�~�̈ʒu�֌W����

	// �����o�ϐ�
	STitleLogo m_aTitle[TYPE_MAX];		// �^�C�g���̃|���S��
	STATE m_state;						// ���
	int m_nStateCount;					// ��ԃJ�E���g
	bool m_bSe;							// SE�Đ���
};

#endif