//===================================
//
// �򖗃w�b�_�[[destruction.h]
// Author ��������
//
//===================================
#ifndef _DESTRUCTION_H_
#define _DESTRUCTION_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "objectbillboard.h"

//-----------------------------------
// �N���X��`(CDestruction)
//-----------------------------------
class CDestruction : public CBillboard
{
public:

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_THORN = 0,		// �g�Q�g�Q
		TYPE_AIRY,			// �t���t��
		TYPE_EXPLOSION,		// ����
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	// �񋓌^��`(���)
	enum STATE
	{
		STATE_ADD = 0,		// ���Z���
		STATE_SUB,			// ���Z���
		STATE_MAX			// ���̗񋓌^�̑���
	};

	CDestruction();			// �R���X�g���N�^
	~CDestruction();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const D3DXCOLOR& col, const TYPE type, const int nLife);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CDestruction* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const D3DXCOLOR& col, const TYPE type, const int nLife);		// ��������

private:

	// �����o�ϐ�
	D3DXCOLOR m_col;	// �F
	STATE m_state;		// ���
	float m_fAddAlpha;	// ���Z���铧���x
	float m_fAlphaDest;	// �ړI�̓����x
};

#endif