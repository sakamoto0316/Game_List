//===================================
//
// �e�N�X�`���w�b�_�[[texture.h]
// Author ��������
//
//===================================
#ifndef _TEXTURE_H_				//���̃}�N����`������Ă��Ȃ�������
#define _TEXTURE_H_				//2�d�C���N���[�h�h�~�̃}�N�����`����

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "main.h"

//-----------------------------------
// �}�N����`
//-----------------------------------
#define MAX_TEXTURE		(256)			// �e�N�X�`���̍ő吔

//-----------------------------------
// �N���X��`(�e�N�X�`��)
//-----------------------------------
class CTexture
{
public:			// �N�ł��A�N�Z�X�ł���

	CTexture();			// �R���X�g���N�^
	~CTexture();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Unload(void);		// �j������

	int Regist(const char* pFilename);						// �e�N�X�`���̓o�^����
	LPDIRECT3DTEXTURE9 GetAddress(const int nIdx) const;	// �e�N�X�`���̎擾����
	char *GetTexName(const int nIdx);	// �e�N�X�`���̎擾����
	HRESULT Load(void);		// ���[�h����

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEXTURE];			// �e�N�X�`���̏��
	char m_aTextureName[MAX_TEXTURE][MAX_STRING];			// �e�N�X�`���̃p�X��

	// �ÓI�����o�ϐ�
	static int m_nNumAll;									// �e�N�X�`���̑���
};


#endif