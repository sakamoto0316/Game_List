//======================================================================================================================
//
//	���[�V�������� [motion.cpp]
//	Author�F��������
//
//======================================================================================================================
//**********************************************************************************************************************
//	�C���N���[�h�t�@�C��
//**********************************************************************************************************************
#include "main.h"
#include "input.h"
#include "useful.h"
#include "motion.h"
#include "manager.h"
#include "result.h"
#include "game.h"

#include "debugproc.h"

//----------------------------------------------------------------------------------------------------------------------
// �}�N����`
//----------------------------------------------------------------------------------------------------------------------
#define MOTION_SET_FRAME		(7)			// ���[�V�����ݒ莞�̃t���[����

//============================================================
// �R���X�g���N�^
//============================================================
CMotion::CMotion()
{
	// ���Z�b�g����
	ResetData();
}

//============================================================
// �f�X�g���N�^
//============================================================
CMotion::~CMotion()
{

}

//============================================================
// ����������
//============================================================
HRESULT CMotion::Init(void)
{
	// ���Z�b�g����
	ResetData();

	// ������Ԃ�
	return S_OK;
}

//============================================================
// �I������
//============================================================
void CMotion::Uninit(void)
{

}

//============================================================
// ���[�V�������̃��Z�b�g����
//============================================================
void CMotion::ResetData(void)
{
	for (int nCntMotion = 0; nCntMotion < MAX_MOTION; nCntMotion++)
	{ // ���[�V�����̎�ޕ�����������

		// ���[�V�����̏���������
		m_aInfo[nCntMotion].nNumKey = 0;		// �L�[�̑���
		m_aInfo[nCntMotion].bLoop = false;		// ���[�v���邩�ǂ���
		m_aInfo[nCntMotion].nNumFrame = 0;		// ���t���[����

		for (int nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
		{ // �L�[�̐�����������

			// �L�[�̏�������������
			m_aInfo[nCntMotion].aKeyInfo[nCntKey].nFrame = 0;		// �t���[����

			for (int nCntPart = 0; nCntPart < MAX_PARTS; nCntPart++)
			{ // �p�[�c������������

				// ���W�̏�������������
				m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntPart].fPosX = 0.0f;			// �ʒu(X���W)
				m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntPart].fPosY = 0.0f;			// �ʒu(Y���W)
				m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntPart].fPosZ = 0.0f;			// �ʒu(Z���W)
				m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntPart].fRotX = 0.0f;			// ����(X���W)
				m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntPart].fRotY = 0.0f;			// ����(Y���W)
				m_aInfo[nCntMotion].aKeyInfo[nCntKey].aKey[nCntPart].fRotZ = 0.0f;			// ����(Z���W)
			}
		}
	}

	for (int nCntPos = 0; nCntPos < MAX_PARTS; nCntPos++)
	{
		m_posInit[nCntPos] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �����ʒu
		m_rotPast[nCntPos] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ߋ��̌���
		m_posPast[nCntPos] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ߋ��̈ʒu
	}

	// ���[�V�����̏�������������
	m_nNumAll = 0;			// ���[�V�����̑���
	m_nType = 0;			// ���
	m_nKey = 0;				// ���݂̃L�[
	m_nCounter = 0;			// �J�E���^�[
	m_nStopFrame = 0;		// ��~����t���[����
	m_bLoop = false;		// ���[�v��
	m_bFinish = false;		// �I���������ǂ���
	m_ppModel = nullptr;	// ���f���̃|�C���^
	m_nNumModel = 0;		// ���f���̑���
	m_nNumKey = 0;			// �L�[�̑���
}

