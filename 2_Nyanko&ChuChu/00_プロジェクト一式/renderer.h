//============================================
//
// �����_���[�̃w�b�_�[[renderer.h]
// Author�F��������
//
//============================================
#ifndef _RENDERER_H_		//���̃}�N����`������Ă��Ȃ�������
#define _RENDERER_H_		//2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "main.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define MAX_VERTEX		(4)			// ���_��

//--------------------------------------------
// �N���X(�����_���[�N���X)
//--------------------------------------------
class CRenderer
{
public:						// �N�ł��A�N�Z�X�ł���

	CRenderer();			// �R���X�g���N�^
	~CRenderer();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(HWND hWnd, BOOL bWindow);		// ����������
	void Uninit(void);							// �I������
	void Update(void);							// �X�V����
	void Draw(void);							// �`�揈��

	LPDIRECT3DDEVICE9 GetDevice(void);			// �f�o�C�X�̎擾����

private:					// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	LPDIRECT3D9 m_pD3D;							// Direct3D�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECT3DDEVICE9 m_pD3DDevice;				// Direct3D�f�o�C�X�ւ̃|�C���^
};

#endif