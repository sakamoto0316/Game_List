//============================================================
//
//	���[�V�����w�b�_�[ [motion.h]
//	Author�F��������
//
//============================================================
#ifndef _MOTION_H_	// ���̃}�N����`������Ă��Ȃ��ꍇ
#define _MOTION_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"
#include "character.h"

//------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------
#define MAX_KEY			(10)				// �L�[�̑���
#define MAX_MOTION		(20)				// ���[�V�����̍ő吔

// �N���X��`(CMotion)
class CMotion
{
public:			// �N�ł��A�N�Z�X�ł���

	//------------------------------------------------------------
	// �񋓌^��`(���)
	//------------------------------------------------------------
	enum STYLE
	{
		TYPE_CAT = 0,				// �L
		TYPE_RAT,					// �l�Y�~
		TYPE_MAX					// ���̗񋓌^�̑���
	};

	//------------------------------------------------------------
	//	�\���̒�`(�L�[�̍\����)
	//------------------------------------------------------------
	struct Key
	{
		float fPosX;				// �ʒuX
		float fPosY;				// �ʒuY
		float fPosZ;				// �ʒuZ
		float fRotX;				// ����X
		float fRotY;				// ����Y
		float fRotZ;				// ����Z
	};

	//------------------------------------------------------------
	//	�\���̒�`(�L�[���̍\����)
	//------------------------------------------------------------
	struct Key_Info
	{
		int nFrame;					// �Đ��t���[��
		Key aKey[MAX_PARTS];		// �e���f���̃L�[�v�f
	};

	//------------------------------------------------------------
	//	�\���̒�`(���[�V�������̍\����)
	//------------------------------------------------------------
	struct Info
	{
		bool bLoop;					// ���[�v���邩���Ȃ���
		int nNumKey;				// �L�[�̑���
		int nNumFrame;				// �t���[���̑���
		Key_Info aKeyInfo[MAX_KEY];	// �L�[�̏��
	};

	CMotion();				// �R���X�g���N�^
	~CMotion();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);									// ����������
	void Uninit(void);									// �I������
	void ResetData(void);								// ���[�V�������̃��Z�b�g����
	void Set(int nType);								// ���[�V�����̎�ނ̐ݒ菈��
	void SetForcibly(void);								// ���[�V�����̎�ނ̋����ݒ菈��
	void Update(void);									// ���[�V�����̍X�V����
	int GetType(void);									// ��ނ̎擾����
	bool IsFinish(void);								// ���[�V�����̏I������
	void SetInfo(Info info);							// ���[�V�����̏��̐ݒ菈��
	void SetModel(CHierarchy **ppHier, int nNumModel);	// ���f���̐ݒ菈��
	void Load(STYLE type);								// ���[�V�����̃��[�h����
	void LoadMotion(const char *pFilename);				// �w�肳�ꂽ�t�@�C���̃��[�V�����̃��[�h����

	// �ÓI�����o�֐�
	static CMotion* Create();							// ���[�V�����̐�������

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	D3DXVECTOR3 m_posInit[MAX_PARTS];	// �����ʒu
	D3DXVECTOR3 m_posPast[MAX_PARTS];	// �ߋ��̈ʒu
	D3DXVECTOR3 m_rotPast[MAX_PARTS];	// �ߋ��̌���
	Info m_aInfo[MAX_MOTION];			// ���
	STYLE m_style;						// ���[�V���������҂̎��
	int m_nNumAll;						// ���[�V�����̑���
	int m_nType;						// ���
	int m_nNumKey;						// �L�[�̑���
	int m_nKey;							// ���݂̃L�[
	int m_nCounter;						// �J�E���^�[
	int m_nStopFrame;					// ��~����t���[����
	bool m_bLoop;						// ���[�v��
	bool m_bFinish;						// �I���������ǂ���
	CHierarchy** m_ppModel;				// ���f���ւ̃_�u���|�C���^
	int m_nNumModel;					// ���f���̑���
};

#endif