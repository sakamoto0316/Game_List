//============================================
//
// ���l�w�b�_�[[number.h]
// Author�F��������
//
//============================================
#ifndef _NUMBER_H_					// ���̃}�N����`������Ă��Ȃ�������
#define _NUMBER_H_					// 2�d�C���N���[�h�h�~�̃}�N�����`����
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "object2D.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define NUMBER_TEXTURE_PATTERN		(0.1f)		// �����̃e�N�X�`�����W

//--------------------------------------------
// �N���X��`(���l)
//--------------------------------------------
class CNumber : public CObject2D
{
public:				// �N�ł��A�N�Z�X�ł���

	//--------------------------------------------
	// ���
	//--------------------------------------------
	enum TYPE
	{
		TYPE_DECIMAL = 0,	// 10�i��
		TYPE_TIME,			// ����
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	CNumber();							// �R���X�g���N�^
	CNumber(CObject::TYPE type, CObject::PRIORITY priority);		// �I�[�o�[���[�h�R���X�g���N�^
	virtual ~CNumber();					// �f�X�g���N�^
	void Box(void);						// �R���X�g���N�^�̔�

	// �����o�֐�
	virtual HRESULT Init(void);		// ����������
	virtual void Uninit(void);		// �I������
	virtual void Update(void);		// �X�V����
	virtual void Draw(void);		// �`�揈��

	static CNumber* Create(void);		// ��������

	// �Z�b�g�E�Q�b�g�֌W
	void SetType(const TYPE type);		// ��ނ̐ݒ菈��
	TYPE GetType(void) const;			// ��ނ̎擾����

	void SetNumber(const int nNum);		// �ԍ��̐ݒ菈��
	int GetNumber(void) const;			// �ԍ��̎擾����

private:			// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	int m_nNumber;			// ����
	TYPE m_type;			// ���
};

#endif