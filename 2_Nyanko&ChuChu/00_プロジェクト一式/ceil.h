//===================================
//
// �V��w�b�_�[[ceil.h]
// Author ��������
//
//===================================
#ifndef _CEIL_H_
#define _CEIL_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "object.h"

//-----------------------------------
// �}�N����`
//-----------------------------------
#define MAX_CEIL	(2)		// �V��|���S���̑���

//-----------------------------------
// �O���錾
//-----------------------------------
class CObject3D;

//-----------------------------------
// �N���X��`(CCeil)
//-----------------------------------
class CCeil : public CObject
{
public:

	CCeil();				// �R���X�g���N�^
	~CCeil();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CCeil* Create(const D3DXVECTOR3& pos);		// ��������

private:

	// �����o�ϐ�
	CObject3D* m_apCeil[MAX_CEIL];		// �����̃|���S��
};

#endif