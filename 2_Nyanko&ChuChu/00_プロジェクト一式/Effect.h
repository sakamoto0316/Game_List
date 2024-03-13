//===================================
//
// �G�t�F�N�g�w�b�_�[[Effect.h]
// Author ��������
//
//===================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "objectbillboard.h"

//-----------------------------------
// �N���X��`(CEffect)
//-----------------------------------
class CEffect : public CBillboard
{
public:

	// ���
	enum TYPE
	{
		TYPE_NONE = 0,			// ����
		TYPE_FIRE,				// ���n
		TYPE_DUST,				// ��
		TYPE_RUPTURE,			// �j��
		TYPE_SMOKE,				// ��
		TYPE_THUNDER,			// �d�C
		TYPE_WIND,				// ��
		TYPE_RESURRECTION,		// ����	
		TYPE_ITEMGET,			// �擾
		TYPE_MAX				// ���̗񋓌^�̑���
	};

	CEffect();			// �R���X�g���N�^
	~CEffect();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);			// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& move, const int nLife, const float fRadius, const TYPE type, const D3DXCOLOR& col, const bool bAdd);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CEffect* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& move, const int nLife, const float fRadius, const TYPE type, const D3DXCOLOR& col, const bool bAdd);		// ��������

private:

	// �����o�֐�
	void Move(void);				// �ړ�����
	void SubAlpha(void);			// �����x���Z����
	void Sizing(void);				// �T�C�W���O����

	// ��ނ��Ƃ̏���
	void FireProcess(void);			// ���n�̏���
	void RuptureProcess(void);		// �j��̏���

	// �����o�ϐ�
	D3DXVECTOR3 m_move;		// �ړ���
	D3DXCOLOR m_col;		// �F
	TYPE m_type;			// ���
	int m_nLife;			// ����
	int m_nLifeOrigin;		// ���X�̎���
	float m_fSub;			// �����ɂȂ�Ԋu
	float m_fContra;		// ���a�̏k�ފԊu
	bool m_bAdd;			// ���Z������
};

#endif