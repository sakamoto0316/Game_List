//============================================
//
// �C�≉�o�w�b�_�[[stun.h]
// Author�F��������
//
//============================================
#ifndef _STUN_H_					// ���̃}�N����`������Ă��Ȃ�������
#define _STUN_H_					// 2�d�C���N���[�h�h�~�̃}�N�����`����
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "object.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define MAX_STUN		(4)		// �C�≉�o�̍ő吔

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CBillboard;			// �r���{�[�h

//--------------------------------------------
// �N���X��`(�C�≉�o)
//--------------------------------------------
class CStun : public CObject
{
public:				// �N�ł��A�N�Z�X�ł���

	CStun();				// �R���X�g���N�^
	~CStun();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3 pos);				// ���̐ݒ菈��

	// �Z�b�g�E�Q�b�g�֌W
	void SetPos(const D3DXVECTOR3& pos);				// �ʒu�̐ݒ菈��

	// �ÓI�����o�ϐ�
	static CStun* Create(const D3DXVECTOR3 pos);		// ��������

private:			// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	D3DXVECTOR3 m_pos;				// �ʒu
	float m_fRot;					// ��]�p�̌���
	CBillboard* m_apStun[MAX_STUN];	// �C�≉�o�̏��
};

#endif