//============================================================
// ���[�V�����̎�ނ̐ݒ菈��
//============================================================
void CMotion::Set(int nType)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 rot;			// ����

	// ���[�V�����̏�������������
	m_nType = nType;						// ���
	m_nNumKey = m_aInfo[nType].nNumKey;		// �L�[�̑���
	m_nKey = 0;								// ���݂̃L�[
	m_nCounter = 0;							// �J�E���^�[
	m_bLoop = m_aInfo[nType].bLoop;			// ���[�v��
	m_bFinish = false;						// �I���������ǂ���
	m_nStopFrame = MOTION_SET_FRAME;		// ��~����t���[����

	// �S���f���̏����ݒ�
	switch (m_style)
	{
	case TYPE_CAT:			// �L

		for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
		{
			// �ʒu�ƌ������擾
			rot = m_ppModel[nCntModel]->GetRot();

			// �p�[�c�̈ʒu�E������ݒ�
			m_posPast[nCntModel].x = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fPosX;
			m_posPast[nCntModel].y = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fPosY;
			m_posPast[nCntModel].z = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fPosZ;
			m_rotPast[nCntModel].x = rot.x;
			m_rotPast[nCntModel].y = rot.y;
			m_rotPast[nCntModel].z = rot.z;
		}

	case TYPE_RAT:			// �l�Y�~

		for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
		{
			// �ʒu�ƌ������擾
			rot = m_ppModel[nCntModel]->GetRot();

			// �p�[�c�̈ʒu�E������ݒ�
			m_posPast[nCntModel].x = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fPosX;
			m_posPast[nCntModel].y = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fPosY;
			m_posPast[nCntModel].z = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fPosZ;
			m_rotPast[nCntModel].x = rot.x;
			m_rotPast[nCntModel].y = rot.y;
			m_rotPast[nCntModel].z = rot.z;
		}

		break;
	}
}

//============================================================
// ���[�V�����̎�ނ̋����ݒ菈��
//============================================================
void CMotion::SetForcibly(void)
{
	for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		// �p�[�c�̈ʒu�E������ݒ�
		m_posPast[nCntModel].x = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fPosX;
		m_posPast[nCntModel].y = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fPosY;
		m_posPast[nCntModel].z = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fPosZ;
		m_rotPast[nCntModel].x = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fRotX;
		m_rotPast[nCntModel].y = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fRotY;
		m_rotPast[nCntModel].z = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fRotZ;
	}
}

