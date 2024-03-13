//===================================
//
// �ۉe�w�b�_�[[shadowCircle.h]
// Author ��������
//
//===================================
#ifndef _SHADOWCIRCLE_H_				//���̃}�N����`������Ă��Ȃ�������
#define _SHADOWCIRCLE_H_				//2�d�C���N���[�h�h�~�̃}�N�����`����

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "main.h"
#include "object3D.h"

//-----------------------------------
// �N���X��`(�e)
//-----------------------------------
class CShadowCircle : public CObject3D
{
public:			// �N�ł��A�N�Z�X�ł���

	CShadowCircle();			// �R���X�g���N�^
	~CShadowCircle();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);			// ����������
	void Uninit(void);			// �I������
	void Update(void);			// �X�V����
	void Draw(void);			// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, float fRadius);		// ���̐ݒ菈��

	void AlphaSet(void);		// �����x�̐ݒ菈��

	// �Z�b�g�E�Q�b�g�֌W
	int GetNumID(void) const;		// ID�̎擾����

	// �ÓI�����o�֐�
	static CShadowCircle* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, float fRadius);	// ��������
	static void SetPosRot(int nIdx, const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);				// �e�̈ʒu�ݒ菈��
	static void SetPosRotXZ(int nIdx, const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);				// �e�̈ʒu�ݒ菈��(Y������)
	static CShadowCircle* GetShadow(int nIdx);														// �ۉe�̎擾����

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	D3DXCOLOR m_col;			// �F
	int m_nID;					// �e�̃C���f�b�N�X

	// �ÓI�����o�ϐ�
	static int m_nNumAll;		// �e�̑���
};


#endif