//===================================
//
// �v���X�G���^�[�w�b�_�[[title_press.h]
// Author ��������
//
//===================================
#ifndef _TITLE_PRESS_H_
#define _TITLE_PRESS_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "object.h"

//-----------------------------------
// �O���錾
//-----------------------------------
class CObject2D;		// 2D�|���S��

//-----------------------------------
// �N���X��`(PRESSENTER)
//-----------------------------------
class CTitlePress : public CObject
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_PRESS = 0,		// �v���X
		TYPE_BUTTON,		// �{�^��
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	// �\���̒�`(�v���X�G���^�[)
	struct SPress
	{
		D3DXVECTOR3 move;		// �ړ���
		float fRotMove;			// �����̈ړ���
		CObject2D* pPress;		// �|���S���̏��
		int nStateCount;		// ��ԃJ�E���g
		float fAlpha;			// �����x
		float fAlphaDest;		// �ړI�̓����x
	};

	CTitlePress();			// �R���X�g���N�^
	~CTitlePress();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(void);		// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CTitlePress* Create(void);	// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void Alpha(const float fAdd);		// �����x�̏���
	void Smash(const int nType);		// ������΂�����

	// �����o�ϐ�
	SPress m_aPress[TYPE_MAX];			// �v���X�̏��\����
	bool m_bSe;							// SE�̍Đ���
};

#endif