//============================================================
// ���[�V�����̍X�V����
//============================================================
void CMotion::Update(void)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 posDest;		// �ڕW�̈ʒu
	D3DXVECTOR3 posDiff;		// �ʒu�̍���
	D3DXVECTOR3 rotDest;		// �ڕW�̌���
	D3DXVECTOR3 rotDiff;		// �����̍���
	D3DXVECTOR3 pos;			// ���݂̈ʒu
	D3DXVECTOR3 rot;			// ���݂̌���

	if (m_bFinish == false)
	{ // �I�����Ă��Ȃ��ꍇ

		for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
		{ // �S���f��(�p�[�c)�̍X�V

			// �ʒu�ƌ������擾����
			pos = m_ppModel[nCntModel]->GetPos();
			rot = m_ppModel[nCntModel]->GetRot();

			// �ʒu�ƌ����̖ڕW�l�̐ݒ�
			posDest.x = m_aInfo[m_nType].aKeyInfo[(m_nKey + 1) % m_nNumKey].aKey[nCntModel].fPosX;
			posDest.y = m_aInfo[m_nType].aKeyInfo[(m_nKey + 1) % m_nNumKey].aKey[nCntModel].fPosY;
			posDest.z = m_aInfo[m_nType].aKeyInfo[(m_nKey + 1) % m_nNumKey].aKey[nCntModel].fPosZ;
			rotDest.x = m_aInfo[m_nType].aKeyInfo[(m_nKey + 1) % m_nNumKey].aKey[nCntModel].fRotX;
			rotDest.y = m_aInfo[m_nType].aKeyInfo[(m_nKey + 1) % m_nNumKey].aKey[nCntModel].fRotY;
			rotDest.z = m_aInfo[m_nType].aKeyInfo[(m_nKey + 1) % m_nNumKey].aKey[nCntModel].fRotZ;

			// �L�[�̏�񂩂�ʒu�E�����̍����̎Z�o
			posDiff.x = posDest.x - m_posPast[nCntModel].x;		// ���W(X��)
			posDiff.y = posDest.y - m_posPast[nCntModel].y;		// ���W(Y��)
			posDiff.z = posDest.z - m_posPast[nCntModel].z;		// ���W(Z��)
			rotDiff.x = rotDest.x - m_rotPast[nCntModel].x;		// ����(X��)
			rotDiff.y = rotDest.y - m_rotPast[nCntModel].y;		// ����(Y��)
			rotDiff.z = rotDest.z - m_rotPast[nCntModel].z;		// ����(Z��)

			// �����̍����̐��K��
			useful::RotNormalize(&rotDiff.x);
			useful::RotNormalize(&rotDiff.y);
			useful::RotNormalize(&rotDiff.z);

			// �p�[�c�̈ʒu�E������ݒ�
			pos.x = m_posInit[nCntModel].x + m_posPast[nCntModel].x + posDiff.x * ((float)(m_nCounter) / (float)(m_nStopFrame));		// ���W(X��)
			pos.y = m_posInit[nCntModel].y + m_posPast[nCntModel].y + posDiff.y * ((float)(m_nCounter) / (float)(m_nStopFrame));		// ���W(Y��)
			pos.z = m_posInit[nCntModel].z + m_posPast[nCntModel].z + posDiff.z * ((float)(m_nCounter) / (float)(m_nStopFrame));		// ���W(Z��)
			rot.x = m_rotPast[nCntModel].x + rotDiff.x * ((float)(m_nCounter) / (float)(m_nStopFrame));		// ����(X��)
			rot.y = m_rotPast[nCntModel].y + rotDiff.y * ((float)(m_nCounter) / (float)(m_nStopFrame));		// ����(Y��)
			rot.z = m_rotPast[nCntModel].z + rotDiff.z * ((float)(m_nCounter) / (float)(m_nStopFrame));		// ����(Z��)

			// �����̍����̐��K��
			useful::RotNormalize(&rot.x);
			useful::RotNormalize(&rot.y);
			useful::RotNormalize(&rot.z);

			// �ʒu�ƌ����̐ݒ菈��
			m_ppModel[nCntModel]->SetPos(pos);
			m_ppModel[nCntModel]->SetRot(rot);
		}

		// ���[�V�����J�E���^�[�����Z����
		m_nCounter++;

		if (m_nCounter >= m_nStopFrame)
		{ // ���[�V�����J�E���^�[���Đ��t���[�����ɒB�����ꍇ

			// ���[�V�����J�E���^�[������������
			m_nCounter = 0;

			// �L�[�̔ԍ������Z����
			m_nKey = (m_nKey + 1) % m_aInfo[m_nType].nNumKey;

			// ��~�t���[����ݒ肷��
			m_nStopFrame = m_aInfo[m_nType].aKeyInfo[m_nKey].nFrame;

			// �S���f���̏����ݒ�
			for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
			{
				// �ߋ��̈ʒu��ݒ�
				m_posPast[nCntModel].x = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fPosX;
				m_posPast[nCntModel].y = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fPosY;
				m_posPast[nCntModel].z = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fPosZ;

				// �ߋ��̌�����ݒ�
				m_rotPast[nCntModel].x = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fRotX;
				m_rotPast[nCntModel].y = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fRotY;
				m_rotPast[nCntModel].z = m_aInfo[m_nType].aKeyInfo[m_nKey].aKey[nCntModel].fRotZ;

				// ������␳����
				m_ppModel[nCntModel]->SetRot(m_rotPast[nCntModel]);
			}

			if (m_nKey == (m_aInfo[m_nType].nNumKey - 1))
			{ // �L�[�ԍ��������ɂȂ����ꍇ

				if (m_bLoop == false)
				{ // ���[�v���Ȃ��ꍇ

					switch (m_style)
					{
					case TYPE_CAT:			// �L

						// �I����Ԃɂ���
						m_bFinish = true;

						break;

					case TYPE_RAT:			// �l�Y�~

						// �I����Ԃɂ���
						m_bFinish = true;

						break;

					default:

						// ��~
						assert(false);

						break;
					}
				}
			}
		}

		// �f�o�b�O
		CManager::Get()->GetDebugProc()->Print("���[�V������\n");
	}
	else
	{ // ��L�ȊO

		// �f�o�b�O
		CManager::Get()->GetDebugProc()->Print("���[�V�����I��\n");
	}
}

