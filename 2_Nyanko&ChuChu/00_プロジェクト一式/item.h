//===================================
//
// �A�C�e���w�b�_�[[item.h]
// Author ��������
//
//===================================
#ifndef _ITEM_H_
#define _ITEM_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �N���X��`(�A�C�e��)
//-----------------------------------
class CItem : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_MOUSETRAP = 0,		// �l�Y�~�߂�
		TYPE_DYNAMITE,			// �_�C�i�}�C�g
		TYPE_MAX				// ���̗񋓌^�̑���
	};

	// �񋓌^��`(���)
	enum STATE
	{
		STATE_NONE = 0,		// �������Ȃ�
		STATE_STANDBY,		// �ҋ@
		STATE_MAX			// ���̗񋓌^�̑���
	};

	CItem();			// �R���X�g���N�^
	~CItem();			// �f�X�g���N�^

	// ���X�g�\���֌W
	void SetPrev(CItem* pPrev);		// �O�̃|�C���^�̐ݒ菈��
	void SetNext(CItem* pNext);		// ��̃|�C���^�̐ݒ菈��
	CItem* GetPrev(void) const;		// �O�̃|�C���^�̐ݒ菈��
	CItem* GetNext(void) const;		// ���̃|�C���^�̐ݒ菈��

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const TYPE type);			// ���̐ݒ菈��

	// �Z�b�g�E�Q�b�g�֌W
	void SetType(const TYPE type);		// ��ނ̐ݒ菈��
	void SetState(const STATE state);	// ��Ԃ̐ݒ菈��

	TYPE GetType(void) const;			// ��ނ̎擾����
	STATE GetState(void) const;			// ��ނ̎擾����

	// �ÓI�����o�֐�
	static CItem* Create(const D3DXVECTOR3& pos, const TYPE type);	// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void Cycle(void);		// ��]����
	void Scaling(void);		// �g�k����

	// �����o�ϐ�
	TYPE m_type;			// ���
	STATE m_state;			// ���
	float m_fScaleDest;		// �ړI�̊g�嗦

	// ���X�g�\���֌W
	CItem* m_pPrev;	// �O�ւ̃|�C���^
	CItem* m_pNext;	// ���ւ̃|�C���^
};

#endif