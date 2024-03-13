//=============================================================================
//
// �T�E���h���� [sound.cpp]
// Author ��������
//
//=============================================================================
#include "sound.h"

//-----------------------------------------------------------------------------
// �ÓI�����o�ϐ��錾
//-----------------------------------------------------------------------------
CSound::SOUNDINFO CSound::m_aSoundInfo[CSound::SOUND_LABEL_MAX] =
{
	{ "data\\BGM\\TitleBGM.wav",-1 },		// �^�C�g��BGM
	{ "data\\BGM\\EntryBGM.wav",-1 },		// �G���g���[BGM
	{ "data\\BGM\\GameBGM.wav",-1 },		// �Q�[��BGM
	{ "data\\BGM\\ResultBGM.wav",-1 },		// ���U���gBGM
	{ "data\\BGM\\RankingBGM.wav",-1 },		// �����L���OBGM
	{ "data\\BGM\\destiny_of_victory.wav",-1 },		// �X�s�[�J�[BGM

	{ "data\\SE\\Select.wav",0 },			// �I����
	{ "data\\SE\\Decide.wav",0 },			// ���艹
	{ "data\\SE\\victory.wav",0 },			// ������
	{ "data\\SE\\CAT_Attack.wav",0},		// �l�R�̍U��
	{ "data\\SE\\Cat_Attack_Hit.wav",0},	// �l�R�̍U�����l�Y�~�Ƀq�b�g�����Ƃ��̉�
	{ "data\\SE\\walk_cat.wav",0},			// �l�R�̕��s��
	{ "data\\SE\\walk_rat.wav",0},			// �l�Y�~�̕��s��
	{ "data\\SE\\mousetrap_HIT.wav",0},		// �l�Y�~���Ƀn�}�鉹
	{ "data\\SE\\Cup_Falls.wav",0 },		// �R�b�v�������鉹
	{ "data\\SE\\TV_sandstorm.wav",-1 },		// �e���r�̍���
	{ "data\\SE\\press_the_switch.wav",0 },	// �X�C�b�`�����������̉�
	{ "data\\SE\\SetItem.wav",0},			// �A�C�e���ݒu��
	{ "data\\SE\\cleaning.wav",-1 },		// �|���@(�����o)
	{ "data\\SE\\Fan.wav",-1 },				// ��@
	{ "data\\SE\\med_bottle04.wav",0 },		// ��e
	{ "data\\SE\\Tarai_Hit.wav",0,},		// �^���C�����ɓ�����
	{ "data\\SE\\bottle_roll.wav",-1 },		// �y�b�g�{�g�����]���鉹
	{ "data\\SE\\bottle_over.wav",0 },		// �y�b�g�{�g�����|��鉹
	{ "data\\SE\\Pick_up.wav",0 },			// �E������
	{ "data\\SE\\tutorial_check.wav",0 },	// �`���[�g���A���̃`�F�b�N��
	{ "data\\SE\\TitleStart.wav",0 },		// �^�C�g���̃X�^�[�g��
	{ "data\\SE\\bubble.wav",0 },			// �`���[�g���A���̂ӂ������o����
	{ "data\\SE\\revival_gauge_save.wav",-1 },	// �����Œ��̉�
	{ "data\\SE\\mouse_revival.wav",0 },	// ������
	{ "data\\SE\\himo.wav",0 },				// �Ђ��������鉹
	{ "data\\SE\\mari.wav",0 },				// �܂�̉�
	{ "data\\SE\\honey_break.wav",0 },		// �I���̕r������鉹
	{ "data\\SE\\honey_leak.wav",0 },		// �I�����L���鉹
	{ "data\\SE\\honey_walk.wav",0 },		// �I���̏������
	{ "data\\SE\\book_down.wav",0 },		// �{�������鉹
	{ "data\\SE\\block_attack.wav",0 },		// �u���b�N�@����
	{ "data\\SE\\electricity_Biting.wav",-1 },	// ���̃r���r����
	{ "data\\SE\\banana_down.wav",0 },		// �o�i�i�����鉹
	{ "data\\SE\\banana_turuturu.wav",0 },	// �o�i�i�����鉹
	{ "data\\SE\\leash.wav",0 },			// ���[�h��
	{ "data\\SE\\Chu.wav",0 },				// �l�Y�~�̖����̉�
	{ "data\\SE\\finish.wav",0 },			// �I���̉�
	{ "data\\SE\\rat_Chuchu.wav",0 },		// ���������ɓ��鉹(�^�C�g��)
	{ "data\\SE\\title_blown_away.wav",0 },	// ������������΂���鉹(�^�C�g��)
	{ "data\\SE\\START_collide.wav",0 },	// �������Ԃ��鉹(�^�C�g��)
	{ "data\\SE\\confusion.wav",0 },		// �C�≹
	{ "data\\SE\\screw_winding.wav",-1 },	// �Ԃ̂˂�������
	{ "data\\SE\\jump.wav",0 },				// �l�Y�~�̃W�����v��
	{ "data\\SE\\Ratmecha_Run.wav",-1 },	// �l�Y�~���J�̑��s��
	{ "data\\SE\\Tutorial_OK.wav",0 },		// �`���[�g���A���̎��s������
	{ "data\\SE\\dynamite_explosion.wav",0 },	// �_�C�i�}�C�g�̔�����
	{ "data\\SE\\CurtainOpen.wav",0 },		// �J�[�e���̊J����
	{ "data\\SE\\Ratmecha_Break.wav",0 },	// �l�Y�~���J�̔j��
	{ "data\\SE\\CatDamage.wav",0 },		// �l�R�̃_���[�W��
	{ "data\\SE\\CountStart.wav",0 },		// �ŏ��̃J�E���g�_�E����
	{ "data\\SE\\CountEnd.wav",0 },			// �Ō�̃J�E���g�_�E����
};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSound::CSound()
{
	
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSound::~CSound()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CSound::Init(HWND hWnd)
{
	HRESULT hr;

	// COM���C�u�����̏�����
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2�I�u�W�F�N�g�̍쐬
	hr = XAudio2Create(&m_pXAudio2, 0);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "XAudio2�I�u�W�F�N�g�̍쐬�Ɏ��s�I", "�x���I", MB_ICONWARNING);

		// COM���C�u�����̏I������
		CoUninitialize();

		return E_FAIL;
	}

	// �}�X�^�[�{�C�X�̐���
	hr = m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "�}�X�^�[�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);

		if (m_pXAudio2 != NULL)
		{
			// XAudio2�I�u�W�F�N�g�̊J��
			m_pXAudio2->Release();
			m_pXAudio2 = NULL;
		}

		// COM���C�u�����̏I������
		CoUninitialize();

		return E_FAIL;
	}

	// �T�E���h�f�[�^�̏�����
	for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		HANDLE hFile;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD dwFiletype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// �o�b�t�@�̃N���A
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// �T�E���h�f�[�^�t�@�C���̐���
		hFile = CreateFile(m_aSoundInfo[nCntSound].pFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			MessageBox(hWnd, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}
		if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{// �t�@�C���|�C���^��擪�Ɉړ�
			MessageBox(hWnd, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}

		// WAVE�t�@�C���̃`�F�b�N
		hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		if (dwFiletype != 'EVAW')
		{
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(3)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		// �t�H�[�}�b�g�`�F�b�N
		hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		// �I�[�f�B�I�f�[�^�ǂݍ���
		hr = CheckChunk(hFile, 'atad', &m_aSizeAudio[nCntSound], &dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}
		m_apDataAudio[nCntSound] = (BYTE*)malloc(m_aSizeAudio[nCntSound]);
		hr = ReadChunkData(hFile, m_apDataAudio[nCntSound], m_aSizeAudio[nCntSound], dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		// �\�[�X�{�C�X�̐���
		hr = m_pXAudio2->CreateSourceVoice(&m_apSourceVoice[nCntSound], &(wfx.Format));
		if (FAILED(hr))
		{
			MessageBox(hWnd, "�\�[�X�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		// �o�b�t�@�̒l�ݒ�
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = m_aSizeAudio[nCntSound];
		buffer.pAudioData = m_apDataAudio[nCntSound];
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount = m_aSoundInfo[nCntSound].nCntLoop;

		// �I�[�f�B�I�o�b�t�@�̓o�^
		m_apSourceVoice[nCntSound]->SubmitSourceBuffer(&buffer);

		// �t�@�C�����N���[�Y
		CloseHandle(hFile);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CSound::Uninit(void)
{
	// �ꎞ��~
	for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if (m_apSourceVoice[nCntSound] != NULL)
		{
			// �ꎞ��~
			m_apSourceVoice[nCntSound]->Stop(0);

			// �\�[�X�{�C�X�̔j��
			m_apSourceVoice[nCntSound]->DestroyVoice();
			m_apSourceVoice[nCntSound] = NULL;

			// �I�[�f�B�I�f�[�^�̊J��
			free(m_apDataAudio[nCntSound]);
			m_apDataAudio[nCntSound] = NULL;
		}
	}

	// �}�X�^�[�{�C�X�̔j��
	m_pMasteringVoice->DestroyVoice();
	m_pMasteringVoice = NULL;

	if (m_pXAudio2 != NULL)
	{
		// XAudio2�I�u�W�F�N�g�̊J��
		m_pXAudio2->Release();
		m_pXAudio2 = NULL;
	}

	// COM���C�u�����̏I������
	CoUninitialize();
}

//=============================================================================
// �Z�O�����g�Đ�(�Đ����Ȃ��~)
//=============================================================================
HRESULT CSound::Play(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// �o�b�t�@�̒l�ݒ�
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_aSizeAudio[label];
	buffer.pAudioData = m_apDataAudio[label];
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = m_aSoundInfo[label].nCntLoop;

	// ��Ԏ擾
	m_apSourceVoice[label]->GetState(&xa2state);

	if (xa2state.BuffersQueued != 0)
	{// �Đ���

		// �ꎞ��~
		m_apSourceVoice[label]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		m_apSourceVoice[label]->FlushSourceBuffers();
	}

	// �I�[�f�B�I�o�b�t�@�̓o�^
	m_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

	// �Đ�
	m_apSourceVoice[label]->Start(0);

	return S_OK;
}

//=============================================================================
// �Z�O�����g��~(���x���w��)
//=============================================================================
void CSound::Stop(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;

	// ��Ԏ擾
	m_apSourceVoice[label]->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// �Đ���

		// �ꎞ��~
		m_apSourceVoice[label]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		m_apSourceVoice[label]->FlushSourceBuffers();
	}
}

//=============================================================================
// �Z�O�����g��~(�S��)
//=============================================================================
void CSound::Stop(void)
{
	// �ꎞ��~
	for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if (m_apSourceVoice[nCntSound] != NULL)
		{
			// �ꎞ��~
			m_apSourceVoice[nCntSound]->Stop(0);
		}
	}
}

//=============================================================================
// �`�����N�̃`�F�b�N
//=============================================================================
HRESULT CSound::CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;

	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^��擪�Ɉړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	while (hr == S_OK)
	{
		if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// �`�����N�f�[�^�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// �t�@�C���^�C�v�̓ǂݍ���
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if (SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// �t�@�C���|�C���^���`�����N�f�[�^���ړ�
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if (dwChunkType == format)
		{
			*pChunkSize = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if (dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}

	return S_OK;
}

//=============================================================================
// �`�����N�f�[�^�̓ǂݍ���
//=============================================================================
HRESULT CSound::ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;

	if (SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^���w��ʒu�܂ňړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// �f�[�^�̓ǂݍ���
		return HRESULT_FROM_WIN32(GetLastError());
	}

	return S_OK;
}

