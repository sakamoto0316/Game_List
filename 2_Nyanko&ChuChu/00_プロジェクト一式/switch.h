//===================================
//
// �X�C�b�`�w�b�_�[[switch.h]
// Author ��������
//
//===================================
#ifndef _SWITCH_H_
#define _SWITCH_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "object.h"

//-----------------------------------
// �O���錾
//-----------------------------------
class CModel;		// ���f��
class CBillboard;	// �r���{�[�h

//-----------------------------------
// �N���X��`(�X�C�b�`)
//-----------------------------------
class CSwitch : public CObject
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_BASE = 0,		// �y��
		TYPE_LEVER,			// ���o�[
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	CSwitch();				// �R���X�g���N�^
	~CSwitch();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��
	virtual void Draw(const float fAlpha);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);				// ���̐ݒ菈��
	void ChangeBoot(void);	// �N���󋵂̓���ւ�����

	// �Z�b�g�E�Q�b�g�֐�
	void SetGimmickUI(bool Set, int Player_Idx);	// �M�~�b�NUI�̐ݒ菈��
	CModel* GetModel(const TYPE type);		// ���f���̎擾����
	void SetBoot(const bool bBoot);			// �N���󋵂̐ݒ菈��
	bool GetBoot(void) const;				// �N���󋵂̎擾����

	// �ÓI�����o�֐�
	static CSwitch* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);		// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void StateManager(void);						// ��ԃ}�l�[�W���[

	// �����o�ϐ�
	CModel* m_apModel[TYPE_MAX];		// ���f���̏��
	CBillboard *m_pGimmickUI;			// �M�~�b�NUI�̏��
	bool m_aUIFalse[MAX_PLAY];			// �S��[False]�̎���UI���폜����
	D3DXVECTOR3 m_posCopy;				// �ʒu�̃R�s�[
	float m_fRotDest;					// �ړI�̌���
	float m_fPosYDest;					// �ړI�̈ʒu(Y��)
	bool m_bBoot;						// �N����
};

#endif