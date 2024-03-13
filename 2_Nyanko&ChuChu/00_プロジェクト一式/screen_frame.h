//============================================
//
// ��ʂ̘g�w�b�_�[[screen_frame.h]
// Author�F��������
//
//============================================
#ifndef _SCREEN_FRAME_H_					// ���̃}�N����`������Ă��Ȃ�������
#define _SCREEN_FRAME_H_					// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "object.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CObject2D;			// 2D�|���S��

//--------------------------------------------
// �N���X��`(��ʂ̘g)
//--------------------------------------------
class CScreenFrame : public CObject
{
public:				// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_HEIGHT = 0,	// �c���̃|���S��
		TYPE_WIDTH,			// �����̃|���S��
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	CScreenFrame();			// �R���X�g���N�^
	~CScreenFrame();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(void);		// ���̐ݒ菈��

	static CScreenFrame* Create(void);		// ��������

private:			// ���������A�N�Z�X�ł���

	CObject2D* m_apFrame[2];		// 
};

#endif