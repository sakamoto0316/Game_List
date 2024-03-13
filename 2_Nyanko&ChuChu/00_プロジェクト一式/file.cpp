//============================================
//
// �t�@�C���̃��C������[file.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "manager.h"
#include "scene.h"
#include "file.h"
#include "object.h"

#include "obstacle_manager.h"
#include "block_manager.h"
#include "game.h"
#include "edit.h"

//--------------------------------------------
// �������O���
//--------------------------------------------
namespace
{
	const char* TXT[CFile::TYPE_MAX] =
	{
		"data\\TXT\\Obstacle.txt",			// ��Q���̃e�L�X�g
		"data\\TXT\\MapObstacle1.txt",		// �}�b�v�̏�Q��1�̃e�L�X�g
		"data\\TXT\\MapObstacle2.txt",		// �}�b�v�̏�Q��2�̃e�L�X�g
		"data\\TXT\\MapObstacle3.txt",		// �}�b�v�̏�Q��3�̃e�L�X�g
		"data\\TXT\\MapObstacleSample.txt",	// �}�b�v�̏�Q���T���v���̃e�L�X�g
		"data\\TXT\\Block1.txt",			// �}�b�v�̃u���b�N1�̃e�L�X�g
		"data\\TXT\\Block2.txt",			// �}�b�v�̃u���b�N2�̃e�L�X�g
		"data\\TXT\\Block3.txt",			// �}�b�v�̃u���b�N3�̃e�L�X�g
		"data\\TXT\\BlockSample.txt",		// �}�b�v�̃u���b�N�T���v���̃e�L�X�g
		"data\\TXT\\Block.txt",				// �u���b�N�̃e�L�X�g
		"data\\TXT\\Tutorial.txt",			// �`���[�g���A���̃f�t�H���g�u���b�N
		"data\\TXT\\TutorialTable.txt",		//�`���[�g���A���̃e�[�u���p�u���b�N
		"data\\TXT\\TutorialKill.txt",		// �`���[�g���A���̃L���p�u���b�N
		"data\\TXT\\TutorialAction.txt",	// �`���[�g���A���̃A�N�V�����p�u���b�N
	};
}

//--------------------------------------------
// �ÓI�����o�ϐ��錾
//--------------------------------------------
const char* CFile::c_apBooleanDisp[2] =					// bool�^�̕\��
{
	"FALSE",							// TRUE
	"TRUE",								// FALSE
};

//===========================================
// �R���X�g���N�^
//===========================================
CFile::CFile()
{
	for (int nCntInfo = 0; nCntInfo < MAX_FILE_DATA; nCntInfo++)
	{
		m_ObstacleInfo.pos[nCntInfo] = NONE_D3DXVECTOR3;		// �ʒu
		m_ObstacleInfo.rot[nCntInfo] = NONE_D3DXVECTOR3;		// �ʒu
		m_ObstacleInfo.type[nCntInfo] = CObstacle::TYPE_HONEY;	// ���
		m_BlockInfo.pos[nCntInfo] = NONE_D3DXVECTOR3;			// �ʒu
		m_BlockInfo.rotType[nCntInfo] = CBlock::ROTTYPE_FRONT;	// �����̎��
		m_BlockInfo.type[nCntInfo] = CBlock::TYPE_CARDBOARD;	// ���
	}

	// �������N���A����
	m_ObstacleInfo.nNum = 0;			// ��Q��
	m_BlockInfo.nNum = 0;				// �u���b�N

	// �����󋵂��N���A����
	m_ObstacleInfo.bSuccess = false;	// ��Q��
	m_BlockInfo.bSuccess = false;		// �u���b�N
}

//===========================================
// �f�X�g���N�^
//===========================================
CFile::~CFile()
{

}