//============================================================
// ��ނ̎擾����
//============================================================
int CMotion::GetType(void)
{
	// ��ނ�Ԃ�
	return m_nType;
}

//============================================================
// ���[�V�����̏I������
//============================================================
bool CMotion::IsFinish(void)
{
	// �I���������ǂ�����Ԃ�
	return m_bFinish;
}

//============================================================
// ���[�V�����̏��̐ݒ菈��
//============================================================
void CMotion::SetInfo(Info info)
{
	// ���[�V�����̏�������
	m_aInfo[m_nType] = info;
}

//============================================================
// ���f���̐ݒ菈��
//============================================================
void CMotion::SetModel(CHierarchy **ppHier, int nNumModel)
{
	// ���f���̏���ݒ肷��
	m_ppModel = ppHier;

	// �p�[�c�̑�����ݒ肷��
	m_nNumModel = nNumModel;
}

//============================================================
// ���[�V�����̃��[�h����
//============================================================
void CMotion::Load(STYLE type)
{
	// ��ނ�ݒ肷��
	m_style = type;

	switch (type)
	{
	case TYPE_CAT:			// �L
					
		if (CManager::Get()->GetMode() == CScene::MODE_RESULT)
		{ // ���U���g�@�l�R�̕���
			if (CResult::GetState() == CGame::STATE_RAT_WIN)
			{
				// �L�̃��[�V�����̃��[�h����
				LoadMotion("data/TXT/motion_losecat.txt");
			}
			if (CResult::GetState() == CGame::STATE_CAT_WIN)
			{
				// �L�̃��[�V�����̃��[�h����
				LoadMotion("data/TXT/motion_cat.txt");
			}
		}
		else
		{
			// �L�̃��[�V�����̃��[�h����
			LoadMotion("data/TXT/motion_cat.txt");
		}

		break;

	case TYPE_RAT:			// �l�Y�~

		// �l�Y�~�̃��[�V�����̃��[�h����
		LoadMotion("data/TXT/motion_rat.txt");

		break;

	default:

		// ��~
		assert(false);

		break;
	}
}

