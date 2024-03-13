//============================================
//
// �A�C�e��UI�w�b�_�[[item_UI.h]
// Author�F��������
//
//============================================
#ifndef _ITEM_UI_H_			// ���̃}�N����`������Ă��Ȃ�������
#define _ITEM_UI_H_			// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "object.h"
#include "item.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CItemMark;			// �A�C�e���̃}�[�N
class CItemFrame;			// �A�C�e���̘g

//--------------------------------------------
// �N���X��`(�A�C�e��UI)
//--------------------------------------------
class CItemUI : public CObject
{
public:				// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(����)
	enum ORDER
	{
		ORDER_BACK = 0,		// ���
		ORDER_FRONT,		// �O
		ORDER_MAX			// ���̗񋓌^�̑���
	};

	// �\���̒�`(�A�C�e��UI)
	struct SItemUI
	{
		CItemMark* pMark;		// �}�[�N�̏��
		CItemFrame* pFrame;		// �g�̏��
	};

	CItemUI();				// �R���X�g���N�^
	~CItemUI();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);					// ���̐ݒ菈��

	void SortInfo(void);	// ���̃\�[�g����

	// �Z�b�g�E�Q�b�g�֌W
	void SetMark(const CItem::TYPE type, const ORDER order);	// �}�[�N�̐�������
	SItemUI GetItemUI(const ORDER order) const;					// �A�C�e��UI�̎擾����

	// �ÓI�����o�֐�
	static CItemUI* Create(const D3DXVECTOR3& pos);				// ��������

private:			// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	SItemUI m_aItemUI[ORDER_MAX];		// �A�C�e��UI�̏��
};

#endif