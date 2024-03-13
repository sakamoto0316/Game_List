//===================================
//
// ���S�}�[�N�w�b�_�[[logo_mark.h]
// Author ��������
//
//===================================
#ifndef _LOGO_MARK_H_
#define _LOGO_MARK_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "object.h"

//-----------------------------------
// �O���錾
//-----------------------------------
class CObject2D;			// �I�u�W�F�N�g2D

//-----------------------------------
// �N���X��`(CEffect2D)
//-----------------------------------
class CLogoMark : public CObject
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_SCREEN = 0,	// ���
		TYPE_MARK,			// �}�[�N
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	CLogoMark();			// �R���X�g���N�^
	~CLogoMark();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	// �ÓI�����o�֐�
	static CLogoMark* Create(void);	// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CObject2D* m_aLogoMark[TYPE_MAX];	// ���S�}�[�N�̏��
};

#endif