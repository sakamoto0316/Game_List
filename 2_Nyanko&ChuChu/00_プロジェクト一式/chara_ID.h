//============================================
//
// �L�����N�^�[��ID�w�b�_�[[chara_ID.h]
// Author�F��������
//
//============================================
#ifndef _CHARA_ID_H_					// ���̃}�N����`������Ă��Ȃ�������
#define _CHARA_ID_H_					// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "object2D.h"

//--------------------------------------------
// �N���X��`(�L�����N�^�[�̉摜)
//--------------------------------------------
class CCharaID : public CObject2D
{
public:				// �N�ł��A�N�Z�X�ł���

	CCharaID();						// �R���X�g���N�^
	~CCharaID();						// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);					// ����������
	void Uninit(void);					// �I������
	void Update(void);					// �X�V����
	void Draw(void);					// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const int nID);			// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CCharaID* Create(const D3DXVECTOR3& pos, const int nID);	// ��������

private:			// ���������A�N�Z�X�ł���

};

#endif