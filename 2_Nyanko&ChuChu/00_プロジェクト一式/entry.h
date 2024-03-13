//============================================
//
// �G���g���[��ʃw�b�_�[[entry.h]
// Author�F��������
//
//============================================
#ifndef _ENTRY_H_			//���̃}�N����`������Ă��Ȃ�������
#define _ENTRY_H_			//2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "main.h"
#include "scene.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CEntryUI;			// �G���g���[UI
class CPlayer;

//--------------------------------------------
// �N���X(�G���g���[��ʃN���X)
//--------------------------------------------
class CEntry : public CScene
{
public:				// �N�ł��A�N�Z�X�ł���

	CEntry();		// �R���X�g���N�^
	~CEntry();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);				// ����������
	void Uninit(void);				// �I������
	void Update(void);				// �X�V����
	void Draw(void);				// �`�揈��

	// �Z�b�g�E�Q�b�g�֐�
	static int GetCatIdx(void);		// �l�R�S���̎擾����

private:					// ���������A�N�Z�X�ł���

	// �ÓI�����o�ϐ�
	static int m_nCatIdx;					// �l�R�����v���C���[
	static int m_nCatOldIdx;				// �����pID
	static int m_EntryId[MAX_PLAY];			// �S�̂�ID
	static CEntryUI* m_apUI[MAX_PLAY];		// �G���g���[UI�̏��
	static CPlayer*  m_apPlayer[MAX_PLAY];	// ���f�����
	bool m_bEnter;							// �G���^�[�����������ǂ���
	int m_nSceneCnt;						// �J�ڂ܂ł̃J�E���g
};

#endif