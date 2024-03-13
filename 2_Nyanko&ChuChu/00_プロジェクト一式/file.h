//============================================
//
// �t�@�C���w�b�_�[[file.h]
// Author�F��������
//
//============================================
#ifndef _FILE_H_			//���̃}�N����`������Ă��Ȃ�������
#define _FILE_H_			//2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "main.h"
#include "obstacle.h"
#include "block.h"

//--------------------------------------------
// �}�N����`
//--------------------------------------------
#define MAX_FILE_DATA		(512)		// �t�@�C���̃f�[�^�̍ő吔

//--------------------------------------------
// �N���X(�t�@�C���ǂݍ��݃N���X)
//--------------------------------------------
class CFile
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_OBSTACLE = 0,	// ��Q��
		TYPE_MAP_OBSTACLE1,	// �}�b�v�̏�Q��1
		TYPE_MAP_OBSTACLE2,	// �}�b�v�̏�Q��2
		TYPE_MAP_OBSTACLE3,	// �}�b�v�̏�Q��3
		TYPE_MAP_OBSTACLESAMPLE,	// �}�b�v�̏�Q���T���v��
		TYPE_MAP_BLOCK1,	// �}�b�v�̃u���b�N1
		TYPE_MAP_BLOCK2,	// �}�b�v�̃u���b�N2
		TYPE_MAP_BLOCK3,	// �}�b�v�̃u���b�N3
		TYPE_MAP_BLOCKSAMPLE,	// �}�b�v�̃u���b�N�T���v��
		TYPE_BLOCK,			// �u���b�N
		TYPE_TUTORIAL_DEFULT,	// �`���[�g���A���̃f�t�H���g�u���b�N
		TYPE_TUTORIAL_TABLE,	//�`���[�g���A���̃e�[�u���p�u���b�N
		TYPE_TUTORIAL_KILL,		// �`���[�g���A���̃L���p�u���b�N
		TYPE_TUTORIAL_ACTION,	// �`���[�g���A���̃A�N�V�����p�u���b�N
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	// ��Q���̏��
	struct SObstacleInfo
	{
		D3DXVECTOR3 pos[MAX_FILE_DATA];			// �ʒu
		D3DXVECTOR3 rot[MAX_FILE_DATA];			// ����
		CObstacle::TYPE type[MAX_FILE_DATA];	// ���
		int nNum;								// ����
		bool bSuccess;							// ������
	};

	// �u���b�N�̏��
	struct SBlockInfo
	{
		D3DXVECTOR3 pos[MAX_FILE_DATA];			// �ʒu
		CBlock::ROTTYPE rotType[MAX_FILE_DATA];	// �����̎��
		CBlock::TYPE type[MAX_FILE_DATA];		// ���
		int nNum;								// ����
		bool bSuccess;							// ������
	};

	CFile();					// �R���X�g���N�^
	~CFile();					// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);			// ����������
	void Uninit(void);			// �I������

	HRESULT Save(const TYPE type);	// �Z�[�u����
	HRESULT Load(const TYPE type);	// ���[�h����

	void FalseSuccess(void);		// �����󋵂̃��Z�b�g
	void SetMap(void);				// �}�b�v�̐ݒ菈��

private:		// �����̂݃A�N�Z�X�ł���

	// �����o�֐�(�Z�[�u�֌W)
	HRESULT SaveObstacle(const char *cFileName);		// ��Q���̃Z�[�u����
	HRESULT SaveBlock(const char *cFileName);			// �u���b�N�̃Z�[�u����

	// �����o�֐�(���[�h�֌W)
	HRESULT LoadObstacle(const char *cFileName);		// ��Q���̃��[�h����
	HRESULT LoadBlock(const char *cFileName);		// �u���b�N�̃��[�h����

	// �����o�ϐ�
	SObstacleInfo m_ObstacleInfo;	// ��Q���̏��
	SBlockInfo m_BlockInfo;			// �u���b�N�̏��

	// �ÓI�����o�ϐ�
	static const char* c_apBooleanDisp[2];			// bool�^�̕\��
};

#endif