//============================================================
// �w�肳�ꂽ�t�@�C���̃��[�V�����̃��[�h����
//============================================================
void CMotion::LoadMotion(const char *pFilename)
{
	// �ϐ���錾
	D3DXVECTOR3 rot;				// �����̐ݒ菈��
	int nEnd;						// �e�L�X�g�ǂݍ��ݏI���̊m�F�p
	int nCntPart = 0;				// �Z�b�g�����p�[�c�̐�
	int nMotionCnt = 0;				// ���[�V�����̔ԍ�
	int nLoop = 0;					// ���[�v�̓ǂݍ��ݕϐ�
	int nCntKey = 0;				// �L�[�̔ԍ�
	int nParent = NONE_PARENT;		// �e�̔ԍ�
	char aString[MAX_STRING];		// �e�L�X�g�̕�����̑���p

	// �t�@�C���̃|�C���^��錾
	FILE  *pFile;							// �t�@�C���|�C���^

	// �t�@�C����ǂݍ��݌`���ŊJ��
	pFile = fopen(pFilename, "r");

	if (pFile != nullptr)
	{ // �t�@�C�����J�����ꍇ

		do
		{ // �ǂݍ��񂾕����� EOF �ł͂Ȃ��ꍇ���[�v

			// �t�@�C�����當�����ǂݍ���
			nEnd = fscanf(pFile, "%s", &aString[0]);	// �e�L�X�g��ǂݍ��݂������� EOF ��Ԃ�

			if (strcmp(&aString[0], "NUM_MODEL") == 0)
			{ // �ǂݍ��񂾕����� NUM_MODEL �������ꍇ

				// ���f���̐���ǂݍ���
				fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
				fscanf(pFile, "%d", &m_nNumModel);				// �����f������ǂݍ���
			}

			if (strcmp(&aString[0], "CHARACTERSET") == 0)
			{ // �ǂݍ��񂾕����� CHARACTERSET �̏ꍇ

				do
				{ // �ǂݍ��񂾕����� PARTSSET �ł͂Ȃ��ꍇ���[�v

					// �t�@�C�����當�����ǂݍ���
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "PARTSSET") == 0)
					{ // �ǂݍ��񂾕����� PARTSSET �̏ꍇ

						do
						{ // �ǂݍ��񂾕����� END_PARTSSET �ł͂Ȃ��ꍇ���[�v

							// �t�@�C�����當�����ǂݍ���
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(&aString[0], "INDEX") == 0)
							{ // �ǂݍ��񂾕����� INDEX �̏ꍇ
								fscanf(pFile, "%s", &aString[0]);		// = ��ǂݍ��� (�s�v)
								fscanf(pFile, "%d", &nCntPart);			// �p�[�c�̔ԍ���ǂݍ���
							}
							else if (strcmp(&aString[0], "PARENT") == 0)
							{ // �ǂݍ��񂾕����� PARENT �̏ꍇ
								fscanf(pFile, "%s", &aString[0]);		// = ��ǂݍ��� (�s�v)
								fscanf(pFile, "%d", &nParent);			// �e�̔ԍ���ǂݍ���

								if (nParent != NONE_PARENT)
								{ // �e�������ꍇ

									// �e�̐ݒ菈��
									m_ppModel[nCntPart]->SetParent(m_ppModel[nParent]);
								}
							}
							else if (strcmp(&aString[0], "POS") == 0)
							{ // �ǂݍ��񂾕����� POS �̏ꍇ
								fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
								fscanf(pFile, "%f%f%f",							// ���f���̈ʒu��ǂݍ���
									&m_posInit[nCntPart].x,
									&m_posInit[nCntPart].y,
									&m_posInit[nCntPart].z
								);

								// �ʒu�̐ݒ菈��
								m_ppModel[nCntPart]->SetPos(m_posInit[nCntPart]);
							}
							else if (strcmp(&aString[0], "ROT") == 0)
							{ // �ǂݍ��񂾕����� ROT �̏ꍇ
								fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
								fscanf(pFile, "%f%f%f",							// ���f���̌�����ǂݍ���
									&rot.x,
									&rot.y,
									&rot.z
								);

								// �����̐ݒ菈��
								m_ppModel[nCntPart]->SetRot(rot);
							}
						} while (strcmp(&aString[0], "END_PARTSSET") != 0);		// �ǂݍ��񂾕����� PARTSSET �ł͂Ȃ��ꍇ���[�v

						nCntPart = 0;				// �p�[�c�̔ԍ�������������
					}
				} while (strcmp(&aString[0], "END_CHARACTERSET") != 0);			// �ǂݍ��񂾕����� END_CHARACTERSET �ł͂Ȃ��ꍇ���[�v
			}

			if (strcmp(&aString[0], "MOTIONSET") == 0)
			{ // �ǂݍ��񂾕����� MOTIONSET �������ꍇ

				do
				{ // �ǂݍ��񂾕����� END_MOTIONSET �ł͂Ȃ��ꍇ���[�v

					// �t�@�C�����當�����ǂݍ���
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "LOOP") == 0)
					{ // �ǂݍ��񂾕����� LOOP �������ꍇ
						fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%d", &nLoop);					// ���[�v���邩�ǂ�����ǂݍ���

						if (nLoop == 0)
						{ // ���[�v���Ȃ������ǂݍ��񂾏ꍇ

							// ���[�v���Ȃ�����ɂ���
							m_aInfo[nMotionCnt].bLoop = false;
						}
						else
						{ // ���[�v���锻���ǂݍ��񂾏ꍇ

							// ���[�v���锻��ɂ���
							m_aInfo[nMotionCnt].bLoop = true;
						}
					}

					if (strcmp(&aString[0], "NUM_KEY") == 0)
					{ // �ǂݍ��񂾕����� NUM_KEY �������ꍇ

						fscanf(pFile, "%s", &aString[0]);							// = ��ǂݍ��� (�s�v)
						fscanf(pFile, "%d", &m_aInfo[nMotionCnt].nNumKey);			// �L�[�̑�����ǂݍ���
					}

					if (strcmp(&aString[0], "KEYSET") == 0)
					{ // �ǂݍ��񂾕����� KEYSET �̏ꍇ

						do
						{ // �ǂݍ��񂾕����� END_KEYSET �ł͂Ȃ��ꍇ���[�v

							// �t�@�C�����當�����ǂݍ���
							fscanf(pFile, "%s", &aString[0]);

							if (strcmp(&aString[0], "FRAME") == 0)
							{ // �ǂݍ��񂾕����� FRAME �������ꍇ

								fscanf(pFile, "%s", &aString[0]);											// = ��ǂݍ��� (�s�v)
								fscanf(pFile, "%d", &m_aInfo[nMotionCnt].aKeyInfo[nCntKey].nFrame);			// �t���[���̑�����ǂݍ���
							}

							if (strcmp(&aString[0], "KEY") == 0)
							{ // �ǂݍ��񂾕����� KEY �̏ꍇ

								do
								{ // �ǂݍ��񂾕����� END_KEY �ł͂Ȃ��ꍇ���[�v

									// �t�@�C�����當�����ǂݍ���
									fscanf(pFile, "%s", &aString[0]);

									if (strcmp(&aString[0], "POS") == 0)
									{ // �ǂݍ��񂾕����� POS �������ꍇ
										fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
										fscanf(pFile, "%f%f%f",							// ���f���̈ʒu��ǂݍ���
											&m_aInfo[nMotionCnt].aKeyInfo[nCntKey].aKey[nCntPart].fPosX,
											&m_aInfo[nMotionCnt].aKeyInfo[nCntKey].aKey[nCntPart].fPosY,
											&m_aInfo[nMotionCnt].aKeyInfo[nCntKey].aKey[nCntPart].fPosZ
										);
									}

									if (strcmp(&aString[0], "ROT") == 0)
									{ // �ǂݍ��񂾕����� ROT �̏ꍇ
										fscanf(pFile, "%s", &aString[0]);				// = ��ǂݍ��� (�s�v)
										fscanf(pFile, "%f%f%f",							// ���f���̌�����ǂݍ���
											&m_aInfo[nMotionCnt].aKeyInfo[nCntKey].aKey[nCntPart].fRotX,
											&m_aInfo[nMotionCnt].aKeyInfo[nCntKey].aKey[nCntPart].fRotY,
											&m_aInfo[nMotionCnt].aKeyInfo[nCntKey].aKey[nCntPart].fRotZ
										);
									}
								} while (strcmp(&aString[0], "END_KEY") != 0);		// �ǂݍ��񂾕����� END_KEY �ł͂Ȃ��ꍇ���[�v

								nCntPart++;				// �p�[�c�̔ԍ������Z����
							}

						} while (strcmp(&aString[0], "END_KEYSET") != 0);		// �ǂݍ��񂾕����� END_KEYSET �ł͂Ȃ��ꍇ���[�v

						nCntPart = 0;					// �p�[�c�̔ԍ�������������
						nCntKey++;						// �L�[�̔ԍ������Z����
					}
				} while (strcmp(&aString[0], "END_MOTIONSET") != 0);			// �ǂݍ��񂾕����� END_CHARACTERSET �ł͂Ȃ��ꍇ���[�v

				nCntKey = 0;			// �L�[�J�E���g������������
				nMotionCnt++;			// ���[�V�����̃J�E���g�����Z����
			}
		} while (nEnd != EOF);			// �ǂݍ��񂾕����� EOF �ł͂Ȃ��ꍇ���[�v

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{ // �t�@�C�����J���Ȃ������ꍇ

		// ��~
		assert(false);
	}
}

//============================================================
// ���[�V�����̐�������
//============================================================
CMotion* CMotion::Create()
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CMotion* pMotion = nullptr;	// �v���C���[�̃C���X�^���X�𐶐�

	if (pMotion == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// �I�u�W�F�N�g�𐶐�
		pMotion = new CMotion;
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pMotion != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		if (FAILED(pMotion->Init()))
		{ // �������Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// NULL ��Ԃ�
			return nullptr;
		}
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �I�u�W�F�N�g2D�̃|�C���^��Ԃ�
	return pMotion;
}