//===========================================
// �Z�[�u����
//===========================================
HRESULT CFile::Save(const TYPE type)
{
	switch (type)
	{
	case TYPE_OBSTACLE:

		// ��Q���̃Z�[�u����
		if (FAILED(SaveObstacle(TXT[TYPE_OBSTACLE])))
		{ // ���s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}

		break;

	case TYPE_MAP_OBSTACLE1:

		// ��Q���̃Z�[�u����
		if (FAILED(SaveObstacle(TXT[TYPE_MAP_OBSTACLE1])))
		{ // ���s�����ꍇ

		  // ���s��Ԃ�
			return E_FAIL;
		}

		break;

	case TYPE_MAP_OBSTACLE2:

		// ��Q���̃Z�[�u����
		if (FAILED(SaveObstacle(TXT[TYPE_MAP_OBSTACLE2])))
		{ // ���s�����ꍇ

		  // ���s��Ԃ�
			return E_FAIL;
		}

		break;

	case TYPE_MAP_OBSTACLE3:

		// ��Q���̃Z�[�u����
		if (FAILED(SaveObstacle(TXT[TYPE_MAP_OBSTACLE3])))
		{ // ���s�����ꍇ

		  // ���s��Ԃ�
			return E_FAIL;
		}

		break;

	case TYPE_MAP_OBSTACLESAMPLE:

		// ��Q���̃Z�[�u����
		if (FAILED(SaveObstacle(TXT[TYPE_MAP_OBSTACLESAMPLE])))
		{ // ���s�����ꍇ

		  // ���s��Ԃ�
			return E_FAIL;
		}

		break;

	case TYPE_MAP_BLOCK1:

		// ��Q���̃Z�[�u����
		if (FAILED(SaveBlock(TXT[TYPE_MAP_BLOCK1])))
		{ // ���s�����ꍇ

		  // ���s��Ԃ�
			return E_FAIL;
		}

		break;

	case TYPE_MAP_BLOCK2:

		// ��Q���̃Z�[�u����
		if (FAILED(SaveBlock(TXT[TYPE_MAP_BLOCK2])))
		{ // ���s�����ꍇ

		  // ���s��Ԃ�
			return E_FAIL;
		}

		break;

	case TYPE_MAP_BLOCK3:

		// ��Q���̃Z�[�u����
		if (FAILED(SaveBlock(TXT[TYPE_MAP_BLOCK3])))
		{ // ���s�����ꍇ

		  // ���s��Ԃ�
			return E_FAIL;
		}

		break;

	case TYPE_MAP_BLOCKSAMPLE:

		// ��Q���̃Z�[�u����
		if (FAILED(SaveBlock(TXT[TYPE_MAP_BLOCKSAMPLE])))
		{ // ���s�����ꍇ

		  // ���s��Ԃ�
			return E_FAIL;
		}

		break;

	case TYPE_BLOCK:

		// �u���b�N�̃Z�[�u����
		if (FAILED(SaveBlock(TXT[TYPE_BLOCK])))
		{ // ���s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}

	case TYPE_TUTORIAL_DEFULT:

		// �u���b�N�̃Z�[�u����
		if (FAILED(SaveBlock(TXT[TYPE_TUTORIAL_DEFULT])))
		{ // ���s�����ꍇ

		  // ���s��Ԃ�
			return E_FAIL;
		}

		break;

	case TYPE_TUTORIAL_TABLE:

		// �u���b�N�̃Z�[�u����
		if (FAILED(SaveBlock(TXT[TYPE_TUTORIAL_TABLE])))
		{ // ���s�����ꍇ

		  // ���s��Ԃ�
			return E_FAIL;
		}

		break;

	case TYPE_TUTORIAL_KILL:

		// �u���b�N�̃Z�[�u����
		if (FAILED(SaveBlock(TXT[TYPE_TUTORIAL_KILL])))
		{ // ���s�����ꍇ

		  // ���s��Ԃ�
			return E_FAIL;
		}

		break;

	case TYPE_TUTORIAL_ACTION:

		// �u���b�N�̃Z�[�u����
		if (FAILED(SaveBlock(TXT[TYPE_TUTORIAL_ACTION])))
		{ // ���s�����ꍇ

		  // ���s��Ԃ�
			return E_FAIL;
		}

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	// ������Ԃ�
	return S_OK;
}

//===========================================
// ���[�h����
//===========================================
HRESULT CFile::Load(const TYPE type)
{
	switch (type)
	{
	case TYPE_OBSTACLE:

		// ��Q���̃��[�h����
		if (FAILED(LoadObstacle(TXT[TYPE_OBSTACLE])))
		{ // ���s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}

		break;

	case TYPE_MAP_OBSTACLE1:

		// ��Q���̃��[�h����
		if (FAILED(LoadObstacle(TXT[TYPE_MAP_OBSTACLE1])))
		{ // ���s�����ꍇ

		  // ���s��Ԃ�
			return E_FAIL;
		}

		break;

	case TYPE_MAP_OBSTACLE2:

		// ��Q���̃��[�h����
		if (FAILED(LoadObstacle(TXT[TYPE_MAP_OBSTACLE2])))
		{ // ���s�����ꍇ

		  // ���s��Ԃ�
			return E_FAIL;
		}

		break;

	case TYPE_MAP_OBSTACLE3:

		// ��Q���̃��[�h����
		if (FAILED(LoadObstacle(TXT[TYPE_MAP_OBSTACLE3])))
		{ // ���s�����ꍇ

		  // ���s��Ԃ�
			return E_FAIL;
		}

		break;

	case TYPE_MAP_OBSTACLESAMPLE:

		// ��Q���̃��[�h����
		if (FAILED(LoadObstacle(TXT[TYPE_MAP_OBSTACLESAMPLE])))
		{ // ���s�����ꍇ

		  // ���s��Ԃ�
			return E_FAIL;
		}

		break;

	case TYPE_MAP_BLOCK1:

		// ��Q���̃��[�h����
		if (FAILED(LoadBlock(TXT[TYPE_MAP_BLOCK1])))
		{ // ���s�����ꍇ

		  // ���s��Ԃ�
			return E_FAIL;
		}

		break;

	case TYPE_MAP_BLOCK2:

		// ��Q���̃��[�h����
		if (FAILED(LoadBlock(TXT[TYPE_MAP_BLOCK2])))
		{ // ���s�����ꍇ

		  // ���s��Ԃ�
			return E_FAIL;
		}

		break;

	case TYPE_MAP_BLOCK3:

		// ��Q���̃��[�h����
		if (FAILED(LoadBlock(TXT[TYPE_MAP_BLOCK3])))
		{ // ���s�����ꍇ

		  // ���s��Ԃ�
			return E_FAIL;
		}

		break;

	case TYPE_MAP_BLOCKSAMPLE:

		// ��Q���̃��[�h����
		if (FAILED(LoadBlock(TXT[TYPE_MAP_BLOCKSAMPLE])))
		{ // ���s�����ꍇ

		  // ���s��Ԃ�
			return E_FAIL;
		}

		break;

	case TYPE_BLOCK:

		// �u���b�N�̃��[�h����
		if (FAILED(LoadBlock(TXT[TYPE_BLOCK])))
		{ // ���s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}

		break;

	case TYPE_TUTORIAL_DEFULT:

		// �u���b�N�̃��[�h����
		if (FAILED(LoadBlock(TXT[TYPE_TUTORIAL_DEFULT])))
		{ // ���s�����ꍇ

		  // ���s��Ԃ�
			return E_FAIL;
		}

		break;

	case TYPE_TUTORIAL_TABLE:

		// �u���b�N�̃��[�h����
		if (FAILED(LoadBlock(TXT[TYPE_TUTORIAL_TABLE])))
		{ // ���s�����ꍇ

		  // ���s��Ԃ�
			return E_FAIL;
		}
		break;

	case TYPE_TUTORIAL_KILL:

		// �u���b�N�̃��[�h����
		if (FAILED(LoadBlock(TXT[TYPE_TUTORIAL_KILL])))
		{ // ���s�����ꍇ

		  // ���s��Ԃ�
			return E_FAIL;
		}

		break;

	case TYPE_TUTORIAL_ACTION:

		// �u���b�N�̃��[�h����
		if (FAILED(LoadBlock(TXT[TYPE_TUTORIAL_ACTION])))
		{ // ���s�����ꍇ

			// ���s��Ԃ�
			return E_FAIL;
		}

		break;

	default:

		// ��~
		assert(false);

		break;
	}

	// ���ʂ�Ԃ�
	return S_OK;
}

//===========================================
// �}�b�v�̐ݒ菈��
//===========================================
void CFile::FalseSuccess(void)
{
	// �����󋵂��N���A����
	m_ObstacleInfo.bSuccess = false;	// ��Q��
	m_BlockInfo.bSuccess = false;		// �u���b�N
}

//===========================================
// �}�b�v�̐ݒ菈��
//===========================================
void CFile::SetMap(void)
{
	if (m_BlockInfo.bSuccess == true)
	{ // �����󋵂� true �̏ꍇ

		for (int nCntBlock = 0; nCntBlock < m_BlockInfo.nNum; nCntBlock++)
		{
			// �u���b�N�̐�������
			CBlock::Create(m_BlockInfo.pos[nCntBlock], m_BlockInfo.rotType[nCntBlock], m_BlockInfo.type[nCntBlock]);
		}
	}

	if (m_ObstacleInfo.bSuccess == true)
	{ // �����󋵂� true �̏ꍇ

		for (int nCntObst = 0; nCntObst < m_ObstacleInfo.nNum; nCntObst++)
		{
			// ��Q���̐�������
			CObstacle::Create(m_ObstacleInfo.pos[nCntObst], m_ObstacleInfo.rot[nCntObst], m_ObstacleInfo.type[nCntObst]);
		}
	}
}

//===========================================
// ����������
//===========================================
HRESULT CFile::Init(void)
{
	for (int nCntInfo = 0; nCntInfo < MAX_FILE_DATA; nCntInfo++)
	{
		m_ObstacleInfo.pos[nCntInfo] = NONE_D3DXVECTOR3;		// �ʒu
		m_ObstacleInfo.rot[nCntInfo] = NONE_D3DXVECTOR3;		// �ʒu
		m_ObstacleInfo.type[nCntInfo] = CObstacle::TYPE_HONEY;	// ���
		m_BlockInfo.pos[nCntInfo] = NONE_D3DXVECTOR3;			// �ʒu
		m_BlockInfo.rotType[nCntInfo] = CBlock::ROTTYPE_FRONT;	// �����̎��
		m_BlockInfo.type[nCntInfo] = CBlock::TYPE_CARDBOARD;	// ���
	}

	// �������N���A����
	m_ObstacleInfo.nNum = 0;			// ��Q��
	m_BlockInfo.nNum = 0;				// �u���b�N

	// �����󋵂��N���A����
	m_ObstacleInfo.bSuccess = false;	// ��Q��
	m_BlockInfo.bSuccess = false;		// �u���b�N

	// ������Ԃ�
	return S_OK;
}

//===========================================
// �I������
//===========================================
void CFile::Uninit(void)
{

}

//===========================================
// ��Q���̃Z�[�u����
//===========================================
HRESULT CFile::SaveObstacle(const char *cFileName)
{
	// ���[�J���ϐ��錾
	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();		// �擪�̏�Q����������

	// �|�C���^��錾
	FILE *pFile;				// �t�@�C���|�C���^

	// �t�@�C����ǂݍ��݌`���ŊJ��
	pFile = fopen(cFileName, "w");

	if (pFile != nullptr)
	{ // �t�@�C�����J�����ꍇ

		while (pObstacle != nullptr)
		{ // �I�u�W�F�N�g�ւ̃|�C���^�� NULL ����Ȃ������ꍇ

			// ���������������
			fprintf(pFile, "SET_OBSTACLE\n");	// ��Q���̐ݒ����������

			fprintf(pFile, "\tPOS = ");			// �ʒu�̐ݒ����������
			fprintf(pFile, "%.1f %.1f %.1f\n", pObstacle->GetPos().x, pObstacle->GetPos().y, pObstacle->GetPos().z);			// �ʒu����������

			fprintf(pFile, "\tROT = ");			// �ʒu�̐ݒ����������
			fprintf(pFile, "%.1f %.1f %.1f\n", pObstacle->GetRot().x, pObstacle->GetRot().y, pObstacle->GetRot().z);			// ��������������

			fprintf(pFile, "\tTYPE = ");		// ��ނ̐ݒ����������
			fprintf(pFile, "%d\n", pObstacle->GetType());			// ��ނ���������

			// ���������������
			fprintf(pFile, "END_SET_OBSTACLE\n\n");	// ��Q���̐ݒ�̏I������������

			// ���̃I�u�W�F�N�g��������
			pObstacle = pObstacle->GetNext();
		}

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

//===========================================
// �u���b�N�̃Z�[�u����
//===========================================
HRESULT CFile::SaveBlock(const char *cFileName)
{
	// ���[�J���ϐ��錾
	CBlock* pBlock = CBlockManager::Get()->GetTop();		// �擪�̃u���b�N��������

	// �|�C���^��錾
	FILE *pFile;				// �t�@�C���|�C���^

	// �t�@�C����ǂݍ��݌`���ŊJ��
	pFile = fopen(cFileName, "w");

	if (pFile != nullptr)
	{ // �t�@�C�����J�����ꍇ

		while (pBlock != nullptr)
		{ // �I�u�W�F�N�g�ւ̃|�C���^�� NULL ����Ȃ������ꍇ

			// ���������������
			fprintf(pFile, "SET_BLOCK\n");		// �u���b�N�̐ݒ����������

			fprintf(pFile, "\tPOS = ");			// �ʒu�̐ݒ����������
			fprintf(pFile, "%.1f %.1f %.1f\n", pBlock->GetPos().x, pBlock->GetPos().y, pBlock->GetPos().z);			// �ʒu����������

			fprintf(pFile, "\tROT = ");			// �����̐ݒ����������
			fprintf(pFile, "%.1f %.1f %.1f\n", pBlock->GetRot().x, pBlock->GetRot().y, pBlock->GetRot().z);			// ��������������

			fprintf(pFile, "\tTYPE = ");		// ��ނ̐ݒ����������
			fprintf(pFile, "%d\n", pBlock->GetType());			// ��ނ���������

			// ���������������
			fprintf(pFile, "END_SET_BLOCK\n\n");	// �u���b�N�̐ݒ�̏I������������

			// ���̃I�u�W�F�N�g��������
			pBlock = pBlock->GetNext();
		}

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

//===========================================
// ��Q���̃��[�h����
//===========================================
HRESULT CFile::LoadObstacle(const char *cFileName)
{
	// �ϐ���錾
	int nEnd;							// �e�L�X�g�ǂݍ��ݏI���̊m�F�p
	char aString[MAX_STRING];			// �e�L�X�g�̕�����̑���p
	m_ObstacleInfo.nNum = 0;			// ����
	m_ObstacleInfo.bSuccess = false;	// ������

	// �|�C���^��錾
	FILE *pFile;						// �t�@�C���|�C���^

	// �t�@�C����ǂݍ��݌`���ŊJ��
	pFile = fopen(cFileName, "r");

	if (pFile != nullptr)
	{ // �t�@�C�����J�����ꍇ

		do
		{ // �ǂݍ��񂾕����� EOF �ł͂Ȃ��ꍇ���[�v

			// �t�@�C�����當�����ǂݍ���
			nEnd = fscanf(pFile, "%s", &aString[0]);	// �e�L�X�g��ǂݍ��݂������� EOF ��Ԃ�

			if (strcmp(&aString[0], "SET_OBSTACLE") == 0)
			{ // �ǂݍ��񂾕����� SET_OBSTACLE �̏ꍇ

				do
				{ // �ǂݍ��񂾕����� END_SET_OBSTACLE �ł͂Ȃ��ꍇ���[�v

				  // �t�@�C�����當�����ǂݍ���
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "POS") == 0)
					{ // �ǂݍ��񂾕����� POS �̏ꍇ

						fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%f%f%f",
							&m_ObstacleInfo.pos[m_ObstacleInfo.nNum].x,
							&m_ObstacleInfo.pos[m_ObstacleInfo.nNum].y,
							&m_ObstacleInfo.pos[m_ObstacleInfo.nNum].z);		// �ʒu��ǂݍ���
					}
					else if (strcmp(&aString[0], "ROT") == 0)
					{ // �ǂݍ��񂾕����� POS �̏ꍇ

						fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%f%f%f",
							&m_ObstacleInfo.rot[m_ObstacleInfo.nNum].x,
							&m_ObstacleInfo.rot[m_ObstacleInfo.nNum].y,
							&m_ObstacleInfo.rot[m_ObstacleInfo.nNum].z);		// �ʒu��ǂݍ���
					}
					else if (strcmp(&aString[0], "TYPE") == 0)
					{ // �ǂݍ��񂾕����� TYPE �̏ꍇ

						fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%d",
							&m_ObstacleInfo.type[m_ObstacleInfo.nNum]);		// �ʒu��ǂݍ���
					}

				} while (strcmp(&aString[0], "END_SET_OBSTACLE") != 0);		// �ǂݍ��񂾕����� END_SET_OBSTACLE �ł͂Ȃ��ꍇ���[�v

				// �f�[�^�̑����𑝂₷
				m_ObstacleInfo.nNum++;
			}
		} while (nEnd != EOF);				// �ǂݍ��񂾕����� EOF �ł͂Ȃ��ꍇ���[�v

		// �t�@�C�������
		fclose(pFile);

		// �����󋵂� true �ɂ���
		m_ObstacleInfo.bSuccess = true;
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

//===========================================
// �u���b�N�̃��[�h����
//===========================================
HRESULT CFile::LoadBlock(const char *cFileName)
{
	// �ϐ���錾
	int nEnd;							// �e�L�X�g�ǂݍ��ݏI���̊m�F�p
	char aString[MAX_STRING];			// �e�L�X�g�̕�����̑���p
	m_BlockInfo.nNum = 0;				// ����
	m_BlockInfo.bSuccess = false;		// ������

	// �|�C���^��錾
	FILE *pFile;						// �t�@�C���|�C���^

	// �t�@�C����ǂݍ��݌`���ŊJ��
	pFile = fopen(cFileName, "r");

	if (pFile != nullptr)
	{ // �t�@�C�����J�����ꍇ

		do
		{ // �ǂݍ��񂾕����� EOF �ł͂Ȃ��ꍇ���[�v

			// �t�@�C�����當�����ǂݍ���
			nEnd = fscanf(pFile, "%s", &aString[0]);	// �e�L�X�g��ǂݍ��݂������� EOF ��Ԃ�

			if (strcmp(&aString[0], "SET_BLOCK") == 0)
			{ // �ǂݍ��񂾕����� SET_BLOCK �̏ꍇ

				do
				{ // �ǂݍ��񂾕����� END_SET_BLOCK �ł͂Ȃ��ꍇ���[�v

				  // �t�@�C�����當�����ǂݍ���
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "POS") == 0)
					{ // �ǂݍ��񂾕����� POS �̏ꍇ

						fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%f%f%f",
							&m_BlockInfo.pos[m_BlockInfo.nNum].x,
							&m_BlockInfo.pos[m_BlockInfo.nNum].y,
							&m_BlockInfo.pos[m_BlockInfo.nNum].z);		// �ʒu��ǂݍ���
					}
					else if (strcmp(&aString[0], "ROT") == 0)
					{ // �ǂݍ��񂾕����� ROT �̏ꍇ
						float fRotType = 0.0f;

						fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%s", &aString[0]);				// ������ǂݍ��� (�s�v)
						fscanf(pFile, "%f", &fRotType);					// ������ǂݍ���
						fscanf(pFile, "%s", &aString[0]);				// ������ǂݍ��� (�s�v)

						if (fRotType <= -1.57f)
						{
							m_BlockInfo.rotType[m_BlockInfo.nNum] = CBlock::ROTTYPE::ROTTYPE_RIGHT;
						}
						else if (fRotType <= 0.1f)
						{
							m_BlockInfo.rotType[m_BlockInfo.nNum] = CBlock::ROTTYPE::ROTTYPE_FRONT;
						}
						else if (fRotType <= 1.7f)
						{
							m_BlockInfo.rotType[m_BlockInfo.nNum] = CBlock::ROTTYPE::ROTTYPE_LEFT;
						}
						else
						{
							m_BlockInfo.rotType[m_BlockInfo.nNum] = CBlock::ROTTYPE::ROTTYPE_BACK;
						}
					}
					else if (strcmp(&aString[0], "TYPE") == 0)
					{ // �ǂݍ��񂾕����� TYPE �̏ꍇ

						fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%d",
							&m_BlockInfo.type[m_BlockInfo.nNum]);		// �ʒu��ǂݍ���
					}

				} while (strcmp(&aString[0], "END_SET_BLOCK") != 0);		// �ǂݍ��񂾕����� END_SET_BLOCK �ł͂Ȃ��ꍇ���[�v

				// �f�[�^�̑����𑝂₷
				m_BlockInfo.nNum++;
			}
		} while (nEnd != EOF);				// �ǂݍ��񂾕����� EOF �ł͂Ȃ��ꍇ���[�v

		// �t�@�C�������
		fclose(pFile);

		// �����󋵂� true �ɂ���
		m_BlockInfo.bSuccess = true;
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