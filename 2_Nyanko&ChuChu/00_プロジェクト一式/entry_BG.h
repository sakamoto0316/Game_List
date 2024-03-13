//===================================
//
// �G���g���[�w�i�w�b�_�[[entry_BG.h]
// Author ��������
//
//===================================
#ifndef _ENTRY_BG_H_
#define _ENTRY_BG_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "object.h"

//-----------------------------------
// �O���錾
//-----------------------------------
class CModel;			// ���f��

//-----------------------------------
// �N���X��`(CEntryBG)
//-----------------------------------
class CEntryBG : public CObject
{
public:

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_FLOOR = 0,		// ��
		TYPE_WALL,			// ��
		TYPE_SHOEBOX,		// �C��
		TYPE_DOOR,			// �h�A
		TYPE_FARWALL,		// ���̕�
		TYPE_SHOEFLOOR,		// �C������̏�
		TYPE_SIDEWALL,		// ���̕�
		TYPE_BOOTS,			//�u�[�c
		TYPE_SANDAL,		//�T���_��
		TYPE_LESTHERSHOES,	//���U�[�V���[�Y
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	CEntryBG();				// �R���X�g���N�^
	~CEntryBG();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(void);					// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CEntryBG* Create(void);		// ��������

private:

	// �����o�ϐ�
	CModel* m_apModel[TYPE_MAX];		// ���f���̏��
};

#endif