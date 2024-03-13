//============================================
//
// �A�C�e���̃}�[�N�w�b�_�[[item_mark.h]
// Author�F��������
//
//============================================
#ifndef _ITEM_MARK_H_					// ���̃}�N����`������Ă��Ȃ�������
#define _ITEM_MARK_H_					// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "object2D.h"
#include "item.h"

//--------------------------------------------
// �N���X��`(�A�C�e���̃}�[�N)
//--------------------------------------------
class CItemMark : public CObject2D
{
public:				// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum STATE
	{
		STATE_SMALL = 0,	// �����
		STATE_BIG,			// ����
		STATE_MAX			// ���̗񋓌^�̑���
	};

	CItemMark();			// �R���X�g���N�^
	~CItemMark();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const CItem::TYPE type);				// ���̐ݒ菈��

	// �Z�b�g�E�Q�b�g�֌W
	CItem::TYPE GetType(void) const;		// ��ނ̎擾����

	// �ÓI�����o�֐�
	static CItemMark* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const CItem::TYPE type);	// ��������

private:			// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	void Sizing(void);		// �T�C�Y�ݒ菈��
	
	// �����o�ϐ�
	D3DXVECTOR3 m_sizeDest;	// �ړI�̃T�C�Y
	D3DXVECTOR3 m_sizeCopy;	// �����̃T�C�Y
	STATE m_state;			// ���
	CItem::TYPE m_type;		// ���
};

#endif