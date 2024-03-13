//===================================
//
// 2D�G�t�F�N�g�w�b�_�[[effect2D.h]
// Author ��������
//
//===================================
#ifndef _EFFECT2D_H_
#define _EFFECT2D_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "object2D.h"

//-----------------------------------
// �N���X��`(CEffect2D)
//-----------------------------------
class CEffect2D : public CObject2D
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_NONE = 0,	// �ʏ�
		TYPE_SHINING,	// �P��
		TYPE_OVERTOP,	// ���E�˔j
		TYPE_INFIRE,	// �����̉�
		TYPE_OUTFIRE,	// �O���̉�
		TYPE_MAX		// ���̗񋓌^�̑���
	};

	CEffect2D();			// �R���X�g���N�^
	~CEffect2D();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& move, const int nLife, const float fRadius, const TYPE type);					// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CEffect2D* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& move, const int nLife, const float fRadius, const TYPE type);		// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void TypeProcess(void);		// ��ނɂ�鏈��

	// �����o�ϐ�
	D3DXVECTOR3 m_move;		// �ړ���
	D3DXCOLOR m_col;		// �F
	TYPE m_type;			// ���
	int m_nLife;			// ����
	float m_fSub;			// �����ɂȂ�Ԋu
	float m_fContra;		// ���a�̏k�ފԊu
	bool m_bAdd;			// ���Z������
};

#endif