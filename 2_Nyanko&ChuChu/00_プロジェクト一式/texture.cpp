//============================================
//
// �e�N�X�`������[texture.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "texture.h"
#include "manager.h"
#include "renderer.h"

// �}�N����`
#define LOAD_TXT		"data/TXT/Texture.txt"		// �e�N�X�`���̏��e�L�X�g

//--------------------------------------------
// �ÓI�����o�ϐ��錾
//--------------------------------------------
int CTexture::m_nNumAll = 0;						// �e�N�X�`���̑���

//--------------------------------------------
// �R���X�g���N�^
//--------------------------------------------
CTexture::CTexture()
{
	// �S�Ă̏����N���A����
	for (int nCnt = 0; nCnt < MAX_TEXTURE; nCnt++)
	{
		m_apTexture[nCnt] = nullptr;		// �e�N�X�`���̏��
		*m_aTextureName[nCnt] = {};			// �e�N�X�`���̃p�X
	}
}

//--------------------------------------------
// �f�X�g���N�^
//--------------------------------------------
CTexture::~CTexture()
{

}

//--------------------------------------------
// �ǂݍ��ݏ���
//--------------------------------------------
HRESULT CTexture::Init(void)
{
	// �S�Ă̒l������������
	for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		m_apTexture[nCntTex] = nullptr;			// �e�N�X�`���̃|�C���^
		*m_aTextureName[nCntTex] = {};			// �e�N�X�`���̃p�X
	}

	// ������Ԃ�
	return S_OK;
}

//--------------------------------------------
// �j������
//--------------------------------------------
void CTexture::Unload(void)
{
	for (int nCntUn = 0; nCntUn < MAX_TEXTURE; nCntUn++)
	{
		if (m_apTexture[nCntUn] != nullptr)
		{ // �e�N�X�`���̔j��

			m_apTexture[nCntUn]->Release();
			m_apTexture[nCntUn] = nullptr;

			// �e�N�X�`���̑��������Z����
			m_nNumAll--;
		}
	}
}

//--------------------------------------------
// �e�N�X�`���̓o�^����
//--------------------------------------------
int CTexture::Regist(const char* pFilename)
{
	// ���[�J���ϐ��錾
	int nNumRegist = NONE_TEXIDX;		// �Ԃ�l�p�ϐ�

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	if (pFilename != nullptr)
	{ // �t�@�C������ NULL ����Ȃ��ꍇ

		for (int nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
		{
			if (m_apTexture[nCntTex] == nullptr)
			{ // �|�C���^�� NULL �̏ꍇ

				// �e�N�X�`���̓ǂݍ���
				if (FAILED(D3DXCreateTextureFromFile
				(
					pDevice,
					pFilename,					// �e�N�X�`���̑��΃p�X
					&m_apTexture[nCntTex]		// �e�N�X�`���̃|�C���^
				)))
				{ // �e�N�X�`���̐����Ɏ��s�����ꍇ

					// �x����
					MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s�I", "�x���I", MB_ICONWARNING);

					// ���s��Ԃ�
					return NONE_TEXIDX;
				}

				// �Ԃ�l�p�ϐ��ɔԍ���������
				nNumRegist = nCntTex;

				// �e�N�X�`���̑��������Z����
				m_nNumAll++;

				// �p�X��o�^����
				strcpy(&m_aTextureName[nCntTex][0], pFilename);

				// �����o��
				break;
			}
			else
			{ // �|�C���^�� NULL ����Ȃ��ꍇ

				if (strcmp(&m_aTextureName[nCntTex][0], pFilename) == 0)
				{ // �ߋ��ɓǂݍ���ł����ꍇ

					// �Ԃ�l�p�ϐ��ɔԍ���������
					nNumRegist = nCntTex;

					// �����o��
					break;
				}
			}
		}

		// �C���f�b�N�X��Ԃ�
		return nNumRegist;
	}
	else
	{ // ��L�ȊO

		// -1 ��Ԃ�
		return NONE_TEXIDX;
	}
}

//--------------------------------------------
// �e�N�X�`���̎擾����
//--------------------------------------------
LPDIRECT3DTEXTURE9 CTexture::GetAddress(const int nIdx) const
{
	if (nIdx > NONE_TEXIDX)
	{ // �e�N�X�`���̔ԍ��� -1 �ȏ�̏ꍇ

		// �e�N�X�`���̏���Ԃ�
		return m_apTexture[nIdx];
	}
	else
	{ // ��L�ȊO

		// NULL ��Ԃ�
		return nullptr;
	}
}

//--------------------------------------------
// �e�N�X�`���̎擾����
//--------------------------------------------
char *CTexture::GetTexName(const int nIdx)
{
	if (nIdx > NONE_TEXIDX)
	{ // �e�N�X�`���̔ԍ��� -1 �ȏ�̏ꍇ

	  // �e�N�X�`���̏���Ԃ�
		return &m_aTextureName[nIdx][0];
	}
	return NULL;
}

//--------------------------------------------
// ���[�h����
//--------------------------------------------
HRESULT CTexture::Load(void)
{
	// ���[�J���ϐ��錾
	int nEnd;						// �e�L�X�g�ǂݍ��ݏI���̊m�F�p
	char aString[MAX_STRING];		// �e�L�X�g�̕�����̑���p
	char aTextureName[MAX_STRING];	// �e�N�X�`���̖��O(���΃p�X)

	// �|�C���^��錾
	FILE *pFile;						// �t�@�C���|�C���^

	// �t�@�C����ǂݍ��݌`���ŊJ��
	pFile = fopen(LOAD_TXT, "r");

	if (pFile != nullptr)
	{ // �t�@�C�����J�����ꍇ

		do
		{ // �ǂݍ��񂾕����� EOF �ł͂Ȃ��ꍇ���[�v

			// �t�@�C�����當�����ǂݍ���
			nEnd = fscanf(pFile, "%s", &aString[0]);	// �e�L�X�g��ǂݍ��݂������� EOF ��Ԃ�

			if (strcmp(&aString[0], "TEXTURE") == 0)
			{ // �ǂݍ��񂾕����� TEXTURE �̏ꍇ

				fscanf(pFile, "%s", &aString[0]);			// = ��ǂݍ��� (�s�v)
				fscanf(pFile, "%s", &aTextureName[0]);		// �e�N�X�`���̑��΃p�X��ǂݍ���

				// �e�N�X�`���̓o�^����
				Regist(&aTextureName[0]);
			}
		} while (nEnd != EOF);				// �ǂݍ��񂾕����� EOF �ł͂Ȃ��ꍇ���[�v

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{ // �t�@�C�����J���Ȃ������ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}